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
	struct ToDo
	{
		int comando; // { Add = 1, Pause = 2, Remove = 3, Clear = 4, Quantum = 5, Stats = 6};
		//Coordenadas para blinkear si comando = 7
		int parametro;// Si comando = 5 guardo milisegundo si comando = 6 guardo tipo de estadísticas
		//algo aalgo
	};

	
	struct PCB
	{
		int ID;
		int Estado;  //{ Corriendo = 1, Listo = 2, Pausa = 3, Removido = 4};
		int quantum;
		int i;
		int j;
		int inicioX;
		int inicioY;
		int tiempoUso; //Si se mata el proceso, este tiempo se reinicia
		int posVentana;
		
		//Lista de comandos a ejecutar
		ToDo List[30];
		int finLista;
		int inicioLista;
	};

/*------------------------------------------------------
Declaracion de Variables Globales
-------------------------------------------------------*/
	//Cada ventan es de 80x18
	int TiempoTotal;
	int QuantumFaltante;
	int CliksVentanas[1600] = {0};
	int inicioX;
	int inicioY;
	int iVentana;
	int jVentana;
	int PCBActual = 0;
	int posVentana;
	int pintar = 1;
	PCB Ventanas[7];

	//Para Instrucciones
	int numVentana = 0;
	int i = 0;
	int Token = 0;

	int PCBSalida = 0;
	int valorConmutar = 0;
	int banderaAccion = 0;
	int z;

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
	void Acciones(ToDo com);
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
	CoreKernel(); //Se realiza la incialización de procesos
	delay(5);
	gotoxy(posX, posY);

	QuantumFaltante = 50;
	Ventana();
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
	TiempoTotal = 0;
	contInstruccion = 0;
	for	(int i = 1; i < 7; i++)
	{
		Ventanas[i].ID = i;
		Ventanas[i].Estado = 4;
		Ventanas[i].quantum = 20;  
 
		if(i<4)
		{
			Ventanas[i].inicioX = 3 + (i-1)*26;
			Ventanas[i].inicioY = 2;
		}
		else
		{
			Ventanas[i].inicioX = 3 + (i-4)*26;
			Ventanas[i].inicioY = 10;
		}

		Ventanas[i].i = Ventanas[i].inicioX;
		Ventanas[i].j = Ventanas[i].inicioY;

		Ventanas[i].tiempoUso  = 0;

		Ventanas[i].finLista = 0;
		Ventanas[i].inicioLista = 0;
		//Coment
	}

	Ventanas[0].ID = 0;
	Ventanas[0].Estado = 1;
	Ventanas[0].quantum = 20;

	Ventanas[0].tiempoUso  = 0;

	Temporizador(); //Ingresa el residente del temporizador en la interrupcion 1C
}

void Temporizador()
{
	ptTick = getvect(0x1C);
	setvect(0x1C, tick);
}

void interrupt tick(...)
{
	TiempoTotal = TiempoTotal + 1;
	(*ptTick)(...); // Executing timer original interrupt
	EscribirClick();
	LeerTeclado();

	//Reviso para no iterrumpir una acción
	if(banderaAccion == 0)
	{
		Ventanas[PCBActual].tiempoUso = Ventanas[PCBActual].tiempoUso - 1;
		QuantumFaltante = QuantumFaltante - 1;
		delay(5);
		if(QuantumFaltante == 0)
		{
			//Inicia la comnutación
			//Obtener el PCB que le toca acceder al procesador
			PCBSalida = PCBActual;

			while(Ventanas[PCBActual].Estado != 2)
			{
				delay(5);
				if(PCBActual == 6)
				{
					if(PCBSalida == 0)
					{
						PCBActual = 0;
					}
					else
					{
						PCBActual = 1;
					}
				}
				else
				{
					PCBActual++;
				}

				if(PCBSalida == PCBActual)
				{
					goto salir;
				}
			}
			salir:

			QuantumFaltante = Ventanas[PCBActual].quantum;
			
			if(Ventanas[PCBSalida].Estado == 1)
			{
				Ventanas[PCBSalida].Estado = 2;
			}
			Ventanas[PCBActual].Estado = 1;

			Ventanas[PCBSalida].i = iVentana;
			Ventanas[PCBSalida].j = jVentana;
			inicioX = Ventanas[PCBActual].inicioX;
			inicioY = Ventanas[PCBActual].inicioY;
			iVentana = Ventanas[PCBActual].i;
			jVentana = Ventanas[PCBActual].j;
			
			int _posX = 10;
			int _posY = 22;
			gotoxy(_posX, _posY);
			imprimirCaracterNVeces(32, 60);
			gotoxy(_posX, _posY);
			printf("conmutación: entra: %d", PCBActual);
			printf(" x: %d", iVentana);
			printf(" y: %d", jVentana);
			gotoxy(posX,posY);
		}
	}
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
	for (int i = 0; i < 40; i++)
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
	i = 0;
	numVentana = 0;
	Token = TomaToken(i);
	char accion[40] = "";

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
		numVentana = atoi(lexema);

		//Verifico el numero de ventana
		if ((Token != 2 || numVentana < 1 || numVentana > 6) && (accion != "stats"))
		{
			printf("Error: El numero de ventana ingresado no es valido");
		}
		else 
		{
			if(strcmp(accion,"stats") == 0)
			{
				//stats ##				
				if (Token == 2)
				{
					if (numVentana == 0)
					{
						//CODIGO SI ESCOGIÓ STATS CON PARÁMETRO 0
						printf("Idle " , "%d" ,Ventanas[0].tiempoUso/TiempoTotal , '%');
					}
					else
					{
						if ( numVentana < 1 || numVentana > 6)
						{
							printf("ErrorStats: La ventana seleccionada no existe ");
						}
						else
						{
							printf("Stats Ventana:  " , "%d" ,Ventanas[numVentana].tiempoUso/TiempoTotal , '%');
						}
					}
					
				}
				else
				{
					if (Token == 3)
					{
						Token = TomaToken(i);
						if (Token != 2 && strcmp(lexema, "1") != 0)
						{
							printf("ErrorStats: La opción de estadistica seleccionada no existe");
						}
						else
						{
							int porcentaje = 0;
							//CODIGO SI ESCOGIÓ STATS CON PARÁMETRO -1;
							for(int i = 1; i < 7; i++)
							{
								if(Ventanas[i].Estado != 4)
								{
									porcentaje = Ventanas[i].tiempoUso/TiempoTotal;
								}
								printf("%d", i , "%d", porcentaje , "%,");
							}
						}	
					}
					else
					{
						printf("Error: valor para estadistica no valido");
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
						if(Ventanas[numVentana].finLista < 30)
						{
							Ventanas[numVentana].List[Ventanas[numVentana].finLista].comando = 5;
							Ventanas[numVentana].List[Ventanas[numVentana].finLista].parametro = atoi(lexema);
							Ventanas[numVentana].finLista++;
						}
						else
						{
							printf("Error: Ventana saturada");
						}
					}
				}
				else
				{
					//todos los demas que no sean estos dos que traen parámetros
					if (strcmp(accion,"add") == 0)
					{
						printf("Nueva ventana: ");
						if(Ventanas[numVentana].Estado == 4)
						{
							Ventanas[numVentana].Estado = 2;
							Ventanas[numVentana].quantum = 50;

							Ventanas[numVentana].i  = Ventanas[numVentana].inicioX;
							Ventanas[numVentana].j = Ventanas[numVentana].inicioY;

							Ventanas[numVentana].tiempoUso  = 0;
							
							Ventanas[numVentana].finLista = 0;
							
						}
						else
						{
							if(Ventanas[numVentana].Estado == 3)
							{
								Ventanas[numVentana].Estado = 2;
							}
							else
							{
								printf("Error: la ventana ya se encuentra activa");
								printf("%d",numVentana);
							}
						}
					}
					else
					{
						if (strcmp(accion,"pause") == 0)
						{
							if(Ventanas[numVentana].finLista < 30)
							{
								Ventanas[numVentana].List[Ventanas[numVentana].finLista].comando = 2;
								Ventanas[numVentana].finLista++;
							}
							else
							{
								printf("Error: Ventana saturada");
							}
							
						}
						else
						{
							if (strcmp(accion,"remove") == 0)
							{
								if(Ventanas[numVentana].finLista < 30)
								{
									Ventanas[numVentana].List[Ventanas[numVentana].finLista].comando = 3;
									Ventanas[numVentana].finLista++;
								}
								else
								{
									printf("Error: Ventana saturada");
								}
							}
							else
							{
								if (strcmp(accion,"clear") == 0)
								{
									if(Ventanas[numVentana].finLista < 30)
									{
										Ventanas[numVentana].List[Ventanas[numVentana].finLista].comando = 4;
										Ventanas[numVentana].finLista++;
									}
									else
									{
										printf("Error: Ventana saturada");
									}
								}
								else
								{
									if(strcmp(accion,"ver") == 0)
									{
										printf("Ventana ");
										printf("%d", numVentana);
										printf("Estado ");
										printf("%d", Ventanas[numVentana].Estado );
									}
									else
									{
										printf("Error: Se necesita una instruccion valida   ");
										printf(accion);
									}
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
			gotoxy(posX,posY);
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
		delay(20);
		if(PCBActual == 0)
		{
			delay(5);
		}
		else
		{
			for(iVentana = inicioX; iVentana < inicioX + 24; iVentana++)
			{
				for(jVentana = inicioY; jVentana < inicioY + 7; jVentana++)
				{
					banderaAccion = 1;
					posVentana = jVentana*80 + iVentana;
					if(CliksVentanas[posVentana] == 1)
					{					
						gotoxy(iVentana, jVentana);	
						if(pintar == 1)
						{
							printf(".");
						}
						else
						{
							printf(" ");
						}
						gotoxy(posX, posY);
					}
					banderaAccion = 0;
				}
			}

			banderaAccion = 1;

			if(pintar == 1)
			{
				pintar = 0;
			}
			else
			{
				pintar = 1;
			}

			if(Ventanas[PCBActual].inicioLista != Ventanas[PCBActual].finLista)
			{
				Acciones(Ventanas[PCBActual].List[Ventanas[PCBActual].inicioLista]);
				Ventanas[PCBActual].inicioLista++;
			}
			else
			{
				Ventanas[PCBActual].inicioLista = 0;
				Ventanas[PCBActual].finLista = 0;
			}

			banderaAccion = 0;
			
			//Basicamente es un while infinito con un for interno
		}
	}
}

void Acciones(ToDo com)
{
	switch(com.comando)
	{
		case 2:
		{
			//pausa
			Ventanas[PCBActual].Estado = 3;

			printf("Ventana: ");
			printf("%d", PCBActual);
			printf("Pausada");
			printf("%d", Ventanas[PCBActual].Estado);
		}break;
		case 3:
		{
			//remove
			Ventanas[PCBActual].Estado = 4;

			printf("Ventana: ");
			printf("%d", PCBActual);
			printf("Removida");
			
		}break;
		case 4:
		{
			//clear
			for(iVentana = inicioX; iVentana < inicioX + 24; iVentana++)
			{
				for(jVentana = inicioY; jVentana < inicioY + 8; jVentana++)
				{
					posVentana = jVentana*80 + iVentana;
					CliksVentanas[posVentana] = 0;
				}
			}

			printf("Ventana: ");
			printf("%d", PCBActual);
			printf("Limpia");

		}break;
		case 5:
		{
			//quantum
			Ventanas[PCBActual].quantum = com.parametro*0.182;
			
			printf("Quantum de Ventana: ");
			printf("%d", PCBActual);
			printf("%d", Ventanas[PCBActual].quantum );
		}break;
	}
}