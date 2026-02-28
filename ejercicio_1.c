#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CARTAS 52
#define CARTAS_JUGADOR 2
#define CARTAS_COMUNITARIAS 5

/* Jerarquía */
#define CARTA_ALTA 1
#define PAR 2
#define DOBLE_PAR 3
#define TERCIA 4
#define ESCALERA 5
#define COLOR 6
#define FULL 7
#define POKER 8
#define ESCALERA_COLOR 9

typedef struct {
    int valor;   // 1-13
    int palo;    // 0-3
} Carta;

typedef struct {
    Carta cartas[NUM_CARTAS];
    int indice;
} Baraja;

typedef struct {
    Carta mano[CARTAS_JUGADOR];
    int activo;
} Jugador;

/* PROTOTIPOS */
void inicializar_baraja(Baraja *b);
void barajar(Baraja *b);
Carta repartir(Baraja *b);
void imprimir_carta(Carta c);
void imprimir_mano(Carta mano[], int n);
int preguntar_continuar(int jugador);
int evaluar_mano(Carta total[]);
int determinar_ganador(Jugador j1, Jugador j2, Carta comunitarias[]);

int main() {

    srand(time(NULL));

    Baraja baraja;
    inicializar_baraja(&baraja);
    barajar(&baraja);

    Jugador j1, j2;
    j1.activo = 1;
    j2.activo = 1;

    Carta comunitarias[CARTAS_COMUNITARIAS];

    printf("===== TEXAS HOLD'EM =====\n\n");

    /* --- PRIMERA RONDA --- */
    printf("PRIMERA RONDA (Reparto inicial)\n");

    for(int i=0;i<2;i++){
        j1.mano[i] = repartir(&baraja);
        j2.mano[i] = repartir(&baraja);
    }

    printf("Jugador 1: ");
    imprimir_mano(j1.mano,2);

    printf("Jugador 2: ");
    imprimir_mano(j2.mano,2);

    j1.activo = preguntar_continuar(1);
    j2.activo = preguntar_continuar(2);

    if(!j1.activo){ printf("Jugador 2 gana.\n"); return 0; }
    if(!j2.activo){ printf("Jugador 1 gana.\n"); return 0; }

    /* --- SEGUNDA RONDA (FLOP) --- */
    printf("\nSEGUNDA RONDA (Flop)\n");

    for(int i=0;i<3;i++)
        comunitarias[i] = repartir(&baraja);

    imprimir_mano(comunitarias,3);

    j1.activo = preguntar_continuar(1);
    j2.activo = preguntar_continuar(2);

    if(!j1.activo){ printf("Jugador 2 gana.\n"); return 0; }
    if(!j2.activo){ printf("Jugador 1 gana.\n"); return 0; }

    /* --- TERCERA RONDA (Turn) --- */
    printf("\nTERCERA RONDA (Turn)\n");

    comunitarias[3] = repartir(&baraja);
    imprimir_mano(comunitarias,4);

    j1.activo = preguntar_continuar(1);
    j2.activo = preguntar_continuar(2);

    if(!j1.activo){ printf("Jugador 2 gana.\n"); return 0; }
    if(!j2.activo){ printf("Jugador 1 gana.\n"); return 0; }

    /* --- CUARTA RONDA (River) --- */
    printf("\nCUARTA RONDA (River)\n");

    comunitarias[4] = repartir(&baraja);
    imprimir_mano(comunitarias,5);

    /* Determinar ganador */
    int ganador = determinar_ganador(j1,j2,comunitarias);

    if(ganador==1)
        printf("\nGANADOR: Jugador 1\n");
    else if(ganador==2)
        printf("\nGANADOR: Jugador 2\n");
    else
        printf("\nEMPATE\n");

    return 0;
}

/* ================= FUNCIONES ================= */

void inicializar_baraja(Baraja *b){
    b->indice = 0;
    for(int i=0;i<NUM_CARTAS;i++){
        b->cartas[i].valor = (i%13)+1;
        b->cartas[i].palo = i/13;
    }
}

void barajar(Baraja *b){
    for(int i=0;i<NUM_CARTAS;i++){
        int j = rand()%NUM_CARTAS;
        Carta temp = b->cartas[i];
        b->cartas[i] = b->cartas[j];
        b->cartas[j] = temp;
    }
}

Carta repartir(Baraja *b){
    return b->cartas[b->indice++];
}

void imprimir_carta(Carta c){
    char *valores[]={"","A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    char *palos[]={"T","E","C","D"};
    printf("%s%s ",valores[c.valor],palos[c.palo]);
}

void imprimir_mano(Carta mano[], int n){
    for(int i=0;i<n;i++)
        imprimir_carta(mano[i]);
    printf("\n");
}

int preguntar_continuar(int jugador){
    char opcion;
    printf("Jugador %d, ¿Desea continuar? (s/n): ",jugador);
    scanf(" %c",&opcion);

    if(opcion=='n' || opcion=='N')
        return 0;
    return 1;
}

int evaluar_mano(Carta total[]){
    int valor[14]={0};
    int palo[4]={0};

    for(int i=0;i<7;i++){
        valor[total[i].valor]++;
        palo[total[i].palo]++;
    }

    int pares=0,tercia=0,poker=0,color=0,escalera=0;

    for(int i=1;i<=13;i++){
        if(valor[i]==4) poker=1;
        if(valor[i]==3) tercia++;
        if(valor[i]==2) pares++;
    }

    for(int i=0;i<4;i++)
        if(palo[i]>=5) color=1;

    for(int i=1;i<=9;i++)
        if(valor[i]&&valor[i+1]&&valor[i+2]&&valor[i+3]&&valor[i+4])
            escalera=1;

    if(escalera && color) return ESCALERA_COLOR;
    if(poker) return POKER;
    if(tercia && pares) return FULL;
    if(color) return COLOR;
    if(escalera) return ESCALERA;
    if(tercia) return TERCIA;
    if(pares>=2) return DOBLE_PAR;
    if(pares==1) return PAR;

    return CARTA_ALTA;
}

int determinar_ganador(Jugador j1, Jugador j2, Carta comunitarias[]){
    Carta total1[7], total2[7];

    for(int i=0;i<2;i++){
        total1[i]=j1.mano[i];
        total2[i]=j2.mano[i];
    }

    for(int i=0;i<5;i++){
        total1[i+2]=comunitarias[i];
        total2[i+2]=comunitarias[i];
    }

    int m1=evaluar_mano(total1);
    int m2=evaluar_mano(total2);

    if(m1>m2) return 1;
    if(m2>m1) return 2;
    return 0;
}
