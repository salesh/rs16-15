#include "x11info.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
# include <X11/Xlib.h>
# include <xcb/xcb.h>
# include <QtGlobal>
#else
# include <QX11Info>
#endif
Display* X11Info::display(){

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    if (!_display) {
        _display = XOpenDisplay(NULL);
    }
    return _display;
#else
    return QX11Info::display();
#endif
}
unsigned long X11Info::app_root_window(int screen){

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    return screen == -1?
    XDefaultRootWindow(display()) :
    XRootWindowOfScreen(XScreenOfDisplay(display(), screen));
#else
    return QX11Info::appRootWindow(screen);
#endif
}
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    xcb_connection_t *X11Info::xcb_connection(){

    if (!_xcb) {
        _xcb = xcb_connect(NULL, &_xcb_preferred_screen);
    Q_ASSERT(_xcb);
    }
    return _xcb;
}
    xcb_connection_t* X11Info::_xcb = 0;
#endif
    Display* X11Info::_display = 0;
    int X11Info::_xcb_preferred_screen = 0;
