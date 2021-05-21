#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <mqueue.h>
#include <sys/wait.h>
#include <errno.h> //Control de errores
#include <string.h> //Para la funcion strerror()

#define MAX_SIZE    1024
#define QUEUE_NAME  "/una_cola"
#define MSG_STOP     "exit"

int main()
{
	int must_stop = 0;
	// Descriptor de la cola
	mqd_t mq;
	// Buffer para la lectura/escritura
	char buffer[MAX_SIZE];
	// Atributos de la cola
	struct mq_attr attr;
    // Almacena el nombre de la cola
    char queue_name[100];
	// Resultado de las operaciones
	int resultado;
	// Para realizar el fork
    pid_t rf, flag;
    int status;
	// Inicializar los atributos de la cola.
	attr.mq_maxmsg = 10;        // Maximo número de mensajes
	attr.mq_msgsize = MAX_SIZE; // Maximo tamaño de un mensaje. Tener en cuenta que debe incluir el '/0'
    // Nombre para la cola. Al concatenar el login, sera unica en un sistema compartido.
    sprintf(queue_name, "%s-%s", QUEUE_NAME, getenv("USER"));

	// Realizar el fork
	rf = fork();
	switch (rf)
	{
		// Error
		case -1:
			printf ("No he podido crear el proceso hijo \n");
			exit(1);

		case 0: // Hijo. El hijo solo se encargará de escribir.

			/* Apertura de la cola
			   O_CREAT: si no existe, se crea
			   O_RDWR: lectura/escritura
			   O_RDONLY: solo lectura
			   O_WRONLY: solo escritura
			   0644: permisos rw-r--r--
			         permisos de lectura y escritura para el propietario, y de sólo lectura para el grupo y para otros
			   attr: estructura con atributos para la cola  */
			mq = mq_open(queue_name, O_CREAT | O_RDWR, 0644, &attr);
            printf ("[HIJO]: El nombre de la cola es: %s\n", queue_name);
            printf ("[HIJO]: El descriptor de la cola es: %d\n", (int) mq);

			if(mq==-1)
			{
				perror("[HIJO]: Error en la apertura de la cola");
				exit(-1);
			}
			printf ("[HIJO]: Mi PID es %d y mi PPID es %d\n", getpid(), getppid());

			printf("[HIJO]: Mandando mensajes al servidor (escribir \"%s\" para parar):\n", MSG_STOP);
			do
			{
				printf("[HIJO]> ");

				/* Leer por teclado. Según la documentación, fgets lo hace de esta manera:
				It stops when either (n-1) characters are read, the newline character is read,
				or the end-of-file is reached, whichever comes first.
				Automáticamente fgets inserta el fin de cadena '\0'
				*/
				fgets(buffer, MAX_SIZE, stdin);

				// Enviar y comprobar si el mensaje se manda
				if(mq_send(mq, buffer, MAX_SIZE, 0) != 0)
				{
					perror("[HIJO]: Error al enviar el mensaje");
					exit(-1);
				}
				if (strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0)
					must_stop = 1;

				// Número de bytes leidos
				ssize_t bytes_read;

				// Recibir el mensaje
				bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
				// Comprar que la recepción es correcta (bytes leidos no son negativos)
				if(bytes_read < 0)
				{
					perror("[HIJO]: Error al recibir el mensaje");
					exit(-1);
				}
				// Cerrar la cadena
				//buffer[bytes_read] = '\0';
				printf("%s\n", buffer);

			// Iterar hasta escribir el código de salida
			}while (!must_stop);
			// Cerrar la cola
			if(mq_close(mq) == -1)
			{
				perror("[HIJO]: Error cerrando la cola");
				exit(-1);
			}
            printf("[HIJO]: Cola cerrada.\n");
				exit(0);
			break; //Saldría del switch()

		default: // Padre. El padre solo se encargará de leer
			/* Apertura de la cola */
			mq = mq_open(queue_name, O_CREAT | O_RDWR, 0644, &attr);
            printf ("[PADRE]: El nombre de la cola es: %s\n", queue_name);
            printf ("[PADRE]: El descriptor de la cola es:%d\n", (int) mq);

			if(mq==-1)
			{
				perror("[PADRE]: Error en la apertura de la cola");
				exit(-1);
			}

			printf ("[PADRE]: Mi PID es %d y el PID de mi hijo es %d \n", getpid(), rf);
			printf ("[PADRE]: Recibiendo mensaje (espera bloqueante)...\n");

			do
				{
					// Número de bytes leidos
					ssize_t bytes_read;

					// Recibir el mensaje
					bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
					// Comprar que la recepción es correcta (bytes leidos no son negativos)
					if(bytes_read < 0)
					{
						perror("[PADRE]: Error al recibir el mensaje");
						exit(-1);
					}
					// Cerrar la cadena
					//buffer[bytes_read] = '\0';

					// Comprobar el fin del bucle
					if (strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0)
						must_stop = 1;
					else
						printf("[PADRE]: Recibido el mensaje: %s", buffer);

						sprintf(buffer, "[HIJO]: Número de caracteres recibidos por mi padre: %ld", (strlen(buffer)-1));
						// Enviar y comprobar si el mensaje se manda
						if(mq_send(mq, buffer, MAX_SIZE, 0) != 0)
						{
							perror("[PADRE]: Error al enviar el mensaje");
							exit(-1);
						}

				} while (!must_stop); 	// Iterar hasta que llegue el código de salida, es decir, la palabra exit

			// Cerrar la cola
			if(mq_close(mq) == -1)
			{
				perror("[PADRE]: Error cerrando la cola");
				exit(-1);
			}
			printf("[PADRE]: Cola cerrada.\n");

			// Eliminar la cola
			if(mq_unlink(queue_name) == -1)
			{
				perror("[PADRE]: Error eliminando la cola");
				exit(-1);
			}

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
	exit(0);
}
