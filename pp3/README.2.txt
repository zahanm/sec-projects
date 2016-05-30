Project 3 Part 2

Zahan Malkani: zahanm@stanford.edu
Megan Kanne: mkanne@stanford.edu

=====

Our implementation of Scan Detection uses a map to keep track of the ratios for each connection and another for the SYN packets already seen.

The first map contains keys which are structs containing {src_ip, dest_ip, src_port, dest_port} and values which are structs containing the number of syns, number of synacks, and a boolean value for whether a warning has already been printed.

The second, a tuple of {src_ip, dest_ip, src_port, dest_port, seq_number} where the sequence number will be matched with the acknowledgment number to see if the SYN and SYN_ACK matches.

When a packet is read, if it is a syn packet, we increment the number of syns in the correct ratio struct of the first map.  If a synack packet is read, we ensure it can be matched to a syn by checking the second map then increment the number of synacks in the correct ratio struct.

We recalculate the ratio on every packet and print a warning if the ratio is exceeded which is not optimal but does allow for a "live" implementation.

We handled division by zero by waiting for the number of syns to exceed 3 before printing a warning while there are still zero valid synacks registered for that connection pair.
