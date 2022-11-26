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
#include"ziggurat.h"
#include"lib.c"
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
	int lim = n_grilla/2, lim_cond = (n_grilla/2) * -1, c = (int)pow(n_grilla, 2);

	Coordenadas* grilla_completa = agregar_coordenadas_completas(c, lim, lim_cond);
	srand(time(NULL));
	Coordenadas* grilla_restaurantes = grilla_aleatoria(c, n_restaurantes, grilla_completa);

	printf("Coordenadas restaurantes aleatoria\n");
	for(int y = 0; y < n_restaurantes; y++){
		printf("(%d,%d)\n", grilla_restaurantes[y].coord_x, grilla_restaurantes[y].coord_y);
	}

	//Servidor Restaurante
	
	/*int server_sockfd, client_sockfd;
	int server_len; 
	int rc; 	
	pid_t pid;
	unsigned client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htons(INADDR_ANY);
	server_address.sin_port = htons(7734) ; 
	server_len = sizeof(server_address);
	
	rc = bind(server_sockfd, (struct sockaddr *) &server_address, server_len);
	printf("RC from bind = %d\n", rc ) ; 
	

	rc = listen(server_sockfd, 5);
	printf("RC from listen = %d\n", rc ) ; 
	
	//signal(SIGINT, salir);
	//signal(SIGCHLD, recoger_hijos_zombies);
	
	//while(1){
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_address, &client_len);
		
		//if((pid = fork()) == 0){
			//close(server_sockfd);
			//while(1){	
				int pid_c;
				//printf("server waiting\n");
				rc = read(client_sockfd, &pid_c, 1);
				printf("Lectura valor id Cli = %d\n", pid_c);	
				write(client_sockfd, &pid_c, 1);
			//}
		//}
	//}
	
	printf("after accept()... client_sockfd = %d\n", client_sockfd) ; 
	
	while(1)
	{
		int sensor_reading;
		//printf("server waiting\n");
		rc = read(client_sockfd, &sensor_reading, 1);
		printf("Lectura valor sensor = %d\n", sensor_reading );	
		write(client_sockfd, &sensor_reading, 1);
	}
	//tupla = make_tuple(sensor_reading)
	//printf("");

	printf("server exiting\n");

	close(client_sockfd);*/
	return 0;
}
