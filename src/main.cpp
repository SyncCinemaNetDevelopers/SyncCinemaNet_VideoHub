#include "rtsp.hpp"

using namespace vserver;

int main() {
    int port = 8000;
    RTSPServer* rtsp = RTSPServer::getInstance();
    rtsp->setPortbase(port);
    rtsp->MainLoop();
}
