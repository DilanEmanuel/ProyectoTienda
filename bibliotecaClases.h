#include <stdlib.h>
#include <iostream>
#include <clocale> //Para acentos y ñ

using namespace std;

//Clase que sirve para mostrar los menús del programa, así como recabar algunas opciones que seleccione el usuario
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

//Clase que sirve para almacenar los datos de los 25 productos a seleccionar y mostrar el catálogo
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

//Clase que sirve para llevar el control de los productos elegidos, el total y los artículos elegidos
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

//Métodos constructores
Menu::Menu(){
}

Producto::Producto(string _nombre, string _descripcion, int _precioUnit){
	nombre = _nombre;
	descripcion = _descripcion;
	precioUnit = _precioUnit;
}

//Sobrecarga de constructor para Producto, útil para crear la lista de Productos elegidos
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

//Métodos destructores
Menu::~Menu(){
}

//...

//Método set para definir la opción elegida por el usuario
void Menu::setOpcion(int _opcion){
	opcion = _opcion;
}

//Método get para obtener la opción elegida por el usuario
int Menu::getOpcion(){
	return opcion;
}

//Método para mostrar el encabezado del programa
void Menu::mostrarEntrada(){
	cout << "shoppingMe.com" << endl << "=================" << endl;
	cout << "Nombre y Matrícula / Nombre y Matrícula" << endl << endl;
}

//Método para mostrar el menú principal del usuario
void Menu::mostrarMenuPrincipal(){
	cout << "*** MENU PRINCIPAL ***" << endl << endl;
	cout << "1) Seleccionar productos" << endl;
	cout << "2) Ver carrito de compras" << endl;
	cout << "3) Terminar compra" << endl;
	cout << "4) Salir" << endl << endl;
	cout << "Selecciona opción: ";
	int aux;
	cin >> aux;
	setOpcion(aux);
}

//Método para mostrar el encabezado del menú de productos a comprar
void Menu::menuProductosHeader(){
	cout << endl << "***SELECCIONAR PRODUCTO***" << endl << endl;
	cout << "Producto\tDescripción\tPrecio unitario" << endl;
	cout << "__________________________________________________" << endl;
}

//Método para preguntar al usuario qué producto desea comprar
int Menu::menuProductosOpcion(){
	cout << endl << "¿Qué productos deseas comprar? (-1 para cancelar): ";
	int aux;
	cin >> aux;
	return aux;
}

//Método para preguntar al usuario cuántos productos desea comprar, verificando si el número es válido
int Menu::menuCantidadProductos(){
	cout << endl << "¿Cuántos productos deseas comprar? (-1 para cancelar): ";
	int aux;
	cin >> aux;
	//Si elige un número de productos mayor a 0, regresa el número de productos
	if(aux > 0){
		return aux;
	}
	//Si elige un número menor a -1 o 0
	else if(aux < -1 || aux == 0){
		cout << "Opción inválida, regresando al menú..." << endl << endl;
	}
	//Si elige la opción -1 (regresar al menú)
	return -1;
}

//Método para mostrar el encabezado del menú del carrito de compras
void Menu::menuCarritoHeader(){
	cout << endl << "***CARRITO DE COMPRAS***" << endl << endl;
	cout << "Cantidad\tProducto\tP. Unitario\tImporte" << endl;
	cout << "-------------------------------------------------------------" << endl;
}

//Método que sirve para mostrar el nombre del producto, descripción y precio unitario de cada artículo del catálogo
void Producto::mostrarProducto(){
	cout << nombre << "\t" << descripcion << "\t" << precioUnit << endl;
}

//Método get para obtener el nombre de un producto
string Producto::getNombre(){
	return nombre;
}

//Método get para obtener el precio unitario de un producto
int Producto::getPrecioUnit(){
	return precioUnit;
}

//Método get para obtener la cantidad de unidades a comprar de un producto
int ProductoElegido::getCantidad(){
	return cantidad;
}

//Método get para obtener el importe total de las unidades a comprar de un producto
int ProductoElegido::getTotalPorProducto(){
	return totalPorProducto;
}

//Método get para almacenar la cantidad de unidades a comprar de un producto, según lo que introduzca el usuario
void ProductoElegido::setCantidad(int _cantidad){
	cantidad = _cantidad;
}

//Método set para almacenar el importe total de las unidades a comprar de un producto, según las unidades que quiera el usuario
void ProductoElegido::setTotalPorProducto(int _totalPorProducto){
	totalPorProducto = _totalPorProducto;
}

//Método para mostrar la descripción de cada uno de los productos que el usuario quiera comprar en el menú de carrito
void ProductoElegido::mostrarProductoElegido(){
	cout << cantidad << "\t" << getNombre() << "\t" << getPrecioUnit() << "\t" << totalPorProducto << endl;
}

//Método get para obtener el valor total de todos los productos que tiene el carrito
int Carrito::getTotal(){
	return total;
}

//Método get para obtener el número de productos de todos los artículos en un carrito
int Carrito::getNumArticulos(){
	return numArticulos;
}

//Método para agregar a la lista de ProductoElegido cada uno de los productos que el usuario quiera comprar
//Usa la función de insertar lista, para la lista ligada
void Carrito::agregarLista(ProductoElegido _prodNuevo){
	insertarLista(lista, _prodNuevo); //Insertamos en la lista el nuevo nodo con el producto
}

//Método set para establecer el valor total de todos los productos que tiene el carrito
void Carrito::setTotal(int _total){
	total = _total;
}

//Método set para establecer el número de productos de todos los artículos en un carrito
void Carrito::setNumArticulos(int _numArticulos){
	numArticulos = _numArticulos;
}

//Método para mostrar cada uno de los artículos del carrito que el usuario quiere comprar
//Usa la función de mostrar lista, para la lista ligada
void Carrito::listarCarrito(){
	mostrarLista(lista);
	cout << "-------------------------------------------------------------" << endl;
	cout << "\t\t\t\t\tTotal: $" << total << endl << endl;
}

//Método para mostrar el total, calcular un descuento si hay más de 10 artículos en el carrito (11 o más)
//Utiliza función de eliminar el primer nodo, para la lista ligada
void Carrito::terminarCompra(){
	cout << endl << "***TERMINAR COMPRA***" << endl << endl;
	cout << "El total de tu compra es: $" << total << endl;
	//Si se compran más de 10 artículos, hacer descuento
	if(numArticulos > 10){
		//Crea un número del 0 al 15 y le suma 5 (de 5 al 20)
		int descuento = rand()%16 + 5;
		cout << "¡Se aplica descuento del " << descuento << "% en buen fin por comprar más de 10 artículos!" << endl;
		// 1 - (valor calculado para descontar / 100) multiplicado por el total sin descuento
		cout << "El nuevo total de tu compra es: $" << (1-(descuento/100.0)) * total << endl;
	}
	cout << "Gracias por comprar en ¡MiTiendita.com!" << endl << endl;
	//Reiniciamos a 0 atributos de carrito
	total = 0;
	numArticulos = 0;
	//Vaciamos toda la lista de ProductosElegidos
	while(lista != NULL){
		eliminarPrimerNodo(lista);
	}
}


//Funciones para lista ligada
//Función para insertar al final de la lista un nuevo nodo, que almacena como dato un ProductoElegido 
void insertarLista(Nodo *&lista, ProductoElegido n){
	Nodo *nuevo_nodo = new Nodo(); //Creamos un nuevo nodo que se va a agregar al final de la lista
	Nodo *aux; //Creamos un apuntador a nodo auxiliar
	
	//Llenar campos del nuevo nodo
	nuevo_nodo->dato = n;
	nuevo_nodo->siguiente = NULL;
	
	if(lista == NULL){ //Si la lista está vacía
		lista = nuevo_nodo; //Hacer que la lista empiece con ese nuevo nodo creado
	}
	else{ //Si la lista ya tenía al menos un nodo
		aux = lista; //aux apunta al inicio de la lista
		while(aux->siguiente != NULL){ //Mientras la lista no esté vacía o no haya llegado al final de la lista
			aux = aux->siguiente; //Avanzar una posición en la lista
		}
		aux->siguiente = nuevo_nodo; //Agregar el nuevo nodo a la lista
	}
}

//Función para recorrer cada uno de los nodos en la lista y mostrar la información 
void mostrarLista(Nodo *lista){
	while(lista != NULL){ //Mientras no sea el final de la lista
		lista->dato.mostrarProductoElegido(); //Muestra la información de dicho producto en la lista
		lista = lista->siguiente; //Recorre al siguiente elemento
	}
}

//Función para eliminar el primer elemento de la lista, iterando esta función podemos vaciar el carrito de compras
void eliminarPrimerNodo(Nodo *&lista){
	Nodo *aux = lista; //Auxiliar apunta al primer nodo de la lista
	lista = aux->siguiente; //lista apunta al segundo nodo
	delete aux; //Se elimina el primer nodo
}


