#include <stdexcept>

namespace vserver {
    class ServerError : public std::exception {
    public:
        ServerError(const char* const &message, int code);
        void print();
    private:
        const char* message;
        int code;
    };
}