#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>

pcap_t *OpenFile(const char *fname){
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t *file;
  file = pcap_open_offline(fname, errbuf);
  if(file == NULL){
    printf("%s", errbuf);
    exit(1); 
  }
  return file;
}

int main(int argc, const char *argv[]){
  if(argc < 2){
    printf("Please provide a trace file to analyze./n");
    exit(0);
  }
 pcap_t *trace;
 trace = OpenFile(argv[1]);
  
}
