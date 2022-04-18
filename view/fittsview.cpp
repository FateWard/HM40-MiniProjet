#include "fittsview.h"
#include "graphicwidget.h"
#include "fittscontroller.h"
#include "fittsmodel.h"

QT_CHARTS_USE_NAMESPACE

FittsView::FittsView(FittsController *fittsController, FittsModel *fittsModel) : QMainWindow() {
    this->fittsModel = fittsModel;

    this->initWindows();

    this->showMaximized();

////////////////////////////////////////////////////////////////////////////
    QMenu *menuQuit = menuBar()->addMenu("Quitter");
    QAction *quitAct = new QAction("Fermer l'appli");
    connect(quitAct, &QAction::triggered,[=](){QApplication::quit();});

    menuQuit->addAction(quitAct);
////////////////////////////////////////////////////////////////////////////


    // Btn clicked
    connect(startBtn,SIGNAL(clicked()),fittsController,SLOT(startSimulation()));

    connect(backBtn,SIGNAL(clicked()),fittsController,SLOT(cancel()));
    connect(backBtn2,SIGNAL(clicked()),fittsController,SLOT(zoomCancel()));

    connect(graphicView, SIGNAL(mouseClicked(int,int)), fittsController, SLOT(cibleClicked(int,int)));
    connect(switchGraphHome, SIGNAL(clicked()),fittsController,SLOT(changeGraphHome()));
    connect(switchMode, SIGNAL(clicked()),fittsController,SLOT(changeMode()));
    connect(graphZoom, SIGNAL(clicked()),fittsController, SLOT(chartZoom()));

    // SpinBox values update
    connect(aValue,SIGNAL(valueChanged(double)),fittsController,SLOT(aValueChanged(double)));
    connect(bValue,SIGNAL(valueChanged(double)),fittsController,SLOT(bValueChanged(double)));
    connect(nbCible,SIGNAL(valueChanged(int)),fittsController,SLOT(nbCibleChanged(int)));
    connect(minSize,SIGNAL(valueChanged(int)),fittsController,SLOT(minSizeChanged(int)));
    connect(maxSize,SIGNAL(valueChanged(int)),fittsController,SLOT(maxSizeChanged(int)));

}

FittsView::~FittsView() {}

void FittsView::change_color(bool choix){


    if(choix){
        this->switchMode->setIcon(QIcon(":/icons/nightModeButton"));
        this->setStyleSheet("QWidget{background-color:" + color_red_grey + ";}");
        frameRight->setStyleSheet("background-color: " + color_red_grey );
        scrollFrame->setStyleSheet("background-color: " + color_white );
        scrollArea->setStyleSheet("QScrollArea{border: none} QScrollBar:vertical{background-color: #F90000;} QScrollBar::handle:vertical{background-color: #F90050;} QScrollBar::add-page:vertical { background-color: #D12525; } QScrollBar::sub-page:vertical { background-color: #D12525; }");
        sepLeft->setStyleSheet("background-color:" + color_white);
        startBtn->setStyleSheet("QPushButton{color: "+color_dark_grey+"; background-color: " + color_blue + "; border-radius:" + button_radius +"; font: bold 20px 'ROBOTO'; padding: 20px; margin: 0px 30px} QPushButton:hover{background-color: " + color_blue_focus + "};");


        //changement des couleurs de la police des labels en Noir
        label1->setStyleSheet("color: #121212; font: bold 30px 'ROBOTO'; padding: 10px");
        label2->setStyleSheet("font: bold 20px 'ROBOTO'; color:" + color_black);
        label3->setStyleSheet("font: bold 20px 'ROBOTO'; color:" + color_black);
        label4->setStyleSheet("font: italic 18px 'ROBOTO'; color:" + color_light_grey);
        label5->setStyleSheet("font: 20px 'ROBOTO'; color:" + color_black);
        label6->setStyleSheet("font: 20px 'ROBOTO'; color:" + color_black);
        label7->setStyleSheet("margin-left: 28px; font: bold 30px 'ROBOTO'; color:" + color_black);
        label8->setStyleSheet("font: 20px 'ROBOTO'; color:" + color_black);
        label9->setStyleSheet("font: 20px 'ROBOTO'; color:" + color_black);
        label10->setStyleSheet("font: 20px 'ROBOTO'; color:" + color_black);
        label11->setStyleSheet("background-color: transparent; color: #121212; font: 20 18px 'ROBOTO';");



        graphTitleHome->setStyleSheet("font: bold 30px 'ROBOTO'; color:" + color_black);
        legendTheo->setStyleSheet("font: 20 20px 'ROBOTO'; color:" + color_black);
        legendExp->setStyleSheet("font: 20 20px 'ROBOTO'; color:" + color_black);
        ecartType->setStyleSheet("font: 14px 'ROBOTO'; color:" + color_black);


        diffMoy->setStyleSheet("font: 14px 'ROBOTO'; color:" + color_black);
        erreurType->setStyleSheet("font: 14px 'ROBOTO'; color:" + color_black);
        itc95->setStyleSheet("font: 14px 'ROBOTO'; color:" + color_black);
        graphTitleHome->setStyleSheet("font: bold 30px 'ROBOTO'; color:" + color_black);
        legendTheo->setStyleSheet("font: 20 20px 'ROBOTO'; color:" + color_black);
        legendExp->setStyleSheet("font: 20 20px 'ROBOTO'; color:" + color_black);
        bottomCardSeparator->setStyleSheet("background-color:" + color_black);
        aValue->setStyleSheet("QDoubleSpinBox{font: 26px 'ROBOTO'; color:" + color_black + ";} QDoubleSpinBox::down-button{subcontrol-origin: margin; subcontrol-position: center left; image: url(:/icons/moinsButton); width: 30px; height: 30px; margin-left: 40px} QDoubleSpinBox::up-button{subcontrol-origin: margin; subcontrol-position: center right; image: url(:/icons/plusButton); width: 30px; height: 30px; margin-right: 40px}");
        bValue->setStyleSheet("QDoubleSpinBox{font: 26px 'ROBOTO'; color:" + color_black + ";} QDoubleSpinBox::down-button{subcontrol-origin: margin; subcontrol-position: center left; image: url(:/icons/moinsButton); width: 30px; height: 30px; margin-left: 40px} QDoubleSpinBox::up-button{subcontrol-origin: margin; subcontrol-position: center right; image: url(:/icons/plusButton); width: 30px; height: 30px; margin-right: 40px}");
        nbCible->setStyleSheet("QSpinBox{font: 26px 'ROBOTO'; color:" + color_black + ";} QSpinBox::down-button{subcontrol-origin: margin; subcontrol-position: center left; image: url(:/icons/moinsButtonDark); width: 30px; height: 30px; margin-left: 40px} QSpinBox::up-button{subcontrol-origin: margin; subcontrol-position: center right; image: url(:/icons/plusButtonDark); width: 30px; height: 30px; margin-right: 40px}");;
        minSize->setStyleSheet("QSpinBox{font: 26px 'ROBOTO'; color:" + color_black + ";} QSpinBox::down-button{subcontrol-origin: margin; subcontrol-position: center left; image: url(:/icons/moinsButtonDark); width: 30px; height: 30px; margin-left: 40px} QSpinBox::up-button{subcontrol-origin: margin; subcontrol-position: center right; image: url(:/icons/plusButtonDark); width: 30px; height: 30px; margin-right: 40px}");
        maxSize->setStyleSheet("QSpinBox{font: 26px 'ROBOTO'; color:" + color_black + ";} QSpinBox::down-button{subcontrol-origin: margin; subcontrol-position: center left; image: url(:/icons/moinsButtonDark); width: 30px; height: 30px; margin-left: 40px} QSpinBox::up-button{subcontrol-origin: margin; subcontrol-position: center right; image: url(:/icons/plusButtonDark); width: 30px; height: 30px; margin-right: 40px}");
        startBtn->setStyleSheet("QPushButton{color: "+color_black+"; background-color: " + color_blue + "; border-radius:" + button_radius +"; font: bold 20px 'ROBOTO'; padding: 20px; margin: 0px 30px} QPushButton:hover{background-color: " + color_blue_focus + "};");
        backBtn->setStyleSheet("QPushButton{color: "+color_black+"; background-color: " + color_red + "; border-radius:" + button_radius +"; font: bold 20px 'ROBOTO'; padding: 20px; margin: 30px} QPushButton:hover{background-color: " + color_red_focus + "};");
        this->testLabel->setStyleSheet("color: "+color_black+"; font: 30px 'ROBOTO'; margin: 30px");

        cardBottom->setStyleSheet("background-color:" + color_white + "; border-radius: 20px");
        cardTop->setStyleSheet("background-color:" + color_white + "; border-radius: 20px");
        switchGraphHome->setStyleSheet("QToolButton{color: "+color_red_grey+"; border-radius:" + button_radius +"; font: bold 10px 'ROBOTO'; padding: 10px; margin-right: 40px}");
        backBtn->setStyleSheet("QPushButton{color: "+color_white+"; background-color: " + color_black + "; border-radius:" + button_radius +"; font: bold 20px 'ROBOTO'; padding: 20px; margin: 30px} QPushButton:hover{background-color: " + color_red_focus + "};");


        for(int i = 0; i < histo.size(); i++){
             current = histo.at(i).toObject();
             label11 = new QLabel(current["dateTime"].toString());
             label11->setStyleSheet("background-color: transparent; color: #121212; font: 20 18px 'ROBOTO';");
             label11->setAlignment(Qt::AlignCenter);
    }


    }else{

        this->switchMode->setIcon(QIcon(":/icons/dayModeButton"));


        label3->setStyleSheet("font: bold 20px 'ROBOTO'; color:" + color_white);
        label4->setStyleSheet("font: italic 18px 'ROBOTO'; color:" + color_light_grey);
        label5->setStyleSheet("font: 20px 'ROBOTO'; color:" + color_white);
        label6->setStyleSheet("font: 20px 'ROBOTO'; color:" + color_white);
        label7->setStyleSheet("margin-left: 28px; font: bold 30px 'ROBOTO'; color:" + color_white);
        label8->setStyleSheet("font: 20px 'ROBOTO'; color:" + color_white);
        label9->setStyleSheet("font: 20px 'ROBOTO'; color:" + color_white);
        label10->setStyleSheet("font: 20px 'ROBOTO'; color:" + color_white);
        label11->setStyleSheet("background-color: transparent; color: #ffffff; font: 20 18px 'ROBOTO';");


        graphTitleHome->setStyleSheet("font: bold 30px 'ROBOTO'; color:" + color_white);
        legendTheo->setStyleSheet("font: 20 20px 'ROBOTO'; color:" + color_white);
        legendExp->setStyleSheet("font: 20 20px 'ROBOTO'; color:" + color_white);
        ecartType->setStyleSheet("font: 14px 'ROBOTO'; color:" + color_white);


        diffMoy->setStyleSheet("font: 14px 'ROBOTO'; color:" + color_white);
        erreurType->setStyleSheet("font: 14px 'ROBOTO'; color:" + color_white);
        itc95->setStyleSheet("font: 14px 'ROBOTO'; color:" + color_white);
        graphTitleHome->setStyleSheet("font: bold 30px 'ROBOTO'; color:" + color_white);
        legendTheo->setStyleSheet("font: 20 20px 'ROBOTO'; color:" + color_white);
        legendExp->setStyleSheet("font: 20 20px 'ROBOTO'; color:" + color_white);
        bottomCardSeparator->setStyleSheet("background-color:" + color_white);
        aValue->setStyleSheet("QDoubleSpinBox{font: 26px 'ROBOTO'; color:" + color_white + ";} QDoubleSpinBox::down-button{subcontrol-origin: margin; subcontrol-position: center left; image: url(:/icons/moinsButton); width: 30px; height: 30px; margin-left: 40px} QDoubleSpinBox::up-button{subcontrol-origin: margin; subcontrol-position: center right; image: url(:/icons/plusButton); width: 30px; height: 30px; margin-right: 40px}");
        bValue->setStyleSheet("QDoubleSpinBox{font: 26px 'ROBOTO'; color:" + color_white + ";} QDoubleSpinBox::down-button{subcontrol-origin: margin; subcontrol-position: center left; image: url(:/icons/moinsButton); width: 30px; height: 30px; margin-left: 40px} QDoubleSpinBox::up-button{subcontrol-origin: margin; subcontrol-position: center right; image: url(:/icons/plusButton); width: 30px; height: 30px; margin-right: 40px}");
        nbCible->setStyleSheet("QSpinBox{font: 26px 'ROBOTO'; color:" + color_white + ";} QSpinBox::down-button{subcontrol-origin: margin; subcontrol-position: center left; image: url(:/icons/moinsButtonDark); width: 30px; height: 30px; margin-left: 40px} QSpinBox::up-button{subcontrol-origin: margin; subcontrol-position: center right; image: url(:/icons/plusButtonDark); width: 30px; height: 30px; margin-right: 40px}");;
        minSize->setStyleSheet("QSpinBox{font: 26px 'ROBOTO'; color:" + color_white + ";} QSpinBox::down-button{subcontrol-origin: margin; subcontrol-position: center left; image: url(:/icons/moinsButtonDark); width: 30px; height: 30px; margin-left: 40px} QSpinBox::up-button{subcontrol-origin: margin; subcontrol-position: center right; image: url(:/icons/plusButtonDark); width: 30px; height: 30px; margin-right: 40px}");
        maxSize->setStyleSheet("QSpinBox{font: 26px 'ROBOTO'; color:" + color_white + ";} QSpinBox::down-button{subcontrol-origin: margin; subcontrol-position: center left; image: url(:/icons/moinsButtonDark); width: 30px; height: 30px; margin-left: 40px} QSpinBox::up-button{subcontrol-origin: margin; subcontrol-position: center right; image: url(:/icons/plusButtonDark); width: 30px; height: 30px; margin-right: 40px}");
        startBtn->setStyleSheet("QPushButton{color: "+color_white+"; background-color: " + color_blue + "; border-radius:" + button_radius +"; font: bold 20px 'ROBOTO'; padding: 20px; margin: 0px 30px} QPushButton:hover{background-color: " + color_blue_focus + "};");
        backBtn->setStyleSheet("QPushButton{color: "+color_white+"; background-color: " + color_red + "; border-radius:" + button_radius +"; font: bold 20px 'ROBOTO'; padding: 20px; margin: 30px} QPushButton:hover{background-color: " + color_red_focus + "};");
        this->testLabel->setStyleSheet("color: "+color_white+"; font: 30px 'ROBOTO'; margin: 30px");
        cardBottom->setStyleSheet("background-color:" + color_black + "; border-radius: 20px");
        cardTop->setStyleSheet("background-color:" + color_black + "; border-radius: 20px");
        switchGraphHome->setStyleSheet("QToolButton{color: "+color_light_grey+"; border-radius:" + button_radius +"; font: bold 10px 'ROBOTO'; padding: 10px; margin-right: 40px}");


    }


}

void FittsView::initWindows() {

    mainWidget = new QWidget;
    this->setCentralWidget(mainWidget);
    this->setStyleSheet("QWidget{background-color:" + color_bg + ";}");

    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setMargin(0);

    mainStack = new QStackedLayout;
    mainLayout->addLayout(mainStack);


    QWidget *settingsWidget = new QWidget;
    mainStack->addWidget(settingsWidget);

    QHBoxLayout *settingsLayout = new QHBoxLayout(settingsWidget);
    QVBoxLayout *settingsLayoutLeft = new QVBoxLayout(settingsWidget);
    QVBoxLayout *settingsLayoutRight = new QVBoxLayout(settingsWidget);

    frameRight = new QFrame();
    frameRight->setStyleSheet("background-color: " + color_black);
    frameRight->setMinimumWidth(350);
    frameRight->setMaximumWidth(350);
    frameRight->setLayout(settingsLayoutRight);
    settingsLayoutRight->setMargin(0);
    settingsLayoutLeft->setMargin(40);

    settingsLayout->setContentsMargins(QMargins(0,0,0,0));
    settingsLayout->addLayout(settingsLayoutLeft);

    QVBoxLayout *rightBoxLayout = new QVBoxLayout(settingsWidget);//Layout pour la partie droite
    QHBoxLayout *buttonLayout = new QHBoxLayout();//Layout pour gérer les boutons
    rightBoxLayout->addLayout(buttonLayout);

//Bouton de switch de mode pour le graphique
    switchGraphHome = new QToolButton(this);
    switchGraphHome->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    switchGraphHome->setMinimumWidth(120);
    switchGraphHome->setMaximumWidth(120);
    switchGraphHome->setMinimumHeight(150);
    switchGraphHome->setMaximumHeight(150);
    switchGraphHome->setStyleSheet("QToolButton{color: "+color_light_grey+"; border-radius:" + button_radius +"; font: bold 10px 'ROBOTO'; padding: 10px; margin-right: 40px}");
    switchGraphHome->setCursor(Qt::PointingHandCursor);
    switchGraphHome->setIcon(QIcon(":/icons/switchGraphe_1"));
    switchGraphHome->setIconSize(switchGraphHome->size());
//Bouton de switch de mode
    switchMode = new QToolButton(this);
    switchMode->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    switchMode->setMinimumSize(130, 130);
    switchMode->setMaximumSize(130, 130);
    switchMode->setStyleSheet("QToolButton{color: "+color_light_grey+"; border-radius:" + button_radius +"; font: bold 10px 'ROBOTO'; padding: 10px; margin-right: 40px}");
    switchMode->setCursor(Qt::PointingHandCursor);
    switchMode->setIcon(QIcon(":/icons/dayModeButton"));
    switchMode->setIconSize(QSize(500, 500));


/////////////////////////////////////////////////////
    graphZoom = new QToolButton(this);
    graphZoom->setIcon(QIcon(":/icons/zoomButton"));
    graphZoom->setIconSize(QSize(130,130));
    graphZoom->setMinimumSize(50, 50);
    graphZoom->setMaximumSize(50, 50);
    graphZoom->setIconSize(graphZoom->size());
/////////////////////////////////////////////////////

    buttonLayout->setMargin(20);
    buttonLayout->addStretch();

    buttonLayout->addWidget(switchGraphHome); //Ajout du bouton de switch du graphique
    buttonLayout->addWidget(switchMode); //Ajout du bouton de switch de mode
    buttonLayout->addWidget(graphZoom);

    rightBoxLayout->addWidget(frameRight); //Ajout
    settingsLayout->addLayout(rightBoxLayout);


    //Droite

    label1 = new QLabel("Liste des tests");
    label1->setStyleSheet("color: #ffffff; font: bold 30px 'ROBOTO'; padding: 10px");
    label1->setMaximumHeight(100);
    label1->setMinimumHeight(100);
    label1->setMargin(0);
    settingsLayoutRight->addWidget(label1);

    this->scrollAreaLayout = new QVBoxLayout;
    scrollFrame = new QFrame();
    scrollFrame->setLayout(this->scrollAreaLayout);
    scrollFrame->setMinimumWidth(333);
    scrollFrame->setStyleSheet("background-color: " + color_itemList_bg );

    QLabel *imageLabel = new QLabel;
    QImage image(":/icons/test");
    imageLabel->setPixmap(QPixmap::fromImage(image));



    reloadHisto();



    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidget(scrollFrame);
    scrollArea->setStyleSheet("QScrollArea{border: none} QScrollBar:vertical{background-color: #242424;} QScrollBar::handle:vertical{background-color: #323232;} QScrollBar::add-page:vertical { background-color: #242424; } QScrollBar::sub-page:vertical { background-color: #242424; }");
    settingsLayoutRight->addWidget(scrollArea);

    //Droite - end


    //Gauche

    QHBoxLayout *settingsLayoutLeftTop = new QHBoxLayout();
    QHBoxLayout *settingsLayoutLeftBottom = new QHBoxLayout();
    settingsLayoutLeft->addLayout(settingsLayoutLeftTop);
    settingsLayoutLeft->addSpacing(25);
    sepLeft = new QFrame();
    sepLeft->setMinimumHeight(2);
    sepLeft->setMaximumHeight(2);
    sepLeft->setStyleSheet("background-color:" + color_dark_grey);
    settingsLayoutLeft->addWidget(sepLeft);
    settingsLayoutLeft->addSpacing(25);
    settingsLayoutLeft->addLayout(settingsLayoutLeftBottom);


    cardTop = new QFrame();
    cardTop->setMinimumWidth(275);
    cardTop->setMaximumWidth(275);
    cardTop->setMinimumHeight(380);
    cardTop->setStyleSheet("background-color:" + color_black + "; border-radius: 20px");

    settingsLayoutLeftTop->addWidget(cardTop);

    cardTopLayout = new QVBoxLayout();
    cardTop->setLayout(cardTopLayout);

    label2 = new QLabel();
    label2->setText("Statistiques");
    label2->setStyleSheet("font: bold 20px 'ROBOTO'; color:" + color_white);
    label2->setAlignment(Qt::AlignCenter);
    cardTopLayout->addWidget(label2);

    ecartType = new QLabel();
    ecartType->setStyleSheet("font: 14px 'ROBOTO'; color:" + color_white);
    ecartType->setAlignment(Qt::AlignCenter);
    cardTopLayout->addWidget(ecartType);

    diffMoy = new QLabel();
    diffMoy->setStyleSheet("font: 14px 'ROBOTO'; color:" + color_white);
    diffMoy->setAlignment(Qt::AlignCenter);
    cardTopLayout->addWidget(diffMoy);

    erreurType = new QLabel();
    erreurType->setStyleSheet("font: 14px 'ROBOTO'; color:" + color_white);
    erreurType->setAlignment(Qt::AlignCenter);
    cardTopLayout->addWidget(erreurType);

    itc95 = new QLabel();
    itc95->setStyleSheet("font: 14px 'ROBOTO'; color:" + color_white);
    itc95->setAlignment(Qt::AlignCenter);
    cardTopLayout->addWidget(itc95);


    QVBoxLayout *graphHomeLayout = new QVBoxLayout();
    settingsLayoutLeftTop->addLayout(graphHomeLayout);

    QHBoxLayout *titleLegend = new QHBoxLayout();
    titleLegend->addSpacing(50);
    graphTitleHome = new QLabel(this);
    graphTitleHome->setMinimumWidth(500);
    graphTitleHome->setText("Temps = f( cible )");
    graphTitleHome->setStyleSheet("font: bold 30px 'ROBOTO'; color:" + color_white);
    titleLegend->addWidget(graphTitleHome);

    titleLegend->addStretch();

    theoriqueSquare = new QFrame(this);
    theoriqueSquare->setMinimumHeight(20);
    theoriqueSquare->setMinimumWidth(20);
    theoriqueSquare->setMaximumHeight(20);
    theoriqueSquare->setMaximumWidth(20);
    theoriqueSquare->setStyleSheet("background-color: " + color_blue + ";border-radius: 3px;");
    titleLegend->addWidget(theoriqueSquare);

    legendTheo = new QLabel(this);
    legendTheo->setText("Théorique");
    legendTheo->setStyleSheet("font: 20 20px 'ROBOTO'; color:" + color_white);
    titleLegend->addWidget(legendTheo);

    titleLegend->addSpacing(30);

    expSquare = new QFrame(this);
    expSquare->setMinimumHeight(20);
    expSquare->setMinimumWidth(20);
    expSquare->setMaximumHeight(20);
    expSquare->setMaximumWidth(20);
    expSquare->setStyleSheet("background-color: " + color_purple + ";border-radius: 3px;");
    titleLegend->addWidget(expSquare);

    legendExp = new QLabel(this);
    legendExp->setText("Expérimental");
    legendExp->setStyleSheet("font: 20 20px 'ROBOTO'; color:" + color_white);
    titleLegend->addWidget(legendExp);

    graphHomeLayout->addLayout(titleLegend);



    plotHome = new QChartView;
    plotHomeDistance = new QChartView;
    plotHomeDistance->setVisible(false);
    graphHomeLayout->addWidget(plotHome);
    graphHomeLayout->addWidget(plotHomeDistance);

    //Gauche Top - end


    //Gauche Bottom

    cardBottom = new QFrame();
    cardBottom->setMinimumWidth(275);
    cardBottom->setMaximumWidth(275);
    cardBottom->setMinimumHeight(380);
    cardBottom->setStyleSheet("background-color:" + color_black + "; border-radius: 20px");
    settingsLayoutLeftBottom->addWidget(cardBottom);

    QVBoxLayout *cardBottomLayout = new QVBoxLayout();
    cardBottomLayout->setMargin(20);
    cardBottom->setLayout(cardBottomLayout);
    cardBottomLayout->addSpacing(10);

    label3 = new QLabel();
    label3->setText("Paramètres formule");
    label3->setStyleSheet("font: bold 20px 'ROBOTO'; color:" + color_white);
    label3->setAlignment(Qt::AlignCenter);
    cardBottomLayout->addWidget(label3);

    bottomCardSeparator = new QFrame();
    bottomCardSeparator->setMinimumHeight(2);
    bottomCardSeparator->setMaximumHeight(2);
    bottomCardSeparator->setStyleSheet("background-color:" + color_white);
    cardBottomLayout->addWidget(bottomCardSeparator);

    label4 = new QLabel();
    label4->setText("a + b*log2(2D/L)");
    label4->setStyleSheet("font: italic 18px 'ROBOTO'; color:" + color_light_grey);
    label4->setAlignment(Qt::AlignCenter);
    cardBottomLayout->addWidget(label4);
    cardBottomLayout->addSpacing(10);

    label5 = new QLabel();
    label5->setText("Variable A");
    label5->setStyleSheet("font: 20px 'ROBOTO'; color:" + color_white);
    label5->setAlignment(Qt::AlignCenter);
    cardBottomLayout->addWidget(label5);

    aValue = new QDoubleSpinBox;
    aValue->setValue(this->fittsModel->a);
    aValue->setMinimum(0.1);
    aValue->setSingleStep(0.1);
    aValue->setButtonSymbols(QAbstractSpinBox::PlusMinus);
    aValue->setAlignment(Qt::AlignHCenter);
    aValue->setMinimumHeight(30);
    aValue->setCursor(Qt::PointingHandCursor);
    aValue->setStyleSheet("QDoubleSpinBox{font: 26px 'ROBOTO'; color:" + color_white + ";} QDoubleSpinBox::down-button{subcontrol-origin: margin; subcontrol-position: center left; image: url(:/icons/moinsButton); width: 30px; height: 30px; margin-left: 40px} QDoubleSpinBox::up-button{subcontrol-origin: margin; subcontrol-position: center right; image: url(:/icons/plusButton); width: 30px; height: 30px; margin-right: 40px}");
    cardBottomLayout->addWidget(aValue);

    cardBottomLayout->addSpacing(10);

    label6 = new QLabel();
    label6->setText("Variable B");
    label6->setStyleSheet("font: 20px 'ROBOTO'; color:" + color_white);
    label6->setAlignment(Qt::AlignCenter);
    cardBottomLayout->addWidget(label6);

    bValue = new QDoubleSpinBox;
    bValue->setValue(this->fittsModel->b);
    bValue->setMinimum(0.1);
    bValue->setSingleStep(0.1);
    bValue->setButtonSymbols(QAbstractSpinBox::PlusMinus);
    bValue->setAlignment(Qt::AlignHCenter);
    bValue->setMinimumHeight(30);
    bValue->setCursor(Qt::PointingHandCursor);
    bValue->setStyleSheet("QDoubleSpinBox{font: 26px 'ROBOTO'; color:" + color_white + ";} QDoubleSpinBox::down-button{subcontrol-origin: margin; subcontrol-position: center left; image: url(:/icons/moinsButton); width: 30px; height: 30px; margin-left: 40px} QDoubleSpinBox::up-button{subcontrol-origin: margin; subcontrol-position: center right; image: url(:/icons/plusButton); width: 30px; height: 30px; margin-right: 40px}");
    cardBottomLayout->addWidget(bValue);
    cardBottomLayout->addSpacing(40);


    QVBoxLayout *settingsLayoutLeftBottomConfig = new QVBoxLayout();
    settingsLayoutLeftBottom->addLayout(settingsLayoutLeftBottomConfig);


    label7 = new QLabel();
    label7->setText("Configurations de la partie");
    label7->setStyleSheet("margin-left: 28px; font: bold 30px 'ROBOTO'; color:" + color_white);
    settingsLayoutLeftBottomConfig->addWidget(label7);

    settingsLayoutLeftBottomConfig->addStretch();

    QHBoxLayout *configLayout = new QHBoxLayout();
    settingsLayoutLeftBottomConfig->addLayout(configLayout);

    configLayoutItem = new QVBoxLayout();

    label8 = new QLabel();
    label8->setText("Nombre de cibles");
    label8->setStyleSheet("font: 20px 'ROBOTO'; color:" + color_white);
    label8->setAlignment(Qt::AlignCenter);
    configLayoutItem->addWidget(label8);

    nbCible = new QSpinBox;
    nbCible->setValue(this->fittsModel->nbCible);
    nbCible->setMaximum(100);
    nbCible->setMinimum(5);
    nbCible->setSingleStep(1);
    //QSize cibleSize(100,10);
    nbCible->setAlignment(Qt::AlignCenter);
    nbCible->setCursor(Qt::PointingHandCursor);
    nbCible->setStyleSheet("QSpinBox{font: 26px 'ROBOTO'; color:" + color_white + ";} QSpinBox::down-button{subcontrol-origin: margin; subcontrol-position: center left; image: url(:/icons/moinsButtonDark); width: 30px; height: 30px; margin-left: 40px} QSpinBox::up-button{subcontrol-origin: margin; subcontrol-position: center right; image: url(:/icons/plusButtonDark); width: 30px; height: 30px; margin-right: 40px}");;
    //nbCible->setMinimumWidth(100);
    configLayoutItem->addWidget(nbCible);
    configLayout->addLayout(configLayoutItem);

    separator = new QFrame;
    separator->setMinimumWidth(2);
    separator->setMaximumWidth(2);
    separator->setStyleSheet("background-color: " + color_grid);
    configLayout->addWidget(separator);


    configLayoutItem = new QVBoxLayout();
    label9 = new QLabel();
    label9->setText("Taille minimum");
    label9->setStyleSheet("font: 20px 'ROBOTO'; color:" + color_white);
    label9->setAlignment(Qt::AlignCenter);
    configLayoutItem->addWidget(label9);

    minSize = new QSpinBox;
    minSize->setMaximum(150);
    minSize->setMinimum(10);
    minSize->setSingleStep(10);
    minSize->setValue(this->fittsModel->minSize);
    minSize->setAlignment(Qt::AlignCenter);
    minSize->setCursor(Qt::PointingHandCursor);
    minSize->setStyleSheet("QSpinBox{font: 26px 'ROBOTO'; color:" + color_white + ";} QSpinBox::down-button{subcontrol-origin: margin; subcontrol-position: center left; image: url(:/icons/moinsButtonDark); width: 30px; height: 30px; margin-left: 40px} QSpinBox::up-button{subcontrol-origin: margin; subcontrol-position: center right; image: url(:/icons/plusButtonDark); width: 30px; height: 30px; margin-right: 40px}");
    configLayoutItem->addWidget(minSize);
    configLayout->addLayout(configLayoutItem);

    separator = new QFrame;
    separator->setMinimumWidth(2);
    separator->setMaximumWidth(2);
    separator->setStyleSheet("background-color: " + color_grid);
    configLayout->addWidget(separator);


    configLayoutItem = new QVBoxLayout();
    label10 = new QLabel();
    label10->setText("Taille maximum");
    label10->setStyleSheet("font: 20px 'ROBOTO'; color:" + color_white);
    label10->setAlignment(Qt::AlignCenter);
    configLayoutItem->addWidget(label10);

    maxSize = new QSpinBox;
    maxSize->setMaximum(400);
    maxSize->setMinimum(160);
    maxSize->setSingleStep(10);
    maxSize->setValue(this->fittsModel->maxSize);
    maxSize->setAlignment(Qt::AlignCenter);
    maxSize->setCursor(Qt::PointingHandCursor);
    maxSize->setStyleSheet("QSpinBox{font: 26px 'ROBOTO'; color:" + color_white + ";} QSpinBox::down-button{subcontrol-origin: margin; subcontrol-position: center left; image: url(:/icons/moinsButtonDark); width: 30px; height: 30px; margin-left: 40px} QSpinBox::up-button{subcontrol-origin: margin; subcontrol-position: center right; image: url(:/icons/plusButtonDark); width: 30px; height: 30px; margin-right: 40px}");
    configLayoutItem->addWidget(maxSize);
    configLayout->addLayout(configLayoutItem);

    settingsLayoutLeftBottomConfig->addStretch();

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(30);
    effect->setXOffset(0);
    effect->setYOffset(0);
    effect->setColor(color_blue);
    startBtn = new QPushButton("Démarrer");
    startBtn->setGraphicsEffect(effect);
    startBtn->setCursor(Qt::PointingHandCursor);
    startBtn->setStyleSheet("QPushButton{color: "+color_white+"; background-color: " + color_blue + "; border-radius:" + button_radius +"; font: bold 20px 'ROBOTO'; padding: 20px; margin: 0px 30px} QPushButton:hover{background-color: " + color_blue_focus + "};");
    settingsLayoutLeftBottomConfig->addWidget(startBtn);

    //Gauche Bottom - end

    //Gauche - end

    // Test part

    QWidget *testWidget = new QWidget;
    mainStack->addWidget(testWidget);
    mainStack->setMargin(0);

    QVBoxLayout *testLayout = new QVBoxLayout(testWidget);
    testLayout->setMargin(0);

    graphicView = new GraphicWidget;
    testLayout->addWidget(graphicView);
    graphicView->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff);
    graphicView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicView->setStyleSheet("border: 0px solid; background-color: #323232");

    scene = new QGraphicsScene;
    graphicView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
    graphicView->setScene(scene);
    scene->setSceneRect(0,0,graphicView->width(),300);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    testLayout->addLayout(btnLayout);

    backBtn = new QPushButton("Annuler");
    btnLayout->addWidget(backBtn);
    backBtn->setStyleSheet("QPushButton{color: "+color_white+"; background-color: " + color_red + "; border-radius:" + button_radius +"; font: bold 20px 'ROBOTO'; padding: 20px; margin: 30px} QPushButton:hover{background-color: " + color_red_focus + "};");
    backBtn->setMinimumHeight(30);
    backBtn->setMinimumWidth(300);
    backBtn->setMaximumWidth(300);
    backBtn->setCursor(Qt::PointingHandCursor);


    testLabel = new QLabel;
    testLabel->setAlignment(Qt::AlignCenter);
    btnLayout->addWidget(testLabel);

    btnLayout->addSpacing(300);

////////////////////////////////////////////////////////////////////////////
    //Widget of graph

    QWidget *graph = new QWidget;
    mainStack->addWidget(graph);
    mainStack->setMargin(0);

    backBtn2 = new QPushButton("Annuler");
    backBtn2->setStyleSheet("QPushButton{color: "+color_white+"; background-color: " + color_red + "; border-radius:" + button_radius +"; font: bold 20px 'ROBOTO'; padding: 20px; margin: 30px} QPushButton:hover{background-color: " + color_red_focus + "};");
    backBtn2->setMinimumHeight(30);
    backBtn2->setMinimumWidth(300);
    backBtn2->setMaximumWidth(300);
    backBtn2->setCursor(Qt::PointingHandCursor);


    QVBoxLayout *showingLayout = new QVBoxLayout(graph);
    chartZoomed = new QChartView;
    showingLayout->addWidget(chartZoomed);
    showingLayout->addWidget(backBtn2);

////////////////////////////////////////////////////////////////////////////
}

void FittsView::updateTestMsg() {
    this->testLabel->setText("<strong style='font-size:100px'>" + QString::number(this->fittsModel->cibleLeft) + "</strong><br>cibles restantes");
    this->testLabel->setStyleSheet("color: "+color_white+"; font: 30px 'ROBOTO'; margin: 30px");

}

void FittsView::displayResults() {
    this->diffMoy->setText("Différence moyenne = " + QString::number(this->fittsModel->diffMoy)+ " ms");
    this->ecartType->setText("Écart type = " + QString::number(this->fittsModel->ecartType) + " ms");
    this->erreurType->setText("Erreur type = " + QString::number(this->fittsModel->erreurType) + " ms");
    this->itc95->setText("Intervalle de conf à 95% = " + QString::number(this->fittsModel->itc95) + " ms");
}

void FittsView::reloadHisto(){

    while(this->scrollAreaLayout->layout()->takeAt(0) != NULL){
        delete this->scrollAreaLayout->widget();
    }

    //ITEM LISTE
    QHBoxLayout *scrollItemLayout;
    QFrame *scrollFrameItem;
    QToolButton *deleteButton;
    QFrame *scrollFrameLine;

    histo = this->fittsController->getHisto();


    for(int i = 0; i < histo.size(); i++){
        QToolButton *eyeButton;

        current = histo.at(i).toObject();

        scrollItemLayout = new QHBoxLayout;
        scrollFrameItem = new QFrame();
        scrollFrameItem->setLayout(scrollItemLayout);
        scrollFrameItem->setMinimumHeight(100);
        scrollFrameItem->setStyleSheet(".QFrame:hover{background-color:" + color_itemList_bg_focus + "}");

        eyeButton = new QToolButton();
        eyeButton->setMinimumWidth(40);
        eyeButton->setMinimumHeight(40);
        eyeButton->setMaximumHeight(40);
        eyeButton->setMaximumWidth(40);
        eyeButton->setStyleSheet("QToolButton{border-radius: 14px; background-color: " + color_blue +"} QToolButton:hover{background-color: " + color_blue_focus +"}");
        eyeButton->setCursor(Qt::PointingHandCursor);
        eyeButton->setIcon(QIcon(":/icons/eyeIcon"));
        eyeButton->setIconSize(QSize(28, 28));


        label11 = new QLabel(current["dateTime"].toString());
        label11->setStyleSheet("background-color: transparent; color: #ffffff; font: 20 18px 'ROBOTO';");
        label11->setAlignment(Qt::AlignCenter);

        deleteButton = new QToolButton();
        deleteButton->setMinimumWidth(25);
        deleteButton->setMinimumHeight(25);
        deleteButton->setMaximumHeight(25);
        deleteButton->setMaximumWidth(25);
        deleteButton->setStyleSheet("QToolButton{background-color: transparent; border-radius: 12px} QToolButton:hover{background-color: " + color_red_focus +"}");
        deleteButton->setCursor(Qt::PointingHandCursor);
        deleteButton->setIcon(QIcon(":/icons/beenIcon"));
        deleteButton->setIconSize(QSize(15, 15));

        scrollFrameLine = new QFrame();
        scrollFrameLine->setMinimumHeight(2);
        scrollFrameLine->setMaximumHeight(2);
        scrollFrameLine->setStyleSheet(".QFrame{background-color:" + color_bg + "}");


        scrollItemLayout->addWidget(eyeButton);
        scrollItemLayout->addWidget(label11);
        scrollItemLayout->addWidget(deleteButton);

        this->scrollAreaLayout->addWidget(scrollFrameItem);
        this->scrollAreaLayout->addWidget(scrollFrameLine);

    }

    //ITEM LISTE END
}
