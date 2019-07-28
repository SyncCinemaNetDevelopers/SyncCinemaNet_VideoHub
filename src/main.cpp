#include "rtsp.hpp"

using namespace vserver;

int main() {
    int port = 8000;
    RTSPServer rtsp;
    rtsp.setPortbase(port);
    rtsp.MainLoop();
}
