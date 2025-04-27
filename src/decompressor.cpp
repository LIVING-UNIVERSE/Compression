#include<iostream>
#include "decompressor.h"
#include<string>
#include<fstream>


struct HuffmanNode{
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode(char chr, int val){
        ch=chr;
        freq=val;
        left=right=NULL;
    }
};


void decompressFile(string &inputFile,string &outputFile){
    ifstream input(inputFile,ios:: binary);
    
}