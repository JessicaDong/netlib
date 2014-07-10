#include"../../../lib/netlib.h"
#include"../../../lib/neterror.h"


/*
struct addrinfo {
    int     ai_flags;
    int     ai_family;
    int     ai_socktype;
    int     ai_protocol;
    size_t  ai_addrlen;
    struct  sockaddr *ai_addr;
    char    *ai_canonname;     // canonical name 
    struct  addrinfo *ai_next; // this struct can form a linked list 
};

int getaddrinfo(const char *host, const char *service,
    const struct addrinfo *hints, struct addrinfo **result)
*/

#define BACKLOG 20
#define PORT 12345
