
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		API : CONTAINER TRAITS FOR C++
//																		AUTHOR : 	JOSÉ RAÚL MORENO ACERO
//																		DATE : 	 	06/05/2023
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Tendremos la sección para la parte de manipulación de contenedores.

/// ----------------------------------------------------------------------------
/// 
/// @defgroup ContainerTraits Manejador de Containers
/// 
/// @brief Conjunto de sub-utilerias especializadas en la gestión de plantillas , variables de plantilla reservadas para validación de containers asi como
/// funciones que permiten generar y gestionar contenedores.
/// 
/// @details
/// 
/// El ContainerTraits o manejador de contenedores es un sub-modulo enfocado en el tratamiento de tipos para los contenedores en general , tiene las variables
/// y evaluadores constantes en tiempo de compilación que permiten determinar <b>si un tipo de dato es un contenedor válido</b> asi como también se tiene 
/// un repertorio de funciones que lo utilizan para tokenizar cadenas , destokenizar , invertir cadenas , etc. Todo esto con la finalidad de poder
/// construir más funciones que puedan realizar operaciones más especificas con grupos de cadenas en general.
/// 
/// @{
/// 
// -----------------------------------------------------------------------------

// Mediante el uso de este conjunto de utilerias es posible realizar manipulaciones en contenedores y meta-programming para poder solventar muchos
// tipos de operaciones que requieran tener varios tipos de validaciones para los contenedores que se están ocupando.

// -----------------------------------------------------------------------------
/// 
/// @file container_traits.h
/// 
/// @brief Archivo con la declaración de todo el conjunto de validadores constexpr , templates para alteración de containers asi como funciones y
/// utilerias adicionales que conllevan al uso de contenedores de cualquier tipo para su gestión y manipulación a nivel de <b>compilación</b>.
/// 
/// @details
/// 
/// Es posible definir contenedores propios mediante el uso de la plantilla @ref ContainerBase , asi también se puede validar en tiempo de
/// compilación las carácteristicas de un determinado contenedor; por ejemplo:
/// @code{.cpp}
/// 
/// 	// Crearemos nuestro propio container de la siguiente manera.
/// 
/// 	template
/// 	
/// 	// Se crea un container de nuestro propio tipo.
///		
///		std::vector <int> ContenedorInts;
///		
///		// Se puede validar si tiene el metodo clear definido.
///		
///		if constexpr (HasClear <std::vector , int>) {
///		
/// 		// Utilizamos el metodo que sabemos que si tiene implementado.
/// 		
///		
///		}
///
/// @endcode
/// 
/// De esta manera se pueden crear y gestionar cualquier tipo de container para que puedan realizarse funciones sin importar el estilo de
/// inserción del contenedor , por ejemplo @ref StringTokenizer.
/// 
/// @see StringTokenizer , StringDestokenizer
/// 
// -----------------------------------------------------------------------------

// Se comienza con la implementación de todos los elementos para los container traits.

#pragma once

// -----------------------------------------------------------------------------
/// @addtogroup ContainerTraits
/// @{
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

// Ahora lo primero que realizaremos será crear nuestro enclosed para la cabecera de este archivo.

#ifndef CONTAINER_TRAITS_H
#define CONTAINER_TRAITS_H

// Ahora pasaremos a lo siguiente con la finalidad de poder establecer los operadores a utilizar.

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// 
// 							INCLUYENDO BASES
// 							
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// Incluiremos las cabeceras principales de c.

#include <stdio.h>

// Incluiremos las cadebas para el C-Style.

#include <string.h>

// Los streams de c++ para cadenas.

#include <sstream>

// Incluiremos los algoritmos para utilizar.

#include <algorithm>

// Tenemos el tipo de dato arbitrario.

#include <any>

// Incluiremos los funcionales.

#include <functional>

// Inlcuiremos las utilerias para C++ 17.

#include <utility>

// Incluiremos el vector para elementos.

#include <vector>

// Incluiremos el tuple para poder validar los tipos de datos.

#include <tuple>

// Incluiremos también type_traits para meta-programming.

#include <type_traits>

// Ahora incluiremos el modulo para los operadores nombrados con la finalidad de poder crear
// nuevos operadores con este modulo también.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							NAMED OPERATORS
// 							
// -----------------------------------------------------------------------------

// Incluiremos el modulo respectivo para poder importar nuestros named operators.

#include "named_operators.hpp"

// Utilizaremos el espacio de nombres respectivo para los operadores.
	
using namespace Operators;

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		CONTAINER TRAITS
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Empezaremos por la declaración de todos los gestionadores y validadores de contenedores a nivel interno dentro del espacio de nombres especifico
// para posteriormente definir todos los validadores a nivel publico los cuales podran accederse desde cualquier lugar donde se incluya este 
// archivo en especifico.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							INTERNAL NAMESPACE
// 							
// -----------------------------------------------------------------------------

// Estableceremos un pequeño espacio de nombres para definir todos los validadores y estructuras a nivel interno que se estarán utilizando.

/// @cond ContainerTraitsInternal

namespace ContainerTraits {

// Primero definiremos los typedefs genericos los cuales permiten realizar la validación de los tipos de contenedores a los que se hacen referencia
// a modo de funcionar como un wrapper interno que determina los valores de template a utilizar para cierto container.

// -----------------------------------------------------------------------------
// 
// 							TEMPLATE CONTAINER TYPE
// 							
// -----------------------------------------------------------------------------

// Empezaremos por la declaración de la estructura general para la validación de cualquier tipo de container a partir de la plantilla de clase
// y posteriormente incluir todos los parametros de plantilla que se especifiquen.

template <template <typename ...> typename TTemplate , typename ... TValues>
struct ContainerType {
	
	// Se incluye el typedef para el tipo de container actual al que estaremos haciendo referencia.
	
	typedef TTemplate <TValues ...> container_type;
	
	// -----------------------------------------------------------------------------
		
};

// -----------------------------------------------------------------------------

// Ahora tendremos una especialización para este template donde está definido el tipo en especifico para cuando se tiene un solo argumento
// en los TValues , por lo que tenemos esta especializacion.

// Tenemos la especialización para 1 parametro de container establecido en defecto a un std::any.

template <template <typename> typename TTemplate>
struct ContainerType <TTemplate> { typedef TTemplate <std::any> container_type; };

// Ahora definiremos todos las variables de plantilla que permiten realizar validaciones en tiempo de compilación para saber si un tipo de contenedor
// es válido y cumple con las condiciones establecidas.

// -----------------------------------------------------------------------------
// 
// 						TEMPLATE VARIABLES VALIDATORS
// 							
// -----------------------------------------------------------------------------

// Tenemos el conjunto de variables de validación a nivel interno que determinan si el template de container en especifico con los values de parametro
// indicados cumplen o no con el criterio en especifico que se está válidando.

// -----------------------------------------------------------------------------

// Comenzaremos entonces con el primer validador para poder determinar si tiene el campo value type.

template <typename TContainer , typename = void>
inline constexpr bool HasTypeMember = false;

// Implementaremos la especialización del validador de tipo miembro de una plantilla de clase.

template <typename TContainer>
inline constexpr bool HasTypeMember <TContainer , std::void_t <typename TContainer::value_type>> = true;

// -----------------------------------------------------------------------------

// El siguiente es el validador para sabe si tiene definido el tipo para los iteradores.

template <typename TContainer , typename = void>
inline constexpr bool HasIterator = false;

// Ahora pasaremos a la implementación del validador para cuando se tenga el iterator contenido como un tipo miembro.

template <typename TContainer>
inline constexpr bool HasIterator <TContainer , std::void_t <typename TContainer::iterator>> = true;

// Ahora a continuación tenemos el conjunto para lo relacionado con los tamaños del container.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							SIZE / EMPTY
// 							
// -----------------------------------------------------------------------------

// A continuación el validador para determinar si tiene el metodo "size" definido el container.

template <typename TContainer , typename = void>
inline constexpr bool HasSize = false;

// Continuando con la especialización de los validadores tenemos ahora al validador para saber si tiene el metodo size implementado.

template <typename TContainer>
inline constexpr bool HasSize <TContainer , std::void_t <decltype (std::declval <TContainer> ().size ())>> = true;

// -----------------------------------------------------------------------------

// Para poder validar si se tiene el metodo "at" definido en un determinado container tenemos este otro metodo.

template <typename TContainer , typename = void>
inline constexpr bool HasAt = false;

// Para determinar si una plantilla tiene el metodo at definido se tiene la especialización siguiente.

template <typename TContainer>
inline constexpr bool HasAt <TContainer , std::void_t <decltype (std::declval <TContainer> ().at (size_t { }))>> = true;

// -----------------------------------------------------------------------------

// Para poder validar si se tiene el metodo "count" definido en un determinado container tenemos este otro metodo.

template <typename TContainer , typename = void>
inline constexpr bool HasCount = false;

// Para determinar si una plantilla tiene el metodo count definido se tiene la especialización siguiente.

template <typename TContainer>
inline constexpr bool HasCount <TContainer ,
	std::void_t <decltype (std::declval <TContainer> ().count (std::declval <typename TContainer::key_type> ()))>> = true;

// -----------------------------------------------------------------------------

// Para poder validar si se tiene el metodo "empty" definido en un determinado container tenemos este otro metodo.

template <typename TContainer , typename = void>
inline constexpr bool HasEmpty = false;

// Para determinar si una plantilla tiene el metodo empty definido se tiene la especialización siguiente.

template <typename TContainer>
inline constexpr bool HasEmpty <TContainer , std::void_t <decltype (std::declval <TContainer> ().empty ())>> = true;

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 								BEGIN / END
// 							
// -----------------------------------------------------------------------------

// Tenemos el caso para validar que se dispongan de los metodos begin y end en el container actual.

template <typename TContainer , typename = void>
inline constexpr bool HasBeginEnd = false;

// Ahora para validar que una determinada plantilla de clase tiene el metodo begin y end definido.

template <typename TContainer>
inline constexpr bool HasBeginEnd <TContainer , std::enable_if_t <std::is_same_v <std::void_t <
	
	// Se valida que la plantilla de clase tenga los metodos begin y end.
	
	decltype (std::declval <TContainer> ().begin ()) , decltype (std::declval <TContainer> ().end ())
	
	// -----------------------------------------------------------------------------
	
> , void>>> = true;

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							ERASE / CLEAR ELEMENTS
// 							
// -----------------------------------------------------------------------------

// Tenemos el siguiente caso para el metodo Erase en los containers que se están validando.

template <typename TContainer , typename = void>
inline constexpr bool HasErase = false;

// Ahora para cuando se tiene el metodo erase definido tenemos la siguiente especialización.

template <typename TContainer>
inline constexpr bool HasErase <TContainer , std::void_t <
	
	// Se valida que existe el metodo "emplace" con el argumento del iterador y el tipo de valor del container mediante void_t.
	
	// decltype (static_cast <typename TTemplate <TValue>::iterator (TTemplate <TValue>:: *) (typename TTemplate <TValue>::iterator)>) , TTemplate <TValue> , typename TTemplate <TValue>::iterator
	
	decltype (std::declval <TContainer> ().erase (std::declval <typename TContainer::iterator> ()))
	
	// -----------------------------------------------------------------------------
	
>> = true;

// -----------------------------------------------------------------------------

// El siguiente es para la validación del metodo Clear en los containers especificados.

template <typename TContainer , typename = void>
inline constexpr bool HasClear = false;

// Si se tiene el metodo clear con la siguiente especialización de la plantilla de variable.

template <typename TContainer>
inline constexpr bool HasClear <TContainer , std::void_t <decltype (std::declval <TContainer> ().clear ())>> = true;

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 					INSERT / EMPLACE / PUSH ELEMENTS
// 							
// -----------------------------------------------------------------------------

// Tenemos primero el caso para el metodo emplace el cuál puede estar definido en el container de multiples formas.

template <typename TContainer , typename = void>
inline constexpr bool HasEmplace = false;

// Ahora para el conjunto de metodos que insertan elementos tenemos primero el metodo emplace y su implementación.

template <typename TContainer>
inline constexpr bool HasEmplace <TContainer ,
	std::void_t <decltype (std::declval <TContainer> ().emplace (std::declval <typename TContainer::value_type> ()))>> = true;

// -----------------------------------------------------------------------------

// Tenemos el caso para el metodo emplace con la posición del iterador donde insertar el elemento.

template <typename TContainer , typename = void>
inline constexpr bool HasEmplacePosition = false;

// Ahora implementamos la validación para cuando se tiene  el metodo emplace con su respectiva validación de invocación.

template <typename TContainer>
inline constexpr bool HasEmplacePosition <TContainer , std::enable_if_t <std::is_invocable_v <
	
	// Se valida que existe el metodo "emplace" con el argumento del iterador y el tipo de valor del container mediante is_invocable.

	decltype (&TContainer::template emplace <typename TContainer::value_type>) , TContainer ,
	typename TContainer::iterator , typename TContainer::value_type
	
	// -----------------------------------------------------------------------------
	
> , void>> = true;

// -----------------------------------------------------------------------------

// Tenemos el siguiente caso para cuando se tiene emplace hasta el final del container.

template <typename TContainer , typename = void>
inline constexpr bool HasEmplaceBack = false;

// Para el caso de emplace back comprobaremos que exista dicho metodo con el tipo de valor como argumento.

template <typename TContainer>
inline constexpr bool HasEmplaceBack <TContainer , 
	std::void_t <decltype (std::declval <TContainer> ().emplace_back (std::declval <typename TContainer::value_type> ()))>> = true;

// -----------------------------------------------------------------------------

// Tenemos el caso para cuando el container tiene definido el metodo "insert".

template <typename TContainer , typename = void>
inline constexpr bool HasInsert = false;

// Ahora pasaremos a la implementación del validador para los insert con el valor simplemente.

template <typename TContainer>
inline constexpr bool HasInsert <TContainer ,
	std::void_t <decltype (std::declval <TContainer> ().insert (std::declval <typename TContainer::value_type> ()))>> = true;

// -----------------------------------------------------------------------------

// Para el caso con el metodo "insert" en una posición determinada se tiene el siguiente metodo.

template <typename TContainer , typename = void>
inline constexpr bool HasInsertPosition = false;

// De igual manera para el caso de insert y la posición en donde insertar y el valor a insertar se tiene su especialización de la siguiente forma.

template <typename TContainer>
inline constexpr bool HasInsertPosition <TContainer ,
	std::void_t <decltype (std::declval <TContainer> ().insert (std::declval <typename TContainer::iterator> () ,
	std::declval <typename TContainer::value_type> ()))>> = true;

// -----------------------------------------------------------------------------

// Tenemos el validador para el caso del metodo "push" en algunos tipos de containers (Pilas , colas , etc).

template <typename TContainer , typename = void>
inline constexpr bool HasPush = false;

// Ahora para el caso de push y el valor a insertar tenemos esta implementación.

template <typename TContainer>
inline constexpr bool HasPush <TContainer ,
	std::void_t <decltype (std::declval <TContainer> ().push (std::declval <typename TContainer::value_type> ()))>> = true;

// -----------------------------------------------------------------------------

// Tenemos el validador para el caso del metodo "pushback" en algunos containers (vector).

template <typename TContainer , typename = void>
inline constexpr bool HasPushBack = false;

// De la misma manera para el caso de push back comprobaremos que se tenga dicho metodo invocando a la función en la especialización.

template <typename TContainer>
inline constexpr bool HasPushBack <TContainer ,
	std::void_t <decltype (std::declval <TContainer> ().push_back (std::declval <typename TContainer::value_type> ()))>> = true;

// -----------------------------------------------------------------------------
// 
// 							POP ELEMENTS
// 							
// -----------------------------------------------------------------------------

// Ahora pasaremos al validador para el caso del metodo "pop" en los containers que lo soporten.

template <typename TContainer , typename = void>
inline constexpr bool HasPop = false;

// Lo siguiente es para la defininición del concept para la validación de nuestra operación pop.

template <typename TContainer>
inline constexpr bool HasPop <TContainer , std::void_t <decltype (std::declval <TContainer> ().pop ())>> = true;

// -----------------------------------------------------------------------------

// Tenemos el validador para el metodo "popback" de ciertos tipos de containers.

template <typename TContainer , typename = void>
inline constexpr bool HasPopBack = false;

// Por otro lado para el caso de que tenga la definición de la operación siguiente pop_back.

template <typename TContainer>
inline constexpr bool HasPopBack <TContainer , std::void_t <decltype (std::declval <TContainer> ().pop_back ())>> = true;

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							ITERABLES CONTAINERS
// 							
// -----------------------------------------------------------------------------

// Tenemos el validador para cuando el determinado container tiene el comportamiento de "iterable" por lo que es posible iterar sobre el.

template <typename TContainer , typename = void>
inline constexpr bool IsIterable = false;

// Definiremos la especialización de la plantilla que determina si un container determinado es Iterable , para esto debe cumplir ciertos
// requisitos que se marcan en la especialización.

template <typename TContainer>
inline constexpr bool IsIterable <TContainer , std::enable_if_t <
	
	// Definiremos el concepto para que esta variable tenga válides y determine que un container puede ser iterable. Las condiciones son :
	// 		Tener un tipo de dato llamado : iterator.
	// 		Tener ambos metodos , begin y end definidos.
	// 		Los tipos de iterator y el devuelto por los metodos begin y end deben coincidir.
	
	HasIterator <TContainer> &&
	HasBeginEnd <TContainer> &&
	std::is_same_v <typename TContainer::iterator , decltype (std::declval <TContainer> ().begin ())> &&
	std::is_same_v <typename TContainer::iterator , decltype (std::declval <TContainer> ().end ())>
	
	// -----------------------------------------------------------------------------
	
>> = true;

// -----------------------------------------------------------------------------

// Pasaremos a cerrar este espacio de nombres internal para poder seguir con la creación de todos los validadores a nivel general.

} // namespace ContainerTraits

/// @endcond

// -----------------------------------------------------------------------------

// Ahora pasaremos a la parte donde se declaran las estructuras auxiliares que determinan el comportamiento de los metodos para modificar y
// alterar los contenedores.

// -----------------------------------------------------------------------------
// 
// 							CONTAINER TYPES
// 							
// -----------------------------------------------------------------------------

// Tenemos para empezar el template type para poder definir un tipo de container a patir del la clase parametrizable o plantilla de clase asi
// como todos los tipos de argumentos de plantilla utilizados.

// -----------------------------------------------------------------------------

// Declaramos nuestro template de tipo para este traits interno.

/// ----------------------------------------------------------------------------
/// 
/// @brief Plantilla de Tipo que determina el tipo de <b>Container</b> a partir de la plantilla de clase y sus tipos de cada argumento de plantilla.
/// 
/// @tparam 	TTemplate 		Plantilla de clase a utilizar como base para el container.
/// @tparam 	TValues 		Tipos de datos de la plantilla de clase que recibe como argumentos de plantilla.
/// 
/// @details
/// 
/// Esta plantilla de tipo funciona como un wrapper para definir el tipo de "Container" al que se está haciendo referencia con los argumentos
/// que se están estableciendo <b>(Solo en caso de tenerlos)</b>.
/// 
/// @note
/// En caso de no tener ningún argumento en el parametro <b class="paramname">TValues</b> se establece el argumento por default en <b>std::any</b>.
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
using ContainerType = typename ContainerTraits::ContainerType <TTemplate , TValues ...>::container_type;

// Ahora pasaremos a la declaración de implementación de todos los validadores que se estarán utilizando para los propositos generales.

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// 
// 							CONTAINER VALIDATORS
// 							
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// Declaramos todo el conjunto de variables de validación que realizan la tarea de comprobar que un determinado template (container) tenga o cumpla
// con ciertas carácteristicas importantes entre las que tenemos las siguientes :

// -----------------------------------------------------------------------------

// Declaramos y definimos la base para la válidación de value_type en un tipo de dato.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que válida en tiempo de compilación si una plantilla de clase tiene definido el tipo de valor contenido mediante
/// el uso de la palabra <b>(value_type)</b> como un typedef que es miembro de dicho tipo de contenedor.
/// 
/// @tparam 		TTemplate 		Tipo de plantilla de clase a validar.
/// @tparam 		TValues 		[opcional] Tipos de valores que tendría la plantilla.
/// 
/// @details
/// 
/// Por medio de esta variable parametrizable es posible conocer si un tipo de contenedor tiene definido el typedef asociado al tipo de dato contenido
/// dentro del mismo container. Tenemos por ejemplo :
/// @code{.cpp}
/// 
/// 	// Plantilla de clase que cumple con un typedef de su tipo de dato contenido.
/// 	
/// 	template <typename TValue>
/// 	class ClaseEjemplo {
/// 	
/// 		public :
/// 			
/// 			// Typedef para el tipo de dato actual Contenido en esta clase.
/// 			
/// 			typedef TValue value_type;	
/// 	
/// 	};
/// 	
/// 	// La válidación de esta clase.
/// 	
/// 	constexpr bool ClaseIsValid = HasTypeMember <ClaseEjemplo>;
/// 	
/// 	// ClaseIsValid = true
/// 
/// @endcode
/// 
/// @pre
/// Todos los templates para utilizar como Containers validos en estas utilerias tienen que tener este typedef declarado en su contenido , asi como los
/// de la biblioteca estandar <b>(STL)</b>
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
inline constexpr bool HasTypeMember = ContainerTraits::HasTypeMember <ContainerType <TTemplate , TValues ...>>;

// Ahora tenemos el validador del tipo de dato iterator dentro de la plantilla de clase.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que válida en tiempo de compilación si una plantilla de clase tiene definido el tipo de iterador utilizado
/// , con el uso del nombre <b>(iterator)</b> como un typedef que es miembro de dicho tipo de contenedor.
/// 
/// @tparam 		TTemplate 		Tipo de plantilla de clase a validar.
/// @tparam 		TValues 		[opcional] Tipos de valores que tendría la plantilla.
/// 
/// @details
/// 
/// Con esta plantilla se determina si un tipo de plantilla en cuestión tiene un miembro de tipo definido que tenga por nombre (iterator)
/// y por tanto que permita obtener información sobre las posiciones de cada elemento dentro del container.
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
inline constexpr bool HasIterator = ContainerTraits::HasIterator <ContainerType <TTemplate , TValues ...>>;

// -----------------------------------------------------------------------------

// Ahora para acceder al tamaño del container se tiene la validación siguiente.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que válida en tiempo de compilación si una plantilla de clase tiene definido el metodo <b>size</b> para
/// obtener la cantidad de elementos en dicha plantilla.
/// 
/// @tparam 		TTemplate 		Tipo de plantilla de clase a validar.
/// @tparam 		TValues 		[opcional] Tipos de valores que tendría la plantilla.
/// 
/// @details
/// 
/// Utilizando esta plantilla de variable se puede determinar si una plantilla de clase cumple con el requisito de tener definido un metodo
/// de nombre <b>size</b> que devuelva la cantidad de elementos en dicho container.
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
inline constexpr bool HasSize = ContainerTraits::HasSize <ContainerType <TTemplate , TValues ...>>;

// Ahora para acceder a un elemeento en particular por su posicion del container se tiene la validación siguiente.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que válida en tiempo de compilación si una plantilla de clase tiene definido el metodo <b>at</b> para
/// obtener la un elemento en una determinada posición.
/// 
/// @tparam 		TTemplate 		Tipo de plantilla de clase a validar.
/// @tparam 		TValues 		[opcional] Tipos de valores que tendría la plantilla.
/// 
/// @details
/// 
/// Utilizando esta plantilla de variable se puede determinar si una plantilla de clase cumple con el requisito de tener definido un metodo
/// de nombre <b>at</b> que devuelva un elemento en una determinada ubicación.
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
inline constexpr bool HasAt = ContainerTraits::HasAt <ContainerType <TTemplate , TValues ...>>;

// Ahora para poder validar cuantos elementos de un valor tiene tenemos lo siguiente.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que  válida en tiempo de compilación si una plantilla de clase tiene definido el metodo <b>count</b> para
/// obtener la cantidad de elementos que son iguales al especificado.
/// 
/// @tparam 		TTemplate 		Tipo de plantilla de clase a validar.
/// @tparam 		TValues 		[opcional] Tipos de valores que tendría la plantilla.
/// 
/// @details
/// 
/// Utilizando esta plantilla de variable se puede determinar si una plantilla de clase cumple con el requisito de tener definido un metodo
/// de nombre <b>count</b> que devuelva un valor entero con la cantidad de elementos de ese valor especifico.
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
inline constexpr bool HasCount = ContainerTraits::HasCount <ContainerType <TTemplate , TValues ...>>;

// Ahora para determinar si está vacio o no un determinado contenedor tenemos el validador de empty.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que válida en tiempo de compilación si una plantilla de clase tiene definido el metodo <b>empty</b> para
/// determinar si un container está <b>vacio</b> o no.
/// 
/// @tparam 		TTemplate 		Tipo de plantilla de clase a validar.
/// @tparam 		TValues 		[opcional] Tipos de valores que tendría la plantilla.
/// 
/// @details
/// 
/// Esta variable nos permite saber si una plantilla de clase tiene definido entre sus metodos uno con el nombre de <b>"empty"</b> que devuelva
/// un bool para saber si un determinado container está vacio o no.
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
inline constexpr bool HasEmpty = ContainerTraits::HasEmpty <ContainerType <TTemplate , TValues ...>>;

// Para daterminar si una plantilla de clase tiene los metodos begin y end respectivamente se tiene la variable siguiente.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que válida en tiempo de compilación si una plantilla de clase tiene definido los metodos de iteración
/// <b>begin</b> y <b>end</b> para poder considerar a la plantilla como iterable.
/// 
/// @tparam 		TTemplate 		Tipo de plantilla de clase a validar.
/// @tparam 		TValues 		[opcional] Tipos de valores que tendría la plantilla.
/// 
/// @details
/// 
/// Con esta plantilla podemos saber si un determinado contenedor tiene habilitados/definidos los metodos begin y end los cuales devuelven
/// un iterador al inicio y al past-end de dicho contenedor.
/// 
/// @note
/// Es requisito para cumplir con el comportamiento @ref IsIterable que la plantilla en cuestión tenga estos metodos y devuelvan el tipo
/// de dato determinado por <b>iterator</b>.
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
inline constexpr bool HasBeginEnd = ContainerTraits::HasBeginEnd <ContainerType <TTemplate , TValues ...>>;

// Para determinar si existe el metodo clear definido dentro del container.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que determina en tiempo de compilación si una plantilla de clase tiene definido el metodo "clear".
/// 
/// @tparam 		TTemplate 		Tipo de plantilla de clase a validar.
/// @tparam 		TValues 		[opcional] Tipos de valores que tendría la plantilla.
/// 
/// @details
/// 
/// Con esta plantilla es posible determinar cuando un tipo de dato parametrizable cuenta con un metodo clear definido que permita
/// como su nombre lo indica , "limpiar" todos los elementos en un determinado contenedor.
/// 
/// @pre
/// El metodo clear es relativamente <b>opcional</b> en la mayoria de los contenedores válidos , siempre que sea <b class="paramname">
/// Removible</b> el contenedor seguirá siendo válido (@ref IsRemovible).
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
inline constexpr bool HasClear = ContainerTraits::HasClear <ContainerType <TTemplate , TValues ...>>;

// El siguiente es la variable para la validación del metodo Emplace en tiempo de compilación.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que determina en tiempo de compilación si una plantilla de clase tiene permitido insertar elementos
/// mediante el metodo <b>"emplace"</b>.
/// 
/// @tparam 		TTemplate 		Tipo de plantilla de clase a validar.
/// @tparam 		TValues 		[opcional] Tipos de valores que tendría la plantilla.
/// 
/// @details
/// 
/// Esta plantilla de variable permite determinar en tiempo de compilación si una determinada plantilla de clase tiene definido el metodo
/// "emplace" para poder construir un elemento nuevo del tipo determinado por <b class="paramname">TValue</b> e <b>insertarlo</b> en dicha
/// plantilla como un nuevo elemento.
/// 
/// @pre
/// Los metodos (<b>"emplace" , "insert" , "push"</b>) son necesarios (<i>por lo menos uno de ellos</i>) para que la plantilla de contenedor sea
/// "insertable" y por tanto pueda ser válida para operaciones como la Tokenización por ejemplo. 
/// 
/// @note
/// El tipo de dato <b class="paramname">TValue</b> debe ser <b>Construible</b> de manera trivial y con copia/move constructor.
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
inline constexpr bool HasEmplace = ContainerTraits::HasEmplace <ContainerType <TTemplate , TValues ...>>;

// Para validar si tiene el metodo de emplace con la posición especifica.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que determina en tiempo de compilación si una plantilla de clase tiene permitido insertar elementos
/// mediante el metodo <b>"emplace"</b> utilizando la sobrecarga del metodo con la posición (iterador) en donde insertar.
/// 
/// @tparam 		TTemplate 		Tipo de plantilla de clase a validar.
/// @tparam 		TValues 		[opcional] Tipos de valores que tendría la plantilla.
/// 
/// @details
/// 
/// Esta plantilla de variable permite determinar en tiempo de compilación si una determinada plantilla de clase tiene definido el metodo
/// "emplace" para poder construir un elemento nuevo del tipo determinado por <b class="paramname">TValue</b> e <b>insertarlo</b> en dicha
/// plantilla como un nuevo elemento en la posición que esté marcada mediante un <b>iterator</b>.
/// 
/// @pre
/// Los metodos (<b>"emplace" , "insert" , "push"</b>) son necesarios (<i>por lo menos uno de ellos</i>) para que la plantilla de contenedor sea
/// "insertable" y por tanto pueda ser válida para operaciones como la Tokenización por ejemplo.
/// 
/// @note
/// El tipo de dato <b class="paramname">TValue</b> debe ser <b>Construible</b> de manera trivial y con copia/move constructor.
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
inline constexpr bool HasEmplacePosition = ContainerTraits::HasEmplacePosition <ContainerType <TTemplate , TValues ...>>;

// Ahora para insertar por la parte final del container.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que determina en tiempo de compilación si una plantilla de clase tiene permitido insertar elementos
/// mediante el metodo <b>"emplace_back"</b>.
/// 
/// @tparam 		TTemplate 		Tipo de plantilla de clase a validar.
/// @tparam 		TValues 		[opcional] Tipos de valores que tendría la plantilla.
/// 
/// @details
/// 
/// Esta plantilla de variable permite determinar en tiempo de compilación si una determinada plantilla de clase tiene definido el metodo
/// "emplace_back" para poder construir un elemento nuevo del tipo determinado por <b class="paramname">TValue</b> e <b>insertarlo</b> en dicha
/// plantilla por la parte final del conteneor.
/// 
/// @pre
/// Los metodos (<b>"emplace" , "insert" , "push"</b>) son necesarios (<i>por lo menos uno de ellos</i>) para que la plantilla de contenedor sea
/// "insertable" y por tanto pueda ser válida para operaciones como la Tokenización por ejemplo.
/// 
/// @note
/// El tipo de dato <b class="paramname">TValue</b> debe ser <b>Construible</b> de manera trivial y con copia/move constructor.
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
inline constexpr bool HasEmplaceBack = ContainerTraits::HasEmplaceBack <ContainerType <TTemplate , TValues ...>>;

// Tenemos el HasInsert para contemplar también el metodo insert que puede ser tanto al final como en una posición determinada.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que determina en tiempo de compilación si una plantilla de clase tiene permitido insertar elementos
/// mediante el metodo <b>"insert"</b>.
/// 
/// @tparam 		TTemplate 		Tipo de plantilla de clase a validar.
/// @tparam 		TValues 		[opcional] Tipos de valores que tendría la plantilla.
/// 
/// @details
/// 
/// El metodo insert a diferencia del metodo emplace , este <b>NO CRÉA</b> un nuevo elemento del tipo especificado por el parametro
/// <b class="paramname">TValue</b> , si no más bien copia o mueve un elemento (dependiendo la semántica utilizada) y lo inserta en el
/// container establecido por la plantilla <b class="paramname">TTemplate</b>.
/// 
/// @pre
/// Los metodos (<b>"emplace" , "insert" , "push"</b>) son necesarios (<i>por lo menos uno de ellos</i>) para que la plantilla de contenedor sea
/// <b style="color: var(--primary-color);">"insertable"</b> y por tanto pueda ser válida para operaciones como la Tokenización por ejemplo. 
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
inline constexpr bool HasInsert = ContainerTraits::HasInsert <ContainerType <TTemplate , TValues ...>>;

// Tenemos el siguiente para el metodo insert con la posición establecida.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que determina en tiempo de compilación si una plantilla de clase tiene permitido insertar elementos
/// mediante el metodo <b>"insert"</b> con la sobrecarga donde se establece la posición.
/// 
/// @tparam 		TTemplate 		Tipo de plantilla de clase a validar.
/// @tparam 		TValues 		[opcional] Tipos de valores que tendría la plantilla.
/// 
/// @details
/// 
/// El metodo insert a diferencia del metodo emplace , este <b>NO CRÉA</b> un nuevo elemento del tipo especificado por el parametro
/// <b class="paramname">TValue</b> , si no más bien copia o mueve un elemento (dependiendo la semántica utilizada) y lo inserta en el
/// container establecido por la plantilla <b class="paramname">TTemplate</b>.
/// 
/// A diferencia de @ref HasInsert , esta plantilla válida que exista un metodo insert que recive como parametros el iterador a la posición
/// donde se va a insertar el nuevo elemento y el valor a insertar.
/// 
/// @pre
/// Los metodos (<b>"emplace" , "insert" , "push"</b>) son necesarios (<i>por lo menos uno de ellos</i>) para que la plantilla de contenedor sea
/// <b style="color: var(--primary-color);">"insertable"</b> y por tanto pueda ser válida para operaciones como la Tokenización por ejemplo. 
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
inline constexpr bool HasInsertPosition = ContainerTraits::HasInsertPosition <ContainerType <TTemplate , TValues ...>>;

// Ahora tenemos la plantilla para validar el metodo erase en un container.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que determina en tiempo de compilación si una plantilla de clase tiene permitido eliminar elementos
/// mediante el metodo <b>"erase"</b> con la posición de dicho en un <b>iterator</b> de parametro.
/// 
/// @tparam 		TTemplate 		Tipo de plantilla de clase a validar.
/// @tparam 		TValues 		[opcional] Tipos de valores que tendría la plantilla.
/// 
/// @details
/// 
/// El metodo erase elimina un determinado elemento mediante la posición dentro del Container. Esta posición está determinada por el valor
/// que tenga un <b>iterator</b>. Para buscar un determinado valor en el Container se puede usar los algoritmos de find , find_if , etc , utilizando
/// los valores devueltos por begin y end en el container.
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
inline constexpr bool HasErase = ContainerTraits::HasErase <ContainerType <TTemplate , TValues ...>>;

// Ahora pasaremos al metodo push para conocer si está definida.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que determina en tiempo de compilación si una plantilla de clase tiene permitido añadir elementos a su contenido
/// utilizando un metodo llamado <b>"push"</b>.
/// 
/// @tparam 		TTemplate 		Tipo de plantilla de clase a validar.
/// @tparam 		TValues 		[opcional] Tipos de valores que tendría la plantilla.
/// 
/// @details
/// 
/// El metodo push es muchas veces incorporado a los containers (por ejemplo STL containers) para poder añadir elementos respetando el tipo
/// de contenedor en cuestión. Por ejemplo para el caso de una pila colocaría el elemento al final de la pila o tope , para el caso de una cola
/// lo colocaría por el final.
/// 
/// @pre
/// Los metodos (<b>"emplace" , "insert" , "push"</b>) son necesarios (<i>por lo menos uno de ellos</i>) para que la plantilla de contenedor sea
/// <b style="color: var(--primary-color);">"insertable"</b> y por tanto pueda ser válida para operaciones como la Tokenización por ejemplo. 
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
inline constexpr bool HasPush = ContainerTraits::HasPush <ContainerType <TTemplate , TValues ...>>;

// Ahora pasamos a la definición de pushback.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que determina en tiempo de compilación si una plantilla de clase tiene permitido añadir elementos a su contenido
/// utilizando un metodo llamado <b>"push_back"</b>.
/// 
/// @tparam 		TTemplate 		Tipo de plantilla de clase a validar.
/// @tparam 		TValues 		[opcional] Tipos de valores que tendría la plantilla.
/// 
/// @details
/// 
/// El metodo push_back suele tenerlo los contenedores que permitan insertar elementos en cualquier lugar del container , con este metodo se
/// asegura que el nuevo elemento se insertará por el final de dicho contenedor.
/// 
/// @pre
/// Los metodos (<b>"emplace" , "insert" , "push"</b>) son necesarios (<i>por lo menos uno de ellos</i>) para que la plantilla de contenedor sea
/// <b style="color: var(--primary-color);">"insertable"</b> y por tanto pueda ser válida para operaciones como la Tokenización por ejemplo. 
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
inline constexpr bool HasPushBack = ContainerTraits::HasPushBack <ContainerType <TTemplate , TValues ...>>;

// Ahora pasaremos al metodo pop para conocer si está definida.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que determina en tiempo de compilación si una plantilla de clase tiene permitido quitar elementos en el
/// container mediante el uso de <b>"pop"</b>.
/// 
/// @tparam 		TTemplate 		Tipo de plantilla de clase a validar.
/// @tparam 		TValues 		[opcional] Tipos de valores que tendría la plantilla.
/// 
/// @details
/// 
/// Los contenedores como por ejemplo la Pila (Stack) y la Cola (Queue) tienen metodos especificos para poder operar con determinado mecanismo
/// , por ejemplo <b>LIFO</b> y <b>FIFO</b>. Por consiguiente es importante también denotar si estos elementos tienen incorporados el metodo
/// pop para poder eliminar cada elemento siguiendo su estilo.
/// 
/// @pre
/// Los metodos (<b>"erase" , "pop" , "clear"</b>) son necesarios (<i>por lo menos uno de ellos</i>) para que la plantilla de contenedor sea
/// <b style="color: var(--primary-color);">"eliminable"</b> y por tanto pueda ser válida para determinadas operaciones. 
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
inline constexpr bool HasPop = ContainerTraits::HasPop <ContainerType <TTemplate , TValues ...>>;

// Ahora pasamos a la definición de popback.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que determina en tiempo de compilación si una plantilla de clase tiene permitido quitar elementos del container
/// utilizando un metodo llamado <b>"pop_back"</b>.
/// 
/// @tparam 		TTemplate 		Tipo de plantilla de clase a validar.
/// @tparam 		TValues 		[opcional] Tipos de valores que tendría la plantilla.
/// 
/// @details
/// 
/// El metodo pop_back suele tenerlo los contenedores como la <b>deque</b> para poder eliminar elementos directamente desde el final. A diferencia
/// de otros contenedores que solamente pueden eliminar por el frente o por el final de manera exclusiva.
/// 
/// @pre
/// Los metodos (<b>"erase" , "pop" , "clear"</b>) son necesarios (<i>por lo menos uno de ellos</i>) para que la plantilla de contenedor sea
/// <b style="color: var(--primary-color);">"eliminable"</b> y por tanto pueda ser válida para determinadas operaciones.
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
inline constexpr bool HasPopBack = ContainerTraits::HasPopBack <ContainerType <TTemplate , TValues ...>>;

// -----------------------------------------------------------------------------

// Ahora pasaremos con los validadores de comportamientos para los containers.

// -----------------------------------------------------------------------------
// 
// 							VALIDADORES GENERALES
// 							
// -----------------------------------------------------------------------------

// Tenemos la siguiente lista de ellos.

/// ----------------------------------------------------------------------------
/// 
/// @name Container Validators
/// 
/// @brief Variables de plantillas que determinan si un contenedor es válido mediante varios criterios de Selección con las técnicas SFINAE.
/// 
/// @details
/// 
/// Se tiene un conjunto de variables de validación en tiempo de compilación que válidan correctamente el comportamiento de un container
/// permitindo saber si tiene o no determinadas propiedades y metodos definidos que permitan operar con dicho contenedor génerico.
/// 
/// @{
/// 
// -----------------------------------------------------------------------------

// Ahora comenzamos con la definición de cada uno de ellos , comenzando primero por el siguiente.

// -----------------------------------------------------------------------------

// Tenemos el validador para determinar si un determinado container es considerado Iterable.

/// ----------------------------------------------------------------------------
/// 
/// @brief Plantilla de Variable que determina en <b>tiempo de compilación</b> si una determinada plantilla de clase tiene los metodos
/// <b style="color: var(--primary-color);">begin , end</b> definidos al momento de instanciar dicha plantilla con el tipo de valor contenido
/// determinado por <b class="paramname">TValue</b>.
/// 
/// @tparam 	TTemplate 	Plantilla de Clase a validar.
/// @tparam 	TValues 	[opcional] Tipos de valores que tendría la plantilla.
/// 
/// @details
/// 
/// La implementación de esta variable de validación es como la siguiente.
/// <b>Valor Inicial :</b>
/// @code{.cpp}
/// = (
/// 	
/// 	HasIterator <TTemplate , TValue> &&
///		HasBeginEnd <TTemplate , TValue> &&
///		std::is_same_v <typename TTemplate <TValue>::iterator , decltype (std::declval <TTemplate <TValue>> ().begin ())> &&
///		std::is_same_v <typename TTemplate <TValue>::iterator , decltype (std::declval <TTemplate <TValue>> ().end ())>
/// 	
/// )
/// @endcode
/// 
/// Este validador realiza la llamada al metodo <b>begin () , end ()</b> de la plantilla de clase <b class="paramname">TTemplate</b> especializada
/// con el tipo de dato indicado. Si el metodo existe entonces esta variable devolverá un valor igual a <span style="color: var(--fragment-keyword);">true</span>
/// , de lo contrario devolverá <span style="color: var(--fragment-keyword);">false</span>.
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
inline constexpr bool IsIterable = ContainerTraits::IsIterable <ContainerType <TTemplate , TValues ...>>;

// Ahora para determinar si es insertable mediante los metodos de inserción permitidos para los contenedores.

/// ----------------------------------------------------------------------------
/// 
/// @brief Plantilla de Variable que determina en <b>tiempo de compilación</b> si una determinada plantilla de clase es insertable mediante los metodos de 
/// inserción comúnmente utilizados.
/// 
/// @tparam 	TTemplate 	Plantilla de Clase a validar.
/// @tparam 	TValues 		[opcional] Tipos de valores que tendría la plantilla.
/// 
/// @details
/// 
/// Este validador realiza la comprobación de la plantilla utilizando las variables de válidación respectivas. Para que una plantilla de clase séa considerada
/// insertable debe cumplir con alguna de las siguientes carácteristicas :
/// 	<ul>
/// 		<li>Tener el metodo <b>emplace/emplaceback</b> definido.
/// 		<li>Tener el metodo <b>insert</b> definido.
/// 		<li>Tener el metodo <b>push/push_back</b> definido.
/// 	</ul>
/// 
/// Tener esta validación en true es un requisito para poder hacer uso del <i>AlterContainer</i> para poder hacer operaciones como por ejemplo las de
/// @ref StringTokenizer / Destokenizer , etc.
/// 
/// @see StringTokenizer
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
inline constexpr bool IsInsertable = (
	
	// Definiremos el concepto y las condiciones para que un container sea insertable , estas serán :
	// 		Metodo emplace definido : Ya sea con o sin posición.
	// 		Metodo emplace_back definido
	// 		Metodo insert definido : Ya sea con o sin posición.
	// 		Metodo push definido.
	// 		Metodo push_back definido.
	HasEmplace 	<TTemplate , TValues ...> 	|| 	HasEmplacePosition 	<TTemplate , TValues ...> 	|| HasEmplaceBack <TTemplate , TValues ...> ||
	HasInsert 	<TTemplate , TValues ...> 	|| 	HasInsertPosition 	<TTemplate , TValues ...> 	||
	HasPush 	<TTemplate , TValues ...> 	|| 	HasPushBack 		<TTemplate , TValues ...>
	// -----------------------------------------------------------------------------
	
);

// Ahora para la válidación de que si un contenedor es precisamente deletable.

/// ----------------------------------------------------------------------------
/// 
/// @brief Plantilla de Variable que determina en <b>tiempo de compilación</b> si una determinada plantilla de clase es eliminable mediante los metodos de 
/// eliminación y borrado comúnmente utilizados.
/// 
/// @tparam 	TTemplate 	Plantilla de Clase a validar.
/// @tparam 	TValues 	[opcional] Tipos de valores que tendría la plantilla.
/// 
/// @details
/// 
/// Este validador realiza la comprobación de la plantilla utilizando las variables de válidación respectivas. Para que una plantilla de clase séa considerada
/// erasable debe cumplir con alguna de las siguientes carácteristicas :
/// 	<ul>
/// 		<li>Tener el metodo <b>erase</b> definido.
/// 		<li>Tener el metodo <b>pop/pop_back</b> definido.
/// 		<li>Tener el metodo <b>clear</b> definido.
/// 	</ul>
/// 
/// Es útil que alguno de estos metodos esté definido así para poder tener un contenedor que permite anexar , consultar y eliminar elementos.
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
inline constexpr bool IsErasable = (
	
	// Definiremos el concepto y las condiciones para que un container sea eliminable , estas serán :
	// 		Metodo erase definido.
	// 		Metodo pop definido.
	// 		Metodo pop_back definido.
	// 		Metodo clear definido.
	HasErase 	<TTemplate , TValues ...>	||
	HasPop 		<TTemplate , TValues ...> 	|| HasPopBack 	<TTemplate , TValues ...> 	||
	HasClear 	<TTemplate , TValues ...>
	// -----------------------------------------------------------------------------
	
);

// Ahora el validador de contenedor válido es el siguiente.

/// ----------------------------------------------------------------------------
/// 
/// @brief Plantilla de Variable que determina en <b>tiempo de compilación</b> si una determinada plantilla de clase es un contenedor válido mediante los criterios
/// especificos.
/// 
/// @tparam 	TTemplate 	Plantilla de Clase a validar.
/// @tparam 	TValues 	[opcional] Tipos de valores que tendría la plantilla.
/// 
/// @details
/// 
/// Este validador realiza la comprobación de la plantilla de clase y sus comportamientos para determinar si es considerada y puede ser utilizada como un
/// contenedor de elementos al estilo de los de la STL.
/// 
/// Para que la plantilla de clase sea válida debe cumplir con el siguiente criterio :
/// 	<ul>
/// 		<li>Tener definido el Tipo Miembro <b>value_type</b> definido.
/// 		<li>Tener el metodo <b>clear</b> para eliminar todos los elementos en el contenedor.
/// 		<li>Ser una plantilla <b>Insertable</b> : @ref IsInsertable.
/// 		<li>Tener un iterador definido mediante el tipo <b>iterator</b>.
/// 		<li>Ser Iterable : @ref IsIterable.
/// 	</ul>
/// 
/// Si la plantilla de clase cumple con esos requisitos entonces se considera una clase válida para utilizar de contenedor de elementos. Algunos ejemplos
/// de plantillas que cumplen con esto : std::vector , std::stack , std::unordered_map ... la mayoria de los containers de la STL.
/// 
/// @see StringTokenizer
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename ... TValues>
inline constexpr bool IsValidContainer = (
	
	// Definimos las condiciones para que el container sea valido : 
	// Debe tener los metodos siguientes :
	// 		Tipo Miembro : value_type
	// 		Insertable : permite insertar un nuevo elemento en el container mediante push , emplace , insert.
	// 		Eliminable : permite eliminar los elementos de alguna forma : pop , erase , clear.
	HasTypeMember 	<TTemplate , TValues ...> 	&&
	IsInsertable 	<TTemplate , TValues ...> 	&&
	IsErasable 		<TTemplate , TValues ...>
	// -----------------------------------------------------------------------------
	
);

/// @}

// Ahora viene la declaración de una base para crear containers válidos.

// -----------------------------------------------------------------------------
// 
// 								BASE CONTAINER
// 							
// -----------------------------------------------------------------------------

// Para poder facilitar la parte de la creación de nuevos containers personalizados se tiene una base de la cuál se puede derivar para poder
// reimplementar todos los elementos que esta contiene y poder crear nuevos elementos.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Plantilla de Clase/Interfaz para crear <b>Contenedores</b> con todos los metodos y tipos necesarios para su funcionamiento.
///
/// @tparam     TValue     		Tipo de Dato para el Contenedor.
/// @tparam     TIterator  		Tipo de Iterador a utilizar [Por defecto se utiliza el tipo (TValue *)]
/// @tparam     TConstIterator  Tipo de Iterador Constante a utilizar [Por defecto se utiliza el tipo (const TValue *)]
/// 
/// @details
/// 
/// Esta pequeña interfaz ó clase abstracta permite heredar a cualquier clase derivada , todos los comportamientos y tipos públicos necesarios para que
/// pueda crearse cualquier tipo de contenedor válido. Para realizarlo solamente basta con reimplementar todos los metodos que se requieran en la clase
/// derivada y colocar el código que se vaya a estar utilizando.
/// 
/// @note
/// Cualquier Clase que Derive directamente de esta Plantilla , se considerará un Container Válido (@ref IsValidContainer devuelve true).
/// 
/// @see IsValidContainer
/// 
// -----------------------------------------------------------------------------

template <typename TValue ,
	typename TIterator = std::add_pointer_t <std::decay_t <TValue>> ,
	typename TConstIterator = std::add_pointer_t <std::add_const_t <std::decay_t <TValue>>>>
class ContainerBase : public std::iterator_traits <TIterator> {
	
	// -----------------------------------------------------------------------------
	// 
	// 							CONDICIONALES
	// 							
	// -----------------------------------------------------------------------------
	
	// Debemos válidar que el tipo de valor del iterator_traits y del TValue son equivalentes.
	
	static_assert (std::is_same_v <std::decay_t <TValue> , typename std::iterator_traits <TIterator>::value_type> , "TValue y value_type son diferentes");
	
	// -----------------------------------------------------------------------------
	// 
	// 							PROPIEDADES PUBLICAS
	// 							
	// -----------------------------------------------------------------------------
	
	// Empezaremos encones con la incorporación de los elementos básicos para que esta plantilla sea considerada un contenedor válido.
	
	public :
	
		// Implementaremos las propiedades básicas.
	
		// -----------------------------------------------------------------------------
		// 
		// 							ALIAS DE TIPOS
		// 							
		// -----------------------------------------------------------------------------
		
		// Tendremos una definición para los alias de tipos.
		
		// -----------------------------------------------------------------------------
		
		// Tenemos el alias para el tipo de dato utilizado.
		
		/// --------------------------------------------------------------------------
		/// 
		/// @brief Typedef para el value_type (Alias de <b class="paramname">TValue</b>).
		/// 
		/// @details
		/// 
		/// Este es el tipo de dato del contenedor , un alias para el parametro de la plantilla respectivo <b class="paramname">TValue</b> sin ningún
		/// tipo de qualificador para el tipo de dato.
		/// 
		/// @note
		/// Es importante definir que utilizaremos el mismo alias de la clase base para que nuestro contenedor siempre esté operando con los mismos
		/// tipos de datos.
		/// 
		// ---------------------------------------------------------------------------
		
		using typename std::iterator_traits <TIterator>::value_type;
		
		// El alias para el tipo de iterador en cuestión.
		
		/// --------------------------------------------------------------------------
		/// 
		/// @brief Tipo de Iterador utilizado por este Container : Por defecto es igual a un Puntero al tipo <b class="paramname">TValue</b>.
		/// 
		/// @details
		/// 
		/// Es posible personalizar el iterador a utilizar , solamente se establece como parametro de plantilla el tipo de iterador que se estaría utilizando
		/// para esta clase de contenedor.
		/// 
		// ---------------------------------------------------------------------------
		
		typedef TIterator iterator;
		
		// El alias para el tipo de iterador constante en cuestión.
		
		/// --------------------------------------------------------------------------
		/// 
		/// @brief Tipo de Iterador Constante utilizado por este Container : Por defecto es igual a un Puntero al tipo const <b class="paramname">TValue</b>.
		/// 
		/// @details
		/// 
		/// Es posible personalizar el iterador a utilizar , solamente se establece como parametro de plantilla el tipo de iterador que se estaría utilizando
		/// para esta clase de contenedor.
		/// 
		// ---------------------------------------------------------------------------
		
		typedef TConstIterator const_iterator;
		
		// Implementamos ahora los metodos con las acciones más comunes en containers.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							PROPERTIES
		// 							
		// -----------------------------------------------------------------------------
		
		// Como la mayoria de contenedores de la STL tendremos un metodo que nos devuelve la cantidad de elementos de este container y otro para determinar
		// de manera rápida si está vacío o no.
		
		// -----------------------------------------------------------------------------
		
		// Implementamos primero el metodo size para saber cuantos elementos hay dentro de nuestro container.
		
		/// --------------------------------------------------------------------------
		/// 
		/// @brief Devuelve la cantidad de elementos en nuestro <b>Container</b>.
		/// 
		/// @return Cantidad de elementos en el Contenedor actual.
		/// 
		/// @details
		/// 
		/// Como la mayoria de los contenedores de la biblioteca estandar (STL) tenemos nuestro metodo size que nos devuelve la cantidad de elementos
		/// contenidos en este objeto. Así de simple. En este caso devolvemos todo el tiempo 0 para que la clase que lo implemente coloque su expresión
		/// que devuelva dicho valor contenido.
		/// 
		// ---------------------------------------------------------------------------
		
		virtual size_t ALWAYS_INLINE size () const { return 0u; /* No hay elementos */ }
		
		// Ahora la implementación del metodo empty para saber si está vacío o no nuestro container.
		
		/// --------------------------------------------------------------------------
		/// 
		/// @brief Determina si el contenedor está vació o no.
		/// 
		/// @return <b style="color: var(--fragment-keyword);">true</b> si está vacío el contenedor , <b style="color: var(--fragment-keyword);">false</b> en
		/// caso contrario.
		/// 
		/// @details
		/// 
		/// Este metodo indica si el contenedor actual está vacío , por lo que es demasiado útil para validar antes de proceder a utilizar un contenedor. En este
		/// caso la plantilla solamente devuelve true para que sea reimplementado de cualquier modo.
		/// 
		// ---------------------------------------------------------------------------
		
		virtual bool ALWAYS_INLINE empty () const { return true; /* Está vació */ }
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							BEGIN / END
		// 							
		// -----------------------------------------------------------------------------
		
		// Básicamente tendremos la implementación de los metodos begin y end respectivamente de nuestra base.
		
		/// --------------------------------------------------------------------------
		/// 
		/// @name
		/// 
		/// <h2 class="groupheader" style="font-style: normal;">Begin y End</h2>
		/// 
		/// @details
		/// <span style="font-style: normal;">
		/// Metodos para poder crear un Container Iterable mediante un determinado limite de elementos.
		/// 
		/// Estos metodos son básicos para que cualquier container pueda ser iterable (@ref IsIterable) y por tanto también se pueda acceder a cada uno
		/// de los elementos contenidos dentro de él con la finalidad de poder buscar valores , modificar información , quitar elementos , etc.
		/// </span>
		/// 
		/// @note
		/// <span style="font-style: normal;">
		/// Para que un determinado Container pueda ser <b style="color: var(--primary-color);">Iterable</b> se requiere tener implementado este par
		/// de metodos <b>begin</b> y <b>end</b> respectivamente para poder definir donde comienza y donde termina el contenedor.
		/// </span>
		/// @{
		/// 
		// ---------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		
		// Implementaremos la base del metodo begin que no devuelve nada útil.
		
		/// --------------------------------------------------------------------------
		/// 
		/// @brief Plantilla base para el metodo begin , no devuelve nada.
		/// 
		/// @return Iterador (iterator) al <b>Origen</b> del contenedor. (en este caso devuelve objeto vacio)
		/// 
		/// @details
		/// 
		/// Este metodo virtual está hecho para ser sobre-escrito en cualquier contenedor nuevo que se quiera hacer , este debe devolver lo que 
		/// viene a ser el <b>origen</b> del contenedor , la expresión siguiente debe ser válida :
		/// @code{.cpp}
		/// 
		/// (*MyContainer.begin ()) = TValue ();
		/// 
		/// @endcode
		/// 
		/// @warning
		/// Todos los metodos de esta interfaz deben ser definidos en la clase que lo implemente para poder hacer útil al contenedor.
		/// 
		// ---------------------------------------------------------------------------
		
		virtual iterator ALWAYS_INLINE begin () { return { }; }
		
		// Declaramos el metodo begin para objetos constantes.
		
		/// --------------------------------------------------------------------------
		/// 
		/// @brief Plantilla base para el metodo begin con un objeto constante , no devuelve nada.
		/// 
		/// @return Iterador (const_iterator) al <b>Origen</b> del contenedor. (en este caso devuelve objeto vacio)
		/// 
		/// @details
		/// 
		/// Este metodo virtual está hecho para ser sobre-escrito en cualquier contenedor nuevo que se quiera hacer , este debe devolver lo que 
		/// viene a ser el <b>origen</b> del contenedor , la expresión siguiente debe ser válida :
		/// @code{.cpp}
		/// 
		/// (*MyContainer.begin ()) = TValue ();
		/// 
		/// @endcode
		/// 
		/// @warning
		/// Todos los metodos de esta interfaz deben ser definidos en la clase que lo implemente para poder hacer útil al contenedor.
		/// 
		// ---------------------------------------------------------------------------
		
		virtual const_iterator ALWAYS_INLINE begin () const { return { }; }
		
		// Ahora declaramos el metodo end.
		
		/// --------------------------------------------------------------------------
		/// 
		/// @brief Plantilla base para el metodo end , no devuelve nada.
		/// 
		/// @return Iterador (iterator) al <b>Post-Final</b> del contenedor. (en este caso devuelve un iterador vacío)
		/// 
		/// @details
		/// 
		/// Este metodo virtual está hecho para ser sobre-escrito en cualquier contenedor nuevo que se quiera hacer , este debe devolver lo que 
		/// viene a ser el <b>post-final</b> del contenedor , la expresión siguiente debe devolver <b style="color: var(--fragment-keyword);">true</b> :
		/// @code{.cpp}
		/// 
		/// (MyContainer.end () > MyContainer.begin ())
		/// 
		/// @endcode
		/// 
		/// @warning
		/// Todos los metodos de esta interfaz deben ser definidos en la clase que lo implemente para poder hacer útil al contenedor.
		/// 
		// ---------------------------------------------------------------------------
		
		virtual iterator ALWAYS_INLINE end () { return { }; }
		
		// De igual manera para nuestro metodo end con objetos const.
		
		/// --------------------------------------------------------------------------
		/// 
		/// @brief Plantilla base para el metodo end para objetos constantes , no devuelve nada.
		/// 
		/// @return Iterador (const_iterator) al <b>Post-Final</b> del contenedor. (en este caso devuelve un iterador vacío)
		/// 
		/// @details
		/// 
		/// Este metodo virtual está hecho para ser sobre-escrito en cualquier contenedor nuevo que se quiera hacer , este debe devolver lo que 
		/// viene a ser el <b>post-final</b> del contenedor , la expresión siguiente debe devolver <b style="color: var(--fragment-keyword);">true</b> :
		/// @code{.cpp}
		/// 
		/// (MyContainer.end () > MyContainer.begin ())
		/// 
		/// @endcode
		/// 
		/// @warning
		/// Todos los metodos de esta interfaz deben ser definidos en la clase que lo implemente para poder hacer útil al contenedor.
		/// 
		// ---------------------------------------------------------------------------
		
		virtual const_iterator ALWAYS_INLINE end () const { return { }; }
		
		/// @}
		
		// El siguiente es el metodo de acceso que pueden tener los containers para buscar un determinado elemento y obtener su iterador respectivo.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 								ACCESS ELEMENT
		// 							
		// -----------------------------------------------------------------------------
		
		// Implementamos las plantillas virtuales para todos los metodos de acceso a la información del contenedor.
		
		// -----------------------------------------------------------------------------
		
		// Tendremos el siguiente que es el operador de acceso aleatorio dentro de un container por medio de la posición del elemento , como si de
		// un array se tratase.
		
		/// --------------------------------------------------------------------------
		/// 
		/// @brief Accede a un determinado elemento mediante la posición en el Contenedor.
		/// 
		/// @return Debe devolver el valor del elemento en caso de que se haya encontrado alguno. (en este caso no devuelve nada)
		/// 
		/// @details
		/// 
		/// Como la mayoria de nuestros contenedores con los que estamos familiarizados (vector , list , deque) , tenemos que tener un determinado
		/// mecanismo para acceder al contenido directamente con una posición. Este metodo hace la busqueda y devuelve el valor encontrado , por lo que
		/// es importante tenerlo en cuenta para su implementación.
		/// 
		/// @note
		/// Algunos Containers no pueden acceder directamente a su contenido con posiciones (map , set) , por lo que otra forma de buscar un elemento
		/// en estos casos es mediante los algoritmos de busqueda <b>find , find_if</b> utilizando los iteradores begin y end de dicho container.
		/// 
		// ---------------------------------------------------------------------------
		
		virtual value_type ALWAYS_INLINE operator [] (size_t) { return value_type (); }
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							INSERT / ERASE / CLEAR
		// 							
		// -----------------------------------------------------------------------------
		
		// Ahora pasaremos con el conjunto de metodos para poder insertar , eliminar y limpiar elementos en el contenedor.
		
		/// --------------------------------------------------------------------------
		/// 
		/// @name
		/// 
		/// <h2 class="groupheader" style="font-style: normal;">Insert / Erase / Clear</h2>
		/// 
		/// @details
		/// <span style="font-style: normal;">
		/// Metodos para la modificación del contenedor , añadir elementos , eliminar elementos , etc.
		/// 
		/// Se tiene el sub-conjunto de metodos dentro de nuestra plantilla de Container con los cuales se pueden realizar las operaciones más
		/// escenciales para los containers. Estas son las siguientes : </span>
		/// 	<ul style="font-style: normal;">
		/// 		<li>Añadir Elementos : Mediante el metodo @ref insert.</li>
		/// 		<li>Eliminar Elementos : Mediante el metodo @ref erase.</li>
		/// 		<li>Limpiar todos los Elementos : Mediante el metodo @ref clear.</li>
		/// 	</ul>
		/// @note
		/// <span style="font-style: normal;">
		/// Cabe señalar que para que un Container sea considerado <b>Válido</b> basta solamente con tener los metodos <b>insert y clear</b> definidos , por
		/// lo que el definir el metodo erase o algunos metodos adicionales como los metodos <b>push , emplace</b> es completamente <b>opcional</b> aunque
		/// bastante recomendable para hacerlo más completo.
		/// </span>
		/// @{
		/// 
		// ---------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		
		// Definiremos el metodo insert de plantilla para la definición formal.
		
		/// --------------------------------------------------------------------------
		/// 
		/// @brief Inserta un nuevo elemento <b>Por Copia</b> en el Contenedor.
		/// 
		/// @return Debe retornar el Iterador que apunta a dicho elemento guardado en el Objeto. (en este caso no devolvemos nada).
		/// 
		/// @details
		/// 
		/// Este metodo base no realiza ninguna acción. Debe definirse su contenido en las clases derivadas para poder anexar algún elemento en 
		/// el contenedor en cuestión respetando cualquier regla personalizada para hacerlo.
		/// 
		// ---------------------------------------------------------------------------
		
		virtual iterator ALWAYS_INLINE insert (const value_type &) { return { }; }
		
		// Ahora el metodo insert para los R-Values.
		
		/// --------------------------------------------------------------------------
		/// 
		/// @brief Inserta un nuevo elemento <b>Mediante R-Value</b> en el Contenedor.
		/// 
		/// @return Debe retornar el Iterador que apunta a dicho elemento guardado en el Objeto. (en este caso no devolvemos nada).
		/// 
		/// @details
		/// 
		/// Este metodo base no realiza ninguna acción. Debe definirse su contenido en las clases derivadas para poder anexar algún elemento en 
		/// el contenedor en cuestión respetando cualquier regla personalizada para hacerlo.
		/// 
		// ---------------------------------------------------------------------------
		
		virtual iterator ALWAYS_INLINE insert (value_type &&) { return { }; }
		
		// Para poder eliminar un elemento en el container tenemos los metodos erase , que en nuestro caso elimina un elemento determinado por su
		// posición utilizando un iterador.
		
		/// --------------------------------------------------------------------------
		/// 
		/// @brief Elimina un determinado elemento en el Contenedor.
		/// 
		/// @return Debe retornar el Iterador que apunta al elemento siguiente al que fue eliminado. (en este caso no devolvemos nada).
		/// 
		/// @details
		/// 
		/// Este metodo base no realiza ninguna acción. Debe definirse en las clases derivadas para que con el parametro iterator pueda buscar y
		/// eliminar un determinado elemento dentro de todo el conjunto de elementos que tenga este metodo.
		/// 
		// ---------------------------------------------------------------------------
		
		virtual iterator ALWAYS_INLINE erase (iterator) { return { }; }
		
		// Ahora pasaremos por último al metodo clear para limpiar todos los elementos en nuestro contenedor.
		
		/// --------------------------------------------------------------------------
		/// 
		/// @brief      Metodo para limpiar todos los elementos en el <b>Contenedor</b>.
		/// 
		/// @details
		/// 
		/// Es hábitual y recomendable que todos los contenedores dispongan de este metodo con la finalidad de que se puedan eliminar cada uno de los
		/// elementos que tenga insertado en estos momentos y dejarlo limpio.
		/// 
		// ---------------------------------------------------------------------------
		
		virtual void clear () { /* Sin Definir */ }
		
		/// @}
		
		// -----------------------------------------------------------------------------
	
};

template <typename TValue , template <typename ...> typename TContainer = std::unordered_map , typename A = std::any , typename B = std::any>
class ContainerAdapter : public TContainer <A , B> { };

template <template <typename ...> typename TMap , typename ... TValues>
using MultiContainer = ContainerAdapter <typename TMap <TValues ...>::value_type , TMap , TValues ...>;

template <template <typename ...> typename TContainer , typename ... TValues>
struct AlterContainerTypes {
	
	using container_type = TContainer <TValues ...>;
	
};

template <template <typename ...> typename TTemplate , typename TValue>
struct AlterContainerA {
	
	using container_type = TTemplate <TValue>;
	
};

template <template <typename ...> typename TTemplate , typename ... TValues>
struct AlterContainerN { };

template <template <typename ...> typename TTemplate , typename A , typename B>
struct AlterContainerN <TTemplate , A , B> : AlterContainerA <std::vector , typename TTemplate <A , B>::value_type> {
	
	// Ahora un alias para el contenedor obtenido.
	
	using container_type = TTemplate <A , B>;
	
};

// -----------------------------------------------------------------------------

// Ahora pasaremos a los metodos para alterar los containers definidos en su respectiva estructura.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							CONTAINER METHODS
// 							
// -----------------------------------------------------------------------------

// Primero tenemos una serie de especializaciones de plantillas de estructuras que permiten realizar la asignación de los metodos respectivos para cada tipo de
// contenedor en particular que se esté utilizando.

/// @cond AlterContainerTraits

// Tenemos primero nuestra base para especializar que define un tipo de estructura para la gestión de un tipo de contenedor de un dato incompleto.

// -----------------------------------------------------------------------------

// Comenzando por las especializaciones del container Alter tenemos lo siguiente para nuestro alter container.

template <template <typename ...> typename TTemplate , typename ... TValues>
struct AlterContainer : std::bool_constant <IsValidContainer <TTemplate , TValues ...>> {
	
	// Definiremos las propiedades de nuestro contenedor.
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							COMPORTAMIENTOS
	// 							
	// -----------------------------------------------------------------------------
	
	// Definiremos de manera general el comportamiento que tiene la plantilla actual con respecto al soporte de metodos.
	
	// -----------------------------------------------------------------------------
	
	// Primero tenemos el definidor de metodo emplace que se tiene asignado.
	
	static constexpr bool has_emplace = HasEmplace <TTemplate , TValues ...>;
	
	// Para validar que se tiene emplace position.
	
	static constexpr bool has_emplace_position = HasEmplacePosition <TTemplate , TValues ...>;
	
	// Para validar si se tiene un emplace back.
	
	static constexpr bool has_emplace_back = HasEmplaceBack <TTemplate , TValues ...>;
	
	// Ahora vamos a comprobar si tiene el metodo insert.
	
	static constexpr bool has_insert = HasInsert <TTemplate , TValues ...>;
	
	// Si tiene un insert con posición establecida lo válidamos.
	
	static constexpr bool has_insert_position = HasInsertPosition <TTemplate , TValues ...>;
	
	// Para validar que esté el metodo erase definido en este container.
	
	static constexpr bool has_erase = HasErase <TTemplate , TValues ...>;
	
	// Para poder saber que efectivamente se estableza el comportamiento efectivo.
	
	static constexpr bool has_size = HasSize <TTemplate , TValues ...>;
	
	// Para poder sabeer que tiene el metodo at tenemos lo siguiente.
	
	static constexpr bool has_at = HasAt <TTemplate , TValues ...>;
	
	// Para saber si tiene el metodo count tendremos lo siguiente.
	
	static constexpr bool has_count = HasCount <TTemplate , TValues ...>;
	
	// Establecemos el siguiente para tener como referencia si tiene el metodo empty.
	
	static constexpr bool has_empty = HasEmpty <TTemplate , TValues ...>;
	
	// Para poder saber si tiene el metodo Clear estabecido.
	
	static constexpr bool has_clear = HasClear <TTemplate , TValues ...>;
	
	// Ahora vamos a comprobar si tiene el metodo push.
	
	static constexpr bool has_push = HasPush <TTemplate , TValues ...>;
	
	// En el caso de push_back se tiene el siguiente valor constante.
	
	static constexpr bool has_push_back = HasPushBack <TTemplate , TValues ...>;
	
	// Para validar que tiene un metodo pop.
	
	static constexpr bool has_pop = HasPop <TTemplate , TValues ...>;
	
	// De la misma manera para saber si tiene el metodo pop_back este contenedor.
	
	static constexpr bool has_pop_back = HasPopBack <TTemplate , TValues ...>;
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							ALIAS DE TIPOS
	// 							
	// -----------------------------------------------------------------------------
	
	// Tendremos todos los tipos de nuestro alterador de contenedor.
	
	// -----------------------------------------------------------------------------
	
	// Ahora un alias para el contenedor obtenido.
	
	using container_type = ContainerType <TTemplate , TValues ...>;
	
	// Tendremos un alias para el tipo de dato de nuestro contenedor.
	
	using value_type = typename container_type::value_type;
	
	// -----------------------------------------------------------------------------
	// 
	// 							EMPLACE / INSERT
	// 							
	// -----------------------------------------------------------------------------
	
	// Implementaremos todos los metodos especializados para cada tipo de operación Insert que tendremos.
	
	// -----------------------------------------------------------------------------
	
	// Implementamos el metodo emplace que ocurre cuando se tiene este metodo definido en el contenedor establecido.
	
	template <typename ... TValuesEmplace>
	static ALWAYS_INLINE auto emplace (container_type & Output , TValuesEmplace && ... Values) {
		
		// Primero determinamos si la construcción o la conversión es valida para el conjunto de argumentos variables establecidos.
		
		static constexpr bool ValidConstruction = std::is_constructible_v <value_type , TValuesEmplace ...>;
		
		// Ahora una validación para continuar en caso de que el objeto TValue se pueda construir con la lista de argumentos pasada al metodo.
		
		static_assert (ValidConstruction , "TValue no es construible/convertible desde los TValuesEmplace establecidos");
		
		// -----------------------------------------------------------------------------
		// 
		// 							EMPLACE BACK ITEM
		// 							
		// -----------------------------------------------------------------------------
		
		// Continuamos si la validación principal se cumple.
		
		if constexpr (ValidConstruction) {
			
			// Validamos lo que tenemos en el contenedor para insertar con emplace.
			
			if constexpr (has_emplace_back) {
			
				// Insertamos el elemento al final de nuestro actual container de salida. Respetamos la semantica l o r value.
				
				return Output.emplace_back (std::forward <TValuesEmplace> (Values) ...);
				
				// -----------------------------------------------------------------------------
				
			}
			else if constexpr (has_emplace_position && IsIterable <TTemplate , TValues ...>) {
				
				// Con el caso de emplace el iterator y el valor tenemos que establecer. Insertamos por el final utilizando end.
				
				return Output.emplace (Output.end () , std::forward <TValuesEmplace> (Values) ...);
				
				// -----------------------------------------------------------------------------
				
			}
			else if constexpr (has_emplace) {
				
				// Insertamos el elemento a nuestro container de salida. Respetamos la semantica l o r value.
				
				return Output.emplace (std::forward <TValuesEmplace> (Values) ...);
				
				// -----------------------------------------------------------------------------
				
			}
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
		
	}
	
	// Ahora implementaremos el metodo insert para cuando se tenga esta operación definida en el contenedor respectivo.
	
	template <typename ... TValuesEmplace>
	static ALWAYS_INLINE auto insert (container_type & Output , TValuesEmplace && ... Values) {
		
		// -----------------------------------------------------------------------------
		// 
		// 								INSERT ITEM
		// 							
		// -----------------------------------------------------------------------------
		
		// Validaremos lo que tiene el contenedor para insertar y lo realizaremos
		
		if constexpr (has_insert_position && IsIterable <TTemplate , TValues ...>) {
		
			// Insertamos el elemento al final de nuestro actual container de salida. Respetamos la semantica l o r value.
			
			return Output.insert (Output.end () , std::forward <TValuesEmplace> (Values) ...);
			
			// -----------------------------------------------------------------------------
			
		}
		else if constexpr (has_insert) {
			
			// Insertamos el elemento a nuestro container de salida. Respetamos la semantica l o r value.
			
			return Output.insert (std::forward <TValuesEmplace> (Values) ...);
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
		
	}
	
	// Ahora unas utilerias adicionales en esta estructura.
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 								PUSH VALUE
	// 							
	// -----------------------------------------------------------------------------
	
	// Para poder realizar la inserción sin importar que metodo utilizar se tiene el siguiente metodo para poner un valor.
	
	template <typename ... TValuesPush>
	static ALWAYS_INLINE decltype (auto) push (container_type & Output , TValuesPush && ... Argumentos) {
		
		// Validaremos que operación efectuar con los metodos que se tienen.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							PUSH VALUE CONTAINER
		// 							
		// -----------------------------------------------------------------------------
		
		// Dependiendo los metodos de los que disponga la plantilla de clase es como se implementa esta función constante.
		
		// -----------------------------------------------------------------------------
		
		// Si tenemos push definido y 1 solo argumento entonces vamos a utilizarlo primero.
		
		if constexpr (has_push && (sizeof ... (TValuesPush) == 1u)) {
			
			// Si se tiene este metodo entonces lo invocaremos con el único argumento que tenemos.
			
			return Output.push (std::forward <TValuesPush> (Argumentos) ...);
			
			// -----------------------------------------------------------------------------
			
		}
		else if constexpr (has_push_back && (sizeof ... (TValuesPush) == 1u)) {
			
			// Si se tiene en su lugar push_back entonces los invocaremos con el único argumento que tenemos.
			
			return Output.push_back (std::forward <TValuesPush> (Argumentos) ...);
			
			// -----------------------------------------------------------------------------
			
		}
		else if constexpr (has_insert || has_insert_position) {
			
			// Si tenemos entonces el metodo insert y ún argumento devolvemos la llamada al metodo respectivo.
			
			return insert (Output , std::forward <TValuesPush> (Argumentos) ...);
			
			// -----------------------------------------------------------------------------
			
		}
		else if constexpr (has_emplace || has_emplace_position || has_emplace_back) {
			
			// En caso de tener emplace y más de 1 solo argumento devolvemos la llamada a nuestro metodo respectivo.
			
			return emplace (Output , std::forward <TValuesPush> (Argumentos) ...);
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
		
	}
	
	// Ahora pasamos a lo contrario , el metodo para quitar elementos.
	
	// -----------------------------------------------------------------------------
	// 
	// 								POP VALUE
	// 							
	// -----------------------------------------------------------------------------
	
	// Para poder realizar la eliminación sin importar que metodo utilizar se tiene el siguiente metodo.
	
	static ALWAYS_INLINE void pop (container_type & Output) {
		
		// Validaremos que operación efectuar con los metodos que se tienen. Solamente se da un static_assert si no tiene ningúno.
		
		static_assert ((has_pop || has_pop_back) , "El Container no tiene el metodo pop/pop_back definido");
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							POP VALUE CONTAINER
		// 							
		// -----------------------------------------------------------------------------
		
		// Dependiendo los metodos de los que disponga la plantilla de clase es como se implementa esta función constante.
		
		// -----------------------------------------------------------------------------
		
		// Si tenemos pop_back definido entonces vamos a utilizarlo primero.
		
		if constexpr (has_pop_back) {
			
			// Realizaremos la invocación al metodo pop_back directamente sobre el container.
			
			Output.pop_back ();
			
			// -----------------------------------------------------------------------------
			
		}
		else if constexpr (has_pop) {
			
			// Si tenemos entonces el metodo pop se invoca en su lugar.
			
			Output.pop ();
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
		
	}
	
	// Ahora para la parte de limpiar elementos , eliminarlos.
	
	// -----------------------------------------------------------------------------
	// 
	// 							ERASE / CLEAR ELEMENTS
	// 							
	// -----------------------------------------------------------------------------
	
	// Si el container en cuestión tiene soporte para estas funciones entonces se implementan con el código respectivo , de lo contrario no
	// se realiza ninguna operación.
	
	// -----------------------------------------------------------------------------
	
	// Tenemos el siguiente metodo para poder efectuar la eliminación de un determinado elemento en el container actual.
	
	template <typename TIterator>
	static ALWAYS_INLINE auto erase (container_type & Output , TIterator Position) {
		
		// Se procede con la validación para poder determinar que el container actual tiene el metodo erase definido.
		
		static_assert (has_erase , "Container no tiene el metodo erase definido");
		
		// Ahora se valida que tenga un iterator válido este container.
		
		static_assert (HasIterator <TTemplate , TValues ...> , "Container no cuenta con un type/alias Iterator valido");
		
		// Se procede con la validación para poder  saber si tiene un iterator definido y así poder seguir con el proceso de eliminación.
		
		if constexpr (has_erase && HasIterator <TTemplate , TValues ...>) {
			
			// Determinamos el alias para el tipo de iterator en el container utilizado.
				
			using iterator = typename container_type::const_iterator;
			
			// Primero se realiza una validación para saber si el tipo de Iterator puede ser convertido al tipo de iterador del container actual.
			
			static_assert (std::is_convertible_v <TIterator , iterator> , "TIterator incompatible con iterator");
			
			// -----------------------------------------------------------------------------
			
			// -----------------------------------------------------------------------------
			// 
			// 							Eliminando Elemento
			// 							
			// -----------------------------------------------------------------------------
			
			// Primero la validación para determinar si tiene el metodo erase definido.
			
			if constexpr (std::is_convertible_v <TIterator , iterator>) {
				
				// Se procede a eliminar el elemento en tal caso utilizando la función respectiva para esto.
				
				return Output.erase (Position);
				
				// -----------------------------------------------------------------------------
				
			}
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
		
	}
	
	// Ahora para limpiar el contenedor actual tenemos el siguiente metodo definido.
	
	static ALWAYS_INLINE void clear (container_type & Output) {
		
		// Primero se valida que existe esta operación o que está al menos definida.
		
		static_assert (has_clear , "Container no tiene definido el metodo clear");
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							Limpiar Elementos
		// 							
		// -----------------------------------------------------------------------------
		
		// Se procede a validar primero para poder aplicar la operación respectiva.
		
		if constexpr (has_clear) {
			
			// Invocaremos el metodo clear sobre este container directamente para limpiarlo.
			
			Output.clear ();
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
		
	}
	
	// -----------------------------------------------------------------------------
	
};

// -----------------------------------------------------------------------------

/// @endcond

// Ahora vamos con algunas utilerias adicionales que complementan a las utilerias base.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																	REVERSE / TOKENIZER
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Implementaremos funciones auxiliares para invertir cadenas y recortarlas de acuerdo a una serie de criterios que se pueden especificar
// mediante procesos.

// -----------------------------------------------------------------------------

// Continuaremos por la implementación del String invertido.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// 
// 							REVERSE STRING
// 							
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// Implementaremos una función para devolver la cadena invertida que queramos.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Invierte una cadena , obtiene una copia con la cadena invertida.
///
/// @param[in]  Input   Cadena de entrada a invertir.
///
/// @tparam     TChar   Tipo de Caracter a utilizar.
///
/// @return     Cadena de entrada invertida STD del mismo tipo de caracter.
/// 
/// @details
/// 
/// Simplemente invierte toda la cadena para que comience desde lo que era el final y termina por el inicio de la cadena original.
/// 
// -----------------------------------------------------------------------------

template <typename TChar>
ALWAYS_INLINE std::basic_string <TChar> ReverseString (const std::basic_string <TChar> & Input) {
	
	// -----------------------------------------------------------------------------
	// 
	// 							Invirtiendo String
	// 							
	// -----------------------------------------------------------------------------
	
	// Devolvemos la cadena invertida mediante la construcción con sus iteradores inversores.
	
	return std::basic_string <TChar> (Input.rbegin () , Input.rend ());
	
	// -----------------------------------------------------------------------------
	
}

// -----------------------------------------------------------------------------

// Ahora pasaremos a la implementación de las funciones para el Tokenizer y Destokenizer de cadenas de texto.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							STRING TOKENIZER
// 							
// -----------------------------------------------------------------------------

// Ahora para la sección del Tokenizer.

/// ----------------------------------------------------------------------------
/// 
/// @name String Tokenizer / Destokenizer
/// 
/// @brief Funciones especificas para la descomposición de una cadena , en un conjunto de sub-cadenas mediante una cadena de corte <b>"TokenCutter"</b> la cuál
/// determina la forma en la que se irán cortando en tokens la cadena de entrada.
/// 
/// @details
/// 
/// StringTokenizer es la función principal para la separación de la cadena
/// 
/// @{
/// 
// -----------------------------------------------------------------------------

// Implementamos entonces la función para tokenizar cualquier cadena de entrada.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Tokeniza cualquier tipo de cadena de entrada y genera un contenedor con todas las sub-cadenas obtenidas.
///
/// @param[in]  Input      Cadena de entrada para tokenizar.
/// @param[in]  Delim      Caracter delimitador para cortar la cadena.
///
/// @tparam     TTemplate  Plantilla de Clase de Container a generar como resultado con el tipo de cadena especifico.
/// @tparam     TChar      Tipo de caracter de la cadena , por defecto es char.
///
/// @return     Contenedor con todas las sub-cadenas generadas a partir de la cadena de entrada original.
/// 
/// @pre
/// TTemplate debe ser una clase parametrizable que validé como true @ref IsValidContainer
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename TChar = char , typename ... TValues>
auto StringTokenizer (const std::basic_string <TChar> & Input , const TChar Delim) -> decltype (
	std::declval <std::enable_if_t <IsValidContainer <TTemplate , std::basic_string <TChar> , TValues ...>>> () ,
	ContainerType <TTemplate , std::basic_string <TChar> , TValues ...> ()) {
	
	// Realizamos la generación de un Tokenizer para cualquier contenedor válido que cumpla con las validaciones.
	
	// -----------------------------------------------------------------------------
	// 
	// 							Typedefs Container
	// 							
	// -----------------------------------------------------------------------------
	
	// Definiremos primero los tipos de datos que estaremos utilizando.
	
	// -----------------------------------------------------------------------------
	
	// Tenemos el tipo de cadena que estamos utilizando.
	
	using TString = std::basic_string <TChar>;
	
	// Tenemos la implementación del tipo de container que vamos a crear con este tipo de cadena.
	
	using TContainer = ContainerType <TTemplate , TString , TValues ...>;
	
	// Asi como el modificador de containers genericos que tenemos definido.
	
	using AContainer = AlterContainer <TTemplate , TString , TValues ...>;
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							TOKENIZANDO STRING
	// 							
	// -----------------------------------------------------------------------------
	
	// Tenemos una cadena de entrada y lo que realizaremos será el recorte (tokenizer) de esta misma en sub-cadenas que están
	// separadas en la cadena original por el delimitador especificado.
	
	// -----------------------------------------------------------------------------
	
	// Tenemos primero nuestro contenedor resultado.
	
	TContainer Output;
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							ITERACION PRINCIPAL
	// 							
	// -----------------------------------------------------------------------------
	
	// Para tokenizar lo que haremos será buscar coincidencias del delimitador dentro de la cadena y ajustar la posición del indice
	// para seguir buscando a partir de dicha posición. Cada busqueda anexa un string al container resultante.
	
	// Por lo que iniciamos nuestros contadores en 0 por defecto.
	
	size_t CurrentPos = 0u , NextPos = 0u;
	
	// -----------------------------------------------------------------------------
	
	// Ahora vamos a realizar la iteración para ir buscando y anexando más resultados al contenedor de salida.
	
	do {
		
		// Primero vamos a obtener la posición del siguiente delimitador en la cadena desde la posición actual.
		
		NextPos = Input.find_first_of (Delim , CurrentPos);
		
		// Asignaremos la cantidad de caracteres a recuperar.
		
		const size_t CurrentCount = std::min ((NextPos - CurrentPos) , Input.size ());
		
		// Ahora insertamos en el container nuestra sub-cadena conformada.
		
		AContainer::push (Output , std::move (Input.substr (CurrentPos , CurrentCount)));
		
		// -----------------------------------------------------------------------------
		
		// Asignaremos la nueva posición original.
		
		CurrentPos = ((NextPos != TString::npos) ? (NextPos + 1) : NextPos);
		
		// -----------------------------------------------------------------------------
		
	} while (CurrentPos != TString::npos);
	
	// -----------------------------------------------------------------------------
	
	// Finalmente devolvemos nuestro contenedor resultado.
	
	return Output;
	
}

// Ahora la contraparte , la función que destokeniza un conjunto de tokens de entrada en una sola cadena concatenada con el delimitador
// que se tiene especificado.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Destokeniza cualquier conjunto de <b>Tokens</b> y genera una cadena con todos los tokens unidos con el <b class="paramname">Delim</b> especificado.
///
/// @param[in]  InputTokens  Conjunto de Tokens de Entrada.
/// @param[in]  Delim        Caracter Delimitador para unir la Cadena.
///
/// @tparam     TTemplate    Plantilla de Clase que indica el <b style="color: var(--primary-color);">Container</b> utilizado.
/// @tparam     TChar        Tipo de Caracter Utilizado. (por default es igual a char)
///
/// @return     Cadena con el conjunto de Tokens unidos.
/// 
/// @details
/// 
/// Esta es la función opuesta a la StringTokenizer , lo que hace es tomar el conjunto de Tokens que pueden venir en <b>cualquier tipo de container</b> , y los
/// concatena uno por uno en una cadena resultado separandolos con el <b class="paramname">Delim</b> especificado.
/// 
/// @note
/// <b class="paramname">TTemplate</b> debe cumplir la condición de <b>Iteración</b> (@ref IsIterable) para que se pueda recorrer completamente y conjuntar todos
/// los tokens. 
/// 
// -----------------------------------------------------------------------------

template <template <typename ...> typename TTemplate , typename TChar = char , std::enable_if_t <IsIterable <TTemplate , std::basic_string <TChar>> , bool> = true>
std::basic_string <TChar> StringDestokenizer (const TTemplate <std::basic_string <TChar>> & InputTokens , const TChar Delim) {
	
	// Realizaremos la iteración por cada token de entrada para poder iterar por el determinado container con la finalidad de construir la cadena de salida.
	
	// -----------------------------------------------------------------------------
	// 
	// 							Typedefs Container
	// 							
	// -----------------------------------------------------------------------------
	
	// Definiremos primero los tipos de datos que estaremos utilizando.
	
	// -----------------------------------------------------------------------------
	
	// Tenemos el tipo de cadena que estamos utilizando.
	
	using TString = std::basic_string <TChar>;
	
	// -----------------------------------------------------------------------------
	
	// Crearemos nuestro buffer para la cadena de salida a conformar.
	
	std::basic_stringstream <TChar> Output;
	
	// Ahora continuaremos con una validación respectiva antes de continuar,
	
	if constexpr 		(HasEmpty <TTemplate , TString>) 	if (InputTokens.empty ()) 		return Output.str ();
	else if constexpr 	(HasSize <TTemplate , TString>) 	if (InputTokens.size () == 0u) 	return Output.str ();
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							Iteración Principal
	// 							
	// -----------------------------------------------------------------------------
	
	// Vamos a iterar por todo el container y se irán concatenando todas las cadenas que se vayan obteniendo.
	
	for (const auto & CurrentToken : InputTokens) {
		
		// Concatenamos el token actual en el buffer de salida junto al delimitador.
		
		Output << CurrentToken << Delim;
		
		// -----------------------------------------------------------------------------
		
	}
	
	// Obtendremos la cadena resultado de salida.
	
	TString Resultado (std::move (Output.str ()));
	
	// Si la cadena no está vacía entonces eliminamos solamente el último caracter.
	
	if (!Resultado.empty ()) {
		
		// Borramos el último delimitador anexado a la cadena total.
		
		Resultado.pop_back ();
		
		// -----------------------------------------------------------------------------
		
	}
	
	// -----------------------------------------------------------------------------
	
	// Finalmente devolvemos el resultado de la cadena de salida actual.
	
	return Resultado;
	
}

// Ahora para poder establecer un StringPair necesitamos saber que dato obtener para poder consultarlo mediante un template.

template <size_t Index , typename TChar = char>
std::basic_string <TChar> StringPair (const std::basic_string <TChar> & Input , const TChar Symbol) {
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							STRING PAIR VALUES
	// 							
	// -----------------------------------------------------------------------------
	
	// Tokenizaremos nuestro elemento actual para saber lo que tenemos que devolver dependiendo el indice.
	
	const auto CurrentTokens (std::move (StringTokenizer <std::vector> (Input , Symbol)));
	
	// Si el indice es menor que el numero de elementos lo devolveremos.
	
	if (Index < CurrentTokens.size ()) return CurrentTokens [Index];
	
	// Devolveremos la salida actual.
	
	return Input;
	
	// -----------------------------------------------------------------------------
	
}

// -----------------------------------------------------------------------------

/// @}

// -----------------------------------------------------------------------------

/// @}

// -----------------------------------------------------------------------------

/// @}

// Implementaremos los operadores para esta sección de los Tokenizer.

// -----------------------------------------------------------------------------
// 
// 							OPERADOR TOKENIZER
// 							
// -----------------------------------------------------------------------------

// Estableceremos un espacio en linea para guardar los operadores especificos de las utilerias.

inline namespace UtilityOperators {
	
	/// 
	/// @addtogroup UtilOperators
	/// @{
	/// 
	
	// Definiremos el operador para poder tokenizar una cadena de entrada con el delimitador especificado generando así un contenedor con todos los 
	// tokens obtenidos de dicha cadena cortada actual.
	
	// -----------------------------------------------------------------------------
	/// 
	/// @brief Operador <STokens> para aplicar función que recorta la cadena en Sub-Cadenas llamadas <b>Tokens</b>.
	/// 
	/// @param "CADENA A TOKENIZAR" <STokens <<b class="paramname">TEMPLATE_CONTAINER</b>>><b class="paramname">'DELIMITADOR'</b>
	/// 
	/// @tparam 	TTemplate 	Tipo de plantilla de Clase a utilizar como <b class="paramname">Container</b> de salida.
	/// 
	/// @details
	/// Con este operador se puede recortar la cadena de entrada y obtener como resultado un contenedor con todos los tokens obtenidos después de
	/// cortar la cadena de entrada utilizando el caracter <b class="paramname">Delimitador</b>.
	/// 
	/// Observemos el siguiente ejemplo :
	/// 
	/// @code{.cpp}
	/// 
	/// 	const auto TokensString = "CADENA|CORTADA|EN|TROZOS" <STokens <std::vector>> '|';
	/// 	
	/// 	// Result : std::vector <std::string> { "CADENA" , "CORTADA" , "EN" , "TROZOS" }
	/// 	
	/// @endcode
	/// 
	/// @note
	/// El operando derecho determina el caracter a utilizar para <b>cortar</b> la cadena mientras que el parametro de plantilla determina el <b>tipo</b> de
	/// contenedor a generar. Este debe ser un <b style="color: var(--primary-color);">Container</b> válido.
	/// 
	/// @see IsValidContainer
	/// 
	// -----------------------------------------------------------------------------
	
	template <template <typename ...> typename TTemplate>
	inline auto STokens = MakeNamedOperator (StringTokenizer <TTemplate>);
	
	// Ahora para aplicar la operación opuesta tenemos el siguiente operador destokenizer.
	
	// -----------------------------------------------------------------------------
	/// 
	/// @brief Operador <DTokens> para aplicar función que re-construye la cadena Tokenizada con los trozos (tokens) especificados.
	/// 
	/// @param 		CONTENEDOR_DE_TOKENS <DTokens <<b class="paramname">TEMPLATE_CONTAINER</b>>><b class="paramname">'DELIMITADOR'</b>
	/// 
	/// @tparam 	TTemplate 	Tipo de plantilla de Clase a utilizar como entrada del Container para el operador.
	/// 
	/// @details
	/// Con este operador se realiza la operación opuesta al Tokenizer , toma un conjunto de Tokens que se tienen dentro del parametro <b class="paramname">
	/// CONTENEDOR</b> , mediante una simple iteración crea lo que es la <b>Cadena</b> original con todos los tokens concatenados junto al caracter
	/// <b class="paramname">Delimitador</b> que se esté utilizando.
	/// 
	/// Observemos el siguiente ejemplo :
	/// 
	/// @code{.cpp}
	/// 
	/// 	const auto StringOriginal = TokensString <DTokens <std::vector>> '|';
	/// 	
	/// 	// Result : "CADENA|CORTADA|EN|TROZOS"
	/// 	
	/// @endcode
	/// 
	/// @note
	/// El operando derecho determina el caracter a utilizar para <b>unir</b> la cadena mientras que el parametro de plantilla determina el <b>tipo</b> de
	/// contenedor a utilizar como entrada. Este debe ser un <b style="color: var(--primary-color);">Container</b> iterable válido.
	/// 
	/// @see IsIterable
	/// 
	// -----------------------------------------------------------------------------
	
	template <template <typename ...> typename TTemplate>
	inline auto DTokens = MakeNamedOperator (StringDestokenizer <TTemplate>);
	
	// Ahora para el caso del string de paridad tenemos lo siguiente.
	
	// -----------------------------------------------------------------------------
	/// 
	/// @brief Operador <SPair> para obtener lo que es un respectivo valor de paridad para un token de string
	/// 
	/// @param 		STRING_TOKENS <SPair <<b class="paramname">INDEX</b>>><b class="paramname">SYMBOL</b>
	/// 
	/// @tparam 	Index 	Indice del cuál tomar el elemento.
	/// 
	/// @details
	/// Con este operador tenemos que a partir de los tokens de un string vamos a buscar lo que es el que corresponde al indice indicado mediante
	/// el valor del Index , con esto podemos consultar por ejemplo valores que esten en paridades.
	/// 
	/// Observemos el siguiente ejemplo :
	/// 
	/// @code{.cpp}
	/// 
	/// 	const auto StringOriginal = "OSO=NORMAL" <SPair <0>> '=';
	/// 	const auto StringOriginal2 = "OSO=NORMAL" <SPair <1>> '=';
	/// 	
	/// 	// Result : "OSO" , "NORMAL"
	/// 	
	/// @endcode
	/// 
	/// @note
	/// El operando derecho determina el caracter a utilizar para <b>separar</b> la cadena mientras que el parametro de plantilla determina el <b>indice</b> de
	/// contenedor a utilizar como posicion.
	/// 
	/// @see IsIterable
	/// 
	// -----------------------------------------------------------------------------
	
	template <size_t Index>
	inline auto SPair = MakeNamedOperator (StringPair <Index>);
	
	/// @}
	
	// -----------------------------------------------------------------------------
	
}

// Ahora intentaremos anexar algunas utilerias para validaciones de type_traits sobre los elementos de contenedor.

// -----------------------------------------------------------------------------

// Validamos que contemos con el estandar C++ 20 para poder continuar.

#if __cplusplus >= 202002L

// -----------------------------------------------------------------------------

// Incluiremos lo siguiente.

// -----------------------------------------------------------------------------
// 
// 							INCLUDES HEADERS
// 							
// -----------------------------------------------------------------------------

// Incluiremos los rangos para el caso de c++ 20.

#include <ranges>

// Incluiremos los conceptos de c++ 20.

#include <concepts>

// -----------------------------------------------------------------------------

// Tenemos lo siguiente para poder validar que en todo momento se tengan valores variadicos independientes.

// -----------------------------------------------------------------------------
// 
// 					VARIADIC DISJUNCTION TYPE ALIAS
// 							
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

// Tenemos un tipo de dato Aliasing que deriva directamente de un integral constant y a su vez que permite
// recibir cuaquier conjunto de plantillas para validar que se tengan los datos establecidos correctamente.

template <typename Type , template <typename ...> typename ... TValidations>
struct AliasValidation : std::conjunction <TValidations <Type> ...> , std::type_identity <Type> {
	
	// Tenemos lo siguiente para poder validar que contemos con los miembros establecidos.
	
	// -----------------------------------------------------------------------------
	
	// Definiremos el alias para el tipo de dato propio del identity.
	
	using type = typename std::type_identity <Type>::type;
	
	// Definiremos el value constante con un std::conjunction de todo el conjunto de elementos para validar algo.
	
	static constexpr bool value = std::conjunction <std::true_type , TValidations <type> ...>::value;
	
	// -----------------------------------------------------------------------------
	
};

// Ahora añadiremos nuestro pequeño traits para poder validar tipos de funciones que devuelven algo y reciben algo.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 						LAMBDA/FUNCTION TYPE TRAITS
// 							
// -----------------------------------------------------------------------------

// Ahora tenemos lo siguiente que es la validación de nuestro respectivo struct para el tipo de dato de una función
// cuyo operador () esté sobrecargado.

template <typename TFunction>
struct FunctionTraits : FunctionTraits <decltype (&TFunction::operator ())> { /* Derivado */ };

// Ahora tenemos la especialización de esta plantilla para poder determinar los tipos de retorno de nuestro lambda asi
// como para poder determinar los tipos de los argumentos de la función.

template <typename TBase , typename TReturn , typename ... TArgs>
struct FunctionTraits <TReturn (TBase:: *) (TArgs ...) const> {
	
	// Implementaremos todos los alias para los tipos de los que dispone nuestra función actual en estos momentos.
	
	// -----------------------------------------------------------------------------
	
	// Capturamos el tipo de dato de la base de la siguiente manera.
	
	using base_type = std::decay_t <TBase>;
	
	// Capturamos el tipo de dato de retorno del operador de llamada sobre el tipo de función en cuestión.
	
	using return_type = std::decay_t <TReturn>;
	
	// Capturamos el tipo de dato del N-Simo argumento en la función en cuestión , para esto tenemos la estructura
	// siguiente la cuál es un trait obre el respectivo conjunto de argumentos.
	
	template <size_t NArg>
	struct ArgumentTypes : std::tuple_element <NArg , std::tuple <TArgs ...>> { /* Derivado de tuple-element */ };
	
	// Ahora un alias de plantilla para acceder al tipo directamente sobre la estructura obtenida.
	
	template <size_t NArg = 0u>
	using argument_type = std::decay_t <typename ArgumentTypes <NArg>::type>;
	
	// -----------------------------------------------------------------------------
	
};

// Ahora tenemos la especialización para cuando se trata de un metodo y tenemos entonces que asociarlo a un lambda respectivo.

template <typename TBase , typename TReturn , typename ... TArgs>
struct FunctionTraits <TReturn (TBase:: *) (TArgs ...)> : FunctionTraits <TReturn (TBase:: *) (TArgs ...) const> { /* Derivado */ };

// Ahora tenemos el caso cuando se trata de un puntero a función/metodo estatico y tenemos que asociarlo de igual forma al lambda base.

template <typename TReturn , typename ... TArgs>
struct FunctionTraits <TReturn (*) (TArgs ...)> : FunctionTraits <TReturn (std::any:: *) (TArgs ...) const> { /* Derivado */ };

// Tenemos el siguiente caso cuando se trata de una función trivial que se haya declarado en algún bloque.

template <typename TReturn , typename ... TArgs>
struct FunctionTraits <TReturn (TArgs ...)> : FunctionTraits <TReturn (*) (TArgs ...)> { /* Derivado */ };

// Ahora definiremos un conjunto de funciones para gestion de rangos entre tuplas y diferentes valores.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							TUPLE LIKE MANAGER
// 							
// -----------------------------------------------------------------------------

// Tenemos un conjunto de funciones que realizan gestion y filtrado de conjuntos en los cuales se pueden iterar con elementos de tipo tupla para poder
// filtrar o aplicar funciones a determinados sub-conjuntos del mismo contenido.

// -----------------------------------------------------------------------------

// Definiremos primero una funcion template de filtro que permite establecer un metodo de validacion que permite comparar los N-Elementos determinados
// por indices de determinadas tuplas y el valor de tupla que contenga dichos valores para comparar.

template <typename TTuple , typename TValue , typename TIndex , TIndex ... Indexs>
requires requires (const TValue & operand) {
	
	// Debemos asegurar que el primer tipo y el segundo son un valor tuple-like construible entre ellos..
	
	{ std::tuple <std::tuple_element_t <Indexs , TTuple> ...> (operand) };
	
	// Debemos saber que son comparables entre ellos tomando los valores respectivos para cada indice obtenido.
	
	requires std::equality_comparable_with <std::tuple <std::tuple_element_t <Indexs , TTuple> ...> , TValue>;
	
	// -----------------------------------------------------------------------------
	
}
static ALWAYS_INLINE bool ContainerTupleFilter (const TTuple & input , const TValue & value ,
	std::integer_sequence <TIndex , Indexs ...> = std::make_index_sequence <std::tuple_size_v <TTuple>> { }) {
	
	// Ahora pasaremos a lo siguiente para poder validar que son iguales ambos elementos.
	
	// -----------------------------------------------------------------------------
	
	// Tenemos que realizar la comparacion de ambos valores para poder determinar si son iguales con el valor de la posición especfico
	
	return (std::tuple (std::get <Indexs> (input) ...) == value);
	
	// -----------------------------------------------------------------------------
	
}

// Ahora definiremos un metodo para poder filtrar todos los sub-elementos que tenemos y conformar un tipo de container con todos los elementos que
// validen con un determinado filtro de datos para determinado container de entrada y de salida.

template <template <typename ...> typename TTemplate , typename TContainerInput , typename TValue , typename TIndex , TIndex ... Indexs>
requires requires (const TContainerInput & input) {
	
	// Requerimos que sea un iterable.
	
	requires ContainerTraits::IsIterable <TContainerInput>;
	
	// Requerimos que tenga definido el value_type.
	
	requires ContainerTraits::HasTypeMember <TContainerInput>;
	
	// Asi mismo que nuestro container de salida sea insertable.
	
	requires IsInsertable <TTemplate , typename TContainerInput::value_type>;
	
	// -----------------------------------------------------------------------------
	
}
static decltype (auto) ContainerTupleSub (const TContainerInput & inputContainer , const TValue & value ,
	std::integer_sequence <TIndex , Indexs ...> sequence = std::make_index_sequence <std::tuple_size_v <typename TContainerInput::value_type>> { }) {
	
	// Usaremos el valor devuelto por el typename de nuestro input container.
	
	using TValueOutput = TContainerInput::value_type;
	
	// Crearemos el alias para el container de salida.
	
	using TContainer = ContainerType <TTemplate , TValueOutput>; 
	
	// Crearemos nuestro tipo de alias para el container type.
	
	using AContainer = AlterContainer <TTemplate , TValueOutput>;
	
	// Usaremos el espacio de nombres de los placeholders.
	
	using namespace std::placeholders;
	
	// Crearemos nuestro container resultado para la salida.
	
	TContainer result;
	
	// Ahora continuaremos con lo siguiente.
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							CONFORM CONTAINER VALUES
	// 							
	// -----------------------------------------------------------------------------
	
	// Primero conformaremos lo que es nuestro alias para la funcion de filtro que usaremos para buscar los elementos.
	
	const auto currentFilter = std::bind (&ContainerTupleFilter <TValueOutput , TValue , TIndex , Indexs ...> , _1 , std::cref (value) , sequence);
	
	// Buscaremos todos los elementos que cumplan determinado filtro y los iremos conformando en un container resultado de la siguiente manera.
	
	if (!inputContainer.empty ()) for (const auto & element : inputContainer | std::views::filter (currentFilter)) {
		
		// Anexaremos el elemento en nuestro container resultado.
		
		AContainer::push (result , element);
		
		// -----------------------------------------------------------------------------
		
	}
	
	// -----------------------------------------------------------------------------
	
	// Finalmente devolveremos nuestro container resultante.
	
	return result;
	
}

// Ahora tenemos otra funcion para aplicar cualquier funcion que se quiera sobre cada valor arrojado por el respectivo filtrador de la siguiente forma.

template <typename TFunction , typename TContainerInput , typename TValue , typename TIndex , TIndex ... Indexs>
requires requires (const TContainerInput & input , const TFunction & currentFunction) {
	
	// Requerimos que sea un iterable.
	
	requires ContainerTraits::IsIterable <TContainerInput>;
	
	// Requerimos que tenga definido el value_type.
	
	requires ContainerTraits::HasTypeMember <TContainerInput>;
	
	// Requerimos que la funcion pueda invocarse con los valores obtenidos de cada elemento.
	
	{ currentFunction (std::declval <typename TContainerInput::value_type> ()) };
	
	// -----------------------------------------------------------------------------
	
}
static void ContainerTupleEach (const TContainerInput & inputContainer , const TValue & value , const TFunction & currentFunction ,
	std::integer_sequence <TIndex , Indexs ...> sequence = std::make_index_sequence <std::tuple_size_v <typename TContainerInput::value_type>> { }) {
	
	// Usaremos el valor devuelto por el typename de nuestro input container.
	
	using TValueOutput = TContainerInput::value_type;
	
	// Usaremos el espacio de nombres de los placeholders.
	
	using namespace std::placeholders;
	
	// Ahora continuaremos con lo siguiente.
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							CONFORM CONTAINER VALUES
	// 							
	// -----------------------------------------------------------------------------
	
	// Primero conformaremos lo que es nuestro alias para la funcion de filtro que usaremos para buscar los elementos.
	
	const auto currentFilter = std::bind (&ContainerTupleFilter <TValueOutput , TValue , TIndex , Indexs ...> , _1 , std::cref (value) , sequence);
	
	// Buscaremos todos los elementos que cumplan determinado filtro y los iremos conformando en un container resultado de la siguiente manera.
	
	if (!inputContainer.empty ()) for (const auto & element : inputContainer | std::views::filter (currentFilter)) {
		
		// Aplicaremos nuestra fncion directamente sobre este elemento.
		
		currentFunction (element);
		
		// -----------------------------------------------------------------------------
		
	}
	
	// -----------------------------------------------------------------------------
	
}

// -----------------------------------------------------------------------------

// Finalizamos el macro if.

#endif // C++ 20

// -----------------------------------------------------------------------------

// Finalmente cerraremos el enclosed de cabecera.

#endif // CONTAINER_TRAITS_H

/// @}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
