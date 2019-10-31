#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include "openssl/md5.h"
#include "openssl/sha.h"
#include "openssl/des.h"
#include "openssl/rsa.h"
#include "openssl/pem.h"
#include "openssl/conf.h"
#include "openssl/evp.h"
#include "openssl/err.h"

class OpenSSLUtils
{
public:
    static std::string md5(std::string);
    static std::string sha256(std::string);
    static std::string base64_encode(std::string);
    static std::string base64_decode(std::string);
    static std::string aes_encrypt(std::string);
    static std::string aes_decrypt(std::string);
    static std::string rsa_encrypt(std::string, std::string);
    static std::string rsa_decrypt(std::string, std::string);
};