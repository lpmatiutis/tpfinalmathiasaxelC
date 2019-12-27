/*
AUTORES
		-Mathias Alfredo Gonzalez Benitez		CI: 4475100
		-Axel Fleitas							CI: 5785570
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//#include <graphics.h>
/*
Estructura de carta, que es asignada a los jugadores
*/
typedef struct carta
{
	int valor, grupo, estado;
	char color, palo;
	char impresion[4];
} Carta;

/*
Estructura de jugador, para realizar las partidas
*/
typedef struct jugador
{
	int tipo, puntaje, normal, heroe, escudero, mosquetero;
	struct carta cartasJugador[6];

} Jugador;

void cargar_mazo(int F, Carta mazo[F]);
char palo(int p);
void repartirMazo(Jugador *jugador, int F, Carta mazo[F], int cantEntregar);
void iniciarlizarDatos(Jugador *jugador);
void asignarImpresion(Carta mazo);
void ordenarMano(Jugador *jh, int n);
void jugar(Jugador *jh, Jugador *jm, int turno, int n, int *salir);
void mosquetero(Jugador *jh, Jugador *jm, int n, int *salir);
void escudero(Jugador *jh, Jugador *jm, int n);
void heroe(Jugador *jh, Jugador *jm, int turno, int n);
void normal(Jugador *jh, Jugador *jm, int n);
void imprimirResultado(Jugador *jh, Jugador *jm, FILE *archivotxt, int turno);
void calcularResultado(Jugador *jh, Jugador *jm, FILE *archivotxt, int cantPartidas);
void ordenarMAquina(Jugador *jm, int n);

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
	int salir = 0;
	int repetir = 0, partidas = 1;
	FILE *archivotxt;
	archivotxt = fopen("logJuego.txt", "a");

	printf("### Partida nro: %d ###", partidas);
	int i;
	for (i = 0; i < 5; i++)
	{
		printf("\n--- Turno nro %d ---\n", i + 1);
		if (salir == 1)
		{
			calcularResultado(jh, jm, archivotxt, partidas);
			break;
		}

		if (i < 4)
		{
			repartirMazo(jh, 52, mazo, 6);
			repartirMazo(jm, 52, mazo, 6);
			ordenarMano(jh, 6);
			ordenarMAquina(jm, 6);

			jugar(jh, jm, i + 1, 6, &salir);
		}
		else
		{
			repartirMazo(jh, 52, mazo, 2);
			repartirMazo(jm, 52, mazo, 2);
			ordenarMano(jh, 2);
			ordenarMAquina(jm, 2);
			jugar(jh, jm, i + 1, 2, &salir);
		}
		imprimirResultado(jh, jm, archivotxt, i + 1);

		if (i == 4)
		{
			printf("\nDesea volver a jugar?	1-Si   2-No");
			scanf("%d", &repetir);
			if (repetir == 1)
			{
				cargar_mazo(52, mazo);
				i = -1;
				partidas++;
				printf("### Partida nro: %d ###", partidas);
			}
			else
			{
				salir = 1;
				calcularResultado(jh, jm, archivotxt, partidas);
			}
		}
	}

	printf("\nFinalizo partida\n");
	fclose(archivotxt);

	return 0;
}

//Metodo para calcular el resultado final de las partidas
void calcularResultado(Jugador *jh, Jugador *jm, FILE *archivotxt, int cantPartidas)
{
	//Se calcula segun los valores obtenidos en la partida
	int totalJH = 0, totalJM = 0;
	totalJH += jh->mosquetero * 8;
	totalJH += jh->escudero * 3;
	totalJH += jh->heroe * 2;
	totalJH += jh->normal * 1;

	totalJM += jm->mosquetero * 8;
	totalJM += jm->escudero * 3;
	totalJM += jm->heroe * 2;
	totalJM += jm->normal * 1;
	printf("\n--------------------\n");
	fprintf(archivotxt, "\n--------------------\n");
	printf("\nTOTAL HUMANO: %d \nTOTAL MAQUINA: %d\n", totalJH, totalJM);
	fprintf(archivotxt, "\nTOTAL HUMANO: %d \nTOTAL MAQUINA: %d\n", totalJH, totalJM);
	if (totalJH > totalJM)
	{
		printf("\n-------------------------------------------\n");
		fprintf(archivotxt, "\n-------------------------------------------\n");
		printf("\nGano Humano	- Cantidad de partidas: %d\n", cantPartidas);
		fprintf(archivotxt, "\nGano Humano	- Cantidad de partidas: %d\n", cantPartidas);
		printf("\n-------------------------------------------\n");
		fprintf(archivotxt, "\n-------------------------------------------\n");
	}
	else if (totalJM > totalJH)
	{
		printf("\n-------------------------------------------\n");
		fprintf(archivotxt, "\n-------------------------------------------\n");
		printf("\nGano Maquina	- Cantidad de partidas: %d\n", cantPartidas);
		fprintf(archivotxt, "\nGano Maquina	- Cantidad de partidas: %d\n", cantPartidas);
		printf("\n-------------------------------------------\n");
		fprintf(archivotxt, "\n-------------------------------------------\n");
	}
	else
	{
		printf("\n-------------------------------------------\n");
		fprintf(archivotxt, "\n-------------------------------------------\n");
		printf("\nEMPATE!	- Cantidad de partidas: %d\n", cantPartidas);
		fprintf(archivotxt, "\nEMPATE!	- Cantidad de partidas: %d\n", cantPartidas);
		printf("\n-------------------------------------------\n");
		fprintf(archivotxt, "\n-------------------------------------------\n");
	}
}

// Metodo para imprimir los resultados por turnos de los jugadores
void imprimirResultado(Jugador *jh, Jugador *jm, FILE *archivotxt, int turno)
{
	fprintf(archivotxt, "\n----- TURNO %d -----\n", turno);
	printf("\n Valor mosqueteros JH: %d", jh->mosquetero);
	fprintf(archivotxt, "\n Valor mosqueteros JH: %d", jh->mosquetero);
	printf("\n Valor mosqueteros JM: %d", jm->mosquetero);
	fprintf(archivotxt, "\n Valor mosqueteros JM: %d", jm->mosquetero);
	printf("\n Valor escudero JH: %d", jh->escudero);
	fprintf(archivotxt, "\n Valor escudero JH: %d", jh->escudero);
	printf("\n Valor escudero JM: %d", jm->escudero);
	fprintf(archivotxt, "\n Valor escudero JM: %d", jm->escudero);
	printf("\n Valor heroe JH: %d", jh->heroe);
	fprintf(archivotxt, "\n Valor heroe JH: %d", jh->heroe);
	printf("\n Valor heroe JM: %d", jm->heroe);
	fprintf(archivotxt, "\n Valor heroe JM: %d", jm->heroe);
	printf("\n Valor normal JH: %d", jh->normal);
	fprintf(archivotxt, "\n Valor normal JH: %d", jh->normal);
	printf("\n Valor normal JM: %d", jm->normal);
	fprintf(archivotxt, "\n Valor normal JM: %d", jm->normal);
}

// Metodo para generar un mazo a traves de la estructura carta
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
			//setear palo
			mazo[c].palo = palo(mazo[c].grupo);
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
}

// Metodo para asignar los palos a las cartas
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

// Metodo para repartir el mazo a los jugadores por turno
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
}

//Se inicializan los datos de los jugadores
void iniciarlizarDatos(Jugador *jugador)
{
	jugador->puntaje = 0;
	jugador->escudero = 0;
	jugador->heroe = 0;
	jugador->mosquetero = 0;
	jugador->normal = 0;
}

//Metodo para asignar impresion personalizable a las cartas
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

// Metodo para ordenar la mano del jugador segun el criterio del mismo
void ordenarMano(Jugador *jh, int n)
{
	int orden[n];
	int i;
	Carta aux[n];
	printf("\nCartas para ordenar: ");
	for (i = 0; i < n; i++)
	{
		printf("| %s |", jh->cartasJugador[i].impresion);
		aux[i] = jh->cartasJugador[i];
	}
	printf("\nIngrese orden de las cartas separadas por espacios: ");
	if (n == 6)
	{
		scanf("%d %d %d %d %d %d", &orden[0], &orden[1], &orden[2], &orden[3], &orden[4], &orden[5]);
	}
	else
	{
		scanf("%d %d", &orden[0], &orden[1]);
	}
	getchar();

	for (i = 0; i < n; i++)
	{
		jh->cartasJugador[i] = aux[orden[i] - 1];
	}
}

// Metodo en el cual se realiza la jugada luego de que el jugador halla ordenado su mazo
void jugar(Jugador *jh, Jugador *jm, int turno, int n, int *salir)
{
	int i;
	printf("*** Cartas Maquina *** \n");
	for (i = 0; i < n; i++)
	{
		printf("| %s |", jm->cartasJugador[i].impresion);
	}

	printf("\n*** Cartas Jugador *** \n");
	for (i = 0; i < n; i++)
	{
		printf("| %s |", jh->cartasJugador[i].impresion);
	}
	printf("\n");
	mosquetero(jh, jm, n, salir);
	if ((*salir) == 1)
	{
		//gana directo quien posee algun mosquetero
		return;
	}
	escudero(jh, jm, n);
	heroe(jh, jm, turno, n);
	normal(jh, jm, n);
}

// Metodo para puntuacion tipo mosquetero
void mosquetero(Jugador *jh, Jugador *jm, int n, int *salir)
{
	int i, j, cantH = 0, cantM = 0, posH, posM;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (jh->cartasJugador[i].valor == jh->cartasJugador[j].valor) // si el jugador H tiene cartas iguales las va contando
			{
				cantH++;
			}
		}
		if (cantH >= 4)
		{
			posH = i;
			break;
		}
		cantH = 0;
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (jm->cartasJugador[i].valor == jm->cartasJugador[j].valor) // si el jugador M tiene cartas iguales las va contando
			{
				cantM++;
			}
		}
		if (cantM >= 4)
		{
			posM = i;
			break;
		}
		cantM = 0;
	}
	if (cantH >= 4 || cantM >= 4) //si alguno de ambos tiene 4 cartas de dominancionens iguales
	{
		if (cantH == cantM) //si ambos tienen 4 cartas iguales(casi imposible)
		{
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
			(*salir) = 1;
		}
		else // sino gana el jugador M
		{
			jm->mosquetero = jm->mosquetero + 1;
			(*salir) = 1;
		}
	}
}

// Metodo para puntuacion tipo escudero
void escudero(Jugador *jh, Jugador *jm, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (jh->cartasJugador[i].valor == 1 && jm->cartasJugador[i].valor == 13 && (jh->cartasJugador[i].estado == 0 && jm->cartasJugador[i].estado == 0)) // si jH gana con escudero
		{
			jh->escudero = jh->escudero + 1;
			jh->cartasJugador[i].estado = 1;
			jm->cartasJugador[i].estado = 1;
		}
		else if (jm->cartasJugador[i].valor == 1 && jh->cartasJugador[i].valor == 13 && (jh->cartasJugador[i].estado == 0 && jm->cartasJugador[i].estado == 0)) // si JM gana con escudero
		{
			jm->escudero = jm->escudero + 1;
			jh->cartasJugador[i].estado = 1;
			jm->cartasJugador[i].estado = 1;
		}
	}
}

// Metodo para puntacion tipo heroe
void heroe(Jugador *jh, Jugador *jm, int turno, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (turno % 2 == 0)
		{
			if ((jh->cartasJugador[i].valor == jm->cartasJugador[i].valor) && (jh->cartasJugador[i].color == 'R') && (jm->cartasJugador[i].color == 'N') && (jh->cartasJugador[i].estado == 0 && jm->cartasJugador[i].estado == 0))
			{
				jh->heroe++;
				jh->cartasJugador[i].estado = 1;
				jm->cartasJugador[i].estado = 1;
			}
			else if ((jm->cartasJugador[i].valor == jh->cartasJugador[i].valor) && (jm->cartasJugador[i].color == 'R') && (jh->cartasJugador[i].color == 'N') && (jh->cartasJugador[i].estado == 0 && jm->cartasJugador[i].estado == 0))
			{
				jm->heroe++;
				jh->cartasJugador[i].estado = 1;
				jm->cartasJugador[i].estado = 1;
			}
			else if ((jm->cartasJugador[i].valor == jh->cartasJugador[i].valor))
			{
				printf("Se debe anular la partida \n");
			}
		}
		else
		{
			if ((jh->cartasJugador[i].valor == jm->cartasJugador[i].valor) && (jh->cartasJugador[i].color == 'N') && (jm->cartasJugador[i].color == 'R') && (jh->cartasJugador[i].estado == 0 && jm->cartasJugador[i].estado == 0))
			{
				jh->heroe++;
				jh->cartasJugador[i].estado = 1;
				jm->cartasJugador[i].estado = 1;
			}
			else if ((jm->cartasJugador[i].valor == jh->cartasJugador[i].valor) && (jm->cartasJugador[i].color == 'N') && (jh->cartasJugador[i].color == 'R') && (jh->cartasJugador[i].estado == 0 && jm->cartasJugador[i].estado == 0))
			{
				jm->heroe++;
				jh->cartasJugador[i].estado = 1;
				jm->cartasJugador[i].estado = 1;
			}
			else if ((jm->cartasJugador[i].valor == jh->cartasJugador[i].valor))
			{
				printf("Se debe anular la partida \n");
			}
		}
	}
}

// Metodo para puntuacion tipo normal
void normal(Jugador *jh, Jugador *jm, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (jh->cartasJugador[i].valor > jm->cartasJugador[i].valor && (jh->cartasJugador[i].estado == 0 && jm->cartasJugador[i].estado == 0))
		{
			jh->normal++;
			jh->cartasJugador[i].estado = 1;
			jm->cartasJugador[i].estado = 1;
		}
		else if (jm->cartasJugador[i].valor > jh->cartasJugador[i].valor && (jh->cartasJugador[i].estado == 0 && jm->cartasJugador[i].estado == 0))
		{
			jm->normal++;
			jh->cartasJugador[i].estado = 1;
			jm->cartasJugador[i].estado = 1;
		}
	}
}

void ordenarMAquina(Jugador *jm, int n)
{
	int i, j;
	Carta aux;
	for (i = 1; i < n; i++)
	{
		for (j = 0; j < n - 1; j++)
		{
			if (jm->cartasJugador[j].color > jm->cartasJugador[j + 1].color) //Ordenamos la carte por su color primeramente
			{
				aux = jm->cartasJugador[j + 1];
				jm->cartasJugador[j + 1] = jm->cartasJugador[j];
				jm->cartasJugador[j] = aux;
			}
		}
	}

	for (i = 1; i < n; i++)
	{
		for (j = 0; j < n - 1; j++)
		{
			// Una vez ordenadas por color procedemos a ordenarlas de menor a mayor por su valor
			if (jm->cartasJugador[j].color == jm->cartasJugador[j + 1].color && jm->cartasJugador[j].valor > jm->cartasJugador[j + 1].valor)
			{
				aux = jm->cartasJugador[j + 1];
				jm->cartasJugador[j + 1] = jm->cartasJugador[j];
				jm->cartasJugador[j] = aux;
			}
		}
	}

	// for (i = 0; i < n; i++)
	// {
	// 	printf("\nCarta valor: %d   palo: %c   color: %c    grupo: %d", jm->cartasJugador[i].valor, jm->cartasJugador[i].palo, jm->cartasJugador[i].color, jm->cartasJugador[i].grupo);
	// }
	// printf("\n");
}
