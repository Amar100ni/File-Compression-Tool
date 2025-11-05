#include "ReportGenerator.h"
#include "Utility.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDateTime>

QString ReportGenerator::lastReportPath = "";

void ReportGenerator::generateReport(const CompressionResult& result) {
    ensureReportsDirectoryExists();
    
    QString reportContent = generateReportContent(result);
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    QString operation = result.operationType.toLower();
    QString algorithm = CompressionManager::algorithmToString(result.algorithm);
    algorithm = algorithm.replace(" ", "_").toLower();
    
    QString reportFileName = QString("reports/operation_reports/%1_%2_%3_report.txt")
                           .arg(timestamp, operation, algorithm);
    
    QFile reportFile(reportFileName);
    if (reportFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&reportFile);
        out << reportContent;
        reportFile.close();
        
        lastReportPath = reportFileName;
    }
}

QString ReportGenerator::getReportsDirectory() {
    return "reports/operation_reports";
}

QString ReportGenerator::getLastReportPath() {
    return lastReportPath;
}

void ReportGenerator::ensureReportsDirectoryExists() {
    QDir dir;
    dir.mkpath("reports/operation_reports");
}

QString ReportGenerator::generateReportContent(const CompressionResult& result) {
    QString content;
    QTextStream stream(&content);
    
    stream << "FILE COMPRESSION TOOL - OPERATION REPORT\n";
    stream << "=========================================\n\n";
    
    stream << "Operation Details:\n";
    stream << "------------------\n";
    stream << "Operation Type: " << result.operationType << "\n";
    stream << "Algorithm: " << CompressionManager::algorithmToString(result.algorithm) << "\n";
    stream << "Timestamp: " << Utility::getCurrentTimestamp() << "\n";
    stream << "Status: " << (result.success ? "SUCCESS" : "FAILED") << "\n\n";
    
    if (result.success) {
        stream << "File Details:\n";
        stream << "-------------\n";
        
        if (result.operationType == "Compression") {
            stream << "Input File Size: " << Utility::formatFileSize(result.originalSize) 
                   << " (" << result.originalSize << " bytes)\n";
            stream << "Output File Size: " << Utility::formatFileSize(result.compressedSize) 
                   << " (" << result.compressedSize << " bytes)\n";
        } else {
            stream << "Input File Size: " << Utility::formatFileSize(result.compressedSize) 
                   << " (" << result.compressedSize << " bytes)\n";
            stream << "Output File Size: " << Utility::formatFileSize(result.originalSize) 
                   << " (" << result.originalSize << " bytes)\n";
        }
        
        stream << "Compression Ratio: " << QString::number(result.compressionRatio, 'f', 2) << "%\n";
        stream << "Execution Time: " << result.executionTime << " ms\n\n";
    }
    
    stream << "Technical Information:\n";
    stream << "---------------------\n";
    stream << "Space Saved: " << QString::number(100.0 - result.compressionRatio, 'f', 2) << "%\n";
    
    if (result.operationType == "Compression") {
        double savedBytes = result.originalSize - result.compressedSize;
        stream << "Bytes Saved: " << Utility::formatFileSize(static_cast<qint64>(savedBytes)) << "\n";
    }
    
    stream << "\nEnd of Report\n";
    
    return content;
}