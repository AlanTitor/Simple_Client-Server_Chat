#include"main.h"


int handle_client(SOCKET client_socket){

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
    printf("Connection is established!\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);


    char *message = "Hello from client!";

    send(client_socket, message, strlen(message),0);


    char buffer[512];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        printf("Received from server: %s\n", buffer);
    }

    closesocket(client_socket);
    WSACleanup();
    return 0;
}

int main(){

    UINT PORT = 0; //Порт
    initialize_port(&PORT);//Инициализация порта

    WSADATA wsadata = {0};
    test_WSAStartup(wsadata);

    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//Создаем клиентский сокет
    test_client_socket(client_socket);

    struct sockaddr_in client_info = {0};//Ифнормация о сервере к которому коннектимся
    client_info.sin_family = AF_INET;//IPv4
    client_info.sin_port = htons(PORT);//Задаем порт сервера
    client_info.sin_addr.s_addr = inet_addr("127.0.0.1"); //IP Адресс сервера

    if(connect(client_socket, (SOCKADDR*)&client_info, sizeof(client_info)) == SOCKET_ERROR){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
        printf("Couldn't establish connection!\n");
        WSAGetLastError();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    handle_client(client_socket);

    closesocket(client_socket);
    WSACleanup();
    return 0;

}

