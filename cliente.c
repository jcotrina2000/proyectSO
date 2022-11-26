// C Program for Message Queue (Writer Process)
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
#include"lib.c"

#define DEBUG 1
int main(){

	/*pid_t ids[5];
    for(int i=0;i<5;i++){
        if(fork() == 0){
            printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
	    ids[i] = getpid();
	    //printf("%d\n", ids[i]);
            exit(0);
        }
    }
    for(int n = 0; n < 5; n++){
        printf("Pid hijo %d : %d\n",n+1, getpid());
    
    }

    for(int i=0;i<5;i++) // loop will run n times (n=5)
    wait(NULL);*/

	int pid_server, fd_cli;
	//Declaración de variables
    	printf("Programando de lado del cliente\n");
    	float fn[128],Tfreq;
  	int ID_sensor,Stype,Davg,Dsd,Tsd,sensor_reading;
    	uint32_t kn[128];
    	unsigned int delay;
    	uint32_t seed;
    	float value;
    	float wn[128];
    	int rc, len, rdm;

   	 /*if (argc != 7) {
		fprintf(stderr,"usage: tiktoker <Tmin:integer> <Tmax:integer value> <Prob:1|0> \n");	
		return -1;
    	}*/

    	/*ID_sensor=atoi(argv[1]);
    	Stype=atoi(argv[2]);
    	Davg=atoi(argv[3]);
    	Dsd=atoi(argv[4]);
    	Tfreq=atof(argv[5]);
    	Tsd=atoi(argv[6]);*/


	/*if ( ID_sensor< 0 || Stype < 0 || Davg < 0 || Dsd < 0|| Tfreq < 0|| Tsd < 0) {
		fprintf(stderr,"Arguments must be non-negative\n");	
		return -1;
	}*/

  	//r4_nor_setup ( kn, fn, wn );
  	srand(time(NULL));   // Initialization, should only be called once.
  	//seed = rand(); 

  	//Creación del socket para el cliente.
  	fd_cli = socket(PF_INET, SOCK_STREAM, 0);
  	if (fd_cli == -1) { 
  		perror("Fallo al crear el socket\n") ; 
  		return -1 ; 
  	}
   
  
  	//Inicializar el número de puerto y direcciones
  	struct sockaddr_in address;
  	address.sin_family = AF_INET;
  	address.sin_addr.s_addr = inet_addr("127.0.0.1");
  	address.sin_port = htons(7734);
 	len = sizeof(address);
  
	//Iniciar la conexión
 	int result = connect(fd_cli, (struct sockaddr *)&address, len);
  	if(result < 0){
		perror("Error de conexión");
		exit(-1);
  	}

  	while(1){
		//rdm = rand() % 9;
		if(fork() == 0){
			int pid_c = getpid();
			rc = write(fd_cli, &pid_c, 1);
			sleep(5);
			read(fd_cli, &pid_c, 1);
			if(DEBUG) printf("Proceso con id enviado : %d\n",pid_c);
		}
        	//value = r4_nor ( &seed, kn, fn, wn );
        	//if (value < 0) value=value*(-1);
        	//sensor_reading= floor(value*Dsd+Davg);
      		//delay=floor(1000000/(value*Tsd+Tfreq));
  		//usleep(delay);
  		/*rc = write(fd_cli, &rdm, 1);
		sleep(5);
  		read(fd_cli, &rdm, 1);	
  		// DEBUG <- 0 TO TEST AWTU
  		if (DEBUG) printf ( "data to be send id-sensor %d\n",rdm);
  		// INSERTAR IPC PARA ENVIO DE MENSAJES AQUI!!*/
       
    	}
    	close(fd_cli);
    	exit(0);
  
  	return(EXIT_SUCCESS);
}

    //printf("id 1 : %d\n", ids[0]);

    /*for(int n = 0; n < 5; n++){
	    printf("Hijo : %d, id : %d\n", n+1, ids[n]);
    }
     
	printf("Programando de lado del cliente\n");
	float fn[128],Tfreq;
	int ID_sensor,Stype,Davg,Dsd,Tsd,sensor_reading;		
	uint32_t kn[128];
	unsigned int delay;
	uint32_t seed;
	float value;
	float wn[128];
	int rc, len;

	//Creación del socket para el cliente.
  	fd_cli = socket(PF_INET, SOCK_STREAM, 0);
  	if (fd_cli == -1) { 
  		perror("Fallo al crear el socket\n") ; 
  	return -1; 
  	}

	//Inicializar el número de puerto y direcciones
  	struct sockaddr_in address;
  	address.sin_family = AF_INET;
  	address.sin_addr.s_addr = inet_addr("127.0.0.1");
  	address.sin_port = htons(7734);
  	len = sizeof(address);

	//Iniciar la conexión
  	int result = connect(fd_cli, (struct sockaddr *)&address, len);
  	if(result < 0){
		perror("Error de conexión");
		exit(-1);
 	}
  	while(1){
        	value = r4_nor ( &seed, kn, fn, wn );
        	if (value < 0) value=value*(-1);
        	sensor_reading= floor(value*Dsd+Davg);
      		delay=floor(1000000/(value*Tsd+Tfreq));
  		usleep(delay);
  		rc = write(fd_cli, &sensor_reading, 1);
  		read(fd_cli, &sensor_reading, 1);	
  		// DEBUG <- 0 TO TEST AWTU
  		if (DEBUG) printf ( "data to be send id-sensor %d, type %d, record %d, delay %d ms. \n",ID_sensor,Stype,sensor_reading,delay/1000);
  		// INSERTAR IPC PARA ENVIO DE MENSAJES AQUI!!
  		if(ID_sensor == 1){
  			break;
  		}
       
    	}
        //rc = write(fd_cli, &sensor_reading, 1);


        close(fd_cli);
        exit(0);
}
// structure for message queue
struct mesg_buffer {
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

