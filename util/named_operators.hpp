
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		API : NAMED OPERATORS FOR C++
//																		AUTHOR : 	JOSÉ RAÚL MORENO ACERO
//																		DATE : 	 	06/05/2023
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

/// 
/// @defgroup Operadores
/// 
/// @brief Conjunto de Funciones para crear Operadores Nombrados.
/// 
/// @details
/// 
/// Empleando técnicas avanzadas de programación se puede realizar una clase para poder parametrizar con funciones empleando el uso de sintaxis <operador> ,
/// por ejemplo el siguiente codigo.
/// 
/// Para poder utilizar los Operadores Nombrados se tiene que utilizar los operadores <b style="font-size: 120%;">></b> y <b style="font-size: 120%;"><</b>
/// mientras se encierra al <b>NamedOperator</b> dentro del parentesis angular <i>(muy parecido a la sintaxis para el uso de templates)</i>. La sintaxis
/// general de estos operadores es la siguiente :
/// 
/// <center style="margin: auto; font-family: var(--font-family-monospace);">
/// <b class="paramname" style="font-size: 130%;">OPERANDO_IZQUIERDO </b><b style="font-size: 150%;"><</b>
/// <b style="color: var(--fragment-keyword); font-size: 120%;"> NAMED_OPERATOR </b><b style="font-size: 150%;">></b>
/// <b class="paramname" style="font-size: 130%;"> OPERANDO_DERECHO</b>
/// </center>
/// 
/// @section Ejemplo Ejemplo :
/// 
/// El siguiente ejemplo muestra el uso de la api de named_operators para crear un operador suma a partir de una función cualquiera.
/// 
/// @code{.cpp}
/// 
///		// Incluiremos primero el archivo de cabecera para los operadores.
///		
///		#include <named_operators.h>
///		
///		// Definiremos una función cualquiera que queramos representar como Operador Nombreado. Por ejemplo una Suma de dos números :
///		
///		static int Suma (int A , int B) { return (A + B); }
///		
///		// Craeremos el Operador para esta función usando el template Operators::MakeNamedOperator de la siguiente manera.
///		
///		static constexpr auto suma = Operators::MakeNamedOperator (Suma); // Damos el nombre de nuestro operador a la variable.
///		
///		// Dentro de nuestro main vamos a utilizar nuestro operador donde querramos.
///		
///		int main () {
///			
///			// Creamos nuestros valores a sumar.
///			
///			int a = 100 , b = 200;
///		
///			// Utilizamos la sintaxis : PARAMETER_A <NAME_OPERATOR> PARAMETER_B
///			
///			auto Result = a <suma> b; // Genera la suma de a y b usando el operador <suma> que creamos.
///			
///		}
///		
/// @endcode
/// 
/// @section Functor Objeto Funcional
/// 
/// No solamente puede utilizarse con Funciones , también se pueden utilizar functores (Objetos funcionales) , Por Ejemplo :
/// 
/// @code{.cpp}
/// 
/// 	// Definiremos un operador llamado "resta". Usamos Lambda-expressións para asignar el contenido.
/// 
/// 	static constexpr auto resta = Operators::MakeNamedOperator ([] (int A , int B) -> int { return (A - B); });
/// 
/// @endcode
/// 
/// @section Object Metodos y Objeto
/// 
/// Asi mismo se pueden usar clases y objetos para asignar al operador , para esto simplemente tenemos que definir el objeto del cuál se estará utilizando
/// para poder invocar el metodo respectivo.
/// 
/// @code{.cpp}
/// 
/// 	// Clase con el metodo a utilizar como operador.
/// 	
/// 	class Calculadora {
/// 	
/// 		// Definimos los metodos y propiedades de la clase.
/// 	
/// 		public :
/// 			
/// 			// Operacion. (1 = suma , 2 = resta , 3 = multi , 4 = division).
/// 			
/// 			int Operacion = -1;
/// 			
/// 			// Constructor con la operación a aplicar.
/// 			
/// 			Calculadora (int CodOper) : Operacion (CodOper) { }
/// 			
/// 			// Definimos todas las funciones en el siguiente metodo.
/// 			
/// 			int Procesar (int A , int B) {
/// 			
/// 				// Switcheamos la operación a devolver.
/// 				
/// 				switch (Operacion) {
/// 						
/// 					case 1 : return (A + B);
/// 					case 2 : return (A - B);
/// 					case 3 : return (A * B);
/// 					case 4 : return (A / B);
/// 					default : return 0;
/// 					
/// 				}
/// 				
/// 				// Devuelve 0 de cualquier modo.
/// 				
/// 				return 0;
/// 				
/// 			}
/// 		
/// 	};
/// 	
/// 	// Ahora en nuestro main tenemos lo siguiente.
/// 
/// 	int main () {
/// 		
/// 		// Creamos un objeto calculadora para una multiplicación.
/// 		
/// 		Calculadora MyCalc (3);
/// 		
/// 		// Ahora creamos el operador calc para el metodo Procesar usando la sobrecarga de MakeNamedOperator.
/// 		
/// 		const auto calc = Operators::MakeNamedOperator (&Calculadora::Procesar , MyCalc);
/// 		
/// 		// Utilizamos el operador de la misma manera.
/// 		
/// 		auto Result = 100 <calc> 20;  // Result = 2000
/// 		
/// 		// Ahora cambiamos de operación a una suma.
/// 		
/// 		MyCalc.Operacion = 1;
/// 		
/// 		// Asignamos la suma de dos numeros.
/// 		
/// 		Result = 300 <calc> 100; // Result = 400
/// 		
/// 	}
/// 
/// @endcode
/// 
/// @section Combination Combinacion de Operadores
/// 
/// La ventaja es que podemos usar cuantos operadores querramos , la manera en la que tienen asociatividad es de <b>Izquierda a Derecha</b> por lo que 
/// si tenemos un conjunto de operadores como se tiene a continuación entonces el resultado sería de la siguiente forma :
/// 
/// @code
/// 
/// 	// Instanciamos 4 operadores para las cuatro operaciones basica : suma , resta , multi y divi.
/// 	
/// 	const auto suma = 	Operators::MakeNamedOperator (Suma);
/// 	const auto resta = 	Operators::MakeNamedOperator (Resta);
/// 	const auto multi = 	Operators::MakeNamedOperator (Multiplicacion);
/// 	const auto divi = 	Operators::MakeNamedOperator (Division);
/// 	
/// 	// Realizamos la siguiente operación usando nuestros operadores (100 + 20) * 10
/// 	
/// 	const auto Result = 100 <suma> 20 <multi> 10; // Result = 1200
/// 	
/// @endcode
/// 
/// @section Assigment Operador de Asignación
/// 
/// Se cuenta además con la sobrecarga para el operador <b style="font-size: 120%;">>=</b> en caso de que el operando se trate de una <b>Referencia</b> de
/// tipo (L-Value referencia). Es posible de la misma forma que los casos anteriores , unir varias veces el mismo operador con la finalidad que los resultados
/// de cada operando queden grabados en el operando <b>izquierdo</b>.
/// 
/// La Sintaxis que se tiene para aplicar el operador de asignación con un NamedOperator es la siguiente :
/// 
/// <center style="margin: auto; font-family: var(--font-family-monospace);">
/// <b class="paramname" style="font-size: 130%;">OPERANDO_IZQUIERDO </b><b style="font-size: 150%;"><</b>
/// <b style="color: var(--fragment-keyword); font-size: 120%;"> NAMED_OPERATOR </b><b style="font-size: 150%;">>=</b>
/// <b class="paramname" style="font-size: 130%;"> OPERANDO_DERECHO</b>
/// </center>
/// 
/// Para visualizar el uso de este operador veamos el siguiente ejemplo :
/// 
/// @code
/// 
/// 	// Crearemos el resultado de aplicar los operadores aritmeticos sobre el siguiente valor base.
/// 	
/// 	auto Result = 100.0f;
/// 	
/// 	// Multiplicamos y asignamos el resultado de la operación de Suma , división de un determinado valor.
/// 	
/// 	Result <multi>= (10 <suma> 100 <divi> 5);
/// 	
/// 	// Result : 2200.0f 
/// 
/// @endcode
/// 
/// @pre
/// El <b class="paramname">Operando Izquierdo</b> debe ser un <b>L-Value</b> Asignable y tener definido el operador <b>=</b>. Esto debido a que se utiliza dicho
/// operador para poder asignar el resultado de la operación al operando en cuestión.
/// 

// -----------------------------------------------------------------------------

// Mediante el uso de estas utilerias es posible realizar la combinación de varios operadores nombrados en secuencia con la finalidad de ahorrar codigo y llamadas
// a funciones que de otra forma no expresan mucho.

// -----------------------------------------------------------------------------
/// 
/// @file named_operators.h
/// 
/// @brief Archivo con la declaración de las funciones para crear operadores personalizados para utilizar con la sintaxis <> , se tiene una especialización para
/// que pueda utilizarse con clases y objetos de la misma manera.
/// 
/// @details
/// 
/// Se pueden crear varios tipos de operadores , todos son <b>Funciones Binarios (2 parametros)</b> , la función @ref MakeNamedOperator se utiliza para conformar
/// una instancia de nuestro @ref Functor el cuál tiene implementados la sobrecarga de los operadores ">" y "<" , por lo que es el elemento que representa
/// el operador mismo y mediante los templates de funciones se puede definir como sea posible para poder usar con cualquier función binaria.
/// 
// -----------------------------------------------------------------------------

// Tenemos entonces lo siguiente para empezar de esta forma.

#pragma once

// -----------------------------------------------------------------------------
/// @addtogroup Operadores
/// @{
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

// Ahora lo primero que realizaremos será crear nuestro enclosed para la cabecera de este archivo.

#ifndef CYTTEK_NAMED_OPERATORS_H
#define CYTTEK_NAMED_OPERATORS_H

// Ahora pasaremos a lo siguiente con la finalidad de poder establecer los operadores a utilizar.

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// 
// 							INCLUYENDO BASES
// 							
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// Primero incluiremos las bases de stdio y stdlib para poder pintar en consolta y tener acceso a ciertas utilerias de la biblioteca estandar.

#include <stdio.h>
#include <stdlib.h>

// Incluiremos los elementos funcionales para poder conectar funciones con std::bind.

#include <functional>

// Incluiremos el typetraits para poder hacer uso de elemento

#include <type_traits>

// Incluiremos las utilerias de C++ para poder utilizar diferentes elementos en la actualización con c++11 , 14 y 17.

#include <utility>

// Incluiremos otros modulos.

// -----------------------------------------------------------------------------

// Ahora tenemos que incluir primero nuestro coresito para poder reutilizar en todos.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 								CORE
// 							
// -----------------------------------------------------------------------------

// Tenemos lo siguiente que es la inclusión de nuestro core para incluir las bases.

#include "core.hpp"

// Ahora pasaremos al espacio de nombres.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							ESPACIO DE NOMBRES
// 							
// -----------------------------------------------------------------------------

// Estableceremos un pequeño espacio de nombres para este tipo de elemento.

/// @brief Espacio de Nombres para las funciones de creación y manejo de Operadores Nombrados.

namespace Operators {

// -----------------------------------------------------------------------------

// Ahora pasaremos a la declaración del tipo para la función de operador y el operador nombrado en si mismo.

// -----------------------------------------------------------------------------
/// @addtogroup Operadores
/// @{
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// 
// 							FUNCTOR WRAPPED
// 							
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// Crearemos un wrapped para un functor de manera que cualquier elemento que sea de un tipo valido callable pueda ser agregado a un operando derecho.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Estructura contenedora de Objetos Funcionales , tales como Lambdas , Functionals , Funciones Estaticas , Punteros a funciones.
///
/// @tparam     TFunctor  Tipo de Función Incorporada.
/// 
/// @details
/// 
/// Los operadores nombrados son construidos a partir de esta estructura que funciona como un wrapped para poder contener el objeto invocable que se
/// utilizará para realizar el proceso con los parametros.
/// 
// -----------------------------------------------------------------------------
	
template <typename TFunctor>
struct Functor {
	
	// Primero declaramos un alias para el tipo de función establecido.
	
	/// @brief Tipo de Función Incorporado (typedef)
	
	typedef TFunctor TypeFunctor;
	
	// -----------------------------------------------------------------------------
	// 
	// 							Objeto Funcional
	// 							
	// -----------------------------------------------------------------------------
	
	// Ahora vamos a establecer
	
	/// @brief Referencia , valor o puntero a Función.
	/// @note Este elemento debe ser invocable con los argumentos que se definan mediante los operadores < y >.
	
	TypeFunctor Funcion;
	
	// -----------------------------------------------------------------------------
	
};

// Para poder crear operadores nombrados requerimos una función para asignar un Objeto Functor a un determinado Objeto callable.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Función para crear y construir un wrapped de función con un tipo de funcion arbitrario.
///
/// @param      Funcion   Referencia , dirección de memoria o valor de la función a utilizar como wrapped para el nuevo operador nombrado.
///
/// @tparam     TFunctor  Tipo de dato para la entrada de la función a utilizar.
///
/// @return     Nueva instancia de Functor que representa el nuevo operador nombrado.
/// 
/// @details
/// 
/// Esta función es la principal de esta cabecera , como su nombre lo indica nos permite crear y construir una instancia del wrapped @ref Functor con
/// el objeto funcional establecido en el parametro , ya sea función , metodo , objeto , lambda , etc.
/// 
/// @note
/// Es importante señalar que este wrapped define el operador nombrado , por lo que es importante construirlo mediante esta función antes de
/// utilizarlo con los operadores < y >.
/// 
// -----------------------------------------------------------------------------

template <typename TFunctor>
ALWAYS_INLINE constexpr Functor <TFunctor> MakeNamedOperator (TFunctor && Funcion) {
	
	// Devolvemos la respectiva versión de Functor para el objeto llamable.
	
	return Functor <TFunctor> { std::forward <TFunctor> (Funcion) };
	
	// -----------------------------------------------------------------------------
	
}

// Para poder conectar una función miembro se tiene el siguiente metodo con el objeto de referencia a utilizar.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Función para crear y construir un wrapped de función con un metodo de cualquier objeto de la misma clase.
///
/// @param      Funcion   Referencia , dirección de memoria de algún metodo.
/// @param 		Objeto 	  Referencia a un Objeto en el cuál invocar el metodo.
///
/// @tparam     TFunctor  Tipo de dato para la entrada de la función a utilizar.
/// @tparam 	TClass 	  Clase de la cuál obtendremos el metodo.
///
/// @return     Nueva instancia de Functor que representa el nuevo operador nombrado.
/// 
/// @details
/// 
/// Esta función es la principal de esta cabecera , como su nombre lo indica nos permite crear y construir una instancia del wrapped @ref Functor con
/// el objeto funcional establecido en el parametro , ya sea función , metodo , objeto , lambda , etc.
/// 
/// @note
/// Es importante señalar que este wrapped define el operador nombrado , por lo que es importante construirlo mediante esta función antes de
/// utilizarlo con los operadores < y >.
/// 
// -----------------------------------------------------------------------------

template <typename TFunctor , typename TClass>
ALWAYS_INLINE decltype (auto) MakeNamedOperator (TFunctor TClass::* Funcion , TClass * Objeto) {
	
	// Devolvemos la conexión de una función miembro con su respectivo objeto.
	
	return MakeNamedOperator (std::bind (Funcion , Objeto , std::placeholders::_1 , std::placeholders::_2));
	
	// -----------------------------------------------------------------------------
	
}

// Ahora continuaremos con la implementación de forma interna de los siguientes operadores.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		OPERATORS IMPLEMENTACION
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Tenemos en particular dos elementos , primero tenemos el respectivo elemento de estructura NamedOperator el cuál es un elemento que anexa un Operando y el
// functor a utilizar para la operación.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							Named Operator
// 							
// -----------------------------------------------------------------------------

// Comenzamos primero por la implementación de nuestro NamedOperator que contiene el Operando Izquierdo y el Functor respectivo para trabajar con dicho operando
// y un operando derecho que sea válido.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Elemento parcial para poder establecer la conexión con los operadores de < y >. Utilizando cualquier operador nombrado instanciado.
///
/// @tparam     TypeA     Tipo del Parametro A.
/// @tparam     TFunctor  Tipo de Función Utilizado en el Operador Nombrado.
/// 
/// @details
/// 
/// Esta estructura es la parte intermedia cuando se invoca un operador nombrado mediante el uso de la sintaxis < op > , el operador > define una sobrecarga
/// para este tipo de dato generando de esta manera la conexión con el operador < que define la conexión con el operador nombrado.
/// 
/// @note
/// Si el operador es una <b style="color: var(--primary-color);">Referencia (L-Value)</b> válida entonces se devuelve una especialización de esta plantilla
/// con el operando en forma de referencia.
/// 
/// @see MakeNamedOperator
/// 
// -----------------------------------------------------------------------------

template <typename TypeA , typename TFunctor , bool = false>
struct NamedOperator {
	
	// -----------------------------------------------------------------------------
	// 
	// 							Propiedades Operator
	// 							
	// -----------------------------------------------------------------------------
	
	// Primero tendremos el Operando que se capturo de la función para procesar como operando Izquierdo.
	
	// -----------------------------------------------------------------------------
	///
	/// @brief Operando A de la expresión actual.
	/// @details Valor que representa el Operando Izquierdo de la expresión.
	/// 
	// -----------------------------------------------------------------------------
	
	TypeA Operando;
	
	// Ahora tenemos el functor respectivo que se utilazá para ser llamado con los dos operandos.
	
	// -----------------------------------------------------------------------------
	///
	/// @brief Instancia a un Operador Nombrado que se haya creado. @see MakeNamedOperator
	/// 
	// -----------------------------------------------------------------------------
	
	Functor <TFunctor> Operacion;
	
	// -----------------------------------------------------------------------------
	
};

// Ahora tendremos una especialización de la estructura named operator para cuando se tiene una referencia como operando.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Elemento especializado para poder establecer la conexión con los operadores de < y > , >=. Utilizando cualquier operador en forma de referencia.
///
/// @tparam     TypeA     Tipo del Parametro A.
/// @tparam     TFunctor  Tipo de Función Utilizado en el Operador Nombrado.
/// 
/// @details
/// 
/// Esta estructura es la parte intermedia cuando se invoca un operador nombrado mediante el uso de la sintaxis < op > , el operador > define una sobrecarga
/// para este tipo de dato generando de esta manera la conexión con el operador < que define la conexión con el operador nombrado.
/// 
/// En este caso se especializa para cuando el parametro bool es igual a <b style="color: var(--fragment-keyword);">True</b>. En tal caso se utiliza
/// el campo <b>Operando</b> en forma de un <i>reference_wrapped</i>.
/// 
/// @note
/// Esta especialización de la estructura NamedOperator , establece el <b>Operando</b> como una referencia que permitirá utilizar la sintaxis de asignación
/// mediante la sobrecarga de >=.
/// 
/// @see MakeNamedOperator
/// 
// -----------------------------------------------------------------------------

template <typename TypeA , typename TFunctor>
struct NamedOperator <TypeA , TFunctor , true> {
	
	// Ahora definiremos la especialización para el caso donde se trate de una referencia.
	
	// -----------------------------------------------------------------------------
	// 
	// 							Propiedades Operator
	// 							
	// -----------------------------------------------------------------------------
	
	// Primero tendremos el Operando que se capturo de la función para procesar como operando Izquierdo en forma de una referencia.
	
	// -----------------------------------------------------------------------------
	///
	/// @brief Operando A (L-Value Referencia) de la expresión actual.
	/// @details
	/// Referencia al Operando Izquierdo de la expresión que también puede utilizarse para realizar la sintaxis de <b>Asignación</b>. @see Operators::operator>=
	/// 
	// -----------------------------------------------------------------------------
	
	std::reference_wrapper <TypeA> Operando;
	
	// Ahora tenemos el functor respectivo que se utilazá para ser llamado con los dos operandos.
	
	// -----------------------------------------------------------------------------
	///
	/// @brief Instancia a un Operador Nombrado que se haya creado. @see MakeNamedOperator
	/// 
	// -----------------------------------------------------------------------------
	
	Functor <TFunctor> Operacion;
	
	// -----------------------------------------------------------------------------
	
};

// Ahora lo siguiente será la implementación de los operadores sobrecargados < > para poder usar junto a estos functores.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// 
// 							OPERATOR OVERLOADING
// 							
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// Tenemos ahora la implementación de nuestro respectiva función para la creación de un NamedOperator con el Operando Izquierdo y el functor respectivo
// que se estará utilizando.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Sobrecarga del operador < para poder utilizar con cualquier operador nombrado que se haya creado.
///
/// @param      Operando   El operando Izquierdo de la Expressión (L-Value , R-Value , X-Value).
/// @param  	Operacion  El operador Nombrado que se haya instanciado.
///
/// @tparam     TypeA      Tipo del Operando Izquierdo.
/// @tparam     TFunctor   Tipo de la función wrapped dentro del @ref Functor.
///
/// @return     Instancia de un NamedOperator para poder conectar con el siguiente operador >.
/// 
/// @details
/// 
/// Esta sobrecarga se implementa para que cuando se utilice un operador nombrado sobre un operando a la izquierda , este devuelva una estructura de datos
/// intermedia que contiene dicho operando y el operador , de esta manera se utiliza para el operador >.
/// 
/// @pre
/// Si el tipo de dato declarado del parametro <b class="paramname">Operando</b> es un valor <b>L-Value</b> asignable entonces la función devolverá un
/// NamedOperator especializado en referencias (puede utilizar el operador <b>>=</b>).
/// 
/// @note
/// El operando A debe ser de un tipo (TypeA) igual al tipo definido para el primer parametro de la Operación a realizar actualmente.
/// 
// -----------------------------------------------------------------------------

template <typename TypeA , typename TFunctor>
decltype (auto) operator < (TypeA && Operando , const Functor <TFunctor> & Operacion) {
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							TYPE A ALIASING
	// 							
	// -----------------------------------------------------------------------------
	
	// Primero vamos a recuperar el tipo Base del operando que se está utilizando en la izquierda
	
	using TypeOperadorA = std::decay_t <std::remove_reference_t <TypeA>>;
	
	// -----------------------------------------------------------------------------
	
	// Validaremos de la misma forma si el tipo de dato actual es un tipo de "referencia" válida , revisamos si es un l-value referencia , que no sea un puntero
	// y que no sea qualificado como const , en ese caso devolvemos una especialización del NamedOperator para referencias.
	
	static constexpr bool IsReference = (std::is_lvalue_reference_v <decltype (Operando)> && !std::is_pointer_v <TypeOperadorA> &&
	                                    !std::is_const_v <std::remove_reference_t <decltype (Operando)>>);
	
	// using TypeOperadorA = std::conditional_t <IsReference , std::add_lvalue_reference_t <TypeOperadorBase> , TypeOperadorBase>;
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							NAMED OPERATOR
	// 							
	// -----------------------------------------------------------------------------
	
	// Una vez Válidado lo anterior ahora devolvemos el respectivo NamedOperator con el functor y el operando izquierdo asignado.
	
	// -----------------------------------------------------------------------------
	
	// Devolvemos una instancia del Operador respectivo para el tipo A la función de Operación a aplicar.
	
	return NamedOperator <TypeOperadorA , TFunctor , IsReference> { std::forward <TypeA> (Operando) , Operacion };
	
	// -----------------------------------------------------------------------------
	
}

// Ahora implementaremos el operador > para poder procesar la operación con ambos operando y el NamedOperator (Functor) respectivo.

/// ----------------------------------------------------------------------------
/// @brief      Implementación del Operador > para los objetos NamedOperator y el segundo parametro.
///
/// @param      Operador  Operador Nombrado creado con la sobrecarga del operador < sobre el named operator instanciado.
/// @param      Operando  Operando Derecho de la expresión.
///
/// @tparam     TypeA     Tipo del Operando Izquierdo.
/// @tparam     TFunctor  Named Operator creado con el operador < sobre el Named Operator.
/// @tparam     Reference Indica que el NamedOperador tiene una referencia al operando o no.
/// @tparam     TypeB     Tipo del Operando Derecho.
///
/// @return     El resultado de la expresión. El equivalente a ejecutar : Operador (Operando A , Operando B);
/// 
/// @details
/// 
/// Una vez que se haya hecho la aplicación del operador < sobre el named operator , se aplica ahora esta sobrecarga con el siguiente
/// operando de la expresión para poder tener de esta forma la sintaxis : Operando A < named-operator > Operando B.
/// 
/// Esta sobrecarga devuelve el resultado de aplicar la función wrapped sobre ambos operandos , si no existe un tipo válido para los operandos
/// establecidos entonces se lanza un error de compilación.
/// 
/// @note
/// La función determina mediante invoke_result_t el tipo del resultado de la expressión aplicada.
/// 
// -----------------------------------------------------------------------------

template <typename TypeA , typename TFunctor , bool Reference , typename TypeB>
auto operator > (NamedOperator <TypeA , TFunctor , Reference> && Operador , TypeB && Operando) -> std::invoke_result_t <TFunctor , TypeA , TypeB> {
	
	// -----------------------------------------------------------------------------
	// 
	// 							Invocacion de Functor
	// 							
	// -----------------------------------------------------------------------------
	
	// Ahora solamente aplicamos nuestro functor sobre los operandos A y B respectivamente para devolver el valor requerido.
	
	return Operador.Operacion.Funcion (Operador.Operando , std::forward <TypeB> (Operando));
	
	// -----------------------------------------------------------------------------
	
}

// Ahora implementaremos el operador >= para realizar la operación y además asignar el resultado directamente a nuestro operando izquierdo.

/// ----------------------------------------------------------------------------
/// @brief      Implementación del Operador >= para los objetos NamedOperator con referencias al Operando y el segundo parametro.
///
/// @param      Operador  Operador Nombrado creado con la sobrecarga del operador < en un operando L-Value sobre el named operator instanciado.
/// @param      Operando  Operando Derecho de la expresión.
///
/// @tparam     TypeA     Tipo del Operando Izquierdo.
/// @tparam     TFunctor  Named Operator creado con el operador < sobre el Named Operator.
/// @tparam     Reference Indica que el NamedOperador tiene una referencia al operando o no.
/// @tparam     TypeB     Tipo del Operando Derecho.
///
/// @return     Referencia al <b>Operando A</b>. Equivalente a : (Operando_A = Operando_A <Operator> Operando_B).
/// 
/// @details
/// 
/// Esta sobrecarga permite utilizar los NamedOperator con la sintaxis <b class="paramname">OPERANDO_I</b><b><</b><b class="paramname">OPERATOR</b><b>>=</b>
/// <b class="paramname">OPERANDO_D</b>. De esta manera se consigue realizar la aplicación del operando sobre el valor y al mismo tiempo asignar el resultado
/// en dicha variable.
/// 
/// Para poder realizarlo es necesario contar con una instancia primero del Objeto o variable que se vaya a operar con su valor inicializado y después aplicar
/// dicho operador sobre el mismo mediante la sintaxis de este operador. Por ejemplo :
/// 
/// @code{.cpp}
/// 
/// 	// Declaramos nuestro objeto para operar.
/// 	
/// 	std::string Operando_A (" CADENA CON BORDES    ");
/// 	
/// 	// Ahora aplicamos el operador Trim sobre el mismo.
/// 	
/// 	Operando_A <Trim>= " "; // Operando_A : "CADENA CON BORDES"
/// 
/// @endcode
/// 
/// @pre
/// El operando izquierdo debe ser un <b>(L-Value)</b> válido y tener el operador de asignación establecido para poder considerar esta sobrecarga.
/// 
/// @note
/// La función determina mediante invoke_result_t el tipo del resultado de la expressión aplicada actualmente.
/// 
// -----------------------------------------------------------------------------

template <typename TypeA , typename TFunctor , bool Reference , typename TypeB>
decltype (auto) operator >= (NamedOperator <TypeA , TFunctor , Reference> && Operador , TypeB && Operando) {
	
	// Primero tendremos que válidar el estado del parametro de plantilla Reference , si es igual a false entonces la operación no puede aplicarse y devolvemos
	// un static assert.
	
	static_assert (Reference , "Operador::Operando no es (L-Value) asignable. [Eg. es un valor const o un puntero]");
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							Invocacion de Functor
	// 							
	// -----------------------------------------------------------------------------
	
	// Válidamos una vez más para poder continuar.
	
	if constexpr (Reference) {
		
		// Aplicamos el functor sobre ambos operandos y realizamos la asignación para el resultado en el operando izquierdo.
		
		return (Operador.Operando.get () = Operador.Operacion.Funcion (Operador.Operando.get () , std::forward <TypeB> (Operando)));
		
		// -----------------------------------------------------------------------------
		
	}
	
	// -----------------------------------------------------------------------------
	
}

// -----------------------------------------------------------------------------

// Cerraremos el espacio de nombres para los operadores.

/// @}

} // namespace Operators

// -----------------------------------------------------------------------------

// Finalmente cerraremos el enclosed de cabecera.

#endif // CYTTEK_NAMED_OPERATORS_H

/// @}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
