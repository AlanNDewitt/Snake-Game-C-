#ifndef LIBGAME_H
#define LIBGAME_H

#include <windows.h>
#include <stdio.h>
#include <conio.h>

// NUMEROS ASOCIADOS A LAS FLECHAS DEL TECLADO
#define ARRIBA     72
#define IZQUIERDA  75
#define DERECHA    77
#define ABAJO      80
#define ESC        27
#define ENTER      13

// colores
#define AZUL     0x009
#define AMARILLO 0x00E
#define ROJO     0x00C
#define VERDE    0x002
#define VERDE2   0x00B
#define MORADO   0x005
#define PLATA    0x00F

void gotoxy(int x, int y)  // funcion que posiciona el cursos en la coordenada (x,y)
{
    HANDLE hCon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon,dwPos);
}

void OcultaCursor() {
    CONSOLE_CURSOR_INFO cci = {100, FALSE}; // El segundo miembro de la estructura indica si se muestra el cursor o no.

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void Color(int color){
	static HANDLE hConsole;
    hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( hConsole, color | (0 * 0x10 + 0x100) );
}

void marco_Total()       // funcion que pinta los limites del escenario
{
     // Lineas horizontals
     for(int i=0; i < 120; i++){
        gotoxy(i, 0); printf ("%c", 205);
        gotoxy(i, 29); printf ("%c", 205);
     }
     //Lineas verticales
     for(int v=0; v < 30; v++){
        gotoxy(0,v);  printf ("%c", 186);
        gotoxy(119,v);  printf ("%c", 186);
     }
     // Esquinas
     /*
     gotoxy (0,0);     printf ("%c", 201);
     gotoxy(0,30);     printf ("%c", 200);
     gotoxy (120,0);    printf ("%c", 187);
     gotoxy(120,30);    printf ("%c", 188);
     */
}


void marco_Secundario()
{
	 for(int i=5; i < 116; i++){
        gotoxy(i, 3); printf ("%c", 205);
        gotoxy(i, 27); printf ("%c", 205);
     }
     //Lineas verticales
     for(int v=3; v < 28; v++){
        gotoxy(5,v);  printf ("%c", 186);
        gotoxy(115,v);  printf ("%c", 186);
     }
}

void pausa(int x){
    Sleep(x);

}


void pausa(){
    getch();
}


#endif

