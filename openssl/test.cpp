#include <iostream>
#include <string>
#include "OpenSSLUtils.h"
using namespace std;

int main()
{
    string text = "my secret";

    cout << "text:" << text << endl;

    cout << "md5:" << OpenSSLUtils::md5(text) << endl;

    cout << "sha256:" << OpenSSLUtils::sha256(text) << endl;

    string base64_encode_text = OpenSSLUtils::base64_encode(text);

    cout << "base64encode:" << base64_encode_text << endl;

    cout << "base64decode:" << OpenSSLUtils::base64_decode(base64_encode_text) << endl;

    string enc = OpenSSLUtils::aes_encrypt(text);
    cout << "aes encrypt:" << enc << endl;
    string dec = OpenSSLUtils::aes_decrypt(enc);
    cout << "aes decrypt:" << dec << endl;

    return 0;
} // clang++ test.cpp OpenSSLUtils.cpp -lssl -lcrypto