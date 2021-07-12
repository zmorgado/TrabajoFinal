#ifndef VENTAS_H_INCLUDED
#define VENTAS_H_INCLUDED

/// Prototipos funciones externas

void menu_ventas(void);
void alta_venta(void);
void baja_venta(void);
void listar_ventas(void);
void modificar_venta(int);
int buscar_venta(int);
int buscar_stock(int, int );
int validar_venta(int);
int CantRegistros(void);
int cantBajas();
int buscar_importe(int,int);
void restar_stock(int, int);
///

class Ventas {
	private:
        int idVenta,idProducto,cantidad,tp;
        Fecha fecha;
        float imp,des,rec;
        bool estado;
	public:
	    ///METODOS DE CLASE
		void Cargar();
		void Cargar_fecha();
		void Mostrar(int);
		int GrabarDisco(void);
		int LeerDisco(int);
		int ModificarDisco(int);
		///GETS
		int getidVenta(){return idVenta;};
		int getidProducto(){return idProducto;};
		int gettp(){return tp;};
		int getcantidad(){return cantidad;};
		bool getestado(){return estado;};
		///SETS
		void setidVenta(int v){idVenta=v;};
		void setidProducto(int p){idProducto=p;};
		void setcantidad(int c){cantidad=c;};
		void settp(int t){tp = t;};
		void setimporte(float i){imp = i;};
		void setestado(bool e){estado = e;};
		void setfecha(int c,int f){fecha.CargarFecha(c,f);}

};

void Ventas::Cargar(){
    idVenta = CantRegistros();
    gotoxy(13,6);cout << idVenta;
    gotoxy(24,8);cin >> idProducto;
    while (buscarpos(idProducto)==-1 || buscar_stock(cantidad, idProducto)==0){
        gotoxy(4,22);cout << "                                                       ";
        gotoxy(24,8);cout << "                                                     ";
        gotoxy(4,23); cout << "PRODUCTO INEXISTENTE O SIN STOCK";gotoxy(24,8);

        cin >> idProducto;}
    gotoxy(4,23);cout << "                                                     ";
    gotoxy(14,10);cin >> cantidad;
    while (buscar_stock(cantidad,idProducto)==-1){
        gotoxy(14,10);cout << "                                                     ";
        gotoxy(4,24);cout << "NO HAY STOCK SUFICIENTE";
        gotoxy(14,10); cin >> cantidad;}
    gotoxy(4,24);cout << "                                                     ";
    fecha.CargarFecha(13,12);
    gotoxy(44,14);cin >> tp;
    while (tp<1 || tp >3){
        gotoxy(44,14);cout<<"                       ";
        gotoxy(44,14);cin>>tp;}
    gotoxy(13,16);imp = buscar_importe(idProducto,cantidad);cout << imp;
    gotoxy(15,18);cin >> des;
    gotoxy(13,20);cin >> rec;
    imp -= imp * (des/100);
    imp += imp * (rec/100);
    estado=true;
}


void Ventas::Mostrar(int p){
    if (estado==true){
        gotoxy(4,p); cout <<idVenta;
        gotoxy(15,p); cout << idProducto;
        gotoxy(30,p); cout << cantidad;
        gotoxy(40,p); fecha.MostrarFecha();
        gotoxy(55,p); cout << tp;
        gotoxy(65,p); cout << "$" << imp;
        gotoxy(77,p); cout << des << "%";
        gotoxy(85,p); cout << rec << "%";
    }
}

int Ventas::GrabarDisco(){
	FILE *p;
	bool t;
	p=fopen("ventas.dat","ab");
	if(p==NULL){cout<<"ERROR EN LA APERTURA DEL ARCHIVO";exit(1);};
	t = fwrite(this,sizeof *this,1,p);
	fclose(p);
	return t;
}

int Ventas::LeerDisco(int pos){
	int x;
	FILE *p;
	p=fopen("ventas.dat","rb");
	if(p==NULL){cout<<"ERROR EN LA APERTURA DEL ARCHIVO";exit(1);};
	fseek(p,pos*sizeof *this,0);
	x=fread(this,sizeof *this,1,p);
	fclose(p);
	return x;
}

int Ventas::ModificarDisco(int pos){
	FILE *p;
	int x;
	p=fopen("ventas.dat","rb+");
	if(p==NULL){cout<<"ERROR EN LA APERTURA DEL ARCHIVO";exit(1);};
	fseek(p,pos*sizeof (Ventas),0);
    x = fwrite(this,sizeof (Ventas),1,p);
	fclose(p);
	return x;
}

int cantBajas(){
    Ventas obj;
    int pos=0,bajas=0;
    while (obj.LeerDisco(pos++)==1){
        if (obj.getestado() == false){
            bajas++;
        }
    }
    return bajas;
}

int CantRegistros(){
    Ventas obj;
    int pos=0,c=1;
    while (obj.LeerDisco(pos++)==1){
        c++;
    }
    return c - cantBajas();
}

void menu_ventas(){
int opc,id;
    cls();
    while(true){
        cuadro(2,80,1,24);
        gotoxy(30,3);cout << "VENTAS" << endl;
        gotoxy (4,6);cout << "1- CARGAR VENTA " << endl;
        gotoxy (4,8);cout << "2- MOSTRAR VENTAS " << endl;
        gotoxy (4,10);cout << "3- MODIFICAR VENTA " << endl;
        gotoxy (4,12);cout << "4- BUSCAR VENTA" << endl;
        gotoxy (4,14);cout << "-------------------" << endl << endl;
        gotoxy (4,16);cout << "0. VOLVER AL MENU PRINCIPAL " << endl << endl;
        gotoxy (4,18);cout << "SELECCIONAR UNA OPCION: ";
        gotoxy (28,18);cin >> opc;
        cls();
        switch (opc){
            case 1:
                cuadro(2,80,1,26);
                gotoxy(30,3);cout << "NUEVA VENTA";
                gotoxy(4,6);cout << "ID VENTA: ";
                gotoxy(4,8);cout << "CODIGO DE PRODUCTO: ";
                gotoxy(4,10);cout << "CANTIDAD: ";
                gotoxy(4,12);cout << "FECHA: " ;
                gotoxy(4,14);cout << "TIPO DE PAGO 1.EFECTIVO/2.TARJETA/3.MP: ";
                gotoxy(4,16);cout << "IMPORTE: ";
                gotoxy(4,18);cout << "DESCUENTO: ";gotoxy(17,18);cout<<"%";
                gotoxy(4,20);cout << "RECARGO: ";gotoxy(15,20);cout<<"%";
                alta_venta();
            break;
            case 2:
                cuadro(2,95,1,26);
                gotoxy(4,3);cout << "NUM VENTA ";
                gotoxy(15,3);cout << "COD PRODUCTO ";
                gotoxy(30,3);cout << "CANTIDAD " ;
                gotoxy(42,3);cout << "FECHA " ;
                gotoxy(50,3);cout << "TIPO DE PAGO";
                gotoxy(64,3);cout << "IMPORTE ";
                gotoxy(73,3);cout << "DESCUENTO ";
                gotoxy(83,3);cout << "RECARGO ";
                listar_ventas();
            break;
            case 3:
                cuadro(2,95,1,26);
                gotoxy(30,3);cout << "MODIFICACION DE VENTAS" << endl;
                gotoxy(4,25);cout << "0 -VOLVER";
                gotoxy(4,6);cout << "ID DE VENTA A MODIFICAR: "; cin >> id;
                while (validar_venta(id)==-1 && id!=0){
                        gotoxy(29,6);cout<<"                  ";
                        gotoxy(4,22);cout << "EL ID NO EXISTE, INGRESE OTRO";
                        gotoxy(29,6);cin >> id;}
                if (id!=0){modificar_venta(id);}

            break;
            case 4:
                cuadro(2,95,1,26);
                gotoxy(6,6);cout << "ID DE VENTA A BUSCAR: ";
                cin >> id;
                if (buscar_venta(id)==1){
                gotoxy(4,8);cout << "NUM VENTA ";
                gotoxy(15,8);cout << "COD PRODUCTO ";
                gotoxy(30,8);cout << "CANTIDAD " ;
                gotoxy(42,8);cout << "FECHA " ;
                gotoxy(50,8);cout << "TIPO DE PAGO";
                gotoxy(64,8);cout << "IMPORTE ";
                gotoxy(73,8);cout << "DESCUENTO ";
                gotoxy(83,8);cout << "RECARGO ";
                }
            break;
            case 0:return;
            break;
            default:cout<<" OPCION INCORRECTA"<<endl;
            break;

        }
        gotoxy(4,25);
        system("pause");
        cls();
    }
}
void alta_venta(){
    int conf;
	Ventas obj;
	gotoxy(4,22);cout << "1- CONFIRMAR / 2- CANCELAR / 3- REINTENTAR: ";
	cod_disp();
    obj.Cargar();
    gotoxy(48,22);cin >> conf;
    if (conf==1 && obj.GrabarDisco()==1){restar_stock(obj.getidProducto(), obj.getcantidad());
    gotoxy(30,24);cout << "VENTA GUARDADA";}
    if (conf==2){gotoxy(4,24);cout << "VENTA CANCELADA";}
    if (conf==3){system("cls"); cuadro(2,80,1,26);
                gotoxy(30,3);cout << "NUEVA VENTA";
                gotoxy(4,6);cout << "ID VENTA: ";
                gotoxy(4,8);cout << "CODIGO DE PRODUCTO: ";
                gotoxy(4,10);cout << "CANTIDAD: ";
                gotoxy(4,12);cout << "FECHA: " ;
                gotoxy(4,14);cout << "TIPO DE PAGO 1.EFECTIVO/2.TARJETA/3.MP: ";
                gotoxy(4,16);cout << "IMPORTE: ";
                gotoxy(4,18);cout << "DESCUENTO: ";gotoxy(17,18);cout<<"%";
                gotoxy(4,20);cout << "RECARGO: ";gotoxy(15,20);cout<<"%";
                alta_venta();}
}

void listar_ventas(){
	Ventas obj;
	int pos=0;
	int i=5;
	while(obj.LeerDisco(pos++)==1){
		obj.Mostrar(i);
		if (obj.getestado()==true){i++;}
    }
    if(pos==1){
        gotoxy(4,10);
		cout<<"NO SE ENCONTRARON REGISTROS DE VENTAS"<<endl;
    }
}

int buscar_stock(int cant, int cod){
	Productos reg;
	int pos=0;
	while(reg.LeerDisco(pos++)){
        if (reg.getcod() == cod){
            if (reg.getstock()==0){return 0;}
            if (cant>reg.getstock()){return -1;}
            else {return 1;}
        }
	}
    return -1;
}

void modificar_venta(int id){
    cls();
    int opc,i,x=0, j,t=0;
    float im;
    Ventas obj;
    obj.LeerDisco(id-1);
    cuadro(2,95,1,24);
    gotoxy(30,3);cout << "MODIFICACION DE VENTAS" << endl;
    gotoxy(4,6);cout << "1. MODIFICAR CANTIDAD" << endl;
    gotoxy(4,8);cout << "2. MODIFICAR FECHA" << endl;
    gotoxy(4,10);cout << "3. MODIFICAR TIPO DE PAGO" << endl;
    gotoxy(4,12);cout << "4. MODIFICAR IMPORTE" << endl;
    gotoxy(4,14);cout << "-------------------------" << endl;
    gotoxy(4,16);cout << "SELECCIONAR UNA OPCION: ";
    gotoxy(4,23);cout << "0 - VOLVER";
    gotoxy(28,16);cin >> opc;
    switch (opc){
            case 1:
                gotoxy(4,18);cout << "NUEVA CANTIDAD: ";
                x=obj.getcantidad();
                cin >> i;
                while (buscar_stock(i,obj.getidProducto())==-1){gotoxy(4,20);cout << "NO HAY STOCK SUFICIENTE";gotoxy(4,18); cin >> i;}
                if (i>x){x = i - x;}
                else {t = x;x = x - i;x = t + x;}
                j=obj.getidProducto();
                restar_stock(j,x);
                obj.setcantidad(i);
            break;
            case 2:
                obj.setfecha(4,18);
            break;
            case 3:
                gotoxy(4,18);cout << "NUEVO TIPO DE PAGO 1.EFECTIVO/2.TARJETA/3.MP: ";
                cin >> i;
                obj.settp(i);
            break;
            case 4:
                gotoxy(4,18);cout << "NUEVO IMPORTE: ";
                cin >> im;
                obj.setimporte(im);
            break;
            case 0:return;
            break;
            default:cout<<" OPCION INCORRECTA"<<endl;
            break;

        }
        cls();
        if (obj.ModificarDisco(id-1)==1){gotoxy(4,10);cout << "VENTA MODIFICADA CORRECTAMENTE ";}
    }


int buscar_venta(int id){
	int pos=0;
	Ventas obj;
	while(obj.LeerDisco(pos)==1){
		if(id==obj.getidVenta()){
			obj.Mostrar(10);
			return 1;
		}
		pos++;
	}
    gotoxy(4,20); cout << "LA VENTA NO EXISTE" << endl;
	return -1;
}

int validar_venta(int id){
	int pos=0;
	Ventas obj;
	while(obj.LeerDisco(pos)==1){
		if(id==obj.getidVenta()){
			return 1;
		}
		pos++;
	}
	return -1;
}

int buscar_importe(int id, int cant){
    Productos obj;
    int pos;
    pos = buscarpos(id);
    obj.LeerDisco(pos);
    return obj.getprecio() * cant;
}

void restar_stock(int id, int cantidad){
    Productos obj;
    int pos;
    pos = buscarpos(id);
    obj.LeerDisco(pos);
    obj.setstock(obj.getstock()-cantidad);
    obj.ModificarDisco(pos);
}



#endif // VENTAS_H_INCLUDED
