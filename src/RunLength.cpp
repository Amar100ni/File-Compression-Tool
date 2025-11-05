#include "RunLength.h"
#include "Utility.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QElapsedTimer>

RunLength::RunLength() : compressionRatio(0.0), executionTime(0) {
}

bool RunLength::compress(const QString& inputFile, const QString& outputFile) {
    QElapsedTimer timer;
    timer.start();
    
    lastError.clear();
    
    // Read input file
    QFile input(inputFile);
    if (!input.open(QIODevice::ReadOnly)) {
        lastError = "Cannot open input file: " + inputFile;
        return false;
    }
    
    QByteArray data = input.readAll();
    input.close();
    
    if (data.isEmpty()) {
        lastError = "Input file is empty";
        return false;
    }
    
    qint64 originalSize = data.size();
    
    // Compress data
    QByteArray compressedData = rleCompress(data);
    
    // Write to output file
    QFile output(outputFile);
    if (!output.open(QIODevice::WriteOnly)) {
        lastError = "Cannot create output file: " + outputFile;
        return false;
    }
    
    QDataStream out(&output);
    
    // Write header: "RLE" magic number
    out.writeRawData("RLE", 3);
    
    // Write original data size
    out << static_cast<quint32>(originalSize);
    
    // Write compressed data
    out.writeRawData(compressedData.constData(), compressedData.size());
    
    output.close();
    
    // Calculate compression ratio
    qint64 compressedSize = Utility::getFileSize(outputFile);
    compressionRatio = Utility::calculateCompressionRatio(originalSize, compressedSize);
    executionTime = timer.elapsed();
    
    return true;
}

bool RunLength::decompress(const QString& inputFile, const QString& outputFile) {
    QElapsedTimer timer;
    timer.start();
    
    lastError.clear();
    
    // Read input file
    QFile input(inputFile);
    if (!input.open(QIODevice::ReadOnly)) {
        lastError = "Cannot open input file: " + inputFile;
        return false;
    }
    
    QDataStream in(&input);
    
    // Check magic number
    char magic[4] = {0};
    in.readRawData(magic, 3);
    if (strcmp(magic, "RLE") != 0) {
        lastError = "Invalid RLE compressed file";
        input.close();
        return false;
    }
    
    // Read original data size
    quint32 originalSize;
    in >> originalSize;
    
    // Read compressed data
    QByteArray compressedData = input.readAll();
    input.close();
    
    // Decompress data
    QByteArray decompressedData = rleDecompress(compressedData);
    
    if (decompressedData.size() != originalSize) {
        lastError = "Decompressed size doesn't match original size";
        return false;
    }
    
    // Write decompressed data
    QFile output(outputFile);
    if (!output.open(QIODevice::WriteOnly)) {
        lastError = "Cannot create output file: " + outputFile;
        return false;
    }
    
    output.write(decompressedData);
    output.close();
    
    // Calculate metrics
    qint64 compressedSize = Utility::getFileSize(inputFile);
    compressionRatio = Utility::calculateCompressionRatio(originalSize, compressedSize);
    executionTime = timer.elapsed();
    
    return true;
}

QByteArray RunLength::rleCompress(const QByteArray& data) {
    QByteArray compressed;
    int i = 0;
    int n = data.size();
    
    while (i < n) {
        char current = data[i];
        int count = 1;
        
        // Count consecutive characters
        while (i + count < n && data[i + count] == current && count < 255) {
            count++;
        }
        
        // Add to compressed data: count followed by character
        compressed.append(static_cast<char>(count));
        compressed.append(current);
        
        i += count;
    }
    
    return compressed;
}

QByteArray RunLength::rleDecompress(const QByteArray& compressedData) {
    QByteArray decompressed;
    int i = 0;
    int n = compressedData.size();
    
    while (i < n) {
        if (i + 1 >= n) {
            break; // Incomplete pair
        }
        
        char count = compressedData[i];
        char character = compressedData[i + 1];
        
        // Expand the run
        for (int j = 0; j < static_cast<unsigned char>(count); ++j) {
            decompressed.append(character);
        }
        
        i += 2;
    }
    
    return decompressed;
}