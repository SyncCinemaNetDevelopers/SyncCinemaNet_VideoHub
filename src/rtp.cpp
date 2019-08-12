#include "rtp.hpp"

using namespace vserver;

std::vector<RTPRoom> RTPRoom::rooms;

RTPRoom::RTPRoom(std::string url, json sdp) {

}

json RTPRoom::getInfo() {
    return this->sdp;
}

bool RTPRoom::getRoomByUrl(RTPRoom& rtp, std::string url) {
    std::vector<RTPRoom>::iterator iter = RTPRoom::rooms.begin();
    while(iter != RTPRoom::rooms.end()) {
        if (url == (*iter).url) {
            rtp = *iter;
            return true;
        }
        iter++;
    }
    return false; 
}

void RTPRoom::Init() {
    RTPRoom::rooms = std::vector<RTPRoom>();
}

RTPAddr RTPRoom::getServer() {
    /* TODO: 
        1. Сделать динамическое получение значения порта из настроек
        2. Сделать динамическое получение внешнего IP адреса
    */
    RTPAddr addr;
    addr.ip = "127.0.0.1";
    addr.port = 9000;
    return addr;
}

