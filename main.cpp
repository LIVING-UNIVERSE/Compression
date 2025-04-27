#include<iostream>
#include<string>
#include "compressor.h"
#include "decompressor.h"

using namespace std;

int main(){
    int choice;
    string inputFile,outputFile;
    cout << "======================================" << endl;
    cout << "      Huffman File Compressor         " << endl;
    cout << "======================================" << endl;

    cout << "Choose an option..."<<endl;
    cout << "(1.) Compress a file."<<endl;
    cout << "(2.) Decompress a file."<<endl;
    cout <<"Enter your choice..."<<endl;
    cin>>choice;
    
    cin.ignore();

    if(choice==1){
        cout << "Enter the input file name to compress (example: sample_files/input.txt): "<<endl;
        getline(cin, inputFile);

        cout << "Enter the output file name for compressed file (example: sample_files/compressed.bin): "<<endl;
        getline(cin, outputFile);

        compressFile(inputFile, outputFile);
        cout << "✅ Compression completed successfully!" << endl;
    }
    else if(choice==2){
        cout << "Enter the compressed file name to decompress (example: sample_files/compressed.bin): "<<endl;
        getline(cin, inputFile);

        cout << "Enter the output file name for decompressed file (example: sample_files/decompressed.txt): "<<endl;
        getline(cin, outputFile);

        decompressFile(inputFile, outputFile);
        cout << "\n✅ Decompression completed successfully!" << endl;
    }
    else{
        cout << "❌ Invalid choice. Please run the program again." << endl;
    }

    cout << "Thank you for using Huffman File Compressor! 🚀" << endl;

    return 0;

}