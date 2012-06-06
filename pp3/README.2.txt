CS 155 Project 3 Part 2

Zahan Malkani: zahanm@stanford.edu
Megan Kanne: mkanne@stanford.edu

=====

Our implementation of Scan Detection uses a map to keep track of the connections and positive responses.  The first map contains keys which are structs containing {src_ip, dest_ip, src_port, dest_port} and values which are structs containing the number of syns, number of synacks, and a boolean value for whether a warning has already been printed.    

When a packet is read, if it is a syn packet, we increment the number of syns in the correct value struct of the first map.  If a synack packet is read, we ensure it can be matched to a syn then increment the number of synacks in the correct value.

We recalculate the ratio on every packet which is not optimal but does allow for a "live" implementation.

We handled division by zero by only counting a src-dest pair as scanning if the matching number of synacks is 0 and the number of syns > 3.  Basically, we determined a scan was occurring if many syns were being sent (maybe to a closed port) although the client recieved no responses.     