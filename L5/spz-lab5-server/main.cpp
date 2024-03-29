#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>

int calculateSumOfOffNumbersInRange(int L, int U, int array[]) {
    int sum = 0;
    for (int i = L; i <= U; i++) {
        if (array[i] % 2 != 0) {
            sum += array[i];
        }
    }
    return sum;
};

int main(void)
{
    printf("TCP Server\n");
    printf("___________\n\n");

    WSADATA wsaData;
    SOCKET ListeningSocket;
    SOCKET NewConnection;
    struct sockaddr_in ServerAddr;
    struct sockaddr_in ClientAddr;
    int ClientAddrLen;
    u_short Port = 5150;
    int Ret;
    int L, U, size; 
    int sum = 0; 
    int* array;

    if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    {
        printf("WSAStartup error, number of error: %d\n", Ret);
        return -1;
    }

    if ((ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) ==
        INVALID_SOCKET)
    {
        printf("Socket error, number of error: %d\n", WSAGetLastError());
        WSACleanup();
        return -2;
    }

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(Port);
    ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(ListeningSocket, (struct sockaddr*)&ServerAddr, sizeof(ServerAddr)) ==
        SOCKET_ERROR)
    {
        printf("Bind error, number of error: %d\n", WSAGetLastError());
        closesocket(ListeningSocket);
        WSACleanup();
        return -3;
    }

    if (listen(ListeningSocket, 5) == SOCKET_ERROR)
    {
        printf("Listen error, number of error: %d\n", WSAGetLastError());
        closesocket(ListeningSocket);
        WSACleanup();
        return -4;
    }

    printf("Waiting for connection on port: %d.\n", Port);
    ClientAddrLen = sizeof(ClientAddr);

    if ((NewConnection = accept(ListeningSocket, (struct sockaddr*)&ClientAddr,
        &ClientAddrLen)) == INVALID_SOCKET)
    {
        printf("Accept error, number of error: %d\n", WSAGetLastError());
        closesocket(ListeningSocket);
        WSACleanup();
        return -5;
    }

    printf("Connection success with %s:%d.\n", inet_ntoa(ClientAddr.sin_addr),
        ntohs(ClientAddr.sin_port));
    closesocket(ListeningSocket);

    if ((Ret = recv(NewConnection, (char*)&L, sizeof(int), 0)) == SOCKET_ERROR)
    {
        printf("Recv error, number of error: %d\n", WSAGetLastError());
        closesocket(NewConnection);
        WSACleanup();
        return -6;
    }

    if ((Ret = recv(NewConnection, (char*)&U, sizeof(int), 0)) == SOCKET_ERROR)
    {
        printf("Recv error, number of error: %d\n", WSAGetLastError());
        closesocket(NewConnection);
        WSACleanup();
        return -7;
    }

    if ((Ret = recv(NewConnection, (char*)&size, sizeof(int), 0)) == SOCKET_ERROR)
    {
        printf("Recv error, number of error: %d\n", WSAGetLastError());
        closesocket(NewConnection);
        WSACleanup();
        return -8;
    }

    array = (int*)malloc(size * sizeof(int));

    if ((Ret = recv(NewConnection, (char*)array, sizeof(int) * size, 0)) == SOCKET_ERROR)
    {
        printf("Recv error, number of error: %d\n", WSAGetLastError());
        closesocket(NewConnection);
        WSACleanup();
        return -9;
    }
    printf("Array: \n");
    for (int i = 0; i < size; i++) {
        printf("%d\n", array[i]);
    }

    printf("\n");

    sum = calculateSumOfOffNumbersInRange(L, U, array);

    printf("Sum of odd numbers in the range [%d, %d] is: %d\n", L, U, sum);

    if ((Ret = send(NewConnection, (char*)&sum, sizeof(int), 0)) == SOCKET_ERROR)
    {
        printf("Send error, number of error: %d\n", WSAGetLastError());
        closesocket(NewConnection);
        WSACleanup();
        return -10;
    }

    printf("Result sent to client.\n");
    printf("Closing connection with client.\n");
    closesocket(NewConnection);
    WSACleanup();
    printf("Press Enter to finish.\n");
    getchar();
    return 0;
}
