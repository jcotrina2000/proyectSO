#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<time.h>
#include<stdint.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/shm.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<signal.h>
#include<string.h>	
#include<semaphore.h>
#include"ziggurat.h"
#include<sys/wait.h>
#include<signal.h>
#include"lib.c"

#define DEBUG 1
#define BUF_SIZE 100


/*Declaración de variables globales*/
int  fd_cli, res_pid;
int rc, len, id_client;
pid_t pid;

/*Definición de funciones*/
void desconectarPorSenial(int signum);

int main(){

        /*Región de memoria compartida*/

        int *buf = malloc(2 * sizeof(int));	
	int key = ftok("shm", 36);	
	
	int *arr;
	
	int shmid = shmget(key,sizeof(int)*2,0666|IPC_EXCL);
	arr = shmat(shmid, NULL, 0);
	int i;
	memcpy(buf, arr, 2 * sizeof(int));    	
	shmdt((void *) arr);
    	shmctl(shmid, IPC_RMID, NULL);

	//TDA para cliente
	int n_grilla = buf[0], n_restaurante = buf[1];
	int lim = n_grilla/2, lim_cond = (n_grilla/2) * -1, c = (int)pow(n_grilla,2);
	Coordenadas* grilla_completa = agregar_coordenadas_completas(c, lim, lim_cond);
	srand(time(NULL));
	Coordenadas* grilla_restaurante = grilla_aleatoria(c, n_restaurante, grilla_completa);
	int n_clientes = c - n_restaurante;
	Coordenadas* grilla_clientes = malloc(n_clientes * sizeof(Coordenadas));

	printf("Programando de lado del cliente\n");
	int cli_pid;
  	srand(time(NULL));   

  	//Creación del socket para el cliente.
	fd_cli = socket(PF_INET, SOCK_STREAM, 0);
	if (fd_cli == -1) { 
		perror("Fallo al crear el socket\n") ; 
		return -1 ; 
	}
  	
  	 /*Inicializar el número de puerto y direcciones*/
	 struct sockaddr_in address;
	 address.sin_family = AF_INET;
	 address.sin_addr.s_addr = inet_addr("127.0.0.1");
	 address.sin_port = htons(7734);
	 len = sizeof(address);

	 /*Iniciar la conexión*/
	 int result = connect(fd_cli, (struct sockaddr *)&address, len);
	 if(result < 0){
		perror("Error de conexión");
		exit(-1);
	}

        signal(SIGINT, desconectarPorSenial);

	pid_t* pids_r = malloc(n_clientes + sizeof(pid_t));

	while(1){
		if(fork() == 0){
			cli_pid =getpid();
			write(fd_cli, &cli_pid, sizeof(pid_t));
			read(fd_cli, &res_pid, sizeof(pid_t));
                	if(DEBUG) printf("Cliente # %d - Restaurante # %d\n",cli_pid, res_pid);
		}else{
			wait(NULL);
		}
	}

	close(fd_cli);
	exit(0);
  
  	return(EXIT_SUCCESS);
}

/*Funciones Manejo de señales*/
void desconectarPorSenial(int sign){
	kill(res_pid, SIGCONT);
}


/*Paso de mensajes para enviar precio aleatorio del cliente*/
/*struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
} message;

int main()
{
	key_t key;
	int msgid;

	// ftok to generate unique key
	key = ftok("progfile", 65);

	// msgget creates a message queue
	// and returns identifier
	msgid = msgget(key, 0666 | IPC_CREAT);
	message.mesg_type = 1;
	
        //fgets(message.mesg_text,MAX,"Hola mundo");
	srand(time(NULL));
	int num_ale = rand() % (15-7+1) + 7;	
	char snum_ale[sizeof(num_ale)];
	
	sprintf(snum_ale, "%d", num_ale);
	memcpy(message.mesg_text, snum_ale, sizeof(snum_ale));

	// msgsnd to send message
	msgsnd(msgid, &message, sizeof(message), 0);

	// display the message
	printf("Valor comida : %s \n", message.mesg_text);

	return 0;
}*/

