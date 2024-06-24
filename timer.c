#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc != 2 && argc != 3) {
    printf("Usage: %s <seconds>\n", argv[0]);
    return 1;
  }

  time_t start = time(NULL);
  time_t runTime = 0;
  if (argc == 2) {
    runTime = atoi(argv[1]);
  } else if (argc == 3) {
    if (strcmp(argv[2], "s") == 0) {
      runTime = atoi(argv[1]);
    } else if (strcmp(argv[2], "m") == 0) {
      runTime = atoi(argv[1]) * 60;
    } else if (strcmp(argv[2], "h") == 0) {
      runTime = atoi(argv[1]) * 60 * 60;
    } else if (strcmp(argv[2], "d") == 0) {
      runTime = atoi(argv[1]) * 60 * 60 * 24;
    } else {
      printf("Invalid time unit\n");
      return 1;
    }
  }

  time_t end = start + runTime;

  while (time(NULL) < end) {
    printf("\033[2K");
    printf("\rTime remaining: %ld seconds", end - time(NULL));
    printf("\033]0;%ld s\007", end - time(NULL));
    fflush(stdout);
    usleep(100000);
  }

  return 0;
}
