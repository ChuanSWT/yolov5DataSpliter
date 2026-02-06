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
    //==扫描目录，录入文件名-------------------------
    QDir images_dir(src_dir.filePath("images"));
    QDir labels_dir(src_dir.filePath("labels"));

    QFileInfoList image_list = images_dir.entryInfoList(
        QDir::Files | QDir::NoDotAndDotDot
        );
    QFileInfoList labels_list = labels_dir.entryInfoList(
        QDir::Files | QDir::NoDotAndDotDot
        );
    QSet<QString> images;
    QSet<QString> labels;
    for (const QFileInfo& info : image_list) {
        images.insert(info.fileName());
    }
    for (const QFileInfo& info : labels_list) {
        labels.insert(info.fileName());
    }
    //==检测每张图片是否有对应的.txt-----------------------------
    for(QString str:images){
        QString temp=str;
        while(temp.size()&&temp.back()!='.')
            temp.chop(1);//删除一个字符
        temp.append("txt");

        if(!labels.contains(temp)){
            qDebug()<<temp;
            emit RaiseERROR("images目录中 "+str+"没有对应的.txt文件");
            return;
        }
    }
    //至此，每个image都有对应的.txt label文件
    //==开始进行复制-------------------------------------------

    emit RaiseERROR("你还没写完呢");
}
