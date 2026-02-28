#include <stdio.h>
#include <string.h>

struct Pizza {
    int radio;
    char masa[20];
    char sabor[30];
    char orilla[10];
    float precio;
};

float calcularPrecio(struct Pizza p) {
    float precioBase = 0;

    // Precio según tamaño
    if (p.radio == 10) precioBase = 80;
    else if (p.radio == 15) precioBase = 120;
    else if (p.radio == 18) precioBase = 150;

    // Extra masa
    if (strcmp(p.masa, "Crunch") == 0) precioBase += 15;
    if (strcmp(p.masa, "Sarten") == 0) precioBase += 20;

    // Extra orilla
    if (strcmp(p.orilla, "Si") == 0) precioBase += 25;

    return precioBase;
}

void llenarPizza(struct Pizza *p) {
    int opcion;

    printf("\nSeleccione el tamaño:\n");
    printf("1) 10 cm\n2) 15 cm\n3) 18 cm\n");
    scanf("%d", &opcion);

    if (opcion == 1) p->radio = 10;
    else if (opcion == 2) p->radio = 15;
    else p->radio = 18;

    printf("\nTipo de masa:\n");
    printf("1) Tradicional\n2) Crunch\n3) Sarten\n");
    scanf("%d", &opcion);

    if (opcion == 1) strcpy(p->masa, "Tradicional");
    else if (opcion == 2) strcpy(p->masa, "Crunch");
    else strcpy(p->masa, "Sarten");

    printf("\nSabor:\n");
    printf("1) Queso\n2) Pepperoni\n3) Mexicana\n4) Hawaiana\n5) BBQ\n6) CarnesFrias\n");
    scanf("%d", &opcion);

    switch(opcion) {
        case 1: strcpy(p->sabor, "Queso"); break;
        case 2: strcpy(p->sabor, "Pepperoni"); break;
        case 3: strcpy(p->sabor, "Mexicana"); break;
        case 4: strcpy(p->sabor, "Hawaiana"); break;
        case 5: strcpy(p->sabor, "BBQ"); break;
        case 6: strcpy(p->sabor, "CarnesFrias"); break;
        default: strcpy(p->sabor, "Queso");
    }

    printf("\n¿Orilla de queso?\n1) Si\n2) No\n");
    scanf("%d", &opcion);

    if (opcion == 1) strcpy(p->orilla, "Si");
    else strcpy(p->orilla, "No");

    p->precio = calcularPrecio(*p);
}

int main() {
    printf("Bienvenido a la Pizzeria de Copilco\n");
    printf("Promocion activa: 2x1 en pizzas del mismo tamano\n\n");

    printf("1) Aceptar promocion\n");
    printf("2) No aceptar\n");

    int opcion;
    scanf("%d", &opcion);

    struct Pizza p1, p2;
    float total = 0;

    if (opcion == 1) {

        printf("\n--- Pizza 1 ---\n");
        llenarPizza(&p1);

        printf("\n--- Pizza 2 ---\n");
        llenarPizza(&p2);

        if (p1.radio == p2.radio)
            total = p1.precio;  // 2x1
        else
            total = p1.precio + p2.precio;

        printf("\nAqui esta su ticket\n");
        printf("Promocion 2x1 aplicada\n");

        printf("\nPizza 1:\n");
        printf("Tamano: %d cm\n", p1.radio);
        printf("Masa: %s\n", p1.masa);
        printf("Sabor: %s\n", p1.sabor);
        printf("Orilla: %s\n", p1.orilla);
        printf("Precio: $%.2f\n", p1.precio);

        printf("\nPizza 2:\n");
        printf("Tamano: %d cm\n", p2.radio);
        printf("Masa: %s\n", p2.masa);
        printf("Sabor: %s\n", p2.sabor);
        printf("Orilla: %s\n", p2.orilla);
        printf("Precio: $%.2f\n", p2.precio);
    }
    else {

        printf("\n--- Pizza ---\n");
        llenarPizza(&p1);
        total = p1.precio;

        printf("\nAqui esta su ticket\n");

        printf("\nPizza:\n");
        printf("Tamano: %d cm\n", p1.radio);
        printf("Masa: %s\n", p1.masa);
        printf("Sabor: %s\n", p1.sabor);
        printf("Orilla: %s\n", p1.orilla);
        printf("Precio: $%.2f\n", p1.precio);
    }

    printf("\nTotal a pagar: $%.2f\n", total);

    return 0;
}
