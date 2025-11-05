#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <QString>
#include <QMap>
#include <QVector>
#include <QByteArray>
#include <QQueue>

class HuffmanNode {
public:
    char data;
    unsigned freq;
    HuffmanNode *left, *right;
    
    HuffmanNode(char data, unsigned freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
    
    bool isLeaf() const {
        return left == nullptr && right == nullptr;
    }
};

class Huffman {
public:
    Huffman();
    ~Huffman();
    
    bool compress(const QString& inputFile, const QString& outputFile);
    bool decompress(const QString& inputFile, const QString& outputFile);
    double getCompressionRatio() const { return compressionRatio; }
    qint64 getExecutionTime() const { return executionTime; }
    QString getLastError() const { return lastError; }

private:
    void buildFrequencyTable(const QByteArray& data);
    HuffmanNode* buildHuffmanTree();
    void generateCodes(HuffmanNode* root, const QString& code);
    void clearTree(HuffmanNode* root);
    QByteArray encodeData(const QByteArray& data);
    QByteArray decodeData(const QByteArray& encodedData);
    QByteArray serializeTree(HuffmanNode* root);
    HuffmanNode* deserializeTree(const QByteArray& data, int& pos);
    void writeBit(QByteArray& buffer, int& bitPos, bool bit);
    bool readBit(const QByteArray& buffer, int& bitPos);
    
    QMap<char, unsigned> frequencyTable;
    QMap<char, QString> huffmanCodes;
    QMap<QString, char> reverseCodes;
    double compressionRatio;
    qint64 executionTime;
    QString lastError;
    HuffmanNode* huffmanTree;
};

#endif