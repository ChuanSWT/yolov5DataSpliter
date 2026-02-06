#include "Backend.h"

Backend::Backend(QObject *parent)
    : QObject{parent}
{
    source_path="none";
    target_path="none";
    part_mp["train"]="70";
    part_mp["verify"]="30";
    part_mp["test"]="0";
}
Q_INVOKABLE void Backend::UpdateSourcePath(QString path) {
    source_path=path;
    emit SourcePathChanged();
}
Q_INVOKABLE void Backend::UpdateTargetPath(QString path){
    target_path=path;
    emit TargetPathChanged();
}

Q_INVOKABLE void Backend::UpdatePart(QString part,QString str){
    part_mp[part]=str;
    if(part=="train")
        TrainPartChanged();
}
Q_INVOKABLE void Backend::START(){
    qDebug()<<"==得到用户输入==";
    qDebug()<<"源路径"<<source_path;
    qDebug()<<"目标路径"<<target_path;

    qDebug()<<"训练集合:"<<part_mp["train"]
             <<"验证集合:"<<part_mp["verify"]
             <<"测试集合"<<part_mp["test"];
    qDebug()<<"----------";
    if(source_path=="none"){
        qDebug()<<"未选择 源路径";return;
    }
    if(target_path=="none"){
        qDebug()<<"未选择 目标路径";return;
    }
    QUrl src_url(source_path);QString src_path = src_url.toLocalFile();
    QUrl tg_url(target_path);QString tg_path = tg_url.toLocalFile();

    QDir src_dir(src_path);
    QDir tg_dir(tg_path);


}
