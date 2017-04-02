#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream.h>
/*------------------------------------------------------
Declaracion de Estructuras
-------------------------------------------------------*/
	struct PBI
	{
		int ID;
		int IP;

	};

	struct CLICK
	{
		int X;
		int Y;
		int Activo; //0 = no, todo lo demás si
	}


/*------------------------------------------------------
Declaracion de Variables Globales
-------------------------------------------------------*/
	//Cada ventan es de 24*8
	CLICK CVentana1[192];
	CLICK CVentana2[192];
	CLICK CVentana3[192];
	CLICK CVentana4[192];
	CLICK CVentana5[192];
	CLICK CVentana6[192];

	PBI Ventanas[7];

	char instruccion[40]= "";
	char lexema[40]= "";
	int contInstruccion;
	int contLexema;
	int posX;
	int posY;


/*------------------------------------------------------
Declaracion de prototipos
------------------------------------------------------*/
	void interrupt tick(...); //New tick function
	void interrupt (*ptTick)(...); //Last tick function
	void Temporizador();
	void CoreKernel();
	void RenderKernel();
	void imprimirCaracterNVeces(char caracter, int cant);
	void Ventana();

	//Teclado
	void Gramatica();
	int TomaToken();
	void LimpiarLexema();
	void LeerTeclado();
	void LimpiarInstruccion();

	//Mouse
	int MostrarPuntero(void);
	int IsClick(void);
	int CordX(void);
	int CordY(void);
	void EscribirClick();

/*------------------------------------------------------
Sistema Operativo
------------------------------------------------------*/
int main()
{
	posX = 10;
	posY = 19;
	RenderKernel(); //Se ejecuta el proceso del Render Kernel, se pinta la pantalla
	CoreKernel(); //Se realiza la incialización de procesos
	delay(5);
	gotoxy(posX, posY);
	int bandera = 1;
	while(bandera)   //Nunca sale del programa
	{

	}
	return 0;
}

/*------------------------------------------------------
Render Kernel
------------------------------------------------------*/
void RenderKernel()
{
	clrscr();
	gotoxy(1,2);
	imprimirCaracterNVeces(205, 80);
	gotoxy(1, 10);
	imprimirCaracterNVeces(205, 80);
	gotoxy(1, 19);
	imprimirCaracterNVeces(205, 80);
	gotoxy(1, 22);
	imprimirCaracterNVeces(205, 80);
	gotoxy(1, 25);
	imprimirCaracterNVeces(205, 80);
	gotoxy(1, 2);
	for (int i = 0; i < 18; i++)
	{
		gotoxy(1, 1+i);
		imprimirCaracterNVeces(186, 2);
		gotoxy(27, 1 + i);
		imprimirCaracterNVeces(186, 2);
		gotoxy(53, 1 + i);
		imprimirCaracterNVeces(186, 2);
		gotoxy(79, 1 + i);
		imprimirCaracterNVeces(186, 2);
	}
	gotoxy(1,1);
	imprimirCaracterNVeces(201, 1);
	imprimirCaracterNVeces(203, 1);

	gotoxy(27,1);
	imprimirCaracterNVeces(203, 2);

	gotoxy(53,1);
	imprimirCaracterNVeces(203, 2);

	gotoxy(79,1);
	imprimirCaracterNVeces(203, 1);
	imprimirCaracterNVeces(187, 1);

	gotoxy(2,9);
	imprimirCaracterNVeces(204, 1);
	gotoxy(27,9);
	imprimirCaracterNVeces(206, 2);
	gotoxy(53,9);
	imprimirCaracterNVeces(206, 2);
	gotoxy(79,9);
	imprimirCaracterNVeces(206, 1);
	imprimirCaracterNVeces(185, 1);

	gotoxy(1,18);
	imprimirCaracterNVeces(200,1);
	gotoxy(2,18);
	imprimirCaracterNVeces(202,1);
	gotoxy(27,18);
	imprimirCaracterNVeces(202, 2);
	gotoxy(53,18);
	imprimirCaracterNVeces(202, 2);
	gotoxy(79,18);
	imprimirCaracterNVeces(202, 1);
	imprimirCaracterNVeces(188, 1);
}

void imprimirCaracterNVeces(char caracter, int cant)
{
	for (size_t i = 0; i < cant; i++)
	{
		printf(&caracter);
	}
}


/*------------------------------------------------------
Core Kernel
------------------------------------------------------*/
void CoreKernel()
{
	contInstruccion = 0;
	Temporizador(); //Ingresa el residente del temporizador en la interrupcion 1C

}

void Temporizador()
{
	ptTick = getvect(0x1C);
	setvect(0x1C, tick);
}

void interrupt tick(...)
{
	(*ptTick)(...); // Executing timer original interrupt
	EscribirClick();
	LeerTeclado();

	//Inicia la conmutacion de procesos.....
	//Verificar si el quantum del proceso se termino
	//En caso haya terminado el quantum
		//Sacar datos de la pila (registros, y de mas cosas importantes)
		//Almacenar esos datos en el PCB actual
		//Obtener datos globales i almacenar en el PCB actual (contador)
		//Obtener el PCB que le toca acceder al procesador
		//Tomar los datos del PCB que sean necesarios para ingresar en la pila
		//Ingresar los datos a la pila
		//Cambiar los datos globales en base al PCB nuevo
}

void LeerTeclado()
{
	if(kbhit()) 
	{
		int x = getch();
		if (x == 13) //Enter
		{
			Gramatica();
			delay(10);
			LimpiarInstruccion();
			contInstruccion = 0;
			posX = 10;
			posY = 19;
			delay(5);
			gotoxy(posX,posY);
			imprimirCaracterNVeces(32, 40);
			posX = 10;
			posY = 19;
			delay(5);
			gotoxy(posX,posY);
		}
		else
		{
			if (x == 8) //BackSpace
			{
				if (posX > 10)
				{
					contInstruccion--;
					instruccion[contInstruccion] = 0;
					posX--;
					gotoxy(posX, posY);
					printf(" ");
					gotoxy(posX, posY);
				}
			}
			else
			{
				if (contInstruccion < 40)
				{
					instruccion[contInstruccion] = x;
					printf(&instruccion[contInstruccion]);
					contInstruccion++;
					posX++;
				}
			}
		}
			//colocar limites de cuanto es lo maximo que puede escribir
			//configurar el backspace
			//hay que almacenar el dato en un string global
			//Llamar a la gramatica
			//Entre la gramatica se debe de incluir la posibilidad salir
			//Para salir cambiar la bandera
	}
}

void LimpiarInstruccion()
{
	for (int i = 0; i < 40; ++i)
	{
		instruccion[i] = 0;
	}
}

//Devuelve el token actual 1 para identificador 2 para número
int TomaToken(int& i )
{
	LimpiarLexema();
	contLexema =0;
	int num = 0;
	int anterior = 0;
	char actual;

	while (num != -1 && i < contInstruccion)
	{
		actual = instruccion[i];
		anterior = num;

		if (!(actual >= 0 && actual <= 31))
		{
			//si es una letra
			if ((actual >= 97 && actual <= 122) || (actual >= 65 && actual <= 90))
			{
				actual = tolower(actual);
				num = 1;
			}
			else
			{
				//si es un número
				if (actual >= 48 && actual <= 57)
				{
					num = 2;
				}
				else
				{
					if (actual == 45)
					{
						num = 3;
					}
					else 
					{
						if(actual != 32)
						{
							//error
							return -1;							
						}
						else
						{
							num = 4;
							i++;
						}
					}
				}
			}

			if ((anterior != num && anterior != 0) || actual == 32)
			{
				return anterior;
			}
			lexema[contLexema] = actual;
			contLexema++;
		}
		i++;
	}

	//verificar esto aún, se acabo string
	return num;
}

void Gramatica()
{
	posX = 10;
	posY = 22;
	gotoxy(posX,posY);
	imprimirCaracterNVeces(32, 60);
	gotoxy(posX,posY);

	int i = 0;
	int Token = TomaToken(i);
	char accion[40] = "";
	int numVentana;
	for(int x = 0; x < contLexema; x++)
	{
		accion[x] = lexema[x];
	}

	//Definir la gramatica segun los parametros que estan en el enunciado
	//Lo primero que debe venir es un identificador
	if (Token != 1)
	{
		printf("Error: Se necesita una instruccion valida");
	}

	Token = TomaToken(i);
	numVentana = lexema[0];

	//Verifico el numero de ventana
	if (Token != 2 || atoi(lexema) < 1 || atoi(lexema) > 6)
	{
		printf("Error: El numero de ventan ingresado no es valido");
	}
	else 
	{
		if (strcmp(accion,"stats") == 0)
		{
			//stats ##
			printf("Estadisticas: ");
			//leo opciones de estadísticas
			Token = TomaToken(i);
			if (Token == 2)
			{
				if (strcmp(lexema, "0") != 0)
				{
					printf("Error: La estadistica seleccionada no existe");
				}
				//CODIGO SI ESCOGIÓ STATS CON PARÁMETRO 0
			}
			else
			{
				if (Token == 3)
				{
					Token = TomaToken(i);
					if (Token != 2 && strcmp(lexema, "1") != 0)
					{
						printf("Error: La estadistica seleccionada no existe");
					}
					//CODIGO SI ESCOGIÓ STATS CON PARÁMETRO -1
				}
				else
				{
					printf("Error: La estadistica seleccionada no existe");
				}
			}
		}
		else
		{
			if (strcmp(accion,"quantum") == 0)
			{
				printf("Nuevo Quantum: ");
				//leo milisegundos
				Token = TomaToken(i);
				if (Token != 2)
				{
					printf("Error: Ingrese un quantum valido");
				}
				else
				{
					int milisegundos = atoi(lexema);
				}
			}
			else
			{
				//todos los demas que no sean estos dos que traen parámetros
				if (strcmp(accion,"add") == 0)
				{
					printf("Nueva ventana: ");
					//Codigo de add
				}
				else
				{
					if (strcmp(accion,"pause") == 0)
					{
						printf("Ventana pausada: ");
						imprimirCaracterNVeces(numVentana, 1);
						//Codigo de pause
					}
					else
					{
						if (strcmp(accion,"remove") == 0)
						{
							printf("Eliminar ventana: ");
							imprimirCaracterNVeces(numVentana, 1);
							//Codigo de remove
						}
						else
						{
							if (strcmp(accion,"clear") == 0)
							{
								printf("Vaciar vetana: ");
								imprimirCaracterNVeces(numVentana, 1);
								//Codigo de clear
							}
							else
							{
								printf("Error: Se necesita una instruccion valida");
							}
						}
					}
				}
			}
		}
	}
}

void LimpiarLexema()
{
	for (int i = 0; i < 40; ++i)
	{
		lexema[i] = 0;
	}
}

/*------------------------------------------------------
Interrupción del mouse
------------------------------------------------------*/
void EscribirClick()
{
	_setcursortype(_NORMALCURSOR);
	MostrarPuntero();
	if(IsClick() == 1)
	{
		gotoxy(CordX()+1,CordY()+1);
		printf(".");
		gotoxy(posX, posY);
	}

	_setcursortype(_NORMALCURSOR);
}

int MostrarPuntero(void)
{
	asm mov ax, 01h
	asm int 33h
	return 1;
}

int IsClick()
{
	asm mov ax, 03h
	asm int 33h
	return _BX;
}

int CordX(void)
{
	asm mov ax, 03h
	asm int 33h
	return (_CX/8)+1;
}

int CordY(void)
{
	asm mov ax, 03h
	asm int 33h
	return (_DX/8)+1;
}

/*------------------------------------------------------
Ventanas
Codigo que se ejecuta por cada ventan para mostrar el
blink de todos los puntos
------------------------------------------------------*/
void Ventana()
{
	while(1)
	{
		//Basicamente es un while infinito con un for interno
		//REGRESAR EL CURSOR A DONDE ESTABA ANTES DE COLOCAR EL PUNTO
	}
}

