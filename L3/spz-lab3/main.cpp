#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define DEQUE_CAPACITY_Byte 7168
#define DEQUE_CAPACITY (DEQUE_CAPACITY_Byte / sizeof (short));
typedef
struct
{
	short* data;
	size_t size;
	size_t capacity;
} Deque;

void createDeque(Deque *deque)
{
	deque->data = (short*) VirtualAlloc(NULL, DEQUE_CAPACITY_Byte, MEM_COMMIT |
		MEM_RESERVE, PAGE_READWRITE);
		if (deque->data == NULL)
		{
			perror("Error allocating memory for deque");
			exit(EXIT_FAILURE);
		}
		deque->size = 0;
		deque->capacity = DEQUE_CAPACITY;
}

int isEmpty(Deque *deque)
{
	return deque->size == 0;
}

void addLeft(Deque* deque, short value) {
	if (deque->size < deque->capacity) {
		for (size_t i = deque->size; i > 0; --i) {
			deque->data[i] = deque->data[i - 1];
		}
		deque->data[0] = value;
		deque->size++;
	}
	else {
		fprintf(stderr, "Deque capacity exceeded\n");
		exit(EXIT_FAILURE);
	}
}

void addRight(Deque* deque, short value) {
	if (deque->size < deque->capacity) {
		deque->data[deque->size] = value;
		deque->size++;
	}
	else {
		fprintf(stderr, "Deque capacity exceeded\n");
		exit(EXIT_FAILURE);
	}
}

void removeLeft(Deque* deque) {
	if (!isEmpty(deque)) {
		for (size_t i = 0; i < deque->size - 1; ++i) {
			deque->data[i] = deque->data[i + 1];
		}
		deque->size--;
	}
	else {
		fprintf(stderr, "Deque is empty\n");
	}
}

void removeRight(Deque* deque) {
	if (!isEmpty(deque)) {
		deque->size--;
	}
	else {
		fprintf(stderr, "Deque is empty\n");
	}
}

short peekLeft(Deque* deque) {
	if (!isEmpty(deque)) {
		return deque->data[0];
	}
	else {
		fprintf(stderr, "Deque is empty\n");
		exit(EXIT_FAILURE);
	}
}

short peekRight(Deque* deque) {
	if (!isEmpty(deque)) {
		return deque->data[deque->size - 1];
	}
	else {
		fprintf(stderr, "Deque is empty\n");
		exit(EXIT_FAILURE);
	}
}

void printDeque(Deque* deque) {
	printf("Deque elements:\n");
	for (size_t i = 0; i < deque->size; ++i) {
		printf("%d ", deque->data[i]);
	}
	printf("\n");
}

void destroyDeque(Deque *deque)
{
	if (deque->data != NULL)
		VirtualFree(deque->data, 0, MEM_RELEASE);
}

int main()
{
	Deque deque;
	createDeque(&deque);	

	printf("Is deque empty ? %s\n", isEmpty(&deque) ? "Yes" : "No");
		
	addLeft(&deque, 10);
	addRight(&deque, 20);
	addLeft(&deque, 5);
	addRight(&deque, 17);

	printf("\nIs deque empty ? %s\n", isEmpty(&deque) ? "Yes" : "No");
	printDeque(&deque);

	printf("\nPeek left: %d", peekLeft(&deque));
	printf("\nPeek right: %d\n", peekRight(&deque));

	removeLeft(&deque);
	removeRight(&deque);

	printDeque(&deque);

	destroyDeque(&deque);
	
	return 0;
}
