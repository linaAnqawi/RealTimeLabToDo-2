

// C Program for Message Queue 
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// structure for message queue
struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
	long pid;

} message;

int main()
{	int c=0;
	key_t key;
	int msgid;
	char buffer[50];

	// ftok to generate unique key
	key = ftok("progfile", 65);

	// msgget creates a message queue
	// and returns identifier
	msgid = msgget(key, 0666 | IPC_CREAT);
	while (1){
	// msgrcv to receive message
	msgrcv(msgid, &message, sizeof(message), 1, 0);
	c=c+1;

	// display the message
	printf("Data Received is : %s ,From ID : %ld counter Is: ", 
				message.mesg_text,message.pid);
	sprintf(buffer,"%d",c);
	printf("%s\n",buffer);
	fflush(stdout);
	message.mesg_type = message.pid;
	strcpy(message.mesg_text,buffer);
	msgsnd(msgid, &message, sizeof(message),0);
	printf("text send from server%s\n",message.mesg_text);
	}
	// to destroy the message queue
	//msgctl(msgid, IPC_RMID, NULL);

	return 0;
}

