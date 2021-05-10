#include "Controller.h"
#include <algorithm>

Controller::Controller()
{
    // Set up a generic keyboard event.
    kinput.type = INPUT_KEYBOARD;
    kinput.ki.wScan = 0; // scan for key
    kinput.ki.time = 0;
    kinput.ki.dwExtraInfo = 0;
}

void Controller::rightClick()
{
    const double XSCALEFACTOR = 65535 / (GetSystemMetrics(SM_CXSCREEN) - 1);
    const double YSCALEFACTOR = 65535 / (GetSystemMetrics(SM_CYSCREEN) - 1);

    POINT cursorPos;
    GetCursorPos(&cursorPos);

    double cx = cursorPos.x * XSCALEFACTOR;
    double cy = cursorPos.y * YSCALEFACTOR;

    INPUT Input={0};
    Input.type = INPUT_MOUSE;

    Input.mi.dx = (LONG)cx;
    Input.mi.dy = (LONG)cy;

    //Click
    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP;
    SendInput(1,&Input,sizeof(INPUT));

    //Release
    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    SendInput(1,&Input,sizeof(INPUT));
}

void Controller::leftClick()
{
    const double XSCALEFACTOR = 65535 / (GetSystemMetrics(SM_CXSCREEN) - 1);
    const double YSCALEFACTOR = 65535 / (GetSystemMetrics(SM_CYSCREEN) - 1);

    POINT cursorPos;
    GetCursorPos(&cursorPos);

    double cx = cursorPos.x * XSCALEFACTOR;
    double cy = cursorPos.y * YSCALEFACTOR;

    INPUT Input={0};
    Input.type = INPUT_MOUSE;

    Input.mi.dx = (LONG)cx;
    Input.mi.dy = (LONG)cy;

    //Click
    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
    SendInput(1,&Input,sizeof(INPUT));

    //Release
    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    SendInput(1,&Input,sizeof(INPUT));
}

void Controller::doubleClick()
{
    const double XSCALEFACTOR = 65535 / (GetSystemMetrics(SM_CXSCREEN) - 1);
    const double YSCALEFACTOR = 65535 / (GetSystemMetrics(SM_CYSCREEN) - 1);

    POINT cursorPos;
    GetCursorPos(&cursorPos);

    double cx = cursorPos.x * XSCALEFACTOR;
    double cy = cursorPos.y * YSCALEFACTOR;

    INPUT Input={0};
    Input.type = INPUT_MOUSE;

    Input.mi.dx = (LONG)cx;
    Input.mi.dy = (LONG)cy;

    // Click
    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;

    SendInput(1,&Input,sizeof(INPUT));
    SendInput(1,&Input,sizeof(INPUT));

    //Release
    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    SendInput(1,&Input,sizeof(INPUT));
}

bool Controller::keyboardKeyPress(KeyBoard key)
{
    bool OKFlag = true;
    kinput.type = INPUT_KEYBOARD;
    switch(key)
    {
        case KeyBoard::UP:
            kinput.ki.wVk = 0x26;
            break;
        case KeyBoard::DOWN:
            kinput.ki.wVk = 0x28;
            break;
        case KeyBoard::LEFT:
            kinput.ki.wVk = 0x25;
            break;
        case KeyBoard::RIGHT:
            kinput.ki.wVk = 0x27;
            break;
        case KeyBoard::ENTER:
            kinput.ki.wVk = 0x0d;
            break;
        case KeyBoard::ESC:
            kinput.ki.wVk = 0x1b;
            break;
        default:
            OKFlag = false;

    }
    if(!OKFlag)
        return false;

    kinput.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &kinput, sizeof(INPUT));

    // Release the key
    kinput.ki.dwFlags = KEYEVENTF_KEYUP; // event for key up
    SendInput(1, &kinput, sizeof(INPUT));

    return true;
}

bool Controller::mouseClick(Mouse click)
{
    bool OKFlag = true;
    kinput.type = INPUT_MOUSE;

    switch(click)
    {
        case Mouse::LEFT_CLICK:
            leftClick();
            break;
        case Mouse::RIGHT_CLICK:
            rightClick();
            break;
        case Mouse::D_ClICK:
            doubleClick();
            break;
        default:
            OKFlag = false;
    }
    if(!OKFlag)
        return false;

    return true;
}

bool Controller::volumeControl(Volume signal)
{
    bool OKFlag = true;
    switch(signal)
    {
        case Volume::VOL_UP:
            kinput.ki.wVk = 0xaf;
            break;
        case Volume::VOL_DOWN:
            kinput.ki.wVk = 0xae;
            break;
        default:
            OKFlag = false;
    }
    if(!OKFlag)
        return false;

    kinput.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &kinput, sizeof(INPUT));

    // Release the key
    kinput.ki.dwFlags = KEYEVENTF_KEYUP; // event for key up
    SendInput(1, &kinput, sizeof(INPUT));
    return true;
}

bool Controller::browseControl(Browse dir)
{
    bool OKFlag = true;

    switch(dir)
    {
    case Browse::FORWARD:
        kinput.ki.wVk = 0xa7;
        break;
    case Browse::BACKWARD:
        kinput.ki.wVk = 0xa6;
        break;
    default:
        OKFlag = false;
    }

    if(!OKFlag)
        return false;

    kinput.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &kinput, sizeof(INPUT));

    // Release the key
    kinput.ki.dwFlags = KEYEVENTF_KEYUP; // event for key up
    SendInput(1, &kinput, sizeof(INPUT));
    return true;
}

void Controller::getCursorPosition(int &x, int &y)
{
    POINT cursorPos;
    GetCursorPos(&cursorPos);

    x = (int)cursorPos.x;
    y = (int)cursorPos.y;
}

void Controller::moveCursor(int dx, int dy)
{
    int curX, curY;
    int row, col;

    GetDesktopResolution(col, row);
    getCursorPosition(curX, curY);

    curX += dx;
    curY += dy;

    curX = std::min(curX, col);
    curX = std::max(curX, 0);

    curY = std::min(curY, row);
    curY = std::max(curY, 0);

    SetCursorPos(curX, curY);
}

void Controller::setCursorPosition(int x, int y)
{
    SetCursorPos(x, y);
}

void Controller::GetDesktopResolution(int& horizontal, int& vertical)
{
   RECT desktop;
   // Get a handle to the desktop window
   const HWND hDesktop = GetDesktopWindow();
   // Get the size of screen to the variable desktop
   GetWindowRect(hDesktop, &desktop);

   horizontal = desktop.right;
   vertical = desktop.bottom;
}