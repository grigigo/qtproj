#ifndef CRYPTOCONTROLLER_H
#define CRYPTOCONTROLLER_H

#include <QObject>
#include <QFile>

struct Cridentials {
public:
    QByteArray site;
    QByteArray encrypted;
};

class CryptoController : public QObject {
    Q_OBJECT
public:
    explicit CryptoController(QObject *parent = nullptr);

    static QList<Cridentials> * decrypt_file(const QString &filename, const QByteArray &key);
    static QString decrypt_record(const QByteArray &record, QString index, const QByteArray &key);
    static QString encrypt_login_password(QString logpass, const QByteArray &key);

    constexpr static unsigned char m_iv[17] = "65e84be33532fb78";
};

/*
 *  65e84be33532fb78
 *  4c48129675f9eff3
 *  a682b27168c0ea74
 *  4b2cf58ee02337c5
*/

#endif // CRYPTOCONTROLLER_H
