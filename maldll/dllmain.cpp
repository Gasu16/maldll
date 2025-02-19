// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <windows.h>
#include <wininet.h>
#include <winsock.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" __declspec(dllexport) void CALLBACK mydllmain()
{
    MessageBox(0, L"Test!", L"Mytest", 0);
}

extern "C" __declspec(dllexport) void CALLBACK amibeingdebugged() {
    if (IsDebuggerPresent() != 0) {
        MessageBox(0, L"Am I being debugged right now?", L"Suspicious debug", 0);
    }
    else {
        MessageBoxW(0, L"Not in a debug environment", L"Everything fine", 0);
    }
}

extern "C" __declspec(dllexport) void CALLBACK createfile() {
    HANDLE hFile = CreateFileA("myfile.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    MessageBox(0, L"File Created", L"File", 0);
    char szBuffer[256];
    char text[255] = "ciao";
    DWORD dwBytesWritten;
    strncpy_s(szBuffer, sizeof(szBuffer), text, strlen(text));
    WriteFile(hFile, szBuffer, strlen(szBuffer), &dwBytesWritten, NULL);
    MessageBox(0, L"File Written", L"FileW", 0);
}

extern "C" __declspec(dllexport) void CALLBACK internet_conn() {
    HANDLE conn = InternetOpenA("Mozilla/4.1337", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    HANDLE conn_url = InternetOpenUrlA(conn, "https://www.google.com", 0, 0, INTERNET_FLAG_RAW_DATA, 0);
    MessageBox(0, L"Connessione riuscita", L"Conn", 0);
}
/*
extern "C" __declspec(dllexport) void CALLBACK createprocess() {
    HANDLE hToken = GetCurrentProcessToken();
    //CreateProcessAsUser(hToken, NULL, NULL, );
    CreateProcessA("test", "test.exe", NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo);
}
*/
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

