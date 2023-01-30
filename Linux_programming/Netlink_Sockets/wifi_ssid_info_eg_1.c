#include <stdio.h>
#include <netlink/netlink.h>
#include <netlink/genl/genl.h>
#include <netlink/genl/family.h>
#include <netlink/genl/ctrl.h>
#include <net/if.h>

#include "nl80211.h"

static int nl80211_family_id;

static int print_ssid(struct nl_msg* msg, void* arg)
{
	/* Parse the genlmsghdr from nlmsghdr */
	/* nlmsghdr returns the netlink message header which contains  message type, flags, and sequence number etc */
	/* nlmsg_data Pointer to start of message payload. */
	struct nlmsghdr* ret_hdr = nlmsg_hdr(msg);
	/* netlink attribute structure for wifi there all lot of attributes again check nl80211.h*/
	struct nlattr *tb_msg[NL80211_ATTR_MAX + 1];

    if (ret_hdr->nlmsg_type != nl80211_family_id)
    {
        // what is this??
        return NL_STOP;
    }
	struct genlmsghdr *gnlh = (struct genlmsghdr*) nlmsg_data(ret_hdr);

	/* nla_parse function is used to parse and extract the attributes of a netlink message. */
	nla_parse(tb_msg, NL80211_ATTR_MAX, genlmsg_attrdata(gnlh, 0), genlmsg_attrlen(gnlh, 0), NULL);	

	if (tb_msg[NL80211_ATTR_IFNAME]) {
		printf("Interface = %s\n", nla_get_string(tb_msg[NL80211_ATTR_IFNAME]));
	}

	if (tb_msg[NL80211_ATTR_SSID]) {
		printf("SSID = ");
		int ssid_len = nla_len(tb_msg[NL80211_ATTR_SSID]);
		char* ptr = nla_data(tb_msg[NL80211_ATTR_SSID]);
		for (int i = 0; i < ssid_len; i++) {
			printf("%c", ptr[i]);
		}
		printf("\n");
	}

	for (int i = 0; i < NL80211_ATTR_MAX; i++) {
		if (tb_msg[i]) {
			printf("Some info is there at %d\n", i);
		}
	}
	return 0;
}

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, "%s wlan0", argv[0]);
		exit(1);
	}
	/* Create a netlink socket */
	struct nl_sock *nl_sock = nl_socket_alloc();
	if (nl_sock == NULL) {
		fprintf(stderr, "Failed to allocate netlink socket.\n");
		return -1;
	}

	/* Connect the socket with kernel */
	if (genl_connect(nl_sock)) {
		fprintf(stderr, "Failed to connect to generic netlink.\n");
		exit(1);
	}

	/* Set the send and receive sockets buffer size */
	nl_socket_set_buffer_size(nl_sock, 8192, 8192);

	/* Get the family id will be used later for */
	nl80211_family_id = genl_ctrl_resolve(nl_sock, "nl80211");

	if (nl80211_family_id < 0) {
		fprintf(stderr, "nl80211 not found.\n");
		exit(1);
	}

	/* Call you own callback when an event occurs such as message received 
	 * In this case print_ssid is going to be called
	 */
	nl_socket_modify_cb(nl_sock,  NL_CB_VALID, NL_CB_CUSTOM, print_ssid, NULL);
	
	/* Create a netlink message that is going to be sent to kernel requesting interface DUMP */
	struct nl_msg* msg = nlmsg_alloc();

	unsigned int if__index = if_nametoindex(argv[1]);
	if (if__index < 0) {
		fprintf(stderr, "interface not found\n");
		exit(1);
	}

	enum nl80211_commands cmd = NL80211_CMD_GET_INTERFACE;
	int flags = 0;
	/* Add generic netlink message header to the netlink messge */
	genlmsg_put(msg, NL_AUTO_PORT, NL_AUTO_SEQ, nl80211_family_id, 0, flags, cmd, 0);

	/* Add some message attributes like interface index of wlanX interface
	 * else the NL80211_CMD_GET_INTERFACE will dump all wifi interfaces
	 * You can add attributes only after adding generic netlink message header if the
	 * below code moved above line 83 you wont get expected result
	 */
	NLA_PUT_U32(msg, NL80211_ATTR_IFINDEX, if__index);
		
	/* Send the message */
	nl_send_auto(nl_sock, msg);
	printf("Message sent\n");
	/* Recevie the damn messagenl_recvmsgs_default*/
	nl_recvmsgs_default(nl_sock);

nla_put_failure:
	/* free the message */
	nlmsg_free(msg);
	/* free socket */
	nl_socket_free(nl_sock);
	return 1;

}
