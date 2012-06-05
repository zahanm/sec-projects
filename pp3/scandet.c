#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>

void ReadPacketData(pcap_t *file){
  const u_char *packet;
  struct pcap_pkthdr h;
  packet = pcap_next(file, &h);
  while(packet != NULL){
    struct ip *ip_hdr = (struct ip*) (packet+14); // 14 is the offset for the Ethernet header
    struct tcphdr *tcp_hdr = (struct tcphdr*) (packet + 14 + ip_hdr->ip_hl * 4);
  }
}

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
  ReadPacketData(trace);
  exit(0);
}
