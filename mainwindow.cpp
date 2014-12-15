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

    // Action Quitter du menu Fichier à la fermeture de l'application
    // Connexion du du signal et du slot
    QObject::connect(ui->actionTexte, SIGNAL(triggered()), this, SLOT(addText()));


    scene = new QGraphicsScene();
    QGraphicsTextItem *text = scene->addText("bogotobogo.com", QFont("Arial", 20) );
    // movable text
    text->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addText("Hello!");



    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);
    QGraphicsEllipseItem *ellipse;
    ellipse = scene->addEllipse(0, -100, 300, 60, outlinePen, greenBrush);
    ellipse->setFlag(QGraphicsItem::ItemIsMovable);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();

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
    if (event->type() == QEvent::Wheel) {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
        ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        double scaleFactor=1.15;

        if (wheelEvent->delta()>0) {
            ui->graphicsView->scale(scaleFactor,scaleFactor);
        } else {
            ui->graphicsView->scale(1/scaleFactor,1/scaleFactor);
        }
        event->accept();
    }
    else
    {

        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if(mouseEvent->pos().x()<=0 && mouseEvent->pos().y()>0){

            openScroll();
        }

        if(mouseEvent->pos().x()>=100 && mouseEvent->pos().y()>0){

            closeScroll();
        }
    }
    return false;
}

void MainWindow::addText(){
    //    // Penser à bloquer les valeurs
    //    //qDebug() << ui->scrollArea->width();
}
