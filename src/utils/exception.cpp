#include "exception.hpp"
#include <iostream>
#include <errno.h>
#include <string.h>

using namespace vserver;
using namespace std;

ServerError::ServerError(const char* const &message, int code) {
    this->message = message;
    this->code = code;
}

void ServerError::print() {
    char buf[1024];
    if(code != 0) {
        cout << message << ": " << strerror_r(code, buf, sizeof(buf)) << endl;
    } else {
        cout << message << endl;
    }
}
