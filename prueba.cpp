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
int array[28];

int main()
{
    asm{
        mov ax, 1234
        push ax
    }

    Temporizador();

    while(1)
    {
        delay(1);
    }
    return 1;
}

void Temporizador()
{
	ptTick = getvect(0x1C);
	setvect(0x1C, tick);
}

void interrupt tick(...)
{
    for(int i = 0; i < 28; i++)
    {
        int x;
        asm {
            pop x;
        }
        array[i] = x;
        printf("%d ", x);

        delay(250);
    }

    for(int i = 27; i >= 0; i--)
    {
        push array[i];
    }

    printf(" Se acabo ");
}