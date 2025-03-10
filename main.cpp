#include <windows.h>

enum { id_button1 = 1, id_button2 };

HBRUSH cyanBrush = nullptr;

void on_create(HWND hw)
{
    CreateWindowW(L"BUTTON", L"Button 1", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10, 10, 100, 25, hw, (HMENU)id_button1, NULL, NULL);

    CreateWindowW(L"BUTTON", L"Button 2", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10, 40, 100, 25, hw, (HMENU)id_button2, NULL, NULL);
}

void on_command(HWND hw, int id)
{
    switch (id) {
    case id_button1:
        MessageBoxW(hw, L"Button 1 was pressed!", L"Warning", MB_OK | MB_ICONWARNING);
        break;
    case id_button2:
        MessageBoxW(hw, L"Button 2 was pressed!", L"Warning", MB_OK | MB_ICONWARNING);
        break;
    }
}

void on_destroy()
{
    if (cyanBrush) {
        DeleteObject(cyanBrush);
    }
    PostQuitMessage(0);
}

LRESULT CALLBACK window_proc(HWND hw, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_CREATE:
        on_create(hw);
        return 0;
    case WM_COMMAND:
        on_command(hw, LOWORD(wp));
        return 0;
    case WM_DESTROY:
        on_destroy();
        return 0;
    }
    return DefWindowProc(hw, msg, wp, lp);
}

int register_class(HINSTANCE hi, const wchar_t* name)
{
    WNDCLASSW wc{};
    wc.lpfnWndProc = window_proc;
    wc.lpszClassName = name;
    wc.hInstance = hi;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    cyanBrush = CreateSolidBrush(RGB(0, 255, 255));
    wc.hbrBackground = cyanBrush;
    return RegisterClassW(&wc);
}

int WINAPI wWinMain(HINSTANCE hi, HINSTANCE, LPWSTR, int show_flag)
{
    const auto class_name = L"NWPClass";
    if (!register_class(hi, class_name))
        return 0;

    CreateWindowW(class_name, L"NWP 1", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hi, 0);

    MSG msg;
    while (GetMessage(&msg, 0, 0, 0))
        DispatchMessage(&msg);
    return msg.wParam;
}
