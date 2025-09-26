
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		GESTIONADOR DE CONFIGURACIONES
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

/// @defgroup Configuracion Configuration
/// @author José Raúl Moreno Acero
/// @date 10/05/2024
/// @brief Clase Singleton Parcial Gestionadora de todas las configuraciones creadas a partir de un nlohmann:json.
/// @details
/// Efectivamente la clase es un wrapper sobre un nlohmann::json sin embargo tiene como finalidad mantener un mismo archivo y sistema de configuracion recilado
/// para todos los objetos , clases y metodos que lo requieran , usando sintaxis fácil e intuitiva para axeder a la información y poder gestionar los valores
/// que están contenidos dentro de la confiuracion.

// Para poder realizar la carga de todas las configuraciones desde un archivo en formato json/xml tenemos el siguiente que es nuestro modulo para establecer
// dicha carga de configuraciones asi como la carga y guardado de archivos en cualquier lugar que se requiera.

#pragma once

// -----------------------------------------------------------------------------
/// 
/// @file configuration.hpp
/// 
/// @brief Archivo con la declaracion de la clase Singleton para la configuracion y la gestión de todas las configuraciones globales de otdo el programa.
/// 
/// @details
/// 
/// Se tiene la declaracion de la clase y todos los metoos que perternecen a la misma para la gestion de la concifugracion de nuestro programa.
/// 
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// @addtogroup Configuracion
/// @{
// -----------------------------------------------------------------------------

// Tendremos otro candado adicional.

#ifndef CYTTEK_CONFIGURATION
#define CYTTEK_CONFIGURATION

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Incluiremos las bases para nuestro cargador de configuraciones.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

// Incluiremos los streams para abrir archivos.

#include <iostream>
#include <fstream>
#include <sstream>

// Algunas exceptions.

#include <stdexcept>

// Incluiremos el sistema de archivos incorporado en c++ 17.

#include <filesystem>

// Incluiremos los concepts.

#include <concepts>

// Incluiremos las expresiones regulares.

#include <regex>

// Incluiremos los std::any.

#include <any>

// Incluiremos nuestros rangos de c++ 20.

#include <ranges>

// Como contenedores para utilizar tenemos el unordered_map y el vector de elementos.

#include <map>
#include <unordered_map>
#include <vector>

// Ahora el uso de la libreria de Core y Logs que tenemos para la dependencia actual.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							CORE CYTTEK , PRINTER LOGGER
// 							
// -----------------------------------------------------------------------------

// Ahora incluiremos el siguiente que es el pintador para los logs de la siguiente forma.

#include "core.hpp"

// Incluiremos las utilerias.

#include "utility.hpp"

// Incluiremos el logger para poder pintar logs internamente en otro canal en caso de estar habilitado.

#include "logger.hpp"

// Incluiremos extensiones adicionales de utilerias.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							JSON PARSER (NLOHMANN)
// 							
// -----------------------------------------------------------------------------

// Incluiremos el parser de jsons de nuestro compa nlohmann.

#include <nlohmann/json.hpp>

// Lo siguiente es la parte de la declaración de todos nuestro contenido para este header , utilizando los respectivos metodos.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		CLASE PROPERTIES
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Tendremos después una función estatica que nos permite parsear archivos de configuración y devolver directamente
// el objeto json de nlohmann respectivo con las flags que se le especifiquen.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							ENABLE CONFIG LOGGING
// 							
// -----------------------------------------------------------------------------

// Para poder establecer el autologging para las configuraciones tenemos lo siguiente que se encargará de realizar la asociación de nuestro INDEX a nuestro
// actual log de esta forma.

static constexpr size_t CYTTEK_LOGGER_IDX_CONFIG = 0x0000'00A0;

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							PARSE CONFIG JSON
// 							
// -----------------------------------------------------------------------------

// Tendremos un conjunto de FLAGS que van a ser de apoyo para poder contener todas las modificaciones y tratamientos
// especiales que se le pueden dar a los Datos en formato json antes de crear el Objeto json respectivo.

/// ----------------------------------------------------------------------------
/// @brief      Configuraciones permitidas por el Parser de Jsons.
/// 
/// @details
/// 
/// Esta enumeración contiene todas las flags permitidas para la función @ref ParseJSON , estas pueden modificar la cadena
/// de origen y determinar el modo de lectura de la misma ya sea mediante un archivo de texto plano (FILE_STREAM) o mediante
/// un std::string de manera directa.
// -----------------------------------------------------------------------------

enum ParseJSONFlags : uint8_t {
	
	// -----------------------------------------------------------------------------
	
	/// -------------------------------------------------------------------------
	/// @brief Esta flag indica que se realiza la lectura de un archivo de datos (Filename) con el json contenido.
	// --------------------------------------------------------------------------
	
	PARSE_FILE_STREAM = 			0b0000'0001 ,
	
	/// -------------------------------------------------------------------------
	/// @brief Esta flag indica que se realiza la lectura de una cadena (String)
	// --------------------------------------------------------------------------
	
	PARSE_STRING = 					0b0000'0010 ,
	
	/// ---------------------------------------------------------------------------
	/// @brief Esta flag indica que hay que eliminar todos los tipos de espacios que están fuera de los valores.
	// ----------------------------------------------------------------------------
	
	PARSE_REMOVE_SPACES = 			0b0000'0100 ,
	
	/// ---------------------------------------------------------------------------
	/// @brief Esta flag indica que se tiene que hacer una limpieza de todos los caracteres especiales que ocupen más de 1
	/// byte mediante el diccionario de caracteres especiales.
	// ----------------------------------------------------------------------------
	
	PARSE_FIX_ESPECIALS = 			0b0000'1000
	
	// -----------------------------------------------------------------------------
	
};

// Ahora tendremos nuestro diccionario de carácteres especiales los cuales ocupan más de 1 byte para poder realizar este
// tratamiento directamente cuando es requerido.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							DICCIONARIO ESPECIALES
// 							
// -----------------------------------------------------------------------------

// Declaramos nuestro pequeño diccionario para poder utilizar cuando sea requerido y se necesite tener bien úbicados los
// caracteres que deben modificarse.

template <typename TChar>
static inline const std::vector <std::pair <std::basic_string <TChar> , std::basic_string <TChar>>> DictionarySpecials = {

	// -----------------------------------------------------------------------------
	
	// Incluiremos los caracteres para la Ñ y ñ.
	
	std::make_pair ("ñ" , "n") ,
	std::make_pair ("Ñ" , "N") ,
	
	// Caso para los caracteres con acento.
	
	std::make_pair ("á" , "a") ,
	std::make_pair ("é" , "e") ,
	std::make_pair ("í" , "i") ,
	std::make_pair ("ó" , "o") ,
	std::make_pair ("ú" , "u") ,
	std::make_pair ("Á" , "A") ,
	std::make_pair ("É" , "E") ,
	std::make_pair ("Í" , "I") ,
	std::make_pair ("Ó" , "O") ,
	std::make_pair ("Ú" , "U") ,
	
	// Caso para las Dierecis.
	
	std::make_pair ("ä" , "a") ,
	std::make_pair ("ë" , "e") ,
	std::make_pair ("ï" , "i") ,
	std::make_pair ("ö" , "o") ,
	std::make_pair ("ü" , "u") ,
	std::make_pair ("Ä" , "A") ,
	std::make_pair ("Ë" , "E") ,
	std::make_pair ("Ï" , "I") ,
	std::make_pair ("Ö" , "O") ,
	std::make_pair ("Ü" , "U") 
	
	// -----------------------------------------------------------------------------
	
};

// Ahoar pasaremos al metodo para el parseo.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							PARSER TO JSON FROM STRING
// 							
// -----------------------------------------------------------------------------

// Tenemos un metodo estatico de utilidad que permite el parseo de un respectivo filename a un JSON respectivo mediante
// el uso del nlohmann::json parser. Devuelve el objeto json respectivo.

template <typename TChar = char>
static nlohmann::json ParseJSON (const std::basic_string <TChar> & Input , uint8_t Flags = (PARSE_STRING | PARSE_REMOVE_SPACES)) try {
	
	// Este metodo nos permite parsear archivos de configuración json a partir de filenames o directamente en el String a un objeto json
	// respectivo con todos los campos llenos.
	
	// -----------------------------------------------------------------------------
	
	// Establecemos el  tipo de string que estaremos manejando en este lugar.
	
	using TString = std::basic_string <TChar>;
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							READ JSON FILE/STRING
	// 							
	// -----------------------------------------------------------------------------
	
	// Tenemos nuestro objeto JSON resultante respectivo para poder devolver a la llamada de este metodo.
	
	nlohmann::json CurrentResult;
	
	// Ahora validaremos que el String que tenemos en la entrada no esté vacio.
	
	if (Input.empty ()) {
		
		// -----------------------------------------------------------------------------
		
		// Devolveremos un objeto nlohmann json vacio.
		
		return CurrentResult;
		
		// -----------------------------------------------------------------------------
		
	}
	
	// Ahora vamos con la carga del archivo o del string.
	
	// -----------------------------------------------------------------------------
	
	// Realizamos la lectura de nuestro archivo de texto en caso de tenerlo establecido , en caso de no tener la flag para el filestream
	// se estaría estableciendo el string directamente de la entrada.
	
	TString StringInput ((Flags & PARSE_FILE_STREAM) ? ReadFile (Input) : Input);
	
	// Ahora realizaremos un tratamiento para el string del json actual dependiendo nuestras flags.
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							REMOVE STRING SPACES
	// 							
	// -----------------------------------------------------------------------------
	
	// Si tenemos el flag para el reemplazamiento de nuestros espacios respectivos entonces tendremos que utilizar nuestro algoritmo
	// para el reemplazo de todos los espacios que están fuera de los valores del JSON.
	
	if (Flags & PARSE_REMOVE_SPACES) {
		
		// -----------------------------------------------------------------------------
		
		// Estableceremos primero un flagsito para determinar si actualmente se tiene un KEY/VALUE de la siguiente manera.
		
		bool IsKeyValue = false;
		
		// Ahora realizaremos el reemplazamiento de nuestro string mediante el uso de nuestro operador ReplacingIf y una función lambda que
		// tomará como argumento el flag que hemos creado y procederá con su reemplazo de la cadena.
		
		StringInput <ReplacingIf ([&] (auto Caracter) -> bool {
			
			// Eliminaremos todos los elementos que sean espacios utilizando la validación siguiente. Incorporamos el IsKeyValue para poder
			// establecer la condición a utilizar cuando se trata de un valor.
			
			return (!(IsKeyValue = ((Caracter == '"') ? !IsKeyValue : IsKeyValue)) && std::ranges::count (TString (" \n\r\t\f\v") , Caracter));
			
			// -----------------------------------------------------------------------------
			
		})>= '\0';
		
		// -----------------------------------------------------------------------------
		
	}
	
	// La siguiente configuración que tenemos es la que nos permite realizar el reemplazo de 
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							FIX ESPECIALS CHARS
	// 							
	// -----------------------------------------------------------------------------
	
	// Ahora vamos a validar si la flag está activada en estos momentos para poder continuar.
	
	if (Flags & PARSE_FIX_ESPECIALS) {
		
		// -----------------------------------------------------------------------------
		
		// Tenemos la referencia a nuestro diccionario que estaremos utilizando en este momento.
		
		static const auto & CurrentDictionary = DictionarySpecials <TChar>;
		
		// Realizaremos el reemplazamiento de todos los caracteres especiales en nuestro actual input utilizando el diccionario
		// respectivo y el operador para poder reemplazar multistrings.
		
		StringInput <Replacing (CurrentDictionary)>= CurrentDictionary;
		
		// -----------------------------------------------------------------------------
		
	}
	
	// Ahora vamos a realizar el parseo de nuestro respectivo json.
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 						PARSE/CREATE MAPPING JSON
	// 							
	// -----------------------------------------------------------------------------
	
	// Realizamos la validación siguiente para poder continuar.
	
	if (!StringInput.empty ()) {
		
		// Crearemos la instancia de nuestro objeto json de nlohmann después de aplicar el parseo sobre el mismo.
		
		CurrentResult = std::move (nlohmann::json::parse (StringInput));
		
		// -----------------------------------------------------------------------------
		
	}
	
	// Devolvemos ahora nuestro resultado actual.
	
	return CurrentResult;
	
	// -----------------------------------------------------------------------------
	
}
catch (const std::exception & Error) {
	
	// Algún tipo de error ocurrido. Relanzaremos nuestra excepción.
	
	throw;
		
	// -----------------------------------------------------------------------------
	
}

// -----------------------------------------------------------------------------
// 
// 							CONCEPT ConfigData
// 							
// -----------------------------------------------------------------------------

// Tendremos el siguiente que será un concepto que determina los valores permitidos para los parametros de plantilla Get en el Configuration Object.

template <typename TValue>
concept ConfigurationValue = ((
(
 
 	// La condición para los datos es que estos sean de algún tipo integral , punto flotante o algún tipo como por ejemplo string.
 
	std::is_integral_v 			<std::decay_t <TValue>> or
	std::is_floating_point_v 	<std::decay_t <TValue>> or
	std::is_convertible_v 		<std::decay_t <TValue> , std::string> or
	std::is_same_v 				<std::decay_t <TValue> , std::any>
	
	// -----------------------------------------------------------------------------
	
) or requires (const TValue & Value) {
	
	// La siguiente condición es para poder establecer el requerimiento de un tipo de dato (container-like) que nos permitá obtener valores por conjuntos
	
	{ Value.size () } -> std::convertible_to <size_t>;
	
	// De igual manera se requiere que sea un tipo de container válido.
	
	requires
		
		// Condiciones base para cualquier container-type.
		
		ContainerTraits::HasTypeMember 	<std::decay_t <TValue>> &&
		ContainerTraits::HasBeginEnd 	<std::decay_t <TValue>> &&
		ContainerTraits::HasTypeMember 	<std::decay_t <TValue>> && (
		
		// Condiciones para ser insertable.
		
		ContainerTraits::HasEmplace 	<std::decay_t <TValue>>	|| 	ContainerTraits::HasEmplacePosition <std::decay_t <TValue>> 	|| 
		ContainerTraits::HasEmplaceBack <std::decay_t <TValue>> ||
		ContainerTraits::HasInsert 		<std::decay_t <TValue>>	|| 	ContainerTraits::HasInsertPosition 	<std::decay_t <TValue>> 	||
		ContainerTraits::HasPush 		<std::decay_t <TValue>>	|| 	ContainerTraits::HasPushBack 		<std::decay_t <TValue>>
		
		);
		
	// -----------------------------------------------------------------------------
	
} or std::is_same_v <std::decay_t <TValue> , nlohmann::json>) and
	
	// Debe ser un valor construible por defecto para poder devolver un valor empty cuando no se encuentré en el mapa.

	std::is_default_constructible_v <std::decay_t <TValue>>
	
	// -----------------------------------------------------------------------------
	
);

// Ahora continuaremos con la declaración formal para la clase de la configuración.

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// 
// 							CONFIGURATION
// 							
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// Tendremos un loader singleton de Properties el cuál es el elemento generico que puede cargar todas las configuraciones al momento en el que
// asi se requiera y posteriormente de que las mapea en un hasher se pueden acceder a estas mediante su respectiva KEY.

class CYTTEK_API Configuration {
	
	// -----------------------------------------------------------------------------
	// 
	// 							Propiedades Privadas
	// 							
	// -----------------------------------------------------------------------------		
	
	// Tendremos todos los elementos privados de la siguiente forma.
	
	private :
		
		// Tendremos para empezar la declaración del modo Logging para este caso en nuestro respectivo Config.
		
		// -----------------------------------------------------------------------------
	
		// -----------------------------------------------------------------------------
		// 
		// 							CONFIGURATION LOG
		// 							
		// -----------------------------------------------------------------------------
		
		// Tendremos nuestro respectivo valor para poder establecer si está habilitado el log o no.
		
		bool LOGEnable = true;
		
		// Definiremos nuestro tipo de LOG interno para este config.
		
		using TCurrentLog = LOGGER <Configuration , CYTTEK_LOGGER_IDX_CONFIG>;
		
		// Utilizaremos el enum de los atributos.
		
		using enum LOGGER_ATTRIBUTE;
		
		// Ahora declaramos nuestro objeto para nuestro caso del Logger.
		
		TCurrentLog & LOG;
		
		// Internamente podrá accederse mediante el uso de la factoria de configuraciones que se provee posteriormente.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							FACTORY CONFIG
		// 							
		// -----------------------------------------------------------------------------
		
		// Para poder realizar la creación de más objetos de configuración en caso de ser necesario utilizaremos una factoria que realiza la creación
		// y construcción de los mismos de manera que puedan estos mismos ser utilizados para más ambitos internamente.
		
		friend class ConfigurationFactory;
		
		// Ahora tenemos los atributos personales de la clase de configuración que se tiene.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							MAPPING JSON
		// 							
		// -----------------------------------------------------------------------------
		
		// Comenzaremos por la declaración de nuestro json de Valores de configuración los cuales son todos los elementos que fueron
		// cargados durante la generación del Objeto de Configuración.
		
		mutable nlohmann::json CurrentMap;
		
		// -----------------------------------------------------------------------------
		// 
		// 							ELEMENTOS DESCARTADOS
		// 							
		// -----------------------------------------------------------------------------
		
		// Nuestro constructor por default se tiene igualado a una implementación por defecto para poder dejar la información vacia de momento.
		
		Configuration (bool CurrentLOGEnable = true) : LOG (TCurrentLog::GetInstance ()) , LOGEnable (CurrentLOGEnable) { /* Inicializado */ }
		
		// Inicializaremos la configuración con un constructor que recibe el json de mapa por r-value.
		
		template <typename TJSon>
		requires std::is_constructible_v <decltype (CurrentMap) , TJSon>
		Configuration (TJSon && CurrentNewMap , bool CurrentLOGEnable = true) : LOG (TCurrentLog::GetInstance ()) , LOGEnable (CurrentLOGEnable) {
			
			// -----------------------------------------------------------------------------
			
			// Inicializaremos nuestro respectivo JSON con el metodo respectivo.
			
			Init (std::forward <TJSon> (CurrentNewMap));
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Tampoco se tiene el constructor por copia y por movimiento.
		
		Configuration (const Configuration &) = delete;
		Configuration (Configuration &&) = delete;
		
		// Por otro lado el asignador con el operador '=' queda descartado.
		
		Configuration & operator = (const Configuration &) = delete;
		Configuration & operator = (Configuration &&) = delete;
		
		// Ahora vamos con el Inicializador para la clase.
		
		// -----------------------------------------------------------------------------
		// 
		// 							INICIALIZADOR DEL CONFIG
		// 							
		// -----------------------------------------------------------------------------
		
		// Tendremos el siguiente metodo privado que es nuestro inicializador del Objeto de Configuración con el parametro establecido
		// para el objeto JSON con las configuraciones.
		
		template <typename TJSon>
		requires std::is_constructible_v <decltype (CurrentMap) , TJSon>
		Configuration & Init (TJSon && CurrentConfigMap) {
			
			// Lo primero será la inicialización de nuestro respectivo LOG.
			
			// -----------------------------------------------------------------------------
			
			// -----------------------------------------------------------------------------
			// 
			// 							INIT LOGGER FOR CONFIG
			// 							
			// -----------------------------------------------------------------------------
			
			// Ahora para poder validar si tenemos la configuración establecida tenemos lo siguiente.
			
			if (LOGEnable) {
				
				// Estableceremos las flags para configuración del mismo.
				
				LOG.Init (std::string () , (ENABLE_CONSOLE | ENABLE_TRUNCATE | ENABLE_TIME | ENABLE_AUTONL | ENABLE_CLASS_ID | LEVEL_DEBUG));
				
				// -----------------------------------------------------------------------------
				
			}
			
			// -----------------------------------------------------------------------------
			
			// Realizaremos la asignación del json object a partir del archivo que se haya leido. y estableceremos el mapeo de toda
			// la información con la ayuda del JSON Parser de nlohnmann.
			
			CurrentMap = std::forward <TJSon> (CurrentConfigMap);
			
			// Validaremos nuestro mapa para poder determinar si fue correcto o incorrectamente cargado.
			
			if (!CurrentMap.empty () && !CurrentMap.is_null ()) {
				
				// -----------------------------------------------------------------------------
				
				// Cargado el mapa de datos entonces procederemos a presentar el siguiente mensaje de aviso.
				
				if (LOGEnable) LOG.PrintfInfo (" >>| Archivo de Configuracion Parseado Correctamente ");
				
				// -----------------------------------------------------------------------------
				
			}
			else {
				
				// Ha ocurrido algún error y no ha podido ser parseado el archivo json de configuración.
				
				if (LOGEnable) LOG.PrintfWarning (" >>| Archivo de Configuracion No se ha podido Cargar ");
				
				// -----------------------------------------------------------------------------
				
			}
			
			// -----------------------------------------------------------------------------
			
			// Devolveremos la referencia a nuestro mismo objeto de configuración ya inicializado.
			
			return *(this);
			
		}
		
		// -----------------------------------------------------------------------------
		
	// -----------------------------------------------------------------------------
	// 
	// 							Propiedades Publicas
	// 							
	// -----------------------------------------------------------------------------
	
	// Ahora continuaremos con las propiedades publicas para acceder a los elementos actuales en el archivo.
	
	public :
	
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							PUBLIC INSTANCE
		// 							
		// -----------------------------------------------------------------------------
		
		// Comenzaremos por el metodo que devolverá la instancia actual de nuestra configuración para el sistema o servicio actual.
		
		// -----------------------------------------------------------------------------
		
		// Crearemos primero el metodo general para poder crear la instancia y recuperar la referencia a la misma , este metodo conforma
		// parte escencial de nuestro escenario actual ya que permite acceder a las mismas configuraciones cargadas previamente.
		
		ALWAYS_INLINE static Configuration & GetInstance (bool EnableLogging = true) {
			
			// Crearemos nuestro elemento actual de configuración (UNICA INSTANCIA).
			
			static Configuration CurrentConfig (EnableLogging); // Inicializado de esta manera por defecto
			
			// -----------------------------------------------------------------------------
			
			// Finalmente devolvemos la referencia a este objeto inicializado por defecto con su constructor y las configuraciones default.
			
			return CurrentConfig;
			
		}
		
		// Ahora para poder inicializarlo con base en un nlohmann json de la siguiente manera.
		
		template <typename TJSon>
		requires std::is_constructible_v <decltype (CurrentMap) , TJSon>
		ALWAYS_INLINE static Configuration & GetInstance (TJSon && CurrentNewMap , bool EnableLogging = true) {
			
			// Devolveremos la Inicialización de nuestro respectivo Init de la siguiente forma.
			
			return GetInstance (EnableLogging).Init (std::forward <TJSon> (CurrentNewMap));
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Después tenemos el metodo GetInstance que lo único que estaría devolviendo sería la instancia de nuestro respectivo
		// objeto Configuratión con el patrón singleton y la configuración a cargar en el input config filename ó string.
		
		template <typename TChar = char>
		static Configuration & GetInstance (const std::basic_string <TChar> & InputConfig ,
		                                    uint8_t InputFlags = (PARSE_STRING | PARSE_REMOVE_SPACES) , bool EnableLogging = true) {
			
			// Determinamos el Config a utilizar en caso de que esté vacia la cadena de entrada.
			
			const std::basic_string <TChar> & CurrentConfigString = (InputConfig.empty () ? std::basic_string <TChar> () : InputConfig);
			
			// Determinaremos las flags para poder indicar como realizar la lectura del String de entrada.
			
			const uint8_t CurrentFlags = (InputConfig.empty () ? ((InputFlags & ~PARSE_FILE_STREAM) | PARSE_STRING) : InputFlags);
			
			// -----------------------------------------------------------------------------
			
			// Se inicializa por defecto con la configuración que se tenga establecida parseando la cadena de entrada según el caso.
			// y Finalmente devolvemos el valor actual.
			
			return GetInstance (EnableLogging).Init (std::move (ParseJSON (CurrentConfigString , CurrentFlags)));
			
		}
		
		// Tendremos otro metodo inline para obtener la configuración directamente mediante un file string.
		
		ALWAYS_INLINE static Configuration & GetInstanceFromFile (const char * const Filename , bool EnableLogging = true) {
			
			// -----------------------------------------------------------------------------
			
			// Devolvemos simplemente la carga de la intsancia con el filename indicado y las flags establecidas.
			
			return GetInstance (std::string (Filename) , (PARSE_FILE_STREAM | PARSE_REMOVE_SPACES) , EnableLogging);
			
		}
		
		// Por otro lado para poder cargar directamente desde una cadena común y corriente.
		
		ALWAYS_INLINE static Configuration & GetInstanceFromString (const char * const DataJSON , bool EnableLogging = true) {
			
			// -----------------------------------------------------------------------------
			
			// Devolvemos simplemente la carga de la intsancia con el filename indicado y las flags establecidas.
			
			return GetInstance (std::string (DataJSON) , (PARSE_STRING | PARSE_REMOVE_SPACES) , EnableLogging);
			
		}
		
		// Para validar las condiciones de nuestra configuration tenemos lo siguiente.
		
		// -----------------------------------------------------------------------------
		// 
		// 							CURRENT CONFIG STATUS
		// 							
		// -----------------------------------------------------------------------------
		
		// Ahora para comprobar nuestro estado actual de nuestra configuración tenemos la siguiente validación.
		
		ALWAYS_INLINE bool IsValid () const {
			
			// Validamos si el mapa interno de configuración ya ha sido cargado y no está vació de momento.
			
			return (!CurrentMap.empty () && !CurrentMap.is_null ());
			
		}
		
		// Ahora algunas funciones extras para el combinado directo desde otros elementos.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							CLONE AND ASSIGN
		// 							
		// -----------------------------------------------------------------------------
		
		// Tenemos un metodo para poder clonar una copia exacta de nuestro respectivo config de la siguiente forma.
		
		Configuration & Clone () const;
		
		// Ahora tendremos otro metodo para poder realizar la asignacion de valores desde un elemento.
		
		Configuration & Copy (const Configuration & copy);
		
		// Ahora para acceder a la información de nuestras configuraciones actuales tenemos el siguiente valor.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							ACCESORS DATA
		// 							
		// -----------------------------------------------------------------------------
		
		// Para poder consultar la existencia de algún dato en nuestro mapa tendremos la siguiente función que nos permite
		// validar si un dato se encuentra actualmente y adicional a esto validar si es convertible a un template especificado.
		
		template <ConfigurationValue TValue = std::string>
		bool Contains (const std::string & Key , const char KeySeparator = '.') const try {
			
			// Tenemos que buscar el tipo de valor contenido en el mapa de jsons mediante la clave , la cuál puede estar compuesta
			// de muchas maneras , por lo que accederemos a esto mediante el uso del separador especificado.
			
			const auto CurrentTags (Key <STokens <std::vector>> KeySeparator);
			
			// Tendremos el siguiente valor para contener la referencia json a la cuál vamos a apuntar.
			
			std::reference_wrapper <nlohmann::json> CurrentJSON = CurrentMap;
			
			// Pasaremos a iterar por todo el conjunto de tags para ir extrallendo el JSON actual mediante uso de los indices.
			
			if (!Key.empty ()) for (const auto & CurrentKey : CurrentTags) {
				
				// Delimitaremos a la posición del array y posteriormente convertiremos a entero para indexar el JSON.
				
				CurrentJSON = (std::ranges::count (CurrentKey , '[') ? 
					CurrentJSON.get () [StringToNumber <size_t> (CurrentKey <Trim> "[]")] :
					CurrentJSON.get () [CurrentKey]);
				
				// -----------------------------------------------------------------------------
				
				// Validaremos si existe el campo indicado para poder continuar. Terminaremos el ciclo actual en caso de no ser así.
				
				if (CurrentJSON.get ().empty () || CurrentJSON.get ().is_null ()) break;
				
				// -----------------------------------------------------------------------------
				
			}
			
			// Ahora pasaremos a la validación de nuestro objeto actual JSON para saber si no está vacio.
			
			if (!CurrentJSON.get ().empty () && !CurrentJSON.get ().is_null ()) {
				
				// -----------------------------------------------------------------------------
				
				// -----------------------------------------------------------------------------
				// 
				// 							VALIDANDO TYPE
				// 							
				// -----------------------------------------------------------------------------
				
				// Ahora solamente queda validar que el objeto actual cumpla con el tipo de dato de la conversión requerido.
				
				if constexpr (std::is_same_v <std::decay_t <TValue> , std::any>) {
					
					// Devolveremos true si no importa que valor sea.
					
					return true;
					
					// -----------------------------------------------------------------------------
					
				}
				else if constexpr (std::is_convertible_v <std::decay_t <TValue> , std::string>) {
					
					// Convertible a string. Devolvemos el resultado.
					
					return (CurrentJSON.get ().is_string ());
					
					// -----------------------------------------------------------------------------
					
				}
				else if constexpr (std::is_arithmetic_v <std::decay_t <TValue>>) {
					
					// Convertible a cualquier tipo de dato númerico.
					
					return (CurrentJSON.get ().is_primitive ());
					
					// -----------------------------------------------------------------------------
					
				}
				else if constexpr (std::is_same_v <std::decay_t <TValue> , nlohmann::json>) {
					
					// Convertible a un objeto de nlohmann::json.
					
					return (CurrentJSON.get ().is_object ());
					
					// -----------------------------------------------------------------------------
					
				}
				else {
					
					// De cualquier otra manera tendría que ser un array.
					
					return (CurrentJSON.get ().is_array ());
					
					// -----------------------------------------------------------------------------
					
				}
				
				// -----------------------------------------------------------------------------
				
			}
			
			// De cualquier otra manera devolveremos false.
			
			return false;
			
			// -----------------------------------------------------------------------------
			
		}
		catch (const std::exception & Error) {
			
			// Algún error ha ocurrido.
			
			if (LOGEnable) LOG.PrintfError (" >>| Error al Consultar Key : %s " , Error.what ());
			
			// Devolvemos false.
			
			return false;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Para recuperar cualquier dato de nuestro mapa tendremos el siguiente que será la plantilla de conversión actual de nuestro
		// respectivo mapa de datos a un valor en especifico mediante el uso del Key.
		
		template <ConfigurationValue TValue>
		auto Get (const std::string & Key , TValue && Default = TValue () , const char KeySeparator = '.') const try {
			
			// Tenemos que buscar el tipo de valor contenido en el mapa de jsons mediante la clave , la cuál puede estar compuesta
			// de muchas maneras , por lo que accederemos a esto mediante el uso del separador especificado.
			
			const auto CurrentTags (Key <STokens <std::vector>> KeySeparator);
			
			// Tendremos el siguiente valor para contener la referencia json a la cuál vamos a apuntar.
			
			std::reference_wrapper <nlohmann::json> CurrentJSON = CurrentMap;
			
			// Para validar si continuar o no.
			
			bool CurrentTagExists = true;
			
			// Pasaremos a iterar por todo el conjunto de tags para ir extrallendo el JSON actual mediante uso de los indices.
			
			if (!Key.empty ()) for (const auto & CurrentKey : CurrentTags) {
				
				// Validaremos si es un especificador de rangos [].
				
				const auto CurrentRangeExists = std::ranges::count (CurrentKey , '[');
				
				// Si no es un especificador de rango y el campo no existe entonces romperemos el ciclo.
				
				if (CurrentRangeExists == 0) if (!CurrentJSON.get ().contains (CurrentKey)) {
					
					// Asignaremos el valor en false.
					
					CurrentTagExists = false;
					
					// Romperemos el bucle.
					
					break;
					
					// -----------------------------------------------------------------------------
					
				}
				
				// Delimitaremos a la posición del array y posteriormente convertiremos a entero para indexar el JSON.
				
				CurrentJSON = (CurrentRangeExists ? 
					CurrentJSON.get () [StringToNumber <size_t> (CurrentKey <Trim> "[]")] :
					CurrentJSON.get () [CurrentKey]);
				
				// -----------------------------------------------------------------------------
				
				// Validaremos si existe el campo indicado para poder continuar. Terminaremos el ciclo actual en caso de no ser así.
				
				if (CurrentJSON.get ().empty () || CurrentJSON.get ().is_null ()) break;
				
				// -----------------------------------------------------------------------------
				
			}
			
			// Validaremos si el campo fue encontrado. Si no fue asi entones devolvemos el default.
			
			if (!CurrentTagExists) return Default;
			
			// Ahora pasaremos a la parte de la conversión.
			
			// -----------------------------------------------------------------------------
			
			// -----------------------------------------------------------------------------
			// 
			// 							CONVERSIÓN DE VALOR
			// 							
			// -----------------------------------------------------------------------------
			
			// Si tenemos la conversión a un tipo dinstinto a json entonces tomaremos simplemente el valor establecido.
			
			if constexpr (std::is_same_v <std::decay_t <TValue> , nlohmann::json>) {
				
				// Devolveremos la referencia dsel JSON respectivo actual.
				
				return CurrentJSON.get ();
				
				// -----------------------------------------------------------------------------
				
			}
			else {
				
				// Validaremos de la siguiente manera que no esté vacio y tampoco sea null.
				
				if (!CurrentJSON.get ().empty () && !CurrentJSON.get ().is_null ()) {
					
					// Intenraremos devolver la conversión respectiva del dato solicitado con el metodo get.
					
					// -----------------------------------------------------------------------------
					
					// Validaremos de manera constante el tipo de valor que se tiene y en este caso intentaremos convertir
					// a dicho tipo de dato.
					
					if constexpr (std::is_same_v <std::decay_t <TValue> , std::any>) {
						
						// Convertible a string. Devolvemos el resultado.
						
						if (CurrentJSON.get ().is_string ()) 				return std::any (CurrentJSON.get ().get <std::string> ());
						else if (CurrentJSON.get ().is_number_float ()) 	return std::any (CurrentJSON.get ().get <double> ());
						else if (CurrentJSON.get ().is_number ()) 			return std::any (CurrentJSON.get ().get <long int> ());
						else if (CurrentJSON.get ().is_boolean ()) 			return std::any (CurrentJSON.get ().get <bool> ());
						else if (CurrentJSON.get ().is_array ()) 			return std::any (CurrentJSON.get ().get <nlohmann::json> ());
						else if (CurrentJSON.get ().is_object ()) 			return std::any (CurrentJSON.get ().get <nlohmann::json> ());
						
						// -----------------------------------------------------------------------------
						
					}
					else if constexpr (std::is_convertible_v <std::decay_t <TValue> , std::string>) {
						
						// Convertible a string. Devolvemos el resultado.
						
						if (CurrentJSON.get ().is_string ()) 				return CurrentJSON.get ().get <TValue> ();
						else if (CurrentJSON.get ().is_number_float ()) 	return NumberToString (CurrentJSON.get ().get <double> () , 0 , 2);
						else if (CurrentJSON.get ().is_number ()) 			return NumberToString (CurrentJSON.get ().get <long int> () , 0 , 0 , false);
						else if (CurrentJSON.get ().is_boolean ()) 			return NumberToString (CurrentJSON.get ().get <bool> () , 0 , 0 , false);
						
						// -----------------------------------------------------------------------------
						
					}
					else if constexpr (std::is_arithmetic_v <std::decay_t <TValue>>) {
						
						// Convertible a cualquier tipo de dato númerico.
						
						if (CurrentJSON.get ().is_primitive ()) return CurrentJSON.get ().get <TValue> ();
						
						// -----------------------------------------------------------------------------
						
					}
					else if constexpr (std::is_same_v <std::decay_t <TValue> , nlohmann::json>) {
						
						// Convertible a un objeto de nlohmann::json.
						
						if (CurrentJSON.get ().is_object ()) return CurrentJSON.get ().get <TValue> ();
						
						// -----------------------------------------------------------------------------
						
					}
					else {
						
						// De cualquier otra manera tendría que ser un array.
						
						return CurrentJSON.get ().get <TValue> ();
						
						// -----------------------------------------------------------------------------
						
					}
					
					// -----------------------------------------------------------------------------
					
				}
				
				// -----------------------------------------------------------------------------
				
			}
			
			// -----------------------------------------------------------------------------
			
			// Finalmente devolveremos un valor por defecto en caso de no haber encontrado nada.
			
			return Default;
			
			// -----------------------------------------------------------------------------
			
		}
		catch (const std::exception & Error) {
			
			// Algún error ha ocurrido.
			
			if (LOGEnable) LOG.PrintfError (" >>| Error al Recuperar Valor : %s " , Error.what ());
			
			// Devolvemos el valor por defecto.
			
			return Default;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora tendremos su contraparte , el metodo Set el cuál establece la información actual para nuestro
		// campo que estemos especificando de la misma manera.
		
		template <ConfigurationValue TValue>
		void Set (const std::string & Key , TValue && Data , const char KeySeparator = '.' , bool MakeKeys = true) const try {
			
			// Primero tenemos que validar que el dato que estamos recibiendo tenga algo o de lo contrario tendremos que retornar
			// la llamada para poder continuar de la siguiente forma.
			
			if (Key.empty ()) {
				
				// Devolveremos la llamada.
				
				return;
				
				// -----------------------------------------------------------------------------
				
			}
			
			// Tenemos que buscar el tipo de valor contenido en el mapa de jsons mediante la clave , la cuál puede estar compuesta
			// de muchas maneras , por lo que accederemos a esto mediante el uso del separador especificado.
			
			const auto CurrentTags (Key <STokens <std::vector>> KeySeparator);
			
			// Tendremos el siguiente valor para contener la referencia json a la cuál vamos a apuntar.
			
			std::reference_wrapper <nlohmann::json> CurrentJSON = CurrentMap;
			
			// Pasaremos a iterar por todo el conjunto de tags para ir extrallendo el JSON actual mediante uso de los indices.
			
			for (const auto & CurrentKey : CurrentTags) {
				
				// Delimitaremos a la posición del array y posteriormente convertiremos a entero para indexar el JSON.
				
				CurrentJSON = (std::ranges::count (CurrentKey , '[') ? 
					CurrentJSON.get () [StringToNumber <size_t> (CurrentKey <Trim> "[]")] :
					CurrentJSON.get () [CurrentKey]);
				
				// -----------------------------------------------------------------------------
				
				// Validaremos si existe el campo indicado para poder continuar. Terminaremos el ciclo actual en caso de no ser así.
				
				if (!MakeKeys && (CurrentJSON.get ().empty () || CurrentJSON.get ().is_null ())) break;
				
				// -----------------------------------------------------------------------------
				
			}
			
			// Tenemos la parte de la conversión del dato a asignar en estos momentos para poder
			// cambiar la información.
			
			// -----------------------------------------------------------------------------
			
			// -----------------------------------------------------------------------------
			// 
			// 							CONVERSIÓN DE VALOR
			// 							
			// -----------------------------------------------------------------------------
				
			// Asignaremos el siguiente valor (utilizando perfect-forwarding).
			
			CurrentJSON.get () = std::forward <TValue> (Data);
			
			// -----------------------------------------------------------------------------
			
		}
		catch (const std::exception & Error) {
			
			// Algún error ha ocurrido.
			
			if (LOGEnable) LOG.PrintfError (" >>| Error al Establecer Valor : %s " , Error.what ());
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora definiremos los operadores de acceso directamente para poder operar sobre el mismo.
		
		// -----------------------------------------------------------------------------
		// -----------------------------------------------------------------------------
		// 
		// 							OPERADTORS INDEX
		// 							
		// -----------------------------------------------------------------------------
		// -----------------------------------------------------------------------------
		
		// Tenemos el operador para los indices mediante las cadenas que indican a que propiedad del JSON referirse.
		
		// -----------------------------------------------------------------------------
		
		// Implementamos el operador de sub-indices de la siguiente manera.
		
		template <ConfigurationValue TValue>
		ALWAYS_INLINE decltype (auto) operator [] (const std::string & Key) const {
			
			// Devolvemos el wrapper sobre el metodo Get respectivo con los otros dos parametros predeterminados.
			
			return Get <TValue> (Key);
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para poder acceder directamente al json interno que se tiene.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							JSON GET INTERNAL MAP
		// 							
		// -----------------------------------------------------------------------------
		
		// Con este llamado podremos obtener acceso directo a nuestro nlohmann json interno.
		
		ALWAYS_INLINE std::add_lvalue_reference_t <std::decay_t <decltype (CurrentMap)>> GetInternalMap () const {
			
			// Devolveremos el mapa interno.
			
			return CurrentMap;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
		
};

// Tendremos algunas funciones auxiliares que nos permitan realizar reemplazo de variables de entorno locales o globales en nuestra configuracion mediante
// el uso de una sintaxis especifica.

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// 
// 							CONFIGURATION REPLACING
// 							
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// Para conformar esto necesitaremos definir lo que serán las expresiones regulares para dicho contenido de las variables y poder obtener el valor que nos
// importa y saber cual aplicar para variable local al config y cual para variable de entorno.

// -----------------------------------------------------------------------------

// Crearemos nuestra clase estatica para realizar esto con cualquier confifuracion que se desee establecer de la siguiente manera.

class CYTTEK_API ConfigurationEnv final {
	
	// Tendremos algunos elementos privados para poder usar como metodos auxiliares
	
	// -----------------------------------------------------------------------------
	// 
	// 							METODOS AUXILIARES
	// 							
	// -----------------------------------------------------------------------------
	
	// Declaramos lo siguiente.
	
	private :
	
		// Tendremos algunos metodos auxiliares para nuestra clase estatica.
		
		// -----------------------------------------------------------------------------
		
		// Realizaremos la declaracion de nuestro respectivo metodo para poder reemplazar una variable local con base en alguna expresion regular que tengamos.
		
		static std::string EnvLocal (const Configuration & config , const std::string & input);
		
		// El siguiente es para el caso de una variable global.
		
		static std::string EnvGlobal (const std::string & input);
		
		// Tendremos los constructores y asignadores desabilitados.
		
		// -----------------------------------------------------------------------------
		// 
		// 							CONSTRUCTORES
		// 							
		// -----------------------------------------------------------------------------
		
		// El constructor por default estará desabilitado
		
		ConfigurationEnv () = delete;
		
		// El constructor para la copia y el r-value de la misma forma.
		
		ConfigurationEnv (const ConfigurationEnv & copy) = delete;
		ConfigurationEnv (ConfigurationEnv && move) = delete;
		
		// De igual forma para los operadores de copia y de r-value.
		
		ConfigurationEnv & operator = (const ConfigurationEnv & copy) = delete;
		ConfigurationEnv & operator = (ConfigurationEnv && move) = delete;
		
		// -----------------------------------------------------------------------------
	
	// Ahora para los elementos publicos tenemos este.
	
	// -----------------------------------------------------------------------------
	// 
	// 							METODOS PUBLICOS
	// 							
	// -----------------------------------------------------------------------------
	
	// Declaramos lo siguiente.
	
	public :
		
		// Primero que nada tendremos que declarar las constantes para poder manejar por defecto.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							CONFIGURATION REPLACING
		// 							
		// -----------------------------------------------------------------------------
		
		// Tenemos la variable constante para la expresion regular que valida el respectivo formato de reemplazo de variable local.
		
		static constexpr const char * ENV_LOCAL_REGEX = 	R"(\$\{([[:alnum:]_.-]+)\})";
		
		// Ahora lo mismo pero para el caso de las variables globales.
		
		static constexpr const char * ENV_GLOBAL_REGEX = 	R"(\$\(([[:alnum:]_.-]+)\))";
		
		// Ahora vamos a declarar nuestra funcion que nos permite realizar la sustitucion de nuestra configuracion y poder realizar con esto la 
		// sustitucion adecuada de los parametros que necesitemos.
		
		static std::string Replacing (const std::string & currentInput , const Configuration & currentConfig ,
			const char * const envLocalRegex = ENV_LOCAL_REGEX ,
			const char * const envGlobalRegex = ENV_GLOBAL_REGEX);
		
		// -----------------------------------------------------------------------------
	
};

// Implementaremos funcion global para poder realizar la sustitucion o reemplazo de un campo especifico para un determinado archivo de confituracion
// con los valores especificados.

CYTTEK_API std::string ConfigurationVariable (const Configuration & currentConfig , const char * const currentKey , bool replacing = true);

// Implementaremos operadores auxiliares para los recortes de cadenas

// -----------------------------------------------------------------------------
// 
// 							OPERADORES RVar y LVar
// 							
// -----------------------------------------------------------------------------

// Estableceremos un espacio en linea para guardar los operadores especificos de este modulo de configuracion

inline namespace UtilityOperators {
	
	/// 
	/// @addtogroup UtilOperators
	/// @{
	/// 
	
	// Utilizaremos los placeholders.
	
	using namespace std::placeholders;
	
	// Definiremos nuestro operaddor RVAR que realiza la sustitucion o modificacion de variables en un campo determinado de un archivo de configuracion.
	
	constexpr inline auto RVar = MakeNamedOperator (std::bind (ConfigurationVariable , _1 , _2 , true));
	
	// Definiremos nuestro operaddor LVar para poder realizar el reemplazo de nuestro respectivo campo pero sin reemplazar.
	
	constexpr inline auto LVar = MakeNamedOperator (std::bind (ConfigurationVariable , _1 , _2 , false));
	
	// -----------------------------------------------------------------------------
	
}

// Ahora pasaremos a lo siguiente que es la clase de la factoria de configuraciones para poder crear mas configs sin importar que exista uno general de singleton.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		FACTORIA DE CONFIGURACIONES
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Tenemos una pequeña clase para contener elementos estaticos que pertitan gestionar y crear nuestros objetos de tipo Configuracion sin importar que este mismo
// sea un singleton , de varias formas. Por lo tanto tenemos lo siguiente.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							CLASE CONFIG FACTORY
// 							
// -----------------------------------------------------------------------------

// Definiremos nuestra clase para la factoria de nuestras configuraciones de la siguiente forma.

class CYTTEK_API ConfigurationFactory final {
	
	// Primero tenemos los elementos privados para poder gestionar toda la parte de nuestros vectores para las referencias que tenemos.
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							PRIVATES ATTRIBUTES
	// 							
	// -----------------------------------------------------------------------------
	
	// Tenemos en primer lugar nuestros siguientes elementos.
	
	private :
	
		// Conformaremos los datos privados que nuestra factorai contendra para tener un registro de los elementos de configuracion que se van creando.
		
		// -----------------------------------------------------------------------------
		// 
		// 							LISTA DE CONFITURACIONES
		// 							
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		
		// Definiremos un limitador para establecer el alcance máximo de valores que podemos tener de configuraciones para despues ser relocated.
		
		static constexpr size_t CONFIG_LIMIT = 100u;
		
		// Tenemos primero nuestro vector de referencias para nuestras configuraciones que van siendo creadas.
		
		static std::vector <std::shared_ptr <Configuration>> configList;
		
		// Constructor privado para inicializar los elementos estaticos.
		
		// -----------------------------------------------------------------------------
		// 
		// 							PRIVATE CONSTRUCTOR
		// 							
		// -----------------------------------------------------------------------------
		
		// Este constructor que definiremos servirá para poder realizar configuraciones de forma estatica.
		
		ConfigurationFactory (); // Config Constructor para elementos estaticos.
		
		// Definiremos el constructor de copia y move invalidos.
		
		ConfigurationFactory (const ConfigurationFactory & copy) = delete;
		ConfigurationFactory (ConfigurationFactory && move) = delete;
		
		// Definiremos el asinador de copia y rvalue invalidos también.
		
		ConfigurationFactory & operator = (const ConfigurationFactory & copy) = delete;
		ConfigurationFactory & operator = (ConfigurationFactory && move) = delete;
		
		// -----------------------------------------------------------------------------
	
	// Tenemos los elementos publicos para nuestra factoria que se encargan de gestionar toda la parte que necesitamos para crear mas configuraciones.
	
	// -----------------------------------------------------------------------------
	// 
	// 							PUBLIC METHODS FOR CREATION
	// 							
	// -----------------------------------------------------------------------------
	
	// Tenemos todos los metodos siguientes para la creacion y la gestion de nuestros elementos de configuracion que tenemos de la siguiente forma.
	
	public :
	
		// Tenemos nuestros siguientes datos para poder conmformar la informacion.
		
		// -----------------------------------------------------------------------------
		// 
		// 							CREATE CONFIGURATIONS
		// 							
		// -----------------------------------------------------------------------------
	
		// -----------------------------------------------------------------------------
		
		// Tneemos primero lo siguiente para poder crear nuestra nueva configuracion de manera vacia sin ningún elemento.
		
		static Configuration & Build ();
		
		// Tenemos la sobrecarga para poder construir con un respectivo objeto nlohmann y poder inicializar todos los valores respectivos.
		
		static Configuration & Build (const nlohmann::json & currentMap);
		
		// Ahora el siguiente metodo permite establecer la información inicial de la configuracion desde un archivo json de texto plano que podamos leer.
		
		static Configuration & BuildFromString (const std::string & currentInput);
		
		// Ahora lo siguiente será crear nuestro metodo para poder crear la confiuracion a partir de un filename en formato json.
		
		static Configuration & BuildFromFile (const std::string & filename); 
		
		// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	
};

// -----------------------------------------------------------------------------

// Finalizaremos la parte de nuestro grupo.

// -----------------------------------------------------------------------------
/// @}
// -----------------------------------------------------------------------------

#endif // CYTTEK_CONFIGURATION

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
