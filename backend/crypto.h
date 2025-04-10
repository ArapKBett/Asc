#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>

class Crypto {
public:
    static void encryptFile(const std::string& inputFile, const std::string& outputFile);
    static void decryptFile(const std::string& inputFile, const std::string& outputFile);
private:
    static const std::string key;  // AES-256 key (32 bytes)
    static const std::string iv;   // Initialization vector (16 bytes)
};

#endif
