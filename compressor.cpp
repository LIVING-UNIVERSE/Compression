#include<iostream>
#include "compressor.h"
#include<unordered_map>
#include<vector>
#include<fstream>
#include<queue>
#include<bitset>

using namespace std;


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



struct compare{
    bool operator()(HuffmanNode* &a, HuffmanNode* &b){
        return a->freq<b->freq;
    }
};


void countFreq(ifstream & input, unordered_map<char,int> &m){
    char ch;
    while(input.get(ch)){
        m[ch]++;
    }
}

HuffmanNode* buildHuffmanTree(priority_queue<HuffmanNode* ,vector<HuffmanNode*>, compare> &pq){
    while(pq.size()>1){
        HuffmanNode* left=pq.top();pq.pop();
        HuffmanNode* right=pq.top();pq.pop();
        HuffmanNode* node = new HuffmanNode('\0',left->freq+right->freq);
        node->left=left;
        node->right=right;
        pq.push(node);
    }
    return pq.top();
}


void generateHuffmanCodes(HuffmanNode* head,unordered_map<char,string> & m,string s){
    if(head==NULL) return ;
    if(head->left==NULL && head->right ==NULL){
        m[head->ch]=s;
    }
    generateHuffmanCodes(head->left,m,s+'0');
    generateHuffmanCodes(head->right,m,s+'1');
}



void compressFile(string &inputFile, string &outputFile){
    // (1.) taking input
    ifstream input(inputFile,ios:: binary);

    if(!input.is_open()){
        cout << "Error: Could not open input file: " << inputFile << endl;
        return;
    }

    // (2.) count frequecies
    unordered_map<char,int> freqMap;
    countFreq(input,freqMap);

    input.close();
    input.open(inputFile,ios:: binary);


    // (3.) Building Huffman Tree
    priority_queue<HuffmanNode* ,vector<HuffmanNode*>, compare> pq;

    for(auto it=freqMap.begin();it!=freqMap.end();it++){
        HuffmanNode* node = new HuffmanNode(it->first,it->second);
        pq.push(node);
    }


    HuffmanNode* root= buildHuffmanTree(pq);


    // (4.) Generating Huffman codes
    unordered_map<char,string> HuffmanCodes;
    string s="";
    generateHuffmanCodes(root,HuffmanCodes,s);


    // (5.) Writing output
    ofstream output(outputFile,ios::binary);
    if(!output.is_open()){
        cout << "Error: Could not open output file: " << outputFile << endl;
        return;
    }


    // (6.) Writing Huffman codes in the output for further decomprssion
    int tableSize= HuffmanCodes.size();
    output.write(reinterpret_cast<const char*>(&tableSize),sizeof(tableSize));

    for(auto& pair : HuffmanCodes){
        output.put(pair.first);

        int codeLength = pair.second.size();
        output.write(reinterpret_cast<const char*>(&codeLength), sizeof(codeLength));
        bitset<256> bits(pair.second);
        for(int i=0;i<(codeLength+7)/8;i++){
            unsigned char byte=0;
            for(int j=0;j<8 && (i*8+j)<codeLength;j++){
                if(pair.second[i*8+7]=='1'){
                    byte|=(1<<(7-j));
                }
            }
            output.put(byte);
        }
    }

    // Encoding actual file content
    char chr;
    string encodedString = "";
    while(input.get(chr)){
        encodedString+=HuffmanCodes[chr];
    }

    unsigned char padding=8-encodedString.size()%8;
    if(padding!=8){
        while(padding--){
            encodedString+='0';
        }
    }
    else{
        padding=0;
    }

    output.put(static_cast<unsigned char>(padding));

    // Write data in ouptut as bytes
    for(int i=0;i<encodedString.size();i=i+8){
        bitset<8> bits(encodedString.substr(i,8));
        output.put(static_cast<unsigned char>(bits.to_ulong()));
    }

    input.close();
    output.close();

    cout<<" Compression Completed Successfully!" <<endl;
}