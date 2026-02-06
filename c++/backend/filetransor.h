#ifndef FILETRANSOR_H
#define FILETRANSOR_H

#include <QObject>
#include <QUrl>
#include <QDir>
class FileTransor : public QObject
{
    Q_OBJECT
public:
    explicit FileTransor(QObject *parent = nullptr);
    explicit FileTransor(QObject *parent = nullptr,QString src="none",QString tg="none",
QString train_str="-1",QString verify_str="-1",QString test_str="-1");
public:
    void Work();
signals:
    void Progress(int n);
    void Finished();
    void RaiseERROR(QString err);
private:
    QString src;
    QString tg;
    QString train_str;QString verify_str;QString test_str;
    int progress;//执行的进度
};

#endif // FILETRANSOR_H
