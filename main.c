#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "stack.h"
#include "list.h"

typedef struct
{
    char nombre[20];
    int puntosHabilidad;
    Map *items;
    int cantItems;
    Stack *funcionesAnteriores;
}Datos;

int is_equal_string(void *key1, void *key2)
{
    if (strcmp((char *)key1, (char *)key2) == 0)
    {
        return 1;
    }
    return 0;
}

Datos *crearPerfilJugador()
{
    char nombre[20];
    Datos *datos = (Datos *)malloc(sizeof(Datos));
    printf("Ingrese el nombre del jugador: ");
    scanf("%s", nombre);
    strcpy(datos->nombre, nombre);
    datos->puntosHabilidad = 0;
    datos->items = createMap(is_equal_string);
    datos->cantItems = 0;
    datos->funcionesAnteriores = stack_create();
    printf("Perfil creado con exito\n");
    return datos;
}

void mostrarPerfilJugador(Map *jugadores, char *nombre)
{
    Datos *datos = searchMap(jugadores, nombre);
    if(datos == NULL)
    {
        printf("El jugador no existe\n");
        return;
    }
    
    printf("Nombre: %s\n", datos->nombre);
    printf("Puntos de habilidad: %d\n", datos->puntosHabilidad);
    printf("Items: ");
    if(firstMap(datos->items) != NULL)
    {
        while(nextMap(datos->items) != NULL)
        {
            printf("%s, ", (char *)firstMap(datos->items));
        }
        printf("%s\n", (char *)firstMap(datos->items));
    }
    else
    {
        printf("No tiene items\n");
    }
}

void agregarItem(Map *jugadores, char *nombre)
{
    Datos *datos = searchMap(jugadores, nombre);
    if(datos == NULL)
    {
        printf("El jugador no existe\n");
        return;
    }
    printf("Ingrese el nombre del item: ");
    char item[20];
    scanf("%s", item);
    if(searchMap(datos->items, item) != NULL)
    {
        printf("El item ya existe\n");
        return;
    }
    insertMap(datos->items, item, item);
    stack_push(datos->funcionesAnteriores, datos);
}

void eliminarItem(Map *jugadores)
{
    char nombre[20];
    printf("Ingrese el nombre del jugador: ");
    scanf("%s", nombre);
    if (searchMap(jugadores, nombre) != NULL)
    {
        Datos *datos = searchMap(jugadores, nombre);
        if (firstList(datos->items) != NULL)
        {
            char item[20];
            printf("Ingrese el nombre del item a eliminar: ");
            scanf("%s", item);
            if (firstList(datos->items) != NULL)
            {
                for(firstList(datos->items);nextList(datos->items)!=NULL;nextList(datos->items))
                {
                    if(strcmp(item,(char *)datos->items)){
                        popCurrent(datos->items);
                        printf("El item ha sido eliminado\n");
                        break;
                    }
                }
            }
            printf("El item no existe\n");
        }
        else
        {
            printf("El jugador no tiene items\n");
        }
    }
    else
    {
        printf("El jugador no existe\n");
    }
} 

void SumarPuntosHabilidad(Map *jugadores, char *nombre)
{
    Datos *datos = searchMap(jugadores, nombre);
    if(datos == NULL)
    {
        printf("El jugador buscado no existe\n");
        return;
    }
    int puntos;
    printf("Ingrese la cantidad de puntos de habilidad que desea agregar:");
    scanf("%d", &puntos);
    datos->puntosHabilidad += puntos;
    stack_push(datos->funcionesAnteriores, datos);
    printf("Puntos de habilidad agregados con exito\n");
    
}

void MostrarJugadoresConItemsEspecifico(Map *jugadores, char *item)
{
    if(firstMap(jugadores) != NULL)
    {
        while(nextMap(jugadores) != NULL)
        {
            Datos *datos = firstMap(jugadores);
            if(searchMap(datos->items, item) != NULL)
            {
                printf("Jugadores con el item especifico: \n");
                printf("%s\n", datos->nombre);
            }
        }
        Datos *datos = firstMap(jugadores);
        if(searchMap(datos->items, item) != NULL)
        {
            printf("%s\n", datos->nombre);
        }
    }
    else
    {
        printf("No hay jugadores\n");
    }
}
void deshacerAccion(Map *jugadores, char *nombre){
    Datos *datos = searchMap(jugadores, nombre);
    if(datos == NULL)
    {
        printf("El jugador no existe\n");
        return;
    }
    stack_pop(datos->funcionesAnteriores);
    datos=stack_top(datos->funcionesAnteriores);
}
int main()
{
    Map *jugadores = createMap(is_equal_string);
    Datos *jugador;
    char nombre[20];
    int opcion = 1;
    while(opcion != 0)
    {
        printf("Menu de acciones:\n");
        printf("1. Crear perfil de jugador\n");
        printf("2. Mostrar perfil de jugador\n");
        printf("3. Agregar item a jugador\n");
        printf("4. Eliminar item de jugador\n");
        printf("5. Agregar puntos de habilidad a jugador\n");
        printf("6. Mostrar jugadores con item especifico\n");
        printf("7. Deshacer ultima accion\n");
        printf("8. Exportar datos de jugadores a archivo de texto\n");
        printf("9. Importar datos de jugadores desde archivo de texto\n");
        printf("0. Salir\n");
        printf("Ingrese la opcion deseada: ");
        scanf("%d", &opcion);
        switch (opcion)
        {
            case 1:
                jugador = crearPerfilJugador();
                insertMap(jugadores, jugador->nombre, jugador);
                break;
            case 2:
                printf("Ingrese el nombre del jugador: ");
                scanf("%s", nombre);
                mostrarPerfilJugador(jugadores, nombre);
                break;
            case 3:
                printf("Ingrese el nombre del jugador: ");
                scanf("%s", nombre);
                agregarItem(jugadores, nombre);
                break;
            case 4:
                break;
            case 5:
                printf("Ingrese el nombre del jugador: ");
                scanf("%s", nombre);
                SumarPuntosHabilidad(jugadores, nombre);
                break;
            case 6: 
                printf("Ingrese el nombre del item: ");
                scanf("%s", nombre);
                MostrarJugadoresConItemsEspecifico(jugadores, nombre);
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida\n");
                break;
        }

    }
    return 0;
}