#include <stdio.h>
#include <time.h>
#include <windows.h>


struct ThreadArgs {
	int* array;
	int array_size;
	int l;
	int u;
};

DWORD WINAPI sumOddsNumbers(LPVOID lpParam) {
	struct ThreadArgs* threadArgs = (struct ThreadArgs*)lpParam;
	int* array = threadArgs->array;
	int size = threadArgs->array_size;
	
	int l = threadArgs->l;
	int u = threadArgs->u;
	
	int sum = 0;

	for (int i = l; i <= u; i++) {
		if (array[i] % 2 != 0) {
			sum += array[i];
		}
	}
	return sum;
}

int main() {
	srand(time(NULL));

	int n;
	int l;
	int u;
	printf("Enter the size of the array: ");
	scanf_s("%d", &n);

	printf("Enter L: ");
	scanf_s("%d", &l);

	printf("Enter U: ");
	scanf_s("%d", &u);

	int* dynamicArray = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		dynamicArray[i] = rand() % 50;
	}

	printf("\nOriginal array: \n");
	for (int i = 0; i < n; i++) {
		printf("%d ", dynamicArray[i]);
	}
	printf("\n");

	printf("\nArray from L to U: \n");
	for (int i = l; i <= u; i++) {
		printf("%d ", dynamicArray[i]);
	}
	printf("\n");

	struct ThreadArgs threadArgs;
	threadArgs.array = dynamicArray;
	threadArgs.array_size = n;
	threadArgs.l = l;
	threadArgs.u = u;

	HANDLE hThread;
	DWORD dwThreadId;

	hThread = CreateThread(
		NULL,
		0,
		sumOddsNumbers,
		&threadArgs,
		0,
		&dwThreadId);

	if (hThread == NULL) {
		fprintf(stderr, "Error creating thread (%lu).\n", GetLastError());
		return 1;
	}

	WaitForSingleObject(hThread, INFINITE);
	DWORD dwExitCode;
	GetExitCodeThread(hThread, &dwExitCode);

	printf("\nSum of odd numbers from L to U: %lu\n", dwExitCode);

	printf("\n");

	printf("\nThread ID: %lu\n", dwThreadId);
	printf("Thread Handle: %p\n\n", hThread);
	printf("Main process ID: %lu\n", GetCurrentProcessId());
	printf("Main thread ID: %lu\n", GetCurrentThreadId());
	printf("Main process Handle: %p\n", GetCurrentProcess());
	printf("Main thread Handle: %p\n", GetCurrentThread());

	CloseHandle(hThread);
	free(dynamicArray);
	
	getchar(); getchar();

	return 0;
}