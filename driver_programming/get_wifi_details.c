#include <stdio.h>
#include <string.h>
#include <math.h>
#include <linux/wireless.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/ethernet.h>

#define KILO 1e3
#define MEGA 1e6
#define GIGA 1e9

static inline __attribute__((always_inline)) int
iw_get_ext(int skfd,           /* Socket to the kernel */
           const char *ifname, /* Device name */
           int request,        /* WE ID */
           struct iwreq *pwrq) /* Fixed part of the request */
{
    /* Set device name */
    strncpy(pwrq->ifr_name, ifname, IFNAMSIZ);
    /* Do the request */
    return (ioctl(skfd, request, pwrq));
}


void iw_ether_ntop(const struct ether_addr * eth, char * buf)                                                                                        
{                                                                                                                       
    sprintf(buf, "%02X:%02X:%02X:%02X:%02X:%02X",                                                                         
            eth->ether_addr_octet[0], eth->ether_addr_octet[1],                                                               
            eth->ether_addr_octet[2], eth->ether_addr_octet[3],                                                               
            eth->ether_addr_octet[4], eth->ether_addr_octet[5]);                                                              
}

int main(int argc, char** argv)
{
    int ret = -1;
    char *ifname = argv[1];
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket opening failed\n");
        return -1;
    }

    
    struct iwreq wrq;

    ret = iw_get_ext(sockfd, ifname, SIOCGIWAP, &wrq);
#ifdef MYCOMMENTS 
    // iw_get_ext is just a handy wrapper if you dont want to use it. Below two lines has to done
    strncpy(wrq.ifr_name, ifname, IFNAMSIZ);
    ret = ioctl(sockfd, SIOCGIWAP, &wrq);
#endif

    if (ret < 0) {
        perror("Unable to get access point mac details\n");
        return -1;
    }

    /* Get AccessPoint Name */
    char ap_address[18] = {0};
    iw_ether_ntop((const struct ether_addr *)wrq.u.ap_addr.sa_data, ap_address);
#ifdef MYCOMMENTS
    // sa_data should be typecasted to type ether_addr else the results are weird
    // sameple weird op
    // Size of sd_data = 14
    // Size of ether_addr = 6
    // AP MAC = 30:49:50:2D:FFFFFFC1:FFFFFF9
    printf("Size of sd_data = %zu\n", sizeof(wrq.u.ap_addr.sa_data));
    printf("Size of ether_addr = %zu\n", sizeof(struct ether_addr));
    printf("AP MAC = %02X:%02X:%02X:%02X:%02X:%02X \n", 
                     wrq.u.ap_addr.sa_data[0], wrq.u.ap_addr.sa_data[1],
                     wrq.u.ap_addr.sa_data[2], wrq.u.ap_addr.sa_data[3],
                     wrq.u.ap_addr.sa_data[4], wrq.u.ap_addr.sa_data[5]);


#endif

    /* Get SSID Name */
    char ssid_name[32] = { 0 };
    wrq.u.essid.pointer = (void* )ssid_name; /* Step 1: Tell where the SSID to be stored. For some case this is not needed eg. getting frequency*/
    wrq.u.essid.length  = sizeof(ssid_name); /* Step 2: Tell the size of the buffer */
    wrq.u.essid.flags   = 0; /*Step 3: You can do anything with this flag, we are going to use it to check pass or fail */
    if (iw_get_ext(sockfd, ifname, SIOCGIWESSID, &wrq) < 0) {
        perror("Unable to get access point SSID NAME\n");
        wrq.u.essid.flags = 1;
    }

    /* Get Frequency channel */
    double freq = 0;
    int divisor = 0;
    char scale;
    if (iw_get_ext(sockfd, ifname, SIOCGIWFREQ, &wrq) < 0) {
        perror("Unable to get frequency\n");
    }

    freq = (wrq.u.freq.m) * pow(10, wrq.u.freq.e);
    if (freq >= GIGA) {
        divisor = GIGA;
        scale   = 'G';
    } else if(freq >= MEGA) {
        divisor = MEGA;
        scale   = 'M';
    } else {
        divisor = KILO;
        scale   = 'K';
    }


    printf("Interface Name = %s\n", wrq.ifr_name);
    printf("Access point mac: %s\n", ap_address);
    printf("SSID Name: %s\n", ssid_name);
    printf("Operating frequency: %lf %cHz\n", freq/divisor, scale);

    return 0;
}
