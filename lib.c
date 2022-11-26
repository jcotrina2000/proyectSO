#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

typedef struct{
	int coord_x;
	int coord_y;
}Coordenadas;

Coordenadas* agregar_coordenadas_completas(int c, int lim, int lim_cond){
	int ind = 0;
	int i, j;
	Coordenadas* grilla_completa = malloc(c * sizeof * grilla_completa);
	for(j = lim; j >= lim_cond; j--){
		for(i = lim_cond; i <= lim; i++){
			grilla_completa[ind].coord_x = i;
			grilla_completa[ind].coord_y = j;
			ind = ind + 1;
		}
	
	}
	return grilla_completa;
}

bool searchvalue(int arr[], int size, int value){
	for(int i = 0; i < size; i++){
		if(arr[i] == value){
			return true;
		}
	}
}

/*int* calculos(char* grilla_n){
	int [3] arreglo;
	int lim = grilla_n/2;
        int lim_cond = (grilla_n/2) * -1;
	int sizee = (int)pow(grilla_n, 2);
	arreglo[0] = lim;
	arreglo[1] = lim_cond;
	arreglo[2] = sizee;

}*/

Coordenadas* grilla_aleatoria(int c, int cant_registrados, Coordenadas* grilla_completa){
	Coordenadas* grid_aleatorio = malloc(cant_registrados * sizeof *grid_aleatorio);
	int i_a_e[cant_registrados];
	//srand(time(NULL));
	int n = 0;
	while(n < cant_registrados){
		//printf("n : %d , cant_registrados : %d \n", n,cant_registrados);
		int randomly = rand() % c;
		bool f = searchvalue(i_a_e, cant_registrados, randomly);
		if(!f){
			i_a_e[n] = randomly;
			grid_aleatorio[n].coord_x = grilla_completa[randomly].coord_x;
			grid_aleatorio[n].coord_y = grilla_completa[randomly].coord_y;	
			n++;
		}
	}

	return grid_aleatorio;
}
