#include "tests.hpp"
#include <string>
#include <iostream>

using namespace vtests;

int main() {
    std::string prs = R"(v=0
o=- 20518 0 IN IP4 203.0.113.1
s=FakeSDP
t=0 0
c=IN IP4 203.0.113.1
a=ice-ufrag:F7gI
a=ice-pwd:x9cml/YzichV2+XlhiMu8g
a=fingerprint:sha-1 42:89:c5:c6:55:9d:6e:c8:e8:83:55:2a:39:f9:b6:eb:e9:a3:a9:e7
m=audio 54400 RTP/SAVPF 0 96
a=rtpmap:0 PCMU/8000
a=rtpmap:96 opus/48000
a=ptime:20
a=sendrecv
a=candidate:0 1 UDP 2113667327 203.0.113.1 54400 typ host
a=candidate:1 2 UDP 2113667326 203.0.113.1 54401 typ host
m=video 55400 RTP/SAVPF 97 98
a=rtcp-fb:* nack
a=rtpmap:97 H264/90000
a=fmtp:97 profile-level-id=4d0028;packetization-mode=1
a=rtcp-fb:97 trr-int 100
a=rtcp-fb:97 nack rpsi
a=rtpmap:98 VP8/90000
a=rtcp-fb:98 trr-int 100
a=rtcp-fb:98 nack rpsi
a=sendrecv
a=candidate:0 1 UDP 2113667327 203.0.113.1 55400 typ host
a=candidate:1 2 UDP 2113667326 203.0.113.1 55401 typ host
a=ssrc:1399694169 foo:bar
a=ssrc:1399694169 baz
)";
    std::string res = R"(v=0
o=- 20518 0 IN IP4 127.0.0.1
s=SCNet
t=0 0
m=audio 9002 RTP/SAVP 0 96
m=video 9000 RTP/SAVP 97 98
a=recvonly
)";
    std::string opt = "PLAY /fake/room RTSP/1.0\r\nAuthorization: Bearer fake_streamer\r\n\r\n";
    std::string ans = "RTSP/1.0 200 OK\r\n\r\n";
    UnitTest::replace(res, "\n", "\r\n");
    UnitTest unit("SDP", opt + prs, ans + res);
    unit.lo_send(8000, 1024);
    unit.check_len();
    opt = "PLAY /fake/room RTSP/1.0\r\nAuthorization: Bearer fake_user\r\n\r\n";
    unit = UnitTest("SDP user", opt, ans + res);
    unit.lo_send(8000, 1024);
    unit.check_len();
}