#include "filetransor.h"
#include <algorithm>
#include <random>

FileTransor::FileTransor(QObject *parent)
    : QObject{parent},progress(0)
{}
FileTransor::FileTransor(QObject *parent,QString src,QString tg,
QString train_str,QString verify_str,QString test_str)
    : QObject{parent},src(src),tg(tg),progress(0),
    train_str(train_str),verify_str(verify_str),test_str(test_str)
{}
void FileTransor::Work(){
    //==接收划分数字----------------------------------
    QVector<bool> s2n_ok(3,true);
    int train_p,verify_p,test_p;
    train_p=train_str.toInt(&s2n_ok[0]);
    verify_p=verify_str.toInt(&s2n_ok[1]);
    test_p=test_str.toInt(&s2n_ok[2]);
    if(!s2n_ok[0]||!s2n_ok[1]||!s2n_ok[2]){
        emit RaiseERROR("划分细节 填写有非数字");
        return;
    }
    if(train_p+verify_p+test_p!=100){
        emit RaiseERROR("划分细节 填写数字和不为100");
        return;
    }
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
    QVector<QPair<QString,QString>> names;//顺便存储一下
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
        names.push_back({str,temp});
    }
    //至此，每个image都有对应的.txt label文件
    //进行打乱
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(names.begin(), names.end(), gen);
    //==防止目标目录数据重叠------------------------------------
    if(tg_dir.exists("splited_dataset")){
        RaiseERROR("目标目录 已经存在");
        return;
    }
    //###开始进行文件操作###//
    //==建立目标目录-------------------------------------------
    tg_dir.mkpath("splited_dataset/images");
    tg_dir.mkpath("splited_dataset/images/train");
    tg_dir.mkpath("splited_dataset/images/val");
    tg_dir.mkpath("splited_dataset/images/test");
    tg_dir.mkpath("splited_dataset/labels");
    tg_dir.mkpath("splited_dataset/labels/train");
    tg_dir.mkpath("splited_dataset/labels/val");
    tg_dir.mkpath("splited_dataset/labels/test");

    QDir splited_dataset=tg_dir.filePath("splited_dataset");
    QDir tg_images_dir(splited_dataset.filePath("images"));
    QDir tg_images_train_dir(tg_images_dir.filePath("train"));
    QDir tg_images_verify_dir(tg_images_dir.filePath("val"));
    QDir tg_images_test_dir(tg_images_dir.filePath("test"));

    QDir tg_labels_dir(splited_dataset.filePath("labels"));
    QDir tg_labels_train_dir(tg_labels_dir.filePath("train"));
    QDir tg_labels_verify_dir(tg_labels_dir.filePath("val"));
    QDir tg_labels_test_dir(tg_labels_dir.filePath("test"));
    //==开始进行复制-------------------------------------------
    int m=names.size();
    int cur=0;

    for(int i=0;i<names.size();++i){
        auto [img_name,lbl_name]=names[i];
        //源图片路径
        QString src_image_path=images_dir.filePath(img_name);
        //源标签路径
        QString src_label_path=labels_dir.filePath(lbl_name);

        //目标图片路径
        QString tg_image_path;
        //目标标签路径
        QString tg_label_path;

        if((double)i/m<(double)train_p/100){//train
            //装载目标
            tg_image_path=tg_images_train_dir.filePath(img_name);
            tg_label_path=tg_labels_train_dir.filePath(lbl_name);

            QFile::copy(src_image_path,tg_image_path);
            QFile::copy(src_label_path,tg_label_path);
            continue;
        }
        if((double)i/m<(double)(train_p+verify_p)/100){//val
            tg_image_path=tg_images_verify_dir.filePath(img_name);
            tg_label_path=tg_labels_verify_dir.filePath(lbl_name);

            QFile::copy(src_image_path,tg_image_path);
            QFile::copy(src_label_path,tg_label_path);
            continue;
        }
        tg_image_path=tg_images_test_dir.filePath(img_name);
        tg_label_path=tg_labels_test_dir.filePath(lbl_name);

        QFile::copy(src_image_path,tg_image_path);
        QFile::copy(src_label_path,tg_label_path);

        continue;
    }
    //emit RaiseERROR("你还没写完");
    emit Finished();
}
