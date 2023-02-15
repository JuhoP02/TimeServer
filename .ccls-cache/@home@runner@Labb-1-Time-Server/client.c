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
#define BUF_SIZE 4096

int main(void) {

  int sckt;

  socklen_t addr_size;

  time_t *buf;

  struct sockaddr_in channel;

  sckt = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

  memset(&channel, 0, sizeof(channel));

  channel.sin_family = AF_INET;
  channel.sin_port = htons(PORT);

  inet_pton(AF_INET, "127.0.0.1", &channel.sin_addr);

  addr_size = sizeof(struct sockaddr_in);

  // Send empty datagram
  sendto(sckt, buf, BUF_SIZE, 0, (struct sockaddr *)&channel, sizeof(channel));

  // Receive time in datagram
  recvfrom(sckt, buf, BUF_SIZE, 0, (struct sockaddr *)&channel, &addr_size);

  // Handle time in datagram (buf)
  printf("%s\n", ctime(buf));
  printf("Client ended");
  return 0;
}