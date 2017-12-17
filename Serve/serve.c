#include <gtk/gtk.h>
#include <stdio.h>
#include "string.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "netdb.h"

#define PORT 3000
#define CLADDR_LEN 100
#define BUF_SIZE 2000

GThread *thread;
GError *error = 0;
int sockfd, ret;
struct sockaddr_in addr, cl_addr;
int sockfd, len, ret, newsockfd;
char clientAddr[CLADDR_LEN];
char code[BUF_SIZE];

static void receiveCmd(void *socket);

void main()
{
    // Create (SOCK_STREAM) TCP socket    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("Error creating socket!\n");
        exit(1);
    }
    printf("Socket created...\n");

    // Cung cấp bộ nhớ cho biến addr
    memset(&addr, 0, sizeof(addr));

    // Bind socket with local port and ip address    
    
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = PORT;
    ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));

    if (ret < 0)
    {
        printf("Error binding!\n");
        exit(1);
    }
    printf("Binding done...\n");

    // Listen for connection, max connection 5
    printf("Waiting for a connection...\n");
    listen(sockfd, 5);      

    len = sizeof(cl_addr);
    // Accept and stored information of client's socket (cl_addr)
    newsockfd = accept(sockfd, (struct sockaddr *)&cl_addr, &len); // Máy sẽ treo ở đây để đợi client connect tới.
    if (newsockfd < 0)
    {
        printf("Error accepting connection!\n");
        exit(1);
    }

    inet_ntop(AF_INET, &(cl_addr.sin_addr), clientAddr, CLADDR_LEN);
    printf("Connection accepted from %s...\n", clientAddr);

    memset(code, 0, BUF_SIZE);

    thread = g_thread_create(receiveCmd, (void *)newsockfd, FALSE, &error);
    if (!thread)
    {
        g_print("Error: %s\n", error->message);
        return (-1);
    }
}

static void receiveCmd(void *socket)
{
    int sockfd, ret;
    char code_rcv[BUF_SIZE];
    sockfd = (int)socket;
    memset(code_rcv, 0, BUF_SIZE);
    for (;;)
    {
        ret = recvfrom(sockfd, code_rcv, BUF_SIZE, 0, NULL, NULL);
        if (ret > 0)
        {
            gdk_threads_enter();
            // decoded temp1;
            // temp1 = getresults(code_rcv);
            // switch(temp1.cmd) {
            //     case 1:
            //         move[0]= temp1.var[0]-'0';
            //         move[1]= temp1.var[1]-'0';
            //         move[2]= temp1.var[2]-'0';
            //         move[3]= temp1.var[3]-'0';
            //         makemove(player,move,board);
            //         updateGUI();
            //         break;
            //     default: break;
            // }
            gdk_threads_leave();
        }
    }
}