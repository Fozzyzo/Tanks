
#define SRV_IP "999.999.999.999"

#include <stdio.h>
#include <sys/types.h>
#include <winsock2.h>
#include <InetSDK.h>

#define BUFLEN 512
#define NPACK 10
#define PORT 9931

int main(void)

{
	struct sockaddr_in si_other;
	int s, i, slen = sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		printf("Socket creation failed! Error code: %d", WSAGetLastError());
	}


	memset((char *)&si_other, 0, sizeof(si_other));

	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);

	if (sendto(s, message, strlen(message), 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
	{
		    fprintf(stderr, "inet_aton() failed\n");
		    exit(EXIT_FAILURE);
	}


	for (i = 0; i<NPACK; i++) 
	{
		printf("Sending packet %d\n", i);
		sprintf(buf, "This is packet %d\n", i);

		if (sendto(s, buf, BUFLEN, 0, (struct sockaddr*)&si_other, slen) == -1)
		{
			printf("Packet sending failed!");
		}
	}

	closesocket(s);
	return 0;
}
