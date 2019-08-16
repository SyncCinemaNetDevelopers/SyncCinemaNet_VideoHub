#ifndef SRC_RTP_HPP
#define SRC_RTP_HPP
#include <string>
#include <vector>
#include <sdptransform/sdptransform.hpp>
#include <sdptransform/json.hpp>

namespace vserver {

    typedef struct {
        std::string ip;
        int audio_port;
        int video_port;

    } RTPAddr;

    class RTPRoom {
    public:
        RTPRoom(std::string url, json sdp);
        json getInfo();
        static RTPRoom* getRoomByUrl(std::string url);
        static void Init();

    private:
        RTPAddr getServer(); 

    private:
        static std::vector<RTPRoom> rooms;
        std::string url;
        json user, streamer, income;
    };

}

#endif