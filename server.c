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
#define QUEUE_SIZE 10

int main(void) {
  int sckt, sckt_accept;
  char buf[BUF_SIZE];
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
    perror("Socket failed");
    return (-1);
  }

  // socket options?

  b = bind(sckt, (struct sockaddr *)&channel, sizeof(channel));
  if (b < 0) {
    perror("Binding failed");
    return -1;
  }

  printf("Server Started!\n");
  
  addr_size = sizeof(channel);

  // Receive empty packet from client
  printf("Waiting for packet from client!\n");
  recvfrom(sckt, buf, BUF_SIZE, 0, (struct sockaddr *)&channel, &addr_size);
  printf("Recieved packet from client!\n");

  // Get time in seconds and cast to int (4 bytes)
  int seconds = (int)time(NULL);

  // Send time
  printf("Sending time (%ld bytes) to client!\n", sizeof(seconds));
  sendto(sckt, (const void *)seconds, sizeof(seconds), 0, (struct sockaddr *)&channel, addr_size);
  printf("Sending done!\n");

  return 0;
}