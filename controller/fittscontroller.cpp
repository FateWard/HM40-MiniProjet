#include <iostream>
//#include <cstdlib>
#include "fittscontroller.h"
#include "fittsview.h"
#include "fittsmodel.h"

QT_CHARTS_USE_NAMESPACE

using namespace std;

FittsController::FittsController() {
    this->fittsModel = new FittsModel();
    this->fittsView = new FittsView(this, this->fittsModel);
    this->histModel = new QList<FittsModel>();
    this->start();
    this->color = false;
}

//initialise la page fittsView
void FittsController::start() {

    this->fittsView->show();
    startSimulation();
    this->fittsView->mainStack->setCurrentIndex(0);
}

//initialise une partie du test Fitts
void FittsController::startSimulation() {
    this->fittsView->mainStack->setCurrentIndex(1);
    this->fittsModel->cibleLeft = this->fittsModel->nbCible;
    this->fittsView->updateTestMsg();
    this->fittsView->graphicView->setEnabled(true);
    this->fittsModel->cercleSize.clear();
    this->fittsModel->cercleCenter.clear();
    this->fittsModel->clickPoints.clear();
    this->fittsModel->times.clear();

    this->initGame();
}

//ferme l'application
void FittsController::quit() {
    QApplication::quit();
}

//s'occupe du mode jour/nuit via un booleen
void FittsController::changeMode(){
    if(color){
            color = false;
            this->fittsView->change_color(color);
        }else{
            color = true;
            this->fittsView->change_color(color);
        }
}

//changer le mode du graphique
void FittsController::changeGraphHome(){
    if(this->fittsView->switchGraphHome->minimumHeight() == 150){
        this->fittsView->switchGraphHome->setIcon(QIcon(":/icons/switchGraphe_2"));
        this->fittsView->switchGraphHome->setMinimumHeight(149);
        this->fittsView->plotHomeDistance->setVisible(true);
        this->fittsView->plotHome->setVisible(false);
        this->fittsView->graphTitleHome->setText("Temps = f(log(D/L+1))");
        this->fittsView->isPlotHome = false;
    }else{
        this->fittsView->switchGraphHome->setIcon(QIcon(":/icons/switchGraphe_1"));
        this->fittsView->switchGraphHome->setMinimumHeight(150);
        this->fittsView->plotHomeDistance->setVisible(false);
        this->fittsView->plotHome->setVisible(true);
        this->fittsView->graphTitleHome->setText("Temps = f( cible )");
        this->fittsView->isPlotHome = true;
    }
}

/**
 * M??thode qui change la fen??tre pour afficher le graphique en grand
 */
void FittsController::chartZoom()
{
    this->fittsView->mainStack->setCurrentIndex(2);
    if(this->fittsView->hasSimulated)
    {
        this->calculateResultHome();
        if(this->fittsView->isPlotHome)
        {
            this->fittsView->chartZoomed->setChart(this->chartHome);
        }
        else
        {
            this->fittsView->chartZoomed->setChart(this->chartDistanceHome);
        }
    }

}

//fait le retour sur la page des param??tres apr??s un test fini
void FittsController::backToSettings() {
    this->fittsView->mainStack->setCurrentIndex(0);
    this->calculateResultHome();
    this->addHisto();
    reloadFittsView();
    loadGraph(this->fittsView->lstEyeButtons.size()-1);
    this->fittsView->displayResults();
}

//fait le retour sur la page des param??tres si le test est abandonn??
void FittsController::cancel() {
    this->fittsView->mainStack->setCurrentIndex(0);
}

/**
 * M??thode appel??e lorsque l'utilisateur sort de la fen??tre zoomant sur le graphique
 */
void FittsController::zoomCancel()
{
    this->fittsView->mainStack->setCurrentIndex(0);
    if(this->fittsView->hasSimulated)
    {
        this->calculateResultHome();
        if(this->fittsView->isPlotHome)
        {
            this->fittsView->plotHome->setChart(this->chartHome);
        }
        else
        {
            this->fittsView->plotHomeDistance->setChart(this->chartDistanceHome);
        }
    }

}

//ensembles de fonctions pour g??rer le changement des param??tres et coeffs
void FittsController::aValueChanged(double value) {
    this->fittsModel->a = value;
    calculateResultHome();
    this->fittsView->displayResults();
}
void FittsController::bValueChanged(double value) {
    this->fittsModel->b = value;
    calculateResultHome();
}
void FittsController::nbCibleChanged(int value) {
    this->fittsModel->nbCible = value;
}
void FittsController::minSizeChanged(int value) {
    this->fittsModel->minSize = value;
}
void FittsController::maxSizeChanged(int value) {
    this->fittsModel->maxSize = value;
}

//g??re les donn??es apr??s le clic sur une cible pendant le test
void FittsController::cibleClicked(int x, int y) {
    if(this->fittsModel->cercleCenter.isEmpty()) {
        // Si vide alors premier click, on demarre le timer
        this->timer = new QElapsedTimer;
        timer->start();

        // On d??marre avec la premi??re cible
        this->fittsModel->clickPoints.append(QPoint(x,y));
        this->nextCible();
    }
    else {
        QPointF coords = this->fittsView->graphicView->mapToScene(x,y);
        if(sqrt(pow(coords.x() - this->fittsModel->cercleCenter.last().x(),2) + pow(coords.y() - this->fittsModel->cercleCenter.last().y(),2)) <= this->fittsModel->cercleSize.last() / 2) {
            // On stock le temps de click
            this->fittsModel->times.append(timer->elapsed());
            // On restart le chrono
            timer->restart();

            // On stock la position du click
            this->fittsModel->clickPoints.append(QPoint(x,y));
            this->nextCible();
        }
    }
}

//s'occupe d'afficher une cible sur la page de test et stocker les donn??es de la cible
void FittsController::nextCible() {
    if(!this->fittsModel->cercleCenter.isEmpty())
        this->fittsModel->cibleLeft--;
    this->fittsView->updateTestMsg();

    QGraphicsScene *scene = this->fittsView->scene;
    scene->clear();

    // On stop si c'est finis
    if(this->fittsModel->cibleLeft == 0) {
        this->fittsView->hasSimulated = true;
        this->finish();
        return;
    }

    // On g??n??re la taille du cercle rouge
    // qrand() % ((high + 1) - low) + low;
    int size = QRandomGenerator::global()->generate() % ((this->fittsModel->maxSize + 1) - this->fittsModel->minSize) + this->fittsModel->minSize;
    // Car on veut le rayon
    // On place le cercle dans la scene (Attention faut pas qu'il soit en dehors du cadre)
    int sceneW = int(this->fittsView->scene->width());
    int sceneH = int(this->fittsView->scene->height());

    qreal posX = QRandomGenerator::global()->generate() % std::max(((sceneW - size) - size) + size, 1);
    qreal posY = QRandomGenerator::global()->generate() % std::max(((sceneH - size) - size) + size, 1);

    // On stock les infos sur le cercle
    this->fittsModel->cercleCenter.append(QPoint(int(posX),int(posY)));
    this->fittsModel->cercleSize.append(size);

    // On place le cercle
    scene->addEllipse(posX - (size / 2), posY - (size / 2), size, size, QPen(QColor(color_red)),QBrush(QColor(color_red)))->setCursor(Qt::PointingHandCursor);
}

//met fin au test apr??s lorsque le nombre de cible d??fini est atteint
void FittsController::finish() {
    this->fittsView->graphicView->setEnabled(false);
    backToSettings();
}

//initialise la page de test
void FittsController::initGame() {
    QGraphicsScene *scene = this->fittsView->scene;
    scene->clear();

    if(this->fittsModel->maxSize >= this->fittsView->graphicView->width() / 2)
        this->fittsModel->maxSize = this->fittsView->graphicView->width() / 2;

    if(this->fittsModel->maxSize >= this->fittsView->graphicView->height() / 2)
        this->fittsModel->maxSize = this->fittsView->graphicView->height() / 2;

    qreal posX = scene->width() / 2;
    qreal posY = scene->height() / 2;
    int size = 180;

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(30);
    effect->setXOffset(0);
    effect->setYOffset(0);
    effect->setColor(color_blue);
    scene->addEllipse(posX - (size / 2), posY - (size / 2), size, size, QPen(QColor(color_blue)),QBrush(QColor(color_blue)))->setGraphicsEffect(effect);
    scene->addEllipse(posX - (size / 2), posY - (size / 2), size, size, QPen(QColor(color_blue)),QBrush(QColor(color_blue)))->setCursor(Qt::PointingHandCursor);
    QLabel *labelStart;
    labelStart = new QLabel("Start");
    labelStart->setAlignment(Qt::AlignCenter);
    labelStart->setStyleSheet("color: #ffffff; font: bold 35px 'ROBOTO'; background-color: transparent;");
    labelStart->setCursor(Qt::PointingHandCursor);
    labelStart->move((size / 2) + 189, (size / 2) + 43);
    scene->addWidget(labelStart);
}

//calcule les valeurs(moy, ecart-type, intervalle de conf...) et courbes du mod??le courant
//trace les courbes sur le graphique
void FittsController::calculateResultHome() {

    chartHome = new QChart;
    this->fittsView->plotHome->setChart(chartHome);
    this->fittsView->plotHome->setRenderHint(QPainter::Antialiasing);
    chartHome->setAnimationOptions(QChart::AllAnimations);
    chartHome->createDefaultAxes();
    chartHome->legend()->setVisible(false);
    chartHome->legend()->setLabelBrush(QBrush(QColor(color_blue)));
    chartHome->setBackgroundVisible(false);

    QLineSeries *expSeries = new QLineSeries;
    QLineSeries *fittsSeries = new QLineSeries;
    QCategoryAxis *axis = new QCategoryAxis;

    //New plotHomeDistance
    chartDistanceHome = new QChart;
    this->fittsView->plotHomeDistance->setChart(chartDistanceHome);
    this->fittsView->plotHomeDistance->setRenderHint(QPainter::Antialiasing);
    chartDistanceHome->setAnimationOptions(QChart::AllAnimations);
    chartDistanceHome->createDefaultAxes();
    chartDistanceHome->legend()->setVisible(false);
    chartDistanceHome->legend()->setLabelBrush(QBrush(QColor(color_blue)));
    chartDistanceHome->setBackgroundVisible(false);

    QLineSeries *expSeriesDistance = new QLineSeries;
    QLineSeries *fittsSeriesDistance = new QLineSeries;
    QCategoryAxis *axisDistance = new QCategoryAxis;
    //end New plotHomeDistance

    QList<double> fittsValues;
    QList<double> DistRelatif;
    QList<double> listeTemps;
    QList<double> listeTempsCalcule;

    for(int i = 0; i < this->fittsModel->nbCible; ++i) {
        //Courbe Experimental
        double T = this->fittsModel->times[i];
        listeTemps.append(T);
        expSeries->append(i,T);
        double D = sqrt(pow(this->fittsModel->clickPoints[i].x() - this->fittsModel->cercleCenter[i].x(),2) + pow(this->fittsModel->clickPoints[i].y() - this->fittsModel->cercleCenter[i].y(),2));



        //Courbe Theorique
        // On multiplie par 1000 pour ??tre en ms
        double value = (this->fittsModel->a * 1000) + ((this->fittsModel->b * 1000) * log2(((D / this->fittsModel->cercleSize[i])) + 1));
        listeTempsCalcule.append(value);
        fittsValues.append(value);
        fittsSeries->append(i,value);

        axis->append(QString::number(i + 1) + "<br />T: "+QString::number(T)+"<br />D: " + QString::number(D,'f', 2),i);

        //Ajout d'une nouvelle courbe : le temps ex??cution (ordonn??e) en fonction de la distance relative log(D/L + 1) en abscisse
        //On utilise D en ordonn??e et value en abscisse

        DistRelatif.append(log(D/this->fittsModel->cercleSize[i] + 1));

    }


    //Sort
    for (int i=DistRelatif.length()-1; i > 0; i--){
        for (int j=0; j < i; j++){
            if (DistRelatif[j]>DistRelatif[j+1]){
                double tmp = DistRelatif[j+1];
                DistRelatif[j+1] = DistRelatif[j];
                DistRelatif[j] = tmp;

                tmp = listeTemps[j+1];
                listeTemps[j+1] = listeTemps[j];
                listeTemps[j] = tmp;

                tmp = listeTempsCalcule[j+1];
                listeTempsCalcule[j+1] = listeTempsCalcule[j];
                listeTempsCalcule[j] = tmp;
            }
        }
    }

    for(int i = 0; i < this->fittsModel->nbCible; ++i) {
        axisDistance->append(QString::number(DistRelatif[i]), DistRelatif[i]);
        expSeriesDistance->append(DistRelatif[i], DistRelatif[i]);
        fittsSeriesDistance->append(DistRelatif[i], listeTemps[i]);
    }

    axis->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

    QPen pen(QRgb(0xffffff));
    pen.setColor(color_purple);
    pen.setWidth(3);
    expSeries->setPen(pen);
    expSeries->setVisible();
    expSeriesDistance->setVisible();
    fittsSeriesDistance->setPen(pen);

    pen.setColor(color_blue);
    pen.setWidth(3);
    expSeriesDistance->setPen(pen);
    fittsSeries->setPen(pen);

    chartHome->addSeries(expSeries);
    chartHome->addSeries(fittsSeries);

    QPen dotted;
    dotted.setWidth(2);
    QVector<qreal> dashes;
    dashes << 4 << 4;
    dotted.setDashPattern(dashes);
    dotted.setColor(color_grid);

    axis->setGridLinePen(dotted);
    axisDistance->setGridLinePen(dotted);

    QFont reperes;
    reperes.setFamily("ROBOTO");
    axis->setLabelsFont(reperes);
    axisDistance->setLabelsFont(reperes);

    axis->setLabelsColor(color_blue);
    axisDistance->setLabelsColor(color_blue);

    chartHome->setAxisX(axis,expSeries);
    chartHome->setAxisX(axis,fittsSeries);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("temps (en ms)");
    axisY->setGridLinePen(dotted);
    axisY->setLabelsColor(color_blue);
    chartHome->setAxisY(axisY,expSeries);

    //New plotHomeDistance axes
    axisDistance->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    chartDistanceHome->addSeries(expSeriesDistance);
    chartDistanceHome->addSeries(fittsSeriesDistance);
    chartDistanceHome->setAxisX(axisDistance,expSeriesDistance);


    QValueAxis *axisYDistance = new QValueAxis;
    axisYDistance->setTitleText("temps (en ms)");
    axisYDistance->setGridLinePen(dotted);
    axisYDistance->setLabelsColor(color_blue);
    chartDistanceHome->addAxis(axisYDistance, Qt::AlignLeft);
    chartDistanceHome->setAxisY(axisYDistance,fittsSeriesDistance);

    //end New plotHomeDistance axes



    // Calcul des valeurs
    // Moyennes
    QList<double> diffValues;
    double diffMoy = 0;

    for (int i = 0; i < fittsValues.size(); ++i) {
        diffValues.append(fabs(fittsValues[i] - this->fittsModel->times[i]));
        diffMoy += fabs(fittsValues[i] - this->fittsModel->times[i]);
    }
    diffMoy /= fittsValues.size();

    // On stock la difference de moyenne
    this->fittsModel->diffMoy = fabs(diffMoy);


    // Ecart type
    double variance = 0;

    for (int i = 0; i < fittsValues.size(); ++i) {
        variance += pow(diffValues[i] - diffMoy,2);
    }
    variance /= fittsValues.size();

    double ecartTypeHome = sqrt(variance);

    // On stock l'ecart type
    this->fittsModel->ecartType = ecartTypeHome;
    // On stock l'erreur type
    this->fittsModel->erreurType = fabs(ecartTypeHome / sqrt(fittsValues.size()));

    // On stock itc 95%
    this->fittsModel->itc95 = 2 * this->fittsModel->erreurType;

    this->fittsView->displayResults();

}

//ajoute un enregistrement au fichier data.json
void FittsController::addHisto(){
    this->histModel->prepend(*this->fittsModel);

    //Cr??e le r??pertoire si n'existe pas encore
    QDir().mkpath(QDir::currentPath()+"/dataFitts");

    //chemin o?? est enregistr?? le fichier data.json
    QString jsonPath = QDir::currentPath()+"/dataFitts/data.json";

    QFile fileReader(jsonPath);
    fileReader.open(QIODevice::ReadOnly);

    QJsonDocument json = QJsonDocument::fromJson(fileReader.readAll());
    QJsonArray array = json.array();
    array.prepend(this->fittsModel->writeDataJson());
    QJsonDocument newJson(array);

    fileReader.close();


    QFile fileWriter(jsonPath);
    fileWriter.open(QIODevice::WriteOnly);
    fileWriter.write(newJson.toJson());
    fileWriter.close();
}

//Supprime un enregistrement du fichier json et recharge la nouvelle page avec liste maj
void FittsController::deleteHisto(int index){
    QMessageBox::StandardButton confirm;
    confirm = QMessageBox::question(this->fittsView,"Demande Suppression","??tes vous sur de vouloir supprimer ?",
                                    QMessageBox::Yes|QMessageBox::Cancel);
    if(confirm == QMessageBox::Yes){
        QString jsonPath = QDir::currentPath()+"/dataFitts/data.json";

        QFile fileReader(jsonPath);
        fileReader.open(QIODevice::ReadOnly);
        QJsonDocument json = QJsonDocument::fromJson(fileReader.readAll());
        QJsonArray array = json.array();

        array.removeAt(index);
        QJsonDocument newJson(array);
        fileReader.close();

        QFile fileWriter(jsonPath);
        fileWriter.open(QIODevice::WriteOnly);
        fileWriter.write(newJson.toJson());
        fileWriter.close();

        this->histModel->removeAt(index);

        //recharger fittsView avec la liste des tests mis ?? jour
        reloadFittsView();
    }
}

//retourne un tableau de tous les enregistrements du fichier json
QJsonArray FittsController::getHisto(){
    QString jsonPath = QDir::currentPath()+"/dataFitts/data.json";

    QFile fileReader(jsonPath);
    fileReader.open(QIODevice::ReadOnly);
    QJsonDocument json = QJsonDocument::fromJson(fileReader.readAll());
    QJsonArray array = json.array();

    fileReader.close();

    return array;
}

//Fonction pour changer le graphique si un enregistrement est choisi
void FittsController::loadGraph(int index){
    //recuperer l'enregistrement correspondant ?? l'index
    QJsonObject dataItem = getHisto().at(index).toObject();
    //mettre les donn??es de l'enregistrement dans le fittsModel
    this->fittsModel->writeDataModel(dataItem);
    this->calculateResultHome();
    this->fittsView->displayResults();
    this->fittsView->hasSimulated = true;
}

//Fonction pour rechager la page apr??s une suppression ou un test
void FittsController::reloadFittsView(){
    QRect geo = this->fittsView->geometry();
    this->fittsView->destroy();
    this->fittsView = new FittsView(this, this->fittsModel);
    this->start();
    //conservation de la taille de la fen??tre
    this->fittsView->setGeometry(geo);
    //pour remttre le mode clair s'il ??tait s??lectionn??
    if(color == true){
        color = false;
        this->changeMode();
    }
    this->fittsView->showMaximized();
}
