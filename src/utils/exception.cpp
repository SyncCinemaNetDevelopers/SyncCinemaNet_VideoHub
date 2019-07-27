#include "exception.h"
#include <iostream>
#include <errno.h>
#include <string.h>

using namespace vserver;
using namespace std;

ServerError::ServerError(const char* const &message, int code = 0) {
    this->message = message;
    this->code = 0;
}

void ServerError::print() {
    char buf[1024];
    if(code != 0) {
        strerror_r(code, buf, sizeof(buf));
        cout << message << ": " << buf << endl;
    } else {
        cout << message << endl;
    }
}
