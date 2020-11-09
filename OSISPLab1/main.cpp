#include <windows.h>
#include <windowsx.h>
#include <string>

#pragma comment (lib,"Gdiplus.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int CALLBACK wWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,//dont used
  
    PWSTR szCmdLine,
                     int       nCmdShow)
{
    HWND hwnd{};
  
    MSG msg{};
    //
    WNDCLASSEX wc{};
  
     wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"MyPaintClass";
    RegisterClassEx(&wc);
    
         hwnd = CreateWindow(wc.lpszClassName, L"MiniPaint",
        WS_OVERLAPPEDWINDOW, 0, 10,
        1400,800, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return static_cast<int> (msg.wParam);
}


BOOL Line(HDC hdc, int x1, int y1, int x2, int y2)
{
    MoveToEx(hdc, x1, y1, NULL); //сделать текущими координаты x1, y1
    return LineTo(hdc, x2, y2);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT messg, WPARAM wParam,
    LPARAM lParam)
{
    HDC hdc;//   храним дискриптор
    LOGFONT lf;//для текста 
    HFONT hFont;
    RECT r;
   


    static COLORREF color = RGB(0, 0, 0);
    static bool isDraw = false;
    static int X1 = 0, Y1 = 0, X2 = 0, Y2 = 0;
    static int shape = 0, line = 1, curveCount = 0, polyCount = 0;
    static POINT curveLine[256];
    static POINT poly[256];
    static wchar_t text[256];
    static HWND hEdit;
    
    switch (messg)
    {
    case WM_CREATE:
    {
        HWND hButtonGreen = CreateWindow(
            L"BUTTON",
            L"Green",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            0, 0, 100, 50, hwnd, (HMENU)0, nullptr, nullptr
        );
        HWND hButtonBlack = CreateWindow(
            L"BUTTON",
            L"Black",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            100, 0, 100, 50, hwnd, (HMENU)1, nullptr, nullptr
        );
        HWND hButtonRed = CreateWindow(
            L"BUTTON",
            L"Red",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            200, 0, 100, 50, hwnd, (HMENU)2, nullptr, nullptr
        );
        HWND hButtonYellow = CreateWindow(
            L"BUTTON",
            L"Yellow",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            300, 0, 100, 50, hwnd, (HMENU)3, nullptr, nullptr
        );
        HWND hButtonBlue = CreateWindow(
            L"BUTTON",
            L"Blue",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            400, 0, 100, 50, hwnd, (HMENU)4, nullptr, nullptr
        );
        HWND hButtonLine = CreateWindow(
            L"BUTTON",
            L"Line",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            0, 50, 100, 50, hwnd, (HMENU)5, nullptr, nullptr
        );
        HWND hButtonRect = CreateWindow(
            L"BUTTON",
            L"Rectangle",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            0, 100, 100, 50, hwnd, (HMENU)6, nullptr, nullptr
        );
        HWND hLineSizeS = CreateWindow(
            L"Button",
            L"Small",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            200, 50, 100, 50, hwnd, (HMENU)7, nullptr, nullptr
        );
        HWND hLineSizeM = CreateWindow(
            L"Button",
            L"Medium",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            300, 50, 100, 50, hwnd, (HMENU)8, nullptr, nullptr
        );
        HWND hLineSizeL = CreateWindow(
            L"Button",
            L"Large",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            400, 50, 100, 50, hwnd, (HMENU)9, nullptr, nullptr
        );
        HWND hButtonCurve = CreateWindow(
            L"BUTTON",
            L"Curve",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            100, 50, 100, 50, hwnd, (HMENU)10, nullptr, nullptr
        );
        HWND hButtonPolygon = CreateWindow(
            L"BUTTON",
            L"Polygon",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            100, 100, 100, 50, hwnd, (HMENU)11, nullptr, nullptr
        );
        HWND hButtonElipse = CreateWindow(
            L"BUTTON",
            L"Elipse",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            200, 100, 100, 50, hwnd, (HMENU)12, nullptr, nullptr
        );
        HWND hButtonText = CreateWindow(
            L"BUTTON",
            L"Text",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            300, 100, 100, 50, hwnd, (HMENU)13, nullptr, nullptr
        );
        hEdit = CreateWindow(
            L"EDIT",
            L"Text",
            WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
            400, 100, 100, 50, hwnd, (HMENU)14, nullptr, nullptr
        );
    }
    return 0;
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case 0:
        {
            color = RGB(55, 255, 0);
        }
        break;
        case 1:
        {
            color = RGB(0, 0, 0);
        }
        break;
        case 2:
        {
            color = RGB(255, 0, 55); 
        }
        break;
        case 3:
        {
            color = RGB(255, 255, 0);
        }
        break;
        case 4:
        {
            color = RGB(55, 0, 255);
        }
        break;
        case 5:
        {
            shape = 0;
        }
        break;
        case 6:
        {
            //прямоугольник
            shape = 1;
        }
        break;
        case 7:
        {
            line = 1;
        }
        break;
        case 8:
        {
            line = 5;
        }
        break;
        case 9:
        {
            line = 10;
        }
        break;
        case 10:
        {
            shape = 2;
            memset(curveLine, 0, sizeof(POINT) * 256);
            curveCount = 0;
        }
        break;
        case 11:
        {
            shape = 3;
            memset(poly, 0, sizeof(POINT) * 256);
            polyCount = 0;
        }
        break;
        case 12:
        {
            //Элипс
            shape = 4;
        }
        break;
        case 13:
        {
            //Текст
            shape = 5;
        }
        break;

        default:
            break;
        }
    }
    return 0;
    
    case WM_LBUTTONDOWN:
    {   // дескриптор устройства, окна в котором 
        hdc = GetDC(hwnd);
        X1 = GET_X_LPARAM(lParam);
        Y1 = GET_Y_LPARAM(lParam);
        X2 = GET_X_LPARAM(lParam);
        Y2 = GET_Y_LPARAM(lParam);
        isDraw = true;

        if (shape == 2)
        {
            if (curveCount > 255)
            {
                curveCount--;
            }
            curveLine[curveCount].x = GET_X_LPARAM(lParam);
            curveLine[curveCount].y = GET_Y_LPARAM(lParam);
            curveCount++;
            HPEN hPen2 = CreatePen(PS_SOLID, line, color);
            SelectObject(hdc, hPen2);
            if (curveCount > 1)
            {
                Line(hdc, curveLine[curveCount-2].x, curveLine[curveCount-2].y, curveLine[curveCount - 1].x, curveLine[curveCount - 1].y);
            }
          
            DeleteObject(hPen2);
        }
        if (shape == 3)
        {
            if (polyCount > 255)
            {
                polyCount--;
            }
            poly[polyCount].x = GET_X_LPARAM(lParam);
            poly[polyCount].y = GET_Y_LPARAM(lParam);
            polyCount++;
            
            HBRUSH hBrush = CreateSolidBrush(color);
            SelectObject(hdc, hBrush);
           
            Polygon(hdc, poly, polyCount);
            DeleteObject(hBrush);
        }
    }
    break;
    case WM_LBUTTONUP:
    {
        isDraw = false;
        HDC hdc = GetDC(hwnd);
        switch (shape)
        {
        case 0:
        {
            HPEN hPen2 = CreatePen(PS_SOLID, line, color);
            SelectObject(hdc, hPen2);

            Line(hdc, X1, Y1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

            DeleteObject(hPen2);
        }
        break;
        }
    }
    break;
    case WM_MOUSEMOVE:
    {
        HDC hdc = GetDC(hwnd);
        if (isDraw)
        {
            switch (shape)
            {
            //Rectangle
            case 1:
            {
                r.top = Y1;
                r.left = X1;
                r.right = X2;
                r.bottom = Y2;
                HBRUSH hBrush1 = CreateSolidBrush(RGB(255, 255, 255));
                FillRect(hdc, &r, hBrush1);
                DeleteObject(hBrush1);

                X2 = GET_X_LPARAM(lParam);
                Y2 = GET_Y_LPARAM(lParam);

              
                r.right = X2;
                r.bottom = Y2;
                HBRUSH hBrush2 = CreateSolidBrush(color);
                FillRect(hdc, &r, hBrush2);
                DeleteObject(hBrush2);
            }
            break;
            case 4:
            {
                HPEN hPen2 = CreatePen(PS_NULL, line, RGB(255, 255, 255));
                SelectObject(hdc, hPen2);
                Ellipse(hdc, X1, Y1, X2, Y2);
                DeleteObject(hPen2);

                X2 = GET_X_LPARAM(lParam);
                Y2 = GET_Y_LPARAM(lParam);

                HBRUSH hBrush2 = CreateSolidBrush(color);
                SelectObject(hdc, hBrush2);
                Ellipse(hdc, X1, Y1, X2, Y2);
                DeleteObject(hBrush2);
            }
            break;
            case 5:
            {
                wcscpy_s(lf.lfFaceName, L"Times New Roman");
                X2 = GET_X_LPARAM(lParam);
                Y2 = GET_Y_LPARAM(lParam);
                lf.lfHeight = -MulDiv(Y2 - Y1, GetDeviceCaps(hdc, LOGPIXELSY), 72);// Y2 - Y1;
                lf.lfStrikeOut = 0;
                lf.lfUnderline = 0;
                lf.lfWidth = X1 - X2;
                lf.lfWeight = 0;
                lf.lfCharSet = DEFAULT_CHARSET;
                lf.lfPitchAndFamily = DEFAULT_PITCH;
                lf.lfEscapement = 0;

                hFont = CreateFontIndirect(&lf);

                SelectObject(hdc, hFont);
                SetTextColor(hdc, color);
                int textLen = GetWindowTextLengthA(hEdit) + 1;
                TCHAR buff[1024];
                GetWindowText(hEdit, buff, textLen);
                TextOut(hdc, X1, Y1, buff, textLen);
            }
            break;
            default:
                break;
            }

        }

    }
    break;
    case WM_DESTROY:
    {
        PostQuitMessage(EXIT_SUCCESS);
    }
    return 0;


    default:
    {
        return(DefWindowProc(hwnd, messg, wParam, lParam));
    }
    }
    return 0;
}