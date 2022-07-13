#include <iostream>
#include <iomanip>
#include <cstdlib> 
#include <fstream> 
#include <cstring>
#include <string.h>
#include <conio.h>
#include <windows.h>


//lA INFO SOLO SE LEE DESDE EL TXT
//eL RESTO DE DATOS ESTA CONTENIDO EN EL LISTA.DAT
const char* LETRAS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ -1234567890";
const char* INFO = "ABCDEFGHIJKLMNOPQRSTUVWXYZ .,;:<>-0123456789#abcdefghijklmnopqrstuvwxyz";
const char* NUMEROS = "0123456789";
const char* REAL = "0123456789.";
const char* NOTAC = "0123456789.E+-";
const char* FICHERO = "SISTEMA.DAT"; 


using namespace std;

class Sistema{
      private:
              char nombre[31];
              int satelites;
              long long administrador;
              long long usuario;
              double diametro;     // Diametro ecuatorial en kilometros
    		  double masa;         // Masa relativa a la tierra
    		  double densidad;     // Relacion Masa - Volumen (En g/cm3)
    		  double perorbital;   // De orbita en A�os terrestres
    		  double perrotac;     // Rotacion (en relacion a los dias terrestres)
    		  long long distsol;      // Notac. cient�fica 1.8E+8
      public:
             void Getdata();
             void Listar();
             void Crear(char c[], char info[]); //Crea el archivo txt concerniente a cada planeta
             void Mostrar(int k, bool cambiar, bool encontr); /*Muestra info b�sica y luego lo que se encuentra en el archivo de texto (Editar directamente al txt y que lo muestre)
                                                               Mostrar por numero de registro (el usuario decide cual ver, y inmediatamente se muestra la info)*/
             void Buscar(); // Buscar por nombre
             void Cambiar(int k); //Cambio de Datos
             void Eliminar(int k);//Borrar
             void OrdNombre();//Organizar por Orden Alfabetico
             void ValidacionU();
             void ValidacionA();
};							  

// Mensajes del Menu
string mensaje[] = {"     [1].    ADICIONAR PLANETA      ", 
                    "     [2].    LISTAR                 ", 
                    "     [3].    CONSULTAR INFORMACION  ", 
                    "     [4].    BUSCAR POR NOMBRE      ", 
                    "     [5].    MODIFICAR DATOS        ", 
                    "     [6].    ELIMINAR DATOS         ", 
                    "     [7].    ORDENAR POR NOMBRE     ", 
                    "     [0]        Salir               "};
                    
// Mensajes del Menu
string usuario[] = {"          INICIO DE SESION         ", 
                    "         �Quien Desea Ingresar?    ", 
                    "     [1].    USUARIO               ", 
                    "     [2].    ADMINISTRADOR         ", 
                    "     [3].    INVITADO              ", 
                    "     [0]        Salir              "};
                    

void setcolor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Validacion de una cadena
void editcad(char* s, long max, const char* validos, bool solomayus)
{
    char c;
    int i;
    s[0] = 0; i = 0;
    do {
        c=getch();
        if (solomayus){
        	c=toupper(c);
		}
        switch (c) {
        case 8: // <Retroceso>
            if (i > 0) {
                i--;  putch(c); //Retroceso
                putch(' ');
                putch(8); //Retroceso
            }
            break;
        case 13: // Tecla <Intro>
            s[i] = 0;
            break;
        default:
            if (i < max)
                if (strchr(validos, c)) {
                    putch(c);
                    s[i++] = c;
                }
        } /* switch */
    } while (c!=13);
    while (i<max)
    {
    	if (i==max-1)
    		s[i]=13;
    	else
    		s[i]=0;
    	i++;
	}
} // editcad

// Valida un numero entero
long getint(int max)
{
    char s[12];
    editcad(s, max, NUMEROS, false);
    return (atol(s));
} /* getint */

// Valida un numero real
double getreal(int max)
{
    char s[21];
    editcad(s, max, REAL, false);
    return (atof(s));
} /* getfloat */

// Valida un numero en notac. cient�fica
double getnotac(int max)
{
    char s[21];
    editcad(s, max, NOTAC, true);
    return (atof(s));
} /* getfloat */

// Valida Contrase�a
long getcont(int max)
{
    char s[21];
    editcad(s, max, INFO, false);
    return (atol(s));
} /* getint */

void addtxt(char s[]) //A�ade la extension Txt a un nombre para crear el archivo
{					  //Asi el usuario solo ingresa el nombre como lo haria normalmente
	for (int i=0; i<30; i++) {
		if (s[i]==0) {
			s[i]='.';
			s[i+1]='T';
			s[i+2]='X';
			s[i+3]='T';
			for (int j=i+4; j<30; j++) {
				s[j]=0;
			}
			break;
		}
	}
}

/* Funciones Globales */

//MENUS

//Menu Principal 
void menu()
{
    int i;
    setcolor(0x17);
    system("CLS");
    setcolor(0x17);
    cout<<"               ______________________________________________ "<<endl;
	cout<<"              |----------------------------------------------|"<<endl;
	cout<<"              |            REGISTRO DE PLANETAS DEL          |"<<endl;
	cout<<"              |          SISTEMA SOLAR SISTEMA SOLAR         |"<<endl;
	cout<<"              *----------------------------------------------*"<<endl;

    for(int i=0;i<8;i++)
    {
    cout<<"              |"      <<mensaje[i]<<"          |"<<endl;
    }
    cout<<"              *----------------------------------------------*"<<endl;
	cout<<"              |______________________________________________|"<<endl;

}

//Color y cabecera
//(esta se la robe a daniel por si su merced quiere ponerle varios colores a la consola)
void cabecera(char txto[], int modo, int nro)//Es una version bonita de Puttdata, sin puttdata v':
{
	int cant = 0; 
	int esp = 40; 
	if (modo==1){
	    printf("\n");
		printf("\t ________________________________\n"); 
		printf("\t --------------------------------\n"); 
		printf("\t          PLANETA NUMERO %3d \n",nro);
		printf("\t --------------------------------\n"); 
		
	}
	else {
		for (int j=0; txto[j]!=0; j++)
			cant++;
		if (modo==2)
   			cout<<"\n\n                          REGISTRO ENCONTRADO:\n";
   		if (modo==3)
   			cout<<"\n                     	  INFORMACION DETALLADA" << endl << endl;
   		if (modo==4)
   			cout<<"\n                      DATOS HASTA EL MOMENTO:" << endl << endl;
		for (int i=0; i<esp-cant; i++)
			cout << " ";
		cout << "*";
		for (int i=0; i<cant+2; i++)
			cout << "-";
		cout << "*" << endl;
		for (int i=0; i<esp-cant; i++)
			cout << " ";
		cout << "| " << txto << " |" << endl;
		for (int i=0; i<esp-cant; i++)
			cout << " ";
		cout << "*";
		for (int i=0; i<cant+2; i++)
			cout << "-";
		cout << "*" << endl;
		
	}
}

//Copia Los datos de un "registro" que estan dentro del archivo txt para luego pasarlos a uno con nombre diferente
void renombre (char nuevo[], char viejo[]) 
{
	string copyc;
	fstream desc; 
	desc.open(viejo, ios::in | ios::binary);
	while(!desc.eof())
    {
        getline(desc, copyc);
    }
	desc.close();
	desc.open(nuevo, ios::out | ios::binary); //Se pasa el texto del archivo viejo al nuevo
	desc << copyc;
	desc.close();
    remove(viejo); // Se elimina el archivo viejo
    rename(viejo, nuevo);
}

/* Funciones espaciales: Sistema */
// Lee los datos y los guarda en un archivo
void Sistema::Getdata()
{
     ofstream fout;
     Sistema planeta;
     char resp = 'A';
     int i;
     fout.open(FICHERO, ios::out | ios::binary | ios::app);
     if (!fout) {
                cout<<"Error en creacion de archivo"<<endl;
                system("PAUSE");
                exit(1);
                }
     do {
     	 char info[101]; 
     	 fout.seekp(0L, ios::end);
     	 i = fout.tellp()/sizeof(Sistema);//tellp; devuelve la posici�n (ahi estoy buscando que el sistema se quede en el ultimo lugar del fichero)
         system("CLS");
         cabecera(planeta.nombre, 1, i+1);//To'o pa' que se vea bonito c:
         cout<<"\t \t  ______________________________________ "<<endl;
		 cout<<"\t \t |--------------------------------------|"<<endl;
		 cout<<"\t \t |           CAPTURA DE DATOS           |"<<endl;
		 cout<<"\t \t |______________________________________|"<<endl;
		 cout<<"\t \t  -------------------------------------- "<<endl;
         cout<<"\n     >) Nombre             : "; editcad(planeta.nombre, 26, LETRAS, true);
         cout<<"\n     >) Informacion del planeta    : "; editcad(info, 100, INFO, false);
         if (resp=='A')//Por si el usuario quiere escribir desde consola, le decimos que lo haga en el .txt (sin tildes pls)
         	cout<<"\n\n Luego puede cambiar la informacion de cada planeta con un editor de texto, desde su correspondiente archivo '.TXT'. \n" ;
         cout<<"\n     >) Nro. de satelites principales : "; planeta.satelites = getint(2);
         cout<<"\n     >) Diametro ecuatorial (Km)  : "; planeta.diametro = getreal(12);
	     cout<<"\n     >) Masa relativa a la tierra   : "; planeta.masa = getreal(12);
	     cout<<"\n     >) Densidad (g/cm3)      : "; planeta.densidad = getreal(12);
	     cout<<"\n     >) Periodo orbital (anios)   : "; planeta.perorbital = getreal(12);
	     cout<<"\n     >) Periodo rotacional (dias)  : "; planeta.perrotac = getreal(12);
	     cout<<"\n     >) Distancia aproximada al sol, Km y en Notac. Cientifica, #E+ : "; planeta.distsol = getnotac(12);
	     fout.write((char*)&planeta, sizeof(Sistema));
         planeta.Crear(planeta.nombre, info);
         cout << "\n\n       Desea agregar otro planeta (S/N)?";
         resp = toupper(getch());
     } while (resp == 'S');
     fout.close();
} // getdata

//Creacion del archivo de texto donde se contendr� la informaci�n de cada planeta.
void Sistema::Crear(char c[], char info[])
{
	ofstream text;
	char resp[31];
	string copyc;
	snprintf(resp, 30, "%s", c);
	addtxt(c);
	text.open(c, ios::out | ios::binary | ios::app);
	text << info; //Otro m�todo de escribir en un archivo
	text.close();
	ifstream desc; // Para obtener el texto dentro del archivo de texto
	desc.open(c, ios::in);
	while(!desc.eof())
    {
        getline(desc, copyc);
    }
	desc.close();
}

// Listado de registros
void Sistema::Listar()
{
     ifstream fin;
     Sistema planeta;
     int i;
     fin.open(FICHERO, ios::in | ios::binary);
     if (!fin) {
         cout<<"\n Error en acceso al archivo"<<endl;
         exit(1);
     }
     system("cls");
     cout<<endl;
     cout<<"       ________________________________________________"<<endl;
     cout<<"      |-----------------------------------------------|"<<endl;
     cout<<"      |     #Reg.      |     NOMBRE DEL PLANETA       |"<<endl;
     cout<<"      *-----------------------------------------------*"<<endl;
     i = 0;
     while (!fin.eof()) {
           fin.read((char*)&planeta, sizeof(Sistema));
           if (!fin.eof()) {
               printf("               %3d              %-30s\n", i+1, planeta.nombre);
           }
           i++;
          
     } // while
      cout<<"      |-----------------------------------------------|"<<endl;
	  cout<<"      |_______________________________________________|"<<endl;
	 fin.close();
} // listar

/*Aqui toca hacer algo loco; En lugar de volver la funcion como un tipo estructura para que no solo nos deje manipular datos tipo privado,
sino tambien los datos guardados en el .txt, capturamos el nombre y lo almacenamos en otra variable, este nombre queda guardado en el fichero 
(y con addtxt agregamos lo que este en el txt)  y de ahi pasamos esos datos de adentro del archivo, a una variable string data*/
void Sistema::Mostrar(int k, bool cambiar, bool encontr) 
{											
	ifstream fin, desc;
	Sistema planeta;
	char access[31];
	string data;
	fin.open(FICHERO, ios::in | ios::binary);
    if (!fin){
        cout<<"Error en acceso al archivo.";
        exit(1);
    }
    fin.seekg(k*sizeof(Sistema), ios::beg);
   	fin.read((char*)&planeta, sizeof(Sistema)); 
   	if (cambiar)     					  
    	cabecera(planeta.nombre, 4, 0);
    else if (encontr)
    	cabecera(planeta.nombre, 2, 0);		  
    else 								  
    	cabecera(planeta.nombre, 3, 0);		  
    //Ahi arribita esta buscando la posicion (cant) de registros del fichero	
   	snprintf(access, 30, "%s", planeta.nombre);//Es como el printf, solo que en lugar de imprimir el contenido se almacena como una cadena en el b�fer se�alado por s
   	addtxt(access);//Pos la funk we                       
   	desc.open(access, ios::in | ios::binary); 
   	while(!desc.eof())
    {
        getline(desc, data);                   
    }
    cout << "\n Breve Descripcion del Planeta O Planetoide: " << data << endl << endl;
    desc.close();
    cout<<"                          -DATOS ADICIONALES-" << endl;
    cout<<"            >) Numero de satelites principales: " << planeta.satelites << "." << endl;
    cout<<"            >) Diametro ecuatorial: " << planeta.diametro << " Km." << endl;
	cout<<"            >) Masa relativa a la tierra: " << planeta.masa << " masas terrestres." << endl;
	cout<<"            >) Densidad: " << planeta.densidad << " g/cm3." << endl;
	cout<<"            >) Periodo orbital: " << planeta.perorbital << " anios." << endl;
	cout<<"            >) Periodo rotacional: " << planeta.perrotac << " dias." << endl;
	cout<<"            >) Distancia aproximada al sol: " << planeta.distsol << " Km." << endl;
	fin.close();
}
//Ordenar por Burbuja
void Sistema::OrdNombre()
{
    Sistema aux, aux1;
    long curpos, length;
    int nr, tam;
    bool ordenado = false;
    
    fstream fs(FICHERO, ios::in | ios::out | ios::binary);
    if (!fs) {
        cout << "Error en acceso al archivo." << endl;
        exit(1);
    }
    
    fs.seekg(0L, ios::end);
    length = fs.tellg(); 
    tam = sizeof(Sistema);
    nr = (length / tam); 
    
    while (!ordenado) {
        ordenado = true;
        for (int i = 0; i < (nr - 1); i++) {
            fs.seekg((long)i * tam, ios::beg);
            fs.read((char*)&aux, tam);
            fs.seekg((long)(i + 1) * tam, ios::beg);
            fs.read((char*)&aux1, tam);
            if (strcmp(aux.nombre,aux1.nombre)>0){
                fs.seekp((long)i * tam, ios::beg);
                fs.write((char*)&aux1, tam);
                fs.seekp((long)(i + 1) * tam, ios::beg);
                fs.write((char*)&aux, tam);
                ordenado = false;
                } //if
            }//for
        } //while
        fs.close();
}//ordNombre


// Consulta por Nombre
void Sistema::Buscar()
{
    ifstream fin;
    Sistema planeta;
    char subj[31];
    bool hallado;
    char resp;
    fin.open(FICHERO, ios::in | ios::binary);
    if (!fin) {
         cout << " \n Error en creacion de archivo" << endl;
         exit(1);
    }
    system("CLS");
    cout << "\n\n            Nombre a buscar: " ; editcad(subj, 30, LETRAS, true);
    hallado = false;
    int i=0;
    while (!fin.eof() && !hallado) {
          fin.read((char*)&planeta, sizeof(Sistema));
          if(strcmp(subj,planeta.nombre)==0){
              hallado=true;
              planeta.Mostrar(i, false, true); 
              cout<<"\n\t\t    Desea editar este registro (S/N)?";  
              resp=toupper(getch());
              fin.close();
              if (resp=='S')
        	      planeta.Cambiar(i);
              break;
          } // if
          i++;
    } // while
    fin.close();
    if(!hallado){
    	cout<<"\n\n       \aAparentemente, este nombre no existe en el registro." << endl;
    	getch();
	}
} // consNombre

//SE ALERA EN EL .DAT                   
void Sistema::ValidacionU()
{
	Sistema planeta;
	long long usuario;
	ifstream fin;
    char subj[31];
    bool hallado;
    char resp;
    fin.open(FICHERO, ios::in | ios::binary);
    if (!fin) {
         cout << " \n Error en creacion de archivo" << endl;
         exit(1);
    }
    system("CLS");
    cout<<"\t Por Favor, ingrese su Contrase�a: " ; cin>>usuario;
    hallado = false;
    int i=0;
    while (!fin.eof() && !hallado) {
          fin.read((char*)&planeta, sizeof(Sistema));
          if(usuario==planeta.usuario){
              hallado=true;
              planeta.Mostrar(i, false, true); 
              cout<<"\n\t\t    Desea editar este registro (S/N)?";  
              resp=toupper(getch());
              fin.close();
              if (resp=='S')
        	      planeta.Cambiar(i);
              break;
          } // if
          i++;
    } // while
    fin.close();
    if(!hallado){
    	cout<<"\n\n       \aAparentemente, este nombre no existe en el registro." << endl;
    	getch();
	}
}

void 

void Sistema::Cambiar(int k)
{
	char opc, access[31], previo[31], newdesc[101];
	int result;
	bool exit = false;
	Sistema planeta;
	ofstream desc;
	fstream fs;
	while (!exit)
	{
		system("cls");
		cout<<"\t \t ______________________________________ "<<endl;
		cout<<"\t \t|--------------------------------------|"<<endl;
		cout<<"\t \t|        MODIFICACION DE DATOS         |"<<endl;
		cout<<"\t \t|    SISTEMA SOLAR SISTEMA SOLAR       |"<<endl;
	    cout<<"\t \t|--------------------------------------|"<<endl;
		cout<<"\t \t|      1. NOMBRE                       |"<<endl;
        cout<<"\t \t|      2. INFORMACION                  |"<<endl;
		cout<<"\t \t|      3. CANTIDAD DE SATELITES        |"<<endl;
		cout<<"\t \t|      4. DIAMETRO ECUATORIAL          |"<<endl;
		cout<<"\t \t|      5. MASA                         |"<<endl;
		cout<<"\t \t|      6. DENSIDAD                     |"<<endl;
		cout<<"\t \t|      7. PERIODO ORBITAL              |"<<endl;
		cout<<"\t \t|      8. PERIODO ROTACIONAL           |"<<endl;
		cout<<"\t \t|      9. DISTANCIA AL SOL             |"<<endl;
		cout<<"\t \t|     10. RENOVACION  DE DATOS         |"<<endl;
		cout<<"\t \t|              0. Salir                |"<<endl;
		cout<<"\t \t|______________________________________|"<<endl;
		cout<<"\t \t|--------------------------------------|"<<endl;
		cout<<"\t \t ----->  Por favor, escoja su opcion: " ; cin>>result;
		cout << endl;
		planeta.Mostrar(k, true, false);
		fs.open(FICHERO, ios::in | ios::out | ios::binary);
    	fs.seekp(k*sizeof(Sistema), ios::beg);
    	fs.read((char*)&planeta, sizeof(Sistema));
		switch(result){
            case 1:
           		snprintf(previo, 30, "%s", planeta.nombre); //Antes de
   				addtxt(previo);
                cout<<"\n      Nuevo Nombre          : "; editcad(planeta.nombre, 26, LETRAS, true);
           		snprintf(access, 30, "%s", planeta.nombre); //Despues de
   				addtxt(access);
   				if (strcmp(access,previo)!=0){ 
   						renombre(access, previo);//Toca "crear" un nuevo fichero que contnta la nueva informacion por eso habia colocado una funcion 
   						                        //que cambiaba el nombre del fichero, (Well joke's on you)
                		cout<<"\n\n        Archivo " <<previo<< " renombrado a " <<access<< "." ;
				   }
                break;
                
            case 2:
           		cout<<"\n       Nueva Informacion           : "; editcad(newdesc, 100, INFO, false);
           		snprintf(access, 30, "%s", planeta.nombre); // Nombre antes del cambio
   				addtxt(access);
           		desc.open(access, ios::out | ios::binary);
           		desc << newdesc ;
           		desc.close();
                break;
                
            case 3: cout<<"\n Nuevo nro de Satelites: "; planeta.satelites=getint(2);
                    break;
                    
            case 4: cout<<"\n  Nuevo Diametro Ecuatorial (en Km): "; planeta.diametro = getreal(12);
                    break;
                    
            case 5: cout<<"\n  Nueva Masa (Relativa a la Tierra): "; planeta.masa = getreal(12);
           		    break;
           	
            case 6: cout<<"\n   Nueva Densidad (g/cm3): "; planeta.densidad = getreal(12);
           	        break;
           	        
		    case 7: cout<<"\n    Nuevo Periodo Orbital (dias)   : "; planeta.perrotac = getreal(12);
				    break;
		    
			case 8: cout<<"\n   Nuevo Periodo Rotacional (anios)  : "; planeta.perrotac = getreal(12);
				    break;
		    
			case 9: cout<<"\n Nueva Distancia Aprox. al Sol (Km o Cientifica #E+): "; planeta.distsol = getnotac(12);
				    break;
				    
		    case 10:
		    	    cout<<"\n\t\t        Renovacion Total de Datos ...\n" ;
					cout<<"\n  Nro. de satelites principales: "; planeta.satelites = getint(2);
            	    cout<<"\n  Diametro Ecuatorial (en Km): "; planeta.diametro = getreal(12);
	        	    cout<<"\n  Masa (Relativa a la Tierra): "; planeta.masa = getreal(12);
	        	    cout<<"\n  Densidad (g/cm3): "; planeta.densidad = getreal(12);
	        	    cout<<"\n  Periodo orbital (dias): "; planeta.perorbital = getreal(12);
	        	    cout<<"\n  Periodo Rotacional (anios): "; planeta.perrotac = getreal(12);
	        	    cout<<"\n  Distancia Aprox. al Sol (Km o Cientifica #E+): "; planeta.distsol = getnotac(12);
	        	break;
        }//switch
		if (result<10&&result!=0)
		{
			fs.seekp(k*sizeof(Sistema), ios::beg);
			fs.write((char*)&planeta, sizeof(Sistema));
			fs.close();
			cout << "\n\n             Continuar (S/N)? " ;
			opc = toupper(getch());
			if (opc!='S')
				exit = true;
		}
		if (result==0)
			exit = true;
	}
}

/* Eliminar */
void Sistema::Eliminar(int k)
{
    system("CLS");
    ifstream fin;
    ofstream fout;
    Sistema planeta;
    char resp, access[31];
    fin.open(FICHERO, ios::in | ios:: binary);
    if (!fin){
        cout<<"Error en acceso al archivo.";
        exit(1);
    }
    fout.open("TEMPORAL.DAT", ios::out | ios:: binary);
    if (!fout){
        cout<<"Error en acceso al archivo.";
        exit(1);
    }
    fin.seekg(k*sizeof(Sistema), ios::beg);
   	fin.read((char*)&planeta, sizeof(Sistema));
    planeta.Mostrar(k, false, false);
    cout << "\n         Esta seguro de eliminar este registro (S/N)?: " ;
    resp=toupper(getche());
    if (resp == 'S'){
        fin.seekg(0L, ios::beg); // Puntero al comienzo
        while(!fin.eof())
        {
            fin.read((char*)&planeta, sizeof(Sistema));
            if (fin.tellg()/sizeof(Sistema)!=k+1&&!fin.eof()){
                fout.write((char*)&planeta, sizeof(Sistema));
            }
            else if (fin.tellg()/sizeof(Sistema)==k+1&&!fin.eof()) // Aqu� se "atrapa" al dato que se quiere eliminar
            	snprintf(access, 30, "%s", planeta.nombre); //Se coge el nombre y se almacena en otra variable
        }
   		addtxt(access);
   		remove(access);
        fin.close();
        fout.close();
        remove(FICHERO);
        rename("TEMPORAL.DAT", FICHERO);
        cout << "                 Datos eliminados satisfactoriamente!" << endl;
    } //if si
    
}




/* Programa Principal */
using namespace std;
int main(int argc, char** argv)
{
	int pos, n = 3;
    Sistema planeta;
    fstream fs;
    char resp, opcion, phi = 157;
    bool salir = false;
    
    do {
    	fs.open(FICHERO, ios::in | ios::binary);
    	if(!fs) //Se comprueba si el archivo existe
    		n=0;
		else{
			fs.seekg(0L, ios::end);
            n = fs.tellg()/sizeof(Sistema); //Numero de registros existentes
		}
    	fs.close();
        menu();
        if (n==0){
        	cout << endl;
        	for (int i=0; i<34; i++)
        		cout << " ";
        	cout << phi;
        	cout << endl ;
		}
		cout << "\n                          Escoja su opcion: ";
        opcion = getche();
        switch(opcion) {
                        case '1':
                            planeta.Getdata();
                            break;
                            
                        case '2':
                        	if (n==0)
                        		cout<<"\n\n            ERROR....! Se ha detectado que no hay registros, no hay informacion disponible para listar.\n";
                        	else
                            	planeta.Listar();
                            getch();
                            break;
                            
                        case '3':
                        	if (n!=0){
                        		planeta.Listar();
                        		cout<<"\n         Por Favor, seleccione un Planeta: " ; cin>>pos;
                        		if (pos>n)
                        			cout<<"\n                    Ha ingresado una Posicion NO VALIDA  ("<<pos<<")."<<endl;
                        		else{
                        			system("CLS");
                        			planeta.Mostrar(pos-1, false, false);
                        			system("pause");
								}
							}
                        	else
                        		cout<<"\n\n        ERROR; ALGO SALIO MAL....!"<<endl;
                            getch();
                            system("cls");
                            break;
                            
                        case '4':
                        	if (n!=0)
                            	planeta.Buscar();
                            else
                               cout<<"\n\n        ERROR; ALGO SALIO MAL....!"<<endl;
                            break;
                            
                        case '5':
                        	
                        	if (n!=0)
                        	{
                        		cout<<endl<<endl;
           		            	planeta.Listar();
           		            	cout<<"\n\n          Que Registro desea Modificar?: " ; cin>>pos;
           		            	if (pos-1>=n) {
           		       	        	cout<<"\n                    Ha ingresado una Posicion NO VALIDA  ("<<pos<<")."<<endl;
           		       	        	getch();
					        	}
                            	else
                                	planeta.Cambiar(pos-1);
                                system("cls");
							}
							else
								cout<<"\n\n        ERROR; ALGO SALIO MAL....!"<<endl;
                            break;
                            
                        case '6':
                        	if (n!=0) {
           		            	planeta.Listar();
           		            	cout<<"\n          ATENCION, ESTA POR ELIMINAR UN REGISTRO"<<endl;
							 	cout<<"         ------> ESTO NO PUEDE SER LUEGO DESHECHO<------"<<endl;
           		            	cout<<"\n            Que Registro desea ELIMINAR?: " ; cin>>pos;
           		            	if (pos>n) {
           		       	        	cout<<"\n                    Ha ingresado una Posicion NO VALIDA  ("<<pos<<")."<<endl;
					        	}
                            	else{
                            		system("CLS");
                            		planeta.Eliminar(pos-1);
								}
							}
                            else
                            	cout<<"\n\n        ERROR; ALGO SALIO MAL....!"<<endl;
                            getch();
                            system("cls");
                            break;
                            
                        case '7':
                        	if (n!=0) {
                        		planeta.OrdNombre();
                            	planeta.Listar();
							}
							else
								cout<<"\n\n        ERROR; ALGO SALIO MAL....!"<<endl;
                            getch();
                            system("cls");
                            break;
                            
                        case '0':
                        	cout<<"\n\n Esta seguro de salir S/N?:";
							resp=toupper(getch());
							if(resp=='S')
                            salir = true;
                            break;
                       }// switch
    } while (!salir);
    return 0;
} /* main */

