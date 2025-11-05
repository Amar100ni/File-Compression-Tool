#include "Huffman.h"
#include "Utility.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QQueue>
#include <QVector>
#include <QElapsedTimer>
#include <algorithm>

Huffman::Huffman() : compressionRatio(0.0), executionTime(0), huffmanTree(nullptr) {
}

Huffman::~Huffman() {
    if (huffmanTree) {
        clearTree(huffmanTree);
    }
}

bool Huffman::compress(const QString& inputFile, const QString& outputFile) {
    QElapsedTimer timer;
    timer.start();
    
    lastError.clear();
    frequencyTable.clear();
    huffmanCodes.clear();
    reverseCodes.clear();
    
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
    
    // Build frequency table
    buildFrequencyTable(data);
    
    // Build Huffman tree
    huffmanTree = buildHuffmanTree();
    if (!huffmanTree) {
        lastError = "Failed to build Huffman tree";
        return false;
    }
    
    // Generate codes
    generateCodes(huffmanTree, "");
    
    // Encode data
    QByteArray encodedData = encodeData(data);
    
    // Write to output file
    QFile output(outputFile);
    if (!output.open(QIODevice::WriteOnly)) {
        lastError = "Cannot create output file: " + outputFile;
        return false;
    }
    
    QDataStream out(&output);
    
    // Write header: "HUFFMAN" magic number
    out.writeRawData("HUFFMAN", 7);
    
    // Write frequency table size
    quint32 tableSize = frequencyTable.size();
    out << tableSize;
    
    // Write frequency table
    for (auto it = frequencyTable.begin(); it != frequencyTable.end(); ++it) {
        out << it.key() << it.value();
    }
    
    // Write encoded data size
    quint32 encodedSize = encodedData.size();
    out << encodedSize;
    
    // Write encoded data
    out.writeRawData(encodedData.constData(), encodedData.size());
    
    output.close();
    
    // Calculate compression ratio
    qint64 compressedSize = Utility::getFileSize(outputFile);
    compressionRatio = Utility::calculateCompressionRatio(originalSize, compressedSize);
    executionTime = timer.elapsed();
    
    // Clean up
    clearTree(huffmanTree);
    huffmanTree = nullptr;
    
    return true;
}

bool Huffman::decompress(const QString& inputFile, const QString& outputFile) {
    QElapsedTimer timer;
    timer.start();
    
    lastError.clear();
    frequencyTable.clear();
    huffmanCodes.clear();
    reverseCodes.clear();
    
    // Read input file
    QFile input(inputFile);
    if (!input.open(QIODevice::ReadOnly)) {
        lastError = "Cannot open input file: " + inputFile;
        return false;
    }
    
    QDataStream in(&input);
    
    // Check magic number
    char magic[8] = {0};
    in.readRawData(magic, 7);
    if (strcmp(magic, "HUFFMAN") != 0) {
        lastError = "Invalid Huffman compressed file";
        input.close();
        return false;
    }
    
    // Read frequency table
    quint32 tableSize;
    in >> tableSize;
    
    for (quint32 i = 0; i < tableSize; ++i) {
        char ch;
        unsigned freq;
        in >> ch >> freq;
        frequencyTable[ch] = freq;
    }
    
    // Read encoded data size
    quint32 encodedSize;
    in >> encodedSize;
    
    // Read encoded data
    QByteArray encodedData(encodedSize, 0);
    in.readRawData(encodedData.data(), encodedSize);
    input.close();
    
    // Build Huffman tree from frequency table
    huffmanTree = buildHuffmanTree();
    if (!huffmanTree) {
        lastError = "Failed to rebuild Huffman tree";
        return false;
    }
    
    // Generate codes for decoding
    generateCodes(huffmanTree, "");
    
    // Decode data
    QByteArray decodedData = decodeData(encodedData);
    
    // Write decoded data to output file
    QFile output(outputFile);
    if (!output.open(QIODevice::WriteOnly)) {
        lastError = "Cannot create output file: " + outputFile;
        return false;
    }
    
    output.write(decodedData);
    output.close();
    
    // Calculate metrics
    qint64 compressedSize = Utility::getFileSize(inputFile);
    qint64 decompressedSize = decodedData.size();
    compressionRatio = Utility::calculateCompressionRatio(decompressedSize, compressedSize);
    executionTime = timer.elapsed();
    
    // Clean up
    clearTree(huffmanTree);
    huffmanTree = nullptr;
    
    return true;
}

void Huffman::buildFrequencyTable(const QByteArray& data) {
    for (char ch : data) {
        frequencyTable[ch]++;
    }
}

HuffmanNode* Huffman::buildHuffmanTree() {
    if (frequencyTable.isEmpty()) {
        return nullptr;
    }
    
    QVector<HuffmanNode*> nodes;
    for (auto it = frequencyTable.begin(); it != frequencyTable.end(); ++it) {
        nodes.append(new HuffmanNode(it.key(), it.value()));
    }
    
    while (nodes.size() > 1) {
        // Sort nodes by frequency (ascending)
        std::sort(nodes.begin(), nodes.end(), [](HuffmanNode* a, HuffmanNode* b) {
            return a->freq < b->freq;
        });
        
        // Take two nodes with smallest frequency
        HuffmanNode* left = nodes.takeAt(0);
        HuffmanNode* right = nodes.takeAt(0);
        
        // Create new internal node
        HuffmanNode* internal = new HuffmanNode('\0', left->freq + right->freq);
        internal->left = left;
        internal->right = right;
        
        nodes.append(internal);
    }
    
    return nodes.isEmpty() ? nullptr : nodes.first();
}

void Huffman::generateCodes(HuffmanNode* root, const QString& code) {
    if (!root) return;
    
    if (root->isLeaf()) {
        huffmanCodes[root->data] = code;
        reverseCodes[code] = root->data;
    } else {
        generateCodes(root->left, code + "0");
        generateCodes(root->right, code + "1");
    }
}

void Huffman::clearTree(HuffmanNode* root) {
    if (!root) return;
    
    clearTree(root->left);
    clearTree(root->right);
    delete root;
}

QByteArray Huffman::encodeData(const QByteArray& data) {
    QString bitString;
    
    // Convert each character to its Huffman code
    for (char ch : data) {
        bitString += huffmanCodes[ch];
    }
    
    // Convert bit string to byte array
    QByteArray encoded;
    int bitPos = 0;
    char currentByte = 0;
    
    for (QChar bit : bitString) {
        if (bit == '1') {
            currentByte |= (1 << (7 - bitPos));
        }
        
        bitPos++;
        if (bitPos == 8) {
            encoded.append(currentByte);
            currentByte = 0;
            bitPos = 0;
        }
    }
    
    // Add remaining bits
    if (bitPos > 0) {
        encoded.append(currentByte);
    }
    
    return encoded;
}

QByteArray Huffman::decodeData(const QByteArray& encodedData) {
    // Convert byte array to bit string
    QString bitString;
    for (uchar byte : encodedData) {
        for (int i = 7; i >= 0; --i) {
            bitString.append((byte & (1 << i)) ? '1' : '0');
        }
    }
    
    // Decode using Huffman tree
    QByteArray decoded;
    HuffmanNode* current = huffmanTree;
    
    for (QChar bit : bitString) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        
        if (current->isLeaf()) {
            decoded.append(current->data);
            current = huffmanTree;
        }
    }
    
    return decoded;
}