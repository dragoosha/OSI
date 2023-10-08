#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    STARTUPINFO si = { 0 };
    PROCESS_INFORMATION pi = { 0 };

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    wstring ApplicationName(L"C:\\Users\\vladzaharinsky\\source\\repos\\Lab1\\Debug\\Lab1.exe");
    LPWSTR lpwAppName = &ApplicationName[0];

    wstring ComandLine(L"waitingsignal.exe");
    LPWSTR lpwCmdLine = &ComandLine[0];

    cout << "Parent process started";
    if (!CreateProcess(NULL, lpwCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "Fail initialisation " << GetLastError() << std::endl;
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);

    std::cout << "Docherny code " << exitCode << std::endl;

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
