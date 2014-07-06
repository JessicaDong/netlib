#include"tcp_rw.h"

int
main(int argc, char* argv[]){

    const char* ip = argv[1];
    int port = atoi(argv[2]);
    int sockfd,ret;
    struct sockaddr_in server_address;

    if(argc <= 2){ 
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }   
 
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &server_address.sin_addr);
    server_address.sin_port = htons(port);

    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if(sockfd<0){
        errExit("The socket creation failed ");
    }   

    ret=connect(sockfd, (struct sockaddr*)&server_address, sizeof(server_address));
    if(ret<0){
        errMsg("connection failed");
    }   
    else{
        printf("write normal data out\n");
        const char* normal_data = "Hello read~~~~~";
        net_write(sockfd, normal_data, strlen(normal_data));
   }   

    close(sockfd);
    return 0;
}
