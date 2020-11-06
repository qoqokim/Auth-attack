## ethernet frame / dot11 frame

ethernet frame (802.3 frame)  /  dot11 frame (802.11 frame)



**802.3 frame** 

- Destination address, Source address

![image-20201104051220184](https://user-images.githubusercontent.com/59726658/98048236-a2b6ee00-1e70-11eb-8899-2bbe00fa403b.png)



**802.11 frame** 

- MAC 주소 지정이 ethernet frame 보다 복잡하다.
- MAC 헤더에 네개의 주소 필드가 존재한다.

![image-20201104051239312](https://user-images.githubusercontent.com/59726658/98048266-aea2b000-1e70-11eb-9e3f-21408453ef00.png)







## Authentication 

Type : 0x000b (1011)

Receiver add 

Detination add

Transmitter add

Source add

BSSId 



**Fixed parameters (6 byte)**

- authentication algorithm (0x0000)
- authentication SEQ (0x0002)
- status code (0x0000)

**Tagged parameters (11 byte)**

- Tag Number : 0xdd
- Tag length : 0x09
- OUI : 00:10:18 (Broadcom)
- vendor OUI type : 0x02
- vendor data : ......





## Association request

Type : 0x0000 (0000)

Receiver add 

Detination add

Transmitter add

Source add

BSSId 



**Fixed parameters (4 byte)**

- capabilities information : 0x1531 (2byte)
- Listen interval : 0x000a (2byte)

**Tagged parameters**

    packet.w_manage.tag_pa.s_rate.s_r[0]=0x82;
    packet.w_manage.tag_pa.s_rate.s_r[1]=0x84;
    packet.w_manage.tag_pa.s_rate.s_r[2]=0x8b;
    packet.w_manage.tag_pa.s_rate.s_r[3]=0x96;
    packet.w_manage.tag_pa.s_rate.s_r[4]=0x24;
    packet.w_manage.tag_pa.s_rate.s_r[5]=0x30;
    packet.w_manage.tag_pa.s_rate.s_r[6]=0x48;
    packet.w_manage.tag_pa.s_rate.s_r[7]=0x6c;




## Association response

Type : 0x0000 (0001)

Receiver add 

Detination add

Transmitter add

Source add

BSSId 



**Fixed parameters (6 byte)**

- capabilities information : 0x0431 (2byte)
- status code : (2byte)
- association id : 0x01c0 (2byte)