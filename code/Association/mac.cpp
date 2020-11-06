#include "mac.h"

Mac::Mac(const std::string r) {
    unsigned int a, b, c, d, e, f;
    int res = sscanf(r.c_str(), "%02X:%02X:%02X:%02X:%02X:%02X", &a, &b, &c, &d, &e, &f);
    if (res != SIZE) {
        fprintf(stderr, "Mac::Mac sscanf return %d r=%s\n", res, r.c_str());
        return;
    }
    mac_[0] = a;
    mac_[1] = b;
    mac_[2] = c;
    mac_[3] = d;
    mac_[4] = e;
    mac_[5] = f;
}
