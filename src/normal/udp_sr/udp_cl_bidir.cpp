#include"udp_sr.h"

int
main(int argc, char *argv[]){

    const char *ip=argv[1], *clip=argv[3];
    int port=atoi(argv[2]), clport=atoi(argv[4]);
    int sockfd,ret,num;
    struct sockaddr_in svaddr,claddr;

    if(argc<=2){
        errExit("The argument numbers are not met.");
    } 

    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0){
        errExit("The socket creation in client side failed");
    }
//    uncomment these lines will bind a certain port, 
//    or bind a temp port that provided by argv.
//    bzero(&claddr,sizeof(claddr));
//    claddr.sin_family=AF_INET;
//    claddr.sin_port=htons(clport);
//    inet_pton(AF_INET,clip,&claddr.sin_addr);
//    ret=bind(sockfd,(struct sockaddr *)&claddr,sizeof(claddr));
//    if(ret<0)
//        errExit("Bind process at client side failed");


    bzero(&svaddr,sizeof(svaddr));
    svaddr.sin_family=AF_INET;
    svaddr.sin_port=htons(port);
    inet_pton(AF_INET,ip,&svaddr.sin_addr);

    const char *data="Sending UDP data.";
    ret=sendto(sockfd,data,strlen(data),0,(struct sockaddr *)&svaddr,sizeof(svaddr));    
    if(ret<0){
        errExit("Sending data failed");
    }else{
        printf("send %d bytes: %s \n", ret,data);
    }


    char rece[BUF_SIZE];
    socklen_t len=sizeof(svaddr);
    ret=recvfrom(sockfd,rece,BUF_SIZE,0,(struct sockaddr *)&svaddr,&len);
    if(ret<0)
        errExit("Receive data from server failed");
    else
        printf("Receive data from server: %d bytes. %s \n",ret,rece);

    close(sockfd);
    return 0;
}
