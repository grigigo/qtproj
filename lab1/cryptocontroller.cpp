#include "cryptocontroller.h"
#include <QDebug>
#include <openssl\evp.h>
#include <QBuffer>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

CryptoController::CryptoController(QObject *parent)
    : QObject{parent}
{

}

QList<Cridentials> * CryptoController::decrypt_file(const QString &filename, const QByteArray &key) {
    QFile encrypted_file;
    encrypted_file.setFileName(filename);
    encrypted_file.open(QIODevice::ReadOnly);
    if (!encrypted_file.isOpen()) {
        return nullptr;
    }
    QByteArray decoded_buf = QByteArray::fromBase64(encrypted_file.readAll());
    QBuffer buffer_stream(&decoded_buf);
    buffer_stream.open(QBuffer::ReadOnly);

    EVP_CIPHER_CTX *ctx;
    if (!(ctx = EVP_CIPHER_CTX_new())) {
        return nullptr;
    }

    // Инициализируем
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)key.data(), CryptoController::m_iv)){
        return 0;
    }

    int read_len = 0, decrypted_len = 0;
    QByteArray buffer;
    while (true) {
        char encrypted_buf[256] = {0};
        unsigned char decrypted_buf[512] = {0};
        read_len = buffer_stream.read(encrypted_buf, 256); // считать 256 байт

        // Расшифруем
        if (1 != EVP_DecryptUpdate(ctx,
                                   decrypted_buf, // выходной параметр, буфер куда записывается зашифрованный текст
                                   &decrypted_len, // выходной параметр, кол-во зашифрованных символов
                                   (unsigned char *)encrypted_buf, // входной параметр, шифруемый буфер
                                   read_len)) {    // входной параметр, кол-во исходных символов
            return 0;
        }

        if (read_len < 256) {
            int tmplen;
            if (!EVP_DecryptFinal_ex(ctx, decrypted_buf + decrypted_len, &tmplen)) {
                /* Error */
                EVP_CIPHER_CTX_free(ctx);
                return 0;
            }
            decrypted_len += tmplen;
            buffer += QByteArray((char *)decrypted_buf, decrypted_len);
            break;
        } else {
            buffer += QByteArray((char *)decrypted_buf, decrypted_len);
        }

    }
    // Конец работы с openssl
    EVP_CIPHER_CTX_free(ctx);

    encrypted_file.close();
    buffer_stream.close();

    QJsonDocument json_doc = QJsonDocument::fromJson(buffer);
    QJsonArray cridentials_array = json_doc.object().value("list").toArray();
    QList<Cridentials> * result = new QList<Cridentials>();
    for (auto item : cridentials_array) {
        Cridentials new_record;
        new_record.site = item.toObject().value("url").toString().toUtf8();
        new_record.encrypted = item.toObject().value("logpass").toString().toUtf8();
        result->append(new_record);
    }

    return result;
}

QString CryptoController::decrypt_record(const QByteArray &record, QString index, const QByteArray &key) {
    QString result;

    EVP_CIPHER_CTX *ctx;
    if (!(ctx = EVP_CIPHER_CTX_new())) {
        return nullptr;
    }

    // Инициализируем
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)key.data(), CryptoController::m_iv)){
        return 0;
    }

    QByteArray ciphertext = QByteArray::fromBase64(record);
    QBuffer buffer(&ciphertext);
    buffer.open(QBuffer::ReadOnly);

    char encrypted_buf[256] = {0};
    unsigned char decrypted_buf[256] = {0};
    int decrypted_len = 0;
    int read_len = buffer.read(encrypted_buf, 256);

    // Расшифруем
    if (1 != EVP_DecryptUpdate(ctx,
                               decrypted_buf, // выходной параметр, буфер куда записывается зашифрованный текст
                               &decrypted_len, // выходной параметр, кол-во зашифрованных символов
                               (unsigned char *) encrypted_buf, // входной параметр, шифруемый буфер
                               read_len)) {    // входной параметр, кол-во исходных символов
        return 0;
    }

    int tmplen;
    if (!EVP_DecryptFinal_ex(ctx, decrypted_buf + decrypted_len, &tmplen)) {
        /* Error */
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }
    decrypted_len += tmplen;
    buffer.close();

    QJsonDocument json_doc = QJsonDocument::fromJson(QByteArray((char *)decrypted_buf, decrypted_len));
    result = json_doc.object().value(index).toString();
    qDebug() << result;

    EVP_CIPHER_CTX_free(ctx);

    return result;
}

QString CryptoController::encrypt_login_password(QString logpass, const QByteArray &key) {
    QString result;

    //QJsonObject::

    EVP_CIPHER_CTX *ctx;
    if (!(ctx = EVP_CIPHER_CTX_new())) {
        return 0;
    }

    // Инициализируем
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)key.data(), CryptoController::m_iv)){
        return 0;
    }

//    QByteArray ciphertext = QByteArray::fromBase64(record);
//    QBuffer buffer(&ciphertext);
//    buffer.open(QBuffer::ReadOnly);

//    char encrypted_buf[256] = {0};
//    unsigned char decrypted_buf[256] = {0};
//    int decrypted_len = 0;
//    int read_len = buffer.read(encrypted_buf, 256);

//    // Расшифруем
//    if (1 != EVP_EncryptUpdate(ctx,
//                               decrypted_buf, // выходной параметр, буфер
//                               &decrypted_len, // выходной параметр, кол-во символов
//                               (unsigned char *) encrypted_buf, // входной параметр, буфер
//                               read_len)) {    // входной параметр, кол-во  символов
//        return 0;
//    }

//    int tmplen;
//    if (!EVP_EncryptFinal_ex(ctx, decrypted_buf + decrypted_len, &tmplen)) {
//        /* Error */
//        EVP_CIPHER_CTX_free(ctx);
//        return 0;
//    }
//    decrypted_len += tmplen;
//    buffer.close();

//    QJsonDocument json_doc = QJsonDocument::fromJson(QByteArray((char *)decrypted_buf, decrypted_len));
//    result = json_doc.object().value(index).toString();
//    qDebug() << result;

    EVP_CIPHER_CTX_free(ctx);

    return 0;
}
