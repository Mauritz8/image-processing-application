#include <string>


class BitmapHeader {
    public:
        std::string identity;
        int size;
        int reserved1;
        int reserved2;
        int offset;
};
