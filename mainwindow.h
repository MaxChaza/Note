#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

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
    void closeSubWindow();
    void openScroll();
    void closeScroll();
    bool eventFilter(QObject * obj, QEvent *event);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
