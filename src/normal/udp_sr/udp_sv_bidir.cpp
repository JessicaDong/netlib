#include"udp_sr.h"

int
main(int argc, char *argv[]){

    const char *ip=argv[1];
    int port=atoi(argv[2]);
    int sockfd,ret,num;
    struct sockaddr_in svaddr,claddr;

    if(argc<=2){
        errExit("usage; %s ip_addr ip_port \n",basename(argv[0]));
    }

    sockfd=socket(AF_INET,SOCK_DGRAM,0); 
    if(sockfd<0){
        errExit("The socket creation in server side failed");
    } 

    bzero(&svaddr,sizeof(svaddr));
    svaddr.sin_family=AF_INET;
    svaddr.sin_port=htons(port);
    inet_pton(AF_INET,ip,&svaddr.sin_addr);
    ret=bind(sockfd,(struct sockaddr *)&svaddr,sizeof(svaddr));
    if(ret<0){
        errExit("The bind process faied");
    }

    char buf[BUF_SIZE];
    socklen_t len=sizeof(claddr);
    ret=recvfrom(sockfd,buf,BUF_SIZE,0,(struct sockaddr *)&claddr,&len);
    if(ret<0){
        errExit("Receive no data.");
    }
    else{
        printf("receive : %d bytes.  %s\n",ret,buf);
    }
    
    int i=0;
    for(;i<ret;++i)
        buf[i]=toupper(buf[i]);

    if(sendto(sockfd,buf,ret,0,(struct sockaddr *)&claddr,len)!=ret)
        errExit("Sending failed data");
    else{
        printf("Echo: %s\n",buf);
    } 

    close(sockfd);
    return 0;    
}
