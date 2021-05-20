#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <errno.h> //Control de errores
#include <string.h> //Para la funcion strerror(), que permite describir el valor de errno como cadena.

/***************************************************************************************************
Cuando la comunicación es simple y ambos extremos de la comunicación han sido generados
con un fork() o pertenecen al mismo proceso, se pueden utilizar tuberías anónimas (pipes).

Implemente un programa que cree un proceso hijo mediante fork(), y usando tuberías realice
lo siguiente:

El proceso padre deberá generar cinco números aleatorios y cada uno de ellos irá en un mensaje
independiente y lo introducirá en la tubería, mientras que el proceso hijo lo leerá de la tubería.

Ejemplo de salida esperada (tenga en cuenta que depende del planificador):
jfcaballero@NEWTS:~$ ./a.out
[PADRE]: Mi PID es 3612 y el PID de mi hijo es 3613 
[PADRE]: Escribo el número aleatorio 2028 en la tubería...
[HIJO]: Mi PID es 3613 y mi PPID es 3612
[PADRE]: Escribo el número aleatorio 2179 en la tubería...
[HIJO]: Leo el número aleatorio 2028 de la tubería.
[PADRE]: Escribo el número aleatorio 4716 en la tubería...
[HIJO]: Leo el número aleatorio 2179 de la tubería.
[PADRE]: Escribo el número aleatorio 2044 en la tubería...
[HIJO]: Leo el número aleatorio 4716 de la tubería.
[PADRE]: Escribo el número aleatorio 2788 en la tubería...
[HIJO]: Leo el número aleatorio 2044 de la tubería.
[HIJO]: Leo el número aleatorio 2788 de la tubería.
[PADRE]: Tubería cerrada...
[HIJO]: Tubería cerrada ...
[PADRE]: Hijo con PID 3613 finalizado, status = 0
[PADRE]: Valor de errno = 10, definido como: No child processes
**************************************************************************************************/



int main() 
{
	// Para realizar el fork
	pid_t rf;
	int flag, status;
	// Para controlar los valores devueltos por las funciones (control de errores)
	int resultado;
	// Lo que vamos a leer y escribir de la tubería
	float a = 5.3;
	float numeroAleatorio1;
	float numeroAleatorio2;
	float sumaAleatorios;
	// Descriptores de los dos extremos de la tubería
	int fileDes[2];
	// Iterador
	int i=0;

	// Creamos la tubería
	resultado = pipe(fileDes);
	if(resultado==-1)
	{
		printf("\nERROR al crear la tubería.\n");
		exit(1);
	}
	
	rf = fork();
	switch (rf)
	{
		case -1:
			printf ("No se ha podido crear el proceso hijo...\n");
			exit(EXIT_FAILURE);
		case 0:
			printf ("[HIJO]: Mi PID es %d y mi PPID es %d\n", getpid(), getppid());
			
			close(fileDes[1]);
	
			//Recibimos un mensaje a través de la cola
			resultado = read( fileDes[0], &sumaAleatorios, sizeof(int));
			
			if(resultado != sizeof(int))
			{
				printf("\n[HIJO]: ERROR al leer de la tubería...\n");
				exit(EXIT_FAILURE);
			}
			// Imprimimos el campo que viene en la tubería
			printf("[HIJO]: El resultado de la suma leido de la tubería es: %f.\n", sumaAleatorios);
					
			// Cerrar el extremo que he usado
			printf("[HIJO]: Tubería cerrada ...\n");
			close(fileDes[0]);
			break;

		default:
			printf ("[PADRE]: Mi PID es %d y el PID de mi hijo es %d \n", getpid(), rf);
			
			close(fileDes[0]);
			
			srand(time(NULL)); // Semilla de los números aleatorios establecida a la hora actual
				
			// Rellenamos los campos del mensaje que vamos a enviar
			numeroAleatorio1 =  (((float)rand()/(float)(RAND_MAX)) * a); //Número aleatorio entre 0 y 4999
			numeroAleatorio2 =  (((float)rand()/(float)(RAND_MAX)) * a);

			printf("[PADRE]: Escribo el resultado de la suma de los números aleatorios %f y %f en la tubería...\n", numeroAleatorio1, numeroAleatorio2);
			
			sumaAleatorios = numeroAleatorio1 + numeroAleatorio2;

			// Mandamos el mensaje
			resultado = write( fileDes[1], &sumaAleatorios, sizeof(int));
			
			if(resultado != sizeof(int))
			{
				printf("\n[PADRE]: ERROR al escribir en la tubería...\n");
				exit(EXIT_FAILURE);
			}
			
			
			// Cerrar el extremo que he usado
			close(fileDes[1]);
			printf("[PADRE]: Tubería cerrada...\n");
			
			/*Espera del padre a los hijos*/
	        while ( (flag=wait(&status)) > 0 ) 
	        {
		        if (WIFEXITED(status)) {
			        printf("Proceso Padre, Hijo con PID %ld finalizado, status = %d\n", (long int)flag, WEXITSTATUS(status));
		        } 
		        else if (WIFSIGNALED(status)) {  //Para seniales como las de finalizar o matar
			        printf("Proceso Padre, Hijo con PID %ld finalizado al recibir la señal %d\n", (long int)flag, WTERMSIG(status));
		        } 		
	        }
	        if (flag==(pid_t)-1 && errno==ECHILD)
	        {
		        printf("Proceso Padre %d, no hay mas hijos que esperar. Valor de errno = %d, definido como: %s\n", getpid(), errno, strerror(errno));
	        }
	        else
	        {
		        printf("Error en la invocacion de wait o waitpid. Valor de errno = %d, definido como: %s\n", errno, strerror(errno));
		        exit(EXIT_FAILURE);
	        }			 
	}
	exit(EXIT_SUCCESS);
}
