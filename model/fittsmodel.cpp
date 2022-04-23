#include "fittsmodel.h"
#include "fittsview.h"

FittsModel::FittsModel() {
}

//Fonction pour transcrire les données dans le fichier json
QJsonObject FittsModel::writeDataJson() {
    QJsonObject dataItem;

    //déclaration et initiation des champs de l'objet Json
    dataItem["cibleLeft"] = cibleLeft;
    dataItem["nbCible"] = nbCible;
    dataItem["minSize"] = minSize;
    dataItem["maxSize"] = maxSize;
    dataItem["a"] = a;
    dataItem["b"] = b;
    dataItem["ecartType"] = ecartType;
    dataItem["erreurType"] = erreurType;
    dataItem["diffMoy"] = diffMoy;
    dataItem["itc95"] = itc95;

    QJsonArray clickPointsArray;

    for(int i = 0; i < clickPoints.size(); i++){

        clickPointsArray.append(QPointToQJsonobject(clickPoints[i]));

    }

    dataItem["clickPoints"] = clickPointsArray;



    QJsonArray cercleCenterArray;

    for(int i = 0; i < cercleCenter.size(); i++){

        cercleCenterArray.append(QPointToQJsonobject(cercleCenter[i]));

    }

    dataItem["cercleCenter"] = cercleCenterArray;



    QJsonArray cercleSizeArray;

    for(int i = 0; i < cercleSize.size(); i++){

        cercleSizeArray.append(cercleSize[i]);

    }

    dataItem["cercleSize"] = cercleSizeArray;

    QJsonArray timesArray;
    for(int i = 0; i < times.size(); i++){
        timesArray.append(times[i]);
    }
    dataItem["times"] = timesArray;

    QDateTime *currentDate = new QDateTime;

    dataItem["dateTime"] = currentDate->currentDateTime().toString("dd/MM/yyyy - hh:mm");

    return dataItem;
}

//transmet les données json à ce fittsModel
void FittsModel::writeDataModel(QJsonObject dataItem){
    this->a = dataItem["a"].toDouble();
    this->b = dataItem["b"].toDouble();
    this->minSize = dataItem["minSize"].toInt();
    this->maxSize = dataItem["maxSize"].toInt();
    this->cibleLeft = dataItem["cibleLeft"].toInt();
    this->nbCible = dataItem["nbCible"].toInt();
    QJsonArray cercleCenterLst = dataItem["cercleCenter"].toArray();
    QJsonArray cercleSizeLst = dataItem["cercleSize"].toArray();
    QJsonArray clickPointsLst = dataItem["clickPoints"].toArray();
    QJsonArray timesLst = dataItem["times"].toArray();
    //remplissage des listes de point de fittsModel
    for(int i=0; i < (this->nbCible - this->cibleLeft); i++){
        this->cercleCenter.append(QJsonObjectToQPoint(cercleCenterLst[i]));
        this->cercleSize.append(cercleSizeLst.at(i).toInt());
        this->clickPoints.append(QJsonObjectToQPoint(clickPointsLst[i]));
        this->times.append(timesLst[i].toDouble());
    }
}

QJsonObject FittsModel::QPointToQJsonobject(QPoint point) {

    QJsonObject converter;
    converter.insert("x", point.x());
    converter.insert("y", point.y());

    return converter;

}

QPoint FittsModel::QJsonObjectToQPoint(QJsonValueRef jsonPoint){
    QPoint point;
    QJsonObject jsonObject = jsonPoint.toObject();
    int x = jsonObject.value("x").toInt();
    int y = jsonObject.value("y").toInt();
    point.setX(x);
    point.setY(y);
    return point;
}
