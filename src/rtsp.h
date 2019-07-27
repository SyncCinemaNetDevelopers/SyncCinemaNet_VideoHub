#include <string>
extern "C" {
  #include "utils/rtsp-parser.h"
}

namespace vserver {

  class RTSPConnect {
    RTSP_MESSAGE request;
    RTSP_MESSAGE response;
    int socket;
    std::string input;
    std::string output;
    public:
      RTSPConnect(int socket);
      ~RTSPConnect();
      int readText();
      int handleData();
      int writeText();
  };

  class RTSPServer {
    char hostname[1024];
    int port;
  public:
    void setPortbase(int port);
    int MainLoop(void);
  };
}
