#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFontComboBox *choixPolice = new QFontComboBox;
    ui->mainToolBar->addWidget(choixPolice);

    closeScroll();

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
    qDebug() << ui->scrollArea->width();

    if(!ui->mdiArea->subWindowList().isEmpty() && ui->scrollArea->width()==5)
    {
        //ui->scrollArea->setVisible(true);

        //ui->scrollArea->setFixedWidth(ui->scrollArea->width()+1);
        QPropertyAnimation *animation = new QPropertyAnimation(ui->scrollArea, "geometry");
        animation->setDuration(300);
        animation->setStartValue(QRectF(ui->scrollArea->x(), ui->scrollArea->y(), ui->scrollArea->width(), ui->scrollArea->height()));
        animation->setEndValue(QRectF(ui->scrollArea->x(), ui->scrollArea->y(), ui->scrollArea->width()+155, ui->scrollArea->height()));

        animation->setEasingCurve(QEasingCurve::Linear);

        animation->start();

        QPropertyAnimation *animatio = new QPropertyAnimation(ui->mdiArea, "geometry");
        animatio->setDuration(300);
        animatio->setStartValue(QRectF(ui->mdiArea->x(), ui->mdiArea->y(), ui->mdiArea->width(), ui->mdiArea->height()));
        animatio->setEndValue(QRectF(ui->mdiArea->x()+155, ui->mdiArea->y(), ui->mdiArea->width()-155, ui->mdiArea->height()));

        animatio->setEasingCurve(QEasingCurve::Linear);

        animatio->start();
        //ui->scrollArea->move(ui->scrollArea->x()+2,ui->scrollArea->y());
        //repaint();

    }
}

void MainWindow::closeScroll(){
    // Penser à bloquer les valeurs
    qDebug() << ui->scrollArea->width();

    if(ui->scrollArea->isVisible() && ui->scrollArea->width()==160)
    {
        QPropertyAnimation *animation = new QPropertyAnimation(ui->scrollArea, "geometry");
        animation->setDuration(300);
        animation->setStartValue(QRectF(ui->scrollArea->x(), ui->scrollArea->y(), ui->scrollArea->width(), ui->scrollArea->height()));
        animation->setEndValue(QRectF(ui->scrollArea->x(), ui->scrollArea->y(), ui->scrollArea->width()-155, ui->scrollArea->height()));

        animation->setEasingCurve(QEasingCurve::Linear);

        animation->start();

        QPropertyAnimation *animatio = new QPropertyAnimation(ui->mdiArea, "geometry");
        animatio->setDuration(300);
        animatio->setStartValue(QRectF(ui->mdiArea->x(), ui->mdiArea->y(), ui->mdiArea->width(), ui->mdiArea->height()));
        animatio->setEndValue(QRectF(ui->mdiArea->x()-155, ui->mdiArea->y(), ui->mdiArea->width()+155, ui->mdiArea->height()));

        animatio->setEasingCurve(QEasingCurve::Linear);

        animatio->start();
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
