#include "OpenSSLUtils.h"

std::string OpenSSLUtils::md5(std::string text)
{
    // md5 hash
    unsigned char mdStr[33] = {0};
    MD5((const unsigned char *)text.c_str(), text.length(), mdStr);

    // after hash, hex 32 digit
    char buf[65] = {0};
    char tmp[3] = {0};
    for (int i = 0; i < 32; i++)
    {
        sprintf(tmp, "%02x", mdStr[i]);
        strcat(buf, tmp);
    }
    buf[32] = '\0'; // after 32 are 0
    return std::string(buf);
}

std::string OpenSSLUtils::sha256(std::string text)
{
    // sha256 hash
    unsigned char mdStr[33] = {0};
    SHA256((const unsigned char *)text.c_str(), text.length(), mdStr);

    // after hash, hex 64 digit
    char buf[65] = {0};
    char tmp[3] = {0};
    for (int i = 0; i < 32; i++)
    {
        sprintf(tmp, "%02x", mdStr[i]);
        strcat(buf, tmp);
    }

    return std::string(buf);
}

static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static inline bool is_base64(unsigned char c)
{
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string OpenSSLUtils::base64_encode(std::string text)
{
    std::string ret;
    unsigned char const *bytes_to_encode = reinterpret_cast<const unsigned char *>(text.c_str());
    int in_len = text.size();
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (in_len--)
    {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3)
        {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4); i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];

        while ((i++ < 3))
            ret += '=';
    }

    return ret;
}

std::string OpenSSLUtils::base64_decode(std::string text)
{
    int in_len = text.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;

    while (in_len-- && (text[in_] != '=') && is_base64(text[in_]))
    {
        char_array_4[i++] = text[in_];
        in_++;
        if (i == 4)
        {
            for (i = 0; i < 4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 4; j++)
            char_array_4[j] = 0;

        for (j = 0; j < 4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++)
            ret += char_array_3[j];
    }

    return ret;
}

void handleErrors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

int internal_aes_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
                         unsigned char *iv, unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    /* Create and initialise the context */
    if (!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /*
     * Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    /*
     * Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}
int internal_aes_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
                         unsigned char *iv, unsigned char *plaintext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int plaintext_len;

    /* Create and initialise the context */
    if (!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /*
     * Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    /*
     * Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary.
     */
    if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();
    plaintext_len = len;

    /*
     * Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        handleErrors();
    plaintext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}

/* A 256 bit key */
unsigned char *key = (unsigned char *)"01234567890123456789012345678901";

/* A 128 bit IV */
unsigned char *iv = (unsigned char *)"0123456789012345";

std::string OpenSSLUtils::aes_encrypt(std::string text)
{

    /* Message to be encrypted */
    unsigned char *plaintext = (unsigned char *)text.c_str();
    // (unsigned char *)"The quick brown fox jumps over the lazy dog";

    unsigned char ciphertext[128];

    int ciphertext_len;

    /* Encrypt the plaintext */
    ciphertext_len = internal_aes_encrypt(plaintext, strlen((char *)plaintext), key, iv,
                                          ciphertext);
    ciphertext[ciphertext_len] = '\0';

    // convert to base64 encode
    return base64_encode(reinterpret_cast<char *>(ciphertext));
}

std::string OpenSSLUtils::aes_decrypt(std::string base64_encode_text)
{
    std::string text = base64_decode(base64_encode_text);
    unsigned char *ciphertext = (unsigned char *)text.c_str();

    unsigned char decryptedtext[128];

    int decryptedtext_len;

    decryptedtext_len = internal_aes_decrypt(ciphertext, text.length(), key, iv,
                                             decryptedtext);

    /* Add a NULL terminator. We are expecting printable text */
    decryptedtext[decryptedtext_len] = '\0';

    return reinterpret_cast<char *>(decryptedtext);
}

std::string OpenSSLUtils::rsa_encrypt(std::string text, std::string public_key)
{
    std::string strRet;
    RSA *rsa = NULL;
    BIO *keybio = BIO_new_mem_buf((unsigned char *)public_key.c_str(), -1);
    // 此处有三种方法
    // 1, 读取内存里生成的密钥对，再从内存生成rsa
    // 2, 读取磁盘里生成的密钥对文本文件，在从内存生成rsa
    // 3，直接从读取文件指针生成rsa
    RSA *pRSAPublicKey = RSA_new();
    rsa = PEM_read_bio_RSAPublicKey(keybio, &rsa, NULL, NULL);

    int len = RSA_size(rsa);
    char *encryptedText = (char *)malloc(len + 1);
    memset(encryptedText, 0, len + 1);

    // 加密函数
    int ret = RSA_public_encrypt(text.length(), (const unsigned char *)text.c_str(), (unsigned char *)encryptedText, rsa, RSA_PKCS1_PADDING);
    if (ret >= 0)
        strRet = std::string(encryptedText, ret);

    // 释放内存
    free(encryptedText);
    BIO_free_all(keybio);
    RSA_free(rsa);

    return strRet;
}

std::string OpenSSLUtils::rsa_decrypt(std::string text, std::string private_key)
{
    std::string strRet;
    RSA *rsa = RSA_new();
    BIO *keybio;
    keybio = BIO_new_mem_buf((unsigned char *)private_key.c_str(), -1);

    // 此处有三种方法
    // 1, 读取内存里生成的密钥对，再从内存生成rsa
    // 2, 读取磁盘里生成的密钥对文本文件，在从内存生成rsa
    // 3，直接从读取文件指针生成rsa
    rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);

    int len = RSA_size(rsa);
    char *decryptedText = (char *)malloc(len + 1);
    memset(decryptedText, 0, len + 1);

    // 解密函数
    int ret = RSA_private_decrypt(text.length(), (const unsigned char *)text.c_str(), (unsigned char *)decryptedText, rsa, RSA_PKCS1_PADDING);
    if (ret >= 0)
        strRet = std::string(decryptedText, ret);

    // 释放内存
    free(decryptedText);
    BIO_free_all(keybio);
    RSA_free(rsa);

    return strRet;
}