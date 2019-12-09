/*
AUTORES
		-Mathias Alfredo Gonzalez Benitez		CI: 4475100
		-Axel Fleitas							CI: 5785570
*/
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
	int tipo, puntaje, normal, heroe, escudero, mosquetero;
	struct carta cartasJugador[6];

} Jugador;

void cargar_mazo(int F, Carta mazo[F]);
char palo(int p);
// void repartirMazo(Jugador jugador, int F, Carta mazo[F], int cantEntregar);
void repartirMazo(Jugador *jugador, int F, Carta mazo[F], int cantEntregar);

//void iniciarlizarDatos(Jugador jugador);
void iniciarlizarDatos(Jugador *jugador);
void asignarImpresion(Carta mazo);
// void ordenarMano(Jugador jh);
void ordenarMano(Jugador *jh);
void jugar(Jugador *jh, Jugador *jm, int turno);
void mosquetero(Jugador *jh, Jugador *jm);
void escudero(Jugador *jh, Jugador *jm);
void heroe(Jugador *jh, Jugador *jm, int turno);
void normal(Jugador *jh, Jugador *jm);

int main(int argc, char *argv[])
{
	srand(time(NULL));
	Carta mazo[52];
	Jugador *i2 = (Jugador *)malloc(sizeof(Jugador));
	Jugador *i3 = (Jugador *)malloc(sizeof(Jugador));
	Jugador *jh = i2, *jm = i3;
	jh->tipo = 0;
	jm->tipo = 1;
	iniciarlizarDatos(jh);
	iniciarlizarDatos(jm);
	cargar_mazo(52, mazo);

	int i;
	for (i = 0; i < 5; i++)
	{
		printf("\nPartida nro %d \n", i + 1);
		if (i < 4)
		{
			repartirMazo(jh, 52, mazo, 6);
			repartirMazo(jm, 52, mazo, 6);
			ordenarMano(jh);
			// Pruebas mosquetero
			//jugador humano
			jh->cartasJugador[0].valor = 1;
			jh->cartasJugador[1].valor = 1;
			// prueba de heroe
			jh->cartasJugador[2].color = 'N';
			jh->cartasJugador[2].valor = 2;
			jh->cartasJugador[3].valor = 13;
			jh->cartasJugador[5].valor = 1;
			jh->cartasJugador[4].valor = 1;
			// jugador maquina
			jm->cartasJugador[0].valor = 13;
			jm->cartasJugador[1].valor = 13;
			// prueba de heroe
			jm->cartasJugador[2].color = 'R';
			jm->cartasJugador[2].valor = 2;
			jm->cartasJugador[3].valor = 1;
			jm->cartasJugador[5].valor = 13;
			jm->cartasJugador[4].valor = 13;
			printf("Valores seteados \n");
			int j;
			for (j = 0; j < 6; j++)
			{
				printf("| %d |", jh->cartasJugador[j].valor);
				//aux[i] = jh->cartasJugador[i];
			}
			jugar(jh, jm, i + 1);
			printf("\n Valor mosqueteros JH: %d", jh->mosquetero);
			printf("\n Valor mosqueteros JM: %d", jm->mosquetero);
			printf("\n Valor escudero JH: %d", jh->escudero);
			printf("\n Valor escudero JM: %d", jm->escudero);
			printf("\n Valor heroe JH: %d", jh->heroe);
			printf("\n Valor heroe JM: %d", jm->heroe);
			printf("\n Valor normal JH: %d", jh->normal);
			printf("\n Valor normal JM: %d", jm->normal);
			//ordenarCartas y tambien la maquina
			//comparar y asignar puntaje
		}
		else
		{
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

void repartirMazo(Jugador *jugador, int F, Carta mazo[F], int cantEntregar)
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
	jugador->escudero = 0;
	jugador->heroe = 0;
	jugador->mosquetero = 0;
	jugador->normal = 0;
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

void ordenarMano(Jugador *jh)
{
	int orden[6];
	int i;
	Carta aux[6];
	printf("Cartas para ordenar: ");
	for (i = 0; i < 6; i++)
	{
		printf("| %s |", jh->cartasJugador[i].impresion);
		aux[i] = jh->cartasJugador[i];
	}
	printf("\n");
	printf("Ingrese orden de las cartas separadas por espacios: ");
	scanf("%d %d %d %d %d %d", &orden[0], &orden[1], &orden[2], &orden[3], &orden[4], &orden[5]);
	getchar();
	for (i = 0; i < 6; i++)
	{
		printf("Valores ingresados: %d \n", orden[i]);
		jh->cartasJugador[i] = aux[orden[i] - 1];
	}
	// for (i = 0; i < 6; i++)
	// {
	// printf("| %s |", jh->cartasJugador[i].impresion);
	// }
}

void jugar(Jugador *jh, Jugador *jm, int turno)
{
	int i;
	//printf("");
	printf("Cartas Maquina \n");
	for (i = 0; i < 6; i++)
	{
		printf("| %s |", jm->cartasJugador[i].impresion);
	}

	printf("\nCartas Jugador \n");
	for (i = 0; i < 6; i++)
	{
		printf("| %s |", jh->cartasJugador[i].impresion);
	}
	printf("\n");
	mosquetero(jh, jm);
	escudero(jh, jm);
	heroe(jh, jm, turno);
	normal(jh, jm);
}

void mosquetero(Jugador *jh, Jugador *jm)
{
	int i, j, cantH = 0, cantM = 0, posH, posM;
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 6; j++)
		{
			if (jh->cartasJugador[i].valor == jh->cartasJugador[j].valor) // si el jugador H tiene cartas iguales las va contando
			{
				cantH++;
			}
		}
		if (cantH >= 4)
		{
			printf("\nse encontro iguales en posicion Jugador: %d", i);
			posH = i;
			break;
		}
		cantH = 0;
	}

	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 6; j++)
		{
			if (jm->cartasJugador[i].valor == jm->cartasJugador[j].valor) // si el jugador M tiene cartas iguales las va contando
			{
				cantM++;
			}
		}
		if (cantM >= 4)
		{
			printf("\nse encontro iguales en posicion Maquina: %d", i);
			posM = i;
			break;
		}
		cantM = 0;
	}
	printf("Cantidad Humano: %d  Cantidad Maquina: %d", cantH, cantM);
	if (cantH >= 4 || cantM >= 4) //si alguno de ambos tiene 4 cartas de dominancionens iguales
	{
		printf("\ningreso if nivel 1");
		if (cantH == cantM) //si ambos tienen 4 cartas iguales(casi imposible)
		{
			printf("\ningreso if nivel 2");
			printf("\n Valor j1: %d  Valor j2: %d", jh->cartasJugador[posH].valor, jm->cartasJugador[posM].valor);
			if (jh->cartasJugador[posH].valor == jm->cartasJugador[posM].valor) // si son de la misma denominacion entonces se anulan
			{
				printf("Son iguales mosqueteros \n");
			}
			else if (jh->cartasJugador[posH].valor == 1) // si el jugador H tienen 4 As gana
			{											 //asignar puntaje a jugador por valor
				jh->mosquetero = jh->mosquetero + 1;
			}
			else if (jm->cartasJugador[posH].valor == 1) // si el jugador M tiene 4 As gana
			{
				jm->mosquetero = jm->mosquetero + 1;
			}
			else if (jh->cartasJugador[posH].valor > jm->cartasJugador[posH].valor) //si el jugador H tiene denominacionn mayor gana
			{
				jh->mosquetero = jh->mosquetero + 1;
			}
			else //sino gana jugador M
			{
				jm->mosquetero = jm->mosquetero + 1;
			}
		} // si jugador H es el unico que tiene 4 cartas entonces gana directamente
		else if (cantH > cantM)
		{
			jh->mosquetero = jh->mosquetero + 1;
		}
		else // sino gana el jugador M
		{
			jm->mosquetero = jm->mosquetero + 1;
		}
	}
	else //Sino ningun jugador tiene mosqueteros
	{
		printf("No mosqueteros");
	}
}

void escudero(Jugador *jh, Jugador *jm)
{
	int i, j, cantH = 0, cantM = 0, posH, posM;
	for (i = 0; i < 6; i++)
	{
		if (jh->cartasJugador[i].valor == 1 && jm->cartasJugador[i].valor == 13) // si jH gana con escudero
		{
			jh->escudero = jh->escudero + 1;
		}
		else if (jm->cartasJugador[i].valor == 1 && jh->cartasJugador[i].valor == 13) // si JM gana con escudero
		{
			jm->escudero = jm->escudero + 1;
		}
	}
}

void heroe(Jugador *jh, Jugador *jm, int turno)
{
	int i;
	for (i = 0; i < 6; i++)
	{
		if (turno % 2 == 0)
		{
			if ((jh->cartasJugador[i].valor == jm->cartasJugador[i].valor) && (jh->cartasJugador[i].color == 'R') && (jm->cartasJugador[i].color == 'N'))
			{
				jh->heroe++;
			}
			else if ((jm->cartasJugador[i].valor == jh->cartasJugador[i].valor) && (jm->cartasJugador[i].color == 'R') && (jh->cartasJugador[i].color == 'N'))
			{
				jm->heroe++;
			}
			else if ((jm->cartasJugador[i].valor == jh->cartasJugador[i].valor))
			{
				printf("Se debe anular la partida \n");
			}
		}
		else
		{
			if ((jh->cartasJugador[i].valor == jm->cartasJugador[i].valor) && (jh->cartasJugador[i].color == 'N') && (jm->cartasJugador[i].color == 'R'))
			{
				jh->heroe++;
			}
			else if ((jm->cartasJugador[i].valor == jh->cartasJugador[i].valor) && (jm->cartasJugador[i].color == 'N') && (jh->cartasJugador[i].color == 'R'))
			{
				jm->heroe++;
			}
			else if ((jm->cartasJugador[i].valor == jh->cartasJugador[i].valor))
			{
				printf("Se debe anular la partida \n");
			}
		}
	}
}

void normal(Jugador *jh, Jugador *jm)
{
	int i;
	for (i = 0; i < 6; i++)
	{
		if (jh->cartasJugador[i].valor > jm->cartasJugador[i].valor)
		{
			jh->normal++;
		}
		else if (jm->cartasJugador[i].valor > jh->cartasJugador[i].valor)
		{
			jm->normal++;
		}
	}
}

// void ordenarMAquina(){
// 	for (size_t i = 0; i < count; i++)
// 	{
// 		for (size_t i = 0; i < count; i++)
// 		{
// 			/* code */
// 		}

// 	}

// }
