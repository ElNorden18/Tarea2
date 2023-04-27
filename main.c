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
}
/*
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
                while (nextList(datos->items) != NULL)
                {
                    if (strcmp((char *)firstList(datos->items), item) == 0)
                    {
                        popCurrent(datos->items);
                        printf("Item eliminado con exito\n");
                        return;
                    }
                }
                if (strcmp((char *)firstList(datos->items), item) == 0)
                {
                    popCurrent(datos->items);
                    printf("Item eliminado con exito\n");
                    return;
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
} */

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
                break;
            case 6: 
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