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
    struct sockaddr_in server_addr; // for naming the server's listening socket
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(23657);
    
    /* Now connect to the server */
    bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }
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
        bzero(buffer,256);
        
        printf("Data received: \n");
        
        char input;
        while (1) {
            n = read(sock,&input,1);
            if (input == '\n') {
                printf("%c",input);
                break;
            }
            if (!n) {
                perror("ERROR reading from socket");
                exit(1);
            }
            printf("%c",input);
        }
    }
    
    return 0;
}
