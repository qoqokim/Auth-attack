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
struct Association_Frame {
    uint16_t  type;
    uint16_t  dur;
    Mac       dst_mac;
    Mac       src_mac;
    Mac       bssid;
    uint16_t  number;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Fixed_parameters {
    uint16_t cap_info;
    uint16_t lis_inter;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Tag_ssid {
    uint8_t tag_num;
    uint8_t tag_len;
    uint8_t ssid ;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Tag_srate {
    uint8_t tag_num;
    uint8_t tag_len;
    uint8_t s_r[8];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Tag_erate {
    uint8_t tag_num;
    uint8_t tag_len;
    uint8_t s_r[4];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Tag_parameters {
    Tag_ssid  SSID;
    Tag_srate s_rate;
    Tag_erate e_rate;
    uint8_t   power;
    uint8_t   s_channel;
    uint8_t   RSN;
    uint8_t   HT_cap;
    uint8_t   e_cap;
    uint8_t   oper_mode;
    uint8_t   v_HT;
    uint8_t   v_epi;
    uint8_t   v_bro;
    uint8_t   v_Mic;
    uint8_t   v_epi2;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct Wir_Management {
    Fixed_parameters fixed_pa;
    Tag_parameters tag_pa;
};
#pragma pack(pop)


struct Association_Packet {
    Radiotap_header   radiotab;
    uint8_t nul[3];
    Association_Frame asso_frame;
    Wir_Management    w_manage;
};


void usage() {
    cout << "syntax : association <interface> <ap mac> <station mac>\n";
    cout << "sample : association 00:11:22:33:44:55 66:77:88:99:AA:BB\n";
}

int main(int argc , char * argv[]) {

    if (argc != 4) {
        usage();
        return -1;
    }

    cout << "** Association Start **\n";

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

    Association_Packet packet;

    packet.radiotab.len = 0x000b;
    packet.asso_frame.type = 0x0000;
    packet.asso_frame.dur = 0x013a;
    packet.asso_frame.dst_mac = Mac(ST_MAC);
    packet.asso_frame.src_mac = Mac(AP_MAC);
    packet.asso_frame.bssid = Mac(ST_MAC);

    packet.w_manage.fixed_pa.cap_info = 0x1531;
    packet.w_manage.fixed_pa.lis_inter = 0x000a;

    packet.w_manage.tag_pa.SSID.tag_len = 0x15;

    packet.w_manage.tag_pa.s_rate.tag_num = 0x01;
    packet.w_manage.tag_pa.s_rate.tag_len = 0x08;


    while(1) {
        int res = pcap_sendpacket(handle,reinterpret_cast<const u_char*>(&packet),sizeof(Association_Packet));
        cout << "Packet  " << j << endl;
        j++;
        if (res != 0) {
            fprintf(stderr, "pcap_sendpacket return %d error=%s\n", res, pcap_geterr(handle));
            break;

        }
        usleep(100000);
    }
    //free(ssid);
    pcap_close(handle);
    cout << "Success!!\n";
}
