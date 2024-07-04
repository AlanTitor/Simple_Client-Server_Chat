#include"main.h"
const UINT SIZE = 500;


int handle_server(){//Инициализируем сервер
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
    test_listen_port(server_socket, SOMAXCONN);//тест на прослушку

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);//Меняем цвет на желтый
    printf("Server is listening on port %d\n", PORT);//Сервер успешно слушает порт
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//Меняем цвет на белый

    recive_send_message(server_socket);//Обработка сообщений


    closesocket(server_socket);
    WSACleanup();
    return 0;
}

int recive_send_message(SOCKET server_socket){//Обрабатываем сообщения

    pthread_t thread_recive, thread_send; //два потока: на отправку сообщений и на получение

    while (TRUE)
    {
        struct sockaddr_in client_info = {0};//Определяем пустую структуру для клиента 
        int client_info_size = sizeof(client_info);//Размер для параметра функции accept()
        SOCKET client_socket = accept(server_socket, (SOCKADDR*)&client_info, &client_info_size);//Принимаем соединение от клиента
        if(test_client_socket(client_socket) != 0) {continue;}


        SOCKET *client_socket_ptr = malloc(sizeof(SOCKET));//Выделяем память под указатель сокета
        if(client_socket_ptr == NULL){
            printf("Memory alloc error");
            closesocket(client_socket);
            continue;
        }
        *client_socket_ptr = client_socket;//Присваеваем сокет клиента указателю
        if(pthread_create(&thread_recive, NULL, recive_message, client_socket_ptr) != 0){//Передаем указатель на клиента в функцию для паралельного вычисления
            printf("Thread creation faild");
            closesocket(client_socket);
            continue;
        }
        pthread_detach(thread_recive);
    }
    closesocket(server_socket);
    WSACleanup();
    return 0;
}

void *recive_message(void *client_socket_ptr){

    SOCKET client_socket = *(SOCKET*)client_socket_ptr;//меняем тип клиенту с поинтера на обычный
    free(client_socket_ptr);
    char buffer[SIZE];//буфер сообщений
    
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);//получаем сообщения от клиента
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        printf("Received from client: %s\n", buffer);
    }
    closesocket(client_socket);
    return NULL;
}