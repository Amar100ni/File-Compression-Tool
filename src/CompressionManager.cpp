#include "CompressionManager.h"
#include "Huffman.h"
#include "RunLength.h"
#include "Utility.h"
#include "ReportGenerator.h"
#include <QDir>
#include <QElapsedTimer>

CompressionManager::CompressionManager(QObject* parent) : QObject(parent) {
}

CompressionResult CompressionManager::compressFile(const QString& inputFile, 
                                                 CompressionAlgorithm algorithm,
                                                 const QString& outputDir) {
    QElapsedTimer timer;
    timer.start();
    
    CompressionResult result;
    result.operationType = "Compression";
    result.algorithm = algorithm;
    
    // Validate input file
    if (!Utility::fileExists(inputFile)) {
        result.success = false;
        result.message = "Input file does not exist: " + inputFile;
        return result;
    }
    
    // Get original file size
    result.originalSize = Utility::getFileSize(inputFile);
    if (result.originalSize == 0) {
        result.success = false;
        result.message = "Input file is empty";
        return result;
    }
    
    // Generate output file name
    QString outputFile = generateOutputFileName(inputFile, algorithm, true);
    if (!outputDir.isEmpty()) {
        QDir dir(outputDir);
        outputFile = dir.absoluteFilePath(Utility::getFileBaseName(outputFile));
    }
    
    // Perform compression based on algorithm
    bool compressionSuccess = false;
    
    switch (algorithm) {
        case CompressionAlgorithm::HUFFMAN: {
            Huffman huffman;
            emit progressUpdated(25);
            compressionSuccess = huffman.compress(inputFile, outputFile);
            emit progressUpdated(75);
            if (compressionSuccess) {
                result.compressionRatio = huffman.getCompressionRatio();
                result.executionTime = huffman.getExecutionTime();
            } else {
                result.message = "Huffman compression failed: " + huffman.getLastError();
            }
            break;
        }
        case CompressionAlgorithm::RUN_LENGTH: {
            RunLength rle;
            emit progressUpdated(25);
            compressionSuccess = rle.compress(inputFile, outputFile);
            emit progressUpdated(75);
            if (compressionSuccess) {
                result.compressionRatio = rle.getCompressionRatio();
                result.executionTime = rle.getExecutionTime();
            } else {
                result.message = "RLE compression failed: " + rle.getLastError();
            }
            break;
        }
    }
    
    emit progressUpdated(100);
    
    if (compressionSuccess) {
        result.success = true;
        result.compressedSize = Utility::getFileSize(outputFile);
        result.outputFile = outputFile;
        result.message = QString("Compression successful! Ratio: %1% Time: %2ms")
                        .arg(result.compressionRatio, 0, 'f', 2)
                        .arg(result.executionTime);
        
        // Generate report
        ReportGenerator::generateReport(result);
    } else {
        result.success = false;
    }
    
    emit operationCompleted(result);
    return result;
}

CompressionResult CompressionManager::decompressFile(const QString& inputFile,
                                                   const QString& outputDir) {
    QElapsedTimer timer;
    timer.start();
    
    CompressionResult result;
    result.operationType = "Decompression";
    
    // Validate input file
    if (!Utility::fileExists(inputFile)) {
        result.success = false;
        result.message = "Input file does not exist: " + inputFile;
        return result;
    }
    
    // Detect algorithm from file extension
    result.algorithm = detectAlgorithm(inputFile);
    if (result.algorithm == CompressionAlgorithm::HUFFMAN && 
        !inputFile.endsWith(".huff") && !inputFile.endsWith(".huffman")) {
        result.success = false;
        result.message = "Cannot detect compression algorithm from file extension";
        return result;
    }
    
    // Get compressed file size
    result.compressedSize = Utility::getFileSize(inputFile);
    
    // Generate output file name
    QString outputFile = generateOutputFileName(inputFile, result.algorithm, false);
    if (!outputDir.isEmpty()) {
        QDir dir(outputDir);
        outputFile = dir.absoluteFilePath(Utility::getFileBaseName(outputFile));
    }
    
    // Perform decompression based on algorithm
    bool decompressionSuccess = false;
    
    switch (result.algorithm) {
        case CompressionAlgorithm::HUFFMAN: {
            Huffman huffman;
            emit progressUpdated(25);
            decompressionSuccess = huffman.decompress(inputFile, outputFile);
            emit progressUpdated(75);
            if (decompressionSuccess) {
                result.compressionRatio = huffman.getCompressionRatio();
                result.executionTime = huffman.getExecutionTime();
            } else {
                result.message = "Huffman decompression failed: " + huffman.getLastError();
            }
            break;
        }
        case CompressionAlgorithm::RUN_LENGTH: {
            RunLength rle;
            emit progressUpdated(25);
            decompressionSuccess = rle.decompress(inputFile, outputFile);
            emit progressUpdated(75);
            if (decompressionSuccess) {
                result.compressionRatio = rle.getCompressionRatio();
                result.executionTime = rle.getExecutionTime();
            } else {
                result.message = "RLE decompression failed: " + rle.getLastError();
            }
            break;
        }
    }
    
    emit progressUpdated(100);
    
    if (decompressionSuccess) {
        result.success = true;
        result.originalSize = Utility::getFileSize(outputFile);
        result.outputFile = outputFile;
        result.message = QString("Decompression successful! Ratio: %1% Time: %2ms")
                        .arg(result.compressionRatio, 0, 'f', 2)
                        .arg(result.executionTime);
        
        // Generate report
        ReportGenerator::generateReport(result);
    } else {
        result.success = false;
    }
    
    emit operationCompleted(result);
    return result;
}

QString CompressionManager::algorithmToString(CompressionAlgorithm algorithm) {
    switch (algorithm) {
        case CompressionAlgorithm::HUFFMAN: return "Huffman Coding";
        case CompressionAlgorithm::RUN_LENGTH: return "Run-Length Encoding";
        default: return "Unknown";
    }
}

QString CompressionManager::getAlgorithmExtension(CompressionAlgorithm algorithm) {
    switch (algorithm) {
        case CompressionAlgorithm::HUFFMAN: return ".huff";
        case CompressionAlgorithm::RUN_LENGTH: return ".rle";
        default: return ".compressed";
    }
}

QString CompressionManager::generateOutputFileName(const QString& inputFile, 
                                                 CompressionAlgorithm algorithm, 
                                                 bool isCompression) const {
    QFileInfo fileInfo(inputFile);
    QString baseName = fileInfo.completeBaseName();
    QString path = fileInfo.absolutePath();
    
    if (isCompression) {
        return path + "/" + baseName + getAlgorithmExtension(algorithm);
    } else {
        // For decompression, remove compression extension and add .decoded
        QString decompressedName = baseName;
        if (baseName.endsWith(".huff") || baseName.endsWith(".rle")) {
            QFileInfo decompressedInfo(baseName);
            decompressedName = decompressedInfo.completeBaseName();
        }
        return path + "/" + decompressedName + "_decoded" + fileInfo.suffix();
    }
}

CompressionAlgorithm CompressionManager::detectAlgorithm(const QString& filePath) const {
    if (filePath.endsWith(".huff") || filePath.endsWith(".huffman")) {
        return CompressionAlgorithm::HUFFMAN;
    } else if (filePath.endsWith(".rle")) {
        return CompressionAlgorithm::RUN_LENGTH;
    } else {
        // Try to detect by reading file header
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly)) {
            char header[8] = {0};
            file.read(header, 7);
            file.close();
            
            if (strcmp(header, "HUFFMAN") == 0) {
                return CompressionAlgorithm::HUFFMAN;
            } else if (strcmp(header, "RLE") == 0) {
                return CompressionAlgorithm::RUN_LENGTH;
            }
        }
        
        return CompressionAlgorithm::HUFFMAN; // Default
    }
}