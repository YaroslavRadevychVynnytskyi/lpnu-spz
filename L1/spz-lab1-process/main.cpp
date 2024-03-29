#include <stdio.h>
#include <windows.h>

int main() {
	LPCWSTR lpApplicationName = L"C:\\3 course 2 sem\\SPZ\\L1\\spz-lab1\\x64\\Debug\\spz-lab1.exe";
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	int status = 0;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOWDEFAULT;

	if (!CreateProcess(
		lpApplicationName,
		NULL,
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi)) {
		fprintf(stderr, "CreateProcess failed (%lu).\n", GetLastError());
		return 1;
	}

	printf("Child process started...\n");

	printf("\nChild process ID: %lu\n", pi.dwProcessId);
	printf("Child thread ID: %lu\n", pi.dwThreadId);
	printf("Child process Handle: %p\n", pi.hProcess);
	printf("Child thread Handle: %p\n", pi.hThread);

	printf("\nParent process ID: %lu\n", GetCurrentProcessId());
	printf("Parent thread ID: %lu\n", GetCurrentThreadId());
	printf("Parent process Handle: %p\n", GetCurrentProcess());
	printf("Parent thread Handle: %p\n", GetCurrentThread());

	WaitForSingleObject(pi.hProcess, INFINITE);

	GetExitCodeProcess(pi.hProcess, (LPDWORD)&status);
	printf("\nChild process finished with status %d\n", status);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return 0;
}