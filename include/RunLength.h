#ifndef RUNLENGTH_H
#define RUNLENGTH_H

#include <QString>
#include <QByteArray>

class RunLength {
public:
    RunLength();
    
    bool compress(const QString& inputFile, const QString& outputFile);
    bool decompress(const QString& inputFile, const QString& outputFile);
    double getCompressionRatio() const { return compressionRatio; }
    qint64 getExecutionTime() const { return executionTime; }
    QString getLastError() const { return lastError; }

private:
    QByteArray rleCompress(const QByteArray& data);
    QByteArray rleDecompress(const QByteArray& compressedData);
    
    double compressionRatio;
    qint64 executionTime;
    QString lastError;
};

#endif