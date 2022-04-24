#ifndef FITTSCONTROLLER_H
#define FITTSCONTROLLER_H

#include <QObject>
#include <QElapsedTimer>
#include <QApplication>
#include <QDebug>
#include <QtGlobal>
#include <QtCharts>
#include <QChart>
#include <QLineSeries>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QLegend>
#include <QBarCategoryAxis>
#include <QHorizontalBarSeries>
#include <QCategoryAxis>
#include <QPieSeries>
#include <QPieSlice>
#include <QStringList>
#include <algorithm>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class FittsView;
class FittsModel;

class FittsController : public QObject
{
    Q_OBJECT
public:
    FittsController();
    virtual ~FittsController() {}
    void start();

    QList<FittsModel> *histModel;
    QJsonArray getHisto();

private:
    void initGame();
    void finish();
    void nextCible();

    void calculateResultHome();
    void addHisto();
    void reloadFittsView();


    FittsModel *fittsModel;
    FittsView *fittsView;

    QElapsedTimer *timer;

    QChart *chartHome;
    QChart *chartDistanceHome;

    bool color;
    QLabel *labelStart;

private slots:
    void quit();
    void startSimulation();
    void backToSettings();
    void cancel();
    void zoomCancel();
    void changeGraphHome();
    void changeMode();
    void chartZoom();

    void aValueChanged(double value);
    void bValueChanged(double value);
    void nbCibleChanged(int value);
    void minSizeChanged(int value);
    void maxSizeChanged(int value);

    void cibleClicked(int x, int y);

    void deleteHisto(int index);
    void loadGraph(int index);
};

#endif // FITTSCONTROLLER_H
