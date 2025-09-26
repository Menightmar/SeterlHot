
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		LOGGER MANAGER
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

/// @defgroup Logger Logger
/// @author José Raúl
/// @date 07/05/2024
/// @brief LOGGER para la escritura de archivos con logs que detallan el proceso y pueden ser de utilidad para fines de debbugeo , encontrar errores y validar
/// los tiempos de respuesta de diferentes partes de los agentes.

#pragma once

// -----------------------------------------------------------------------------
/// 
/// @file logger.hpp
/// 
/// @brief Archivo con la declaracion de la clase LOGGER que comparten la mayoria de los modulos con un sistema de rotacion de archivos , impresion de
/// variables con formato , timestamps , chekadores de errores , niveles de debbugueo , etc.
/// 
/// @details
/// 
/// Este archivo de cabecera es util para los modulos que utilizan el sistema de LOGGER de cyttek para poder mostrar la información que se consideré pertinente
/// a lo largo de todo el programa.
/// 
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// @addtogroup Logger
/// @{
// -----------------------------------------------------------------------------

// Tenemos el siguiente Header Guard.

#ifndef CYTTEK_LOGGER
#define CYTTEK_LOGGER

// Incluiremos todas las bases para poder trabajar sobre esto.

#include <stdio.h>
#include <stdlib.h>

// Incluiremos los strings de la siguiente forma.

#include <string.h>
#include <string>
#include <sstream>

// Incluiremos algunas dependencias adicionales de utilerias.

#include <utility>
#include <fstream>
#include <iostream>
#include <type_traits>

// Incluiremos lo que sería el chekador de tiempos de chrono.

#include <chrono>

// Necesitaremos los hilos de ejecucion.

#include <thread>
#include <mutex>

// Mapa hash para mapeo de elementos.

#include <unordered_map>

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							UTILERIAS BASE CYTTEK
// 							
// -----------------------------------------------------------------------------

// Incluiremos las utilerias base de este proyecto por si todavia no están incluidas.

#include "utility.hpp"

// Ahora pasaremos a lo siguiente.

// -----------------------------------------------------------------------------
// 
// 								LOGGER FORMAT
// 							
// -----------------------------------------------------------------------------

// Usaremos el siguiente formato para nuestros datos.

/*
 *
[DateTime]           || 2024-06-12 13:46:25.698
[Log][Debug]         || Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit...
--------------------

[DateTime]           || 2024-06-12 13:46:25.700
[Log][Info]          || Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit...
[Parameters]         || System.String (cadena)
--------------------

[DateTime]           || 2024-06-12 13:46:25.701
[Log][Info]          || Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit...
[Parameters]         || System.Int32 (1)
--------------------

[DateTime]           || 2024-06-12 13:46:25.701
[Log][Info]          || Neque porro quisquam est qui dolorem ipsu…

*/

// Para poder customizar un poco nuestros logs tenemos una serie de campos que podemos modificar como el numero de saltos de linea
// el separador , si pintar el ClassID , etc. Para esto tendremos una enumeracion para dichos campos.

// -----------------------------------------------------------------------------
// 
// 							LOGGER FLAGS CONFIG
// 							
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
		
// Tenemos una serie de flags que determinan comportamiento de nuestro respectivo LOGGER de la siguiente manera.

// -----------------------------------------------------------------------------

/**
 * @brief Flags para setear configuraciones a nuestro LOGGER.
 * 
 */

enum LOGGER_ATTRIBUTE : long int {
	
	// -----------------------------------------------------------------------------
	
	// Tenemos las siguientes banderas.
	
	// -----------------------------------------------------------------------------
	
	/// @brief Bandera que permite habilitar la impresión del LOG mediante la salida estandar por Consola.
	
	ENABLE_CONSOLE = 		0b0000'0000'0000'0001 ,
	
	/// @brief Bandera que habilita la impresión del log en un archivo (determinado al momento de inicializar)
	
	ENABLE_FILE = 			0b0000'0000'0000'0010 ,
	
	/// @brief Bandera que permite anexar el timestamp al inicio del LOG para saber en que tiempo se mostró.
				
	ENABLE_TIME = 			0b0000'0000'0000'0100 ,
	
	/// @brief Bandera que permite anexar un salto de linea y un separador entre log y log que se estén presentando.
	
	ENABLE_AUTONL =			0b0000'0000'0000'1000 ,
	
	/// @brief Permite limpiar el archivo de log que se quiera utilizar antes de escribir en él.
	
	ENABLE_TRUNCATE =		0b0000'0000'0001'0000 ,
	
	/// @brief Permite añadir la clase asociada a este log de la siguiente forma.
	
	ENABLE_CLASS_ID =		0b0000'0000'0010'0000 ,
	
	/// @brief Permite definir el separador a utilizar.
	
	ENABLE_SEPARATOR =		0b0000'0000'0100'0000 ,
	
	/// @brief Permite habilitar un writter personalizado para escribir el log.
	
	ENABLE_WRITTER =		0b0000'0000'1000'0000 ,
	
	/// @brief Establece el nivel de log en DEBUG.
	
	LEVEL_DEBUG = 			0b0000'0001'0000'0000 ,
	
	/// @brief Establece el nivel de log en WARNING.
	
	LEVEL_WARNING = 		0b0000'0010'0000'0000 ,
	
	/// @brief Establece el nivel de log en ERROR.
	
	LEVEL_ERROR = 			0b0000'0100'0000'0000 ,
	
	/// @brief Establece el nivel de log en CRITICAL.
	
	LEVEL_CRITICAL = 		0b0000'1000'0000'0000 ,
	
	/// @brief Establece el nivel de log en INFO.
	
	LEVEL_INFO = 			0b0001'0000'0000'0000
	
	// -----------------------------------------------------------------------------	
	
};

// Validar nivel de log mediante la siguiente constante de bits.

static constexpr long int LOGGER_ENABLE_LEVEL = (LEVEL_DEBUG | LEVEL_WARNING | LEVEL_ERROR | LEVEL_CRITICAL | LEVEL_INFO);

// Ahora para poder manejar diferentes logs apuntando a un mismo archivo con un mecanismo de semaforo mediante mutex tenemos lo siguiente.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							MUTEX FOR LOGGER CLASS
// 							
// -----------------------------------------------------------------------------

// Tendremos lo siguiente que se encarga de realizar la construccion de los elementos para el control de los diferentes logs de la siguiente manera.

// -----------------------------------------------------------------------------

// Ahora para poder bloquear la escritura del archivo desde diferentes lugares tendremos un mapa asociado a diferentes archivos de texto en general

extern CYTTEK_API std::unordered_map <std::string , std::mutex> cyttekLoggerMutex;

// De igual forma para poder gestionar los streams tenemos un ofstream respectivo para la escritura de los archivos reutilizando uno solamente.

extern CYTTEK_API std::unordered_map <std::string , std::ofstream> cyttekLoggerStreams;

// Ahora para poder apuntar a un mismo mutex para diferentes threads tendremos lo siguiente.

extern CYTTEK_API std::timed_mutex cyttekLoggerMapMutex;

// Ahora definiremos una funcion para poder recuperar el logger respectivo para el determinado filename que tenemos.

std::mutex & CYTTEK_API CyttekLoggerGetMutex (const std::string & currentFilename);

// Ahora pasaremos con la clase logger de la siguiente forma.

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// 
// 							LOGGER PRINTER.
// 							
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

/// @author JRMA
/// @brief Clase especializada en la generación de archivo LOG asi como la presentación con formato especifico de información general
/// en la consola para poder organizar el tiempo y observar con detalle las partes de cada proceso que van ayudando a saber en qué parte
/// pueden haber problemas.
/// @tparam INDEX Identificador de canal para este Logger en caso de querer tener más de uno asociados a diferentes archivos por ejemplo.

template <typename TClass = void , size_t Index = 0u>
class LOGGER {
	
	// Primero tenemos el indice y la clase como un alias para este logger en especifico.
	
	// -----------------------------------------------------------------------------
	// 
	// 							ATRIBUTOS PUBLICOS
	// 							
	// -----------------------------------------------------------------------------
	
	// Tenemos lo siguiente para este elemento.
	
	public :
	
		// -----------------------------------------------------------------------------
		
		// Primero tenemos que declarar lo que será nuestro alias de tipo.
		
		using classType = TClass;
		
		// Utilizaremos nuestro enum para las configuraciones.
		
		using enum LOGGER_ATTRIBUTE;
		
		// Ahora pasaremos a establecer el indice asociado a este logger.
		
		static constexpr size_t index = Index;
		
		// -----------------------------------------------------------------------------
	
	// Tenemos los siguientes elementos que conforman parte de nuestro LOGGER para poder comenzar.
	
	// -----------------------------------------------------------------------------
	// 
	// 							ATRIBUTOS PRIVADOS
	// 							
	// -----------------------------------------------------------------------------
	
	// La información privada de esta clase.
	
	private :
		
		// Tenemos lo siguiente que es la parte del archivo donde se está escribiendo actualmente para este LOG. Elemento que puede ser establecido
		// de manera dinámica.
		
		std::string currentFilename;
		
		// Para validar si está abierto el stream para el archivo.
		
		bool streamInitialized = false;
		
		// Tenemos varios tipos de banderas para poder configurar algun comportamiento de nuestro objeto.
		
		long int currentFlags = 0;
		
		// Cantidad de espacio entre log y log para el caso de tener establecido el AUTONL en true.
		
		size_t currentLineSpace = 0u;
		
		// Para poder tener dinamismo y permitir personalizar la forma en la que se pinta la salida tenemos un objeto funcional que permite guardar
		// una funcion que recibiendo un string permite escribirlo en donde se necesite.
		
		std::function <void (const std::string &)> currentWritter;
		
		// -----------------------------------------------------------------------------
		
		// Ahora definiremos lo que es el metodo Write con el actual texto que será anexado a nuestro respectiva consola o simplemente archivo.
		
		template <typename ... TExtensions>
		void Write (const std::string & currentText , TExtensions && ... currentExtensions) {
			
			// Crearemos un lockguard para el determinado filename que tenemos actualmente abierto.
			
			std::unique_lock <std::mutex> currentLock (CyttekLoggerGetMutex (currentFilename));
			
			// Validaremos si el ofstream o la consola está actualmente abierto.
			
			if (!currentText.empty () && (currentFlags & (ENABLE_CONSOLE | ENABLE_FILE))) try {
			
				// Texto de salida.
				
				std::stringstream currentOutput;
				
				// Tendremos nuestro buffer temporal de 20 posiciones maximo para el encabezado.
				
				static constexpr size_t LOG_HEADER_SIZE = 20u;
				
				// Tendremos el formato estatico.
				
				static const std::string headerFormat (std::string (R"(%-)") + StringPrintf ("%i" , LOG_HEADER_SIZE) + "s");
				
				// Iniciaremos el buffer.
				
				static char headerBuffer [LOG_HEADER_SIZE + 1u] = { '\0' };
				
				// Definiremos nuestro respectiva funcion para poder escribir nuestro respectivo log.
				
				auto headerPrintf = [&] (const std::string & value) -> void {
					
					// Limpiaremos todo el buffer de la siguiente forma.
					
					memset (headerBuffer , '\0' , (LOG_HEADER_SIZE + 1u));
					
					// Ahora pintaremos el dato en nuestro buffer.
					
					snprintf (headerBuffer , LOG_HEADER_SIZE , headerFormat.c_str () , value.c_str ());
					
					// Pintaremos en nuestro output y lo devolveremos.
					
					currentOutput << std::string (headerBuffer) << "|| ";
					
					// -----------------------------------------------------------------------------
					
				};
				
				// Antes de continuar validaremos las banderas que tenemos establecidas para este logger , de la siguiente manera tendremos que.
				
				// -----------------------------------------------------------------------------
				
				// Validaremos si está habilitado la impresión del timestamp actual , para esto tenemos el operador a nivel de bit.
				
				if (currentFlags & ENABLE_TIME) {
					
					// -----------------------------------------------------------------------------
					
					// Realizaremos lo que es la obtención de nuestro tiempo actual local al sistema.
					
					const auto currentTimestamp = std::chrono::system_clock::now ();
					
					// Pintaremos nuestro header respectivo.
					
					headerPrintf ("[DateTime]");
					
					// Ahora vamos a darle un formato más adecuado para poderlo entender.
					
					currentOutput << FormatDateAPI ("%d-%m-%Y %H:%M:%S.");
					
					// Anexaremos lo quie son los segundos en este timestamp actual.
					
					currentOutput << (std::chrono::duration_cast <std::chrono::milliseconds> (currentTimestamp.time_since_epoch ()).count () % 1000);
					
					// Ahora simplemente anexaremos un salto de linea automático.
					
					currentOutput << "\n";
					
					// -----------------------------------------------------------------------------
					
				}
				
				// -----------------------------------------------------------------------------
				
				// Ahora sabremos si pintar el ClassID para el tipo de dato asociado.
				
				if ((currentFlags & ENABLE_CLASS_ID) && (not std::is_void_v <classType>)) {
					
					// Pintaremos nuestro header respectivo para la class.
					
					headerPrintf ("[ClassID]");
					
					// Anexaremos el class id de esta manera para poder saber que clase invoca.
					
					currentOutput << TypeString <classType>::c_str () << "\n";
					
					// -----------------------------------------------------------------------------
					
				}
				
				// Habilitamos la bandera si es debug , warning o error.

				if (!currentText.empty () && (currentFlags & LOGGER_ENABLE_LEVEL)) {
					
					// Anexaremos un texto con la leyenda del nivel del que estamos mandando a imprimir , esto para poder diferenciarlos.
					
					headerPrintf (std::string ("[Log][") + GetLevelString (currentFlags & LOGGER_ENABLE_LEVEL) + "]");
					
					// Ahora simplemente escribiremos esto en el buffer de salida para poder pintar en el stream que tenemos abierto.
					
					currentOutput << currentText << "\n";
					
					// -----------------------------------------------------------------------------
					
				}
				
				// Ahora tenemos lo siguiente para saber si hay extensiones para algun tipo de valor.
				
				// -----------------------------------------------------------------------------
				
				// -----------------------------------------------------------------------------
				// 
				// 							EXTENSIONS FOR LOGGER
				// 							
				// -----------------------------------------------------------------------------
				
				// Si tenemos alguna extensión entonces tambien los pintaremos de acuerdo al tipo de valor que sean.
				
				// -----------------------------------------------------------------------------
				
				// Crearemos una funcion para saber que tipo de valor se trata y poderlo parsear.
				
				auto extensionPrintf = [&] <typename TParam> (const TParam & value) -> void {
					
					// Ahora tendremos que validar nuestro tipo de dato respectivo para saber el tratamiento que le vamos a dar.
					
					// -----------------------------------------------------------------------------
					
					// Validaremos que tipo de valor tenemos y verificamos que hacer.
					
					if constexpr (std::is_base_of_v <std::exception , std::decay_t <TParam>>) {
						
						// Pintaremos el siguiente header respectivo.
						
						headerPrintf ("[Ex]");
						
						// Pintaremos nuestro respectivo what para el error actual.
						
						currentOutput << TypeString <TParam>::c_str () << " (" << std::string (value.what ()) << ")";
						
						// -----------------------------------------------------------------------------
						
					}
					else if constexpr (requires (TParam value) {
						
						// Requerimos que tenga un Alias de Tipo.
						
						{ typeid (TParam) };
						
						// Requerimos que nuestro value sea pintable mediante ofstream.
						
						{ std::declval <decltype (currentOutput)> () << value };
						
						// -----------------------------------------------------------------------------
						
					}) {
						
						// Pintaremos nuestro siguiente header.
						
						headerPrintf ("[Parameters]");
						
						// Pintaremos el parametro en especifico con el tipo de dato que corresponda y su valor respectivo.
						
						currentOutput << TypeString <TParam>::c_str () << " (" << value << ")";
						
						// -----------------------------------------------------------------------------
						
					}
					
					// Pintaremos nuestro respectivo separador.
					
					currentOutput << "\n";
					
					// -----------------------------------------------------------------------------
					
				};
				
				// Validaremos si tenemos extensiones de la siguiente forma.
				
				if constexpr (sizeof ... (currentExtensions)) {
					
					// Realizaremos la aplicacion de las extensiones de la siguiente forma.
					
					(extensionPrintf (std::forward <TExtensions> (currentExtensions)) , ...);
					
					// -----------------------------------------------------------------------------
					
				}
				
				// Ahora para decorar un separador establecido.
				
				// -----------------------------------------------------------------------------
				
				// Validaremos si hay que pintar un separador por default desabilitado.
				
				if (currentFlags & ENABLE_SEPARATOR) {
					
					// Tenemos lo siguiente que es para poder pintar el separador.
					
					currentOutput << "------------------------------ \n";
					
					// -----------------------------------------------------------------------------
					
				}
				
				// -----------------------------------------------------------------------------
				
				// Ahora validaremos que la bandera de auto-salto de linea está habilitada para poder entonces anexar un espaciador separador.
				
				if (currentFlags & ENABLE_AUTONL) {
					
					// -----------------------------------------------------------------------------
					
					// Ahora para poder dar un salto de linea tenemos lo siguiente.
					
					for (int i = 0 ; i < currentLineSpace ; ++ i) currentOutput << '\n';
					
					// -----------------------------------------------------------------------------
					
				}
				
				// -----------------------------------------------------------------------------
				
				// Ahora obtenemos el string de salida que vamos a escribir en el archivo resultante.
				
				auto currentStringOutput = currentOutput.str ();
				
				// -----------------------------------------------------------------------------
				
				// Ahora tenemos lo siguiente que son las flags para validar si estaremos imprimiendo en la consola y/o en el archivo.
				
				if (currentFlags & ENABLE_CONSOLE) puts (currentStringOutput.c_str ());
				
				// Validaremos si tenemos el modo para habilitar el writter de la siguiente forma.
				
				if ((currentFlags & ENABLE_WRITTER) && currentWritter) currentWritter (currentStringOutput);
				
				// Validarmeos lo siguiente para poder validar los loggers de streams.
				
				if (streamInitialized && (currentFlags & ENABLE_FILE) && cyttekLoggerStreams.count (currentFilename)) {
					
					// Ahora pasaremos a imprimir en el archivo me diante el stream si es que está abierto.
					
					if (auto & currentStream = cyttekLoggerStreams [currentFilename] ; currentStream.is_open ()) {
						
						// Escribiremos el output actual.
						
						currentStream << currentStringOutput << std::endl;
						
						// Liberamos el buffer para pintar en el archivo.
						
						currentStream.flush ();
						
						// -----------------------------------------------------------------------------
						
					}
					
					// -----------------------------------------------------------------------------
					
				}
				
				// -----------------------------------------------------------------------------
				
			}
			catch (const std::exception & error) { /* Error */ }
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
		
		// Ahora vamos a implementar lo siguiente que es un metodo que devuelve el nivel de log en formato de cadena para poder representar.
		
		std::string GetLevelString (long int currentLevel) const {
			
			// Tenemos un mapa estatico que lo que hace es mapear lo que es el indice de cada nivel a un determinado string de la siguiente forma.
			
			static const std::unordered_map <long int , std::string> currentStrings = {
				
				// -----------------------------------------------------------------------------
				
				// Mapearemos todos los niveles en cada uno de los diferentes flags asociados.
				
				{ LEVEL_DEBUG , 		"DEBUG" } ,
				{ LEVEL_WARNING , 		"WARNING" } ,
				{ LEVEL_ERROR , 		"ERROR" } ,
				{ LEVEL_CRITICAL , 		"CRITICAL" } ,
				{ LEVEL_INFO , 			"INFO" }
				
				// -----------------------------------------------------------------------------
				
			};
			
			// Ahora pásaremos a lo siguiente que es devolver lo que es el string resultado para este mapa de acuerdo a lo que tengamos
			// en el parametro de entrada.
			
			return (static_cast <bool> (currentStrings.count (currentLevel)) ? currentStrings.at (currentLevel) : std::string ("NORMAL"));
			
			// -----------------------------------------------------------------------------
				
		}
		
		// -----------------------------------------------------------------------------
		
		// Tenemos lo siguiente que es la parte de poder cargar e inicializar el siguiente archivo para poder escribir sobre el mismo.
		
		void InitLogger () {
			
			// Crearemos un lock guard para crear este elemento.
			
			std::unique_lock <std::timed_mutex> currentLock (cyttekLoggerMapMutex);
			
			// Primero tenemos que validar que el filename esté asignado.
			
			if (!currentFilename.empty () && !cyttekLoggerStreams.contains (currentFilename)) {
				
				// Validamos el directorio actual.
				
				CyttekFS::path currentPath (currentFilename);
				
				// Si no existe el directorio entonces lo crearemos.
				
				if (!CyttekFS::exists (currentPath.parent_path ())) CreateDirectories (currentPath.parent_path ().generic_string ());
				
				// Estableceremos las flags que vamos a utilizar al momento de abrir nuestro archivo donde estaremos escribiendo.
				
				const auto currentStreamFlags = (std::ios::out | ((currentFlags & ENABLE_TRUNCATE) ? std::ios::trunc : std::ios::app));
				
				// Crearemos y abrirermos lo que es nuestro stream de la siguiente forma , para esto emplearemos los flags para abrirlo en
				// modo de salida y de appended.
				
				std::ofstream currentStream (currentFilename , currentStreamFlags);

				// Para poder inicializar tenemos lo siguiente.
				
				if (currentStream.is_open ()) {
					
					// Anexaremos el siguiente elemento
					
					cyttekLoggerStreams.emplace (std::make_pair (currentFilename , std::move (currentStream)));
					
					// -----------------------------------------------------------------------------
					
				}
				
				// -----------------------------------------------------------------------------
				
			}
			
			// Si tenemos el stream abierto en este momento entonces pasaremos a realizar la inicialización de nuestro respectivo stream.
			
			if (cyttekLoggerStreams.count (currentFilename) && cyttekLoggerStreams.at (currentFilename).is_open ()) streamInitialized = true;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Tenemos nuestro constructor privado asignado por defecto.
		
		LOGGER () = default;
		
		// La construccion de copia y de movimiento estarán eliminadas.
		
		LOGGER (const LOGGER & copy) = delete;
		LOGGER (LOGGER && move) = delete;
		
		// Ahora para los asignadores de la misma forma
		// Ahora el asignador de copia y de movimiento tendremos desabilitados.
		
		LOGGER & operator = (const LOGGER & copy) = delete;
		LOGGER & operator = (LOGGER && move) = delete;
		
		// Destructor normalizad.
		
		~LOGGER () {
			
			// Cerraremos el archivo.
			
			if (cyttekLoggerStreams.count (currentFilename) && cyttekLoggerStreams [currentFilename].is_open ()) cyttekLoggerStreams [currentFilename].close ();
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
	
	// Ahora tenemos los metodos publicos para poder generar el Singleton de esta clase Logger.
		
	// -----------------------------------------------------------------------------
	// 
	// 							Elementos Publicos
	// 							
	// -----------------------------------------------------------------------------
	
	// Tenemo lo siguiente.

	public :
		
		// Tenemos los siguientes metodos para la inicializacion de nuestro logger respectivamente.
		
		// -----------------------------------------------------------------------------
		
		// Initializador de todos los elementos en el LOGGER.
		
		static void Init (const std::string & filename = std::string () , long int flags = (ENABLE_CONSOLE | ENABLE_FILE | LEVEL_DEBUG)) {
			
			// Asignaremos las propiedades que obtenemos de nuestro parametros.
			
			// -----------------------------------------------------------------------------
			
			// Asignaremos el filename que staremos utilizando para poder asignar el stream de la escritura para ese archivo.
			
			GetInstance ().currentFilename = filename;
			
			// Asignaremos las banderas iniciales para poder establecer el comportamiento que tendrá este logger.

			GetInstance ().currentFlags = flags;
			
			// Ahora inicializaremos internamente los componentes de nuestro logger.
			
			GetInstance ().InitLogger ();
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Tenemos primero el Inicializador de nuestro singleton.
		
		static LOGGER & GetInstance () {
			
			// Construiremos una sola vez este logger.
			
			static LOGGER Objeto;
			
			// Devolvemos el objeto.
			
			return Objeto;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Para determinar si es valido entonces tenemos este metodo.
		
		ALWAYS_INLINE bool IsValid () const {
			
			// Devolvemos true si al menos se permite escribir en consola y/o archivo.
			
			return (currentFlags & (ENABLE_CONSOLE | ENABLE_FILE | ENABLE_WRITTER));
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Pasaremos a los properties para nuestro respectivo LOG para poder configurar.
		
		// -----------------------------------------------------------------------------
		// 
		// 							ATTRIBUTES GETTER AND SETTER
		// 							
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		
		// Para poder recuperar rapidamente el actual valor de los atributos tenemos esto.
		
		ALWAYS_INLINE long int GetAttributes () const {
			
			// Devolveremos el valor de nuestros flags actuales.
			
			return currentFlags;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// El siguiente será el metodo setInterlined para poder establecer el espacio entre linea y linea de log para el caso de AUTONL.
		
		void setInterlined (const size_t interlined) {
			
			// -----------------------------------------------------------------------------
			
			// Estableceremos el respectivo valor de interlineado.
			
			currentLineSpace = interlined;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para poder personalizar si es necesaria la salida de un writter necesitamos tener un metodo que permite recibir una funcion
		// que acepte un string a su entrada.
		
		template <typename TFunction> requires std::is_constructible_v <decltype (currentWritter) , TFunction>
		void SetWritter (TFunction && currentNewWritter) {
			
			// Asignaremos el writter a nuestro respectivo objeto.
			
			currentWritter = decltype (currentWritter) (std::forward <TFunction> (currentNewWritter));
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora pasaremos a la parte de los printers de la siguiente forma.
		
		// -----------------------------------------------------------------------------
		// 
		// 							PRINTF METHODS
		// 							
		// -----------------------------------------------------------------------------
		
		// Tenemos en primer lugar el metodo para poder pintar lo que sería nuestro log con el nivel por defecto asignado.
		
		template <typename ... TParams>
		ALWAYS_INLINE void Printf (const char * const format , TParams ... values) {
			
			// Ahora escribiremos lo que hay que escribir con esas banderas asignadas.
			
			if (IsValid ()) Write (StringPrintf (format , values ...));
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Tenemos ahora un printf generral que establecel lo que vendría a ser nuestro printf con los parametros necesarios.

		template <typename ... TParams>
		void Printf (const long int current_level , const char * const format , TParams ... values) {
			
			// Primero asignaremos el 
			
			currentFlags = (currentFlags & (~LOGGER_ENABLE_LEVEL)) | current_level;
			
			// Ahora escribiremos lo que hay que escribir con esas banderas asignadas.
			
			if (IsValid ()) Write (StringPrintf (format , values ...));
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Declaramos lo siguiente.
		
		// -----------------------------------------------------------------------------
		// 
		// 							MACRO DEF FOR PRINTF ALIAS
		// 							
		// -----------------------------------------------------------------------------
		
		// Definiremos nuestra macro def para sustirtuir facilmente en cada tipo de level.
		
		#define PRINTF_ALIAS(LEVEL , String)																	\
																												\
		/* Ahora estableceremos lo que es el print para el nivel en especifico de ERROR. */						\
																												\
		template <typename ... TParams>																			\
		ALWAYS_INLINE void Printf ## String (const char * const format , TParams ... values) {					\
																												\
			/* Invocaremos la función respectiva con el estado de este tipo de log en especifico. */			\
																												\
			if (IsValid ()) Printf (LEVEL , format , values ...);												\
																												\
			/* ----------------------------------------------------------------------------- */					\
																												\
		}																										\
																												\
		// -----------------------------------------------------------------------------
		
		// Definiremos nuestro Printf para level Error.
		
		PRINTF_ALIAS (LEVEL_ERROR , Error)
		
		// Definiremos nuestro Printf para level Debug.
		
		PRINTF_ALIAS (LEVEL_DEBUG , Debug)
		
		// Definiremos nuestro Printf para level Warning.
		
		PRINTF_ALIAS (LEVEL_WARNING , Warning)
		
		// Definiremos nuestro Printf para level Critical.
		
		PRINTF_ALIAS (LEVEL_CRITICAL , Critical)
		
		// Definiremos nuestro Printf para level Info.
		
		PRINTF_ALIAS (LEVEL_INFO , Info)
		
		// Tenemos otra especialización que realiza la impresión rapida de un tipo especifico de log con un template.
		
		template <long int NLevel = LEVEL_DEBUG , typename ... TParams>
		static ALWAYS_INLINE void Print (const char  * const format , TParams ... values) {
			
			// Devolveremos lo que es la llamada con los respectivos parametros.
			
			if (GetInstance ().IsValid ()) GetInstance ().Printf (NLevel , format , values ...);
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora pasaremos con los metodos de PrintfEx para las extensiones.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 								PRINTF EX METHODS
		// 							
		// -----------------------------------------------------------------------------
		
		// Tenemos un metodo actual para pintar
		
		template <CStringValue TStringCurrent , typename ... TExtensions>
		ALWAYS_INLINE void PrintfEx (const TStringCurrent & message , const TExtensions & ... values) {
			
			// Ahora escribiremos lo que hay que escribir con esas banderas asignadas.
			
			if (IsValid ()) Write (MakeString (message) , values ...);
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Tenemos ahora un printf generral que establecel lo que vendría a ser

		template <CStringValue TStringCurrent , typename ... TExtensions>
		void PrintfLevelEx (const long int current_level , const TStringCurrent & message , const TExtensions & ... values) {
			
			// Primero asignaremos el 
			
			currentFlags = (currentFlags & (~LOGGER_ENABLE_LEVEL)) | current_level;
			
			// Ahora escribiremos lo que hay que escribir con esas banderas asignadas.
			
			if (IsValid ()) Write (MakeString (message) , values ...);
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Declaramos lo siguiente.
		
		// -----------------------------------------------------------------------------
		// 
		// 							MACRO DEF FOR PRINTF ALIAS
		// 							
		// -----------------------------------------------------------------------------
		
		// Definiremos la siguiente macro para poder sustituir por las funciones necesarias para cada level.
		
		#define PRINTF_EX_ALIAS(LEVEL , String)																			\
																														\
		/* Ahora estableceremos lo que es nuestro template para los PrintfEx */											\
																														\
		template <CStringValue TStringCurrent , typename ... TExtensions>												\
		ALWAYS_INLINE void Printf ## String ## Ex (const TStringCurrent & message  , const TExtensions & ... values) {	\
																														\
			/* Ahora escribiremos lo que hay que escribir con esas banderas asignadas. */								\
																														\
			if (IsValid ()) PrintfLevelEx (LEVEL , message , values ...);												\
																														\
			/* ----------------------------------------------------------------------------- */							\
																														\
		}																												\
																														\
		// -----------------------------------------------------------------------------
		
		// Definiremos nuestro macro para la funcion PrintfErrorEx.
		
		PRINTF_EX_ALIAS (LEVEL_ERROR , Error)
		
		// Definiremos lo siguiente para poder tener la funcion Printf con el siguiente nivel.
		
		PRINTF_EX_ALIAS (LEVEL_DEBUG , Debug)
		
		// Definiremos lo siguiente para poder tener la funcion Printf con el siguiente nivel.
		
		PRINTF_EX_ALIAS (LEVEL_WARNING , Warning)
		
		// Definiremos lo siguiente para poder tener la funcion Printf con el siguiente nivel.
		
		PRINTF_EX_ALIAS (LEVEL_CRITICAL , Critical)
		
		// Definiremos lo siguiente para poder tener la funcion Printf con el siguiente nivel.
		
		PRINTF_EX_ALIAS (LEVEL_INFO , Info)
		
		// Tenemos otra especialización que realiza la impresión rapida de un tipo especifico de log con un template.
		
		template <long int NLevel = LEVEL_DEBUG , CStringValue TStringCurrent , typename ... TExtensions>
		static ALWAYS_INLINE void PrintEx (const TStringCurrent & message , const TExtensions & ... values) {
			
			// Devolveremos lo que es la llamada con los respectivos parametros.
			
			if (GetInstance ().IsValid ()) GetInstance ().PrintfLevelEx (NLevel , message , values ...);
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
	
};

// Ahora estableceremos lo que serán los diferentes canales por defecto que estaremos utilizando de la siiguiente forma.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		LOGGER CHANNELS
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// La clase LOGGER tiene un parametro de template que sirve para establecer un canal de logg que estamos utilizando , esto ya que la clase en si misma
// es un singleton por lo que solamente existe una sola instancia sin importar desde donde se le invoca , entonces para poder crear otra copia en otro archivo
// con información diferente requerimos otro mecanismo para separar y para esto tenemos el uso de los diferentes tipos de canales.

// -----------------------------------------------------------------------------

// Tenemos entonces princopalmente el canal de LOGG DEBUG para todo el sistema en general.

static constexpr size_t CYTTEK_LOGGER_IDX_DEFAULT = 		0u;

// Ahora determinaremos todos los canales por los que nuestro logger tendría que estar 

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

// Finalizaremos el grupo de documentación del Logger.

// -----------------------------------------------------------------------------
/// @}
// -----------------------------------------------------------------------------

// Terminador de la validación de la macro de nuestro respectivo IFDEF.

#endif // CYTTEK_LOGGER

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
