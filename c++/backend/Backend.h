#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QtQml>
#include <QDir>
#include <qdebug.h>
class Backend : public QObject
{
    Q_OBJECT
    QML_ELEMENT //自动暴露

    //====暴露信息-----------------------------------------------
    Q_PROPERTY(QString source_path READ GetSourcePath NOTIFY SourcePathChanged)
    Q_PROPERTY(QString target_path READ GetTargetPath NOTIFY TargetPathChanged)
    Q_PROPERTY(QString train_part READ GetTrainPart NOTIFY TrainPartChanged)
    Q_PROPERTY(QString verify_part READ GetVerifyPart NOTIFY VerifyPartChanged)
    Q_PROPERTY(QString test_part READ GetTestPart NOTIFY TestPartChanged)
public:
    explicit Backend(QObject *parent = nullptr);
    //Get 方法，前端隐调用
    QString GetSourcePath(){return source_path;}
    QString GetTargetPath(){return target_path;}
    QString GetTrainPart(){return part_mp["train"];}
    QString GetVerifyPart(){return part_mp["verify"];}
    QString GetTestPart(){return part_mp["test"];}
public:
    //更新路径选择
    Q_INVOKABLE void UpdateSourcePath(QString path);
    Q_INVOKABLE void UpdateTargetPath(QString path);
    //更新划分细节
    Q_INVOKABLE void UpdatePart(QString part,QString str);
    Q_INVOKABLE void START();
signals:
    void SourcePathChanged();
    void TargetPathChanged();

    void TrainPartChanged();
    void VerifyPartChanged();
    void TestPartChanged();
private:
    QString source_path;
    QString target_path;
    //划分细节中 关键词到数值的映射
    QMap<QString,QString> part_mp;//[train,verify,test]
};

#endif // BACKEND_H
