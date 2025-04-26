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
    cout << "(1.) Compress a file.";
    cout << "(2.) Decompress a file.";
    cout <<"Enter your choice...";
    cin>>choice;
    
    cin.ignore();

    if(choice==1){
        cout << "\nEnter the input file name to compress (example: sample_files/input.txt): ";
        getline(cin, inputFile);

        cout << "Enter the output file name for compressed file (example: sample_files/compressed.bin): ";
        getline(cin, outputFile);

        compressFile(inputFile, outputFile);
        cout << "\n✅ Compression completed successfully!" << endl;
    }
    else if(choice==2){
        cout << "\nEnter the compressed file name to decompress (example: sample_files/compressed.bin): ";
        getline(cin, inputFile);

        cout << "Enter the output file name for decompressed file (example: sample_files/decompressed.txt): ";
        getline(cin, outputFile);

        decompressFile(inputFile, outputFile);
        cout << "\n✅ Decompression completed successfully!" << endl;
    }
    else{
        cout << "\n❌ Invalid choice. Please run the program again." << endl;
    }

    cout << "\nThank you for using Huffman File Compressor! 🚀" << endl;

    return 0;

}