STP is spanning tree protol. This is L2 layer protocol.
Developed by DEC.

- In L2 there can be only one active link between two devices. STP forces the redundent link to blocked state.
- In case active link goes down it allows redundent link in the network to prevent network failure.
- Prevents layer 2 loop formation mainly and stop broadcast storm. It does this by selecting a single active path between two devices and disabling all other paths to those devices.
- Without STP, a loop could occur if two devices both try to transmit data to each other at the same time, causing a feedback loop that would flood the network with data. 



What is layer 2 loop:
=====================
          SW2
        /    \
PC1 - SW1------SW3 - PC2

Advantages:
===========
- Avoid Broadcast storm in layer 2 network.
- Avoid database inconsistency. Arp table having two or more entries
- Avoid duplicate copy of data transmission.  

There are a few disadvantages to using Spanning Tree Protocol (STP):
=====================================================================
- Slow convergence: STP can take a relatively long time to converge, meaning that it can take a while for the protocol to detect and disable redundant paths in the network. This can be a problem in environments where rapid network reconfiguration is necessary.
- Limited scalability: STP is not designed to scale to very large networks, as the number of STP instances increases with the size of the network. This can lead to performance issues in large networks.
- Limited flexibility: STP is designed to prevent loops, but it does not offer much flexibility in terms of controlling how traffic is routed through the network.
- Complex configuration: STP requires careful configuration to ensure that it functions correctly and does not cause network outages. This can be complex and time-consuming, particularly in large networks.


STP DS:
=======
Spanning Tree Protocol (STP) uses a data structure called a spanning tree to prevent loops in the network. A spanning tree is a tree-like data structure that represents the network topology and includes all of the devices in the network. It is used to ensure that there is only a single active path between any two devices in the network, preventing loops from forming.

The spanning tree data structure includes a root node, which is typically the central switch in the network, and a series of child nodes that represent the other devices in the network. Each child node is connected to the root node by a single active path, and all other paths to the child nodes are disabled. This ensures that there is only one active path between each child node and the root node, preventing loops from forming.

STP uses the spanning tree data structure to determine which paths should be active and which should be disabled in order to prevent loops. It periodically sends messages between devices to update the spanning tree data structure and ensure that it accurately reflects the current state of the network. This helps to ensure that the network remains stable and reliable even if there are changes in the network topology.

STP components:
================
- Root bridge (RB): One among all the switches in the network will be selected as Root bridge and this bridge will provide interconnection to all other bridges. Root bridge is automatically selected by STP or the network admin can also select root bridge if needed.
- Non Root bridge (NRB): Bridge other than root bridge
- Root port: 
    - A port in NRB that leads to RB. It will have low cost to RB.
    - RB does not need root port.
    - But every NRB must have root port.
- Designated port: 
    - Every NRB will receive frames from the DP and forward the same through its Root port towards the root bridge
- BPDU  All the switches exchange information to use in the selection of the root switch as well as in subsequent configuration of the network. Each switch compares the parameters in the Bridge Protocol Data Unit (BPDU) that it sends to one neighbor with the ones that it receives from other neighbors.
Types
    1. Configuration BPDU
    2. TCN (Topology change notification) BPDU

- Bridge ID  The bridge ID is how STP keeps track of all the switches in the network. It is determined by a combination of the bridge priority (32,768 by default on all Cisco switches) and the base MAC address. The bridge with the lowest bridge ID becomes the root bridge in the network.

- Path cost: The path cost is typically calculated based on the speed of the link between the two devices. Faster links typically have a lower path cost, while slower links have a higher path cost. For example, a Gigabit Ethernet link might have a lower path cost than a 100 Megabit Ethernet link.

The specific formula for calculating the path cost varies depending on the version of STP being used and the type of link being used. For example, in the original version of STP (IEEE 802.1D), the path cost for an Ethernet link was calculated as:

Path Cost = 10000 / Link Speed (in Megabits per second)

For example, a 100 Megabit Ethernet link would have a path cost of 100, while a 1 Gigabit Ethernet link would have a path cost of 10.


STP working steps:
==================
1. Root bridge selection
2. Root port selection.
3. Selecting desginated and non designated port
