#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <winsock2.h>
#include <windows.h>

int main()
{
    printf("TCP Client\n");
    printf("___________\n\n");

    WSADATA wsaData;
    SOCKET s;
    struct sockaddr_in ServerAddr;
    u_short Port = 5150;
    int Ret;
    int L, U;
    int* array;
    int size;
    int sum = 0;

    if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    {
        printf("WSAStartup error, number of error: %d\n", Ret);
        return 1;
    }

    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET)
    {
        printf("Socket error, number of error: %d\n", WSAGetLastError());
        WSACleanup();
        return 2;
    }

    char ipAddress[32];
    printf("Enter server IP-address : ");
    gets_s(ipAddress);

    printf("Enter the lower bound (L) of the range: ");
    scanf_s("%d", &L);
    printf("Enter the upper bound (U) of the range: ");
    scanf_s("%d", &U);

    printf("Enter array size: ");
    scanf_s("%d", &size);

    array = (int*)malloc(size * sizeof(int));

    srand(time(NULL));
    printf("Generated array: \n");
    for (int i = 0; i < size; i++)
    {
        array[i] = rand() % 50;
        printf("%d\n", array[i]);
    }
    printf("\n");

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(Port);
    ServerAddr.sin_addr.s_addr = inet_addr(ipAddress);

    printf("Connection attempt with %s:%d ...\n", inet_ntoa(ServerAddr.sin_addr),
        ntohs(ServerAddr.sin_port));

    if (connect(s, (struct sockaddr*)&ServerAddr, sizeof(ServerAddr)) ==
        SOCKET_ERROR)
    {
        printf("Connect error, number of error: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return 3;
    }

    printf("Connection success.\n");

    if ((Ret = send(s, (char*)&L, sizeof(int), 0)) == SOCKET_ERROR)
    {
        printf("Send error, number of error: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return 4;
    }

    if ((Ret = send(s, (char*)&U, sizeof(int), 0)) == SOCKET_ERROR)
    {
        printf("Send error, number of error: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return 5;
    }


    if ((Ret = send(s, (char*)&size, sizeof(int), 0)) == SOCKET_ERROR)
    {
        printf("Send error, number of error: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return 6;
    }

    if ((Ret = send(s, (char*)array, sizeof(int) * size, 0)) == SOCKET_ERROR)
    {
        printf("Send error, number of error: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return 7;
    }



    printf("Data sent to server.\n");

    printf("Data received from server:\n");

    if ((Ret = recv(s, (char*)&sum, sizeof(int), 0)) == SOCKET_ERROR)
    {
        printf("Recv error, number of error: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return -8;
    }

    printf("Sum of odd numbers in the range [%d, %d] is: %d\n", L, U, sum);

    closesocket(s);
    WSACleanup();
    printf("Press ENTER to finish.\n");
    getchar();
    return 0;
}
