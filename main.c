#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/wireless.h>
#include <stdlib.h>

#define MAXDBM 20

int main(int argc, char const *argv[])
{
    int sfd; 

    struct iwreq wrq;
    struct iw_statistics stats;

    if((sfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Nieudana próba stworzenia socket'u");
        exit(EXIT_FAILURE);
    }
    
    memset(&wrq, 0, sizeof(wrq)); 
    memset(&stats, 0, sizeof(stats)); 
    strncpy(wrq.ifr_name, argv[1], IFNAMSIZ);

    wrq.u.data.pointer = &stats;
    wrq.u.data.length = sizeof(stats);

	
	ioctl(sfd, SIOCGIWSTATS, &wrq);


    int value = atoi(argv[2]);
    if (value > 100) value = 100;
    else if(value < 0) value = 0;
    
    ioctl(sfd, SIOCGIWTXPOW, &wrq);
    int startvalue = wrq.u.txpower.value;
    
    value = MAXDBM * value / 100;        
    do{        
        if(startvalue<value){
            wrq.u.txpower.value++;
        }        
        else if(startvalue>value){
            wrq.u.txpower.value--;
        }        
            
        ioctl(sfd, SIOCSIWTXPOW, &wrq);
        sleep(1);
        ioctl(sfd, SIOCGIWTXPOW, &wrq);
        startvalue = wrq.u.txpower.value;
        printf("Obecna wartosc Tx-Power = %d dBm\n", wrq.u.txpower.value);
    }while(startvalue!=value);

    close(sfd);
    return 0;

}



