#include "auth.hpp"
#include <iostream>
#include <vector>
#include <sstream>

using namespace vserver;

BaseAuth::BaseAuth(std::string token, std::string room) {
    std::vector<std::string> words;
    std::istringstream ist(token);
    std::string tmp;
    while(ist >> tmp) {
        std::cout << tmp << std::endl;
        words.push_back(tmp);
    }
    this->token = words[1];
    this->room = room;
}

int FakeAuth::checkRoom() {
    if(room == "/fake/room")
        return 1;
    return 0;
}

int FakeAuth::authorize() {
    if(token == "fake_user")
        return AUTH_USER;
    if(token == "fake_streamer")
        return AUTH_STREAMER;
    return AUTH_UNAUTHORIZED;
}