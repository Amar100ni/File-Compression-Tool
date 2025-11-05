#include "Utility.h"
#include <QFileInfo>
#include <QDateTime>
#include <QDir>

qint64 Utility::getFileSize(const QString& filePath) {
    QFileInfo fileInfo(filePath);
    return fileInfo.exists() ? fileInfo.size() : -1;
}

QString Utility::getCurrentTimestamp() {
    return QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
}

bool Utility::fileExists(const QString& filePath) {
    return QFileInfo::exists(filePath);
}

QString Utility::formatFileSize(qint64 bytes) {
    const qint64 KB = 1024;
    const qint64 MB = KB * 1024;
    const qint64 GB = MB * 1024;
    
    if (bytes >= GB) {
        return QString("%1 GB").arg(bytes / static_cast<double>(GB), 0, 'f', 2);
    } else if (bytes >= MB) {
        return QString("%1 MB").arg(bytes / static_cast<double>(MB), 0, 'f', 2);
    } else if (bytes >= KB) {
        return QString("%1 KB").arg(bytes / static_cast<double>(KB), 0, 'f', 2);
    } else {
        return QString("%1 bytes").arg(bytes);
    }
}

double Utility::calculateCompressionRatio(qint64 original, qint64 compressed) {
    if (original == 0) return 0.0;
    return (static_cast<double>(compressed) / original) * 100.0;
}

QString Utility::getFileExtension(const QString& filePath) {
    QFileInfo fileInfo(filePath);
    return fileInfo.suffix();
}

QString Utility::safeFileName(const QString& originalName) {
    QString safe = originalName;
    // Remove or replace invalid characters
    safe.replace(':', '_');
    safe.replace('*', '_');
    safe.replace('?', '_');
    safe.replace('"', '_');
    safe.replace('<', '_');
    safe.replace('>', '_');
    safe.replace('|', '_');
    return safe;
}

bool Utility::createDirectory(const QString& path) {
    QDir dir;
    return dir.mkpath(path);
}

QString Utility::getFileBaseName(const QString& filePath) {
    QFileInfo fileInfo(filePath);
    return fileInfo.fileName();
}