extern "C" {
  #include "utils/rtsp-parser.h"
}

namespace vserver {

  class RTSPConnect {
    PRTSP_MESSAGE msg;
    int socket;
  };

  class RTSPServer {
    char hostname[1024];
    int port;
  public:
    void setPortbase(int port);
    int MainLoop(void);
  };
}
