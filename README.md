<h1>proyectSO</h1>

<h3>Compilar programa.c</h3>
gcc -o prog programa.c ziggurat.o -lm

<h3>Compilar motorizado.c</h3>
gcc -o motorizado motorizado.c -lm

<h3>Compilar cliente.c</h3>
gcc -o client cliente.c -lm

<h3>Compilar restaurante.c</h3>
gcc -o restaurant cliente.c -lm

<h4>Observación:<h4> 
<p>programa.c funciona como proceso que comparte secciones de memoria compartida con otros procesos, por lo que se lo debe ejecutar primero, y luego los otros programas, restaurante, cliente y motorizado respectivamente</p>

<h3>Ejecutar programa.c</h3>
./prog 'lista de parametros'

<h3>Ejecutar restaurante.c</h3>
./restaurant 

<h3>Ejecutar cliente.c</h3>
./client

<h3>Ejecutar motorizado.c</h3>
./motorizado
