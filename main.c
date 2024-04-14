#include "tdas/list.h"
#include "tdas/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void registrar_paciente(List *pacientes, time_t *tiempo)
{
  tipoPaciente *pacienteNuevo = (tipoPaciente *) malloc(sizeof(tipoPaciente));
  struct tm *infoTiempo;
  int tempHora;
  
  printf("Registrar nuevo paciente\n");
  printf("Ingrese nombre del paciente: ");
  scanf(" %49[^\n]", pacienteNuevo->nombre);
  printf("Ingrese edad del paciente: ");
  scanf("%i", &pacienteNuevo->edad);
  printf("Ingrese síntoma del paciente: ");
  scanf(" %49[^\n]", pacienteNuevo->sintoma);
  strcpy(pacienteNuevo->prioridad, "Bajo");

  time(tiempo);
  infoTiempo = localtime(tiempo);
  tempHora = infoTiempo->tm_hour -= 4;
  if (infoTiempo->tm_hour < 0) infoTiempo->tm_hour += 24;
  
  pacienteNuevo->horaIngreso = tempHora;
  pacienteNuevo->minutoIngreso = infoTiempo->tm_min;

  list_pushBack(pacientes, pacienteNuevo);
}

void mostrar_lista_pacientes(List *pacientes)
{
  tipoPaciente *aux = list_first(pacientes);
  if (aux == NULL)
  {
    printf("No hay pacientes en la lista\n\n");
    return;
  }
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

void reordenar_pacientes(List *pacientes)
{
  List *listaTemp = list_create();
  
  tipoPaciente *aux = list_first(pacientes);
  while (aux != NULL)
    {
      if (strcmp(aux->prioridad, "Alto") == 0) list_pushBack(listaTemp, aux);
      aux = list_next(pacientes);
    }

  aux = list_first(pacientes);
  while (aux != NULL)
  {
    if (strcmp(aux->prioridad, "Medio") == 0) list_pushBack(listaTemp, aux);
    aux = list_next(pacientes);
  }

  aux = list_first(pacientes);
  while (aux != NULL)
  {
    if (strcmp(aux->prioridad, "Bajo") == 0) list_pushBack(listaTemp, aux);
    aux = list_next(pacientes);
  }
  list_clean(pacientes);

  aux = list_first(listaTemp);
  while (aux != NULL)
    {
      list_pushBack(pacientes, aux);
      aux = list_next(listaTemp);
    }

  free(listaTemp);
}

void asignar_prioridad_y_reordenar(List *pacientes)
{
  tipoPaciente *aux = list_first(pacientes);
  if (aux == NULL)
  {
    printf("No hay pacientes en la lista\n\n");
    return;
  }

  char nombreTemp[50];
  printf("Ingrese el nombre del paciente: ");
  scanf(" %49[^\n]", nombreTemp);
  printf("\n");
  
  int numPrio = 0;
  while (aux != NULL)
    {
      if (strcmp(aux->nombre, nombreTemp) == 0)
      {
        printf("Ingrese nueva prioridad (1|Bajo  2|Medio  3|Alto): ");
        scanf("%i", &numPrio);
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
      aux = list_next(pacientes);
      if (aux == NULL)
      {
        printf("Paciente no encontrado\n\n");
        return;
      }
    }
  printf("Reordenando pacientes...\n");
  reordenar_pacientes(pacientes);
  printf("Pacientes reordenados con éxito\n\n");
}

void atender_paciente(List *pacientes)
{
  tipoPaciente *aux = list_first(pacientes);
  if (aux == NULL)
  {
    printf("No hay pacientes en la lista\n\n");
    return;
  }

  printf("Atendiendo al paciente:\n\n");
  printf("Nombre: %s\n", aux->nombre);
  printf("Edad: %i\n", aux->edad);
  printf("Síntoma: %s\n", aux->sintoma);
  printf("Hora Ingreso: %02d:%02d\n", aux->horaIngreso, aux->minutoIngreso);
  printf("Prioridad: %s\n\n", aux->prioridad);
  printf("Paciente %s se ha atendido\nEliminando de la lista...\n\n", aux->nombre);
  list_popFront(pacientes);
}

void mostrar_pacientes_por_prioridad(List *pacientes)
{
  tipoPaciente *aux = list_first(pacientes);
  if (aux == NULL)
  {
    printf("No hay pacientes en la lista\n\n");
    return;
  }
  
  int numPrio;
  char prioElegida[6];
  
  printf("Por favor ingrese prioridad (1|Bajo  2|Medio  3|Alto): ");
  scanf("%i", &numPrio);
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