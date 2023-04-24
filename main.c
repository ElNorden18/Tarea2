#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "stack.h"
#include "list.h"

typedef struct 
{
    int puntosHabilidad;
    List *items;
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

void crearPerfilJugador(Map *jugadores)
{
    char nombre[20];
    printf("Ingrese el nombre del jugador: ");
    scanf("%s", nombre);
    if (searchMap(jugadores, nombre) == NULL)
    {
        Datos *datos = (Datos *)malloc(sizeof(Datos));
        datos->puntosHabilidad = 0;
        datos->items = createList();
        datos->funcionesAnteriores = stack_create();
        insertMap(jugadores, nombre, datos);
        printf("Perfil de jugador creado con exito\n");
    }
    else
    {
        printf("El jugador ya existe\n");
    }
}

void mostrarPerfilJugador(Map *jugadores)
{
    char nombre[20];
    printf("Ingrese el nombre del jugador: ");
    scanf("%s", nombre);
    if (searchMap(jugadores, nombre) != NULL)
    {
        Datos *datos = (Datos *)searchMap(jugadores, nombre);
        printf("Nombre: %s\n", nombre);
        printf("Puntos de habilidad: %d\n", datos->puntosHabilidad);
        printf("Items: ");
        printf("%s",datos->items);
        printf("\n");
    }
    else
    {
        printf("El jugador no existe\n");
    }
}


int main()
{
    Map *jugadores = createMap(is_equal_string);
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
                crearPerfilJugador(jugadores);
                break;
            case 2:
                mostrarPerfilJugador(jugadores);
                break;
            case 3:
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