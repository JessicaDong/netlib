#include"tcp_sr.h"

int main(int argc, char *argv[]){
    
    const char* ip=argv[1];    
    const int port=atoi(argv[2]);
    int sockfd,connfd;
    struct sockaddr_in server_addr;
    
    if(argc<=2){
        printf("usage: %s ip_addr ip_port \n",basename(argv[0]));
        return 1;
    }
   
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        errExit("The cilent socket creation process failed");
    }     
    
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    inet_pton(AF_INET,ip,&server_addr.sin_addr); 

    connfd=connect(sockfd, (struct sockaddr*)&server_addr,sizeof(server_addr));
    if(connfd<0){
        printf("The connect process failed\n ");
    }else{
        printf("-------Test MSG_OOB FIELD--------\n");
        const char *data="normal_data";
        send(sockfd,data,strlen(data),0);
        data="oob_data";
        send(sockfd,data,strlen(data),MSG_OOB);
        data="normal_data";
        send(sockfd,data,strlen(data),0);
       
        close(connfd); 
   }
    close(sockfd);

    return 0;
}
