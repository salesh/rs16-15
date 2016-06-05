#ifndef TOUCHPAD_H
#define TOUCHPAD_H

#include <QScrollArea>
#include <QEvent>
#include <QTouchEvent>

class TouchPad : public QScrollArea {
    Q_OBJECT
public:
    explicit TouchPad(QWidget* parent)
        : QScrollArea(parent)
    {

        setAttribute(Qt::WA_AcceptTouchEvents);
    }

    bool viewportEvent(QEvent *event);

signals:
    void sendMove(const QPointF& delta);
};


#endif // TOUCHPAD_H
