What is NAT ?
=============
NAT (Network Address Translation) is a networking technique that is used to allow devices on a private network to communicate with the internet. It is commonly used in home and small business networks to allow multiple devices to share a single public IP address.

In a NAT configuration, a router or other networking device is configured to act as a gateway between the private network and the internet. The NAT device translates the private IP addresses of the devices on the private network to a single public IP address that is used to communicate with the internet.

There are several different types of NAT, including:

- Static NAT: This type of NAT maps a specific private IP address to a specific public IP address.
- Dynamic NAT: This type of NAT assigns a public IP address to a private IP address from a pool of available addresses.
- Port Address Translation (PAT): This type of NAT allows multiple devices on a private network to share a single public IP address by using different port numbers. This is also called Overloading.

NAT is useful because it allows devices on a private network to access the internet without requiring a unique public IP address for each device. It also provides a level of security by hiding the private IP addresses of the devices on the network from the internet.


NAT operates in which layer ?
=============================
NAT operates at the network layer (layer 3) of the OSI model. The network layer is responsible for routing and forwarding data packets between devices on a network.

NAT works by translating the IP addresses and port numbers of the packets being transmitted between the private network and the internet. It intercepts packets that are being transmitted between the private network and the internet, translates the private IP addresses and port numbers to a public IP address and port number, and then forwards the packets to their destination.

NAT is often implemented on a router or other networking device that acts as a gateway between the private network and the internet. It is typically used to allow devices on a private network to communicate with the internet without requiring a unique public IP address for each device.




When would you use static NAT versus dynamic NAT?
=================================================
Static NAT and dynamic NAT are two types of NAT that are used to allow devices on a private network to communicate with the internet.

Static NAT maps a specific private IP address to a specific public IP address. It is typically used when a device on a private network needs to be accessible from the internet on a consistent basis, such as a web server or a mail server.
Keep in mind that the static version requires you to have one real Internet IP address for every host on your network.

Dynamic NAT assigns a public IP address to a private IP address from a pool of available addresses. It is typically used when there are more devices on a private network than there are available public IP addresses.

In general, static NAT is preferred over dynamic NAT when possible because it allows devices on a private network to initiate communication with devices on the internet more easily. Dynamic NAT can cause problems with applications or services that rely on incoming connections, as it may not always be possible to determine which public IP address is currently mapped to a particular private IP address.

It is important to consider the needs of the network when deciding which type of NAT to use. Static NAT may be more suitable for networks with a small number of devices that need to be consistently accessible from the internet, while dynamic NAT may be more suitable for networks with a larger number of devices that do not need to initiate communication with the internet.


Some scenarios in which NAT is useful
======================================
- You need to connect to the Internet and your hosts don’t have globally unique IP addresses.
- You change to a new ISP that requires you to renumber your network. 
- You need to merge two intranets with duplicate addresses.
