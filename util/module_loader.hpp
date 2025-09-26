
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		MODULO : CARGADOR DE MODULOS - LIBRERIAS
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

/// @defgroup ModuleLoader ModuleLoader
/// @author José Raúl Moreno Acero
/// @brief Con esta utileria se puede gestonar de manera eficiente la carga y descarga de modulos en forma de librerias dinámicas (.dll) con la finalidad
/// de tener un mecanismoa automatizado para realizar dicha tarea asi como la de realizar la invocación de todos los procesos mediante los simbolos exportados
/// de dicha libreria de manera más eficiente que directamente usando la api de C.

// Para esto incluiremos primero nuestro guard para el hpp.

#pragma once

// -----------------------------------------------------------------------------
/// 
/// @file module_loader.hpp
/// 
/// @brief Archivo con la declaracion de todos los elementos para los modulos respectivos , que se encarga de encender el archivo de libreria dinamica
/// y subir eel archivo a la memoria del sistmea.
/// 
/// @details
/// 
/// Con este modulo se puede cargar a la memoria del siwtema e larchiv ode modul ode una dll d ela que dependa nuestro sistema para poder gestionsr
/// de manera dinamica la carga de las mismas.
/// 
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// @addtogroup ModuleLoader
/// @{
// -----------------------------------------------------------------------------

// Ahora vamos a definir los guard para el include.

#ifndef CYTTEK_MODULE_LOADER
#define CYTTEK_MODULE_LOADER

// -----------------------------------------------------------------------------

// Incluiremos las bases para poder realizar uso de las funciones de la biblioteca estandar asi como salida y entrada.

#include <stdio.h>
#include <stdlib.h>

// Incluiremos las bases para manejar los strings.

#include <string.h>
#include <string>

// Incluiremos elementos de utilerias para poder tarbajar con esto.

#include <utility>

// Ahora vamos a incluir los modulos especificos del proyecto para poder establecer datos.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							CYTTEK MODULES INCLUDE
// 							
// -----------------------------------------------------------------------------

// Incluiremos primero nuestro core para poder trabajar con todos los elementos de base.

#include "core.hpp"

// Incluiremos toda laparte de nuestro respectivo logger para poder pintar logs a medida que pasa el get info.

#include "logger.hpp"

// Incluiremos asi mismo las utilerias en general.

#include "utility.hpp"

// Pasaremos a realizar la declaración y definición de la clase de Modulo para poder trabajar con todo el contenido que esta permite ofrecer
// de la siguiente forma.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		CLASE MODULE LOADER
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Esta clase permitirá el uso de las funciones de la api de windows para poder realizar la carga , liberación y utilización de los recursos proporcionados
// por una bibliote ca dinámica en tiempo de ejecución. Para esto tenemos lo siguiente.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// 
// 								CLASE MODULE
// 							
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// La clase Module no es más que un container para todas las funciones y procesos que pueden ser llamados desde una determinada
// biblioteca una vez que esta es establecida y cargada correctamente. Se puede obtener el status para esta clase , saber que directorio de dll se tiene
// asi como el archivo DLL que se cargó en este momento.

class CYTTEK_API Module {
	
	// Definiremos todos los elementos privados para esta clase de la siguiente forma.
	
	// -----------------------------------------------------------------------------
	// 
	// 							PRIVATE PROPERTIES
	// 							
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	
	// Tenemos lo siguiente que es la parte de las propiedades para nuestro modulo actual de la siguiente forma.
	
	private :
		
		// -----------------------------------------------------------------------------
		
		// Ahora definiremos la variable con el Modulo en cuestión para poder cargarlo cuando se requiera.
		
		HMODULE currentModule = nullptr;
		
		// Guardaremos nuestro nombre asociado a este modulo , este también servirá para identificarlo cuando estemos buscando un modulo dentro
		// de un conjunto de varios modulos.
		
		std::string name;
		
		// Declaramos un mapa hash para asociar todos las funciones o procesos que se tienen en nuestro modulo actual y poder invocarlos de
		// manera directa cuando sea necesario.
		
		mutable std::unordered_map <std::string , FARPROC> currentFunctions;
		
		// -----------------------------------------------------------------------------
	
	// Ahora pasaremos con la parte de las funciones para nuestro Loader.
	
	// -----------------------------------------------------------------------------
	// 
	// 							METODOS PUBLICOS
	// 							
	// -----------------------------------------------------------------------------
	
	// Tenemos todos los elementos publicos para utilizar en nuestro loader de la siguiente manera.
	
	public :
	
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							CONSTRUCTOR DE MODULO
		// 							
		// -----------------------------------------------------------------------------
		
		// Estableceremos lo que son nuestros respectivos constructores para poder crear el modulo vacio de momento.
		
		Module () = default;
		
		// Ahora para poder copiar un modulo a otro tendremos definidos nuestros operadores de copia y move de la siguiente forma.
		
		Module (const Module & copy) = default;
		
		// Ahora para el caso de un R-Value tenemos el siguiente constructor.
		
		Module (Module && move);
		
		// Ahora para la asignación por copia definiremos el siguiente.
		
		Module & operator = (const Module & copy) = default;
		
		// Ahora de la misma forma para el r-value asignment.
		
		Module & operator = (Module && move);
		
		// Ahora tendremos el constructor para poder especificarle el archivo que se va a cargar y poder realizar la carga de nuestro modulo
		// de la siguiente forma.
		
		Module (const std::string & moduleFilename);
		
		// Ahora pasaremos a las funciones para la carga de elementos.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							CARGADOR DE MODULOS
		// 							
		// -----------------------------------------------------------------------------
		
		// Para cargar un modulo necesitaremos establecer un metodo que haga posible la carga desde un respectivo archivo filename para el
		// archivo de libreria dinámica que se desee cargar.
		
		bool LoadLibrary (const std::string & moduleFilename);
		
		// Para poder descargar un modulo y liberarlo tendremos lo siguiente.
		
		bool UnloadLibrary () const;
		
		// Para recuperar información sobre este modulo tenemos otras funciones.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							GER PROPERTIES
		// 							
		// -----------------------------------------------------------------------------
		
		// Ahora pasaremos a realizar el metodo para obtener la información respectiva sobre el nombre.
		
		ALWAYS_INLINE const std::string & GetName () const {
			
			// Devolveremos el nombre actual.
			
			return name;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Para saber rápidamente si el modulo está cargado en estos momentos.
		
		ALWAYS_INLINE bool IsLoaded () const {
			
			// Devolveremos true si el HMODULE no es null.
			
			return static_cast <bool> (currentModule);
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora pasaremos a lo que nos interesa que es la parte de la invocación de los procesos.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							INVOQUE MODULE PROCESS
		// 							
		// -----------------------------------------------------------------------------
		
		// Primero tenemos el metodo para poder buscar obtener una función convertida a un tipo en especifico tendremos lo siguiente.
		
		template <typename TFunction>
		requires std::is_pointer_v <TFunction>
		TFunction GetFunction (const std::string & functionName) const {
			
			// -----------------------------------------------------------------------------
			
			// -----------------------------------------------------------------------------
			// 
			// 							OBTENCION DE FUNCTION
			// 							
			// -----------------------------------------------------------------------------
			
			// Primero tendremos el resultado null por defecto.
			
			TFunction currentResult = nullptr;
			
			// Validaremos que tenemos modulo cargado para continuar.
			
			if (currentModule) {
				
				// Ahora pasaremos a realizar la asignación del mapa si es que lo tiene contenido.
			
				if (currentFunctions.count (functionName)) {
					
					// Asignaremos el valor de nuestro mapa directamente convertido al dato que se tiene.
					
					currentResult = reinterpret_cast <TFunction> (currentFunctions.at (functionName));
					
					// -----------------------------------------------------------------------------
					
				}
				else {
					
					// -----------------------------------------------------------------------------
					// 
					// 							CARGAR NUEVO PROCESO
					// 							
					// -----------------------------------------------------------------------------
					
					// Si no está en el mapa todavía entonces lo obtendremos desde el modulo directamente.
					
					currentResult = reinterpret_cast <TFunction> (GetProcAddress (currentModule , Convert <LPCSTR> (functionName.c_str ())));
					
					// si es diferente de null lo anexaremos a nuestro mapa.
					
					if (currentResult) currentFunctions.emplace (functionName , reinterpret_cast <FARPROC> (currentResult));
					
					// -----------------------------------------------------------------------------
					
				}
				
				// -----------------------------------------------------------------------------
				
			}
			
			// Finalmente devolveremos el resultado.
			
			return currentResult;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Para poder invocar las funcionalidades que están dentro de un modulo cargado tendremos un template que nos permita convertir
		// la función respectiva a su tipo en común.
		
		template <typename TReturn , typename ... TParams>
		requires requires (TReturn (* currentFunction) (TParams ...)) {
			
			// -----------------------------------------------------------------------------
			
			// Requerimos que esta función sea invocable con todos los elementos.
			
			{ currentFunction (std::declval <TParams> () ...) } -> std::convertible_to <TReturn>;
			
			// Requerimos que no sea puntero a función.
			
			requires not std::is_function_v <TReturn>;
			
			// Necesitamos que sea default-constructible.
			
			requires std::is_default_constructible_v <TReturn>;
			
			// -----------------------------------------------------------------------------
			
		}
		TReturn Call (const std::string & functionName , TParams && ... params) const {
			
			// -----------------------------------------------------------------------------
			
			// Realizaremos la busqueda de nuestro proceso a invocar primero para poderlo llamar.
			
			if (auto currentFunction = GetFunction <TReturn (*) (TParams ...)> (functionName) ; currentFunction) {
				
				// Invocaremos la función y devolveremos el resultado.
				
				return currentFunction (std::forward <TParams> (params) ...);
				
				// -----------------------------------------------------------------------------
				
			}
			
			// Devolvemos el valor por default.
			
			return TReturn ();
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Una especialización del template para cuando es un puntero simple.
		
		template <typename TFunction , typename ... TParams>
		requires std::is_function_v <TFunction>
		ALWAYS_INLINE decltype (auto) Call (const std::string & functionName , TParams && ... params) const {
			
			// Devolveremos el valor de la llamada a nuestra función superior.
			
			return Call <std::invoke_result_t <TFunction , TParams ...> , TParams ...> (functionName , std::forward <TParams> (params) ...);
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Finalmente para poder liberar recuros con el destructor tendremos esto.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							DESTRUCTOR VIRTUAL
		// 							
		// -----------------------------------------------------------------------------
		
		// Tendremos el destructor para liberar la libreria.
		
		virtual ~Module () {
			
			// -----------------------------------------------------------------------------
			
			// Liberamos la libreria.
			
			UnloadLibrary ();
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	
};

// -----------------------------------------------------------------------------

// Finalizaremos el grupo de documentación del ModuleLoader.

// -----------------------------------------------------------------------------
/// @}
// -----------------------------------------------------------------------------

// Finalmente cerraremos el guard para el ionclude.

#endif // CYTTEK_MODULE_LOADER

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
