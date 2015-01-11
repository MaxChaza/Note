#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtSvg/QtSvg>
#include <mygraphicsscene.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

public slots:
    void createNote();
    void closeNote();
    void openScroll();
    void closeScroll();
    bool eventFilter(QObject * obj, QEvent *event);
    void addText(int x, int y);
    void addText(int x, int y, QString text);
    void setPolicy(QString policy);
    void textState();

private:
    Ui::MainWindow *ui;
    MyGraphicsScene *scene;
    QComboBox *choixPolice;
};

#endif // MAINWINDOW_H
