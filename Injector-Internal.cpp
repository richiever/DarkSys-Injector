

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

DWORD GetProcId(const char* procName) 
{
    DWORD procId = 0;
    HANDLE hSnap  = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnap != INVALID_HANDLE_VALUE)
    {
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);
        if (Process32First(hSnap, &procEntry))
        {
            do
            {
                if (!_stricmp(procEntry.szExeFile, procName))
                {
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
    CloseHandle(hSnap);
    return procId;
}

int main()
{
    HANDLE console_color;
    console_color = GetStdHandle(
        STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 4);
    std::cout << R"(



     ________                __      _________                      .___            __               __                                      
    \______ \ _____ _______|  | __ /   _____/__.__. ______         |   | ____     |__| ____   _____/  |_  ___________   ____ ___  ___ ____  
     |    |  \\__  \\_  __ \  |/ / \_____  <   |  |/  ___/  ______ |   |/    \    |  |/ __ \_/ ___\   __\/  _ \_  __ \_/ __ \\  \/  // __ \ 
     |    `   \/ __ \|  | \/    <  /        \___  |\___ \  /_____/ |   |   |  \   |  \  ___/\  \___|  | (  <_> )  | \/\  ___/ >    <\  ___/ 
    /_______  (____  /__|  |__|_ \/_______  / ____/____  >         |___|___|  /\__|  |\___  >\___  >__|  \____/|__| /\ \___  >__/\_ \\___  >
            \/     \/           \/        \/\/         \/                   \/\______|    \/     \/                 \/     \/      \/    \/  



 )";


    std::cout << "\n produced by Richie1\n";

    SetConsoleTextAttribute(console_color, 15);

    const char* dllPath = ""; // Enter DLL Path (E.g: C:\\User\\User\\Documents\\Projects\\Generic-Code\\x64\\Debug\\Generic-code.dll)
    const char* procName = ""; // Enter process name (E.g: CrabChampions-Win64-Shipping.exe)

    DWORD procId = 0;

    while (!procId) {
        procId = GetProcId(procName);
        Sleep(30);

    }
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS,0, procId);

    if (hProc && hProc != INVALID_HANDLE_VALUE) 
    {
        void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

        WriteProcessMemory(hProc, loc, dllPath, strlen(dllPath) + 1, 0);

        HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);

        if (hThread) {
            CloseHandle(hThread);
        }

        std::cout << "Injected!" << std::endl;
    }

    if (hProc) {
        CloseHandle(hProc);
    }
    return 0;


}
