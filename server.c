/**
 * @file   server.c
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
    int serv_sock = socket( AF_INET, SOCK_STREAM, 0);

    if ( serv_sock == -1 )
    {
        printf("error: create listen socket \n");
    }

	struct sockaddr_in addr;

	bzero ((void *)&addr, sizeof (addr));

	addr.sin_family = AF_INET;
	addr.sin_port = htons (9090);
	addr.sin_addr.s_addr = htonl (INADDR_ANY);

    /* set addr for socket */
    if ( bind(serv_sock, (struct sockaddr *)&addr, sizeof(addr) ) == -1)
    {
        printf("error: bind socket \n");

        close(serv_sock);
    }

    /* to set socket for listen incoming requests */
    if ( listen(serv_sock, 5) == -1)
    {
        printf("error: listen \n");

        close(serv_sock);
    }

	while (1)
	{
		struct sockaddr_in addr;

		socklen_t n = sizeof(addr);

		int sock = accept(serv_sock, (struct sockaddr *)&addr, &n);
	
		if ( sock == -1 )
		{
			printf("error: accept socket \n");
		
			continue;
		}

		printf("-> connection accept -- ok \n");

		char data[255];

		while (recv(sock, data, 255, 0) != 0)
		{
			memset(data, '-', 255);
			
			data[0] = 'x';
			data[2] = 'x';
			data[7] = 'x';
			data[9] = 'x';
			
			data[10] = 0;

			send(sock, data, 255, 0);
		}

		close(sock);
	}

	close(serv_sock);

	return 0;
}

