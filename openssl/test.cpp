#include <iostream>
#include <string>
#include "../utils/OpenSSLUtils.h"
#include "../utils/StringUtils.h"
#include "../utils/FileUtils.h"

int main()
{
    std::string text = "my secret";

    std::cout << "text:" << text << std::endl;

    // hash
    std::cout << "md5:" << OpenSSLUtils::md5(text) << std::endl;
    std::cout << "sha256:" << OpenSSLUtils::sha256(text) << std::endl;

    // base64
    std::string base64_encode_text = OpenSSLUtils::base64_encode(text);
    std::cout << "base64encode:" << base64_encode_text << std::endl;
    std::cout << "base64decode:" << OpenSSLUtils::base64_decode(base64_encode_text) << std::endl;

    // aes
    std::string aes_enc = OpenSSLUtils::aes_encrypt(text);
    std::cout << "aes encrypt:" << aes_enc << std::endl;
    std::string aes_dec = OpenSSLUtils::aes_decrypt(aes_enc);
    std::cout << "aes decrypt:" << aes_dec << std::endl;

    // rsa
    std::string rsa_public_key = FileUtils::read_file("pubkey.pem");
    std::string rsa_private_key = FileUtils::read_file("prikey.pem");
    std::string rsa_enc = OpenSSLUtils::rsa_encrypt(text, rsa_public_key);
    std::string rsa_enc_base64 = OpenSSLUtils::base64_encode(rsa_enc);
    std::cout << "rsa encrypt(base64):" << rsa_enc_base64 << std::endl;
    std::string rsa_dec_base64 = OpenSSLUtils::base64_decode(rsa_enc_base64);
    std::string rsa_dec = OpenSSLUtils::rsa_decrypt(rsa_dec_base64, rsa_private_key);
    std::cout << "rsa decrypt:" << rsa_dec << std::endl;

    return 0;
}
/*
clang++ test.cpp \
../utils/OpenSSLUtils.cpp \
../utils/StringUtils.cpp \
../utils/FileUtils.cpp -lssl -lcrypto
 */