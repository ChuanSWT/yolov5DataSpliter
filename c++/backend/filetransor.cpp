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
    //progress=10;emit Progress(progress);
    //==打开路径------------------------
    QUrl src_url(src);
    QUrl tg_url(tg);
    QDir src_dir(src_url.toLocalFile());
    QDir tg_dir(tg_url.toLocalFile());
    //==开始逻辑判断----------------------
    //检测images文件夹和labels文件夹是否存在
    if(!src_dir.exists("images")){
        RaiseERROR("源文件 找不到images子目录");
        return;
    }
    if(!src_dir.exists("labels")){
        RaiseERROR("源文件 找不到labels子目录");
        return;
    }
    //==扫描文件-------------------------
    QDir images_dir(src_dir.filePath("images"));
    QDir labels_dir(src_dir.filePath("labels"));

    QFileInfoList list = images_dir.entryInfoList(
        QDir::Files | QDir::NoDotAndDotDot
        );

    for (const QFileInfo& info : list) {
        qDebug() << info.fileName()
        << info.absoluteFilePath();
    }
    emit RaiseERROR("你还没写完呢");
    emit Finished();
}
