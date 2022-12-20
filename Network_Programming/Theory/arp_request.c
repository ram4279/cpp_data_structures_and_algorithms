#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <netpacket/packet.h>

#define ARP_REQUEST 1
#define ARP_REPLY 2

struct arphdr {
  uint16_t htype;
  uint16_t ptype;
  uint8_t hlen;
  uint8_t plen;
  uint16_t opcode;
  uint8_t sender_mac[6];
  uint8_t sender_ip[4];
  uint8_t target_mac[6];
  uint8_t target_ip[4];
};

int main(int argc, char *argv[]) {
  int sockfd;
  struct sockaddr_ll dest_addr;
  struct arphdr *arp_header;
  struct ifreq if_idx;
  struct ifreq if_mac;
  char buffer[64];
  int broadcast_perm = 1;

  // Create a raw socket
  sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
  if (sockfd < 0) {
    perror("Failed to create socket");
    exit(EXIT_FAILURE);
  }

  // Allow socket to send broadcast packets
  if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast_perm,
                 sizeof(broadcast_perm)) < 0) {
    perror("Failed to set socket options");
    exit(EXIT_FAILURE);
  }

  // Get the index of the interface to send the packet through
  memset(&if_idx, 0, sizeof(struct ifreq));
  strncpy(if_idx.ifr_name, "eth0", IFNAMSIZ-1);
  if (ioctl(sockfd, SIOCGIFINDEX, &if_idx) < 0) {
    perror("Failed to get interface index");
    exit(EXIT_FAILURE);
  }

  // Get the MAC address of the interface to send the packet through
  memset(&if_mac, 0, sizeof(struct ifreq));
  strncpy(if_mac.ifr_name, "eth0", IFNAMSIZ-1);
  if (ioctl(sockfd, SIOCGIFHWADDR, &if_mac) < 0) {
    perror("Failed to get interface MAC address");
    exit(EXIT_FAILURE);
  }

  // Construct the destination address
  memset(&dest_addr, 0, sizeof(struct sockaddr_ll));
  dest_addr.sll_ifindex = if_idx.ifr_ifindex;
  dest_addr.sll_family = AF_PACKET;
  // Set the destination MAC address to the broadcast address
  memset(dest_addr.sll_addr, 0xff, 6);

  // Fill in the buffer with the ARP request packet
  arp_header = (struct arphdr *) buffer;
  arp_header->htype = htons(1);
  arp_header->ptype = htons(ETH_P_IP);
  arp_header->hlen = 6;
  arp_header->plen = 4;
  arp_header->opcode = htons(ARP_REQUEST);
  memcpy(arp_header->sender_mac, if_mac.ifr_hwaddr.sa_data, 6);
  memcpy(arp_header->sender_ip, "\x0a\x00\x00\x01", 4); // 10.0.0.1
  memset(arp_header->target_mac, 0, 6);
  memcpy(arp_header->target_ip, "\x0a\x00\x00\x02", 4); // 10.0.0.2

  // Send the ARP request packet
  if (sendto(sockfd, buffer, sizeof(struct arphdr), 0,
             (struct sockaddr *) &dest_addr, sizeof(struct sockaddr_ll)) < 0) {
    perror("Failed to send packet");
    exit(EXIT_FAILURE);
  }

  return 0;
}
