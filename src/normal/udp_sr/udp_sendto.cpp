#include"udp_sr.h"

int main(int argc, char *argv[]){

    const char *ip=argv[1];
    int port=atoi(argv[2]);
    int sockfd,ret,num;
    struct sockaddr_in svaddr,claddr;

    if(argc<=2){
        errExit("usage; %s ip_addr ip_port \n",basename(argv[0]));
    } 

    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0){
        errExit("The socket creation in client side failed");
    }

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

    close(sockfd);
    return 0;
}
