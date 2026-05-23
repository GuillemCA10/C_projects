Esta es una selección de algunos de los programas que desarrollé durante mi aprendizaje de C.
Cada programa ilustra un conjunto específico de habilidades fundamentales de programación, como se describe a continuación:

1. CREDIT

Un programa que utiliza el algoritmo de Luhn para validar una tarjeta de crédito e identificar el proveedor.
El programa solicitará al usuario que introduzca su número de tarjeta de crédito.
Si es un número válido de American Express, MasterCard o Visa, devolverá el nombre de la marca correspondiente.
Si no lo es, devolverá "INVALID".

2. FILTER

Aplica filtros de procesamiento de imagen a archivos BMP manipulando directamente los datos de cada píxel.
El programa toma un archivo BMP de entrada y un indicador de filtro, y genera un nuevo archivo BMP con el efecto aplicado.
Los filtros disponibles son escala de grises (-g), sepia (-s), reflejo (-r) y desenfoque (-b).
Uso: ./filter -[indicador] archivo_entrada archivo_salida

3. RECOVER

Recupera archivos JPEG eliminados a partir de una imagen forense de memoria en bruto.
El programa analiza la imagen byte a byte, detecta las firmas binarias que marcan el inicio de cada archivo JPEG,
y los reconstruye como archivos numerados independientes (001.jpg, 002.jpg, etc.). 
Uso: ./recover imagen

4. READABILITY

Calcula el nivel de lectura aproximado de un texto utilizando el índice Coleman-Liau, una fórmula que calibra la dificultad de lectura
en base a parámetros como la longitud de las palabras y las frases. El programa solicitará al usuario que introduzca un texto.
Contará las letras, palabras y frases para calcular el nivel, y devolverá un resultado como "Grade 7" o "Grade 16+".

5. RUNOFF

Simula unas elecciones con varias rondas. Los votantes ordenan los candidatos por orden de preferencia.
El programa elimina al candidato en último lugar en cada ronda y redistribuye sus votos hasta que un candidato obtiene la mayoría.
Uso: ./runoff [candidato ...]

6. SPELLER

Un programa que revisa la ortografía de un archivo de texto comparándolo con un diccionario mediante una tabla hash.
El programa carga el diccionario en memoria y comprueba cada palabra del texto de entrada, reportando todas las palabras mal escritas
junto con métricas de rendimiento para cada etapa del proceso.
Uso: ./speller [DICCIONARIO] texto

COMPILACIÓN

gcc -o credit credit.c
gcc -o readability readability.c
gcc -o recover recover.c
gcc -o runoff runoff.c

Para filter y speller se incluye un Makefile, por lo que debes ejecutar 'make' desde su directorio correspondiente.
