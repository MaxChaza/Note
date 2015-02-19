#include "mygraphicsscene.h"
#include "mygraphicsscene.h"

MyGraphicsScene::MyGraphicsScene(qreal x, qreal y, qreal width, qreal height, QGraphicsView *par) : QGraphicsScene(x, y, width, height, par)
{
    installEventFilter(this);
    parent = par;
    zoom = 0;
    state = MyGraphicsScene::Selection;
    parent->setMouseTracking(true);
    bufferTextCoord = new QTextEdit("");
    bufferTextCoord->setVisible(false);
    bufferTextDisplayed = new QTextEdit("");
    policy = 20;
}

bool MyGraphicsScene::eventFilter(QObject * obj, QEvent *event)
{

//    qDebug() << event->type();


    switch (event->type()) {
    case QEvent::GraphicsSceneWheel:
    {
        QGraphicsSceneWheelEvent *wheelEvent = static_cast<QGraphicsSceneWheelEvent*>(event);
        parent->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        double scaleFactor=1.15;
        double modif;
        if (wheelEvent->delta()>0) {
            qDebug() << "Zoom";
            modif=scaleFactor;
            if(zoom<10){
                zoom++;
                parent->scale(modif,modif);
            }
        } else {
            qDebug() << "Dezoom";
            modif=1/scaleFactor;
            if(zoom>-10){
                zoom--;
                parent->scale(modif,modif);
            }
        }
        event->accept();
        qDebug() << zoom;
        break;
    }
/*
    case QEvent::FocusOut:
    {

        if(bufferText->toPlainText()!="" && state==MyGraphicsScene::Text )
        {
            displayText(bufferText->geometry().x(), bufferText->geometry().y(), bufferText->toPlainText());
        }
        bufferText->setVisible(false);
        break;
    }

    case QEvent::GraphicsSceneMousePress:
    {
        QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);

//        switch (state) {
//        case MyGraphicsScene::Text:
            bufferText->setGeometry(mouseEvent->scenePos().x(),mouseEvent->scenePos().y(), bufferText->geometry().width(), bufferText->geometry().height());
            break;
//        }
        //        else
        //        {
        //            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        //            if(mouseEvent->pos().x()<=0 && mouseEvent->pos().y()>0){
        //                openScroll();
        //            }
        //            if(mouseEvent->pos().x()>=100 && mouseEvent->pos().y()>0){
        //                closeScroll();
        //            }
        //        }
        break;
    }
    */
    case QEvent::FocusOut:
    {
        qDebug()<<"QEvent::FocusOut";
//        if(bufferTextDisplayed->toPlainText()!="" && state==MyGraphicsScene::Text )
//        {
//            displayText(bufferTextCoord->geometry().x(), bufferTextCoord->geometry().y(), bufferTextDisplayed->toPlainText());
//            state=MyGraphicsScene::Selection;
//        }
//        bufferTextDisplayed->setVisible(false);
        break;
    }

    case QEvent::FocusIn:
    {
        qDebug()<<"QEvent::FocusIn";
        qDebug()<<bufferTextDisplayed->toPlainText();
        qDebug()<<state;
       if(bufferTextDisplayed->toPlainText()!="" && state==MyGraphicsScene::Text )
        {
            qDebug()<<"bufferTextDisplayed->toPlainText()!="" && state==MyGraphicsScene::Text";

            displayText(bufferTextCoord->geometry().x(), bufferTextCoord->geometry().y(), bufferTextDisplayed->toPlainText());
        }
        bufferTextDisplayed->setVisible(false);
        break;
    }

    case QEvent::GraphicsSceneMousePress:
    {
        QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
        qDebug()<<"QEvent::GraphicsSceneMousePress";

        switch (state) {
        case MyGraphicsScene::Selection:
        {
            createTextEdit(mouseEvent->scenePos().x(),mouseEvent->scenePos().y());
            state = MyGraphicsScene::Text;
            break;
        }
        case MyGraphicsScene::Text:
        {
            state = MyGraphicsScene::Selection;
            break;
        }

        //        else
        //        {
        //            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        //            if(mouseEvent->pos().x()<=0 && mouseEvent->pos().y()>0){
        //                openScroll();
        //            }
        //            if(mouseEvent->pos().x()>=100 && mouseEvent->pos().y()>0){
        //                closeScroll();
        //            }
        //        }
        }
        break;
    }
    }
    return false;
}


void MyGraphicsScene::createTextEdit(int x, int y){

    QGraphicsTextItem *text = this->addText("" , QFont("Arial", policy));

    // movable text
    text->setPos(x, y);
    text->setFlag(QGraphicsItem::ItemIsMovable);
    text->setFlag(QGraphicsItem::ItemIsFocusable);
    text->setFlag(QGraphicsItem::ItemIsSelectable);
    text->setTextInteractionFlags(Qt::TextEditorInteraction);
    text->setSelected(true);
    text->setActive(true);
    text->setAcceptHoverEvents(true);
}

void MyGraphicsScene::displayText(int x, int y, QString inText){
    }

void MyGraphicsScene::textState(){
    QCursor curseur;
    if(state != MyGraphicsScene::Text){
        state = MyGraphicsScene::Text;

        if(parent->cursor().shape() == Qt::ArrowCursor){
            curseur = QCursor(Qt::IBeamCursor);
            parent->setCursor(curseur);
        }
    }
    else
    {
        state = MyGraphicsScene::Selection;

        curseur = QCursor(Qt::ArrowCursor);
        parent->setCursor(curseur);
    }
}
