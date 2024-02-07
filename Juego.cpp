#include<iostream>
#include "libgame.h"
#include<windows.h>
#include<string.h>
#include<conio.h>
#include<time.h>

//#include<dos.h>
using namespace std;


int Num_Jugador = 0;




class Jugador_Snake 
{
  private:
		
	string Nombre ;
	float Puntuacion ;
	float tiempo ;
	
	float Promedio_PT; //Promedio puntos sobre tiempo
	
  
  public:
  	
  	bool ya_impreso_en_tabla;
  	
	void Asigna_Nombre()
  	{
  		gotoxy(15,15);
  		Color(AMARILLO);
  		cout<<"Ingresa tu Nombre : ";
  		Color(VERDE2);
  		cin>>Nombre;
	}
	
	
	string Obtener_Nombre()
	{
		return Nombre;
	}
	
	
	void Asigna_Puntuacion(short comida_serpientee)
	{
		Puntuacion = comida_serpientee * 100;
	}
	
	
	short Obtener_Puntuacion()
	{
		return Puntuacion;
	}
	
	void Asigna_tiempo(short t) //Tiempo en segundos
	{
		tiempo =  t;
	}
	
	float Obtener_tiempo_minutos()
	{
		return tiempo/60;
	}
	
	float Obtener_Promedio()   //PUNTOS POR SEGUNDO
	{
		Promedio_PT = Puntuacion / tiempo;
			
		return Promedio_PT;
	}
	
}Jugador;  // ARREGLO DE OBJETOS PUBLICOS







class Serpiente_Snake : public Jugador_Snake
{
  private:
  	
   short posicion_x;
   short posicion_y; //POSICION GENERAL DE DONDE SE ENCUENTRA LA CABEZA
   	
   char  cuerpo;
   short color_serpiente;
   short cuerpo_total;
   short posicion_del_cuerpo_X[99];
   short posicion_del_cuerpo_y[99];
   
   //char  comida;
   short posicion_comida_x;
   short posicion_comida_y;
   
   bool Game_Over;
   	 
  
  public:
  	
  	
   void Asigna_Cuerpo()
   {
   	  gotoxy(15,18);
   	  Color(AMARILLO);
   	  cout<<"letra que sera el cuerpo de la serpiente : ";
   	  Color(VERDE2);
   	  cin>>cuerpo;
   	
   }
   
   
   void Asigna_Color_Serpiente()
   {
   		//Color(AMARILLO);
   		gotoxy(70,15);
   		cout<<"1.-AZUL";
   		gotoxy(70,16);
   		cout<<"2.-AMARILLO";
   		gotoxy(70,17);
   		cout<<"3.-ROJO";
   		gotoxy(70,18);
   		cout<<"4.-VERDE";
   		gotoxy(70,19);
   		cout<<"5.-PLATA";
   		
   		gotoxy(65,21);
   		cout<<"Seleccione el color de la Serpiente y Comida : ";
   		Color(VERDE2);
   		cin>>color_serpiente;
   		
   }
   
   short Obtener_color_serpiente()
   {
   		return color_serpiente;
   }
  	
  	
  	
   void Vida_serpiente()
   {
  	  
	  char TECLA;
	  
	  short W = 0; //contador auxiliar
	  
	  clock_t inicio_tiempo; // time.h
	  clock_t final_tiempo;  //variables tipo clock_t para calcular tiempo de juego en los jugadoress
	  
      Game_Over = false;
      
  	  posicion_x = 50;
	  posicion_y = 15;
	  cuerpo_total=1;
	  
	  
	  posicion_comida_x = 50;
   	  posicion_comida_y = 25;			//INICIALIZAR LA PRIMERA IMPRESION DE LA COMIDA		  	  
   	  gotoxy(posicion_comida_x,posicion_comida_y);
   	  printf("%c",254);
	  
  	  
	   inicio_tiempo = clock(); // time.h
  	  
  	   
	   while(Game_Over == false)  // JUEGO
	   {
	   		
	   		
	   	   if (TECLA == DERECHA || TECLA == IZQUIERDA )
	   	   {
	   		   Sleep(30);
		   }
			
		   else 
		   {
			  Sleep(200);
		   }
	   	
	   	
	   	   switch(color_serpiente)
		   {
			  	case 1 : Color(AZUL); break;
			  	case 2 : Color(AMARILLO); break;
			  	case 3 : Color(ROJO); break;
			  	case 4 : Color(VERDE); break;
			  	case 5 : Color(PLATA); break;
			  
			  	default : Color(PLATA); 
		   }
	   	
	   	
	   	
	   	   gotoxy(50,1);
	   	   cout<<"PUNTUACION : | "<<Obtener_Puntuacion()<<" |";
	   	   
	   	   
	   	   
		   
		   
		   //--------------------------------------------------------
		   
		   gotoxy(posicion_del_cuerpo_X[W],posicion_del_cuerpo_y[W]);
		   cout<<" ";
		   	   				
		   posicion_del_cuerpo_X[W] = posicion_x;
		   posicion_del_cuerpo_y[W] = posicion_y;
		   W++;
		   
		   if(W == cuerpo_total)
		   {
		   	  W = 0;
		   }
		   
		   
		   for(int b=0 ; b < cuerpo_total; b++)
		   {
		   	gotoxy(posicion_del_cuerpo_X[b],posicion_del_cuerpo_y[b]);
		   	cout<<cuerpo;  				
		   }
		   
		   //--------------------------------------------------------
		   
		   
		   
		   Comida_serpiente(); //verifica si la comida es ingerida y si es asi, asigna otra en otro lugar
		   
		   Asigna_Puntuacion(comida_ingerida()); 
		   
		   Muerte_Serpiente(); //verifica si muere y si es asi, da la instruccion de terminar el ciclo
		   
		   
		   
		   if(kbhit() == true)
		   {
		   	
		   	  TECLA = getch(); // LA TECLA SERA LO QUE LEA GETCH EN EL TECLADO
			
		   		
				switch( TECLA )
		  		{
		  			
		  		   if(TECLA != ABAJO)
		   	   		  {
		   	   		  	case ARRIBA:
		   	   		  	posicion_y--;
					  }
		   	   		
		   	   		break;
		   	   		
		   	    
			   
			   		case ABAJO:			//Valores ya definidos para las teclas en la libreria libgame
		   	   		   
		   	   		  if(TECLA != ARRIBA)
		   	   		  {
		   	   		  	posicion_y++;
					  }
		   	   			
		   	   	
		   	   		break;
		   	   		
							  
					case DERECHA:			//Valores ya definidos para las teclas en la libreria libgame
		   	   		
		   	   		  if(TECLA != IZQUIERDA)
		   	   		  {
		   	   		  	posicion_x++;
					  }
					  
					  
			    		
		   	   	
		   	   		break;
						  			  
							  		
		   	   		case IZQUIERDA:			//Valores ya definidos para las teclas en la libreria libgame
		   	   	
					if(TECLA != DERECHA)
		   	   		  {
		   	   		  	posicion_x--;
					  }
					  
					  
		   	   	
		   	   		break;
		   	   			
		   		}
		   	   
		   }
	       
	       
	       
	       
	       if(kbhit() == false)
		   {
		   	
		   		
				switch( TECLA )
		  		{
		   	   		
					if(TECLA != ABAJO)
		   	   		  {
		   	   		  	case ARRIBA:
		   	   		  	posicion_y--;
					  }
		   	   		
		   	   		break;
		   	   		
		   	    
			   
			   		case ABAJO:			//Valores ya definidos para las teclas en la libreria libgame
		   	   		   
		   	   		  if (TECLA != ARRIBA)
		   	   		  {
		   	   		  	posicion_y++;
					  }
		   	   		
		   	   		break;
		   	   		
							  
					case DERECHA:			//Valores ya definidos para las teclas en la libreria libgame
		   	   		
		   	   		  if(TECLA != IZQUIERDA)
		   	   		  {
		   	   		  	posicion_x++;
					  }
					  
					  
			    		
		   	   	
		   	   		break;
						  			  
							  		
		   	   		case IZQUIERDA:			//Valores ya definidos para las teclas en la libreria libgame
		   	   	
					  if(TECLA != DERECHA)
		   	   		  {
		   	   		  	posicion_x--;
					  }
					  
					  
		   	   	
		   	   		break;
		   	   		
		   	   			
		   		}
		   		   
		   }
		   
		   
		
	   }
	   
	   final_tiempo = clock(); // time.h
	   
	   Asigna_tiempo(  (final_tiempo - inicio_tiempo) / CLK_TCK ); // tiempo resgistrado en segundos
	   
  	   
  	   gotoxy(90,1);
  	   cout<<"Minutos : "<<Obtener_tiempo_minutos();
	   
	   
	   
   }
  	
  	
   void Comida_serpiente()
   {
		   	  
		if(posicion_x == posicion_comida_x && posicion_y == posicion_comida_y )
		{
			
			posicion_comida_x = (5+rand()%(116-6));
   			posicion_comida_y = (3+rand()%(28-4));
   			  	  
   			gotoxy(posicion_comida_x,posicion_comida_y);
   			//cout<<comida;
   			printf("%c",254);
   			
   			Beep(900,250);
   			
   			cuerpo_total++;
		}
	}
	
	void Muerte_Serpiente()
	{
		if(posicion_x == 115 || posicion_x == 5 || posicion_y == 3 || posicion_y == 27 || Obtener_Puntuacion() == 5000)
		{
			Game_Over = true;
		}
	}	  
   	
	
	short comida_ingerida()
	{
		return cuerpo_total-1;
	}  
		
}Serpiente;




class JUEGO : public Serpiente_Snake //----------------------- CLASE FINAL , OBJETOS DE JUEGO -----------------------
{
	
}Juego_de_jugador[50]; 




void Nuevo_Juego()
{
	system("cls");
	
	bool nombre_repetido = false;
	
	Num_Jugador = Num_Jugador + 1;
	
	for(int x = 0 ; x < 120; x++)	// LLENAR DE PUNTITOS LA PANTALLA
	{
		gotoxy(x,0);
		cout<<".";
		
		for(int y = 0 ; y < 30 ; y++)
		{
			Color(ROJO);
			gotoxy(x,y);
			cout<<".";
		}
	}
	
	Color(AZUL);
	marco_Secundario();
	
	Color(AMARILLO);
	gotoxy(20,5);
	cout<<" #     #                                            #                                ";
	gotoxy(20,6);
	cout<<" ##    #  #    #  ######  #    #   ####             #  #    #  ######   ####    #### ";
	gotoxy(20,7);
	cout<<" # #   #  #    #  #       #    #  #    #            #  #    #  #       #    #  #    #";
	gotoxy(20,8);
	cout<<" #  #  #  #    #  #####   #    #  #    #            #  #    #  #####   #       #    #";
	gotoxy(20,9);
	cout<<" #   # #  #    #  #       #    #  #    #      #     #  #    #  #       #  ###  #    #";
	gotoxy(20,10);
	cout<<" #    ##  #    #  #        #  #   #    #      #     #  #    #  #       #    #  #    #";
	gotoxy(20,11);
	cout<<" #     #   ####   ######    ##     ####        #####    ####   ######   ####    ####";
	
	
	
	
	Juego_de_jugador[Num_Jugador].Asigna_Nombre();
	
	for(short p = 1 ; p < Num_Jugador + 1 ; p++)
	{
		if( Juego_de_jugador[Num_Jugador].Obtener_Nombre() == Juego_de_jugador[p].Obtener_Nombre() && Num_Jugador != p)
		{
			nombre_repetido = true;
			gotoxy(25,18);
			Color(MORADO);
			cout<<"* ESTE NOMBRE YA EXISTE * ";
			
			Num_Jugador = Num_Jugador - 1;
		}
	}
	
	
	
	if(nombre_repetido == false)
	{
		Juego_de_jugador[Num_Jugador].Asigna_Cuerpo();
	
	
		Color(AMARILLO);
		Juego_de_jugador[Num_Jugador].Asigna_Color_Serpiente();
	
	
	
		system("cls");
	
	 
	
		Color(ROJO);
		marco_Secundario();
	
		switch(Juego_de_jugador[Num_Jugador].Obtener_color_serpiente())
    	{
 	  		case 1 : Color(AZUL); break;
	  		case 2 : Color(AMARILLO); break;
	  		case 3 : Color(ROJO); break;
	  		case 4 : Color(VERDE); break;
	  		case 5 : Color(PLATA); break;
			  
	  		default : Color(PLATA); 
   	
		}
	
		gotoxy(10,1);
		cout<<"NOMBRE : "<<Juego_de_jugador[Num_Jugador].Obtener_Nombre();
	
	

		Juego_de_jugador[Num_Jugador].Vida_serpiente();
	
	
	
		Color(MORADO);
		gotoxy(30,10);
		cout<<"o--o               o     o                            ";
		gotoxy(30,11);
		cout<<"|    o             |     |         o                  ";
		gotoxy(30,12);
		cout<<"O-o    o-o       o-O o-o |           o  o o-o o--o o-o";
		gotoxy(30,13);
		cout<<"|    | |  |     |  | |-' |         o |  | |-' |  | | |";
		gotoxy(30,14);
		cout<<"o    | o  o      o-o o-o o         | o--o o-o o--O o-o";
		gotoxy(30,15);
		cout<<"                               o   o             |";
		gotoxy(30,16);
		cout<<"                                o-o           o--o";
	   
	   	Color(ROJO);
		gotoxy(15,20);
		cout<<"*************************";
  		gotoxy(15,21);
  		cout<<"*PRESS ENTER TO CONTINUE*";
  		gotoxy(15,22);
  		cout<<"*************************";
	}
	

	else
	{
		Color(MORADO);
		gotoxy(15,20);
		cout<<"*************************";
  		gotoxy(15,21);
  		cout<<"*PRESS ENTER TO CONTINUE*";
  		gotoxy(15,22);
  		cout<<"*************************";
	}
	
  	
  	pausa();
	
}




void Reanudar()
{
	system("cls");
	
	string name;
	bool se_encontro_concidencia = false;
	short jugador_reanudar;
	bool cargando = false;
	
	for(int x = 0 ; x < 120; x++)	// LLENAR DE PUNTITOS LA PANTALLA
	{
		gotoxy(x,0);
		cout<<".";
		
		for(int y = 0 ; y < 30 ; y++)
		{
			Color(AZUL);
			gotoxy(x,y);
			cout<<".";
		}
	}
	
	Color(VERDE);
	marco_Secundario();
	
	Color(VERDE);
	gotoxy(20,5);
	cout<<" ######";
	gotoxy(20,6);
	cout<<" #     #  ######    ##    #    #  #    #  #####     ##    #####";
	gotoxy(20,7);
	cout<<" #     #  #        #  #   ##   #  #    #  #    #   #  #   #    #";
	gotoxy(20,8);
	cout<<" ######   #####   #    #  # #  #  #    #  #    #  #    #  #    #";
	gotoxy(20,9);
	cout<<" #   #    #       ######  #  # #  #    #  #    #  ######  #####";
	gotoxy(20,10);
	cout<<" #    #   #       #    #  #   ##  #    #  #    #  #    #  #   #";
	gotoxy(20,11);
	cout<<" #     #  ######  #    #  #    #   ####   #####   #    #  #    #";
	
	Color(AZUL);
	gotoxy(15,15);
	Color(VERDE);
	cout<<"Ingresa tu nombre de Jugador : ";
	Color(VERDE2);
	cin>>name;
	
	
	for(short n = 1 ; n < Num_Jugador + 1 ; n++) //Busqueda de concidencia en el nombre
	{
		if(name == Juego_de_jugador[n].Obtener_Nombre()) 
		{
			se_encontro_concidencia = true;
			jugador_reanudar = n;
		}
	}
	
	while(cargando == false)
	{
		Color(PLATA);
		gotoxy(20,18);
		cout<<"O.o.o.o";
		pausa(1000);
		gotoxy(20,18);
		cout<<"o.O.o.o";
		pausa(1000);
		gotoxy(20,18);
		cout<<"o.o.O.o";
		pausa(1000);
		gotoxy(20,18);
		cout<<"o.o.o.O";
		pausa(1000);
		
		gotoxy(20,18);
		cout<<"O.o.o.o";
		pausa(1000);
		gotoxy(20,18);
		cout<<"o.O.o.o";
		pausa(1000);
		gotoxy(20,18);
		cout<<"o.o.O.o";
		pausa(1000);
		gotoxy(20,18);
		cout<<"o.o.o.O";
		pausa(1000);
		cargando = true;
	}
	
	
	if(se_encontro_concidencia == true)
	{
		Color(PLATA);
		gotoxy(17,18);
		cout<<"¡Se encontro tu nombre!";
		
		Color(VERDE);
	    Juego_de_jugador[jugador_reanudar].Asigna_Color_Serpiente();
		
		
		system("cls");
		
		//Color(AZUL);
		//marco_Secundario();
		
		switch(Juego_de_jugador[jugador_reanudar].Obtener_color_serpiente()) //Asignar color del marco dependiendo del elegido
    	{
 	  		case 1 : Color(ROJO); break;
	  		case 2 : Color(ROJO); break;
	  		case 3 : Color(AZUL); break;
	  		case 4 : Color(MORADO); break;
	  		case 5 : Color(VERDE2); break;
			  
	  		default : Color(PLATA); 
		}
	
		marco_Secundario();
		
		
			
		switch(Juego_de_jugador[jugador_reanudar].Obtener_color_serpiente()) // asigna el color elegido para el nombre tambien
    	{
 	  		case 1 : Color(AZUL); break;
	  		case 2 : Color(AMARILLO); break;
	  		case 3 : Color(ROJO); break;
	  		case 4 : Color(VERDE); break;
	  		case 5 : Color(PLATA); break;
			  
	  		default : Color(PLATA); 
		}
	
		gotoxy(10,1);
		cout<<"NOMBRE : "<<Juego_de_jugador[jugador_reanudar].Obtener_Nombre();

		
		
		Juego_de_jugador[jugador_reanudar].Vida_serpiente();
		
		
		
		Color(MORADO);
		gotoxy(30,10);
		cout<<"o--o               o     o                            ";
		gotoxy(30,11);
		cout<<"|    o             |     |         o                  ";
		gotoxy(30,12);
		cout<<"O-o    o-o       o-O o-o |           o  o o-o o--o o-o";
		gotoxy(30,13);
		cout<<"|    | |  |     |  | |-' |         o |  | |-' |  | | |";
		gotoxy(30,14);
		cout<<"o    | o  o      o-o o-o o         | o--o o-o o--O o-o";
		gotoxy(30,15);
		cout<<"                               o   o             |";
		gotoxy(30,16);
		cout<<"                                o-o           o--o";
	   
		Color(VERDE2);
		gotoxy(15,20);
    	cout<<"*************************";
  		gotoxy(15,21);
  		cout<<"*PRESS ENTER TO CONTINUE*";
  		gotoxy(15,22);
  		cout<<"*************************";
  	
  		pausa();
		
		
		
	}
	
	else
	{
		Color(ROJO);
		gotoxy(17,18);
		cout<<"¡No se encontro tu nombre!";
		
		
		Color(VERDE);
		gotoxy(15,20);
    	cout<<"*************************";
  		gotoxy(15,21);
  		cout<<"*PRESS ENTER TO CONTINUE*";
  		gotoxy(15,22);
  		cout<<"*************************";
  	
  		pausa();
	}
		
}


void Tabla_puntuacion()
{
	system("cls");
	
	float Promedios[50];
	float auxiliar=0;
	short Y = 14;

	
	for(int x = 0 ; x < 120; x++)	// LLENAR DE PUNTITOS LA PANTALLA
	{
		gotoxy(x,0);
		cout<<".";
		
		for(int y = 0 ; y < 30 ; y++)
		{
			Color(VERDE);
			gotoxy(x,y);
			cout<<".";
		}
	}
	
	
	Color(MORADO);
	gotoxy(5,3);
	cout<<" ######";
	gotoxy(5,4);
	cout<<" #     #  #    #  #    #  #####  #    #    ##     ####   #   ####   #    #  ######   ####";
	gotoxy(5,5);
	cout<<" #     #  #    #  ##   #    #    #    #   #  #   #    #  #  #    #  ##   #  #       #";
	gotoxy(5,6);
	cout<<" ######   #    #  # #  #    #    #    #  #    #  #       #  #    #  # #  #  #####    ####";
	gotoxy(5,7);
	cout<<" #        #    #  #  # #    #    #    #  ######  #       #  #    #  #  # #  #            #";
	gotoxy(5,8);
	cout<<" #        #    #  #   ##    #    #    #  #    #  #    #  #  #    #  #   ##  #       #    #";
	gotoxy(5,9);
	cout<<" #         ####   #    #    #     ####   #    #   ####   #   ####   #    #  ######   ####";
	
	
	
	gotoxy(9,12);
	cout<<"POSICION";
	
	gotoxy(24,12);
	cout<<"NOMBRE";
	
	gotoxy(37,12);
	cout<<"PUNTOS";
	
	gotoxy(49,12);
	cout<<"TIEMPO Minutos";
	
	gotoxy(68,12);
	cout<<"PROMEDIO Puntos/segundo";
	
	gotoxy(7,13);
	cout<<"--------------------------------------------------------------------------------------";
	
	
	if(Num_Jugador == 0)
	{
		gotoxy(35,15);
		Color(AZUL);
		cout<<"Todavia no hay Jugadores";
		gotoxy(35,17);
		cout<<"Inica un nuevo Juego";
		
	}
	
	//-------------------------------------------------------------------------------
	
	for(short M = 1 ; M < Num_Jugador + 1 ; M++) 
	{
		Promedios[M] = Juego_de_jugador[M].Obtener_Promedio();
		
	}
	
	
	for(short R = 1 ; R < Num_Jugador + 1 ; R++) 
	{
		for(short S = R + 1 ; S < Num_Jugador + 1 ; S++)				//Ordena los promedios de mayor a menor
		{
				
			if(Promedios[R] <= Promedios[S])
			{
				auxiliar = Promedios[R];
				Promedios[R] = Promedios[S];
				Promedios[S] = auxiliar;
			}
		}
	}
	
	//-------------------------------------------------------------------------------
	
	
	for(short L = 1 ; L < Num_Jugador + 1 ; L++)
	{
		Juego_de_jugador[L].ya_impreso_en_tabla = false; 
	}
	
	
	
	
	for(short T = 1; T < Num_Jugador + 1 ; T++)
	{
		
		for(short U = 1 ; U < Num_Jugador + 1 ; U++)
		{

			if(Promedios[T] == Juego_de_jugador[U].Obtener_Promedio() && Juego_de_jugador[U].ya_impreso_en_tabla == false)
			{
				Color(VERDE2);
				
				gotoxy(11,Y);
				cout<<T;
		
				gotoxy(24,Y);
				cout<<Juego_de_jugador[U].Obtener_Nombre();
		
				gotoxy(38,Y);
				cout<<Juego_de_jugador[U].Obtener_Puntuacion();
		
				gotoxy(54,Y);
				cout<<Juego_de_jugador[U].Obtener_tiempo_minutos();
				
				Color(ROJO);
		
				gotoxy(76,Y);
				cout<<Juego_de_jugador[U].Obtener_Promedio();
				
				Juego_de_jugador[U].ya_impreso_en_tabla = true;
		
				Y++;	
				
			}
			
		}
		
	}
	
	
	
	Color(PLATA);
	gotoxy(80,25);
    cout<<"*************************";
  	gotoxy(80,26);
  	cout<<"*PRESS ENTER TO CONTINUE*";
  	gotoxy(80,27);
  	cout<<"*************************";
  	
  		
	pausa();
	
}



void Portada()
{
	system("cls");
	
	OcultaCursor();
	
	Beep(400 ,5000);

	
	for(int x = 0 ; x < 120; x++)	// LLENAR DE PUNTITOS LA PANTALLA
	{
		gotoxy(x,0);
		cout<<".";
		
		for(int y = 0 ; y < 30 ; y++)
		{
			Color(MORADO);
			gotoxy(x,y);
			cout<<".";
		}
	}
	

	Color(MORADO);
	
	Color(ROJO);
	
	marco_Total();
	
	Color(AZUL);
	
	marco_Secundario();
	
	
	
	Color(PLATA);
	gotoxy(9,10); 
	cout<<":'######::'##::: ##::::'###::::'##:::'##:'########:::::'######::::::'###::::'##::::'##:'########:";
	gotoxy(9,11);                         
	cout<<"'##... ##: ###:: ##:::'## ##::: ##::'##:: ##.....:::::'##... ##::::'## ##::: ###::'###: ##.....::";
	gotoxy(9,12);          
  	cout<<" ##:::..:: ####: ##::'##:. ##:: ##:'##::: ##:::::::::: ##:::..::::'##:. ##:: ####'####: ##:::::::"; 
   	gotoxy(9,13);
  	cout<<". ######:: ## ## ##:'##:::. ##: #####:::: ######:::::: ##::'####:'##:::. ##: ## ### ##: ######:::";
  	gotoxy(9,14);
  	cout<<":..... ##: ##. ####: #########: ##. ##::: ##...::::::: ##::: ##:: #########: ##. #: ##: ##...::::";
  	gotoxy(9,15);
  	cout<<"'##::: ##: ##:. ###: ##.... ##: ##:. ##:: ##:::::::::: ##::: ##:: ##.... ##: ##:.:: ##: ##:::::::";
  	gotoxy(9,16);
  	cout<<". ######:: ##::. ##: ##:::: ##: ##::. ##: ########::::. ######::: ##:::: ##: ##:::: ##: ########:";
  	gotoxy(9,17);
  	cout<<":......:::..::::..::..:::::..::..::::..::........::::::......::::..:::::..::..:::::..::........::";
  	
  	
  	
  	gotoxy(15,20);
    cout<<"By : Edgar Alan ";
  	
	Beep(1200 ,500);
	Beep(1100 ,500);
	Beep(1000 ,500);
	Beep(900 ,500);
	Beep(800 ,500);
	Beep(700 ,500);
	Beep(600 ,500);
	Beep(500 ,500);
	Beep(400 ,500);
	Beep(300 ,8000);
	
	
	Color(VERDE);
	gotoxy(15,20);
  	cout<<"*************************";
  	gotoxy(15,21);
  	cout<<"*PRESS ENTER TO CONTINUE*";
  	gotoxy(15,22);
  	cout<<"*************************";
  	
  	//getch();
  	pausa();
	
	
}




void Menu_Snake()
{
	system("cls");
	
	short opcion;
	
	Beep(600,1500);
	
	
	do
	{
		
		
		Color(MORADO);
		for(int x = 0 ; x < 120; x++)	// LLENAR DE PUNTITOS LA PANTALLA
		{
			gotoxy(x,0);
			cout<<".";
		
			for(int y = 0 ; y < 30 ; y++)
			{
				gotoxy(x,y);
				cout<<".";
			}
		}
	
		Color(AMARILLO);
		marco_Secundario();
		
		/*
	
		Color(ROJO);
		gotoxy(20,5);
		cout<<"::::    ::::  :::::::::: ::::    ::: :::    :::";
		gotoxy(20,6);
		cout<<"+:+:+: :+:+:+ :+:        :+:+:   :+: :+:    :+:";
		gotoxy(20,7);
		cout<<"+:+ +:+:+ +:+ +:+        :+:+:+  +:+ +:+    +:+";
		gotoxy(20,8);
		cout<<"+#+  +:+  +#+ +#++:++#   +#+ +:+ +#+ +#+    +:+";
		gotoxy(20,9);
		cout<<"+#+       +#+ +#+        +#+  +#+#+# +#+    +#+";
		gotoxy(20,10);
		cout<<"#+#       #+# #+#        #+#   #+#+# #+#    #+#";
		gotoxy(20,11);
		cout<<"###       ### ########## ###    ####  ########"; */
		
		
		
		
		Color(ROJO);
		gotoxy(20,5);
		cout<<"        :::   :::       ::::::::::       ::::    :::      :::    :::";
		gotoxy(20,6);
		cout<<"      :+:+: :+:+:      :+:              :+:+:   :+:      :+:    :+:";
		gotoxy(20,7);
		cout<<"    +:+ +:+:+ +:+     +:+              :+:+:+  +:+      +:+    +:+";
		gotoxy(20,8);
		cout<<"   +#+  +:+  +#+     +#++:++#         +#+ +:+ +#+      +#+    +:+";
		gotoxy(20,9);
		cout<<"  +#+       +#+     +#+              +#+  +#+#+#      +#+    +#+";
		gotoxy(20,10);
		cout<<" #+#       #+#     #+#              #+#   #+#+#      #+#    #+#";
		gotoxy(20,11);
		cout<<"###       ###     ##########       ###    ####       ########";
	
	
	
		gotoxy(30,13);
		Color(AMARILLO);
		cout<<"1.-Nuevo Juego ";
		gotoxy(30,14);
		Color(ROJO);
		cout<<"***************";
	
		gotoxy(30,17);
		Color(AMARILLO);
		cout<<"2.-Reanudar  ";
		gotoxy(30,18);
		Color(ROJO);
		cout<<"************";
	
		gotoxy(30,21);
		Color(AMARILLO);
		cout<<"3.-Tabla de Puntuacion";
		gotoxy(30,22);
		Color(ROJO);
		cout<<"**********************";
	
		gotoxy(30,25);
		Color(AMARILLO);
		cout<<"4.-SALIR  ";
		gotoxy(30,26);
		Color(ROJO);
		cout<<"*********";
	
	
		Color(VERDE);
		gotoxy(100,5);
		cout<<",___,";
		gotoxy(100,6);
		cout<<"[O.o]";
		gotoxy(100,7);
		cout<<"/)__)";
		gotoxy(100,8);
		cout<<" -''-";
	
	
	
	
		Color(PLATA);
		gotoxy(80,18);
		cout<<"--------";
		gotoxy(80,19);
		cout<<"-      -";
		gotoxy(80,20);
		cout<<"--------";
		gotoxy(80,21);
		cout<<"opcion";
	
		gotoxy(83,19);
		cin>>opcion;
	
	
		while(opcion > 4 || opcion < 1 )
		{
			Color(AZUL);
			gotoxy(70,17);
			cout<<" ___";
			gotoxy(70,18);
			cout<<"(._.)";
			gotoxy(70,19);
			cout<<"<|---<";
			gotoxy(70,20);
			cout<<"_||_";
		
			Color(PLATA);
			gotoxy(80,18);
			cout<<"--------";
			gotoxy(80,19);
			cout<<"-      -";
			gotoxy(80,20);
			cout<<"--------";
			gotoxy(80,21);
			Color(ROJO);
			cout<<"opcion";
	
			gotoxy(82,19);
			cin>>opcion;
		}
		
		
		switch (opcion)
		{
			case 1 :
				
			   Nuevo_Juego();
				
							break;
			case 2 :
				
				Reanudar();
							break;
			case 3 :
				
				Tabla_puntuacion();
							break;
		}
		
	pausa(2000);	
	Beep(700,1500);
		
	
	} while(opcion != 4);
	
    Beep(300,500);

}





int main()
{
	
	Portada();
	Menu_Snake();
		
	return 0;
}


void rvr()
{
		
	Color(PLATA);
	gotoxy(9,10); 
	cout<<"  ******** ****     **     **     **   ** ********      ******   **                           **         ";
	gotoxy(9,11);                         
	cout<<" **////// /**/**   /**    ****   /**  ** /**/////      **////** /**                          //         /";
	gotoxy(9,12);          
  	cout<<"/**       /**//**  /**   **//**  /** **  /**          **    //  /**  ******    ******  ****** **  *****  "; 
   	gotoxy(9,13);
  	cout<<"/*********/** //** /**  **  //** /****   /*******    /**        /** //////**  **////  **//// /** **///** ";
  	gotoxy(9,14);
  	cout<<"////////**/**  //**/** **********/**/**  /**////     /**        /**  ******* //***** //***** /**/**  //  ";
  	gotoxy(9,15);
  	cout<<"       /**/**   //****/**//////**/**//** /**         //**    ** /** **////**  /////** /////**/**/**   ** ";
  	gotoxy(9,16);
  	cout<<" ******** /**    //***/**     /**/** //**/********    //******  ***//******** ******  ****** /**//*****  ";
  	gotoxy(9,17);
  	cout<<"////////  //      /// //      // //   // ////////      //////  ///  //////// //////  //////  //  /////   ";
  	
  	
}
