## ethernet frame / dot11 frame

ethernet frame (802.3 frame)  /  dot11 frame (802.11 frame)



**802.3 frame** 

- Destination address, Source address

![image-20201104051220184](C:\Users\jin36\AppData\Roaming\Typora\typora-user-images\image-20201104051220184.png)



**802.11 frame** 

- MAC 주소 지정이 ethernet frame 보다 복잡하다.
- MAC 헤더에 네개의 주소 필드가 존재한다.

![image-20201104051239312](C:\Users\jin36\AppData\Roaming\Typora\typora-user-images\image-20201104051239312.png)







## authentication 

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





## association

Type : 0x0001 (0001)

Receiver add 

Detination add

Transmitter add

Source add

BSSId 



**Fixed parameters (6 byte)**

- capabilities information (0x0431)
- status code (0x0000)
- (0xc001)