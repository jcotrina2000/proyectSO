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
#include<sys/wait.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<signal.h>
#include<string.h>	
#include"ziggurat.h"
#include"lib.c"


/*Declaración de variables globales*/

int server_sockfd, client_sockfd, max_clients;
int server_len, id_client; 
int rc ; 
Coordenadas cli;	
pid_t server_pid, *pids, cli_pid;
unsigned client_len;
struct sockaddr_in server_address;
struct sockaddr_in client_address;


/*Referencia a funciones*/
void desconectarPorSenial(int sig);


int main(){
	int *buf = malloc(2 * sizeof(int));
	int key = ftok("shmfile", 35);
	int *arr;

	int shmid = shmget(key,sizeof(int)*2,0666|IPC_EXCL);
	arr = shmat(shmid, NULL,0);
	int i;
	memcpy(buf, arr, 2 * sizeof(int));
	shmdt((void *) arr);
	shmctl(shmid, IPC_RMID,NULL);

	
	int n_grilla = buf[0], n_restaurantes = buf[1];
	int lim = n_grilla/2, lim_cond = (n_grilla/2) * -1, c = (int)pow(n_grilla, 2), n_clientes = c - n_restaurantes, conta;

	Coordenadas* grilla_completa = agregar_coordenadas_completas(c, lim, lim_cond);
	srand(time(NULL));
	Coordenadas* grilla_restaurantes = grilla_aleatoria(c, n_restaurantes, grilla_completa);

        /*Región de memoria 3 para clientes*/
	int key3 = ftok("shm", 36);
	int *arr3;
	int shmid3 = shmget(key3, sizeof(int)*2, 0666|IPC_CREAT);

	arr3 = (int*)shmat(shmid3, NULL, 0);
	arr3[0] = n_grilla;
	arr3[1] = n_restaurantes;
	
	shmdt((void *) arr3);	
	
	
	printf("Coordenadas restaurantes aleatoria\n");
	for(int y = 0; y < n_restaurantes; y++){
		printf("(%d,%d)\n", grilla_restaurantes[y].coord_x, grilla_restaurantes[y].coord_y);
	}
	
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htons(INADDR_ANY);
	server_address.sin_port = htons(7734) ; 
	server_len = sizeof(server_address);
	
	rc = bind(server_sockfd, (struct sockaddr *) &server_address, server_len);
	printf("RC from bind = %d\n", rc ) ; 
	

	rc = listen(server_sockfd, 5);
	printf("RC from listen = %d\n", rc);

        //signal(SIGINT, cerrarServidor);

	max_clients = c - n_restaurantes;
	printf("Max clients size: %d\n", max_clients);

	client_len = sizeof(client_address);
	client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_address, &client_len);

	id_client = 0;
        conta = 0;
	do{
		//read(client_sockfd, &id_client, sizeof(int));
	        //pids[id_client++] = fork();
	        //if(pids[id_client - 1] == 0){
		read(client_sockfd, &cli_pid, sizeof(pid_t));
		if(fork() == 0){
			server_pid = getpid();
                        //signal(SIGINT, desconectarPorSenial);
			printf("Cliente recibido : %d\n", cli_pid);
			write(client_sockfd, &server_pid, sizeof(pid_t));
        	}
		else{
			wait(NULL);
		}

	}
	while(1);
	
	printf("after accept()... client_sockfd = %d\n", client_sockfd) ; 
	

	printf("server exiting\n");

	close(client_sockfd);

        
	return 0;
}

void desconectarPorSenial(int sig){
	if(sig == SIGINT) kill(cli_pid, SIGUSR1);
	close(client_sockfd);

}
