#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <time.h>

#define PORT 37
#define BUF_SIZE 4

int main(void) {

  int sckt;

  socklen_t addr_size;

  time_t *buf;

  struct sockaddr_in channel;

  sckt = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

  memset(&channel, 0, sizeof(channel));

  channel.sin_family = AF_INET;
  channel.sin_port = htons(PORT);

  // Convert ip address to binary form
  inet_pton(AF_INET, "127.0.0.1", &channel.sin_addr);

  addr_size = sizeof(struct sockaddr_in);

  printf("Client Started!\n");
  
  // Send empty datagram
  sendto(sckt, buf, 0, 0, (struct sockaddr *)&channel, sizeof(channel));
  
  uint32_t packet;
  time_t seconds;
  
  // Receive time in datagram
  recvfrom(sckt, &packet, sizeof(uint32_t), 0, (struct sockaddr *)&channel, &addr_size);

  // Network bitorder to host
  seconds = (time_t)ntohl(packet) - 2208988800;
  
  // Handle time in datagram (buf)
  printf("%s\n", ctime(&seconds));
  return 0;
}