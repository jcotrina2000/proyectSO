#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdbool.h>

bool searchvalue(int arr[], int size, int value);

bool searchvalue(int arr[],int size,int value){
     for(int i=0;i<size;i++){
         if(arr[i]==value){
            return true;
         }
     }
}

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
        
        if(grilla_n <= 0 || num_restaurante_n <= 0 || intervalo_n <= 0 || motorizados_n <= 0 || km_distancia <= 0){
		fprintf(stderr, "El valor de los parámetros debe ser mayor a cero");
	return -1;
	}	

	printf("Grilla de %dx%d, %d restaurantes, intervalo %d milisegundos, %d motorizados, %d kilómetros de distancia\n", grilla_n, grilla_n, num_restaurante_n, intervalo_n, motorizados_n, km_distancia_n);

	/*TDA para grilla nxn*/

	typedef struct{
		int coord_x;
		int coord_y;
	}Coordenadas;

        int j,i,n, ind;
	int lim = grilla_n/2, lim_cond = (grilla_n/2) * -1;
        int c = (int)pow(grilla_n, 2);
	Coordenadas* grilla_completa = malloc(c * sizeof *grilla_completa);
	//Coordenadas* elegidos = malloc(num_restaurante_n + motorizados_n * sizeof *elegidos);
	Coordenadas* motorizado = malloc(motorizados_n * sizeof *motorizado);
	Coordenadas* restaurante = malloc(num_restaurante_n * sizeof *restaurante);

	srand(time(NULL));
	ind = 0;
	for(j = lim; j >= lim_cond; j--){
		for(i = lim_cond; i <= lim; i++){
			grilla_completa[ind].coord_x = i;
			grilla_completa[ind].coord_y = j;
			ind = ind + 1;
		 }	
	}
	for(n = 0; n < c; n++){
		printf("(%d,%d)\n", grilla_completa[n].coord_x, grilla_completa[n].coord_y);
	}

	int n_r = 0, n_m = 0, size_elegidos = num_restaurante_n + motorizados_n;
	int i_a_e[size_elegidos];
	while(n_r < num_restaurante_n){
		int randomly = rand() % c;
		bool f = searchvalue(i_a_e, size_elegidos, randomly);
		if(!f){
			i_a_e[n_r] = randomly;
			restaurante[n_r].coord_x = grilla_completa[randomly].coord_x;
			restaurante[n_r].coord_y = grilla_completa[randomly].coord_y;	
			n_r++;
		}
	
	}

	while(n_m < motorizados_n){
		int random_n = rand() % c;
		bool f1 = searchvalue(i_a_e, size_elegidos, random_n);
		if(!f1){
			i_a_e[n_r+n_m] = random_n;
			motorizado[n_m].coord_x = grilla_completa[random_n].coord_x;
			motorizado[n_m].coord_y = grilla_completa[random_n].coord_y;
			n_m++;
		}
	
	}
	

	printf("\n");

	printf("Imprimir coordenadas restaurantes\n");

	for(int siu = 0; siu < num_restaurante_n; siu++){
		printf("(%d, %d)\n",restaurante[siu].coord_x, restaurante[siu].coord_y);
	}


	printf("\n");

	printf("Imprimir coordenadas motorizados\n");
	for(int siuu = 0; siuu < motorizados_n; siuu++){
		printf("(%d,%d)\n", motorizado[siuu].coord_x, motorizado[siuu].coord_y);
	}

	printf("\n");


	int r, s;
        
	//motorizado
	/*double calcularDistancia(int x1, int y1, int x2, int y2){
            return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        }*/

        for(r = 0; r < grilla_n-1; r++){
            /* Draw Top */
            for(s = 0; s < grilla_n-1; s++)
                printf("+--");
            printf("+\n");

            /* Draw Middle */
            for(s = 0; s < grilla_n-1; s++)
                printf("|  ");
            printf("|\n");
        }

        /* Draw Bottom */
        for(s = 0; s < grilla_n-1; s++)
            printf("+--");
        printf("+\n");

}
