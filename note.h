#ifndef NOTE_H
#define NOTE_H

#include <QDialog>
#include <QtWidgets>


class Note : public QGraphicsView
{
    Q_OBJECT

public:
    explicit Note(QMdiArea *parent = 0);
    ~Note();

private:
};

#endif // NOTE_H
