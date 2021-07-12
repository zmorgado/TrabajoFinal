#ifndef PROVEEDORES_H_INCLUDED
#define PROVEEDORES_H_INCLUDED

///PROTOTIPOS FUNCIONES EXTERNAS
void alta_pago();
void alta_proveedor();
int BajaProveedor();
void baja();
void listar_proveedores();
void listar_pagos();
int buscarposchar(char *);
int buscar_prov(char *);
int Cantidad_Registros(void);
int cantidad_bajas();
void prov_disp();
///



class Fecha {
    private:
        int dia, mes, anio;
    public:
        void CargarFecha(int, int);
        void MostrarFecha();
};

void Fecha::CargarFecha(int c, int f){
    time_t tiempo;
    struct tm *tmPtr;
    tiempo = time(NULL);
    tmPtr = localtime(&tiempo);
    gotoxy(c,f);cout << "DIA: ";
    gotoxy(c+6,f);cin >> dia;
    if (dia<1 || dia >31){dia=tmPtr->tm_mday;}
    gotoxy(c+9,f);cout << "MES: ";
    gotoxy(c+14,f);cin >> mes;
    if (mes<1 || mes >12){mes=tmPtr->tm_mon+1;}
    gotoxy(c+17,f);cout << "ANIO: ";
    gotoxy(c+23,f);cin >> anio;
    if (anio<2020 || anio > 2021){anio=tmPtr->tm_year+1900;}
    ///SI HAY UN INGRESO INVALIDO SE TOMA LA FECHA ACTUAL
}

void Fecha::MostrarFecha(){
    cout  << dia << "/" << mes << "/" <<  anio << endl;
}

class Pagos {

    private:
            Fecha fecha;
            char cuit [20];
            int tp, numProv;
            float importe;
    public:
        ///METODOS
            void CargarPago();
            void MostrarPagos(int );
            int LeerPagoDisco(int );
            int GrabarPagoDisco();
        ///GETS
            Fecha getfecha(){return fecha;};
            float getimporte(){return importe;}
            float gettp(){return tp;}
            float getnumProv(){return numProv;}
        ///SETS
            void settp(int t){tp=t;}
            void setnumProv(int n){numProv=n;}
            void setimporte(float i){importe=i;}

};

class Proveedores {

    private:
            char cuit[20];
            char direccion[50];
            char rs[50];
            char tel[15];
            bool estado;
    public:
        ///METODOS
            void Cargar();
            void Mostrar(int);
            int GrabarDisco(void);
            int LeerDisco(int);
            int ModificarDisco(int);
        ///GETS
            char *getcuit(){return cuit;};
            bool getestado(){return estado;};
        ///SETS
            void setestado(bool e){estado = e;};
};

void Proveedores::Cargar(){
    gotoxy(10,6);cin >> cuit;
    cin.ignore();
    gotoxy(15,8);cin.getline(direccion,50,'\n');
    gotoxy(18,10);cin.getline(rs,50,'\n');
    gotoxy(14,12);cin >> tel;
    estado=1;
}

void Pagos::CargarPago(){
    gotoxy(23,6);cin >> cuit;
    while (buscar_prov(cuit)==-1){
            gotoxy(23,6);cout << "                      ";
            gotoxy(4,23);cout << "EL NUMERO DE CUIT DEBE PERTENECER A UN PROVEEDOR YA INGRESADO" << endl;
            gotoxy(23,6);cin >> cuit;}
    gotoxy(4,23);cout << "                                                                  ";
    gotoxy(13,8);cin >> importe;
    while (importe <= 0){gotoxy(13,8);cout << "         ";gotoxy(13,8);cin >> importe;}
    gotoxy(44,10);cin >> tp;
    while (tp<1 || tp >3){gotoxy(44,10);cout << "         ";gotoxy(44,10);cin>>tp;}
    gotoxy(12,12);fecha.CargarFecha(12,12);

}


void Proveedores::Mostrar(int p){
        gotoxy(4,p); cout << cuit;
        gotoxy(25,p); cout << direccion;
        gotoxy(45,p); cout << rs;
        gotoxy(65,p); cout << tel;

}

void Pagos::MostrarPagos(int p){
        gotoxy(4,p); cout << cuit;
        gotoxy(25,p); cout << importe;
        gotoxy(38,p); fecha.MostrarFecha();
        gotoxy(55,p); cout << tp;
}

int Proveedores::GrabarDisco(){
	FILE *p;
	int x;
	p=fopen("proveedores.dat","ab");
	if(p==NULL){cout<<"ERROR EN LA APERTURA DEL ARCHIVO";exit(1);};
	x = fwrite(this,sizeof (Proveedores),1,p);
	fclose(p);
	return x;
}
int Pagos::GrabarPagoDisco(){
	FILE *p;
	int x;
	p=fopen("pagos.dat","ab");
	if(p==NULL){cout<<"ERROR EN LA APERTURA DEL ARCHIVO";exit(1);};
	x = fwrite(this,sizeof (Pagos),1,p);
	fclose(p);
	return x;
}
int Pagos::LeerPagoDisco(int pos){
	int x;
	FILE *p;
	p=fopen("pagos.dat","rb");
	if(p==NULL){cout<<"ERROR EN LA APERTURA DEL ARCHIVO";exit(1);};
	fseek(p,pos*sizeof (Pagos),0);
	x=fread(this,sizeof (Pagos),1,p);
	fclose(p);
	return x;
}

int Proveedores::LeerDisco(int pos){
	int x;
	FILE *p;
	p=fopen("proveedores.dat","rb");
	if(p==NULL){cout<<"ERROR EN LA APERTURA DEL ARCHIVO";exit(1);};
	fseek(p,pos*sizeof (Proveedores),0);
	x=fread(this,sizeof (Proveedores),1,p);
	fclose(p);
	return x;
}


int Proveedores::ModificarDisco(int pos){
	FILE *p;
	int x;
	p=fopen("proveedores.dat","rb+");
	if(p==NULL){cout<<"ERROR EN LA APERTURA DEL ARCHIVO";exit(1);};
	fseek(p,pos*sizeof *this,0);
	x = fwrite(this,sizeof (Proveedores),1,p);
	fclose(p);
	return x;
	}

int cantidad_bajas(){
    Proveedores obj;
    int pos=0,bajas=0;
    while (obj.LeerDisco(pos++)==1){
        if (obj.getestado() == false){
            bajas++;
        }
    }
    return bajas;
}

int Cantidad_Registros(){
    Proveedores obj;
    int pos=0,c=0;
    while (obj.LeerDisco(pos++)==1){
        c++;
    }
    return c - cantidad_bajas();
}


void menu_proveedores(){
int opc;
    cls();
    while(true){
        cuadro(2,80,1,24);
        gotoxy(30,3);cout << "PROVEEDORES" << endl;
        gotoxy (4,6);cout << "1- NUEVO PROVEEDOR " << endl;
        gotoxy (4,8);cout << "2- LISTAR PROVEEDORES " << endl;
        gotoxy (4,10);cout << "3- ELIMINAR PROVEEDOR " << endl;
        gotoxy (4,12);cout << "4- PAGO A PROVEEDOR " << endl;
        gotoxy (4,14);cout << "5- LISTAR PAGOS " << endl;
        gotoxy (4,16);cout << "-------------------" << endl << endl;
        gotoxy (4,18);cout << "0. VOLVER AL MENU PRINCIPAL " << endl << endl;
        gotoxy (4,20);cout << "SELECCIONAR UNA OPCION: ";
        gotoxy (28,20);cin >> opc;
        cls();
        switch (opc){
            case 1:
                cuadro(2,80,1,24);
                gotoxy(30,3);cout << "NUEVO PROVEEDOR" << endl;
                gotoxy(4,6);cout << "CUIT: ";
                gotoxy(4,8);cout << "DIRECCION: ";
                gotoxy(4,10);cout << "RAZON SOCIAL: ";
                gotoxy(4,12);cout << "TELEFONO: ";
                alta_proveedor();
            break;
            case 2:
                cuadro(2,80,1,24);
                gotoxy(4,3);cout << "CUIT ";
                gotoxy(25,3);cout << "DIRECCION";
                gotoxy(45,3);cout << "RAZON SOCIAL ";
                gotoxy(65,3);cout << "TELEFONO ";
                listar_proveedores();
            break;
            case 3:
                cuadro(2,80,1,24);
                baja();
            break;
            case 4:
                cuadro(2,80,1,24);
                gotoxy(30,3);cout << "NUEVO PAGO" << endl;
                gotoxy(4,6);cout << "CUIT DE PROVEEDOR: ";
                gotoxy(4,8);cout << "IMPORTE: ";
                gotoxy(4,10);cout << "TIPO DE PAGO 1.EFECTIVO/2.TARJETA/3.MP: ";
                gotoxy(4,12);cout << "FECHA: ";
                alta_pago();
            break;
            case 5:
                cuadro(2,65,1,24);
                gotoxy(4,3);cout << "CUIT DE PROVEEDOR ";
                gotoxy(25,3);cout << "IMPORTE ";
                gotoxy(40,3);cout << "FECHA ";
                gotoxy(50,3);cout << "TIPO DE PAGO ";
                listar_pagos();
            break;
            case 0:return;
            break;
            default:
                system("pause");
                cls();
                cout<<" OPCION INCORRECTA"<<endl;
                return;
            break;

        }
        gotoxy(4,25);
        system("pause");
        cls();
    }
}
void alta_proveedor(){
	Proveedores obj;
	int conf;
	gotoxy(4,22);cout << "1- CONFIRMAR / 2- CANCELAR / 3- REINTENTAR: ";
    obj.Cargar();
    gotoxy(48,22);cin >> conf;
    if (conf==1 && obj.GrabarDisco()==1){gotoxy(30,23);cout << "PROVEEDOR GUARDADO";}
    if (conf==2){gotoxy(30,23);cout << "PROVEEDOR CANCELADO";}
    if (conf==3){system("cls");cuadro(2,80,1,24);
                gotoxy(30,3);cout << "NUEVO PROVEEDOR" << endl;
                gotoxy(4,6);cout << "CUIT: ";
                gotoxy(4,8);cout << "DIRECCION: ";
                gotoxy(4,10);cout << "RAZON SOCIAL: ";
                gotoxy(4,12);cout << "TELEFONO: ";
                alta_proveedor();}
}


int BajaProveedor(){
    Proveedores obj;
	int pos,x,conf;
	char cuit[20];
	gotoxy(30,3);cout << "ELIMINACION DE PROVEEDOR" << endl;
	gotoxy(4,5);cout<<"CUIT DE PROVEEDOR A ELIMINAR: ";
	cin>>cuit;
	while (buscar_prov(cuit)==-1){
            gotoxy(34,5);cout << "                           ";
            gotoxy(4,7);
            cout << "CUIT INEXISTENTE, INGRESE OTRO ";
            gotoxy(34,5);cin>>cuit;}
    gotoxy(4,7);cout << "                                   ";
	pos = buscarposchar(cuit);
    obj.LeerDisco(pos);
    gotoxy(6,8);cout << "CUIT ";
    gotoxy(25,8);cout << "DIRECCION";
    gotoxy(45,8);cout << "RAZON SOCIAL ";
    gotoxy(65,8);cout << "TELEFONO ";
    obj.Mostrar(9);
    gotoxy(4,11);cout << "ELIMINAR ESTE PROVEEDOR? 1-CONFIRMAR / 2-CANCELAR: ";cin>>conf;
    if (conf==1){obj.setestado(false);
    x = obj.ModificarDisco(pos);}
    return x;
}

void alta_pago(){
    Pagos obj;
    int conf;
    prov_disp();
    gotoxy(4,22);cout << "1- CONFIRMAR / 2- CANCELAR / 3- REINTENTAR: ";
    obj.CargarPago();
    gotoxy(48,22);cin >> conf;
    if (conf==1 && obj.GrabarPagoDisco()==1){gotoxy(30,17);cout << "PAGO GUARDADO";}
    if (conf==2){gotoxy(30,17);cout << "PAGO CANCELADO";}
    if (conf==3){system("cls");cuadro(2,80,1,24);
                gotoxy(30,3);cout << "NUEVO PAGO" << endl;
                gotoxy(4,6);cout << "CUIT DE PROVEEDOR: ";
                gotoxy(4,8);cout << "IMPORTE: ";
                gotoxy(4,10);cout << "TIPO DE PAGO 1.EFECTIVO/2.TARJETA/3.MP: ";
                gotoxy(4,12);cout << "FECHA: ";
                alta_pago();}
}

void baja(){
    int x;
    prov_disp();
    x = BajaProveedor();
    if (x==1){gotoxy(4,18);cout << "PROVEEDOR ELIMINADO CORRECTAMENTE";}
    }

void listar_proveedores(){
    Proveedores obj;
	int pos=0,c=0;
	int i=5;
	while(obj.LeerDisco(pos++)==1){
		if (obj.getestado()==true){obj.Mostrar(i);i++;}
        c++;
    }
    if (c==0){
        gotoxy(4,10);
        cout << "NO SE ENCONTRARON PROVEEDORES" << endl;
    }
}
void listar_pagos(){
    Pagos obj;
	int pos=0,i=5;
	while(obj.LeerPagoDisco(pos++)==1){
		obj.MostrarPagos(i);
		i++;
    }
    if(pos==1){
        gotoxy(4,7);
		cout<<"NO SE ENCONTRARON REGISTROS DE PAGOS"<<endl;
    }
}

int buscar_prov(char * prov){
    FILE *p;
    Proveedores obj;
    int pos=0;
    p= fopen("proveedores.dat","rb");
    if (p==NULL){cout << "ERROR AL ABRIR EL ARCHIVO";exit(1);}
    while (fread(&obj,sizeof (Proveedores),1, p)==1){
        if (strcmp(prov,obj.getcuit())==0 && obj.getestado()==true){
            return pos;
        }
        pos++;
    }
    return -1;
}

int buscarposchar(char *c){
    FILE *p;
    Proveedores obj;
    int pos=0,x=0;
    p = fopen("proveedores.dat","rb");
    if (p==NULL){cout << "ERROR AL ABRIR EL ARCHIVO";exit(1);}
    while (obj.LeerDisco(pos++)==1){
        if (strcmp(c,obj.getcuit())==0){
            return x;
        }
        x++;
    }
    cout << "NO SE ENCONTRO EL CUIT A ELIMINAR" << endl;
}

void prov_disp(){

    FILE *p;
    Proveedores obj;
    int pos=0,i=5;
    p= fopen("proveedores.dat","rb");
    if (p==NULL){cout << "ERROR AL ABRIR EL ARCHIVO";exit(1);}

    while (obj.LeerDisco(pos++)==1){
        if (obj.getestado()==true){
            gotoxy(90,3);cout << "CUITS DISPONIBLES";
            gotoxy(93,i);cout << obj.getcuit();
            i++;
        }
    }
}


#endif // PROVEEDORES_H_INCLUDED
