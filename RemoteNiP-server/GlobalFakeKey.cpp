#include"GlobalFakeKey.h"

class FakeKeyPrivate {
public:
    FakeKeyPrivate();
    GlobalFakeKey *_q;

    Display *display;
};
FakeKeyPrivate::FakeKeyPrivate(){
    display=X11Info::display();
}

GlobalFakeKey::GlobalFakeKey(QObject * parent):QObject(parent), _d(new FakeKeyPrivate){
    _d->_q=this;
}

GlobalFakeKey::~GlobalFakeKey(){

}


//We need to find out which key we get

void GlobalFakeKey::sendKey(Qt::Key key, bool down){
    KeySym keySym;
    bool shiftSet= false;
    bool altSet=false;

    Display *display=X11Info::display();
    if(!display)
        return;
    do{
        if(key>=Qt::Key_A && key<=Qt::Key_Z){
            keySym=QChar(key).toLower().unicode();
            break;
        }
        int i=1;
        bool found=false;
        while (KeyTbl[i]){
            if(key==KeyTbl[i]){
                keySym=(KeySym)KeyTbl[i-1];
                found=true;
                break;
            }
            i+=2;
        }
        if(found)
            break;

        //finding native code of the key
        if((key <0x1000 && key>=0x20) || (key>=Qt::Key_0 && key<=Qt::Key_9)){
            keySym=QChar(key).unicode();
            KeyCode keyCode =XKeysymToKeycode(display, keySym);
            int symsPerKeycode;
            KeySym *keyMap=XGetKeyboardMapping(display, keyCode, 1, &symsPerKeycode);

            if(keySym==keyMap[1] && key!=keyMap[0]){ //to check !
                sendModifiers(Qt::ShiftModifier, true);
                shiftSet=true;

            }
            else if(keySym==keyMap[4]){
                sendModifiers(Qt::AltModifier, true);
                altSet=true;
            }
            XFree(keyMap); //everything allocated via Xlib, is set free by Xfree (allocated memory)
            break;
        }
        return;
    } while(0);

    XTestFakeKeyEvent(display, XKeysymToKeycode(display, keySym), down, 0);
    XFlush(display);
    if(shiftSet)
        sendModifiers(Qt::ShiftModifier, false);
    else if(altSet)
        sendModifiers(Qt::AltModifier, false);
    GlobalFakeKey::wait(1);
}

void GlobalFakeKey::sendModifiers(Qt::KeyboardModifier modifiers, bool down){
    if(!(_d->display)) //running the check server is actually ON
        return;
    
    
    KeyCode shiftKeyCode=XKeysymToKeycode(_d->display, XK_Shift_L );
    KeyCode controlKeyCode=XKeysymToKeycode(_d->display, XK_Control_L );
    KeyCode altKeyCode=XKeysymToKeycode(_d->display, XK_Alt_L );
    
    if(modifiers & Qt::ShiftModifier)
        XTestFakeKeyEvent(_d->display, shiftKeyCode, down, 0);
    if(modifiers & Qt::ControlModifier)
        XTestFakeKeyEvent(_d->display, controlKeyCode, down, 0);
    if(modifiers & Qt::AltModifier)
        XTestFakeKeyEvent(_d->display, altKeyCode, down, 0);
    
    GlobalFakeKey::wait(1);

}

void GlobalFakeKey::sendButton(Qt::MouseButton button, bool down){
    if(!(_d->display))
        return;
    int nativeButton=1;
    
    if(button==Qt::LeftButton)
        nativeButton=1;
    else if (button==Qt::RightButton)
        nativeButton=3;
    else if (button==Qt::MiddleButton)
        nativeButton=2;
    
    XTestFakeButtonEvent(_d->display, nativeButton, down, 0);
    GlobalFakeKey::wait(1);
}

void GlobalFakeKey::sendScroll(int direction, int delta, double acceleration){
    if(!(_d->display))
        return;
    
    int button=6;
    if(direction==1){
        if(delta<0)
            button=6;
        else if(delta>0)
            button=7;
    }
    else{
        if(delta<0)
            button=4;
        else if(delta>0)
            button=5;
    }
    for(int i=0; i<qAbs(delta*acceleration); i++){
        XTestFakeButtonEvent(_d->display, button, true, 0);
        XTestFakeButtonEvent(_d->display, button, false, 0);
    }
    GlobalFakeKey::wait(1);
    
}



Qt::KeyboardModifier const GlobalFakeKey::AllModifiers[] =
{Qt::ShiftModifier, Qt::ControlModifier, Qt::AltModifier, Qt::KeypadModifier};

void GlobalFakeKey::wait(const int ms){

    QTime time;
    time.start();
    while (time.elapsed() < ms);
}
