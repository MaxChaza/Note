#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSvgWidget"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dockWidget->setHidden(true);
    choixPolice = new QComboBox;
    choixPolice->addItem("Titre");
    choixPolice->addItem("Contenu");
    ui->mainToolBar->addWidget(choixPolice);
    choixPolice->installEventFilter(this);


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
    QObject::connect(ui->actionTexte, SIGNAL(triggered()), this, SLOT(textState()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Création d'une nouvelle note
void MainWindow::createNote(){
    ui->actionFermer->setEnabled(true);
    ui->actionTexte->setEnabled(true);

    //    scene = new QGraphicsScene(-ui->graphicsView->width()*2+ui->graphicsView->width()/2, -ui->graphicsView->height()*2+ui->graphicsView->height()/2, ui->graphicsView->width()*4, ui->graphicsView->height()*4);
    scene = new MyGraphicsScene(0, 0, ui->graphicsView->width()*4, ui->graphicsView->height()*4, ui->graphicsView);
    // movable text
    //    QGraphicsTextItem *text = scene->addText("texte->toPlainText()", QFont("Arial", 20));
    //    text->setFlag(QGraphicsItem::ItemIsMovable);
    //    text->setFlag(QGraphicsItem::ItemIsFocusable);
    //    text->setFlag(QGraphicsItem::ItemIsSelectable);
    //    text->setAcceptHoverEvents(true);
    //    scene->addText("Hello!");




    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);
    QGraphicsEllipseItem *ellipse;
    ellipse = scene->addEllipse(0, -30+scene->height()/2, ui->graphicsView->width()*4, 60, outlinePen, greenBrush);
    ellipse->setFlag(QGraphicsItem::ItemIsMovable);



    choixPolice->setEnabled(true);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();

    setMouseTracking(true);

    installEventFilter(this);
    installEventFilter(choixPolice);
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
    if(false)
    {
        ui->dockWidget->setHidden(false);
        choixPolice->setEnabled(false);
    }
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

void MainWindow::textState(){
    scene->textState();
}

bool MainWindow::eventFilter(QObject * obj, QEvent *event)
{
    qDebug() << event->type();

    if(event->type() == QEvent::ActionChanged){}

    if(event->type() == QEvent::UpdateRequest){}

    if(event->type() == QEvent::MouseButtonPress){}

    return false;
}


void MainWindow::setPolicy(QString policy)
{
    if(policy=="Contenu")
        scene->policy = 15;
    else
        scene->policy = 25;
}

//void MainWindow::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
//{
//    scene->setActive(true);
//    this->setFocus();
//}

