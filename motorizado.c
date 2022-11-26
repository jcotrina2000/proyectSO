// C Program for Message Queue (Reader Process)
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<math.h>
#include<unistd.h>
#include<time.h>
#include<sys/ipc.h> 
#include<sys/shm.h>
#include<string.h>
#include"lib.c"

int main(){
        int *buf = malloc(2 * sizeof(int));	
	int key = ftok(".", 34);
	int *arr;
	
	int shmid = shmget(key,sizeof(int)*2,0666|IPC_EXCL);
	arr = shmat(shmid, NULL, 0);
	int i;
	memcpy(buf, arr, 2 * sizeof(int));    	
	shmdt((void *) arr);
    	shmctl(shmid, IPC_RMID, NULL);	

    	/*TDA para motorizado*/
	int n_grilla = buf[0], n_motorizados = buf[1];
	int lim = n_grilla/2, lim_cond = (n_grilla/2) * -1, c = (int)pow(n_grilla,2);
	Coordenadas* grilla_completa = agregar_coordenadas_completas(c, lim, lim_cond);
	srand(time(NULL));
	Coordenadas* grilla_motorizados = grilla_aleatoria(c, n_motorizados, grilla_completa);
	
	printf("Coordenadas motorizados aleatoria\n");	
	for(int y = 0; y < n_motorizados; y++){
		printf("(%d,%d)\n", grilla_motorizados[y].coord_x, grilla_motorizados[y].coord_y);
	}

	return 0;

}

// structure for message queue
/*struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
} message;

int main(){

	key_t key;
	int msgid;

	// ftok to generate unique key
	key = ftok("progfile", 65);

	// msgget creates a message queue
	// and returns identifier
	msgid = msgget(key, 0666 | IPC_CREAT);

	// msgrcv to receive message
	msgrcv(msgid, &message, sizeof(message), 1, 0);

	// display the message
	printf("Valor comida recibido : %s \n", message.mesg_text);
        srand(time(NULL));

	printf("La probabilidad es: %f \n", (1.0*(rand())/RAND_MAX));

	// to destroy the message queue
	msgctl(msgid, IPC_RMID, NULL);

	return 0;
}*/


