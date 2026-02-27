#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Si M_PI no está definido en tu compilador, lo definimos manualmente
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 1. Definición del tipo de dato struct para el Círculo
typedef struct {
    double x;     // Coordenada x del centro
    double y;     // Coordenada y del centro
    double radio; // Radio del círculo (debe ser positivo)
} Circulo;

// Función auxiliar para calcular la distancia entre dos puntos (centros)
double calcular_distancia(Circulo c1, Circulo c2) {
    return sqrt(pow(c2.x - c1.x, 2) + pow(c2.y - c1.y, 2));
}

// Función que calcula y devuelve el área de intersección de dos círculos
double calcular_area_interseccion(Circulo c1, Circulo c2) {
    double d = calcular_distancia(c1, c2);

    // Caso 1: Los círculos están muy separados o apenas se tocan en un punto
    if (d >= c1.radio + c2.radio) {
        return 0.0;
    }

    // Caso 2: Un círculo está completamente dentro del otro
    if (d <= fabs(c1.radio - c2.radio)) {
        // El área de intersección es simplemente el área del círculo más pequeño
        double r_menor = (c1.radio < c2.radio) ? c1.radio : c2.radio;
        return M_PI * r_menor * r_menor;
    }

    // Caso 3: Intersección parcial (cálculo trigonométrico)
    double r1_sq = c1.radio * c1.radio;
    double r2_sq = c2.radio * c2.radio;
    double d_sq = d * d;

    // Distancias desde los centros hasta el eje radical (la línea donde se cruzan)
    double d1 = (r1_sq - r2_sq + d_sq) / (2 * d);
    double d2 = d - d1;

    // Calculamos los ángulos de los sectores circulares
    double theta1 = acos(d1 / c1.radio);
    double theta2 = acos(d2 / c2.radio);

    // Calculamos el área de cada segmento circular
    double area1 = r1_sq * theta1 - d1 * sqrt(r1_sq - d1 * d1);
    double area2 = r2_sq * theta2 - d2 * sqrt(r2_sq - d2 * d2);

    // El área total es la suma de ambos segmentos
    return area1 + area2;
}

int main() {
    Circulo c1, c2;

    printf("--- Interseccion de Circunferencias ---\n\n");

    // Captura de datos para el Círculo 1
    printf("Circulo 1\n");
    printf("Ingrese la posicion del centro (x y): ");
    scanf("%lf %lf", &c1.x, &c1.y);
    do {
        printf("Ingrese el radio (positivo): ");
        scanf("%lf", &c1.radio);
    } while (c1.radio <= 0);

    // Captura de datos para el Círculo 2
    printf("\nCirculo 2\n");
    printf("Ingrese la posicion del centro (x y): ");
    scanf("%lf %lf", &c2.x, &c2.y);
    do {
        printf("Ingrese el radio (positivo): ");
        scanf("%lf", &c2.radio);
    } while (c2.radio <= 0);

    // Procesamiento
    double area = calcular_area_interseccion(c1, c2);

    // Salida de resultados
    printf("\n--- Resultados ---\n");
    if (area > 0.0) {
        printf("Los circulos SI tienen puntos de interseccion.\n");
        printf("El area de interseccion es: %.4lf\n", area);
    } else {
        // Revisamos si se tocan exactamente en un solo punto (tangentes externos)
        double distancia = calcular_distancia(c1, c2);
        if (fabs(distancia - (c1.radio + c2.radio)) < 0.0001) {
            printf("Los circulos se tocan exactamente en UN punto (tangentes).\n");
            printf("El area de interseccion es: 0.0000\n");
        } else {
            printf("Los circulos NO se intersectan.\n");
        }
    }

    return 0;
}
