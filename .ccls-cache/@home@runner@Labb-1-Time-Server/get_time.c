#include <stdio.h>
#include <time.h>

int main(void) {
  time_t seconds;
  // Get time
  seconds = time(NULL);

  int test = (int)seconds;
  printf("Num size: %ld\n", sizeof(test));

  printf("The time is : %d\t%s\n", (int)seconds, ctime(&seconds));
  return 0;
}