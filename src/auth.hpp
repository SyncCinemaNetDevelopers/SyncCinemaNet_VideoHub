#ifndef SRC_AUTH_HPP
#define SRC_AUTH_HPP

#define AUTH_ERROR -1
#define AUTH_UNAUTHORIZED 0
#define AUTH_USER 1
#define AUTH_STREAMER 2

#include <string>
namespace vserver {
    class BaseAuth {
    public:
        virtual int checkRoom() = 0;
        virtual int authorize() = 0;
        BaseAuth(std::string token, std::string room);

    protected:
        std::string token;
        std::string room;
    };

    class FakeAuth : public BaseAuth {
    public:
        FakeAuth(std::string token, std::string room);
        int checkRoom();
        int authorize();
    };
}
#endif