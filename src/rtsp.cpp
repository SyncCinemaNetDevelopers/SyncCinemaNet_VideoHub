#include "rtsp.h"
#include "utils/exception.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
extern int errno;

using namespace vserver;

void RTSPServer::setPortbase(int port) {
  gethostname(this->hostname, sizeof(this->hostname));
  this->port = port;
}

int RTSPServer::MainLoop(void) {
  int sock, listener, ret;
  char buf[1024];
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
      /* TODO: реализовать получение строки неопределённой длины и собственно RTSP, вместо эхо-сервера */
      while (true) {
        int bytes_read = recv(sock, buf, 1024, 0);
        if(bytes_read <= 0) break;
        send(sock, buf, bytes_read, 0);
      }
      close(sock);
    }
    close(listener);
  } catch(ServerError &e) {
    e.print();
    return -1;
  }
  return 0;
}
