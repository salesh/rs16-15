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

    void send_key(Qt::Key key, bool down);
    void send_modifier(Qt::KeyboardModifier modifaers, bool down);
    void send_button(Qt::MouseButton button, bool down);
    void send_scroll(int direction, int delta, double acceleration);


private:
    FakeKeyprivate *_d;
    friend class FakeKeyprivate;

    static Qt::Key modifier_to_key(Qt::KeyboardModifier mod);
    static Qt::KeyboardModifier const AllModifiers[4];

    static void wait(int const ms);
};



#endif // GLOBALFAKEKEY_H
