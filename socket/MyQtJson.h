#ifndef MYQTJSON_H
#define MYQTJSON_H

#include <QDebug>
#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

namespace MyQtJson {
//接受Qt二进制流数据，输出对应的jsonObject,用完记得delete
QJsonObject& analysisByteArray(QByteArray data)
{
    //检验文件完整性
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(data, &json_error));
    if(json_error.error != QJsonParseError::NoError){

        qDebug() << "Json Error!";
        return *(new QJsonObject);
    }

    QJsonObject* rootObj = new QJsonObject;
    *rootObj = jsonDoc.object();
    return *rootObj;
}

//接受字段名，字段数据类型(1表示是Int数据)，字段数据,由于是new在堆里面的，用完记得delete
QJsonObject& DataToJson(QVector<QString> DataName, QVector<int> DataType, QVector<QString> Data)
{
    QJsonObject *jsonObject=new QJsonObject();
    int DataSize=DataName.size();
    if(!DataSize)
        qDebug("NoData!");
    for(int i=0;i<DataSize;i++){
        if(DataType[i]){
            jsonObject->insert(DataName[i],Data[i].toInt());
        }
        else{
            jsonObject->insert(DataName[i],Data[i]);
        }
    }
    return *jsonObject;
}
}
#endif // MYQTJSON_H
