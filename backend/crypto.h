#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>

class Crypto {
public:
    static void encryptFile(const std::string& inputFile, const std::string& outputFile);
    static void decryptFile(const std::string& inputFile, const std::string& outputFile);
private:
    static const std::string key;  // 32 bytes for AES-256
    static const std::string iv;   // 16 bytes for CBC
    static const int AES_BLOCK_SIZE = 16;  // Define block size explicitly
};

#endif
