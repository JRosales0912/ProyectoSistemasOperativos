#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream.h>

void interrupt tick(...); //New tick function
void interrupt (*ptTick)(...); //Last tick function
void Temporizador();
int array[30];
void prueba();
void prueba_();
int ad;

int main()
{
       ad = (int) &prueba;
    asm{
	mov ax, 1234
	push ax
	mov ax, ad
	push ax
    }

    Temporizador();
    prueba();

    return 1;
}

void prueba()
{
	    while(1)
	    {
		delay(5);
		printf("x");
	    }
}

void Temporizador()
{
	ptTick = getvect(0x1C);
	setvect(0x1C, tick);
}

void interrupt tick(...)
{
    for(int i = 0; i < 30; i++)
    {
	int x;
	asm {
	    pop x;
	}
	array[i] = x;
	printf("%d ", x);

	delay(250);
    }

    for(int j = 29; j >= 0; j--)
    {
	int y = array[j];
	asm push y;
    }

    printf(" Se acabo ");
}