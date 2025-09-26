
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		SYNCRONIZED CONTAINERS
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Tenemos lo siguiente que será una utileria para poder realizar la creacion de containers que funcionen con base a diferentes tipos de contenedores para
// poder tener un mecanismo de sincronia para diferentes hilos y que pueda personalizarse el tipo de contenedor que debe de estar incluido y conteemplado
// para todos estos casos.

/// ----------------------------------------------------------------------------
/// 
/// @brief Administrador de contenedores Seguros para concurrencia con Thread-Safe.
/// 
/// @details
/// 
/// El SyncContainer es un modulo dentro de los gestionadores de containers que se basa en un template generico de contenedores para poder establecer un
/// mecanismo de alto nivel de abstracción sobre todos los tipos de contenedores y compartiendo propiedades que para algunos contenewdores ppudieran
/// no estar presente pero para otros si.
/// 
/// @{
/// 
// -----------------------------------------------------------------------------

// Definiremos lo siguiente para poder guardar el archivo de encabezado.

#pragma once

// -----------------------------------------------------------------------------
/// 
/// @file sync_container.h
/// 
/// @brief Archivo con la declaracion del template para el contenedor de sincronizacion que permite crear estructuras de datos seguras para usar
/// en un entorno multi-thread y evitando errores.
/// 
/// @details
/// 
/// Se tiene una clase que encapsula un container de cualquier tipo para poder gestionar la información de manera segura para usar en varios
/// hilos a la vez.
/// 
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// @addtogroup ContainerTraits
/// @{
// -----------------------------------------------------------------------------

// Definiremos la macro guard para poder asegurar que no se repita nuestro codigo.

#ifndef CYTTEK_SYNC_CONTAINER_HPP
#define CYTTEK_SYNC_CONTAINER_HPP

// Incluiremos las bases para poder comenzar y poder iniciar a realizar la lectura 

// -----------------------------------------------------------------------------

// Incluiremos los elementos base para los printf , scant , cin y cout para pintar sobre la salida estandar de nuestro aplicativo.

#include <stdio.h>
#include <stdlib.h>

// Requerimos asi mismo la inclusion de los strings para el manejo de etodo lo relacionado a nuestras cadenas.

#include <string.h>
#include <string>

// Para la metaprogramación requerimos de las siguientes utilerias.

#include <type_traits>
#include <concepts>

// Inccluiremos las utilerias base para c++ 11.

#include <utility>
#include <optional>
#include <functional>
#include <memory>

// Incluiremos funciones de algorithm y rangos.

#include <algorithm>
#include <ranges>

// Incluiremos el acceso a elementos de conmcurrencia como los hilos , mutex , condiciones variables y furutors.

#include <thread>
#include <condition_variable>
#include <mutex>
#include <shared_mutex>
#include <future>

// Ahora pasaremos a incluir modulos principales para poder usar utilerias y otros elementos de la base.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							CYTTEK CORE INCLUDE
// 							
// -----------------------------------------------------------------------------

// Incluiremos el elemento core para tener acceso a todos los elementos que necesitamos

#include "core.hpp"

// Incluiremos las utilerias para poder acceder a diferentes funciones de utilidad.

#include "utility.hpp"

// Ahora pasaremos a la definición de todo el contenido para nuestra clase de plantilla que contempla el meta-sync-container.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		SINCRONIZER CONTAINER
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Tendremos una clase de template la cual permitirá tener un metodo para sincronizacion de diferentes tipos de containers tanto para el insertado de datos
// como para el acceso a los mismos mediante condiciones futuras o mediante validaciones de la siguiente forma.

// -----------------------------------------------------------------------------

// Tendremos lo que es un container para poder gestionar los accesos a nuestro container interno de manera segura para todos los threads con los que se
// comparte dicho contenedor.

// -----------------------------------------------------------------------------
// 
// 							SYNC CONTAINER CLASS
// 							
// -----------------------------------------------------------------------------

// Definiremos el template con todos los miembros y metodos para la gestión de la información contenida dentro de nuestro objeto.

template <template <typename ...> typename TTemplate , typename ... TValues>
requires (IsValidContainer <TTemplate , TValues ...> and IsIterable <TTemplate , TValues ...>)
class SyncContainer {
	
	// Ahora vamoos a declarar los elementos y propiedades de nuestro sync_container de la siguienteforma.
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							PRIVATE ATTRIBUTES
	// 							
	// -----------------------------------------------------------------------------
	
	// Declaramos nuestro elemento interno para poder gestionar la información de la siguiente forma.
	
	private :
		
		// -----------------------------------------------------------------------------
		
		// Ahora vamos a declarar nuestro elemento privado del container de la siguiente forma.
		
		using TContainer = ContainerType <TTemplate , TValues ...>;
		
		// Ahora para el alterador de nuestro container tendremos lo siguiente.
		
		using AContainer = AlterContainer <TTemplate , TValues ...>;
		
		// Declaramos nuestro tipo de dato de la siguiente forma.
		
		using ValueType = typename AContainer::value_type;
		
		// Ahora nuestra instancia para nuestro container del tipo respectivo que tendremos de la siguiente forma.
		
		TContainer currentData;
		
		// Ahora nuestro mutex asociado a nuestro container para el acceso a la información de la siguiente forma.
		
		mutable std::shared_mutex currentMutex;
		
		// Ahora una condicion variable de cualquier tipo que sea modificable en cualquier contexto.
		
		mutable std::condition_variable_any currentCondition;
		
		// Definiremos un objeto que libeeree la condicion al ser destruido.
		
		struct ConditionReleaser {
			
			// Obtendremos la referencia a una condicion variable de la siguiente forma.
			
			std::add_lvalue_reference_t <decltype (currentCondition)> releaserCondition;
			
			// Anexaremos lo que es el destructor.
			
			~ConditionReleaser () {
				
				// Liberamos la condicion.
				
				releaserCondition.notify_all ();
				
				// -----------------------------------------------------------------------------
				
			}
			
			// -----------------------------------------------------------------------------
			
		};
		
		// -----------------------------------------------------------------------------
	
	// Ahora para los meetodos publicos de acceso a cualquier parte tendremos lo siguiente.
	
	// -----------------------------------------------------------------------------
	// 
	// 							METODOS PUBLICOS
	// 							
	// -----------------------------------------------------------------------------
	
	// Definiremos los metodos publicos de nuestro container de soncrinizacion.
	
	public :
		
		// Definiremos primero los tipos publicos para usar en ambitos externos.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							PUBLIC ALIAS
		// 							
		// -----------------------------------------------------------------------------
		
		// Definiremos el alias de nuestro tipo de la siguiente forma.
		
		typedef TContainer container_type;
		
		// Ahora definiremos el alias para nuestro tipo de valor internio.
		
		typedef ValueType value_type;
		
		// Definiremos el tipo del iterador interno.
		
		typedef typename TContainer::iterator iterator;
		
		// Definirelos el alias para nuestro const_iterator.
		
		typedef typename TContainer::const_iterator const_iterator;
		
		// -----------------------------------------------------------------------------
		
		// Definiremos ahora los constructores para nuestro elemento de la siguiente forma.
		
		// -----------------------------------------------------------------------------
		// 
		// 							CONSTRUCTORES
		// 							
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		
		// Ahora definiremos primero nuestro constructor por defecto para poder ir llenando nuestro container con los elementos respectivos.
		
		SyncContainer () = default;
		
		// Ahora lo siguiente son el constructor de copia por defecto.
		
		SyncContainer (const SyncContainer & copy) = default;
		
		// Ahora para poder mover todos los elemeentos tendremos lo siguiente.
		
		SyncContainer (SyncContainer && move) = default;
		
		// Ahora tendremos un constructor adicional para poder construir internamente nuestro objeto con un perfect-forwarding.
		
		template <typename ... TInputValues>
		requires (std::is_constructible_v <TContainer , TInputValues ...>)
		SyncContainer (TInputValues && ... values) : currentData (std::move (TContainer (std::forward <TInputValues> (values) ...))) { /* Inicializado */ }
		
		// Ahora pasareos a lo intereesante para el acceeso a los datos , poder inseertar elementos o eliminar elementos.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							INSERTERS CONTAINER
		// 							
		// -----------------------------------------------------------------------------
		
		// Comenzaremos primero por el metodo push para poder insertar un nuevo elemento con el funcionamiento de un push (pila o vector) de la 
		// siguiente forma.
		
		template <typename ... TInputValues>
		requires (IsInsertable <TTemplate , TValues ...>)
		auto Push (TInputValues && ... elements) {
			
			// Para poder pushear un valor nuevo en el container tendremos lo siguiente.
			
			// -----------------------------------------------------------------------------
			
			// -----------------------------------------------------------------------------
			// 
			// 							PUSH NEW ELEMENT
			// 							
			// -----------------------------------------------------------------------------
			
			// Ahora crearemos un tipo de dato de retorno de la funcion.
			
			using TReturn = decltype (AContainer::push (currentData , std::forward <TInputValues> (elements) ...));
			
			// Ahora para un valor valido tendremos que validar si es void o no.
			
			constexpr bool TReturnValid = not std::is_void_v <TReturn>;
			
			// El resultado será la validacion del tipo de dato o bool por default.
			
			std::conditional_t <TReturnValid , TReturn , bool> result;
			
			// Primero crearemos nuestro releaser de la notificacion.
			
			ConditionReleaser currentReleaser { currentCondition };
			
			// Crearemos el bloque para asegurarnos de liberar mutex.
			
			{
				// Crearemos nuestro lock para el mutex de la siguiente manera.
				
				std::unique_lock <std::shared_mutex> currentLock (currentMutex);
				
				// Asignaremos la llamada del container si es valido el tipo de retorno.
				
				if constexpr (TReturnValid) result = AContainer::push (currentData , std::forward <TInputValues> (elements) ...);
				else 						result = (AContainer::push (currentData , std::forward <TInputValues> (elements) ...) , true);
				
				// -----------------------------------------------------------------------------
				
			}
			
			// Devolveremos el resultado.
			
			return result;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para el caso del metodo insert tendremos lo siguiente.
		
		template <typename ... TInputValues>
		requires (AContainer::has_insert or AContainer::has_insert_position)
		auto Insert (TInputValues && ... elements) {
			
			// Para podeer insertar un elemento indicado.
			
			// -----------------------------------------------------------------------------
			
			// -----------------------------------------------------------------------------
			// 
			// 							INSERT NEW ELEMENT
			// 							
			// -----------------------------------------------------------------------------
			
			// Ahora crearemos un tipo de dato de retorno de la funcion.
			
			using TReturn = decltype (AContainer::insert (currentData , std::forward <TInputValues> (elements) ...));
			
			// Ahora para un valor valido tendremos que validar si es void o no.
			
			constexpr bool TReturnValid = not std::is_void_v <TReturn>;
			
			// El resultado será la validacion del tipo de dato o bool por default.
			
			std::conditional_t <TReturnValid , TReturn , bool> result;
			
			// Crearemos nuestro releaser de la notificacion.
			
			ConditionReleaser currentReleaser { currentCondition };
			
			// Crearemos el bloque para poder establece la info.
			
			{
				
				// Crearemos nuestro lock para el mutex de la siguiente manera.
				
				std::unique_lock <std::shared_mutex> currentLock (currentMutex);
				
				// Asignaremos la llamada del container si es valido el tipo de retorno.
				
				if constexpr (TReturnValid) result = AContainer::insert (currentData , std::forward <TInputValues> (elements) ...);
				else 						result = (AContainer::insert (currentData , std::forward <TInputValues> (elements) ...) , true);
				
				// -----------------------------------------------------------------------------
				
			}
			
			// Devolveremos el resultado.
			
			return result;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para poder construir e insertar un determinado valor tendremos lo siguiente.
		
		template <typename ... TInputValues>
		requires ((AContainer::has_emplace or AContainer::has_emplace_back or AContainer::has_emplace_position) and std::is_constructible_v <ValueType , TInputValues ...>)
		auto Emplace (TInputValues && ... elements) {
			
			// Para poder construir e insertar directamente el elemeento en el container si lo ssoporta.
			
			// -----------------------------------------------------------------------------
			
			// -----------------------------------------------------------------------------
			// 
			// 							EMPLACE NEW ELEMENT
			// 							
			// -----------------------------------------------------------------------------
			
			// Ahora crearemos un tipo de dato de retorno de la funcion.
			
			using TReturn = decltype (AContainer::emplace (currentData , std::forward <TInputValues> (elements) ...));
			
			// Ahora para un valor valido tendremos que validar si es void o no.
			
			constexpr bool TReturnValid = not std::is_void_v <TReturn>;
			
			// El resultado será la validacion del tipo de dato o bool por default.
			
			std::conditional_t <TReturnValid , TReturn , bool> result;
			
			// Crearemos nuestro releaser de la notificacion.
			
			ConditionReleaser currentReleaser { currentCondition };
			
			// Creasremos el bloqur d codigo para lo siguiente.
			
			{
				
				// Crearemos nuestro lock para el mutex de la siguiente manera.
				
				std::unique_lock <std::shared_mutex> currentLock (currentMutex);
				
				// Asignaremos la llamada del container si es valido el tipo de retorno.
				
				if constexpr (TReturnValid) result = AContainer::emplace (currentData , std::forward <TInputValues> (elements) ...);
				else 						result = (AContainer::emplace (currentData , std::forward <TInputValues> (elements) ...) , true);
				
				// -----------------------------------------------------------------------------
					
			}
			
			// Devolveremos el resultado.
			
			return result;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora pasaremos a los accesos a la información de nuestro container.
		
		// -----------------------------------------------------------------------------
		// 
		// 							ACCESORS CONTAINER
		// 							
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		
		// Para poder acceder a nuestro valor final tendremos un metodo para el acceso desde el frente (si está presente).
		
		std::optional <ValueType> Front (bool waitForValue = false) const {
			
			// Para acceder al valor frontal (primer element).
			
			// -----------------------------------------------------------------------------
			
			// -----------------------------------------------------------------------------
			// 
			// 							FRONT ELEMENT ACCESS
			// 							
			// -----------------------------------------------------------------------------
			
			// Crearemos nuestro shared_lock de la siguiente forma.
			
			std::shared_lock <std::shared_mutex> currentLock (currentMutex);
			
			// Ahora validaremos si tenemos el metodo empty de la siguiente forma.
			
			if constexpr (AContainer::has_empty) if (waitForValue) {
				
				// Realizaremos la espera de que nuestro container no esté vacio de la siguiente forma.
				
				currentCondition.wait (currentLock , [&] () -> bool { return !currentData.empty (); });
				
				// -----------------------------------------------------------------------------
				
			}
			
			// Validaremos si hay elementos disponibles asi como validaremos si tiene la operación front definida de la siguiente manera.
			
			if (!currentData.empty ()) if constexpr (requires { { TContainer ().front () } -> std::convertible_to <ValueType>; }) {
				
				// Accediendo al dato internamente o simplemente devolviendo lo que tenemos.
				
				return currentData.front ();
				
				// -----------------------------------------------------------------------------
				
			}
			else if constexpr (AContainer::has_at) {
				
				// Validaremos si tiene el metodo has count para saber si será un dato lo que mandaremos.
				
				if constexpr (AContainer::has_count and requires (ValueType element) { { std::get <0> (element) } -> std::convertible_to <size_t>; }) {
					
					// Devolveremos el valor respectivo.
					
					if (currentData.count (static_cast <typename TContainer::key_type> (0))) return ValueType (0 , currentData.at (size_t (0)));
					
					// -----------------------------------------------------------------------------
					
				}
				else if constexpr (AContainer::has_size) return currentData.at (0);
				
				// -----------------------------------------------------------------------------
				
			}
			
			// Devolveremos un vacio por default.
			
			return std::nullopt;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para el caso del metodo back tendremos lo siguiente.
		
		std::optional <ValueType> Back (bool waitForValue = false) const {
			
			// Ahora para acceder a lo que el elemento del fondo.
			
			// -----------------------------------------------------------------------------
			
			// -----------------------------------------------------------------------------
			// 
			// 							BACK ELEMENT ACCEESS
			// 							
			// -----------------------------------------------------------------------------
			
			// Crearemos nuestro shared_lock de la siguiente forma.
			
			std::shared_lock <std::shared_mutex> currentLock (currentMutex);
			
			// Ahora validaremos si tenemos el metodo empty de la siguiente forma.
			
			if constexpr (AContainer::has_empty) if (waitForValue) {
				
				// Realizaremos la espera de que nuestro container no esté vacio de la siguiente forma.
				
				currentCondition.wait (currentLock , [&] () -> bool { return !currentData.empty (); });
				
				// -----------------------------------------------------------------------------
				
			}
			
			// Validaremos si hay elementos disponibles y validaremos si tiene la operación back definida de la siguiente manera.
			
			if (!currentData.empty ()) if constexpr (requires { { TContainer ().back () } -> std::convertible_to <ValueType>; }) {
					
				// Accediendo al dato internamente o simplemente devolviendo lo que tenemos.
				
				return currentData.back ();
				
				// -----------------------------------------------------------------------------
				
			}
			
			// Devolveremos un vacio por default.
			
			return std::nullopt;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para poder consultar un determinado container por su indice (llave) en caso de que sea correcta.
		
		template <typename TIndex>
		requires (AContainer::has_at)
		std::optional <ValueType> At (TIndex index , bool waitForValue = false) const {
			
			// Busca un determinado indice y devuelve el valor del container.
			
			// -----------------------------------------------------------------------------
			
			// -----------------------------------------------------------------------------
			// 
			// 							CURRENT AT ELEMENT
			// 							
			// -----------------------------------------------------------------------------
			
			// Crearemos nuestro shared_lock de la siguiente forma.
			
			std::shared_lock <std::shared_mutex> currentLock (currentMutex);
			
			// Ahora validaremos si tenemos el metodo empty de la siguiente forma.
			
			if constexpr (AContainer::has_empty) if (waitForValue) {
				
				// Realizaremos la espera de que nuestro container no esté vacio de la siguiente forma.
				
				currentCondition.wait (currentLock , [&] () -> bool { return !currentData.empty (); });
				
				// -----------------------------------------------------------------------------
				
			}
			
			// Ahora para acceder al contenido tendremos que validar si nuestro tipo de contenedor soporta el metodo At y al mismo tiempo
			// si es posible convertir el tipo de indice al tipo de llave que acepta.
			
			if (!currentData.empty ()) if constexpr (requires {
				
				// Validaremos si existe el tipo de dato key_type dentro del tipo de container.
				
				typename TContainer::key_type;
				
				// Ahora validaremos si el tipo de dato es convertible.
				
				requires std::is_convertible_v <TIndex , typename TContainer::key_type>;
				
				// Validaremos si la expresión siguiente es valida.
				
				{ TContainer ().at (std::declval <TIndex> ()) };
				
				// -----------------------------------------------------------------------------
				
			}) {
				
				// Devolveremos el valor respectivo que estamos esperando.
				
				return std::make_pair (index , currentData.at (index));
				
				// -----------------------------------------------------------------------------
				
			}
			else if constexpr (requires { { TContainer ().at (std::declval <TIndex> ()) } -> std::convertible_to <ValueType>; }) {
				
				// Ahora devolveremos el siguiente valor.
				
				return currentData.at (index);
				
				// -----------------------------------------------------------------------------
				
			}
			
			// Devolveremos un vacio por default.
			
			return std::nullopt;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para consultar si un elemento existe o la cantidad de elementos iguales que hay en nuestro container tendremos lo siguiente.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							CONTAINER ALGORITHMS
		// 							
		// -----------------------------------------------------------------------------
		
		// Tendremos el apartado de los algoritmos para busqueda , validacion de cantidad , etc.
		
		// -----------------------------------------------------------------------------
		
		// Definiremos lo siguiente para poder determinar si un elemento existe dentro de nuestro container.
		
		template <typename TValidation>
		auto Find (const TValidation & element) const {
			
			// Ahora tendremos lo siguiente para poder buscar un elemento o un Predicate determinado.
			
			// -----------------------------------------------------------------------------
			
			// -----------------------------------------------------------------------------
			// 
			// 							FIND ELEMENT
			// 							
			// -----------------------------------------------------------------------------
			
			// Crearemos nuestro shared_lock de la siguiente forma.
			
			std::shared_lock <std::shared_mutex> currentLock (currentMutex);
			
			// Ahora tendremos lo siguiente para poder buscar nuestro elemento y poderlo devolver de la siguiente forma.
			
			if constexpr (requires { { currentData.find (element) }; }) {
				
				// Devolveremos la busqueda dentro del mapa o elemento con esta condicion.
				
				return currentData.find (element);
				
				// -----------------------------------------------------------------------------
				
			}
			else if constexpr (requires { { std::ranges::find (currentData , element) }; }) {
				
				// Buscaremos usando el tradicional find de ranges.
				
				return std::ranges::find (currentData , element);
				
				// -----------------------------------------------------------------------------
				
			}
			else if constexpr (requires { { element (std::declval <ValueType> ()) } -> std::convertible_to <bool>; }) {
				
				// Buscaremos usando la libreria de rangos find_if de la siguiente forma.
				
				return std::ranges::find_if (currentData , element);
				
				// -----------------------------------------------------------------------------
				
			}
			
			// De otra forma devolveremos un end.
			
			return currentData.end ();
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora lo que haremos será validar para saber si un elemento está contenido o no de la siguiente forma.
		
		template <typename TValidation>
		ALWAYS_INLINE bool Contains (const TValidation & element) const {
			
			// Devolveremos la llamada a find de la siguiente forma.
			
			return (Find (element) != std::ranges::end (currentData));
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora pasaremos para los elementos que eliminn datos dentro de la estructura de daos.
		
		// -----------------------------------------------------------------------------
		// 
		// 							ERASE ELEMENTS CONTAINER
		// 							
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		
		// Ahora tendremos lo siguiente para poder establecer lo que es nuestro respectivo metodo para eliminar el elemento del tope.
		
		bool Pop (bool waitForValue = false) {
			
			// Para eliminar un eelemento del final teendremos lo siguiente.
			
			// -----------------------------------------------------------------------------
			
			// -----------------------------------------------------------------------------
			// 
			// 							POP BACK ELEMENT
			// 							
			// -----------------------------------------------------------------------------
			
			// Crearemos nuestro unique_lock de la siguiente forma.
			
			std::unique_lock <std::shared_mutex> currentLock (currentMutex);
			
			// Ahora validaremos si tenemos el metodo empty de la siguiente forma.
			
			if constexpr (AContainer::has_empty) if (waitForValue) {
				
				// Realizaremos la espera de que nuestro container no esté vacio de la siguiente forma.
				
				currentCondition.wait (currentLock , [&] () -> bool { return !currentData.empty (); });
				
				// -----------------------------------------------------------------------------
				
			}
			
			// Validaremos de la siguiente manera si el elemento soporta pop para eliminar el elemento respectivo.
			
			if constexpr (AContainer::has_pop) if (!currentData.empty ()) {
				
				// Borraremos nuestro ultimo elemento.
				
				AContainer::pop (currentData);
				
				// Devolveremos true.
				
				return true;
				
				// -----------------------------------------------------------------------------
				
			}
			
			// Devolveremos false de otro modo.
			
			return false;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para poder eliminar un determinado elemento por su posicion tendremos lo siguiente.
		
		template <typename TFinder>
		requires (AContainer::has_erase and HasIterator <TTemplate , TValues ...>)
		void Erase (const TFinder & element , bool waitForValue = false) {
			
			// Para eliminar un elmento por su posicion o valor tendremos lo siguiente.
			
			// -----------------------------------------------------------------------------
			
			// -----------------------------------------------------------------------------
			// 
			// 							ERASE CURRENT ELEMENT
			// 							
			// -----------------------------------------------------------------------------
			
			// Crearemos nuestro unique_lock de la siguiente forma.
			
			std::unique_lock <std::shared_mutex> currentLock (currentMutex);
			
			// Ahora validaremos si tenemos el metodo empty de la siguiente forma.
			
			if constexpr (AContainer::has_empty) if (waitForValue) {
				
				// Realizaremos la espera de que nuestro container no esté vacio de la siguiente forma.
				
				currentCondition.wait (currentLock , [&] () -> bool { return !currentData.empty (); });
				
				// -----------------------------------------------------------------------------
				
			}
			
			// Tomaremos el tipo de iterador que tenemos de la siguiente manera.
			
			using TIterator = std::conditional_t <HasIterator <TTemplate , TValues ...> , typename TContainer::const_iterator , void>;
			
			// Ahora para poder borrar un elemento tendremos que validar si es convertible a un const iterator de la siguiente forma.
			
			if constexpr (not std::is_void_v <TIterator> and std::is_convertible_v <TFinder , TIterator>) {
				
				// Eliminaremos el eelemento por su respectivo iterador.
				
				AContainer::erase (currentData , static_cast <TIterator> (element));
				
				// -----------------------------------------------------------------------------
				
			}
			else if constexpr (HasBeginEnd <TTemplate , TValues ...> and requires (ValueType compareA) {
				
				// Validaremeos que ambos elementos sean comparables de la siguiente manera.
				
				{ (compareA == element) } -> std::convertible_to <bool>;
				
				// Validaremos si la operacion find está contenida y podemos buscar en el elemento actual.
				
				{ std::find (currentData.begin () , currentData.end () , element) } -> std::convertible_to <TIterator>;
				
				// -----------------------------------------------------------------------------
				
			}) {
				
				// Buscaremos el elemento usando el algoritmo respectivo.
				
				if (const auto currentPosition = std::find (currentData.begin () , currentData.end () , element) ; currentPosition != currentData.end ()) {
					
					// Lo eliminaremos de la siguiente forma.
					
					AContainer::erase (currentData , currentPosition);
					
					// -----------------------------------------------------------------------------
					
				}
				
				// -----------------------------------------------------------------------------
				
			}
			else if constexpr (HasBeginEnd <TTemplate , TValues ...> and requires {
				
				// Validaremos si el predicado es un callable que devuelve true y recibe un valor del value_type.
				
				{ element (std::declval <ValueType> ()) } -> std::convertible_to <bool>;
				
				// Ahora validaremos que si puede llamarse usando find_if.
				
				{ std::find_if (currentData.begin () , currentData.end () , element) } -> std::convertible_to <TIterator>;
				
				// -----------------------------------------------------------------------------
				
			}) {
				
				// Buscaremeos nuestro elemento actual de la siguiente manera.
				
				if (const auto currentPosition = std::find_if (currentData.begin () , currentData.end () , element) ; currentPosition != currentData.end ()) {
					
					// Lo eliminaremos de la siguiente forma.
					
					AContainer::erase (currentData , currentPosition);
					
					// -----------------------------------------------------------------------------
					
				}
				
				// -----------------------------------------------------------------------------
				
			}
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para poder eliminar todos los elementos que tengan una validacion true para el siguiente elemento.
		
		template <typename TValidation>
		requires (AContainer::has_erase and HasIterator <TTemplate , TValues ...>)
		void EraseAllIf (const TValidation & validation , bool waitForValue = false) {
			
			// Para eliminar un elmento por su posicion o valor tendremos lo siguiente.
			
			// -----------------------------------------------------------------------------
			
			// -----------------------------------------------------------------------------
			// 
			// 							ERASE CURRENT ELEMENT
			// 							
			// -----------------------------------------------------------------------------
			
			// Crearemos nuestro unique_lock de la siguiente forma.
			
			std::unique_lock <std::shared_mutex> currentLock (currentMutex);
			
			// Ahora validaremos si tenemos el metodo empty de la siguiente forma.
			
			if constexpr (AContainer::has_empty) if (waitForValue) {
				
				// Realizaremos la espera de que nuestro container no esté vacio de la siguiente forma.
				
				currentCondition.wait (currentLock , [&] () -> bool { return !currentData.empty (); });
				
				// -----------------------------------------------------------------------------
				
			}
			
			// Validaremos si tenemos los iteradores y que el elemento es 
			
			if constexpr (AContainer::has_empty and HasBeginEnd <TTemplate , TValues ...> and requires {
				
				// Validaremos si el predicado es un callable que devuelve true y recibe un valor del value_type.
				
				{ validation (std::declval <ValueType> ()) } -> std::convertible_to <bool>;
				
				// Ahora validaremos que si puede llamarse usando find_if.
				
				{ std::find_if (currentData.begin () , currentData.end () , validation) } -> std::convertible_to <decltype (currentData.end ())>;
				
				// -----------------------------------------------------------------------------
				
			}) if (!currentData.empty ()) {
				
				// Buscaremos nuestro siguiente elemento para poder validar.
				
				auto currentElement = std::find_if (currentData.begin () , currentData.end () , validation);
				
				// Validaremos si el elemento fue encontrado para seguir buscando hasta terminar de eliminar los elementos.
				
				while (currentElement != currentData.end ()) {
					
					// Lo eliminaremos de la siguiente forma.
					
					AContainer::erase (currentData , currentElement);
					
					// Ahora buscaremos el siguiente elemento que cumpla con la condicion.
					
					currentElement = std::find_if (currentData.begin () , currentData.end () , validation);
					
					// -----------------------------------------------------------------------------
					
				}
				
				// -----------------------------------------------------------------------------
				
			}
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para poder limpiar los elementos tendremos simplemente el siguiente metodo.
		
		void Clear (bool waitForValue = false) {
			
			// Para poder eliminar todos los elementos tendremos lo siguientee.
			
			// -----------------------------------------------------------------------------
			
			// -----------------------------------------------------------------------------
			// 
			// 							CLEAR CONTAINER
			// 							
			// -----------------------------------------------------------------------------
			
			// Crearemos nuestro unique_lock de la siguiente forma.
			
			std::unique_lock <std::shared_mutex> currentLock (currentMutex);
			
			// Ahora validaremos si tenemos el metodo empty de la siguiente forma.
			
			if constexpr (AContainer::has_empty) if (waitForValue) {
				
				// Realizaremos la espera de que nuestro container no esté vacio de la siguiente forma.
				
				currentCondition.wait (currentLock , [&] () -> bool { return !currentData.empty (); });
				
				// -----------------------------------------------------------------------------
				
			}
			
			// Limpiaremos los elementos.
			
			if constexpr (AContainer::has_clear) if (!currentData.empty ()) AContainer::clear (currentData);
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora tendremos un par de metodos para el acceso al tamaño y a la validación de si nuestro container está vacio o no.
		
		// -----------------------------------------------------------------------------
		// 
		// 							PROPERTIES CONTAINER
		// 							
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		
		// Para poder validar el tamaño tendremos lo siguiente.
		
		size_t Size () const {
			
			// Crearemos un simple shared_lock para este caso.
			
			std::shared_lock <std::shared_mutex> currentLock (currentMutex);
			
			// Devolveremos el tamaño si tiene la funcion si no devolveremos 0.
			
			if constexpr (AContainer::has_size) return currentData.size (); else return 0;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para poder validar si esta vacio.
		
		bool Empty () const {
			
			// Crearemos un simple shared_lock para este caso.
			
			std::shared_lock <std::shared_mutex> currentLock (currentMutex);
			
			// Validaremos si tiene la funcion si no devolveremos true.
			
			if constexpr (AContainer::has_empty) return currentData.empty (); else return true;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para acceder al container interno tendremos que especificar el operador de conversion.
		
		ALWAYS_INLINE operator decltype (currentData) & () {
			
			// Devolveremos la reeferencia a nuestro container interno.
			
			return currentData;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para la conversion de un tipo de dato const.
		
		ALWAYS_INLINE operator const decltype (currentData) & () const {
			
			// Devolveremos la reeferencia a nuestro container interno.
			
			return currentData;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora otra forma de obtenerla directamente con la palabra GetData.
		
		ALWAYS_INLINE decltype (currentData) & GetData () {
			
			// Devolveremos la reeferencia a nuestro container interno.
			
			return currentData;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para erl modo constante.
		
		ALWAYS_INLINE const decltype (currentData) & GetData () const {
			
			// Devolveremos la reeferencia a nuestro container interno.
			
			return currentData;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
		
		// Ahora para hacerlo iterable tendremos nuestro SyncContainer adapter de la siguiente forma.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							ITERATORS FOR CONTAINER
		// 							
		// -----------------------------------------------------------------------------
		
		// Para lo siguiente tendremos una funcion que nos devolverá lo que es nuestro iterador al inicio de la siguiente forma.
		
		ALWAYS_INLINE iterator begin () noexcept {
			
			// Devolvermeos la referencia a nuestro iterador inicial de la siguiente manera.
			
			return currentData.begin ();
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para poder devolver un const referece tenemos lo siguiente.
		
		ALWAYS_INLINE const_iterator begin () const noexcept {
			
			// Devolvermeos la referencia a nuestro iterador inicial de la siguiente manera.
			
			return currentData.begin ();
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora tendremos lo siguiente para poder devolver un cbegin.
		
		ALWAYS_INLINE const_iterator cbegin () const noexcept {
			
			// Devolvermeos la referencia a nuestro iterador inicial de la siguiente manera.
			
			return currentData.cbegin ();
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para el caso del iterador al final tendremos lo siguiente.
		
		ALWAYS_INLINE iterator end () noexcept {
			
			// Devolvermeos la referencia a nuestro iterador final de la siguiente manera.
			
			return currentData.end ();
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para poder devolver un const referece tenemos lo siguiente.
		
		ALWAYS_INLINE const_iterator end () const noexcept {
			
			// Devolvermeos la referencia a nuestro iterador final de la siguiente manera.
			
			return currentData.end ();
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora tendremos lo siguiente para poder devolver un cbegin.
		
		ALWAYS_INLINE const_iterator cend () const noexcept {
			
			// Devolvermeos la referencia a nuestro iterador final de la siguiente manera.
			
			return currentData.cend ();
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para poder acceder a nuestro mutex interno tendremos lo siguiente.
		
		ALWAYS_INLINE std::shared_mutex & GetMutex () const {
			
			// Devolveremos lo que es nuestro mutex actual.
			
			return currentMutex;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para podere hacer un for each en este respectivo container tendremos lo siguiente.
		
		template <typename TFunction>
		requires requires (TFunction consumer) {
			
			// Validaremos que se pueda invocar usando como artumento un valor respectivo.
			
			{ consumer (std::declval <ValueType> ()) };
			
			// -----------------------------------------------------------------------------
			
		}
		void ForEach (TFunction && consumer) const {
			
			// Crearemos un simple shared_lock para este caso.
			
			std::shared_lock <std::shared_mutex> currentLock (currentMutex);
			
			// Ahora realizaremos la iteración por cada elemento aplicando el consumer respectivo.
			
			for (const auto & element : currentData) consumer (element);
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
		
};

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// @}
// -----------------------------------------------------------------------------

// Finalizaremos la cabecera con el terminador dee nuestro header.

#endif // CYTTEK_SYNC_CONTAINER_HPP

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
