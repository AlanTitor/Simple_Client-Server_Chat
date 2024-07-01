#include"main.h"

int handle_server(){
    
    UINT PORT = 0; //Порт
    initialize_port(&PORT);//Инициализация порта
    
    WSADATA wsadata = {0};
    test_WSAStartup(wsadata);//инициализируем версию сокета
    
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//IPv4/TCP задаем параметры сокета 
    test_server_socket(server_socket);//Проверка целостности работы сокета


    struct sockaddr_in server_info = {0};
    server_info.sin_family = AF_INET;//IPv4
    server_info.sin_port = htons(PORT);//Задаем порт
    server_info.sin_addr.s_addr = inet_addr("127.0.0.1"); //IP Адресс

    test_bind(server_socket, server_info);//Привязываем сокет к адрессу
    test_listen_port(server_socket, SOMAXCONN);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);//Меняем цвет на желтый
    printf("Server is listening on port %d\n", PORT);//Сервер успешно слушает порт
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//Меняем цвет на белый

    char buffer[512];//буфер сообщений

    while (TRUE)
    {
        struct sockaddr_in client_info = {0};//Определяем пустую структуру для клиента 
        int client_info_size = sizeof(client_info);//Размер для параметра функции accept()
        SOCKET client_socket = accept(server_socket, (SOCKADDR*)&client_info, &client_info_size);//Устанавливаем соединение с клиентом
        test_client_socket(client_socket);

        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);//получаем сообщения от клиента
        if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        printf("Received from server: %s\n", buffer);
        }
    }

    closesocket(server_socket);
    WSACleanup();
    return 0;
}