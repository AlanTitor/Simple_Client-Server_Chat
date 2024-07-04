#include"main.h"

const UINT SIZE = 500;


void send_message(SOCKET client_socket){

    
    char message[SIZE];//Сообщение от клиента

    printf("Enter message: ");
    fflush(stdout);
    
    // Очищаем буфер ввода перед чтением
    while (getchar() != '\n');
    
    // Читаем строку с вводом пользователя
    if (fgets(message, sizeof(message), stdin) == NULL) {
        printf("Error reading input.\n");
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    // Удаляем символ новой строки, если он есть
    size_t len = strlen(message);
    if (len > 0 && message[len - 1] == '\n') {
        message[len - 1] = '\0';
    }

    send(&client_socket, message, sizeof(message), 0);
}

void recive_message(SOCKET client_socket){
    
    char buffer[SIZE];//Получение сообщения от сервера
    int bytes_received;//Размер сообщения полученого от сервера


    bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);//Получаем сообщение от сервера
    if (bytes_received > 0 && bytes_received <= sizeof(buffer)) {//Проверяем размер сообщения
        buffer[bytes_received] = '\0';
        printf("Received from server: %s\n", buffer);
    }
}

int handle_client(SOCKET client_socket){




    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
    printf("Connection is established!\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);


    send_message(&client_socket);
    recive_message(&client_socket);
    

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

    test_client_connect(client_socket, client_info);

    handle_client(client_socket);

    closesocket(client_socket);
    WSACleanup();
    return 0;

}

