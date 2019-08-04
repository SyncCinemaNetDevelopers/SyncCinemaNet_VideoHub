#include "tests.hpp"

using namespace vtests;

int main() {
    UnitTest unit("Fake User", "PLAY /fake/room RTSP/1.0\r\nAuthorization: Bearer fake_user\r\n\r\n", "RTSP/1.0 200 OK\r\n\r\n");
    unit.lo_send(8000, 1024);
    unit.check_test();
    unit = UnitTest("Fake Streamer", "PLAY /fake/room RTSP/1.0\r\nAuthorization: Bearer fake_streamer\r\n\r\n", "RTSP/1.0 200 OK\r\n\r\n");
    unit.lo_send(8000, 1024);
    unit.check_test();
    unit = UnitTest("Wrong Room", "PLAY /wrong RTSP/1.0\r\nAuthorization: Bearer fake_user\r\n\r\n", "RTSP/1.0 403 Forbidden\r\n\r\n");
    unit.lo_send(8000, 1024);
    unit.check_test();
    unit = UnitTest("Wrong Token", "PLAY /fake/room RTSP/1.0\r\nAuthorization: Bearer wrong_token\r\n\r\n", "RTSP/1.0 403 Forbidden\r\n\r\n");
    unit.lo_send(8000, 1024);
    unit.check_test();
}