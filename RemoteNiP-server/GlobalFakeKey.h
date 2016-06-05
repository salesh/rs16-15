#ifndef GLOBALFAKEKEY_H
#define GLOBALFAKEKEY_H

#include<QObject>
#include<QKeySequence>
#include<QTime>
#include <QDebug>
#include <X11/keysym.h>
#include <X11/XF86keysym.h>
#include <X11/keysymdef.h>
#include <X11/Xmd.h>
#include <X11/extensions/XTest.h>
#include "x11info.h"

//Since we dont have package we need to install it x11/etc
//sudo apt-get install x11proto-core-dev
//sudo apt-get install libxtst-dev
//sudo apt-get install libx11-dev




//The most platforms support this kind of defines, thats why is Ifndef, in the case they dont


#ifndef XK_ISO_Left_Tab
#define XK_ISO_Left_Tab 0xFE20
#endif
#ifndef XK_dead_hook
#define XK_dead_hook 0xFE61
#endif
#ifndef XK_dead_horn
#define XK_dead_horn 0xFE62
#endif
#ifndef XK_Codeinput
#define XK_Codeinput 0xFF37
#endif
#ifndef XK_Kanji_Bangou
#define XK_Kanji_Bangou 0xFF37 /* same as codeinput */
#endif
// Fix old X libraries
#ifndef XK_KP_Home
#define XK_KP_Home 0xFF95
#endif
#ifndef XK_KP_Left
#define XK_KP_Left 0xFF96
#endif
#ifndef XK_KP_Up
#define XK_KP_Up 0xFF97
#endif
#ifndef XK_KP_Right
#define XK_KP_Right 0xFF98
#endif
#ifndef XK_KP_Down
#define XK_KP_Down 0xFF99
#endif
#ifndef XK_KP_Prior
#define XK_KP_Prior 0xFF9A
#endif
#ifndef XK_KP_Next
#define XK_KP_Next 0xFF9B
#endif
#ifndef XK_KP_End
#define XK_KP_End 0xFF9C
#endif
#ifndef XK_KP_Insert
#define XK_KP_Insert 0xFF9E
#endif
#ifndef XK_KP_Delete
#define XK_KP_Delete 0xFF9F
#endif


//Not common defines thats why we skip ifndef part and define them eitherway

#define XF86XK_ModeLock		0x1008FF01	/* Mode Switch Lock */

/* Backlight controls. */
#define XF86XK_MonBrightnessUp   0x1008FF02  /* Monitor/panel brightness */
#define XF86XK_MonBrightnessDown 0x1008FF03  /* Monitor/panel brightness */
#define XF86XK_KbdLightOnOff     0x1008FF04  /* Keyboards may be lit     */
#define XF86XK_KbdBrightnessUp   0x1008FF05  /* Keyboards may be lit     */
#define XF86XK_KbdBrightnessDown 0x1008FF06  /* Keyboards may be lit     */

/*
 * Keys found on some "Internet" keyboards.
 */
#define XF86XK_Standby		0x1008FF10   /* System into standby mode   */
#define XF86XK_AudioLowerVolume	0x1008FF11   /* Volume control down        */
#define XF86XK_AudioMute	0x1008FF12   /* Mute sound from the system */
#define XF86XK_AudioRaiseVolume	0x1008FF13   /* Volume control up          */
#define XF86XK_AudioPlay	0x1008FF14   /* Start playing of audio >   */
#define XF86XK_AudioStop	0x1008FF15   /* Stop playing audio         */
#define XF86XK_AudioPrev	0x1008FF16   /* Previous track             */
#define XF86XK_AudioNext	0x1008FF17   /* Next track                 */
#define XF86XK_HomePage		0x1008FF18   /* Display user's home page   */
#define XF86XK_Mail		0x1008FF19   /* Invoke user's mail program */
#define XF86XK_Start		0x1008FF1A   /* Start application          */
#define XF86XK_Search		0x1008FF1B   /* Search                     */
#define XF86XK_AudioRecord	0x1008FF1C   /* Record audio application   */

/* These are sometimes found on PDA's (e.g. Palm, PocketPC or elsewhere)   */
#define XF86XK_Calculator	0x1008FF1D   /* Invoke calculator program  */
#define XF86XK_Memo		0x1008FF1E   /* Invoke Memo taking program */
#define XF86XK_ToDoList		0x1008FF1F   /* Invoke To Do List program  */
#define XF86XK_Calendar		0x1008FF20   /* Invoke Calendar program    */
#define XF86XK_PowerDown	0x1008FF21   /* Deep sleep the system      */
#define XF86XK_ContrastAdjust	0x1008FF22   /* Adjust screen contrast     */
#define XF86XK_RockerUp		0x1008FF23   /* Rocker switches exist up   */
#define XF86XK_RockerDown	0x1008FF24   /* and down                   */
#define XF86XK_RockerEnter	0x1008FF25   /* and let you press them     */

/* Some more "Internet" keyboard symbols */
#define XF86XK_Back		0x1008FF26   /* Like back on a browser     */
#define XF86XK_Forward		0x1008FF27   /* Like forward on a browser  */
#define XF86XK_Stop		0x1008FF28   /* Stop current operation     */
#define XF86XK_Refresh		0x1008FF29   /* Refresh the page           */
#define XF86XK_PowerOff		0x1008FF2A   /* Power off system entirely  */
#define XF86XK_WakeUp		0x1008FF2B   /* Wake up system from sleep  */
#define XF86XK_Eject            0x1008FF2C   /* Eject device (e.g. DVD)    */
#define XF86XK_ScreenSaver      0x1008FF2D   /* Invoke screensaver         */
#define XF86XK_WWW              0x1008FF2E   /* Invoke web browser         */
#define XF86XK_Sleep            0x1008FF2F   /* Put system to sleep        */
#define XF86XK_Favorites	0x1008FF30   /* Show favorite locations    */
#define XF86XK_AudioPause	0x1008FF31   /* Pause audio playing        */
#define XF86XK_AudioMedia	0x1008FF32   /* Launch media collection app */
#define XF86XK_MyComputer	0x1008FF33   /* Display "My Computer" window */
#define XF86XK_VendorHome	0x1008FF34   /* Display vendor home web site */
#define XF86XK_LightBulb	0x1008FF35   /* Light bulb keys exist       */
#define XF86XK_Shop		0x1008FF36   /* Display shopping web site   */
#define XF86XK_History		0x1008FF37   /* Show history of web surfing */
#define XF86XK_OpenURL		0x1008FF38   /* Open selected URL           */
#define XF86XK_AddFavorite	0x1008FF39   /* Add URL to favorites list   */
#define XF86XK_HotLinks		0x1008FF3A   /* Show "hot" links            */
#define XF86XK_BrightnessAdjust	0x1008FF3B   /* Invoke brightness adj. UI   */
#define XF86XK_Finance		0x1008FF3C   /* Display financial site      */
#define XF86XK_Community	0x1008FF3D   /* Display user's community    */
#define XF86XK_AudioRewind	0x1008FF3E   /* "rewind" audio track        */
#define XF86XK_BackForward	0x1008FF3F   /* ??? */
#define XF86XK_Launch0		0x1008FF40   /* Launch Application          */
#define XF86XK_Launch1		0x1008FF41   /* Launch Application          */
#define XF86XK_Launch2		0x1008FF42   /* Launch Application          */
#define XF86XK_Launch3		0x1008FF43   /* Launch Application          */
#define XF86XK_Launch4		0x1008FF44   /* Launch Application          */
#define XF86XK_Launch5		0x1008FF45   /* Launch Application          */
#define XF86XK_Launch6		0x1008FF46   /* Launch Application          */
#define XF86XK_Launch7		0x1008FF47   /* Launch Application          */
#define XF86XK_Launch8		0x1008FF48   /* Launch Application          */
#define XF86XK_Launch9		0x1008FF49   /* Launch Application          */
#define XF86XK_LaunchA		0x1008FF4A   /* Launch Application          */
#define XF86XK_LaunchB		0x1008FF4B   /* Launch Application          */
#define XF86XK_LaunchC		0x1008FF4C   /* Launch Application          */
#define XF86XK_LaunchD		0x1008FF4D   /* Launch Application          */
#define XF86XK_LaunchE		0x1008FF4E   /* Launch Application          */
#define XF86XK_LaunchF		0x1008FF4F   /* Launch Application          */

#define XF86XK_ApplicationLeft	0x1008FF50   /* switch to application, left */
#define XF86XK_ApplicationRight	0x1008FF51   /* switch to application, right*/
#define XF86XK_Book		0x1008FF52   /* Launch bookreader           */
#define XF86XK_CD		0x1008FF53   /* Launch CD/DVD player        */
#define XF86XK_Calculater	0x1008FF54   /* Launch Calculater           */
#define XF86XK_Clear		0x1008FF55   /* Clear window, screen        */
#define XF86XK_Close		0x1008FF56   /* Close window                */
#define XF86XK_Copy		0x1008FF57   /* Copy selection              */
#define XF86XK_Cut		0x1008FF58   /* Cut selection               */
#define XF86XK_Display		0x1008FF59   /* Output switch key           */
#define XF86XK_DOS		0x1008FF5A   /* Launch DOS (emulation)      */
#define XF86XK_Documents	0x1008FF5B   /* Open documents window       */
#define XF86XK_Excel		0x1008FF5C   /* Launch spread sheet         */
#define XF86XK_Explorer		0x1008FF5D   /* Launch file explorer        */
#define XF86XK_Game		0x1008FF5E   /* Launch game                 */
#define XF86XK_Go		0x1008FF5F   /* Go to URL                   */
#define XF86XK_iTouch		0x1008FF60   /* Logitch iTouch- don't use   */
#define XF86XK_LogOff		0x1008FF61   /* Log off system              */
#define XF86XK_Market		0x1008FF62   /* ??                          */
#define XF86XK_Meeting		0x1008FF63   /* enter meeting in calendar   */
#define XF86XK_MenuKB		0x1008FF65   /* distingush keyboard from PB */
#define XF86XK_MenuPB		0x1008FF66   /* distinuish PB from keyboard */
#define XF86XK_MySites		0x1008FF67   /* Favourites                  */
#define XF86XK_New		0x1008FF68   /* New (folder, document...    */
#define XF86XK_News		0x1008FF69   /* News                        */
#define XF86XK_OfficeHome	0x1008FF6A   /* Office home (old Staroffice)*/
#define XF86XK_Open		0x1008FF6B   /* Open                        */
#define XF86XK_Option		0x1008FF6C   /* ?? */
#define XF86XK_Paste		0x1008FF6D   /* Paste                       */
#define XF86XK_Phone		0x1008FF6E   /* Launch phone; dial number   */
#define XF86XK_Q		0x1008FF70   /* Compaq's Q - don't use      */
#define XF86XK_Reply		0x1008FF72   /* Reply e.g., mail            */
#define XF86XK_Reload		0x1008FF73   /* Reload web page, file, etc. */
#define XF86XK_RotateWindows	0x1008FF74   /* Rotate windows e.g. xrandr  */
#define XF86XK_RotationPB	0x1008FF75   /* don't use                   */
#define XF86XK_RotationKB	0x1008FF76   /* don't use                   */
#define XF86XK_Save		0x1008FF77   /* Save (file, document, state */
#define XF86XK_ScrollUp		0x1008FF78   /* Scroll window/contents up   */
#define XF86XK_ScrollDown	0x1008FF79   /* Scrool window/contentd down */
#define XF86XK_ScrollClick	0x1008FF7A   /* Use XKB mousekeys instead   */
#define XF86XK_Send		0x1008FF7B   /* Send mail, file, object     */
#define XF86XK_Spell		0x1008FF7C   /* Spell checker               */
#define XF86XK_SplitScreen	0x1008FF7D   /* Split window or screen      */
#define XF86XK_Support		0x1008FF7E   /* Get support (??)            */
#define XF86XK_TaskPane		0x1008FF7F   /* Show tasks */
#define XF86XK_Terminal		0x1008FF80   /* Launch terminal emulator    */
#define XF86XK_Tools		0x1008FF81   /* toolbox of desktop/app.     */
#define XF86XK_Travel		0x1008FF82   /* ?? */
#define XF86XK_UserPB		0x1008FF84   /* ?? */
#define XF86XK_User1KB		0x1008FF85   /* ?? */
#define XF86XK_User2KB		0x1008FF86   /* ?? */
#define XF86XK_Video		0x1008FF87   /* Launch video player       */
#define XF86XK_WheelButton	0x1008FF88   /* button from a mouse wheel */
#define XF86XK_Word		0x1008FF89   /* Launch word processor     */
#define XF86XK_Xfer		0x1008FF8A
#define XF86XK_ZoomIn		0x1008FF8B   /* zoom in view, map, etc.   */
#define XF86XK_ZoomOut		0x1008FF8C   /* zoom out view, map, etc.  */

#define XF86XK_Away		0x1008FF8D   /* mark yourself as away     */
#define XF86XK_Messenger	0x1008FF8E   /* as in instant messaging   */
#define XF86XK_WebCam		0x1008FF8F   /* Launch web camera app.    */
#define XF86XK_MailForward	0x1008FF90   /* Forward in mail           */
#define XF86XK_Pictures		0x1008FF91   /* Show pictures             */
#define XF86XK_Music		0x1008FF92   /* Launch music application  */

#define XF86XK_Battery		0x1008FF93   /* Display battery information */
#define XF86XK_Bluetooth	0x1008FF94   /* Enable/disable Bluetooth    */
#define XF86XK_WLAN		0x1008FF95   /* Enable/disable WLAN         */
#define XF86XK_UWB		0x1008FF96   /* Enable/disable UWB	    */

#define XF86XK_AudioForward	0x1008FF97   /* fast-forward audio track    */
#define XF86XK_AudioRepeat	0x1008FF98   /* toggle repeat mode          */
#define XF86XK_AudioRandomPlay	0x1008FF99   /* toggle shuffle mode         */
#define XF86XK_Subtitle		0x1008FF9A   /* cycle through subtitle      */
#define XF86XK_AudioCycleTrack	0x1008FF9B   /* cycle through audio tracks  */
#define XF86XK_CycleAngle	0x1008FF9C   /* cycle through angles        */
#define XF86XK_FrameBack	0x1008FF9D   /* video: go one frame back    */
#define XF86XK_FrameForward	0x1008FF9E   /* video: go one frame forward */
#define XF86XK_Time		0x1008FF9F   /* display, or shows an entry for time seeking */
#define XF86XK_Select		0x1008FFA0   /* Select button on joypads and remotes */
#define XF86XK_View		0x1008FFA1   /* Show a view options/properties */
#define XF86XK_TopMenu		0x1008FFA2   /* Go to a top-level menu in a video */

#define XF86XK_Red		0x1008FFA3   /* Red button                  */
#define XF86XK_Green		0x1008FFA4   /* Green button                */
#define XF86XK_Yellow		0x1008FFA5   /* Yellow button               */
#define XF86XK_Blue             0x1008FFA6   /* Blue button                 */

#define XF86XK_Suspend		0x1008FFA7   /* Sleep to RAM                */
#define XF86XK_Hibernate	0x1008FFA8   /* Sleep to disk               */
#define XF86XK_TouchpadToggle	0x1008FFA9   /* Toggle between touchpad/trackstick */
#define XF86XK_TouchpadOn	0x1008FFB0   /* The touchpad got switched on */
#define XF86XK_TouchpadOff	0x1008FFB1   /* The touchpad got switched off */

#define XF86XK_AudioMicMute	0x1008FFB2   /* Mute the Mic from the system */

/* Keys for special action keys (hot keys) */
/* Virtual terminals on some operating systems */
#define XF86XK_Switch_VT_1	0x1008FE01
#define XF86XK_Switch_VT_2	0x1008FE02
#define XF86XK_Switch_VT_3	0x1008FE03
#define XF86XK_Switch_VT_4	0x1008FE04
#define XF86XK_Switch_VT_5	0x1008FE05
#define XF86XK_Switch_VT_6	0x1008FE06
#define XF86XK_Switch_VT_7	0x1008FE07
#define XF86XK_Switch_VT_8	0x1008FE08
#define XF86XK_Switch_VT_9	0x1008FE09
#define XF86XK_Switch_VT_10	0x1008FE0A
#define XF86XK_Switch_VT_11	0x1008FE0B
#define XF86XK_Switch_VT_12	0x1008FE0C

#define XF86XK_Ungrab		0x1008FE20   /* force ungrab               */
#define XF86XK_ClearGrab	0x1008FE21   /* kill application with grab */
#define XF86XK_Next_VMode	0x1008FE22   /* next video mode available  */
#define XF86XK_Prev_VMode	0x1008FE23   /* prev. video mode available */
#define XF86XK_LogWindowTree	0x1008FE24   /* print window tree to log   */
#define XF86XK_LogGrabInfo	0x1008FE25   /* print all active grabs to log */


//end for x86 common defines



//Qtopia defines (phones, projectors etc..)
#define QTOPIAXK_Select 0x11000601
#define QTOPIAXK_Yes 0x11000602
#define QTOPIAXK_No 0x11000603
#define QTOPIAXK_Cancel 0x11000604
#define QTOPIAXK_Printer 0x11000605
#define QTOPIAXK_Execute 0x11000606
#define QTOPIAXK_Sleep 0x11000607
#define QTOPIAXK_Play 0x11000608
#define QTOPIAXK_Zoom 0x11000609
#define QTOPIAXK_Context1 0x1100060A
#define QTOPIAXK_Context2 0x1100060B
#define QTOPIAXK_Context3 0x1100060C
#define QTOPIAXK_Context4 0x1100060D
#define QTOPIAXK_Call 0x1100060E
#define QTOPIAXK_Hangup 0x1100060F
#define QTOPIAXK_Flip 0x11000610

#define XK_Space 0x020



static const unsigned int KeyTbl[] ={
    XK_Space,                      Qt::Key_Space,
    XK_Escape,                    Qt::Key_Escape,
    XK_Tab,                        Qt::Key_Tab,
    XK_ISO_Left_Tab,               Qt::Key_Backtab,
    XK_BackSpace,                  Qt::Key_Backspace,
    XK_Return,                     Qt::Key_Return,
    XK_Insert,                     Qt::Key_Insert,
    XK_Delete,                     Qt::Key_Delete,
    XK_Clear,                      Qt::Key_Delete,
    XK_Pause,                      Qt::Key_Pause,
    XK_Print,                      Qt::Key_Print,
    0x1005FF60,                    Qt::Key_SysReq, // hardcoded Sun SysReq
    0x1007ff00,                    Qt::Key_SysReq, // hardcoded X386 SysReq

    // cursor movement
    XK_Home,                Qt::Key_Home,
    XK_End,                 Qt::Key_End,
    XK_Left,                Qt::Key_Left,
    XK_Up,                  Qt::Key_Up,
    XK_Right,               Qt::Key_Right,
    XK_Down,                Qt::Key_Down,
    XK_Prior,               Qt::Key_PageUp,
    XK_Next,                Qt::Key_PageDown,

    // modifiers
    XK_Shift_L,           Qt::Key_Shift,
    XK_Shift_R,           Qt::Key_Shift,
    XK_Shift_Lock,        Qt::Key_Shift,
    XK_Control_L,         Qt::Key_Control,
    XK_Control_R,         Qt::Key_Control,
    XK_Meta_L,            Qt::Key_Meta,
    XK_Meta_R,            Qt::Key_Meta,
    XK_Alt_L,             Qt::Key_Alt,
    XK_Alt_R,             Qt::Key_Alt,
    XK_Caps_Lock,         Qt::Key_CapsLock,
    XK_Num_Lock,          Qt::Key_NumLock,
    XK_Scroll_Lock,       Qt::Key_ScrollLock,
    XK_Super_L,           Qt::Key_Super_L,
    XK_Super_R,           Qt::Key_Super_R,
    XK_Menu,              Qt::Key_Menu,
    XK_Hyper_L,           Qt::Key_Hyper_L,
    XK_Hyper_R,           Qt::Key_Hyper_R,
    XK_Help,              Qt::Key_Help,
    0x1000FF74,           Qt::Key_Backtab, // hardcoded HP backtab
    0x1005FF10,           Qt::Key_F11, // hardcoded Sun F36 (labeled F11)
    0x1005FF11,           Qt::Key_F12, // hardcoded Sun F37 (labeled F12)


    //Function Keys
    XK_F1,       Qt::Key_F1,
    XK_F2,       Qt::Key_F2,
    XK_F3,       Qt::Key_F3,
    XK_F4,       Qt::Key_F4,
    XK_F5,       Qt::Key_F5,
    XK_F6,       Qt::Key_F6,
    XK_F7,       Qt::Key_F7,
    XK_F8,       Qt::Key_F8,
    XK_F9,       Qt::Key_F9,
    XK_F10,      Qt::Key_F10,
    XK_F11,      Qt::Key_F11,
    XK_F12,      Qt::Key_F12,
    XK_F13,      Qt::Key_F13,
    XK_F14,      Qt::Key_F14,
    XK_F15,      Qt::Key_F15,
    XK_F16,      Qt::Key_F16,
    XK_F17,      Qt::Key_F17,
    XK_F18,      Qt::Key_F18,
    XK_F19,      Qt::Key_F19,
    XK_F20,      Qt::Key_F20,

    // numeric and function keypad keys
    //XK_KP_Space, Qt::Key_Space,
    //XK_KP_Tab, Qt::Key_Tab,
    //XK_KP_Enter, Qt::Key_Enter,
    //XK_KP_F1, Qt::Key_F1,
    //XK_KP_F2, Qt::Key_F2,
    //XK_KP_F3, Qt::Key_F3,
    //XK_KP_F4, Qt::Key_F4,
    //XK_KP_Home, Qt::Key_Home,
    //XK_KP_Left, Qt::Key_Left,
    //XK_KP_Up, Qt::Key_Up,
    //XK_KP_Right, Qt::Key_Right,
    //XK_KP_Down, Qt::Key_Down,
    //XK_KP_Prior, Qt::Key_PageUp,
    //XK_KP_Next, Qt::Key_PageDown,
    //XK_KP_End, Qt::Key_End,
    //XK_KP_Begin, Qt::Key_Clear,
    //XK_KP_Insert, Qt::Key_Insert,
    //XK_KP_Delete, Qt::Key_Delete,
    //XK_KP_Equal, Qt::Key_Equal,
    //XK_KP_Multiply, Qt::Key_Asterisk,
    //XK_KP_Add, Qt::Key_Plus,
    //XK_KP_Separator, Qt::Key_Comma,
    //XK_KP_Subtract, Qt::Key_Minus,
    //XK_KP_Decimal, Qt::Key_Period,
    //XK_KP_Divide, Qt::Key_Slash,

    #if QT_VERSION >= 0x047000
    XF86XK_LaunchE, Qt::Key_LaunchG,
    XF86XK_LaunchF, Qt::Key_LaunchH,
    #endif


    // Qtopia keys
    QTOPIAXK_Select,       Qt::Key_Select,
    QTOPIAXK_Yes,          Qt::Key_Yes,
    QTOPIAXK_No,           Qt::Key_No,
    QTOPIAXK_Cancel,       Qt::Key_Cancel,
    QTOPIAXK_Printer,      Qt::Key_Printer,
    QTOPIAXK_Execute,      Qt::Key_Execute,
    QTOPIAXK_Sleep,        Qt::Key_Sleep,
    QTOPIAXK_Play,         Qt::Key_Play,
    QTOPIAXK_Zoom,         Qt::Key_Zoom,
    QTOPIAXK_Context1,     Qt::Key_Context1,
    QTOPIAXK_Context2,     Qt::Key_Context2,
    QTOPIAXK_Context3,     Qt::Key_Context3,
    QTOPIAXK_Context4,     Qt::Key_Context4,
    QTOPIAXK_Call,         Qt::Key_Call,
    QTOPIAXK_Hangup,       Qt::Key_Hangup,
    QTOPIAXK_Flip,         Qt::Key_Flip,
    0,                    0
};

class FakeKeyPrivate;

class GlobalFakeKey : public QObject{

    Q_OBJECT
public:
    explicit GlobalFakeKey(QObject * parent=0);
    virtual ~GlobalFakeKey();

    void sendKey(Qt::Key key, bool down);
    void sendModifiers(Qt::KeyboardModifier modifiers, bool down);
    void sendButton(Qt::MouseButton button, bool down);
    void sendScroll(int direction, int delta, double acceleration);


private:
    FakeKeyPrivate *_d;
    friend class FakeKeyPrivate;


    static Qt::KeyboardModifier const AllModifiers[4];

    static void wait(int const ms);
};



#endif // GLOBALFAKEKEY_H
