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
	struct PCB
	{
		int ID;
		int Estado;  //{ Corriendo = 1, Listo = 2, Pausa = 3, Removido = 4};
		int IsKilled; //agregar 0-no, 1-si
		int quantum;
		int inicioX;
		int inicioY;
		int i;
		int j;
		int tiempoUso; //Si se mata el proceso, este tiempo se reinicia
		int posVentana;

		//Contexto en el CPU
		int banderas;
		int IP;
		int CS;
		int ax;
		int bx;
		int cx;
		int dx;
	};

/*------------------------------------------------------
Declaracion de Variables Globales
-------------------------------------------------------*/
	//Cada ventan es de 80x18
	int QuantumFaltante;
	int CliksVentanas[1440] = {0};
	int inicioX;
	int inicioY;
	int iVentana;
	int jVentana;
	int PCBActual = 0;
	int posVentana;
	int pintar = 1;
	PCB Ventanas[7];

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
	void Idle();

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
	//CoreKernel(); //Se realiza la incialización de procesos
	delay(5);
	gotoxy(posX, posY);
	int bandera = 1;
	QuantumFaltante = 91;
	int x;
	asm mov x, ax;
	printf("%d ", x);
	asm mov x, bx;
	printf("%d ", x);
	asm mov x, cx;
	printf("%d ", x);
	asm mov x, dx;
	printf("%d ", x);
	asm mov x, cs;
	printf("%d ", x);	

	asm push 1234;
	
	Idle();
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
	for	(int i = 1; i < 7; i++)
	{
		Ventanas[i].ID = i;
		Ventanas[i].Estado = 4;
		Ventanas[i].IsKilled = 1;
		Ventanas[i].quantum = 500;

		if(i<4)
		{
			Ventanas[i].inicioX = 2 + (i-1)*26;
			Ventanas[i].inicioY = 1;
		}
		else
		{
			Ventanas[i].inicioX = 2 + (i-4)*26;
			Ventanas[i].inicioY = 11;
		}	

		Ventanas[i].i = Ventanas[i].inicioX;
		Ventanas[i].j = Ventanas[i].inicioY;

		Ventanas[i].tiempoUso  = 0;
		Ventanas[i].banderas = 0;
		
		Ventanas[i].IP = (int)&Ventana;
		int cs_;
		asm{
			mov ax, cs 
			mov cs_, ax
		}

		Ventanas[i].CS = cs_;
		Ventanas[i].ax = 0;
		Ventanas[i].bx = 0;
		Ventanas[i].cx = 0;
		Ventanas[i].dx = 0;
	}

	Ventanas[0].ID = 0;
	Ventanas[0].Estado = 1;
	Ventanas[0].IsKilled = 0;
	Ventanas[0].quantum = 500;

	Ventanas[0].tiempoUso  = 0;
	Ventanas[0].banderas = 0;
	Ventanas[0].IP = (int)&Idle;
	int cs_;
	asm{
		mov ax, cs 
		mov cs_, ax
	}

	Ventanas[0].CS = cs_;
	Ventanas[0].ax = 0;
	Ventanas[0].bx = 0;
	Ventanas[0].cx = 0;
	Ventanas[0].dx = 0;

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

	Ventanas[PCBActual].tiempoUso++;
	QuantumFaltante--;
	if(QuantumFaltante = 0)
	{
		//Inicia la comnutación
	}
		//Sacar datos de la pila (registros, y de mas cosas importantes)
		//Almacenar esos datos en el PCB actual
		//Obtener datos globales i almacenar en el PCB actual (contador)
		//Obtener el PCB que le toca acceder al procesador
		//Tomar los datos del PCB que sean necesarios para ingresar en la pila
		//Ingresar los datos a la pila
		//Cambiar los datos globales en base al PCB nuevo
}

//Captura los datos ingresan al teclado
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
	}
}

void LimpiarInstruccion()
{
	for (int i = 0; i < 40; ++i)
	{
		instruccion[i] = 0;
	}
}

void LimpiarLexema()
{
	for (int i = 0; i < 40; ++i)
	{
		lexema[i] = 0;
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
	else
	{
		Token = TomaToken(i);
		numVentana = lexema[0];

		//Verifico el numero de ventana
		if (Token != 2 || atoi(lexema) < 1 || atoi(lexema) > 6)
		{
			printf("Error: El numero de ventana ingresado no es valido");
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
}

/*------------------------------------------------------
Interrupción del mouse
------------------------------------------------------*/
//Captura los clicks del usuario
void EscribirClick()
{
	_setcursortype(_NORMALCURSOR);
	MostrarPuntero();
	if(IsClick() == 1)
	{
		int x = CordX();
		int y = CordY();
		//Ingresar el Click a la ventana
		int pos = y*80 + x;
		if(pos < 1440)
		{
			CliksVentanas[pos] = 1;
		}
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
		delay(5);
		for(iVentana = inicioX; iVentana < inicioX + 24; iVentana++)
		{
			for(jVentana = inicioY; jVentana < inicioY + 8; jVentana++)
			{
				posVentana = jVentana*80 + iVentana;
				if(!CliksVentanas[posVentana])
				{
					gotoxy(iVentana, jVentana);
					if(pintar)
					{
						printf(".");
					}
					else
					{
						printf(" ");
					}
					
					gotoxy(posX, posY);
				}
			}
		}
		//Basicamente es un while infinito con un for interno
		//REGRESAR EL CURSOR A DONDE ESTABA ANTES DE COLOCAR EL PUNTO
	}
}

void Idle()
{
	int x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13;
	asm{
		pop x1
		pop x2
		pop x3
		pop x4 
		pop x5
		pop x6
		pop x7
		pop x8
		pop x9
		pop x10
		pop x11
		pop x12
		pop x13
	}
	printf("call ");
	printf("%d ", x1);
	printf("%d ", x2);
	printf("%d ", x3);
	printf("%d ", x4);
	printf("%d ", x5);
	printf("%d ", x6);
	printf("%d ", x7);
	printf("%d ", x8);
	printf("%d ", x9);
	printf("%d ", x10);
	printf("%d ", x11);
	printf("%d ", x12);
	printf("%d ", x13);

	while(1)
	{
		delay(5);
	}
}             

