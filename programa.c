#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdbool.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include"lib.c"


int main(int argc, char **argv){
	char *grilla, *num_restaurante, *intervalo, *motorizados, *km_distancia; 	
	if(argc != 6){
		fprintf(stderr, "uso: prog <Grilla:integer> , <Restaurantes:integer> , <Intervalo:integer>, <Motorizados:integer> , <km de distancia:integer>\n");
		return -1;

	}
	grilla = argv[1];
	num_restaurante = argv[2];
	intervalo = argv[3];
	motorizados = argv[4];
	km_distancia = argv[5];
	int grilla_n = atoi(grilla), num_restaurante_n = atoi(num_restaurante), intervalo_n = atoi(intervalo),  motorizados_n = atoi(motorizados), km_distancia_n = atoi(km_distancia);
	
	printf("\n");

        if (grilla_n % 2 == 0) {
		fprintf(stderr,"El valor de la grilla debe ser un número impar\n");	
	return -1;
        }
        
        if(grilla_n <= 0 || num_restaurante_n <= 0 || intervalo_n <= 0 || motorizados_n <= 0 || km_distancia_n <= 0){
		fprintf(stderr, "El valor de los parámetros debe ser mayor a cero");
	return -1;
	}	

	printf("Grilla de %dx%d, %d restaurantes, intervalo %d milisegundos, %d motorizados, %d kilómetros de distancia\n", grilla_n, grilla_n, num_restaurante_n, intervalo_n, motorizados_n, km_distancia_n);
	/*Región de memoria 1 para motorizados*/
	int key = ftok(".", 34);
	int *arr;
	int shmid = shmget(key,sizeof(int)*2,0666|IPC_CREAT);

	arr = (int *)shmat(shmid, NULL, 0);
	arr[0] = grilla_n;
	arr[1] = motorizados_n;

    	shmdt((void *) arr);

	/*Región de memoria 2 para restaurantes*/
	int key2 = ftok("shmfile", 35);
	int *arr2;
	int shmid2 = shmget(key2, sizeof(int)*2, 0666|IPC_CREAT);

	arr2 = (int*)shmat(shmid2, NULL, 0);
	arr2[0] = grilla_n;
	arr2[1] = num_restaurante_n;
	
	shmdt((void *) arr2);
	
	/*Región de memoria 3 para clientes*/
	int key3 = ftok("shm", 36);
	int *arr3;
	int shmid3 = shmget(key3, sizeof(int)*2, 0666|IPC_CREAT);

	arr3 = (int*)shmat(shmid3, NULL, 0);
	arr3[0] = grilla_n;
	arr3[1] = num_restaurante_n;
	
	shmdt((void *) arr3);

	/*Prueba instancia estructuras*/
        int j,i,n, ind;
	int lim = grilla_n/2, lim_cond = (grilla_n/2) * -1;
        int c = (int)pow(grilla_n, 2);
	Coordenadas* motorizado = malloc(motorizados_n * sizeof *motorizado);
	Coordenadas* restaurante = malloc(num_restaurante_n * sizeof *restaurante);
	Coordenadas* grilla_completa = agregar_coordenadas_completas(c, lim, lim_cond);
	
	for(n = 0; n < c; n++){
		printf("(%d,%d)\n", grilla_completa[n].coord_x, grilla_completa[n].coord_y);
	
	}

	srand(time(NULL));
}
