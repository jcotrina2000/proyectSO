#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<math.h>

/*Creación de la estructura para el GRID*/

typedef struct{
	int coord_x;
	int coord_y;
}Coordenadas;


/*Función para agregar todas las coordenadas que corresponden al GRID nxn*/

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

/*Función para verificar si existe un número dentro de un arreglo*/

bool searchvalue(int arr[], int size, int value){
	for(int i = 0; i < size; i++){
		if(arr[i] == value){
			return true;
		}
	}
}

/*Función para generar una estructura con x coordenadas aleatorias*/

Coordenadas* grilla_aleatoria(int c, int cant_registrados, Coordenadas* grilla_completa){
	Coordenadas* grid_aleatorio = malloc(cant_registrados * sizeof *grid_aleatorio);
	int i_a_e[cant_registrados];
	//srand(time(NULL));
	int n = 0;
	while(n < cant_registrados){
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

/*Función para hallar el indice del menor número de un arreglo*/
int indiceMinimo(int* arreglo, int size){
	int mayor = 0;
	int indice = 0;
	for(int i = 0; i < size; i++){
		if(arreglo[i] > mayor){
			mayor = arreglo[i];
			indice = i;
		}
	}
	return indice;
}

/*Función para localizar al motorizado más cercano*/
Coordenadas distanciaMinima(Coordenadas rest, int size, Coordenadas* Motorizados){
	int* distancias = malloc(size * sizeof(int));
	int x1 = rest.coord_x, y1 = rest.coord_y;
	for(int i = 0; i < size; i++){
		int p1 = pow(x1 - Motorizados[i].coord_x, 2);
		int p2 = pow(y1 - Motorizados[i].coord_y, 2);
		distancias[i] = sqrt(p1 + p2);
	}
	int indiceMenorDistancia = indiceMinimo(distancias, size);
	return Motorizados[indiceMenorDistancia];
}

/*Funciones para poder ingresar un nuevo cliente*/
int buscarIndice(Coordenadas* grid, int n, Coordenadas valor){
	for(int i = 0; i < n; i++){
		if((grid[i].coord_x == valor.coord_x) && (grid[i].coord_y == valor.coord_y)){
			return true;
		}  
	}

}

//Coordenadas coordCliente(Coordenadas *grilla_completa,int n_g, Coordenadas* rest, int n_r)
Coordenadas coordCliente(Coordenadas *grilla_completa, int c){
	int i_aleatorio = rand() % c;
	return grilla_completa[i_aleatorio];

}
	
	

