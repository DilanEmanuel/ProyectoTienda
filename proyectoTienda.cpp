#include "bibliotecaClases.h"

int main(){
	//Función para poder imprimir ñ y acentos
	setlocale(LC_CTYPE,"Spanish");
	
	//Inicializar catálogo
	Producto *catalogo[25];
	catalogo[0] = new Producto("Horrocrux", "Horrocrux mágico con fragmento de alma de mago", 890);
	catalogo[1] = new Producto("Vibranio", "Escudo indestructible de vibranio", 615);
	catalogo[2] = new Producto("Cataclista", "Bomba cataclista para destruir sector de OASIS", 915);
	catalogo[3] = new Producto("Varita mágica", "Varita mágica de Dimmsdale para padrino que concede deseos", 1020);
	//...
	
	//Crear carrito con lista de productos vacía, total 0 y numArticulos 0
	Carrito carrito1(0, 0);
	//Crear menu
	Menu menu1;
	//Mostrar el encabezado del programa
	menu1.mostrarEntrada();
	
	//do while hace que sea infinito hasta que elija 4 (salir)
	do{
		menu1.mostrarMenuPrincipal(); //Se muestra el menú principal
		switch(menu1.getOpcion()){ //Según la opción elegida por el usuario en el menú principal
			case 1: //Si elige opción 1
				menu1.menuProductosHeader(); //Se muestra encabezado del menú de productos 
				//Recorrer el catálogo de productos mostrando uno por uno su nombre, descripción y precio unitario
				// i<=24
				for(int i=0; i<=3; i++){
                    cout << i+1 << ") "; //Se imprime 1), 2), 3), etc
					catalogo[i]->mostrarProducto();
				}
				int productoElegido; //Se crea una variable para almacenar el número de producto que quiere comprar
				productoElegido = menu1.menuProductosOpcion(); //Pregunta qué producto desea adquirir y lo guarda en la variable
				if(productoElegido>0 && productoElegido<26){ //Si elige entre el 1 y el 25
					int cantidad = menu1.menuCantidadProductos(); //Ahora pregunta cuántas unidades de ese producto quiere comprar y guárdalo
					if(cantidad != -1){ //Si no elige -1 unidades de producto, agrega al carrito
						//Crea un objeto de la clase ProductoElegido, con su nombre, descripción vacía, precio unitario, cantidad de unidades y total del importe
						ProductoElegido prodNuevo(catalogo[productoElegido-1]->getNombre(),"",catalogo[productoElegido-1]->getPrecioUnit(), cantidad, cantidad * catalogo[productoElegido-1]->getPrecioUnit());
						carrito1.agregarLista(prodNuevo); //Agrega a la lista el producto que quiere comprar
						//Imprime cadena "n unidad(es) de cierto producto a $xxxx c/u, importe = $xxxx"
						cout << cantidad << " unidad(es) de " << catalogo[productoElegido-1]->getNombre() << " a $" << catalogo[productoElegido-1]->getPrecioUnit() << " c/u, importe = $" << cantidad * catalogo[productoElegido-1]->getPrecioUnit() << endl << endl;
						//Incrementa el número de artículos en el carrito
						carrito1.setNumArticulos(carrito1.getNumArticulos() + cantidad);
						//Aumenta el total del carrito según los productos
						carrito1.setTotal(carrito1.getTotal() + cantidad * catalogo[productoElegido-1]->getPrecioUnit());
					}
				}else if(menu1.getOpcion() != -1){ //Si no elige un número entre el 1 y el 25 ni tampoco elige -1
					cout << "Opción inválida, regresando al menú principal" << endl;
				}
				break;
			case 2: //Si elige la opción 2
				if(carrito1.getNumArticulos() == 0){ //Si el carrito de compras está vacío
					cout << "El carrito de compras está vacío!" << endl << endl;
				}else{ //Si al menos un artículo fue agregado al carrito
					menu1.menuCarritoHeader(); //Imprime el encabezado del menú para ver el carrito
					carrito1.listarCarrito(); //Lista cada uno de los artículos agregados al carrito y el total
				}
				break;
			case 3: //Si elige la opción 3
				carrito1.terminarCompra(); //Muestra el total global del carrito, aplica un descuento si hay más de 10 productos y vacía el carrito
				break;
			case 4: //Si elige la opción 4
				cout << "Gracias por venir, ¡vuelva pronto!";
				break;
			default: //Si elige alguna otro opción que no sea del 1 al 4
				cout << "Opción no válida" << endl;
		}
	}while (menu1.getOpcion() != 4); //Sal del ciclo infinito y termina el programa si elige la opción 4 "Salir"
	
}
