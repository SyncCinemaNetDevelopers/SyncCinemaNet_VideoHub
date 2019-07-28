#include "tests.hpp"

using namespace vtests;

int main() {
    UnitTest unit("Options", "OPTIONS * RTSP/1.1\r\n\r\n", "RTSP/1.1 200 OK\r\n\r\n");
    unit.lo_send(8000, 1024);
    unit.check_test();
}