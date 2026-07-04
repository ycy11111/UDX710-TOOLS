#include <stdio.h>
#include <unistd.h>

int main() {
  printf("=== MINIMAL TEST ===\n");
  fprintf(stderr, "stderr message\n");
  sleep(10);
  printf("exiting\n");
  return 0;
}
