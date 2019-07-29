#include "rtsp.hpp"
#include "utils/exception.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <string>
extern int errno;

using namespace vserver;

RTSPServer* RTSPServer::instance = nullptr;

RTSPServer::RTSPServer(){

}

RTSPServer::~RTSPServer(){
  
}

RTSPServer* RTSPServer::getInstance(){
    if(instance == nullptr)
        instance = new RTSPServer();
    return instance;
}

void RTSPServer::setPortbase(int port) {
    gethostname(this->hostname, sizeof(this->hostname));
    this->port = port;
}

RTSPConnect::RTSPConnect(int socket) {
    this->socket = socket;
}

int RTSPConnect::readText() {
    char buf[1024];
    input = "";
    int flag = 0;
    while (true) {
        memset(buf, 0, 1024);
        int bytes_read = recv(socket, buf, 1024, flag);
        if(bytes_read < 0) {
            if(flag != 0 && errno == EAGAIN)
                break;
        return -errno;
        }
        if(bytes_read == 0) break;
        input += buf;
        flag = MSG_DONTWAIT;
    }
    std::cout << "Получены данные: " << input;
    return input.length();
}

int RTSPConnect::handleData() {
    /*
    TODO:
    1. Сделать отделение SDP от RTSP-заголовка
    2. Сделать получение и обрабтку данных от веб-API
    3. Добавить полезную нагрузку, сформированную в шаге 2
    */
    const char* src = input.c_str();
    char* data = new char[strlen(src)];
    strcpy(data,src);
    int ret = parseRtspMessage(&request, (char*)data, strlen(data));
    if(ret < 0) {
        createRtspResponse(&response, nullptr, 0, (char*)"RTSP/1.1", 400, (char*)"Bad Request", 0, nullptr, nullptr, 0);
        output = serializeRtspMessage(&response, &ret);
    } else {
        createRtspResponse(&response, nullptr, 0, (char*)"RTSP/1.1", 200, (char*)"OK", 0, nullptr, nullptr, 0);
        output = serializeRtspMessage(&response, &ret);
    }
    freeMessage(&request);
    freeMessage(&response);
    return ret;
}

int RTSPConnect::writeText() {
    const char *str = output.c_str();
    int ret = send(socket, str, output.length(), 0);
    std::cout << "Отправлены данные: " << output;
    if(ret < 0) return -errno;
    return ret;
}

RTSPConnect::~RTSPConnect() {
    close(socket);
}

int RTSPServer::MainLoop(void) {
    int sock, listener, ret;
    struct sockaddr_in addr;
    try {
        listener = socket(AF_INET, SOCK_STREAM, 0);
        if (listener < 0) {
            throw ServerError("socket", errno);
        }
        addr.sin_family = AF_INET;
        addr.sin_port = htons(this->port);
        /* TODO: добавить поддержку внешнего IP-адреса сервера */
        addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        ret = bind(listener, (struct sockaddr* )&addr, sizeof(addr));
        if(ret < 0) {
            throw ServerError("bind", errno);
        }
        listen(listener, 1024);
        while(true) {
            sock = accept(listener, nullptr, nullptr);
            if (sock < 0) {
                throw ServerError("accept", errno);
            }
            RTSPConnect *connect = new RTSPConnect(sock); // Храним в куче для вызова деструктора
            while(true) {
                ret = connect->readText();
                if (ret < 0) {
                    throw ServerError("read", -ret);
                }
                if (ret == 0) break;
                ret = connect->handleData();
                if(ret < 0) {
                throw ServerError("handle", 0);
                } 
                ret = connect->writeText();
                if(ret < 0) {
                throw ServerError("write", -ret);
                }
            }     
            delete connect;
        }
        close(listener);
    } catch(ServerError &e) {
        e.print();
        return -1;
    }
    return 0;
}
