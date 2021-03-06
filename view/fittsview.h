#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graphicwidget.h"

#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QStackedLayout>
#include <QGraphicsView>
#include <QLabel>
#include <QLineSeries>
#include <QtCharts>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QChart>
#include <QPolarChart>
#include <QGraphicsDropShadowEffect>
#include <QToolBar>
#include <QToolButton>
#include <QScrollArea>
#include <QDateTime>

QT_CHARTS_USE_NAMESPACE

class FittsModel;
class FittsController;

class FittsView : public QMainWindow
{
    Q_OBJECT
public:
    FittsView(FittsController *fittsController, FittsModel *fittsModel);
    ~FittsView();

    void initWindows();
    void sizeWindows();
    void reloadHisto();
    void change_color(bool);

private:
    void updateTestMsg();
    void displayResults();
    void displayHisto();

    FittsModel *fittsModel;
    FittsController *fittsController;

    QPushButton *startBtn;
    QPushButton *backBtn;
    QPushButton *backBtn2;

    QToolButton *switchGraphHome;
    QToolButton *switchMode;
    QToolButton *graphZoom;
    bool isPlotHome = true;
    bool hasSimulated = false;

    QList<QToolButton *> lstEyeButtons;
    QList<QToolButton *> lstDeleteButtons;
    QSignalMapper *eyeSignalMapper;
    QSignalMapper *deleteSignalMapper;

    QDoubleSpinBox *aValue;
    QDoubleSpinBox *bValue;
    QSpinBox *nbCible;
    QSpinBox *minSize;
    QSpinBox *maxSize;

    QVBoxLayout *scrollAreaLayout;

    QStackedLayout *mainStack;

    GraphicWidget *graphicView;
    QGraphicsScene *scene;

    QLabel *testLabel;
    QLabel *ecartType;
    QLabel *erreurType;
    QLabel *diffMoy;
    QLabel *itc95;
    QLabel *graphTitle;
    QLabel *graphTitleHome;

    QChartView *plotHome;
    QChartView *plotHomeDistance;
    QChartView *chartZoomed;

    QWidget *mainWidget = new QWidget;
      QFrame *frameRight = new QFrame();
      QFrame *buttonFrame = new QFrame();
      QFrame *scrollFrame = new QFrame();
      QFrame *sepLeft = new QFrame();
      QLabel *label1;
      QLabel *label2;
      QLabel *label3;
      QLabel *label4;
      QLabel *label5;
      QLabel *label6;
      QLabel *label7;
      QLabel *label8;
      QLabel *label9;
      QLabel *label10;
      QLabel *label11;
      QLabel *label12;

      QScrollArea *scrollArea = new QScrollArea;
      QFrame *cardTop = new QFrame();
      QVBoxLayout *cardTopLayout = new QVBoxLayout();
      QFrame *theoriqueSquare;
      QLabel *legendTheo;
      QFrame *expSquare;
      QLabel *legendExp;
      QFrame *cardBottom;
      QList<QLabel *> lstlabelDate;
      QFrame *bottomCardSeparator;
      QFrame *optionSeparator;
      QFrame *statSeparator;
      QFrame *testSeparator;
      QVBoxLayout *configLayoutItem;
      QFrame *separator;
      QJsonObject current;
      QJsonArray histo;

    friend FittsController;
};

//Utiles
static QString color_bg = "#212121";
static QString color_black = "#121212";
static QString color_dark_grey = "#272727";
static QString color_light_grey = "#b7b7b7";
static QString color_blue = "#00dac7";
static QString color_blue_focus = "#00fcdd";
static QString color_purple = "#bd88f7";
static QString color_purple_focus = "#c49fff";
static QString color_red = "#d36579";
static QString color_red_focus = "#f77994";
static QString color_white = "#ffffff";
static QString color_grid = "#3d3f44";
static QString  color_red_grey = "#f8f0ed";
static QString  color_red_light = "#FF0000";
static QString color_itemList_bg = "#151618";
static QString color_itemList_bg_focus = "#212121";

static QString color_white_pink = "#F3FFFE";
static QString color_white_blue = "#D3EFFF";


static QString button_radius = "15px";

#endif // MAINWINDOW_H
