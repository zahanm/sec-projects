
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <map>

using namespace std;

typedef struct key{
  long src;
  long dest;
  int srcPort;
  int destPort;
}keys_t;

typedef struct packetInfo{
  long src;
  long dest;
  int srcPort;
  int destPort;
  int seq;
} packetInfo_t;

typedef struct value{
  int syns;
  int synacks;
  bool warned;
}value_t;

class keyComp {
  public:
  bool operator() (const keys_t &A, const keys_t &B) const
  {return A.src<B.src;}
};

class packetComp {
  public:
   bool operator() (const packetInfo_t &A, const packetInfo_t &B) const
   {return A.seq<B.seq;}
};

typedef map<keys_t, value_t, keyComp> map_t;
typedef map<packetInfo_t, bool, packetComp> packetmap_t;


/*Functions*/

void Report(map_t &map, packetmap_t &syns, packetmap_t &synacks){
  //go through connections and report any ratios above 3
  printf("number of unique syns is: %d\n", (int)syns.size());
  printf("number of unique synacks is: %d\n", (int)synacks.size());
  printf("number of unique ipdst pairs is: %d\n", (int)map.size());
}

void PrintPacketSrcDest(struct ip  *ip_hdr, struct tcphdr *tcp_hdr) {
  printf("%d.%d.%d.%d", (ip_hdr->ip_src.s_addr) & 0xff, (ip_hdr->ip_src.s_addr >> 8) & 0xff, (ip_hdr->ip_src.s_addr >> 16) & 0xff, (ip_hdr->ip_src.s_addr >> 24) & 0xff);
  printf(" %d.%d.%d.%d\n", (ip_hdr->ip_dst.s_addr) & 0xff, (ip_hdr->ip_dst.s_addr >> 8) & 0xff, (ip_hdr->ip_dst.s_addr >> 16) & 0xff, (ip_hdr->ip_dst.s_addr >> 24) & 0xff);
}

void CheckRatio( map_t::iterator it ) {
  if ( !it->second.warned ) {
    // printf("syns %d synacks %d\n", it->second.syns, it->second.synacks);
    if ( it->second.synacks == 0 && it->second.syns > 3) {
      printf( "Warning, syns to synacks ratio exceeded.\n");
      printf( "A malicious agent might be \'scanning\' the network.\n");
      it->second.warned = true;
    }
    else if ( it->second.synacks > 0 && ( (float) it->second.syns / it->second.synacks ) > 3 ) {
      printf( "Warning, syns to synacks ratio exceeded.\n");
      printf( "A malicious agent might be \'scanning\' the network.\n");
      it->second.warned = true;
    }
  }
}

void UpdateMap(map_t &map, packetmap_t &syns, packetmap_t &synacks, struct ip  *ip_hdr, struct tcphdr *tcp_hdr){
  //printf("flags in binary of packet is: %x", tcp_hdr->th_flags);
  packetInfo_t curPacket = {ip_hdr->ip_src.s_addr, ip_hdr->ip_dst.s_addr, ntohs(tcp_hdr->th_sport), ntohs(tcp_hdr->th_dport), tcp_hdr->th_seq};
  map_t::iterator it;
  if ( (TH_SYN & tcp_hdr->th_flags) && !(TH_ACK & tcp_hdr->th_flags) ) {
    //determine if already seen in syns
    //printf("syn found\n");
    if (syns.count(curPacket) < 1) {
      //if not seen add to syns
      syns.insert(pair<packetInfo_t, bool>(curPacket, 1));
      //printf("inserted syn\n");
      //increment syns in correct struct of map
      keys_t key = {ip_hdr->ip_src.s_addr, ip_hdr->ip_dst.s_addr, ntohs(tcp_hdr->th_sport), ntohs(tcp_hdr->th_dport)};
      if (map.count(key) < 1) {
        //insert new pair
        // printf("Adding %ld: %d => %ld: %d to src-dst map\n", key.src, key.srcPort, key.dest, key.destPort);
        value_t val = {0,0,false};
        map.insert(pair<keys_t,value_t>(key,val));
      }
      //find and increment
      it = map.find(key);
      it->second.syns++;
      CheckRatio(it);
    }
  } else if ( (TH_SYN & tcp_hdr->th_flags) && (TH_ACK & tcp_hdr->th_flags) ) {
    //do stuff with syn-ack
    if (synacks.count(curPacket) < 1) {
      // de-duplicated synacks too
      synacks.insert(pair<packetInfo_t, bool>(curPacket, 1));
      keys_t key = {ip_hdr->ip_dst.s_addr, ip_hdr->ip_src.s_addr, ntohs(tcp_hdr->th_dport), ntohs(tcp_hdr->th_sport)};
      //find and increment
      it = map.find(key);
      it->second.synacks++;
      CheckRatio(it);
    }
  }
}

void ReadPacketData(pcap_t *file, map_t &map, packetmap_t &syns, packetmap_t &synacks){
  const u_char *packet;
  struct pcap_pkthdr h;
  packet = pcap_next(file, &h);
  while(packet != NULL){
    struct ip *ip_hdr = (struct ip*) (packet+14); // 14 is the offset for the Ethernet header
    struct tcphdr *tcp_hdr = (struct tcphdr*) (packet + 14 + ip_hdr->ip_hl * 4);
    PrintPacketSrcDest(ip_hdr, tcp_hdr);
    UpdateMap(map, syns, synacks, ip_hdr, tcp_hdr);
    packet = pcap_next(file, &h);
  }
}

pcap_t *OpenFile(const char *fname){
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t *file;
  file = pcap_open_offline(fname, errbuf);
  if(file == NULL){
    printf("%s\n", errbuf);
    exit(1);
  }
  return file;
}

int main(int argc, const char *argv[]){
  if(argc < 2){
    printf("Please provide a trace file to analyze.\n");
    exit(0);
  }
  map_t connections;
  packetmap_t syns;
  packetmap_t synacks;
  pcap_t *trace;
  trace = OpenFile(argv[1]);
  ReadPacketData(trace, connections, syns, synacks);
  Report(connections, syns, synacks);
  exit(0);
}
