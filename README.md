# Tarea1-MCI
Tarea 1 de Estructura de Datos 2024 Paralelo 1

## Cómo ejecutar el programa
Para ejecutar el programa primero debemos compilar (en la carpeta raíz):
````
gcc tdas/*.c main.c -Wno-unused-result -o main
````
Y luego ejecutar
````
./main
````
## Control de funcionamiento
Se han probado las 5 funciones en distintas situaciones y no se han encontrado fallos de lógica o compilación.
## Ejemplo de funcionamiento
````
========================================
     Sistema de Gestión Hospitalaria
========================================
1) Registrar paciente
2) Asignar prioridad a paciente
3) Mostrar lista de espera
4) Atender al siguiente paciente
5) Mostrar pacientes por prioridad
6) Salir
Ingrese su opción: 
````
En esta pantalla se le pedirá al usuario que ingrese el número correspondiente a la opción deseada. En este ejemplo usaremos la opción 1.
Se le pedirá al usuario los datos del nuevo paciente a registrar: Su nombre, edad, y síntoma. El programa guardará automáticamente su hora de llegada y asignará su prioridad en Bajo.
````
========================================
     Sistema de Gestión Hospitalaria
========================================
1) Registrar paciente
2) Asignar prioridad a paciente
3) Mostrar lista de espera
4) Atender al siguiente paciente
5) Mostrar pacientes por prioridad
6) Salir
Ingrese su opción: 1
Registrar nuevo paciente
Ingrese nombre del paciente: John Doe
Ingrese edad del paciente: 25
Ingrese síntoma del paciente: Inflamación en garganta
Presione una tecla para continuar...
````
