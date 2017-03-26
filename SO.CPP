#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream.h>
#include <mmu.h>

#pragma region Estructuras
/*------------------------------------------------------
Declaracion de Estructuras
-------------------------------------------------------*/

//codigo obtenido de  http://samwho.co.uk/blog/2013/06/01/context-switching-on-x86
struct PBI
{
	int ID;
	int IP;
	enum int State; //agregar estados
	struct PBI *parent; //Creo que no es necesario ya que todos los procesos son independientes
						// y no vamos a usar threads
	struct context *context;     // swtch() here to run process
	enum int IsKilled; //agregar 0-no, 1-si
	double quantum;
	struct trapframe *tf;        // Trap frame for current syscall
	/*
	*	Agregar colas de mouse ??
	*/
};

struct trapframe {
	// registers as pushed by pusha
	int edi;
	int esi;
	int ebp;
	int oesp;      // useless & ignored
	int ebx;
	int edx;
	int ecx;
	int eax;

	// rest of trap frame
	short gs;
	short padding1;
	short fs;
	short padding2;
	short es;
	short padding3;
	short ds;
	short padding4;
	int trapno;

	// below here defined by x86 hardware
	int err;
	int eip;
	short cs;
	short padding5;
	int eflags;
	
	// below here only when crossing rings, such as from user to kernel
	int esp;
	short ss;
	short padding6;
};

struct context {
	uint edi;
	uint esi;
	uint ebx;
	uint ebp;
	uint eip;
};
#pragma endregion

#pragma region Variables Globales
/*------------------------------------------------------
Declaracion de Variables Globales
-------------------------------------------------------*/
char instruccion[40];
char lexema[20];
int contInstruccion;
int contLexema;
#pragma endregion

#pragma region Prototipos
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
void Gramatica();
int TomaToken();
void LimpiarLexema();

#pragma endregion

#pragma region Sistema Operativo
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

	}
	return 0;
}

#pragma region Render Kernel
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
#pragma endregion

#pragma region Core Kernel
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

	//Obtener datos del teclado
	if(kbhit())
	{
		char caracter = getch();
		printf(&caracter);
		char enter = '\r';

		if (!(&caracter == &enter))
		{
			instruccion[contInstruccion] = caracter;
			contInstruccion++;

		}
		else
		{
			Gramatica();
		}

			//colocar limites de cuanto es lo maximo que puede escribir
			//configurar el backspace
			//hay que almacenar el dato en un string global
			//Llamar a la gramatica
			//Entre la gramatica se debe de incluir la posibilidad salir
			//Para salir cambiar la bandera
	}

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
#pragma endregion

#pragma region Gramatica
//Devuelve el token actual 1 para identificador 2 para número
int TomaToken(int& i )
{
	LimpiarLexema();
	contLexema =0;
	lexema;
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
					if (actual == '-')
					{
						return 3;
					}
					else
					{
						//error
						return -1;
					}
				}
			}

			if (anterior != num && anterior != 0)
			{
				i--;
				return num;
			}
			lexema[contLexema] = actual;
			contLexema++;
		}
		i++;
	}

	//verificar esto aún, se acabo string
	return -1;
}

void Gramatica()
{
	int i = 0;
	int Token = TomaToken(i);
	char accion[20];
	for(int x = i; x < contLexema; x++)
	{
		accion[x] = lexema[x];
	}
	printf(accion);
	//Definir la gramatica segun los parametros que estan en el enunciado
	//Lo primero que debe venir es un identificador
	if (Token != 1)
	{
		//error
	}

	Token = TomaToken(i);

	//Verifico el número de ventana
	if (Token != 2 || atoi(lexema) < 1 || atoi(lexema) > 6)
	{
		//error
	}

	if (accion == "stats")
	{
		//leo opciones de estadísticas
		Token = TomaToken(i);
		if (Token == 2)
		{
			if (lexema != "0")
			{
				//error
			}
			//CODIGO SI ESCOGIÓ STATS CON PARÁMETRO 0
		}
		else
		{
			if (Token == 3)
			{
				Token = TomaToken(i);
				if (Token != 2 && lexema != "1")
				{
					//error
				}
				//CODIGO SI ESCOGIÓ STATS CON PARÁMETRO -1
			}
			else
			{
				//error
			}
		}
	}
	else
	{
		if (accion == "quantum")
		{
			//leo milisegundos
			Token = TomaToken(i);
			if (Token != 3)
			{
				//error
			}

			double milisegundos = atof(lexema);
		}
		else
		{
			//todos los demas que no sean estos dos que traen parámetros
			if (accion == "add")
			{

			}
			else
			{
				if (accion == "pause")
				{

				}
				else
				{
					if (accion == "remove")
					{

					}
					else
					{
						if (accion == "clear")
						{

						}
						else
						{
							//error
						}
					}
				}
			}
		}
	}

}

void LimpiarLexema()
{
}
#pragma endregion

#pragma endregion

#pragma region Ventana
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
#pragma endregion

#pragma region Cambio de Contexto Experimental
void syscall()
{
	int num;

	// Get the syscall number from eax
	num = proc->tf->eax;

	// Check that the syscall number is greater than 0, inside the range of total
	// syscalls and that a function pointer exists for that syscall number.
	if (num > 0 && num < NELEM(syscalls) && syscalls[num]) 
	{
		// Set eax to the return value of the syscall.
		proc->tf->eax = syscalls[num]();
	}
	else 
	{
		// Else print an error and return -1 to the user program.
		cprintf("%d %s: unknown sys call %d\n",
			proc->pid, proc->name, num);
		proc->tf->eax = -1;
	}
}

void TrapFrameSetUp()
{
	__asm
	{
	.globl alltraps
		alltraps :
		# Build trap frame.
		pushl %ds
		pushl %es
		pushl %fs
		pushl %gs
		pushal

		# Set up data and per - cpu segments.
		movw $(SEG_KDATA << 3), %ax
		movw %ax, %ds
		movw %ax, %es
		movw $(SEG_KCPU << 3), %ax
		movw %ax, %fs
		movw %ax, %gs

		# Call trap(tf), where tf = %esp
		pushl %esp
		call trap # < -ENTRY INTO C TRAP FUNCTION
		addl $4, %esp

		# Return falls through to trapret...
		.globl trapret
		trapret :
		popal
		popl %gs
		popl %fs
		popl %es
		popl %ds
		addl $0x8, %esp  # trapno and errcode
		iret
	}
}

#pragma endregion

