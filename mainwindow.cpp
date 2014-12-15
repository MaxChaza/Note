#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSvgWidget"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() <<ui->dockWidget->isHidden();
    ui->dockWidget->setHidden(true);
    QFontComboBox *choixPolice = new QFontComboBox;
    ui->mainToolBar->addWidget(choixPolice);



    // Action Créer une note
    // Connexion du du signal et du slot
    QObject::connect(ui->actionNouvelle_note, SIGNAL(triggered()), this, SLOT(createNote()));

    // Action Fermer le fichier en cours
    // Connexion du du signal et du slot
    QObject::connect(ui->actionFermer, SIGNAL(triggered()), this, SLOT(closeNote()));

    // Action Quitter du menu Fichier à la fermeture de l'application
    // Connexion du du signal et du slot
    QObject::connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(close()));

    setMouseTracking(true);
    installEventFilter(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

// Création d'une nouvelle note
void MainWindow::createNote(){
//    if(!ui->mdiArea->subWindowList().isEmpty())
//    {
//        // Si une note est en cours on propose l'enregistrement puis on la ferme avant d'en créer une nouvelle
//        // QDialogue pour l'enregistrement


//        QMdiSubWindow *first = ui->mdiArea->subWindowList().at(0);
//        first->close();
//    }
//    else
//    {
//        // Si aucune note n'est ouverte on en créé une
//        ui->actionFermer->setEnabled(true);
//    }

//    //QGraphicsView *note = new QGraphicsView(ui->mdiArea);

//    QSvgWidget window("../build-Note-Desktop_Qt_5_3_MinGW_32bit-Debug/debug/icon/NewTux.svg");
//    QMdiSubWindow *sub = ui->mdiArea->addSubWindow(&window);
//    QSvgRenderer *renderer = window.renderer();
//    QImage image(850, 900, QImage::Format_RGB32);
//    QPainter painter;
//    painter.begin(&image);
//    renderer->render(&painter);
//    painter.end();

//    sub->show();

}

void MainWindow::closeNote(){

}

void MainWindow::openScroll(){
//    //qDebug() << ui->scrollArea->width();

    if(true)
    {
         ui->dockWidget->setHidden(false);
    }
}

void MainWindow::closeScroll(){
//    // Penser à bloquer les valeurs
//    //qDebug() << ui->scrollArea->width();
    ui->dockWidget->setHidden(true);
}

bool MainWindow::eventFilter(QObject * obj, QEvent *event)
{
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    if(mouseEvent->pos().x()<=0 && mouseEvent->pos().y()>0){

        openScroll();
    }

    if(mouseEvent->pos().x()>=100 && mouseEvent->pos().y()>0){

        closeScroll();
    }
    return false;
}
