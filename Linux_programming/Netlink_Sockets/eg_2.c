#include <stdio.h>
#include <netlink/genl/family.h>
#include <netlink/genl/ctrl.h>
#include <netlink/genl/genl.h>
#include <netlink/netlink.h>
#include <net/if.h>
#include "nl80211.h"

#define MAX_PARAMS 3

typedef enum commands
{
    WIFI_DUMP_INFO,
    WIFI_START_SCAN,
    WIFI_CMDS_END
} commands_t;

const char* commmands_str[WIFI_CMDS_END] = {
    [WIFI_DUMP_INFO]  = "info",
    [WIFI_START_SCAN] = "scan",
};

int main(int argc, char const *argv[])
{
    if (argc != MAX_PARAMS) {
        fprintf(stderr, "%s wlan0 info\n", argv[0]);
        fprintf(stderr, "%s wlan0 scan\n", argv[0]);
        exit(1);
    }

    commands_t input_cmd = WIFI_CMDS_END;
    for (int i = 0; i < WIFI_CMDS_END; i++) {
        if (!strcmp(commmands_str[i], argv[2])) {
            input_cmd = i;
            break;
        }
    }

    if (input_cmd == WIFI_CMDS_END) {
        fprintf(stderr, "error cmd not found!!\n", argv[0]);
        exit(1);
    }

    struct nl_sock* nl_sk = nl_socket_alloc();
    genl_connect(nl_sk);

    int family_id = genl_ctrl_resolve(nl_sk, "nl80211");
    
    if (input_cmd == WIFI_START_SCAN) {
        handle_cmd_wifi_scan(sk, family_id);
    }


cleanup:
    return 1;
}
