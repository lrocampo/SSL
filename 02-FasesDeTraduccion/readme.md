# TP 2

## Cómo detener las fases de traducción con GCC
Tenemos a disposición distintos flags para indicarle a GCC qué es lo que debe hacer:
* -c: Compila o ensambla los archivos fuente, pero no los linkea. El output de esta operación es un archivo objeto. Por defecto, el nombre del archivo objeto es el mismo que el archivo fuente pero cambiando el .c por un .o.
* -S: Se detiene inmediatamente despues de compilar, no ensambla. El output es código en assembly por cada archivo que no posea assembly code.
* -E: Se detiene inmediatamente despues de preprocesar, no compila. El output es código fuente preprocesado, que es enviado a standard output.
* -o: Asociado al output principal, sin importar de que tipo de output se trate.

## Secuencia de pasos
1. Preprocesador
   
   a. Escribimos el hello2.c
   ```c
    #include <stdio.h>

    int/*medio*/main(void) {
        int i=42;
        prontf("La respuesta es %d\n");
   ``` 
   b. Pasamos a preprocesar con el comando 
   ```
   gcc -E hello2.c -o hello2.i
   ``` 

    Al preprocesar el archivo fuente, observamos que en hello.i se ha introducido todos los prototipos de funciones que pertenecen a stdio.h, así como typdefs y structs. Al final del archivo, se encuentra el código escrito por nosotros.

    c. Escribimos hello3.c, una nueva variante:
    ```c
    int printf(const char * restrict s, ...);
    int main(void){
    int i=42;
    prontf("La respuesta es %d\n");
    ```

    d. `printf`  retorna un valor de tipo int y recibe un puntero que apunta a valores de char.

    e. Preprocesamos hello3.c de forma similar a cómo lo hicimos con hello2.c. A diferencia de hello2.i, hello3.i no posee los prototipos ni demas definiciones de la biblioteca standard, pues este header no ha sido incluido en su archivo fuente original.

2.  Compilación
   
    a. Compilaremos el hello3.i con el siguiente comando:
    ```
        gcc -S hello3.i -o hello3.s
    ``` 

    Obtenemos este mensaje como resultado:

    ```
    hello3.c:4:2: error: expected declaration or statement at end of input
    ```
    Tenemos un error en la linea 4, gcc nos dice que esperaba algo al final pero no lo encontró. Seguramente se refiere a la llave que falta para cerrar la estructura del main.

    b. Corregiremos eso en un nuevo archivo hello4.c y volvemos a realizar el proceso desde el inicio:
    ```
        gcc -E hello4.c -o hello4.i
        gcc -S hello4.i -o hello4.s
    ``` 

    c. El resultado del último comando es una archivo con código assembly. El lenguaje assembly está en el medio de los lenguajes de alto nivel como C o Java y el código de máquina (binario). En un lenguaje compilado, el compilador transforma el código de alto nivel a código en assembly.

    d. Ensamblaremos el hello4.s, ejecutando:
    ```
        gcc -c hello4.s -o hello4.o 
    ```
    Obtenemos como resultado un archivo objeto hello4.o.

3. Vinculación
   
   a. Vincularemos el hello4.o con la biblioteca estandar:
    ```
        gcc hello4.o -o hello4
    ```
    El linker nos devuelve el siguiente error:
    ```
    /usr/bin/ld: hello4.o: in function `main':
    hello4.c:(.text+0x20): undefined reference to `prontf'
    collect2: error: ld returned 1 exit status

    ```
    b. No entiende a qué hace referencia prontf. Esto es un pequeño typo. Lo solucionamos en un archivo fuente aparte hello5.c y volvemos a hacer el proceso:
    ```
        gcc hello5.c -o hello5
    ```
    c. Ejecutamos hello5 de la siguiente manera:
    ```
        ./hello5
    ```
    Imprime lo siguiente por pantalla:
    ```
        La respuesta es -91444936
    ```
    
    Si lo ejecutamos otra vez:
    ```
        La respuesta es 1866102168
    ```

    El valor entero que está imprimiendo en cada ocasión es basura.

4. Correción de Bug
   
   a. Corregimos el bug en hello6.c. Le diremos a `printf` que imprima el valor de `i`. Buildeamos y ejecutamos el archivo, obteniendo como resultado:

   ```
    La respuesta es 42
   ```

   Que es lo esperado.

5. Remoción de prototipo

    a. Escribimos una variante llamada hello7.c:
    ``` c
    int main(void){
        int i=42;
        printf("La respuesta es %d\n", i);
    }
    ```
    b. A pesar de que removemos el prototipo, el código compila y se ejecuta adecuadamente. Por qué es esto? printf es una función cuya definición se encuentra en la C Standard Library (libc.so en Linux). Esta se encuentra linkeada por default en cualquier programa de C. Sin embargo, no es una buena practica pasar de alto los prototipos de las funciones. Por lo tanto, lo correcto es incluir el header stdio.h

6. Compilación Separada: Contratos y Módulos

    a. Creamos los archivos studio1.c y hello8.c. studio1.c contiene la siguiente implementación de prontf:

    ``` c
    void prontf(const char* s, int i) {
        printf("La respuesta es %d\n", i);  
    }
    ```
    hello8.c es muy similar a hello4.c:
    ``` c
    int main(void){
        int i=42;
        prontf("La respuesta es %d\n", i);
    }
    ```
    
    b. Para poder ejecutar este programa, debemos ejecutar el siguiente comando:
    
    ```
    gcc hello8.c studio1.c -o hello8
    ```
    Esto generará el ejecutable hello8.

    c. ¿qué ocurre si eliminamos o agregamos argumentos a la invocación de prontf?
    Si le sacamos el primer argumento, compila pero no obtenemos el resultado esperado. Sucede lo mismo que en el inciso 3c.
    
    Si solo le sacamos el segundo argumento, no compila. Y nos arroja un error: una variable no ha sido declarada antes de ser utilizada:
    ```
    ...
    studio1.c:2:33: error: ‘i’ undeclared (first use in this function)
    2 |  printf("La respuesta es %d\n", i);
      |
    ...         
    ```
    Si le agregamos un nuevo argumento, compila y se ejecuta adecuadamente.

    d. Escribiremos un header para nuestra unidad de traducción studio.

    i. Contenido de studio.h:
    ```
    #ifndef _STUDIO_H_INCULDED_
    #define _STUDIO_H_INCULDED_

    void prontf(const char*, int);

    #endif
    ```

    ii. Escribiremos hello9.c, un cliente que sí incluye el contrato.

    ``` c
    #include "studio.h" // Interfaz que importa
    int main(void){
        int i=42;
        prontf("La respuesta es %d\n", i);
    }
    ```

    iii. Escribimos el studio2.c:
    ``` c
    #include "studio.h" // Interfaz que exporta
    #include <stdio.h> // Interfaz que importa
    void prontf(const char* s, int i){
        printf("La respuesta es %d\n", i);
    }
    ```

    iv. ¿Qué ventaja da incluir el contrato en los clientes y en el
proveedor? La principal ventaja es que los consumidores dependan de la abstracción y no de la implementación del contrato.