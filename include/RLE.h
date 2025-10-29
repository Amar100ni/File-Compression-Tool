#ifndef RLE_H
#define RLE_H

#include <string>
#include <fstream>
#include <sstream>
#include <cctype>

class RLE {
public:
    // Compress input string and return compressed string
    static std::string compress(const std::string& input);

    // Decompress input string and return original string
    static std::string decompress(const std::string& input);

    // Compress a file and save to another file
    static bool compressFile(const std::string& inputFile, const std::string& outputFile);

    // Decompress a file and save to another file
    static bool decompressFile(const std::string& inputFile, const std::string& outputFile);
};

#endif
