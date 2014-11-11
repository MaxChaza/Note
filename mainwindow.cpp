#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFontComboBox *choixPolice = new QFontComboBox;
    ui->mainToolBar->addWidget(choixPolice);

   // ui->scrollArea->move(ui->scrollArea->x()-ui->scrollArea->width(),ui->scrollArea->y());

    // Action Créer une note
    // Connexion du du signal et du slot
    QObject::connect(ui->actionNouvelle_note, SIGNAL(triggered()), this, SLOT(createNote()));

    // Action Fermer le fichier en cours
    // Connexion du du signal et du slot
    QObject::connect(ui->actionFermer, SIGNAL(triggered()), this, SLOT(closeSubWindow()));

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

void MainWindow::createNote(){
    if(!ui->mdiArea->subWindowList().isEmpty())
    {
        QMdiSubWindow *first = ui->mdiArea->subWindowList().at(0);
        first->close();
    }
    else
    {
        ui->actionFermer->setEnabled(true);
    }
    QGraphicsView *note = new QGraphicsView(ui->mdiArea);
    QMdiSubWindow *sub = ui->mdiArea->addSubWindow(note);

    sub->show();
}

void MainWindow::closeSubWindow(){
    if(!ui->mdiArea->subWindowList().isEmpty())
    {
        QMdiSubWindow *first = ui->mdiArea->subWindowList().at(0);
        first->close();
        ui->actionFermer->setEnabled(false);
    }
}

void MainWindow::openScroll(){
    //qDebug() << ui->scrollArea->x();
    if(!ui->mdiArea->subWindowList().isEmpty() && !ui->scrollArea->isVisible())
    {
        for(int i=0 ; i < ui->scrollArea->width() ; i=i+2)
        {
            ui->scrollArea->move(ui->scrollArea->x()+2,ui->scrollArea->y());
            repaint();
        }
        ui->scrollArea->setVisible(true);
    }
}

void MainWindow::closeScroll(){
    if(ui->scrollArea->isVisible())
    {
        int width=ui->scrollArea->width();
        for(int i=0 ; i < width ; i=i+2)
        {
            //ui->scrollArea->move(ui->scrollArea->x()-1,ui->scrollArea->y());
            ui->scrollArea->setFixedWidth(ui->scrollArea->width()-2);
            repaint();
        }
        ui->scrollArea->setVisible(false);
    }
}

bool MainWindow::eventFilter(QObject * obj, QEvent *event)
{
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    if(mouseEvent->pos().x()<=0 && mouseEvent->pos().y()>0){
        openScroll();
    }

    if(mouseEvent->pos().x()>=20 && mouseEvent->pos().y()>0){
        closeScroll();
    }
    return false;
}
