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
        List *lista = datos->items;
        printf("Nombre: %s\n", nombre);
        printf("Puntos de habilidad: %d\n", datos->puntosHabilidad);
        printf("Items: ");
        struct Node *aux = lista->head;
        while(aux != NULL)
        {
            printf("%s ", (char *)aux->data);
            aux = aux->next;
        }
        printf("\n");
    }
    else
    {
        printf("El jugador no existe\n");
    }
}

void agregarItemJugador(Map *jugadores)
{
    char nombre[20];
    char item[20];
    printf("Ingrese el nombre del jugador: ");
    scanf("%s", nombre);
    if (searchMap(jugadores, nombre) != NULL)
    {
        printf("Ingrese el nombre del item: ");
        scanf("%s", item);
        Datos *datos = searchMap(jugadores, nombre);
        pushBack(datos->items, item);
        datos->cantItems++;
        printf("Item agregado con exito\n");
    }
    else
    {
        printf("El jugador no existe\n");
    }
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
                while (nextList(datos->items) != NULL)
                {
                    if (strcmp((char *)firstList(datos->items), item) == 0)
                    {
                        pop(datos->items);
                        printf("Item eliminado con exito\n");
                        return;
                    }
                }
                if (strcmp((char *)firstList(datos->items), item) == 0)
                {
                    pop(datos->items);
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