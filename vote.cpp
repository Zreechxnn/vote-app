#include "framework.h"
#include "vote.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <iostream>
#include <Windows.h>

#define MAX_LOADSTRING 100

// Resource ID
#define IDC_EDIT_NIK        101
#define IDC_EDIT_PASSWORD   102
#define ID_LOGIN            103
#define IDM_ABOUT           104
#define IDM_EXIT            105
#define ID_VOTE_SUBMIT      106
#define IDC_EDIT_ADMIN      110
#define ID_ADMIN            200
#define ID_ADMIN_TAMBAH     201

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

// Struktur data calon pemimpin
struct Calon {
    std::wstring nama;
    std::wstring deskripsi;
    std::wstring photoPath;  // Path to the candidate's photo
};

// Variabel global
std::vector<Calon> daftarCalon;
std::wstring currentUserNIK;
HWND hEditNIK, hEditPassword, hVoteSubmit;
std::vector<HWND> hRadioButtons; // Tombol radio untuk voting
bool isLoggedIn = false;
bool isAdmin = false;

// Prototipe fungsi
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void LoadDataCalon();
bool VerifyLogin(const std::wstring& nik, const std::wstring& password);
void DisplayVoteUI(HWND hWnd);
void SaveVote(int pilihan);
void DisplayAdminUI(HWND hWnd);
void SaveDataAdmin(const std::wstring& adminName);
bool VerifyAdmin(const std::wstring& adminName);
void LoadImageFromFile(HWND hWnd, const std::wstring& imagePath, int x, int y, int width, int height);

// Fungsi Utama
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_VOTE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    LoadDataCalon(); // Load data calon dari file

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VOTE));
    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex = { 0 };
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VOTE));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_VOTE);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hEditAdmin;

    switch (message)
    {
    case WM_CREATE:
        // Input NIK
        hEditNIK = CreateWindowW(L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            10, 50, 200, 25, hWnd, (HMENU)IDC_EDIT_NIK, hInst, nullptr);

        // Input Password
        hEditPassword = CreateWindowW(L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD,
            10, 100, 200, 25, hWnd, (HMENU)IDC_EDIT_PASSWORD, hInst, nullptr);

        // Tombol Login
        CreateWindowW(L"BUTTON", L"Login",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            10, 150, 100, 30, hWnd, (HMENU)ID_LOGIN, hInst, nullptr);

        break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case ID_LOGIN:
        {
            wchar_t bufferNIK[100], bufferPassword[100];
            GetWindowTextW(hEditNIK, bufferNIK, 100);
            GetWindowTextW(hEditPassword, bufferPassword, 100);
            std::wstring nik(bufferNIK);
            std::wstring password(bufferPassword);

            if (nik.empty() || password.empty()) {
                MessageBox(hWnd, L"NIK atau Password tidak boleh kosong!", L"Error", MB_OK);
            }
            else if (VerifyLogin(nik, password)) {
                MessageBox(hWnd, L"Login Berhasil", L"Info", MB_OK);
                isLoggedIn = true;
                currentUserNIK = nik;

                // Admin check
                if (VerifyAdmin(nik)) {
                    isAdmin = true;
                }

                // Hilangkan kontrol login
                ShowWindow(hEditNIK, SW_HIDE);
                ShowWindow(hEditPassword, SW_HIDE);
                ShowWindow(GetDlgItem(hWnd, ID_LOGIN), SW_HIDE);

                if (isAdmin) {
                    DisplayAdminUI(hWnd);
                } else {
                    DisplayVoteUI(hWnd);
                }
            }
            else {
                MessageBox(hWnd, L"Login Gagal", L"Error", MB_OK);
            }
        }
        break;

        case ID_VOTE_SUBMIT:
            for (size_t i = 0; i < hRadioButtons.size(); i++) {
                if (SendMessage(hRadioButtons[i], BM_GETCHECK, 0, 0) == BST_CHECKED) {
                    SaveVote((int)i);
                    MessageBox(hWnd, L"Vote Berhasil!", L"Info", MB_OK);
                    break;
                }
            }
            break;

        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        }
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void DisplayVoteUI(HWND hWnd)
{
    int yOffset = 50;
    hRadioButtons.clear();

    for (size_t i = 0; i < daftarCalon.size(); i++) {
        std::wstring text = daftarCalon[i].nama + L" - " + daftarCalon[i].deskripsi;

        HWND hRadio = CreateWindowW(L"BUTTON", text.c_str(),
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            10, yOffset, 400, 25, hWnd, nullptr, hInst, nullptr);

        hRadioButtons.push_back(hRadio);
        yOffset += 30;

        // Display the candidate's photo
        LoadImageFromFile(hWnd, daftarCalon[i].photoPath, 420, yOffset - 25, 50, 50);
    }

    hVoteSubmit = CreateWindowW(L"BUTTON", L"Submit Vote",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        10, yOffset + 20, 100, 30, hWnd, (HMENU)ID_VOTE_SUBMIT, hInst, nullptr);
}

void SaveVote(int pilihan)
{
    std::wofstream file("data/hasil_vote.txt", std::ios::app);
    file << currentUserNIK << L";" << daftarCalon[pilihan].nama << std::endl;
    file.close();
}

void LoadDataCalon()
{
    std::wifstream file("data/calon.txt");
    std::wstring line;

    while (std::getline(file, line))
    {
        std::wstringstream ss(line);
        Calon calon;
        std::getline(ss, calon.nama, L';');
        std::getline(ss, calon.deskripsi, L';');
        std::getline(ss, calon.photoPath, L';'); // Load the photo path
        daftarCalon.push_back(calon);
    }
    file.close();
}

void DisplayAdminUI(HWND hWnd)
{
    // You can add more UI elements (e.g., text fields, list views, etc.)
}

bool VerifyAdmin(const std::wstring& adminName)
{
    std::wifstream file("data/admin.txt");
    std::wstring line;

    while (std::getline(file, line))
    {
        if (line == adminName)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void SaveDataAdmin(const std::wstring& adminName)
{
    std::wofstream file("data/admin.txt", std::ios::app);
    if (file.is_open())
    {
        file << adminName << std::endl;
        file.close();
    }
}

bool VerifyLogin(const std::wstring& nik, const std::wstring& password)
{
    std::wifstream file("data/login.txt");
    std::wstring line;

    while (std::getline(file, line))
    {
        std::wstringstream ss(line);
        std::wstring fileNIK, filePassword;
        std::getline(ss, fileNIK, L';');
        std::getline(ss, filePassword, L';');

        if (fileNIK == nik && filePassword == password)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void LoadImageFromFile(HWND hWnd, const std::wstring& imagePath, int x, int y, int width, int height)
{
    HBITMAP hBitmap = (HBITMAP)LoadImageW(NULL, imagePath.c_str(), IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    if (hBitmap) {
        HDC hdc = GetDC(hWnd);
        HDC hMemDC = CreateCompatibleDC(hdc);
        SelectObject(hMemDC, hBitmap);

        BitBlt(hdc, x, y, width, height, hMemDC, 0, 0, SRCCOPY);

        DeleteDC(hMemDC);
        ReleaseDC(hWnd, hdc);
        DeleteObject(hBitmap);
    }
}
