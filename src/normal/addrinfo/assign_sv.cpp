#include"betaddrinfo.h"

int 
main(int argc, char *argv[]){

    struct addrinfo hints;
    struct addrinfo *res,*rp;
    struct sockaddr_storage claddr; /*adapt to IPV4 and IPV6*/
    int optval;
    int sockfd,ret;
    socklen_t addrlen;
    /*Ignore SIGPIPE, prevent unnormal close*/
    /* should use isgaction */
    if(signal(SIGPIPE,SIG_IGN==SIG_ERR))
        errExit("signal");

    bzero(&hints,sizeof(hints));
    hints.ai_canonname=NULL;
    hints.ai_addr=NULL;
    hints.next=NULL;
    hints.socktype=SOCK_STREAM;
    hints.ai_family=AF_UNSPEC;
    hints.ai_flags=AI_PASSIVE | AI_NUMERICSERV; 

    if(getaddrinfo(NULL,PORT,&hints,&res)!=0)
        errExit("getaddrinfo");
   
    optval=1;
    /* get a valid socket */
    for(rp=res;rp!=NULL;rp=rp->rp->ai_next){
        sockfd=socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
        if(sockfd==-1)
             continue;
    
        if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval))==-1){
            errExit("setsockopt");
        }

        if(bind(sockfd,rp->ai_addr,rp->addrlen)==0)
            break;

        close(sockfd);
    }

    if(rp==NULL)
         printf("Bind process failed");

    if(listen(sockfd,BACKLOG)==-1)
         errExit("listen");

    freeaddrinfo(result);

    while(1){
        
        addrlen=sizeof(claddr);
        ret=accept(ret,(struct sockaddr *)&claddr,&addrlen);
        if(ret==-1){
            printf("accept failed");
            continue;
        } 
    }

    return 0;
}
