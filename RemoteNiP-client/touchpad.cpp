#include "touchpad.h"


bool TouchPad::viewportEvent(QEvent *event) {
    switch(event->type()) {
    case QEvent::TouchBegin:
    {
        QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
        QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();
        touchPoints.first().setLastPos(touchPoints.first().pos());
    }
        break;
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
    {

        QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
        QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();

        const QTouchEvent::TouchPoint &touchPoint0 = touchPoints.first();
        if (touchPoints.count() == 1 && !touchPoint0.lastPos().isNull()) {
            QPointF delta = touchPoint0.pos() - touchPoint0.lastPos();
            emit sendMove(delta);
            return true;
        }
    }
        break;
    default:
        return QWidget::event(event);
    }
    return false;
}
