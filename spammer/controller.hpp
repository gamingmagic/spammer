#ifndef CONTROLLER_H
#define CONTROLLER_H

#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <iostream>
#include <shellapi.h>
#include <winuser.h>

enum KeyBoard
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ENTER,
    ESC
};

enum Mouse
{
    RIGHT_CLICK,
    LEFT_CLICK,
    D_ClICK
};

enum Volume
{
    VOL_UP,
    VOL_DOWN
};

enum Browse
{
    FORWARD,
    BACKWARD
};

class Controller
{
    public:
        Controller();
        bool keyboardKeyPress(KeyBoard key);
        bool mouseClick(Mouse click);
        bool volumeControl(Volume signal);
        bool browseControl(Browse dir);
        void moveCursor(int dx, int dy);
        void getCursorPosition(int &x, int &y);
        void GetDesktopResolution(int& horizontal, int& vertical);
        void setCursorPosition(int x, int y);

    private:
        INPUT kinput;

        void rightClick();
        void leftClick();
        void doubleClick();

};

#endif // CONTROLLER_H