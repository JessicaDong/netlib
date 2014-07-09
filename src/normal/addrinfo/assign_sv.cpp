#include"betaddrinfo.h"

int 
main(int argc, char *argv[]){

    struct addrinfo hints;


    bzero(&hints,sizeof(hints));
    hints.ai_canonname=NULL;
    hints.ai_addr=NULL;
    hints.next=NULL;
    hints.socktype=SOCK_STREAM;
    hints.ai_family=AF_UNSPEC;
    hints.ai_flags=AI_PASSIVE | AI_NUMERICSERV; 



    return 0;
}
