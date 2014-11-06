#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Action Quitter du menu Fichier à la fermeture de l'application
    // Connexion du du signal et du slot
    QObject::connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(close()));
/*
    // Raccourci
    ui->actionQuitter->setShortcut(QKeySequence("Ctrl+Alt+Q"));
    // Ajout d'une icône
    ui->actionQuitter->setIcon(QIcon("icon/block.png"));
*/
/*
    QFontComboBox *choixPolice = new QFontComboBox;
    ui->mainToolBar->addWidget(choixPolice);
*/}

MainWindow::~MainWindow()
{
    delete ui;
}
