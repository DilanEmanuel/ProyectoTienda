#include "bibliotecaClases.h"

int main(){
	//Funci�n para poder imprimir � y acentos
	setlocale(LC_CTYPE,"Spanish");
	
	//Inicializar cat�logo
	Producto *catalogo[25];
	catalogo[0] = new Producto("Horrocrux", "Horrocrux m�gico con fragmento de alma de mago", 890);
	catalogo[1] = new Producto("Vibranio", "Escudo indestructible de vibranio", 615);
	catalogo[2] = new Producto("Cataclista", "Bomba cataclista para destruir sector de OASIS", 915);
	catalogo[3] = new Producto("Varita m�gica", "Varita m�gica de Dimmsdale para padrino que concede deseos", 1020);
	//...
	
	//Crear carrito con lista de productos vac�a, total 0 y numArticulos 0
	Carrito carrito1(0, 0);
	//Crear menu
	Menu menu1;
	//Mostrar el encabezado del programa
	menu1.mostrarEntrada();
	
	//do while hace que sea infinito hasta que elija 4 (salir)
	do{
		menu1.mostrarMenuPrincipal(); //Se muestra el men� principal
		switch(menu1.getOpcion()){ //Seg�n la opci�n elegida por el usuario en el men� principal
			case 1: //Si elige opci�n 1
				menu1.menuProductosHeader(); //Se muestra encabezado del men� de productos 
				//Recorrer el cat�logo de productos mostrando uno por uno su nombre, descripci�n y precio unitario
				// i<=24
				for(int i=0; i<=3; i++){
                    cout << i+1 << ") "; //Se imprime 1), 2), 3), etc
					catalogo[i]->mostrarProducto();
				}
				int productoElegido; //Se crea una variable para almacenar el n�mero de producto que quiere comprar
				productoElegido = menu1.menuProductosOpcion(); //Pregunta qu� producto desea adquirir y lo guarda en la variable
				if(productoElegido>0 && productoElegido<26){ //Si elige entre el 1 y el 25
					int cantidad = menu1.menuCantidadProductos(); //Ahora pregunta cu�ntas unidades de ese producto quiere comprar y gu�rdalo
					if(cantidad != -1){ //Si no elige -1 unidades de producto, agrega al carrito
						//Crea un objeto de la clase ProductoElegido, con su nombre, descripci�n vac�a, precio unitario, cantidad de unidades y total del importe
						ProductoElegido prodNuevo(catalogo[productoElegido-1]->getNombre(),"",catalogo[productoElegido-1]->getPrecioUnit(), cantidad, cantidad * catalogo[productoElegido-1]->getPrecioUnit());
						carrito1.agregarLista(prodNuevo); //Agrega a la lista el producto que quiere comprar
						//Imprime cadena "n unidad(es) de cierto producto a $xxxx c/u, importe = $xxxx"
						cout << cantidad << " unidad(es) de " << catalogo[productoElegido-1]->getNombre() << " a $" << catalogo[productoElegido-1]->getPrecioUnit() << " c/u, importe = $" << cantidad * catalogo[productoElegido-1]->getPrecioUnit() << endl << endl;
						//Incrementa el n�mero de art�culos en el carrito
						carrito1.setNumArticulos(carrito1.getNumArticulos() + cantidad);
						//Aumenta el total del carrito seg�n los productos
						carrito1.setTotal(carrito1.getTotal() + cantidad * catalogo[productoElegido-1]->getPrecioUnit());
					}
				}else if(menu1.getOpcion() != -1){ //Si no elige un n�mero entre el 1 y el 25 ni tampoco elige -1
					cout << "Opci�n inv�lida, regresando al men� principal" << endl;
				}
				break;
			case 2: //Si elige la opci�n 2
				if(carrito1.getNumArticulos() == 0){ //Si el carrito de compras est� vac�o
					cout << "El carrito de compras est� vac�o!" << endl << endl;
				}else{ //Si al menos un art�culo fue agregado al carrito
					menu1.menuCarritoHeader(); //Imprime el encabezado del men� para ver el carrito
					carrito1.listarCarrito(); //Lista cada uno de los art�culos agregados al carrito y el total
				}
				break;
			case 3: //Si elige la opci�n 3
				carrito1.terminarCompra(); //Muestra el total global del carrito, aplica un descuento si hay m�s de 10 productos y vac�a el carrito
				break;
			case 4: //Si elige la opci�n 4
				cout << "Gracias por venir, �vuelva pronto!";
				break;
			default: //Si elige alguna otro opci�n que no sea del 1 al 4
				cout << "Opci�n no v�lida" << endl;
		}
	}while (menu1.getOpcion() != 4); //Sal del ciclo infinito y termina el programa si elige la opci�n 4 "Salir"
	
}
