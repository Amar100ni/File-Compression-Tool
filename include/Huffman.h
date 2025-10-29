#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <sstream>

class Huffman {
public:
    // Compress input string and return compressed binary string
    static std::string compress(const std::string& input, std::unordered_map<char, std::string>& huffmanCode);

    // Decompress binary string using Huffman codes
    static std::string decompress(const std::string& binary, const std::unordered_map<char, std::string>& huffmanCode);

    // Compress a file and save to another file
    static bool compressFile(const std::string& inputFile, const std::string& outputFile);

    // Decompress a file and save to another file
    static bool decompressFile(const std::string& inputFile, const std::string& outputFile);
};

#endif
