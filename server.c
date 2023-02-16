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

  b = bind(sckt, (struct sockaddr *)&channel, sizeof(channel));
  if (b < 0) {
    perror("Binding failed");
    return -1;
  }

  printf("Server Started!\n");
  
  addr_size = sizeof(channel);

  while(1){

    // Wait for empty datagram
    recvfrom(sckt, buf, 0, 0, (struct sockaddr *)&channel, &addr_size);

    struct tm start_time; // 00:00 Jan 1 1900
    start_time.tm_hour = 0;
    start_time.tm_sec = 0;
    start_time.tm_mon = 0; // Jan
    start_time.tm_yday = 0;
    start_time.tm_mday = 1;
    start_time_late.tm_year = 0;

     struct tm start_time_late; // 00:00 Jan 1 1900
    start_time_late.tm_hour = 0;
    start_time_late.tm_sec = 0;
    start_time_late.tm_mon = 0; // Jan
    start_time_late.tm_yday = 0;
    start_time_late.tm_mday = 1;
    start_time_late.tm_year = 70;

    // convert to time_t
    time_t t1 = mktime(&start_time);
    time_t t2 = mktime(&start_time_late);

    double diff_time = difftime(t2, t1);


    time_t ti = time(NULL);

    struct tm *a;
  
    a = localtime(&ti);

    time_t p = mktime(a);

    

    time_t current_time = time(NULL); // Feb 16 2023 (time between (1900 + 70) years and 2023)

    // Get time in seconds and cast to int (4 bytes)
    //int32_t seconds = (int32_t)time(NULL) - (int32_t)2208988800;
    //time_t local = time(NULL);
    //printf("Connection received, seconds: %d, local time: %s\n", seconds, ctime(&local));

    int32_t packet = htonl(p);
    
    // Host bitorder to network
    //int32_t packet = htonl(seconds);
  
    // Send time    
    sendto(sckt, &packet, sizeof(int32_t), 0, (struct sockaddr *)&channel, addr_size);
  }

  return 0;
}