#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QtWidgets>
class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
    Q_ENUMS(States)
public:
    MyGraphicsScene(qreal x, qreal y, qreal width, qreal height, QGraphicsView *parent);
    enum states
    {
        Text,
        Selection
    };
    QGraphicsView *parent;
    double zoom;
    int policy;
    states state;
    QTextEdit *bufferTextCoord;
    QTextEdit *bufferTextDisplayed;

public slots:
    bool eventFilter(QObject * obj, QEvent *event);
    void createTextEdit(int x, int y);
    void displayText(int x, int y, QString inText);
    void textState();
};

#endif // MYGRAPHICSSCENE_H
