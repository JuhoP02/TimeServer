#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT 37
#define BUF_SIZE 4096
#define QUEUE_SIZE 10

int main(void) {
  int sckt, sckt_accept;
  char *buf[BUF_SIZE];
  int b;
  int l;
  socklen_t addr_size;

  struct sockaddr_in channel;
  memset(&channel, 0, sizeof(channel));

  channel.sin_family = AF_INET;
  channel.sin_addr.s_addr = htonl(INADDR_ANY);
  channel.sin_port = htons(PORT);

  sckt = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sckt < 0) {
    perror("Socket failed\n");
    return (-1);
  }

  // socket options?

  b = bind(sckt, (struct sockaddr *)&channel, sizeof(channel));
  if (b < 0) {
    perror("Binding failed\n");
    return -1;
  }

  addr_size = sizeof(struct sockaddr_in);

  recvfrom(sckt, buf, BUF_SIZE, 0, (struct sockaddr *)&channel, &addr_size);

  // Get time

  sendto(sckt, buf, BUF_SIZE, 0, (struct sockaddr *)&channel, addr_size);

  return 0;
}