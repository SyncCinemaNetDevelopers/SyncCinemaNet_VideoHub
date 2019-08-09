#ifndef TESTS_SRC_TESTS_HPP
#define TESTS_SRC_TESTS_HPP

#include <string>

namespace vtests { 
    class UnitTest {
    public:
        UnitTest(std::string selfName, std::string src, std::string target);
        int lo_send(int port, int len);
        void check_test();
        void check_len();
        static void replace(std::string& old, std::string from, std::string to);

    private:
        std::string selfName;
        std::string src;
        std::string dest;
        std::string target;
        int status;
    };
}

#endif