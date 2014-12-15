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
    Q_ENUMS(States)
public:
    explicit MainWindow(QWidget *parent = 0);
    enum states
    {
        Text,
        Selection
    };
    ~MainWindow();

public slots:
    void createNote();
    void closeNote();
    void openScroll();
    void closeScroll();
    bool eventFilter(QObject * obj, QEvent *event);
    void addText(int x, int y);
    void textState();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    states state;
};

#endif // MAINWINDOW_H
