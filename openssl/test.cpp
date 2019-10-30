#include <iostream>
#include <string>
#include "../utils/OpenSSLUtils.h"
#include "../utils/StringUtils.h"
#include "../utils/FileUtils.h"

int main()
{
    std::string text = "my secret";

    cout << "text:" << text << endl;

    // hash
    cout << "md5:" << OpenSSLUtils::md5(text) << endl;
    cout << "sha256:" << OpenSSLUtils::sha256(text) << endl;

    // base64
    std::string base64_encode_text = OpenSSLUtils::base64_encode(text);
    cout << "base64encode:" << base64_encode_text << endl;
    cout << "base64decode:" << OpenSSLUtils::base64_decode(base64_encode_text) << endl;

    // aes
    std::string aes_enc = OpenSSLUtils::aes_encrypt(text);
    cout << "aes encrypt:" << aes_enc << endl;
    std::string aes_dec = OpenSSLUtils::aes_decrypt(aes_enc);
    cout << "aes decrypt:" << aes_dec << endl;

    // rsa
    std::string rsa_public_key = FileUtils::read_file("pubkey.pem");
    std::string rsa_private_key = FileUtils::read_file("prikey.pem");
    std::string rsa_enc = OpenSSLUtils::rsa_encrypt(text, rsa_public_key);
    std::string rsa_enc_base64 = OpenSSLUtils::base64_encode(rsa_enc);
    cout << "rsa encrypt(base64):" << rsa_enc_base64 << endl;
    std::string rsa_dec_base64 = OpenSSLUtils::base64_decode(rsa_enc_base64);
    std::string rsa_dec = OpenSSLUtils::rsa_decrypt(rsa_dec_base64, rsa_private_key);
    cout << "rsa decrypt:" << rsa_dec << endl;

    return 0;
}
/*
clang++ test.cpp \
../utils/OpenSSLUtils.cpp \
../utils/StringUtils.cpp \
../utils/FileUtils.cpp -lssl -lcrypto
 */