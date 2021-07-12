#include <iostream>
#include "rlutil.h"
#include <locale.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <conio.h>
#include <string.h>
#include <dos.h>
#include <windows.h>
#include <ctime>

/// TOMO: 600 FOLIO: 3564 NOTA: 8

/// SISTEMA DE GESTION DE ARCHIVOS PARA "ONTHEROAD"

/// ARCHIVOS:  Productos - Ventas - Proveedores - Pagos

/// CLASES:

    /// Productos (modelo, precio, color, stock, talle) (abml)
	/// Ventas (nº venta, fecha, tipo de pago, descuento, recargo) (abml)
	/// Proveedores (cuit, dirección, razón social) (abml, pagos)
	/// Pagos (cuit, tp, importe, fecha)

using namespace std;
using namespace rlutil;
void cuadro(int,int,int,int);
void Archivos();
#include "productos.h"
#include "proveedores.h"
#include "ventas.h"





int main() {
        int opc;
        Archivos();
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,WHITE);
        setBackgroundColor(BLUE);
        while(true){
        cls();
        cuadro(2,80,1,24);
        gotoxy(30,3); cout << "MENU PRINCIPAL" << endl;
        gotoxy (4,6); cout << "1. PRODUCTOS " << endl;
        gotoxy (4,8);cout << "2. VENTAS " << endl;
        gotoxy (4,10);cout << "3. PROVEEDORES " << endl;
        gotoxy (4,12);cout << "--------------" << endl << endl;
        gotoxy (4,14);cout << "0. SALIR DEL PROGRAMA " << endl << endl;
        gotoxy (4,16);cout << "SELECCIONAR UNA OPCION: ";
        gotoxy (28,16);cin >> opc;
        switch(opc){
            case 1:
                menu_productos();
            break;
            case 2:
                menu_ventas();
            break;
            case 3:
                menu_proveedores();
            break;
            case 0:
            gotoxy(6,25);return 0;
            break;
            default:cout<<" OPCION INCORRECTA"<<endl;
            break;
        }

    }

gotoxy(6,25);return 0;

}

void Archivos(){
	FILE *p;
	p=fopen("productos.dat","rb");
	if(p==NULL)
		p=fopen("productos.dat","wb");
	fclose(p);


	p=fopen("ventas.dat","rb");
	if(p==NULL)
		p=fopen("ventas.dat","wb");
	fclose(p);

	p=fopen("proveedores.dat","rb");
	if(p==NULL)
		p=fopen("proveedores.dat","wb");
	fclose(p);

	p=fopen("pagos.dat","rb");
	if(p==NULL)
		p=fopen("pagos.dat","wb");
	fclose(p);
}


void cuadro(int ci, int cf, int fi, int ff){
    int o;
    for(o=ci; o<=cf; o++){
    gotoxy(o,fi); cout<<"*";
    gotoxy(o,ff); cout<<"*";
    }

    for(o=fi; o<=ff; o++){
    gotoxy(ci,o);cout<<"*";
    gotoxy(cf,o);cout<<"*";
    }

gotoxy(ci,fi); cout<<"*";
gotoxy(cf,fi); cout<<"*";
gotoxy(ci,ff); cout<<"*";
gotoxy(cf,ff); cout<<"*";
}

