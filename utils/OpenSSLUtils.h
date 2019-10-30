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
using namespace std;

class OpenSSLUtils
{
public:
    static string md5(string);
    static string sha256(string);
    static string base64_encode(string);
    static string base64_decode(string);
    static string aes_encrypt(string);
    static string aes_decrypt(string);
    static string rsa_encrypt(string, string);
    static string rsa_decrypt(string, string);
};