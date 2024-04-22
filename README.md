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
- Cuando se registra un paciente, el código puede corromperse si el usuario ingresa un carácter no numérico en la entradad de edad.
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
Ingrese su opción: 3
Pacientes en espera: 

Paciente N°1: 

Nombre: John Doe
Edad: 25
Síntoma: Inflamación de garganta
Hora Ingreso: 21:59
Prioridad: Bajo

Presione una tecla para continuar...
````
Después de añadir un paciente, podemos visualizarlo en la lista de espera eligiendo la opción 3.
