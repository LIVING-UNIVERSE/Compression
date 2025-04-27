#include<iostream>
#include "decompressor.h"
#include<string>
#include<fstream>
#include<unordered_map>
#include<bitset>

using namespace std;

struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode(char chr, int val) {
        ch = chr;
        freq = val;
        left = right = NULL;
    }
};

void decompressFile(string &inputFile, string &outputFile) {
    // (1.) Open input file
    ifstream input(inputFile, ios::binary);
    if (!input.is_open()) {
        cout << "Error: Could not open input file: " << inputFile << endl;
        return;
    }

    unordered_map<string, char> HuffmanCodes;

    // (2.) Fetch Huffman codes table
    int tableSize;
    input.read(reinterpret_cast<char*>(&tableSize), sizeof(tableSize));

    for (int i = 0; i < tableSize; i++) {
        char ch;
        input.get(ch);

        int codeLength;
        input.read(reinterpret_cast<char*>(&codeLength), sizeof(codeLength));

        string code;
        for (int j = 0; j < (codeLength + 7) / 8; j++) {
            unsigned char byte;
            input.get(reinterpret_cast<char&>(byte));
            bitset<8> bits(byte);
            for (int k = 0; k < 8 && 8 * j + k < codeLength; k++) {
                code.push_back(bits[7 - k] ? '1' : '0');
            }
        }
        HuffmanCodes[code] = ch;
    }

    // (3.) Read the padding
    unsigned char padding;
    input.get(reinterpret_cast<char&>(padding));

    // (4.) Read encoded bits
    string encodedString = "";
    char byte;
    while (input.get(byte)) {
        bitset<8> bits(byte);
        encodedString += bits.to_string();
    }

    // Remove padding bits at the end
    if (padding > 0 && padding <= 8) {
        encodedString = encodedString.substr(0, encodedString.size() - padding);
    }

    // (5.) Write decoded output to output file
    ofstream output(outputFile, ios::binary);
    if (!output.is_open()) {
        cout << "Error: Could not open output file: " << outputFile << endl;
        return;
    }

    string currentCode = "";
    for (size_t i = 0; i < encodedString.size(); i++) {
        currentCode += encodedString[i];
        if (HuffmanCodes.find(currentCode) != HuffmanCodes.end()) {
            output.put(HuffmanCodes[currentCode]);
            currentCode = "";
        }
    }

    input.close();
    output.close();

    cout << "Decompression completed successfully!" << endl;
}
