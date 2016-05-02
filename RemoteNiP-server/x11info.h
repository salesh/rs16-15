#ifndef X11INFO_H
#define X11INFO_H
#include <qglobal.h>
typedef struct _XDisplay Display;
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
typedef struct xcb_connection_t xcb_connection_t;
#endif
class X11Info {

    static Display *_display;
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    static xcb_connection_t *_xcb;
#endif
    static int _xcb_preferred_screen;
public:
    static Display* display();
    static unsigned long app_root_window(int screen = -1);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    static xcb_connection_t* xcb_connection();
    static inline int xcb_preferred_screen() { return _xcb_preferred_screen; }
#endif
};
#endif // X11INFO_H
