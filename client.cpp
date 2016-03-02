/*Advanced Operating Systems - Spring 2016 
 * Programming Project #1
 * 
 * Client.cpp - Client node of the system
 * @author - Anoop S Somashekar
*/

#include "common.h"
map<string, string> serverList;

void help()
{
    printf("*********************************************************\n");
    printf("The following commands are supported (case sensitive!!!) :\n");
    printf("create <filename>\n");
    printf("seek filename index\n");
    printf("read filename [length]\n");
    printf("write filename \"text\"\n");
    printf("delete filename\n");
    printf("help\n");
    printf("terminate\n");
    printf("**********************************************************\n");
}

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("Usage %s server_name server_port\n", argv[0]);
        exit(0);
    }
    serverList["s1"] = "anoop-VPCEB46FX";
    serverList["s2"] = "anoop-VPCEB46FX";
    serverList["s3"] = "anoop-VPCEB46FX";

	struct sockaddr_in my_addr;
    struct hostent *serv;
    serv = gethostbyname(serverList.find(argv[1])->second.c_str());
	int hsock;
	int * p_int;
    int err;

    //client socket
	hsock = socket(AF_INET, SOCK_STREAM, 0);
	if(hsock == -1){
		printf("Error initializing socket %d\n",errno);
		goto FINISH;
	}
	
    //temporary int pointer for setsockopt call
	p_int = (int*)malloc(sizeof(int));
	*p_int = 1;
		
    //set client socket opt    
	if( (setsockopt(hsock, SOL_SOCKET, SO_REUSEADDR, (char*)p_int, sizeof(int)) == -1 )||
		(setsockopt(hsock, SOL_SOCKET, SO_KEEPALIVE, (char*)p_int, sizeof(int)) == -1 ) ){
		printf("Error setting options %d\n",errno);
		free(p_int);
		goto FINISH;
	}
	free(p_int);

    //server socket setup details.
	my_addr.sin_family = AF_INET ;
    my_addr.sin_port = htons(atoi(argv[2]));
    memset(&(my_addr.sin_zero), 0, 8);
    bcopy((char *)serv->h_addr, (char *)&my_addr.sin_addr.s_addr, serv->h_length);
    
    //establish socket connection from client to server
	if( connect( hsock, (struct sockaddr*)&my_addr, sizeof(my_addr)) == -1 ){
		if((err = errno) != EINPROGRESS){
			fprintf(stderr, "Error connecting socket %d\n", errno);
			goto FINISH;
		}
	}
    help();

    msgPkt m_pkt;
    m_pkt.optParam = 0;
    while(1)
    {
        memset(&m_pkt, 0, sizeof(m_pkt));
        std::string line;
        getline(cin, line);
        std::istringstream iss(line);
        std::string token;
        int count =1;

        while(std::getline(iss, token, ' '))
        {
            if(count == 1)
                strcpy(m_pkt.cmd, token.c_str());
            else if(count == 2)
                strcpy(m_pkt.fname, token.c_str());
            else
            {                
                if(count == 3)
                {
                    m_pkt.optParam = 1; 
                    if(strcmp(m_pkt.cmd, "write") == 0)
                    {
                        //remove double quote at the begining of the text
                        token.erase(0, 1);
                        strcpy(m_pkt.data, token.c_str());
                    }
                    else
                        strcpy(m_pkt.data, token.c_str());
                }
                else
                {
                    strcat(m_pkt.data, " ");
                    strcat(m_pkt.data, token.c_str());
                }
            }
            count++;
        }

        //remove double quote at the end of the text.
        if(strcmp(m_pkt.cmd, "write") == 0)
        {
            m_pkt.data[strlen(m_pkt.data)-1] = 0;
        }
        m_pkt.master_server = 1;
        strcpy(m_pkt.context, argv[1]);
        char result[1024] = {0};

        //create command
        if(strcmp(m_pkt.cmd, "create") == 0)
        {
            if(send(hsock, (void *)&m_pkt, sizeof(m_pkt), 0) == -1)
            {
                fprintf(stderr, "Error sending data %d\n", errno);
                goto FINISH;
            }

            if(recv(hsock,result, 1024, 0) == -1)
            {
                fprintf(stderr, "Error receiving data %d\n", errno);
                goto FINISH;
            }
            printf("%s\n", result);
        }

        //seek command
        else if(strcmp(m_pkt.cmd, "seek") == 0)
        {
            if(send(hsock, (void *)&m_pkt, sizeof(m_pkt), 0) == -1)
            {
                fprintf(stderr, "Error sending data %d\n", errno);
                goto FINISH;
            }

            if(recv(hsock,result, 1024, 0) == -1)
            {
                fprintf(stderr, "Error receiving data %d\n", errno);
                goto FINISH;
            }
            printf("%s\n", result);
        }

        //read command
        else if(strcmp(m_pkt.cmd, "read") == 0)
        {
            if(send(hsock, (void *)&m_pkt, sizeof(m_pkt), 0) == -1)
            {
                fprintf(stderr, "Error sending data %d\n", errno);
                goto FINISH;
            }

            if(recv(hsock,result, 1024, 0) == -1)
            {
                fprintf(stderr, "Error receiving data %d\n", errno);
                goto FINISH;
            }
            printf("%s\n", result);

        }

        //delete command
        else if(strcmp(m_pkt.cmd, "delete") == 0)
        {
            if(send(hsock, (void *)&m_pkt, sizeof(m_pkt), 0) == -1)
            {
                fprintf(stderr, "Error sending data %d\n", errno);
                goto FINISH;
            }

            if(recv(hsock,result, 1024, 0) == -1)
            {
                fprintf(stderr, "Error receiving data %d\n", errno);
                goto FINISH;
            }
            printf("%s\n", result);
        }

        //write command
        else if(strcmp(m_pkt.cmd, "write") == 0)
        {
            if(send(hsock, (void *)&m_pkt, sizeof(m_pkt), 0) == -1)
            {
                fprintf(stderr, "Error sending data %d\n", errno);
                goto FINISH;
            }

            if(recv(hsock,result, 1024, 0) == -1)
            {
                fprintf(stderr, "Error receiving data %d\n", errno);
                goto FINISH;
            }
            printf("%s\n", result);
        }

        //terminate command
        else if(strcmp(m_pkt.cmd, "terminate") == 0)
        {
            printf("Output : The session is going to be closed\n");
            send(hsock, (void *)&m_pkt, sizeof(m_pkt), 0);
            sleep(0.4);
            close(hsock);
            exit(0);
        }
        else if(strcmp(m_pkt.cmd, "help") == 0)
        {
            help();
        }
        else
        {
            printf("Command not supported!!!!!! Use help command\n");
        }    
    }
    return 0;
FINISH:
;
}
