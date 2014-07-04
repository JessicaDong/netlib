#include"tcp_sr.h"

int main(int argc, char *argv[]){

    const char *ip=argv[1];
    int port=atoi(argv[2]);
    int sockfd,ret,num;
    struct sockaddr_in addr,cli_addr;

    if(argc<=2){
        errExit("usage; %s ip_addr ip_port \n",basename(argv[0]));
    }

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        errExit("The server socket creation process failed");
    }

    bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    inet_pton(AF_INET,ip,&addr.sin_addr); 
    
    ret=bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));
    if(ret<0){
        errExit("The bind process failed");
    }

    ret=listen(sockfd,5);
    if(ret<0){
        errExit("The listen process failed");
    }

    socklen_t addrlen=sizeof(cli_addr);
    ret=accept(sockfd,(struct sockaddr *)&cli_addr,&addrlen);
    if(ret<0){
        errExit("The accept process failed");
    }
    
    char buffer[BUF_SIZE];
    memset(buffer,'\0',BUF_SIZE);
    printf("-------Test MSG_OOB FIELD--------\n");
    num=recv(ret,buffer,BUF_SIZE-1,0);
    printf("got %d bytes of normal data : %s \n",num,buffer);
   
    memset(buffer,'\0',BUF_SIZE);
    num=recv(ret,buffer,BUF_SIZE-1,MSG_OOB);
    printf("got %d bytes of  oob data : %s \n",num,buffer);

    memset(buffer,'\0',BUF_SIZE);
    num=recv(ret,buffer,BUF_SIZE-1,0);
    printf("got %d bytes of  oob data : %s \n",num,buffer);


    close(ret);

    close(sockfd); 
 
    return 0;
}
