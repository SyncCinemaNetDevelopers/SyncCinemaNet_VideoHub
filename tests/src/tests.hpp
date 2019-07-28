#include <string>

namespace vtests { 
    class UnitTest {
        std::string selfName;
        std::string src;
        std::string dest;
        std::string target;
        int status;
        public:
        UnitTest(std::string selfName, std::string src, std::string target);
        int lo_send(int port, int len);
        void check_test();
    };
}