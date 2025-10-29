#include "Huffman.h"
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <bitset>
#include <string>

struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char character, int frequency) {
        ch = character;
        freq = frequency;
        left = right = nullptr;
    }
};

struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// Build Huffman codes
void buildCodes(Node* root, std::string str, std::unordered_map<char, std::string> &huffmanCode) {
    if (!root) return;
    if (!root->left && !root->right)
        huffmanCode[root->ch] = str;

    buildCodes(root->left, str + "0", huffmanCode);
    buildCodes(root->right, str + "1", huffmanCode);
}

// Compress file
bool Huffman::compressFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in.is_open()) return false;

    std::string text((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();

    std::unordered_map<char, int> freq;
    for (char ch : text) freq[ch]++;

    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    for (auto pair : freq) pq.push(new Node(pair.first, pair.second));

    while (pq.size() != 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        Node *sum = new Node('\0', left->freq + right->freq);
        sum->left = left;
        sum->right = right;
        pq.push(sum);
    }

    Node* root = pq.top();

    std::unordered_map<char, std::string> huffmanCode;
    buildCodes(root, "", huffmanCode);

    std::string encodedStr;
    for (char ch : text) encodedStr += huffmanCode[ch];

    std::ofstream out(outputFile, std::ios::binary);
    if (!out.is_open()) return false;

    // Write frequency table first
    size_t tableSize = freq.size();
    out.write(reinterpret_cast<char*>(&tableSize), sizeof(tableSize));
    for (auto pair : freq) {
        out.write(&pair.first, sizeof(char));
        out.write(reinterpret_cast<char*>(&pair.second), sizeof(int));
    }

    // Write encoded string as bytes
    while (encodedStr.size() % 8 != 0) encodedStr += '0'; // pad with 0
    for (size_t i = 0; i < encodedStr.size(); i += 8) {
        std::bitset<8> b(encodedStr.substr(i, 8));
        char c = static_cast<char>(b.to_ulong());
        out.write(&c, 1);
    }

    out.close();
    return true;
}

// Decompress file
bool Huffman::decompressFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in.is_open()) return false;

    size_t tableSize;
    in.read(reinterpret_cast<char*>(&tableSize), sizeof(tableSize));
    std::unordered_map<char, int> freq;
    for (size_t i = 0; i < tableSize; i++) {
        char ch;
        int f;
        in.read(&ch, sizeof(char));
        in.read(reinterpret_cast<char*>(&f), sizeof(int));
        freq[ch] = f;
    }

    // Rebuild Huffman tree
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    for (auto pair : freq) pq.push(new Node(pair.first, pair.second));
    while (pq.size() != 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        Node *sum = new Node('\0', left->freq + right->freq);
        sum->left = left;
        sum->right = right;
        pq.push(sum);
    }
    Node* root = pq.top();

    // Read rest of file as bits
    std::string bits;
    char c;
    while (in.get(c)) {
        std::bitset<8> b(c);
        bits += b.to_string();
    }
    in.close();

    std::ofstream out(outputFile, std::ios::binary);
    Node* curr = root;
    for (char bit : bits) {
        if (bit == '0') curr = curr->left;
        else curr = curr->right;

        if (!curr->left && !curr->right) {
            out.put(curr->ch);
            curr = root;
        }
    }
    out.close();
    return true;
}
