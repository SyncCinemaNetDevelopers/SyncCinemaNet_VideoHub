#include "rtp.hpp"
#include <iostream>

using namespace vserver;

std::vector<RTPRoom> RTPRoom::rooms;

static std::string blank = R"(v=0
o={{origin}}
s=SCNet
t=0 0
m=audio {{aport}} RTP/SAVP {{apayloads}}
m=video {{vport}} RTP/SAVP {{vpayloads}}
a={{direction}}
)";

static void setValue(std::string& dest,std::string name, std::string value) {
    name = "{{" + name + "}}";
    size_t start_pos = 0;
    while((start_pos = dest.find(name, start_pos)) != std::string::npos) {
         dest.replace(start_pos, name.length(), value);
         start_pos += value.length();
    }
}

RTPRoom::RTPRoom(std::string url, json sdp) {
    RTPAddr addr = RTPRoom::getServer();
    this->url = url;
    std::string data = blank, spush;
    std::string apay, vpay;
    std::string origin = sdp["origin"].value("username","") + " " + std::to_string(sdp["origin"].value("sessionId",0));
    origin += " " + std::to_string(sdp["origin"].value("sessionVersion",0)) + " " + sdp["origin"].value("netType","");
    origin += " IP" + std::to_string(sdp["origin"].value("ipVer",0)) + " " + addr.ip;
    setValue(data, "origin", origin);
    for(int i=0; i<sdp["media"].size(); i++) {
        if(sdp["media"][i]["type"] == "audio") {
            setValue(data, "apayloads", sdp["media"][i]["payloads"]);
            setValue(data, "aport", std::to_string(addr.audio_port));
        } else if(sdp["media"][i]["type"] == "video") {
            setValue(data, "vpayloads", sdp["media"][i]["payloads"]);
            setValue(data, "vport", std::to_string(addr.video_port));
        }
    }
    spush = data;
    setValue(data, "direction", "recvonly");
    setValue(spush, "direction", "sendonly");
    std::cout << "Входим тут"  << data << spush << std::endl;
    this->user = sdptransform::parse(data);
    std::cout << "Помилка изыди" << std::endl;
    this->streamer = sdptransform::parse(spush);
    std::cout << "Помилка изыди 2" << std::endl;
    this->income = sdp;
    rooms.push_back(*this);
}

json RTPRoom::getInfo() {
    return this->user;
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
    addr.video_port = 9000;
    addr.audio_port = 9002;
    return addr;
}

