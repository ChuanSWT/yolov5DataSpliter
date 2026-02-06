#include "filetransor.h"

FileTransor::FileTransor(QObject *parent)
    : QObject{parent},progress(0)
{}
FileTransor::FileTransor(QObject *parent,QString src,QString tg,
QString train_str,QString verify_str,QString test_str)
    : QObject{parent},src(src),tg(tg),progress(0),
    train_str(train_str),verify_str(verify_str),test_str(test_str)
{}
void FileTransor::Work(){
    //==打开路径------------------------
    QUrl src_url(src);QString src_path = src_url.toLocalFile();
    QUrl tg_url(tg);QString tg_path = tg_url.toLocalFile();
    QDir src_dir(src_path);
    QDir tg_dir(tg_path);

    QFileInfoList list = src_dir.entryInfoList(
        QDir::Files | QDir::NoDotAndDotDot
        );
    //progress=100;
    //emit Progress(100);
    emit RaiseERROR("你还没写完呢");
    emit Finished();
}
