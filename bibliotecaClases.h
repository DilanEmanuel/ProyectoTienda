#include <stdlib.h>
#include <iostream>
#include <clocale> //Para acentos y �

using namespace std;

//Clase que sirve para mostrar los men�s del programa, as� como recabar algunas opciones que seleccione el usuario
class Menu{
	private:
		int opcion;
	public:
		Menu();
		~Menu();
		void setOpcion(int);
		int getOpcion();
		void mostrarEntrada();
		void mostrarMenuPrincipal();
		void menuProductosHeader();
		int menuProductosOpcion();
		int menuCantidadProductos();
		void menuCarritoHeader();
};

//Clase que sirve para almacenar los datos de los 25 productos a seleccionar y mostrar el cat�logo
class Producto{
	private:
		string nombre;
		string descripcion;
		int precioUnit;
	public:
		Producto();
		Producto(string, string, int);
		void mostrarProducto();
		string getNombre();
		int getPrecioUnit();
};

//Clase que sirve para almacenar en el carrito los productos elegidos, hereda de la clase Producto
class ProductoElegido : public Producto{
	private:
		int cantidad;
		int totalPorProducto;
	public:
		ProductoElegido();
		ProductoElegido(string, string, int, int, int);
		int getCantidad();
		void setCantidad(int);
		int getTotalPorProducto();
		void setTotalPorProducto(int);
		void mostrarProductoElegido();
};

//Definimos nodo para lista anidada para Carrito, almacena como dato los productos elegidos
struct Nodo{
	Nodo *siguiente;
	ProductoElegido dato;
};

//Clase que sirve para llevar el control de los productos elegidos, el total y los art�culos elegidos
//Tiene como atributo una lista de ProductoElegido, implementada utilizando apuntadores
class Carrito{
	private:
		Nodo *lista; //List<ProductoElegido>
		int total;
		int numArticulos;
	public:
		Carrito(int, int);
		int getTotal();
		void setTotal(int);
		int getNumArticulos();
		void setNumArticulos(int);
		void agregarLista(ProductoElegido);
		void listarCarrito();
		void terminarCompra();
};

//Cabecera de funciones de nodo, sirven para que el programa reconoza que las funciones existen
void insertarLista(Nodo *&, ProductoElegido);
void mostrarLista(Nodo *);
void eliminarPrimerNodo(Nodo *&);

//M�todos constructores
Menu::Menu(){
}

Producto::Producto(string _nombre, string _descripcion, int _precioUnit){
	nombre = _nombre;
	descripcion = _descripcion;
	precioUnit = _precioUnit;
}

//Sobrecarga de constructor para Producto, �til para crear la lista de Productos elegidos
Producto::Producto(){
}

ProductoElegido::ProductoElegido(){
}

ProductoElegido::ProductoElegido(string _nombre, string _descripcion, int _precioUnit, int _cantidad, int _totalPorProducto) : Producto(_nombre, _descripcion, _precioUnit){
	cantidad = _cantidad;
	totalPorProducto = _totalPorProducto;
}

Carrito::Carrito(int _total, int _numArticulos){
	lista = NULL;
	total = _total;
	numArticulos = _numArticulos;
}

//M�todos destructores
Menu::~Menu(){
}

//...

//M�todo set para definir la opci�n elegida por el usuario
void Menu::setOpcion(int _opcion){
	opcion = _opcion;
}

//M�todo get para obtener la opci�n elegida por el usuario
int Menu::getOpcion(){
	return opcion;
}

//M�todo para mostrar el encabezado del programa
void Menu::mostrarEntrada(){
	cout << "shoppingMe.com" << endl << "=================" << endl;
	cout << "Nombre y Matr�cula / Nombre y Matr�cula" << endl << endl;
}

//M�todo para mostrar el men� principal del usuario
void Menu::mostrarMenuPrincipal(){
	cout << "*** MENU PRINCIPAL ***" << endl << endl;
	cout << "1) Seleccionar productos" << endl;
	cout << "2) Ver carrito de compras" << endl;
	cout << "3) Terminar compra" << endl;
	cout << "4) Salir" << endl << endl;
	cout << "Selecciona opci�n: ";
	int aux;
	cin >> aux;
	setOpcion(aux);
}

//M�todo para mostrar el encabezado del men� de productos a comprar
void Menu::menuProductosHeader(){
	cout << endl << "***SELECCIONAR PRODUCTO***" << endl << endl;
	cout << "Producto\tDescripci�n\tPrecio unitario" << endl;
	cout << "__________________________________________________" << endl;
}

//M�todo para preguntar al usuario qu� producto desea comprar
int Menu::menuProductosOpcion(){
	cout << endl << "�Qu� productos deseas comprar? (-1 para cancelar): ";
	int aux;
	cin >> aux;
	return aux;
}

//M�todo para preguntar al usuario cu�ntos productos desea comprar, verificando si el n�mero es v�lido
int Menu::menuCantidadProductos(){
	cout << endl << "�Cu�ntos productos deseas comprar? (-1 para cancelar): ";
	int aux;
	cin >> aux;
	//Si elige un n�mero de productos mayor a 0, regresa el n�mero de productos
	if(aux > 0){
		return aux;
	}
	//Si elige un n�mero menor a -1 o 0
	else if(aux < -1 || aux == 0){
		cout << "Opci�n inv�lida, regresando al men�..." << endl << endl;
	}
	//Si elige la opci�n -1 (regresar al men�)
	return -1;
}

//M�todo para mostrar el encabezado del men� del carrito de compras
void Menu::menuCarritoHeader(){
	cout << endl << "***CARRITO DE COMPRAS***" << endl << endl;
	cout << "Cantidad\tProducto\tP. Unitario\tImporte" << endl;
	cout << "-------------------------------------------------------------" << endl;
}

//M�todo que sirve para mostrar el nombre del producto, descripci�n y precio unitario de cada art�culo del cat�logo
void Producto::mostrarProducto(){
	cout << nombre << "\t" << descripcion << "\t" << precioUnit << endl;
}

//M�todo get para obtener el nombre de un producto
string Producto::getNombre(){
	return nombre;
}

//M�todo get para obtener el precio unitario de un producto
int Producto::getPrecioUnit(){
	return precioUnit;
}

//M�todo get para obtener la cantidad de unidades a comprar de un producto
int ProductoElegido::getCantidad(){
	return cantidad;
}

//M�todo get para obtener el importe total de las unidades a comprar de un producto
int ProductoElegido::getTotalPorProducto(){
	return totalPorProducto;
}

//M�todo get para almacenar la cantidad de unidades a comprar de un producto, seg�n lo que introduzca el usuario
void ProductoElegido::setCantidad(int _cantidad){
	cantidad = _cantidad;
}

//M�todo set para almacenar el importe total de las unidades a comprar de un producto, seg�n las unidades que quiera el usuario
void ProductoElegido::setTotalPorProducto(int _totalPorProducto){
	totalPorProducto = _totalPorProducto;
}

//M�todo para mostrar la descripci�n de cada uno de los productos que el usuario quiera comprar en el men� de carrito
void ProductoElegido::mostrarProductoElegido(){
	cout << cantidad << "\t" << getNombre() << "\t" << getPrecioUnit() << "\t" << totalPorProducto << endl;
}

//M�todo get para obtener el valor total de todos los productos que tiene el carrito
int Carrito::getTotal(){
	return total;
}

//M�todo get para obtener el n�mero de productos de todos los art�culos en un carrito
int Carrito::getNumArticulos(){
	return numArticulos;
}

//M�todo para agregar a la lista de ProductoElegido cada uno de los productos que el usuario quiera comprar
//Usa la funci�n de insertar lista, para la lista ligada
void Carrito::agregarLista(ProductoElegido _prodNuevo){
	insertarLista(lista, _prodNuevo); //Insertamos en la lista el nuevo nodo con el producto
}

//M�todo set para establecer el valor total de todos los productos que tiene el carrito
void Carrito::setTotal(int _total){
	total = _total;
}

//M�todo set para establecer el n�mero de productos de todos los art�culos en un carrito
void Carrito::setNumArticulos(int _numArticulos){
	numArticulos = _numArticulos;
}

//M�todo para mostrar cada uno de los art�culos del carrito que el usuario quiere comprar
//Usa la funci�n de mostrar lista, para la lista ligada
void Carrito::listarCarrito(){
	mostrarLista(lista);
	cout << "-------------------------------------------------------------" << endl;
	cout << "\t\t\t\t\tTotal: $" << total << endl << endl;
}

//M�todo para mostrar el total, calcular un descuento si hay m�s de 10 art�culos en el carrito (11 o m�s)
//Utiliza funci�n de eliminar el primer nodo, para la lista ligada
void Carrito::terminarCompra(){
	cout << endl << "***TERMINAR COMPRA***" << endl << endl;
	cout << "El total de tu compra es: $" << total << endl;
	//Si se compran m�s de 10 art�culos, hacer descuento
	if(numArticulos > 10){
		//Crea un n�mero del 0 al 15 y le suma 5 (de 5 al 20)
		int descuento = rand()%16 + 5;
		cout << "�Se aplica descuento del " << descuento << "% en buen fin por comprar m�s de 10 art�culos!" << endl;
		// 1 - (valor calculado para descontar / 100) multiplicado por el total sin descuento
		cout << "El nuevo total de tu compra es: $" << (1-(descuento/100.0)) * total << endl;
	}
	cout << "Gracias por comprar en �MiTiendita.com!" << endl << endl;
	//Reiniciamos a 0 atributos de carrito
	total = 0;
	numArticulos = 0;
	//Vaciamos toda la lista de ProductosElegidos
	while(lista != NULL){
		eliminarPrimerNodo(lista);
	}
}


//Funciones para lista ligada
//Funci�n para insertar al final de la lista un nuevo nodo, que almacena como dato un ProductoElegido 
void insertarLista(Nodo *&lista, ProductoElegido n){
	Nodo *nuevo_nodo = new Nodo(); //Creamos un nuevo nodo que se va a agregar al final de la lista
	Nodo *aux; //Creamos un apuntador a nodo auxiliar
	
	//Llenar campos del nuevo nodo
	nuevo_nodo->dato = n;
	nuevo_nodo->siguiente = NULL;
	
	if(lista == NULL){ //Si la lista est� vac�a
		lista = nuevo_nodo; //Hacer que la lista empiece con ese nuevo nodo creado
	}
	else{ //Si la lista ya ten�a al menos un nodo
		aux = lista; //aux apunta al inicio de la lista
		while(aux->siguiente != NULL){ //Mientras la lista no est� vac�a o no haya llegado al final de la lista
			aux = aux->siguiente; //Avanzar una posici�n en la lista
		}
		aux->siguiente = nuevo_nodo; //Agregar el nuevo nodo a la lista
	}
}

//Funci�n para recorrer cada uno de los nodos en la lista y mostrar la informaci�n 
void mostrarLista(Nodo *lista){
	while(lista != NULL){ //Mientras no sea el final de la lista
		lista->dato.mostrarProductoElegido(); //Muestra la informaci�n de dicho producto en la lista
		lista = lista->siguiente; //Recorre al siguiente elemento
	}
}

//Funci�n para eliminar el primer elemento de la lista, iterando esta funci�n podemos vaciar el carrito de compras
void eliminarPrimerNodo(Nodo *&lista){
	Nodo *aux = lista; //Auxiliar apunta al primer nodo de la lista
	lista = aux->siguiente; //lista apunta al segundo nodo
	delete aux; //Se elimina el primer nodo
}


