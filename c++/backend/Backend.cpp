#include "Backend.h"

Backend::Backend(QObject *parent)
    : QObject{parent}
{
    source_path="none";
    target_path="none";
    part_mp["train"]="70";
    part_mp["verify"]="30";
    part_mp["test"]="0";

    progress=0;
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
    //--DEBUG--------------------------
    qDebug()<<"==得到用户输入==";
    qDebug()<<"源路径"<<source_path;
    qDebug()<<"目标路径"<<target_path;

    qDebug()<<"训练集合:"<<part_mp["train"]
             <<"验证集合:"<<part_mp["verify"]
             <<"测试集合"<<part_mp["test"];
    qDebug()<<"----------";
    //==验证 路径可达性-------------------
    if(source_path=="none"){
        info="未选择 源路径";
        emit InfoChanged();
        return;
    }
    if(target_path=="none"){
        info="未选择 目标路径";
        emit InfoChanged();
        return;
    }

    //创建线程
    QThread* th = new QThread(this);
    //创建一个类的对象
    FileTransor* worker = new FileTransor(nullptr,source_path,target_path,
part_mp["train"],part_mp["verify"],part_mp["test"]);

    //改变对象的线程归属
    worker->moveToThread(th);

    //...连接信号...//
    connect(th,&QThread::started,worker,[=](){
        worker->Work();
    });
    connect(worker,&FileTransor::Progress,this,[=](int n){
        progress=n;
        ProgressChanged();
    });
    connect(worker,&FileTransor::RaiseERROR,this,[=](QString err){
        info=err;
        emit InfoChanged();
    });
    connect(worker,&FileTransor::Finished,this,[=](){
        progress=100;
        info="完成";
        emit InfoChanged();
        emit ProgressChanged();
    });
    //...链接自动销毁信号...//
    connect(worker, &FileTransor::Finished, th, &QThread::quit);
    connect(worker, &FileTransor::Finished, worker, &QObject::deleteLater);
    connect(worker, &FileTransor::RaiseERROR, th, &QThread::quit);
    connect(worker, &FileTransor::RaiseERROR, worker, &QObject::deleteLater);
    connect(th, &QThread::finished, th, &QObject::deleteLater);
    //启动线程，执行完后会自动销毁
    th->start();//！这是非阻塞调用
}
