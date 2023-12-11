#include<Windows.h>
#include<processthreadsapi.h>
#include<stdio.h>


BOOL WINAPI CtrlHandler(_In_ DWORD dwCtrlType) {
    if (dwCtrlType == CTRL_C_EVENT) {
        printf("Ctrl-C event\n");
        exit(1);
    }
    else if (dwCtrlType == CTRL_CLOSE_EVENT) {
        printf("CTRL-CLOSE event\n");
        exit(2);
    }
    else {
        return FALSE;
    }
}

void printRandomNumber() {
    while (TRUE) {
        printf("%f\n", (double)rand() / RAND_MAX);
        Sleep(1500);
    }
}

void reversString() {
    while (TRUE) {

        char str[250];
        scanf_s("%s", str, 250);
        printf("%s\n", _strrev(str));
    }
}

int main() {
    SetConsoleCtrlHandler(CtrlHandler, TRUE);
    CreateThread(NULL, 0, printRandomNumber, NULL, 0, NULL);
    CreateThread(NULL, 0, reversString, NULL, 0, NULL);
    while(TRUE){}
    return 0;
}
