#ifndef GLOBALFAKEKEY_H
#define GLOBALFAKEKEY_H

#include<QObject>
#include<QKeySequence>
#include<QTime>

class FakeKeyprivate;

class GlobalFakeKey : public QObject{

    Q_OBJECT
public:
    explicit GlobalFakeKey(QObject * parent=0);
    virtual ~GlobalFakeKey();

    void sendKey(Qt::Key key, bool down);
    void sendModifier(Qt::KeyboardModifier modifiers, bool down);
    void sendButton(Qt::MouseButton button, bool down);
    void sendScroll(int direction, int delta, double acceleration);


private:
    FakeKeyprivate *_d;
    friend class FakeKeyprivate;

    static Qt::Key modifierToKey(Qt::KeyboardModifier mod);
    static Qt::KeyboardModifier const AllModifiers[4];

    static void wait(int const ms);
};



#endif // GLOBALFAKEKEY_H
