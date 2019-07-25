#include <stdexcept>

namespace vserver {
    class ServerError : public std::exception {
        const char* message;
        int code;
        public:
        ServerError(const char* const &message, int);
        void print();
    };
}