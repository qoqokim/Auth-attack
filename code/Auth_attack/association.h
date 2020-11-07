#include <mac.h>

using namespace std;

#pragma pack(push, 1)
struct Asso_Radiotap_header {
    uint8_t   version;     /* set to 0 */
    uint8_t   pad;
    uint16_t  len;         /* entire length */
    uint32_t  present;     /* fields present */
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Asso_Frame {
    uint16_t  type;
    uint16_t  dur;
    Mac       dst_mac;
    Mac       src_mac;
    Mac       bssid;
    uint16_t  number;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Asso_Fixed_parameters {
    uint16_t cap_info;
    uint16_t lis_inter;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Asso_Wir_Management {
    Asso_Fixed_parameters fixed_pa;
    uint8_t tag_ssid[2];
};
#pragma pack(pop)

struct Association_Packet {
    Asso_Radiotap_header asso_radiotab;
    uint8_t              asso_nul[3];
    Asso_Frame           asso_frame;
    Asso_Wir_Management  asso_wmanage;
};
