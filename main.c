#include "tdas/list.h"
#include "tdas/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definimos el struct que será el formato de cada paciente.
typedef struct
{
  char nombre[50];
  int edad;
  char sintoma[50];
  char prioridad[6];
  int horaIngreso;
  int minutoIngreso;
} tipoPaciente;

void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar();
  getchar();
}

void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir");
}

// Función para registrar un paciente. Requiere la lista de pacientes y
// la variable para gestionar el tiempo.
void registrar_paciente(List *pacientes, time_t *tiempo)
{
  // Reservamos memoria para el nuevo paciente, que manejaremos durante la función
  // en una variable temporal.
  tipoPaciente *pacienteNuevo = (tipoPaciente *) malloc(sizeof(tipoPaciente));
  // Llamamos al struct tm, que nos ayudará a almacenar la hora de registro del paciente.
  struct tm *infoTiempo;
  int tempHora;

  // Obtenemos nombre, edad y síntoma del paciente y lo almacenamos en pacienteNuevo.
  printf("Registrar nuevo paciente\n");
  printf("Ingrese nombre del paciente: ");
  scanf(" %49[^\n]", pacienteNuevo->nombre);
  printf("Ingrese edad del paciente: ");
  scanf("%i", &pacienteNuevo->edad);
  printf("Ingrese síntoma del paciente: ");
  scanf(" %49[^\n]", pacienteNuevo->sintoma);
  strcpy(pacienteNuevo->prioridad, "Bajo");

  // Recibimos la hora actual con este bloque
  time(tiempo);
  infoTiempo = localtime(tiempo);
  // Y después manipulamos la hora para que esté a la
  // zona horaria de Chile.
  tempHora = infoTiempo->tm_hour -= 4;
  if (tempHora < 0) tempHora += 24;

  // Se guardan hora y minuto de ingreso en 2 variables int.
  pacienteNuevo->horaIngreso = tempHora;
  pacienteNuevo->minutoIngreso = infoTiempo->tm_min;

  // Se almacena el paciente registrado en la lista.
  list_pushBack(pacientes, pacienteNuevo);
}

// Función para mostrar a todos los pacientes por orden de prioridad y hora 
// de llegada.
void mostrar_lista_pacientes(List *pacientes)
{
  // Si no hay pacientes en la lista, se
  // volverá al menú.
  tipoPaciente *aux = list_first(pacientes);
  if (aux == NULL)
  {
    printf("No hay pacientes en la lista\n\n");
    return;
  }

  // Imprimimos todos los pacientes.
  printf("Pacientes en espera: \n");
  int numPaciente = 1;
  printf("\n");
  while (aux != NULL)
  {
    printf("Paciente N°%i: ", numPaciente);
    printf("\n\n");
    printf("Nombre: %s\n", aux->nombre);
    printf("Edad: %i\n", aux->edad);
    printf("Síntoma: %s\n", aux->sintoma);
    printf("Hora Ingreso: %02d:%02d\n", aux->horaIngreso, aux->minutoIngreso);
    printf("Prioridad: %s\n\n", aux->prioridad);
    aux = list_next(pacientes);
    numPaciente++;
  }
}

// Función para reordenar los pacientes después de asignar nueva prioridad.
void reordenar_pacientes(List *pacientes)
{
  // Creamos una lista temporal para auxiliar el proceso
  List *listaTemp = list_create();

  // Comenzamos a enviar los pacientes a listaTemp
  tipoPaciente *aux = list_first(pacientes);
  while (aux != NULL)
    {
      // Nos aseguramos de enviar primero los de prioridad Alto.
      if (strcmp(aux->prioridad, "Alto") == 0) list_pushBack(listaTemp, aux);
      aux = list_next(pacientes);
    }

  aux = list_first(pacientes);
  while (aux != NULL)
  {
    // Enviamos los de prioridad Medio.
    if (strcmp(aux->prioridad, "Medio") == 0) list_pushBack(listaTemp, aux);
    aux = list_next(pacientes);
  }

  aux = list_first(pacientes);
  while (aux != NULL)
  {
    // Enviamos los de prioridad Bajo.
    if (strcmp(aux->prioridad, "Bajo") == 0) list_pushBack(listaTemp, aux);
    aux = list_next(pacientes);
  }
  // Limpiamos la lista original.
  list_clean(pacientes);

  // Enviamos todos los pacientes reordenados a la lista original.
  aux = list_first(listaTemp);
  while (aux != NULL)
    {
      list_pushBack(pacientes, aux);
      aux = list_next(listaTemp);
    }

  // Liberamos la memoria de la lista original.
  free(listaTemp);
}

// Función para asignar nueva prioridad de paciente y reordenarlos a todos.
void asignar_prioridad_y_reordenar(List *pacientes)
{
  // Si no hay pacientes en la lista, se
  // volverá al menú.
  tipoPaciente *aux = list_first(pacientes);
  if (aux == NULL)
  {
    printf("No hay pacientes en la lista\n\n");
    return;
  }

  // Le pedimos al usuario el nombre del paciente a
  // modificar.
  char nombreTemp[50];
  printf("Ingrese el nombre del paciente: ");
  scanf(" %49[^\n]", nombreTemp);
  printf("\n");
  
  int numPrio = 0;
  while (aux != NULL)
    {
      // Si se encuentra al paciente, se pedirá ingresar un número del
      // 1 al 3 que corresponden a cada nivel de prioridad.
      if (strcmp(aux->nombre, nombreTemp) == 0)
      {
        printf("Ingrese nueva prioridad (1|Bajo  2|Medio  3|Alto): ");
        scanf("%i", &numPrio);
        // Un switch() para reescribir la prioridad del paciente.
        // Si no es válida, se cancelará y se volverá al menú.
        switch (numPrio)
          {
            case 1:
              strcpy(aux->prioridad, "Bajo");
              break;
            case 2:
              strcpy(aux->prioridad, "Medio");
              break;
            case 3:
              strcpy(aux->prioridad, "Alto");
              break;
            default:
              printf("Prioridad no válida\n\n");
              return;
          }
        printf("Prioridad modificada con éxito\n\n");
        break;
      }
      // Si no hay pacientes en la lista, se
      // volverá al menú.
      aux = list_next(pacientes);
      if (aux == NULL)
      {
        printf("Paciente no encontrado\n\n");
        return;
      }
    }
  // Una vez modificada la prioridad, se proceden a reordenar
  // los pacientes.
  printf("Reordenando pacientes...\n");
  reordenar_pacientes(pacientes);
  printf("Pacientes reordenados con éxito\n\n");
}

// Función para atender a un paciente.
void atender_paciente(List *pacientes)
{
  // Si no hay pacientes en la lista, se
  // volverá al menú.
  tipoPaciente *aux = list_first(pacientes);
  if (aux == NULL)
  {
    printf("No hay pacientes en la lista\n\n");
    return;
  }

  // A continuación se muestran por pantalla
  // los datos del paciente a atender.
  printf("Atendiendo al paciente:\n\n");
  printf("Nombre: %s\n", aux->nombre);
  printf("Edad: %i\n", aux->edad);
  printf("Síntoma: %s\n", aux->sintoma);
  printf("Hora Ingreso: %02d:%02d\n", aux->horaIngreso, aux->minutoIngreso);
  printf("Prioridad: %s\n\n", aux->prioridad);
  // Se retira al paciente de la lista.
  printf("Paciente %s se ha atendido\nEliminando de la lista...\n\n", aux->nombre);
  list_popFront(pacientes);
}

void mostrar_pacientes_por_prioridad(List *pacientes)
{
  // Si no hay pacientes en la lista, se
  // volverá al menú.
  tipoPaciente *aux = list_first(pacientes);
  if (aux == NULL)
  {
    printf("No hay pacientes en la lista\n\n");
    return;
  }
  
  int numPrio;
  char prioElegida[6];

  // Se le pedirá al usuario que seleccione una prioridad con
  // números del 1 al 3.
  printf("Por favor ingrese prioridad (1|Bajo  2|Medio  3|Alto): ");
  scanf("%i", &numPrio);
  // switch() para almacenar la prioridad a mostrar.
  // Si no es válida, se volverá al menú.
  switch (numPrio)
    {
      case 1:
        strcpy(prioElegida, "Bajo");
        break;
      case 2:
        strcpy(prioElegida, "Medio");
        break;
      case 3:
        strcpy(prioElegida, "Alto");
        break;
      default:
        printf("Prioridad no válida\n\n");
        return;
    }

  // Se imprimen por pantalla los pacientes correspondientes
  // a la prioridad seleccionada.
  printf("Pacientes con prioridad %s: \n\n", prioElegida);
  int numPaciente = 1;
  while (aux != NULL)
    {
      if (strcmp(aux->prioridad, prioElegida) == 0)
      {
        printf("Paciente N°%i: ", numPaciente);
        printf("\n\n");
        printf("Nombre: %s\n", aux->nombre);
        printf("Edad: %i\n", aux->edad);
        printf("Síntoma: %s\n", aux->sintoma);
        printf("Hora Ingreso: %02d:%02d\n", aux->horaIngreso, aux->minutoIngreso);
        numPaciente++;
      }
      aux = list_next(pacientes);
    }
  // Si numPaciente no sufrió cambios quiere decir que no había ningún paciente válido
  // y se vuelve al menú.
  if (numPaciente == 1) printf("No hay pacientes con prioridad %s\n\n", prioElegida);
}

int main() {
  time_t tiempoActual;
  
  char opcion;
  List *pacientesBajo = list_create();
  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion);

    switch (opcion) {
    case '1':
      registrar_paciente(pacientesBajo, &tiempoActual);
      break;
    case '2':
      asignar_prioridad_y_reordenar(pacientesBajo);
      break;
    case '3':
      mostrar_lista_pacientes(pacientesBajo);
      break;
    case '4':
      atender_paciente(pacientesBajo);
      break;
    case '5':
      mostrar_pacientes_por_prioridad(pacientesBajo);
      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  list_clean(pacientesBajo);

  return 0;
}
