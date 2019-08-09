#include "tests.hpp"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>

using namespace vtests;

UnitTest::UnitTest(std::string selfName, std::string src, std::string target) {
    this->selfName = selfName;
    this->src = src;
    this->target = target;
    status = 0;
}

int UnitTest::lo_send(int port, int len) {
    const char* buf = src.c_str();
    char* res = new char[len];
    int sock;
    struct sockaddr_in addr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        status = -1;
        return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        status = -2;
        return -2;
    }

    send(sock, buf, src.length(), 0);
    recv(sock, res, len, 0);
    
    dest = res;
    close(sock);

    return 0;
}

void UnitTest::check_test() {
    if(status < 0) {
        std::cout << "Test " << selfName << " failed with error status " << status << std::endl;
    } else if (dest == target) {
        std::cout << "Test " << selfName << " OK.\n";
    } else {
        std::cout << "Test " << selfName << " failed with data " << dest << " and sample " << target << std::endl;
    }
}

void UnitTest::check_len() {
    if(status < 0) {
        std::cout << "Test " << selfName << " failed with error status " << status << std::endl;
    } else if (dest.length() == target.length()) {
        std::cout << "Test " << selfName << " OK.\n";
    } else {
        std::cout << "Test " << selfName << " failed with data " << dest << " and sample " << target << std::endl;
    }
}

void UnitTest::replace(std::string& old, std::string from, std::string to) {
    size_t start_pos = 0;
    while((start_pos = old.find(from, start_pos)) != std::string::npos) {
         old.replace(start_pos, from.length(), to);
         start_pos += to.length();
    }
}