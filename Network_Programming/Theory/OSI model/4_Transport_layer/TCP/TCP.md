- TCP segments large amount of data from application later into segments (collection of bytes).
- Connection oriented
    - reliable
    - retransmits
- Full duplex
- Piggbacking
    - We have to Send acknowledgement whenever you receive a data
    - We will send ack along with data that is called piggybacking

- Error control
- Flow control

TCP header (20-60 bits)
========================

  0                   1                   2                   3
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |          Source Port          |       Destination Port        |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |                        Sequence Number                        |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |                    Acknowledgment Number                      |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |  Data |           |U|A|P|R|S|F|                               |
 | Offset| Reserved  |R|C|S|S|Y|I|            Window             |
 |       |           |G|K|H|T|N|N|                               |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |           Checksum            |         Urgent Pointer        |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |                    Options                    |    Padding    |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |                             data                              |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+


The TCP header consists of a number of fields that are used to control the transmission of data between the devices. The fields include:

- Source Port: The port number of the device that is sending the data.
- Destination Port: The port number of the device that is receiving the data.
- Sequence Number: A 32-bit number that is used to identify the order of the data being transmitted.
- Acknowledgment Number: A 32-bit number that is used to acknowledge the receipt of data.
- Data Offset: The number of 32-bit words in the TCP header.
- Reserved: A reserved field that is not used.
- Flags: A set of flags that are used to control the transmission of data.
- Window: The maximum amount of data that the device is willing to receive.
- Checksum: A 16-bit value that is used to detect errors in the data.
- Urgent Pointer: A 16-bit field that is used to indicate urgent data.
- Options: A field that is used to specify additional options for the transmission of data.
- Padding: A field that is used to pad the TCP header to a multiple of 32 bits.
- Data: The data being transmitted between the devices.


TCP connection establishment
==============================
FULL DUPLEX
Steps:
1. client sent TCP with SYN (sychronize)
2. server responds with SYN + ACK.
3. client sends ACK