#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED

/// PROTOTIPOS FUNCIONES EXTERNAS
void Archivos();
void abml_productos(void);
void menu_productos(void);
int alta_producto(void);
void baja_prod();
void listar_prod(void);
void modificar_prod();
int buscarpos(int );
int CantidadRegistros();
int Cantidad_bajas();
void cod_disp();
///

class Productos {

    private:
        int cod,stock,talle;
        char modelo[30];
        char color[20];
        float precio;
        bool estado=false;
    public:
        ///METODOS DE CLASE
        void Mostrar(int p);
        void Cargar();
        int GrabarDisco();
        int LeerDisco(int);
        int ModificarDisco(int);
        ///SETS
        void setcod (int i){cod = i;};
        void setstock (int s){stock = s;};
        void settalle (int t){talle = t;};
        void setmodelo (char *m){strcpy(modelo,m);};
        void setcolor (char *c){strcpy(color,c);};
        void setprecio (float p){precio = p;};
        void setestado (bool e) {estado = e;};
        ///GETS
        int getcod(){return cod;};
        int getstock(){return stock;};
        int gettalle(){return talle;};
        char *getmodelo(){return modelo;};
        char *getcolor(){return color;};
        float getprecio(){return precio;};
        bool getestado(){return estado;};
};

void Productos::Cargar(){
    gotoxy(12,6);cin >> cod;
    while(buscarpos(cod)!=-1 || cod ==0){
            gotoxy(12,6);cout<<"                           ";
            gotoxy(4,20);cout << "CODIGO YA INGRESADO O INVALIDO, INGRESE UNO NUEVO ";
            gotoxy(12,6);cin >> cod;}
    gotoxy(4,20);cout <<"                                                 ";
    gotoxy(11,8);cin >> stock;
    while (stock <= 0){gotoxy(11,8);cout << "         ";gotoxy(11,8);cin >> stock;}
    gotoxy(11,10);cin >> talle;
    while (talle <= 0){gotoxy(11,10);cout << "         ";gotoxy(11,10);cin >> talle;}
    cin.ignore();
    gotoxy(12,12);cin.getline(modelo,30,'\n');
    gotoxy(11,14);cin.getline(color,20,'\n');
    gotoxy(12,16);cin >> precio;
    while (precio <= 0){gotoxy(12,16);cout << "         ";gotoxy(12,16);cin >> precio;}
    estado=true;
}

void Productos::Mostrar(int p){
        gotoxy(8,p); cout << cod;
        gotoxy(21,p); cout << talle;
        gotoxy(36,p); cout << stock;
        gotoxy(50,p); cout << modelo;
        gotoxy(69,p); cout << color;
        gotoxy(85,p); cout << precio;
}

int Productos::GrabarDisco(){
    FILE *p;
    int t;
	p=fopen("productos.dat","ab");
	if(p==NULL){cout<<"ERROR EN LA APERTURA DEL ARCHIVO";exit(1);}
	t = fwrite(this,sizeof *this,1,p);
	fclose(p);
	return t;
}

int Productos::LeerDisco(int pos){
    int a;
	FILE *p;
	p=fopen("productos.dat","rb");
	if(p==NULL){
		cout<<"ERROR AL ABRIR EL ARCHIVO"<<endl;
		system("pause");
		return 0;
		}
	fseek(p,pos*sizeof *this,0);
	a=fread(this,sizeof *this,1,p);
	fclose(p);
	return a;
}

int Productos::ModificarDisco(int pos){
	FILE *p;
	int x;
	p=fopen("productos.dat","rb+");
	if(p==NULL){cout<<"ERROR EN LA APERTURA DEL ARCHIVO";exit(1);}
	fseek(p,pos*sizeof (Productos),0);
    x = fwrite(this,sizeof (Productos),1,p);
	fclose(p);
	return x;
}

int Cantidad_bajas(){
    Productos obj;
    int pos=0,bajas=0;
    while (obj.LeerDisco(pos++)==1){
        if (obj.getestado() == false){
            bajas++;
        }
    }
    return bajas;
}

int CantidadRegistros(){
    Productos obj;
    int pos=0,c=0;
    while (obj.LeerDisco(pos++)==1){
        c++;
    }
    return c - Cantidad_bajas();
}


void menu_productos(){
int opc;
    cls();

    while(true) {
        cuadro(2,80,1,24);
        gotoxy(30,3);cout << "PRODUCTOS" << endl;
        gotoxy (4,6);cout << "1- CARGAR PRODUCTO " << endl;
        gotoxy (4,8);cout << "2- MOSTRAR PRODUCTOS " << endl;
        gotoxy (4,10);cout << "3- MODIFICAR PRODUCTO " << endl;
        gotoxy (4,12);cout << "4- ELIMINAR PRODUCTO " << endl;
        gotoxy (4,14);cout << "-------------------" << endl << endl;
        gotoxy (4,16);cout << "0. VOLVER AL MENU PRINCIPAL " << endl << endl;
        gotoxy (4,18);cout << "SELECCIONAR UNA OPCION: ";
        gotoxy (28,18);cin >> opc;
        cls();
        switch (opc){
            case 1:
                cuadro(2,80,1,24);
                gotoxy(30,3);cout << "NUEVO PRODUCTO" << endl;
                gotoxy(4,6);cout << "CODIGO: ";
                gotoxy(4,8);cout << "TALLE: ";
                gotoxy(4,10);cout << "STOCK: ";
                gotoxy(4,12);cout << "MODELO: ";
                gotoxy(4,14);cout << "COLOR: ";
                gotoxy(4,16);cout << "PRECIO: ";
                alta_producto();
            break;
            case 2:
                cuadro(2,92,1,24);
                gotoxy(6,3);cout << "CODIGO ";
                gotoxy(20,3);cout << "TALLE ";
                gotoxy(35,3);cout << "STOCK ";
                gotoxy(50,3);cout << "MODELO ";
                gotoxy(70,3);cout << "COLOR ";
                gotoxy(83,3);cout << "PRECIO ";
                gotoxy(4,23);cout << "CANTIDAD DE PRODUCTOS: ";
                listar_prod();
            break;
            case 3:
                cuadro(2,80,1,24);
                modificar_prod();
            break;
            case 4:
                cuadro(2,92,1,24);
                baja_prod();
            break;
            case 0: return;
            break;
            default:cout<<" OPCION INCORRECTA"<<endl;
            break;

        }
        gotoxy(3,27);
        system("pause");
        cls();
    }
}

int alta_producto(){
    int conf;
    gotoxy(4,22);cout << "1- CONFIRMAR / 2- CANCELAR / 3- REINTENTAR: ";
    Productos obj;
    obj.Cargar();
    gotoxy(48,22);cin >> conf;
    if (conf==1 && obj.GrabarDisco()==1){gotoxy(4,23);cout << "PRODUCTO GUARDADO";}
    if (conf==2){gotoxy(4,23);cout << "PRODUCTO CANCELADO";}
    if (conf==3){system("cls");cuadro(2,80,1,24);
                gotoxy(30,3);cout << "NUEVO PRODUCTO" << endl;
                gotoxy(4,6);cout << "CODIGO: ";
                gotoxy(4,8);cout << "TALLE: ";
                gotoxy(4,10);cout << "STOCK: ";
                gotoxy(4,12);cout << "MODELO: ";
                gotoxy(4,14);cout << "COLOR: ";
                gotoxy(4,16);cout << "PRECIO: ";alta_producto();}
    return 1;
}

void listar_prod(){
    Productos obj;
    int pos=0;
    int i=5;
    while (obj.LeerDisco(pos)==1){
        if (obj.getestado()==true){obj.Mostrar(i);i++;}
        pos++;
    }
    gotoxy(28,23);cout << i-5;
    if(pos==0){
        gotoxy(5,10);
		cout<<"NO SE ENCONTRARON REGISTROS DE PRODUCTOS"<<endl;
    }

}

void modificar_prod(){
    int opc,i,cod,pos;
    char c[20];
    char m[30];
    float p;
    cod_disp();
    Productos obj;
    gotoxy(30,3);cout << "MODIFICACION DE PRODUCTOS" << endl;
    gotoxy(4,6);cout << "CODIGO DE PRODUCTO A MODIFICAR: ";cin >> cod;
    pos = buscarpos(cod);
    while (pos==-1){
            gotoxy(4,10);cout << "EL PRODUCTO NO EXISTE, INGRESE UN CODIGO EXISTENTE / 0- VOLVER: ";
            gotoxy(68,10);cout << "           ";
            gotoxy(68,10);cin >> cod;
            pos=buscarpos(cod);
            if (cod==0){return;}
    }
    cls();
    cuadro(2,80,1,24);
    obj.LeerDisco(pos);
    gotoxy(20,3);cout << "MODIFICACION DE PRODUCTO / CODIGO "<< cod << endl;
    gotoxy(4,6);cout << "1. MODIFICAR CODIGO" << endl;
    gotoxy(4,8);cout << "2. MODIFICAR STOCK" << endl;
    gotoxy(4,10);cout << "3. MODIFICAR TALLE" << endl;
    gotoxy(4,12);cout << "4. MODIFICAR MODELO" << endl;
    gotoxy(4,14);cout << "5. MODIFICAR COLOR" << endl;
    gotoxy(4,16);cout << "6. MODIFICAR PRECIO" << endl;
    gotoxy(4,18);cout << "0. VOLVER" << endl;
    gotoxy(4,20);cout << "-------------------------" << endl;
    gotoxy(4,21);cout << "SELECCIONAR UNA OPCION: ";
    gotoxy(28,21);cin >> opc;
    switch (opc){
            case 1:
                gotoxy(4,22);cout << "NUEVO CODIGO: ";
                cin >> i;
                while(buscarpos(i)!=-1){gotoxy(4,23);cout << "CODIGO YA INGRESADO, INGRESE UNO NUEVO ";gotoxy(18,22);cin >> i;}
                obj.setcod(i);

            break;
            case 2:
                gotoxy(4,22);cout << "NUEVO STOCK: ";
                cin >> i;
                obj.setstock(i);
            break;
            case 3:
               gotoxy(4,22);cout << "NUEVO TALLE: ";
               cin >> i;
               obj.settalle(i);
            break;
            case 4:
                gotoxy(4,22);cout << "NUEVO MODELO: ";
                cin.ignore();
                cin.getline(m,30,'\n');
                obj.setmodelo(m);
            break;
            case 5:
                gotoxy(4,22);cout << "NUEVO COLOR: ";
                cin.ignore();
                cin.getline(c,20,'\n');
                obj.setcolor(c);
            break;
            case 6:
                gotoxy(4,22);cout << "NUEVO PRECIO: ";
                cin >> p;
                obj.setprecio(p);
            break;
            case 0:return;
            break;
            default:gotoxy(4,23);cout<<" OPCION INCORRECTA"<<endl;
            break;

        }

        cls();
        if (obj.ModificarDisco(pos)==1){
                cuadro(2,80,1,24);
                gotoxy(20,3);cout << "MODIFICACION DE PRODUCTO / CODIGO "<< cod;
                gotoxy(23,10);cout << "MODIFICADO CORRECTAMENTE ";}
    }

int buscarpos(int c){
    FILE *p;
    Productos obj;
    int pos=0;
    p= fopen("productos.dat","rb");

    if (p==NULL){cout << "ERROR AL ABRIR EL ARCHIVO";exit(1);}
    while (fread(&obj,sizeof (Productos),1, p)==1){
        if (c == obj.getcod() && obj.getestado()==true){
            return pos;
        }

        pos++;

    }
    return -1;
}

void cod_disp(){
    FILE *p;
    Productos obj;
    int pos=0,i=5;
    p= fopen("productos.dat","rb");
    if (p==NULL){cout << "ERROR AL ABRIR EL ARCHIVO";exit(1);}

    while (obj.LeerDisco(pos++)==1){
        if (obj.getestado()==true){
            gotoxy(90,3);cout << "CODIGOS DISPONIBLES";
            gotoxy(98,i);cout << obj.getcod();
            i++;
        }
    }
}

void baja_prod(){
    Productos obj;
	int pos,cod,x,conf;
    gotoxy(4,23);cout << "0 - VOLVER";
	gotoxy(30,3);cout << "ELIMINACION DE PRODUCTOS" << endl;
	gotoxy(4,5);cout<<"CODIGO DE PRODUCTO A ELIMINAR: ";
	cin>>cod;
	pos = buscarpos(cod);
    if (cod==0){return;}
	while (pos==-1 && cod!=0){
            gotoxy(4,7);
            cout << "CODIGO INEXISTENTE ";
            gotoxy(35,5);cout<<"             ";
            gotoxy(35,5);cin >> cod;
            pos = buscarpos(cod);}
    gotoxy(4,7);cout << "                                                        ";
    if (cod==0){return;}
    obj.LeerDisco(pos);
    gotoxy(6,8);cout << "CODIGO ";
    gotoxy(20,8);cout << "TALLE ";
    gotoxy(35,8);cout << "STOCK ";
    gotoxy(50,8);cout << "MODELO ";
    gotoxy(68,8);cout << "COLOR ";
    gotoxy(83,8);cout << "PRECIO ";
    obj.Mostrar(9);
    gotoxy(4,11);cout << "ELIMINAR ESTE PRODUCTO? 1-CONFIRMAR / 2-CANCELAR: ";cin>>conf;
    if (conf==1){
    obj.setestado(false);
    x = obj.ModificarDisco(pos);
    if (x==1){gotoxy(4,13);cout << "PRODUCTO ELIMINADO CORRECTAMENTE";}}
    else {return;}
}





#endif // PRODUCTOS_H_INCLUDED
