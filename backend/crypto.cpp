#include "crypto.h"
#include <fstream>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <iostream>
#include <cstring>

const std::string Crypto::key = "12345678901234567890123456789012";  // 32 bytes
const std::string Crypto::iv = "abcdefghijklmnop";                  // 16 bytes

void Crypto::encryptFile(const std::string& inputFile, const std::string& outputFile) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        std::cerr << "Failed to create EVP context\n";
        return;
    }

    unsigned char iv[Crypto::AES_BLOCK_SIZE];
    memcpy(iv, Crypto::iv.c_str(), Crypto::AES_BLOCK_SIZE);

    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);
    outFile.write((char*)iv, Crypto::AES_BLOCK_SIZE);  // Write IV

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)key.c_str(), iv) != 1) {
        std::cerr << "Failed to initialize encryption\n";
        EVP_CIPHER_CTX_free(ctx);
        return;
    }

    unsigned char inBuf[1024], outBuf[1024 + Crypto::AES_BLOCK_SIZE];
    int outLen;
    while (inFile.read((char*)inBuf, sizeof(inBuf)) || inFile.gcount()) {
        int bytesRead = inFile.gcount();
        if (EVP_EncryptUpdate(ctx, outBuf, &outLen, inBuf, bytesRead) != 1) {
            std::cerr << "Encryption update failed\n";
            EVP_CIPHER_CTX_free(ctx);
            return;
        }
        outFile.write((char*)outBuf, outLen);
    }

    if (EVP_EncryptFinal_ex(ctx, outBuf, &outLen) != 1) {
        std::cerr << "Encryption finalization failed\n";
        EVP_CIPHER_CTX_free(ctx);
        return;
    }
    outFile.write((char*)outBuf, outLen);

    EVP_CIPHER_CTX_free(ctx);
}

void Crypto::decryptFile(const std::string& inputFile, const std::string& outputFile) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        std::cerr << "Failed to create EVP context\n";
        return;
    }

    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);

    unsigned char iv[Crypto::AES_BLOCK_SIZE];
    inFile.read((char*)iv, Crypto::AES_BLOCK_SIZE);

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)key.c_str(), iv) != 1) {
        std::cerr << "Failed to initialize decryption\n";
        EVP_CIPHER_CTX_free(ctx);
        return;
    }

    unsigned char inBuf[1024], outBuf[1024 + Crypto::AES_BLOCK_SIZE];
    int outLen;
    while (inFile.read((char*)inBuf, sizeof(inBuf)) || inFile.gcount()) {
        int bytesRead = inFile.gcount();
        if (EVP_DecryptUpdate(ctx, outBuf, &outLen, inBuf, bytesRead) != 1) {
            std::cerr << "Decryption update failed\n";
            EVP_CIPHER_CTX_free(ctx);
            return;
        }
        outFile.write((char*)outBuf, outLen);
    }

    if (EVP_DecryptFinal_ex(ctx, outBuf, &outLen) != 1) {
        std::cerr << "Decryption finalization failed\n";
        EVP_CIPHER_CTX_free(ctx);
        return;
    }
    outFile.write((char*)outBuf, outLen);

    EVP_CIPHER_CTX_free(ctx);
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
