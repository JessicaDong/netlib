#include"tcp_rw.h"

int
main(int argc, char* argv[]){

    const char* ip = argv[1];
    int port = atoi(argv[2]);
    int sockfd,ret;
    struct sockaddr_in address;
    char buffer[ BUF_SIZE ];

    if(argc <= 2){ 
        printf("usage: %s ip_address port_number\n",basename(argv[0]));
        return 1;
    }   
 
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    sockfd = socket(PF_INET, SOCK_STREAM, 0); 
    if(sockfd<0){
        errExit("The socket creation failed ");
    }   

    ret = bind(sockfd, (struct sockaddr*)&address, sizeof(address));
    if(ret<0){
        errExit("The bind process failed ");
    }   

    ret = listen(sockfd, 5); 
    if(ret<0){
        errExit("The listen process failed ");
    }   

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);
    int connfd = accept(sockfd, (struct sockaddr*)&client, &client_addrlength);
    if (connfd < 0){ 
        errMsg("The accept process failed ");
    }   
    else{
        memset(buffer, '\0', BUF_SIZE);
        ret = net_read(connfd, buffer, BUF_SIZE-1);
        printf("got %d bytes of normal data '%s'\n", ret, buffer);

		close(connfd);
    }

    close(sockfd);
    return 0;
}
