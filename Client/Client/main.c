//
//  main.c
//  Client
//
//  Created by jr2339 on 10/8/16.
//  Copyright © 2016 jr2339. All rights reserved.
//

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>



int main(int argc, const char * argv[]) {
    int sock;
    size_t n;
    char buffer[256];
    struct hostent *host;
    struct sockaddr_in server_addr; // for naming the server's listening socket
    
    host = gethostbyname("127.0.0.1");
    
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *)host->h_addr, (char *)&server_addr.sin_addr.s_addr, host->h_length);
    server_addr.sin_port = htons(23657);
 
    /* Now connect to the server */
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }
    /* Now ask for a message from the user, this message
     * will be read by server
     */
    while(1){
        printf("Please enter the message: ");
        bzero(buffer,256);
        fgets(buffer,255,stdin);
    
        /* Send message to the server */
        n = write(sock, buffer, strlen(buffer));
        
        if (!n) {
            perror("ERROR writing to socket");
            exit(1);
        }
    }

    return 0;
}
