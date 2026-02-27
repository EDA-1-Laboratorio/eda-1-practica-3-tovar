#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CARTAS 52
#define NUM_JUGADORES 2
#define CARTAS_POR_JUGADOR 2
#define CARTAS_COMUNITARIAS 5

// Definición de los palos y los valores de las cartas
#define TREBOLES 0
#define ESPADAS 1
#define CORAZONES 2
#define DIAMANTES 3

// Definición de los valores de las cartas
#define AS 1
#define DOS 2
#define TRES 3
#define CUATRO 4
#define CINCO 5
#define SEIS 6
#define SIETE 7
#define OCHO 8
#define NUEVE 9
#define DIEZ 10
#define J 11
#define Q 12
#define K 13

// Estructura de una carta
typedef struct {
    int valor; // Valor de la carta (1-13)
    int palo;  // Palo de la carta (0=Treboles, 1=Espadas, 2=Corazones, 3=Diamantes)
} Carta;

// Estructura de la baraja
typedef struct {
    Carta cartas[NUM_CARTAS];
    int indice; // Indica el siguiente lugar disponible en la baraja
} Baraja;

// Estructura de un jugador
typedef struct {
    Carta cartas_jugador[CARTAS_POR_JUGADOR]; // Cartas del jugador
    int fichas; // Fichas del jugador
} Jugador;

// Funciones para manejar la baraja
void inicializar_baraja(Baraja* baraja);
void barajar(Baraja* baraja);
Carta repartir_carta(Baraja* baraja);

// Funciones para las rondas del juego
void primera_ronda(Jugador jugadores[], Baraja* baraja);
void segunda_ronda(Jugador jugadores[], Baraja* baraja);
void tercera_ronda(Jugador jugadores[], Baraja* baraja);
void cuarta_ronda(Jugador jugadores[], Baraja* baraja);

// Función para determinar el ganador
int determinar_ganador(Jugador jugadores[], Carta cartas_comunitarias[]);

// Funciones de impresión
void imprimir_carta(Carta carta);
void imprimir_cartas_jugador(Jugador jugador);

int main() {
    srand(time(NULL));

    // Crear la baraja
    Baraja baraja;
    inicializar_baraja(&baraja);
    barajar(&baraja);

    // Inicializar jugadores
    Jugador jugadores[NUM_JUGADORES] = { { .fichas = 1000 }, { .fichas = 1000 } };

    // Iniciar el juego
    printf("¡Comienza el juego!\n");

    // Primera ronda
    primera_ronda(jugadores, &baraja);
    // Segunda ronda
    segunda_ronda(jugadores, &baraja);
    // Tercera ronda
    tercera_ronda(jugadores, &baraja);
    // Cuarta ronda
    cuarta_ronda(jugadores, &baraja);

    // Determinar el ganador
    Carta cartas_comunitarias[CARTAS_COMUNITARIAS];
    int ganador = determinar_ganador(jugadores, cartas_comunitarias);

    printf("El ganador es el jugador %d\n", ganador + 1);

    return 0;
}

// Funciones de la baraja
void inicializar_baraja(Baraja* baraja) {
    baraja->indice = 0;
    for (int i = 0; i < NUM_CARTAS; i++) {
        baraja->cartas[i].valor = (i % 13) + 1;       // Asigna valores de 1 a 13
        baraja->cartas[i].palo = i / 13;              // Asigna palo 0-3 (Treboles, Espadas, Corazones, Diamantes)
    }
}

void barajar(Baraja* baraja) {
    for (int i = 0; i < NUM_CARTAS; i++) {
        int j = rand() % NUM_CARTAS;
        Carta temp = baraja->cartas[i];
        baraja->cartas[i] = baraja->cartas[j];
        baraja->cartas[j] = temp;
    }
}

Carta repartir_carta(Baraja* baraja) {
    return baraja->cartas[baraja->indice++];
}

// Funciones para las rondas
void primera_ronda(Jugador jugadores[], Baraja* baraja) {
    printf("\nPrimera ronda:\n");
    for (int i = 0; i < NUM_JUGADORES; i++) {
        jugadores[i].cartas_jugador[0] = repartir_carta(baraja);
        jugadores[i].cartas_jugador[1] = repartir_carta(baraja);
        printf("Jugador %d recibe: ", i + 1);
        imprimir_cartas_jugador(jugadores[i]);
    }
}

void segunda_ronda(Jugador jugadores[], Baraja* baraja) {
    printf("\nSegunda ronda:\n");
    Carta river[3];
    for (int i = 0; i < 3; i++) {
        river[i] = repartir_carta(baraja);
    }

    printf("Cartas comunitarias (River): ");
    for (int i = 0; i < 3; i++) {
        imprimir_carta(river[i]);
    }

    // Aquí puedes preguntar a los jugadores si desean quedarse o retirarse
}

void tercera_ronda(Jugador jugadores[], Baraja* baraja) {
    printf("\nTercera ronda:\n");
    Carta carta_extra = repartir_carta(baraja);
    printf("Carta comunitaria adicional: ");
    imprimir_carta(carta_extra);

    // Aquí puedes preguntar a los jugadores si desean quedarse o retirarse
}

void cuarta_ronda(Jugador jugadores[], Baraja* baraja) {
    printf("\nCuarta ronda:\n");
    Carta carta_extra = repartir_carta(baraja);
    printf("Carta comunitaria final: ");
    imprimir_carta(carta_extra);

    // Aquí no hace falta preguntar a los jugadores, ya que el juego concluye
}

// Función para determinar el ganador (por simplicidad, esta parte debe expandirse)
int determinar_ganador(Jugador jugadores[], Carta cartas_comunitarias[]) {
    // Implementar la lógica de comparación de manos (para simplificar no se implementa aquí)
    return 0;  // Retornar el índice del ganador
}

// Funciones para imprimir las cartas
void imprimir_carta(Carta carta) {
    const char* nombres_valores[] = {"", "As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    const char* nombres_palos[] = {"Treboles", "Espadas", "Corazones", "Diamantes"};
    printf("%s de %s ", nombres_valores[carta.valor], nombres_palos[carta.palo]);
}

void imprimir_cartas_jugador(Jugador jugador) {
    for (int i = 0; i < CARTAS_POR_JUGADOR; i++) {
        imprimir_carta(jugador.cartas_jugador[i]);
    }
    printf("\n");
}
