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

  inet_pton(AF_INET, "127.0.0.1", &channel.sin_addr);

  addr_size = sizeof(struct sockaddr_in);

  printf("Client Started!\n");
  
  // Send empty datagram
  printf("Sending to server!\n");
  sendto(sckt, buf, 0, 0, (struct sockaddr *)&channel, sizeof(channel));
  printf("Sending complete!\n");
  
  // Receive time in datagram
  printf("Waiting for return packet\n");
  recvfrom(sckt, buf, BUF_SIZE, 0, (struct sockaddr *)&channel, &addr_size);
  printf("Recieved packet!\n");
  
  // Handle time in datagram (buf)
  printf("%s\n", ctime(buf));
  printf("Client ended");
  return 0;
}