#include"../include/include.h"

void initialize_port(UINT *pPORT){//Инициализация порта

    int flag = 1;
    do{
        printf("Enter number of port: ");
        scanf("%u", pPORT);//вводим порт
        if((*pPORT) <= 0){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);//меняем цвет консоли
            printf("Incorrect number of port! Try again\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
            continue;
        }
        flag = 0;
    }while(flag);
}

int test_WSAStartup(WSADATA wsadata){//Инициализируем версию сокетов и тестируем (версия 2.2)

    if(WSAStartup(MAKEWORD(2,2), &wsadata) != 0){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
        printf("ERROR WSAStartup version!\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
        return 1;        
    }
    return 0;
}

int test_server_socket(SOCKET server_socket){//Проверка целостности работы сокета
    if(server_socket == INVALID_SOCKET){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
        printf("Couldn't establish server_socket connection!\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    return 0;
}

int test_bind(SOCKET server_socket, struct sockaddr_in server_info){//Пытаемся привязать сокет к адрессу

    if(bind(server_socket, (SOCKADDR*)&server_info, sizeof(server_info)) != 0){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
        printf("Couldn't bind socket to address!\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    return 0;
}

int test_listen_port(SOCKET server_socket, int MAXCONN){

    if(listen(server_socket, MAXCONN) != 0){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
        printf("Couldn't listen port!\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    return 0;
}

int test_client_socket(SOCKET client_socket){

    if(client_socket == INVALID_SOCKET){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
        printf("Couldn't establish client_socket connection!\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);     
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }
    return 0;
}

int test_client_connect(SOCKET client_socket, struct sockaddr_in client_info){
    if(connect(client_socket, (SOCKADDR*)&client_info, sizeof(client_info)) == SOCKET_ERROR){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
        printf("Couldn't establish connection!\n");
        WSAGetLastError();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }
}