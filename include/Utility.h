#ifndef UTILITY_H
#define UTILITY_H

#include <QString>
#include <QFileInfo>
#include <QDateTime>
#include <QDir>

class Utility {
public:
    static qint64 getFileSize(const QString& filePath);
    static QString getCurrentTimestamp();
    static bool fileExists(const QString& filePath);
    static QString formatFileSize(qint64 bytes);
    static double calculateCompressionRatio(qint64 original, qint64 compressed);
    static QString getFileExtension(const QString& filePath);
    static QString safeFileName(const QString& originalName);
    static bool createDirectory(const QString& path);
    static QString getFileBaseName(const QString& filePath);
};

#endif