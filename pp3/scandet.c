#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <map>

using namespace std;

typedef struct key{
  long src;
  long dest;
}keys_t;

typedef struct synInfo{
  long src;
  long dest;
  int srcPort;
  int destPort;
  int seq;
}synInfo_t;

typedef struct value{
  int syns;
  int synacks;  
}value_t;

class keyComp {
  public:
  bool operator() (const keys_t &A, const keys_t &B) const
  {return A.src<B.src;}
};

class synComp {
  public:
   bool operator() (const synInfo_t &A, const synInfo_t &B) const
   {return A.seq<B.seq;}
};

typedef map<keys_t, value_t, keyComp> map_t;
typedef map<synInfo_t, bool, synComp> syn_t;


/*Functions*/

void Report(map_t &map, syn_t &syns){
  //go through connections and report any ratios above 3
  printf("number of unique syns is: %d\n", (int)syns.size());
}

void UpdateMap(map_t &map, syn_t &syns, struct ip  *ip_hdr, struct tcphdr *tcp_hdr){
  //printf("flags in binary of packet is: %x", tcp_hdr->th_flags);
  if((TH_SYN & tcp_hdr->th_flags) && !(TH_ACK & tcp_hdr->th_flags)){
    synInfo_t curSyn = {ip_hdr->ip_src.s_addr, ip_hdr->ip_dst.s_addr, tcp_hdr->th_sport, tcp_hdr->th_dport, tcp_hdr->th_seq};
    //determine if already seen in syns
    //printf("syn found\n");
    if(syns.count(curSyn) < 1){
      //if not seen add to syns
      syns.insert(pair<synInfo_t, bool>(curSyn, 1));
      //printf("inserted syn\n");
      //increment syns in correct struct of map
      keys_t key = {ip_hdr->ip_src.s_addr, ip_hdr->ip_dst.s_addr};
      if(map.count(key) < 1){
        //insert new pair
      }else{
        //find and increment
      } 
    }
  }else if(TH_ACK & tcp_hdr->th_flags){
    //do stuff with ack 
  }
}

void ReadPacketData(pcap_t *file, map_t &map, syn_t &syns){
  const u_char *packet;
  struct pcap_pkthdr h;
  packet = pcap_next(file, &h);
  while(packet != NULL){
    struct ip *ip_hdr = (struct ip*) (packet+14); // 14 is the offset for the Ethernet header
    struct tcphdr *tcp_hdr = (struct tcphdr*) (packet + 14 + ip_hdr->ip_hl * 4);
    UpdateMap(map, syns, ip_hdr, tcp_hdr);
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
  syn_t syns;
  pcap_t *trace;
  trace = OpenFile(argv[1]);
  ReadPacketData(trace, connections, syns);
  Report(connections, syns);
  exit(0);
}
