#ifndef COMPRESSIONMANAGER_H
#define COMPRESSIONMANAGER_H

#include <QString>
#include <QObject>
#include <QElapsedTimer>

enum class CompressionAlgorithm {
    HUFFMAN,
    RUN_LENGTH
};

struct CompressionResult {
    bool success;
    QString message;
    double compressionRatio;
    qint64 originalSize;
    qint64 compressedSize;
    qint64 executionTime;
    QString outputFile;
    CompressionAlgorithm algorithm;
    QString operationType;
};

class CompressionManager : public QObject {
    Q_OBJECT

public:
    CompressionManager(QObject* parent = nullptr);
    
    CompressionResult compressFile(const QString& inputFile, 
                                 CompressionAlgorithm algorithm,
                                 const QString& outputDir = "");
    CompressionResult decompressFile(const QString& inputFile,
                                   const QString& outputDir = "");

    static QString algorithmToString(CompressionAlgorithm algorithm);
    static QString getAlgorithmExtension(CompressionAlgorithm algorithm);

signals:
    void progressUpdated(int percentage);
    void operationCompleted(const CompressionResult& result);

private:
    QString generateOutputFileName(const QString& inputFile, 
                                 CompressionAlgorithm algorithm, 
                                 bool isCompression) const;
    CompressionAlgorithm detectAlgorithm(const QString& filePath) const;
};

#endif