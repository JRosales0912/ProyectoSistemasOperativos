#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>

//Declaración de prototipos
void interrupt tick(...); //New tick function
void interrupt (*ptTick)(...); //Last tick function
void Temporizador();
void CoreKernel();
void RenderKernel();
void imprimirCaracterNVeces(char caracter, int cant);
void Ventana();
void Gramatica();

//Declaracion de prototipos de mouse
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
	RenderKernel(); //Se ejecuta el proceso del Render Kernel, se pinta la pantalla
	CoreKernel(); //Se realiza la incialización de procesos
	gotoxy(0,19);
	int bandera = 1;
	while(bandera)   //Nunca sale del programa
	{
		char caracter = getch();
		printf(&caracter);
		//colocar limites de cuanto es lo maximo que puede escribir
		//configurar el backspace
		//hay que almacenar el dato en un string global
		//Llamar a la gramatica
		//Entre la gramatica se debe de incluir la posibilidad salir
		//Para salir cambiar la bandera
	}
	return 0;
}

void Gramatica()
{
	//Definir la gramatica segun los parametros que estan en el enunciado
}
/*------------------------------------------------------
Render Kernel
------------------------------------------------------*/
void RenderKernel()
{
	clrscr();
	gotoxy(1,2);
	imprimirCaracterNveces(205, 80);
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

	//Escribir clicks
	EscribirClick();
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

/*---------------------------------------------------------------
interrucion del mouse
---------------------------------------------------------------*/
void EscribirClick()
	{
		_setcursortype(_NORMALCURSOR);
		MostrarPuntero();
		do
			{
				if(IsClick() == 1)
					{
						gotoxy(CordX()+1,CordY()+1);
						printf(".");
					}
			}
		while (!kbhit());
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