#include <mac.h>

using namespace std;

#pragma pack(push, 1)
struct Auth_Radiotap_header {
    uint8_t   version;     /* set to 0 */
    uint8_t   pad;
    uint16_t  len;         /* entire length */
    uint32_t  present;     /* fields present */
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Auth_Frame {
    uint16_t  type;
    uint16_t  dur;
    Mac       dst_mac;
    Mac       src_mac;
    Mac       bssid;
    uint16_t  number;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Auth_Fixed_parameters {
    uint16_t auth_al;
    uint16_t auth_SEQ;
    uint16_t sta_code;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Auth_Tag_parameters {
    uint8_t  tag_num;
    uint8_t  tag_len;
    uint8_t  OUI[3];
    uint8_t ven_Data[6];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Auth_Wir_Management {
    Auth_Fixed_parameters fixed_pa;
    Auth_Tag_parameters   tag_pa;
};
#pragma pack(pop)

struct Authentication_Packet {
    Auth_Radiotap_header auth_radiotab;
    uint8_t              auth_nul[3];
    Auth_Frame           auth_frame;
    Auth_Wir_Management  auth_wmanage;
};
