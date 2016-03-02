# Banking_System

CS/CE/TE 6378: Project I
Design:
For each client session, the client establishes a socket connection with one of the server (master) and that master server establishes socket connection with the other 2 servers. Whenever a client sends a command, first it will be sent to the master server. Then the master server forwards it to the other 2 servers. The other 2 servers executes that command and sends a reply message to the master server. If the other 2 server’s command execution was successful then the master server also executes that command and sends a reply to the client. 
Run Procedure:
Server:
Compilation: g++ server.cpp –pthread –o server
Server program requires 3 command line parameters. First parameter indicates the port number of the server, second and third parameter indicates the other 2 server’s context.
On dc23 machine (s1):
./server 8000 s2 s3
On dc24 machine (s2):
./server 8001 s1 s3
On dc25 machine (s3):
./server 8002 s1 s2
S1 is mapped to dc23.
S2 is mapped to dc24.
S3 is mapped to dc25
Client:
Compilation: g++ client.cpp –o client
Client program requires 2 common line parameters. First parameter indicate which server to act as a master server and second parameter indicates the port number of master server.
For e.g.  ./client s1 8000
Client can be run on any machine. 

Note: 
1) In the code, s1, s2 and s3 are mapped to dc23 – 8000, dc24 – 8001 and dc25 – 8002 respectively. So the servers has to be run on dc23, dc24 and dc25 machines with the corresponding port numbers. If the server needs to be run on other machines, then the mapping has to be changed in the code (one line change).
2) During client session, commands are case sensitive and single space separated. It takes all lower case characters. Here are the format of the supported commands:
a) read file.txt
b) write file.txt “This is a sample string”
c) seek file.txt 5
d) read file.txt 2
e) help
f) delete file.txt
g) terminate
3) Since the client itself specifies which server (master) to connect, the output will not show server name.

