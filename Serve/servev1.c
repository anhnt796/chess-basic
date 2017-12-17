#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 3000
#define BUF_SIZE 2000

typedef struct
{
    int pid;
    int sockfd;
    struct sockaddr_in addr;
} ChessPlayer;

typedef struct
{
    int status;
    ChessPlayer player1;
    ChessPlayer player2;
} Pair;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int i = 0;
    int sockfd, newsockfd, portno, player1sockfd, player2sockfd;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    // initial pairs
    Pair pairs[3];
    for (int j = 0; j < 3; j++)
    {
        pairs[j].status = 0;
    }

    // Create Socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    //
    memset(&serv_addr, 0, sizeof(serv_addr));
    //bzero((char *)&serv_addr, sizeof(serv_addr));
    //portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = PORT;
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    listen(sockfd, 6);
    clilen = sizeof(cli_addr);
    //Below code is modified to handle multiple clients using fork
    //------------------------------------------------------------------
    int pid;
    while (1)
    {
        char temp[30];
        char code[4];
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0)
            error("ERROR on accept");
        if (pairs[0].status == 0)
        {
            pairs[0].player1.sockfd = newsockfd;
            pairs[0].player1.addr = cli_addr;
            pairs[0].status = 1;
        }
        else
        {
            pairs[0].player2.sockfd = newsockfd;
            pairs[0].player2.addr = cli_addr;
            pairs[0].status = 2;
        }

        // Send player's color to client, 0 White, 1 Black.
        code[0] = i % 2 + '0';
        code[1] = '\0';
        i++;
        strcpy(temp, "PCLR   ");
        strcpy(temp + strlen(temp), code);
        printf("%s", temp);
        int ret = sendto(newsockfd, temp, BUF_SIZE, 0, (struct sockaddr *)&cli_addr, sizeof(cli_addr));
        if (ret < 0)
        {
            printf("Error sending data\n");
        }
        //fork new process
        //
        switch (pairs[0].status)
        {
        case 1:
            printf("Case 1\n");
            break;
        case 2:
            printf("Case 2\n");
            pid = fork();
            if (pid < 0)
            {
                error("ERROR in new process creation");
            }
            if (pid == 0)
            {
                //child process
                close(sockfd);
                //do whatever you want
                while (1)
                {
                    memset(&buffer, 0, 256);
                    printf("%d\n",getpid());
                    n = read(pairs[0].player1.sockfd, buffer, 255);
                    if (n < 0)
                        error("ERROR reading from socket");
                    printf("Here is the message: %s\n", buffer);
                    n = write(pairs[0].player2.sockfd, buffer, 255);
                    if (n < 0)
                        error("ERROR writing to socket");
                }
                close(newsockfd);
            }
            else
            {
                printf("abc\n");
                pid = fork();
                if (pid < 0)
                {
                    error("ERROR in new process creation");
                }
                if (pid == 0)
                {
                    close(sockfd);
                    while (1)
                    {
                        memset(&buffer, 0, 256);
                        printf("%d\n",getpid());
                        n = read(pairs[0].player2.sockfd, buffer, 255);
                        if (n < 0)
                            error("ERROR reading from socket");
                        n = write(pairs[0].player1.sockfd, buffer, 255);
                        if (n < 0)
                            error("ERROR writing to socket");
                    }
                    close(newsockfd);
                }
                else
                {
                    close(pairs[0].player2.sockfd);
                    close(pairs[0].player1.sockfd);
                }
            }
            break;
        }
    }
    //-------------------------------------------------------------------
    return 0;
}