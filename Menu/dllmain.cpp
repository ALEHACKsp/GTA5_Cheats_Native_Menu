#include "main.h"

BOOL WINAPI ThreadFunc(LPVOID hMod){
    Hook::Start((HMODULE)hMod);
    return 0;
}

BOOL WINAPI DllMain(HMODULE hModule,DWORD ul,LPVOID lpPar){
    switch (ul){
        case DLL_PROCESS_ATTACH:
            //创建线程
            CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ThreadFunc, lpPar, 0, 0);
            break;
        case DLL_PROCESS_DETACH:
            //卸载钩子
            Hook::Cleanup();
            //退出
            ExitThread(0);
            break;
    }
    return TRUE;
}