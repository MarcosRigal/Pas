/*
Ejemplo extraído y adaptado del estándar POSIX y glibc.
Enlace a la página de documentación de la implemencación de getopt de glibc:
http://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Options.html
http://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html
*/

/*
./a.out
./a.out -d hola
./a.out -d hola -b
./a.out --delete
./a.out -k
./a.out k    // (Que observas en este caso)?
*/

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char **argv) {
    int c;

    /* Estructura a utilizar por getoptlong */
    static struct option long_options[] = {/* Opciones que no van a actuar sobre un flag */
    //  {<nombre largo>, <recibe/no recibe argumento>, NULL, <nombre corto>}
        {"hide", no_argument, NULL, 'h'},
        {"add", no_argument, NULL, 'a'},
        {"block", no_argument, NULL, 'b'},
        {"delete", required_argument, NULL, 'd'},
        {"create", required_argument, NULL, 'c'},
        {"list", required_argument, NULL, 'l'},
        {"file", required_argument, NULL, 'f'},
        /* Necesario para indicar el final de las opciones */
        {0, 0, 0, 0}
	};

    /* Estas variables servirán para almacenar el resultado de procesar la línea
     * de comandos */
    bool hflag = false;
    bool aflag = false;
    bool bflag = false;
    char *cvalue = NULL;
    char *dvalue = NULL;
    char *lvalue = NULL;
    char *fvalue = NULL;

    /* Deshabilitar la impresión de errores por defecto */
    /* opterr=0; */
    while ( (c= getopt_long(argc, argv, "abd:c:f:", long_options, NULL)) != -1) {
        switch (c) {
       
        case 'h':
            // printf("Opción -a\n");
            hflag = true;
            break;
       
        case 'a':
            // printf("Opción -a\n");
            aflag = true;
            break;

        case 'b':
            // printf("Opción -b\n");
            bflag = true;
            break;
        
        case 'd':
            // printf("Opción -d con valor '%s'\n", optarg);
            dvalue = optarg;
            break;

        case 'c':
            // printf("Opción -c con valor '%s'\n", optarg);
            cvalue = optarg;
            break;

        case 'l':
            // printf("Opción -f con valor '%s'\n", optarg);
            lvalue = optarg;
            break;

        case 'f':
            // printf("Opción -f con valor '%s'\n", optarg);
            fvalue = optarg;
            break;

        case '?':
            /* getopt_long ya imprime su mensaje de error, no es necesario hacer
             * nada */
            /* Si queremos imprimir nuestros propios errores, debemos poner
            opterr=0, y hacer algo como lo que se expone a continuacion. Pruebe
            a hacer sus propios errores. if (optopt == 'c')
                    fprintf (stderr, "La opción %c requiere un argumento.\n",
            optopt);*/
            break;

        default:
            abort();
        }
        printf("optind: %d, optarg: %s, optopt: %c\n", optind, optarg, optopt);
    }

    /* Imprimir el resto de argumentos de la línea de comandos que no son
     * opciones con "-" */
    if (optind < argc) {
        printf("Argumentos ARGV que no son opciones: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        putchar('\n');
    }
    printf("hflag = %d, aflag = %d, bflag = %d, cvalue = %s, dvalue = %s, lvalue = %s, fvalue = %s\n", hflag, aflag, bflag, cvalue, dvalue, lvalue, fvalue);

    exit(0);
}
