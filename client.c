/**
 * @file   client.c
 * @author Alexander Velichko <alexv.prog@gmail.com>
 * 
 * @brief  Simple TCP/IP client programm. The programm works with select.
 *
 */

#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
        return 1;

    char* hostname = argv[1];

    int port = atoi(argv[2]);

    /* create socket ... */
    int fd_3 = socket( AF_INET, SOCK_STREAM, 0);

    if ( fd_3 == -1 )
    {
        printf("error: create fd_3et \n");
    }

    struct sockaddr_in addr;

    memset((void *)&addr, 0, sizeof (addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(hostname);

    /* connect */
    int ok = connect(fd_3, (struct sockaddr *)&addr, sizeof(addr) );

    if (ok != 0)
    {
        printf("error: connect fail\n");

        close(fd_3);

        return 1;
    }

    int fd_0 = STDIN_FILENO;
/*
    int fd_1 = STDOUT_FILENO;
    int fd_2 = STDERR_FILENO;
*/

    int _maxfd;

    fd_set _rset;
    fd_set _wset;
    fd_set _xset;

    while (1)
    {
        _maxfd = 0;

        /* clean fdsets */
        FD_ZERO (&_rset);
        FD_ZERO (&_wset);
        FD_ZERO (&_xset);

        /* set fd_0, fd_3 for select */
        FD_SET(fd_0, &_rset);
        FD_SET(fd_3, &_rset);

        /* set maximum of fd number {fd_0 and fd_3} */
        _maxfd = fd_3;

        /* block to wait input-output event and timeout */
        int ready = select (_maxfd + 1, &_rset, &_wset, &_xset, NULL);

        if (ready > 0)
        {
            /* there are some ready input or output fd */

            if (FD_ISSET(fd_0, &_rset))
            {
                /* ready stdin */

                char data[255];

                memset(data, 0, 255);

                /* read line from stdin */
                read(fd_0, data, 255);

                /* send to net */
                send(fd_3, data, 255, 0);
            }

            if (FD_ISSET(fd_3, &_rset))
            {
                /* ready fd_3 */

                char data[255];

                /* recv from net not more then size of 'data' array */
                int num = recv(fd_3, data, 255, 0);

                if (num == 0)
                {
                    /* connection was closed */
                    close(fd_3);
                }

                    printf("serv [ %s ]\n", data);
            }
        }
    }

    return 0;
}

