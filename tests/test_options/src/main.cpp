#include "tests.hpp"

using namespace vtests;

int main() {
    UnitTest unit("Options", "OPTIONS * RTSP/1.0\r\n\r\n", "RTSP/1.0 403 Forbidden\r\n\r\n");
    unit.lo_send(8000, 1024);
    unit.check_test();
}