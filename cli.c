#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>

int main(){
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        printf("CreateToolhelp32Snapshot failed. Error: %lu\n", GetLastError());
        return 1;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if(!Process32First(hProcessSnap, &pe32)){
        printf("Process32First failed\n");
        CloseHandle(hProcessSnap);
        return 1;
    }

    do{
        printf("Process ID: %u\tExecutable Name: %s\n", pe32.th32ProcessID, pe32.szExeFile);
    } while(Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return 0;

}