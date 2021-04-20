#include <windows.h>
#include <math.h>

#define M_PI 3.14159265358979323846
#define n 12

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char ProgName[] = "Yevgen Yakovliev - Third Lab";

void arrow(int px, int py, int dx, int dy, HDC hdc) {
    int lx, ly = py, rx = px, ry;
    if (dx == 0) {
        ly = py + (15 * dy / abs(dy));
        ry = ly;
        lx = px - 15;
        rx = px + 15;
    } else if (dy == 0) {
        ly = py - 15;
        ry = py + 15;
        lx = px + (15 * dx / abs(dx));
        rx = lx;
    }
    else {
        lx = px + (dx / abs(dx)) * 15;
        ry = py + (dy / abs(dy)) * 15;
    }

    MoveToEx(hdc, lx, ly, NULL);
    LineTo(hdc, px, py);
    LineTo(hdc, rx, ry);
}

void generateNodes(int centerX, int centerY, int dx, int dy, int dtx, int nx[], int ny[], HDC hdc, HPEN pen, int text[]) {
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            nx[i] = centerX;
            ny[i] = centerY;
        }
        else {
            nx[i] = nx[0] + 192 * cos(2 * i * M_PI / (n - 1));
            ny[i] = ny[0] + 192 * sin(2 * i * M_PI / (n - 1));
        }
    }
}

void drawNodes(int dx, int dy, int dtx, int nx[], int ny[], HDC hdc, HPEN pen, int text[]) {
    for (int i = 0; i < n; i++) {
        SelectObject(hdc, pen);
        Ellipse(hdc, nx[i] - dx, ny[i] - dy, nx[i] + dx, ny[i] + dy);
        TextOut(hdc, nx[i] - dtx, ny[i] - dy / 2, text[i], 2);
    }
}

void paintLine(int matrix[n][n], HDC hdc, int dx, int dy, int nx[], int ny[], int draw_arrows) {
    int  radius = 16, divine = 1, xDif, yDif;
    float koef = 1.0 - 0 * 0.02 - 3 * 0.005 - 0.25;
    for (int start = 0; start < n; start++) {
        for (int end = 0; end < n; end++) {
            if (matrix[start][end] == 1) {
                xDif = nx[start] - nx[end];
                yDif = ny[start] - ny[end];
                koef = sqrt(xDif * xDif + yDif * yDif) / radius;
                dx = xDif / koef;
                dy = yDif / koef;
                if (start == end) {
                    MoveToEx(hdc, nx[end], ny[end], NULL);
                    LineTo(hdc, nx[end] + 40, ny[end] + 10);
                    LineTo(hdc, nx[end] + 40, ny[end] + 40);
                    LineTo(hdc, nx[end] + 10, ny[end] + 40);
                    LineTo(hdc, nx[end], ny[end]);
                    if (draw_arrows) arrow(nx[end] + 2, ny[end] + 13, 2, 13, hdc);
                }
                else if (matrix[start][end] == 1 && matrix[end][start] == 1) {
                    MoveToEx(hdc, nx[start], ny[start], NULL);
                    LineTo(hdc, nx[end] + xDif / 2 + (20 * divine), ny[end] + yDif / 2 + (20 * divine));
                    LineTo(hdc, nx[end], ny[end]);
                    if (draw_arrows)arrow(nx[end] + dx, ny[end] + dy, dx, dy, hdc);
                    divine = -divine;
                }
                else {
                    MoveToEx(hdc, nx[start], ny[start], NULL);
                    if (yDif == 0 && abs(xDif) > 300 && end <= 3) {
                        LineTo(hdc, nx[end] + xDif / 2, ny[end] - 35);
                        dx = xDif / 2 / koef;
                        dy = (yDif - 35) / koef;
                    }
                    else if (abs(xDif) == 300 && abs(yDif) == 300 && (end == 0 || end == 3)) {
                        LineTo(hdc, nx[end] + xDif / 2, ny[end] + yDif / 1);
                        dx = xDif / 2 / koef;
                        dy = yDif / koef;
                    }
                    LineTo(hdc, nx[end], ny[end]);
                    if (draw_arrows) arrow(nx[end] + dx, ny[end] + dy, dx, dy, hdc);
                }
            }
        }
    }
}

int matrix[n][n] = {
    { 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
    { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
    { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0 },
    { 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
    { 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0 },
    { 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
    { 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 }
};

int symmetricMatrix[n][n] = {
    { 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
    { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
    { 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0 },
    { 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 },
    { 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0 },
    { 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1 },
    { 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0 },
    { 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
    { 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0 }
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w;

    w.lpszClassName = ProgName;
    w.hInstance = hInstance;
    w.lpfnWndProc = WndProc;
    w.hCursor = LoadCursor(NULL, IDC_ARROW);
    w.hIcon = 0;
    w.lpszMenuName = 0;
    w.hbrBackground = LTGRAY_BRUSH;
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if (!RegisterClass(&w))
        return 0;

    hWnd = CreateWindow(ProgName,
        "Yevgen Yakovliev - Third Lab",
        WS_OVERLAPPEDWINDOW,
        100,
        100,
        1024,
        512,
        (HWND)NULL,
        (HMENU)NULL,
        (HINSTANCE)hInstance,
        (HINSTANCE)NULL);

    ShowWindow(hWnd, nCmdShow);

    while (GetMessage(&lpMsg, hWnd, 0, 0)) {
        TranslateMessage(&lpMsg);
        DispatchMessage(&lpMsg);
    }
    return(lpMsg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    switch (messg) {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            char* nn[n] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12" };
            int nx[n + 1], ny[n + 1];
            int nx2[n + 1], ny2[n + 1];
            int dx = 16, dy = 16, dtx = 5;

            HPEN BluePen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
            HPEN BlackPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

            // Drawing first matrix
            generateNodes(250, 250, dx, dy, dtx, nx, ny, hdc, BlackPen, nn);

            paintLine(matrix, hdc, dx, dy, nx, ny, 1);

            drawNodes(dx, dy, dtx, nx, ny, hdc, BlackPen, nn);

            // Drawing second matrix
            generateNodes(750, 250, dx, dy, dtx, nx2, ny2, hdc, BlackPen, nn);

            paintLine(symmetricMatrix, hdc, dx, dy, nx2, ny2, 0);

            drawNodes(dx, dy, dtx, nx2, ny2, hdc, BlackPen, nn);

            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return 0;
}