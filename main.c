#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
typedef struct carta
{
	int valor, grupo, estado;
	char color, palo;
	char impresion[4];
} Carta;

typedef struct jugador
{
	int tipo, puntaje;
	struct carta cartasJugador[6];

} Jugador;

void cargar_mazo(int F, Carta mazo[F]);
char palo(int p);
// void repartirMazo(Jugador jugador, int F, Carta mazo[F], int cantEntregar);
void repartirMazo(Jugador * jugador, int F, Carta mazo[F], int cantEntregar);

//void iniciarlizarDatos(Jugador jugador);
void iniciarlizarDatos(Jugador *jugador);
void asignarImpresion(Carta mazo);
// void ordenarMano(Jugador jh);
void ordenarMano(Jugador * jh);

int main(int argc, char *argv[])
{
	srand(time(NULL));
	Carta mazo[52];
	Jugador *i2=(Jugador *) malloc(sizeof(Jugador));
	Jugador *i3=(Jugador *) malloc(sizeof(Jugador));
	Jugador *jh = i2, *jm = i3;
	jh->tipo = 0;
	jm->tipo = 1;
	iniciarlizarDatos(jh);
	iniciarlizarDatos(jm);
	cargar_mazo(52, mazo);
	
	int i;
	for ( i = 0; i < 5; i++)
	{
		printf("Partida nro %d \n", i+1);
		if (i<4)
		{
			repartirMazo(jh, 52, mazo, 6);
			repartirMazo(jm, 52, mazo, 6);
			ordenarMano(jh);
			//ordenarCartas y tambien la maquina
			//comparar y asignar puntaje
		}else{
			repartirMazo(jh, 52, mazo, 2);
			repartirMazo(jm, 52, mazo, 2);
		}

		
	}

	printf("Finalizo partida wey");
	

	return 0;
}

void cargar_mazo(int F, Carta mazo[F])
{
	int i, j, c = 0;
	for (i = 1; i < 5; i++)
	{
		for (j = 1; j < 14; j++)
		{
			mazo[c].valor = j;  //valor
			mazo[c].grupo = i;  //grupo
			mazo[c].estado = 0; //estado
			if (i % 2 == 0)
			{						 //colores de carta
				mazo[c].color = 'R'; //rojo
			}
			else
			{
				mazo[c].color = 'N'; //negro
			}
			//
			//setear palo con switch
			mazo[c].palo = palo(mazo[c].grupo);
			//asignarImpresion(mazo[c]);

			//asginar impresion
			switch (mazo[c].valor)
			{
			case 1:
				sprintf(mazo[c].impresion, "%c%c", 'A', mazo[c].palo);
				break;
			case 11:
				sprintf(mazo[c].impresion, "%c%c", 'J', mazo[c].palo);
				break;
			case 12:
				sprintf(mazo[c].impresion, "%c%c", 'Q', mazo[c].palo);
				break;
			case 13:
				sprintf(mazo[c].impresion, "%c%c", 'K', mazo[c].palo);
				break;
			default:
				sprintf(mazo[c].impresion, "%d%c", mazo[c].valor, mazo[c].palo);
				break;
			}
			c++;
		}
	}

	for (i = 0; i < 52; i++)
		printf("Carta %d %s \n", i + 1, mazo[i].impresion);
	//printf("Carta %d: %d %d %c %c \n", i + 1, mazo[i].valor, mazo[i].grupo, mazo[i].color, mazo[i].palo);
}

char palo(int p)
{
	switch (p)
	{
	case 1:
		return 'E';
		break;
	case 2:
		return 'C';
		break;
	case 3:
		return 'T';
		break;
	case 4:
		return 'D';
		break;
	}
}

void repartirMazo(Jugador * jugador, int F, Carta mazo[F], int cantEntregar)
{
	int i;
	for (i = 0; i < cantEntregar; i++)
	{
		int aux = rand() % 52;
		while (mazo[aux].estado)
		{
			aux = rand() % 52;
		}
		jugador->cartasJugador[i] = mazo[aux];
		mazo[aux].estado = 1;
	}

	for (i = 0; i < cantEntregar; i++)
	{
		printf("Cartas de jugador tipo: %s %d %c %c \n", jugador->tipo ? "Maquina" : "Humano", jugador->cartasJugador[i].valor, jugador->cartasJugador[i].color, jugador->cartasJugador[i].palo);
	}
}

void iniciarlizarDatos(Jugador *jugador)
{
	jugador->puntaje = 0;
}

void asignarImpresion(Carta mazo)
{
	switch (mazo.valor)
	{
	case 1:
		sprintf(mazo.impresion, "%c%c", 'A', mazo.palo);
		break;
	case 11:
		sprintf(mazo.impresion, "%c%c", 'J', mazo.palo);
		break;
	case 12:
		sprintf(mazo.impresion, "%c%c", 'Q', mazo.palo);
		break;
	case 13:
		sprintf(mazo.impresion, "%c%c", 'K', mazo.palo);
		break;
	default:
		sprintf(mazo.impresion, "%d%c", mazo.valor, mazo.palo);
		break;
	}
}

void ordenarMano(Jugador * jh)
{
	int orden[6];
	int i;
	printf("Cartas para ordenar: ");
	for (i = 0; i < 6; i++)
	{
	printf("| %s |", jh->cartasJugador[i].impresion);

	}
	printf("\n");
	printf("Ingrese orden de las cartas separadas por espacios: ");
	scanf("%d %d %d %d %d %d", &orden[0], &orden[1], &orden[2], &orden[3], &orden[4], &orden[5]);
	getchar();
	for ( i = 0; i < 6; i++)
	{
		printf("Valores ingresados: %d \n", orden[i]);
	}
	
	
}
