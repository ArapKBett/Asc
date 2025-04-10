#include "crypto.h"
#include <fstream>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <iostream>

const std::string Crypto::key = "12345678901234567890123456789012";  // 32 bytes
const std::string Crypto::iv = "abcdefghijklmnop";                  // 16 bytes

void Crypto::encryptFile(const std::string& inputFile, const std::string& outputFile) {
    unsigned char iv[AES_BLOCK_SIZE];
    memcpy(iv, Crypto::iv.c_str(), AES_BLOCK_SIZE);

    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);
    outFile.write((char*)iv, AES_BLOCK_SIZE);  // Write IV

    AES_KEY aesKey;
    AES_set_encrypt_key((unsigned char*)key.c_str(), 256, &aesKey);

    unsigned char inBuf[AES_BLOCK_SIZE], outBuf[AES_BLOCK_SIZE];
    while (inFile.read((char*)inBuf, AES_BLOCK_SIZE) || inFile.gcount()) {
        int bytesRead = inFile.gcount();
        AES_cbc_encrypt(inBuf, outBuf, bytesRead, &aesKey, iv, AES_ENCRYPT);
        outFile.write((char*)outBuf, bytesRead);
    }
}

void Crypto::decryptFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);

    unsigned char iv[AES_BLOCK_SIZE];
    inFile.read((char*)iv, AES_BLOCK_SIZE);

    AES_KEY aesKey;
    AES_set_decrypt_key((unsigned char*)key.c_str(), 256, &aesKey);

    unsigned char inBuf[AES_BLOCK_SIZE], outBuf[AES_BLOCK_SIZE];
    while (inFile.read((char*)inBuf, AES_BLOCK_SIZE) || inFile.gcount()) {
        int bytesRead = inFile.gcount();
        AES_cbc_encrypt(inBuf, outBuf, bytesRead, &aesKey, iv, AES_DECRYPT);
        outFile.write((char*)outBuf, bytesRead);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " [encrypt/decrypt] input_file output_file\n";
        return 1;
    }
    std::string mode = argv[1], inFile = argv[2], outFile = argv[3];
    if (mode == "encrypt") Crypto::encryptFile(inFile, outFile);
    else if (mode == "decrypt") Crypto::decryptFile(inFile, outFile);
    else std::cerr << "Invalid mode\n";
    return 0;
}
