#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtSvg/QtSvg>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QGraphicsScene *scene;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void createNote();
    void closeNote();
    void openScroll();
    void closeScroll();
    bool eventFilter(QObject * obj, QEvent *event);
    void addText();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
