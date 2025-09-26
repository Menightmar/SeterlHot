
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		ADMINISTRACION DE PROCESOS
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// El siguiente elemento es para poder realizar diferentes acciones en causa de que algun proceso sea ejecutado o se realice alguna ejecucion alterna que
// requiera que nuestro sistema tenga alguna acción para poderse detener o cerrar de alguna manera.

#pragma once

// Ahora definiremos lo siguiente para poder trabajar con nuestro archivo de encabezado de la siguiente forma.

#ifndef PROCESS_MANAGER_UTILITY_HPP
#define PROCESS_MANAGER_UTILITY_HPP

// Ahora lo siguiente será la inclusión de todos nuestros archivos de cabeceras necessraios para poder trabajr con nuestro modulo actual.

// -----------------------------------------------------------------------------
// 
// 							INCLUDING RESOURCES
// 							
// -----------------------------------------------------------------------------

// Comenzaremos incluyendo nuestras bases par poder trabajr con las funcioens mas éstandar de nuestro lenguaje.

#include <stdio.h>
#include <stdlib.h>

// Ahora para el caso de las utilerias tenemos lo siguiente.

#include <utility>

// Incluiremos nuestro acceso al as funciones para el manejamioento de cadenas.

#include <string.h>
#include <string>

// Ahora lo siguiente es para incluir nuestros containers que ocuparemos para nuestros programas.

#include <vector>

// Incluiremos los multi-threads asi como los mutex y el atomic operations.

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

// Incluiremos el importante uso de los std::chrono de esta manera.

#include <chrono>

// Incluiremos el container para el unordered map.

#include <unordered_map>

// Ahora para poder trabajar con funciones especificas de la plataforma windows tendremos que incluir lo siguiente.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							WINDOWS API C++
// 							
// -----------------------------------------------------------------------------

// Para lo siguiente tendremos que estar en la plataforma de windows.

#ifdef _WIN32

// Incluiremos el siguiente header para poder usar funcuiones de la win api.

#include <windows.h>

// Ahora para funciones relacionadas con el manejo de procesos.

#include <tlhelp32.h>

// Para obtener datos de procesos tenemos esto.

#include <psapi.h>

// Para sacar otro tipo de información tenemos este.

#include <shlwapi.h>

// Finalizaremos la validacion siguiente.

#endif

// Ahora pasremos a incluir las dependencias con el resto de modulos de las utilerias que tenemos en estos momentos.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							UTILITY MODULES
// 							
// -----------------------------------------------------------------------------

// Necesitaremos los elementos del core para poder hacer uso de las funciones especificas para manejar archivos.

#include "core.hpp"

// Necesitaremos trabajr con el modulo para las utilerias base de la siguiente forma.

#include "utility.hpp"

// Incluiremos la parte de configuraciones.

#include "configuration.hpp"

// Crearemos registros por lo que necesitaremos estas utilerias para usarlos.

#include "register.hpp"

// Incluiremos los logger también de la misma forma.

#include "logger.hpp"

// Ahora vamos con todos los elementos actuales que conforman este modulo empezando por funciones auxiliares globales asi como clases y sus definiciones.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																	ADMIN PROCESS FUNCTIONS
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Primero tendremos un conjunto de funciones auxiliares que nos permiten obtener lo que realizaremos para poder recuperar todas las funcioens que actualmente
// tendremos para poder establecer la informacipon necesaria para el administrador de procesos de la siguiente forma.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							GET PROCESS UTILITY
// 							
// -----------------------------------------------------------------------------

// Primero tenemos una funcion global que nos devuelve todo el conjunt ode funciones que actualmente sirven para poder obtener lo que es nuestro respectivo
// conjunto de procesos que estarán siendo ejecutados en este momento.s

CYTTEK_API std::vector <std::string> GetAllProcess ();

// Para poder habilitar permisos especiales para poder realizar la lectura de todos los procesos como administrador tendremos la siguiente funcion.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							ENABLE DEBUG MODE PRIVILEGES
// 							
// -----------------------------------------------------------------------------

// Tendremos la siguetne función para poder elevar los privilegios de nuestro sistema y poder obtener todos los procesos.

CYTTEK_API bool EnableProcessPrivileges ();

// Ahora para poder conocer el consumo de recursos de un determinado proceso tendremos nuestro respectivo conjunto de utilerias para gestionarlo.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							GET PROCESS INFO
// 							
// -----------------------------------------------------------------------------

// Tendrmeos ern primer lugar nuestrra estructura para contener todos los datos más importantes de un determinado proceso como su nombre , identificador
// de proceso o manejador y tambien información sobre el consumo de recursos que tiene este determinado proceso.

// -----------------------------------------------------------------------------

// Declaramos la estructura con la información de nuestro determinado proceso para validar su correcto funcionamiento.

struct ProcessInfo {
	
	// Definiremos todosl os elementos publicos para este proceso.
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							PROCESS INFO PUBLIC
	// 							
	// -----------------------------------------------------------------------------
	
	// Tendremos primero nuestro nombre para el proceso actual.
	
	std::string name;
	
	// Tenemos lo siguiente para el full path de nuestro ejecutable asociado al proceso.
	
	std::string filename;
	
	// Tendremos asi mismo el manejador para el proceso indicado.
	
	HANDLE process = nullptr;
	
	// Ahora el process ID (PID) para este proceso.
	
	DWORD PID = 0;
	
	// Ahora bien asignaremos lo que es nuestro respectivo consumo de memoria para este proceso indicado.
	
	size_t processMemory = 0u;
	
	// Ahora para poder asignarl o que es el consumo de handles para recursos tenemos lo siguiente.
	
	size_t processHandles = 0u;
	
	// Ahora para el numero de hilos tenemos esto.
	
	size_t processThreads = 0u;
	
	// De igual forma para poder validar todos los DLL que tienen cargados nuestros procesos necesitamos saber el listado de
	// modulos de los mismos de la siguiente forma.
	
	std::vector <std::string> processModules;
	
	// Ahora algunos metodos auxiliares para la validación de esta estructura.
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							PUBLIC METHODS
	// 							
	// -----------------------------------------------------------------------------
	
	// Tendremos el siguiente para validar que nuestro elemento sea valido.
	
	ALWAYS_INLINE bool IsValid () const {
		
		// Devolveremos true si el nombre y el manejador son correctos.
		
		return !name.empty ();
		
		// -----------------------------------------------------------------------------
		
	}
	
	// -----------------------------------------------------------------------------
	
};

// Ahora pasarmeos a la declaracion de una función para poder generar el info a partir de un determinado nombre de proceso.

CYTTEK_API std::vector <ProcessInfo> GetProcessInfo (bool allProcess , const std::vector <std::string> currentProcessList = std::vector <std::string> ());

// Ahora los servicios tenemos que gestionarlos mediante un conjunto de funciones para poder manejarlos de form aadecuado.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		SERVICE MANAGER
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Para el caso de los servicios que se gestuiona una poco dioferente paral a plataforma windows tendremos aalgunas funciones axuiliares para poder
// realizar diferentes acciones sobre los mismos usando las funcuiones directas dde la api como las que tenemoks a continuiacion.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							START / END SERVICE
// 							
// -----------------------------------------------------------------------------

// Para empezar tendremos un par de funciones para poder realiizar la apertura de un proceso de la siguiente forma.

// -----------------------------------------------------------------------------

// Declaramos nuestra siguiente funcion para poder aperturar un serbicio on el nombre determinado del mismo,

CYTTEK_API bool InitService (const std::string & serviceName);

// Ahora para poder finalizar un determinado servicio tendremos lo siguiente.

CYTTEK_API bool EndService (const std::string & serviceName);

// Ahora pasaremos a nuestro contenido para nuestra clase para poder realizar los respaldos de archivos con la información necesaria.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		PROCESS MANAGER
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Definiremos primero nuestra clase del menejador de procesos que se encarga de levantar un hilo mediante el cuál es indispensable que esté todo momento
// monitoreando los procesos de forma que si alguno de los procesos que están en una lista respectiva es ejecutado entonces exista alguna acción que se
// tenga que realizar para dicho proceso.

// -----------------------------------------------------------------------------

// Primero tendremos unas funciones auxiliares de ayuda para poder finalizar algún proceso o para poder iniciar otro proceso mediante el nombre y el filename
// del mismo , junto a los argumentos para su lanzamiento.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// 
// 							OPEN/CLOSE NEW PROCESSS
// 							
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// Tendremos una funcion para poder gestionar la apertura y el cierre de un nuevo proceso , primero tendremos para aperturar un nuevo proceso conociendo
// el nombre del mismo y el filename a donde está ubicado de la siguiente forma.

CYTTEK_API bool StartNewProcess (const std::string & currentFilename , const std::string & currentArguments = CYTTEK_EMPTY_STRING);

// Ahora para cerrar un proceso tendremos esta otra funcionalidad nativa.

CYTTEK_API bool EndProcess (const std::string & currentProcessName);

// -----------------------------------------------------------------------------

// Ahora tendremos las funciones nativas para manejar los servicios

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// 
// 							CREATE/SET_DECRIPTION/DELETE SERVICE
// 							
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// Para crear un servicio, utilizaremos esta funcionalidad nativa.

CYTTEK_API bool ServiceCreate (const std::string & serviceName, const std::string & binPath, const std::string & opt = "auto");

// Esta es nuestra funcionalidad nativa para poder colocar una descripcion a nuestro servicio

CYTTEK_API bool SetServiceDescription (const std::string & serviceName, const std::string & serviceDescription);

// Y tenemos la funcion nativa para poder eliminar un determinado servicio

CYTTEK_API bool ServiceDelete (const std::string & serviceName);

// Ahora para mejorar un poco las rutinas tendremos un conjunto de funciones de sistema para determinados comandos basicos que serán de ayuda.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		BASIC COMMANDS SYSTEM
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Ahora unas funcionalidades relacioamndas con los comandos del sistema.

// -----------------------------------------------------------------------------

// Para el caso de nuestro reboot tendremos lo siguiente que realiza un reboot forzado.

CYTTEK_API bool ForceRebootWinlogon ();

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// 
// 							CLASE PROCESS MANAGER
// 							
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// Tendremos lo siguiente para poder definir lo siguiente que es la parte de nuestra clase en general para el administrador dep rocesos que
// permite realizar el ajuste en caso de que nuestro sistema tenga que estar monitoreando en todo momento cuando un determinado proceso o servicio es levantado
// y por ende poder realizar las acciones que ahí se especifiquen.

class CYTTEK_API ProcessManager {
	
	// Tendremos primero nuestro respectivo tipo de funcion que determina los datos que pasaremos a los callbacks para poder atender lo que sucede con un
	// determinado proceso ya sea que fue iniciado ocerrado dependiendo el caso.
	
	// -----------------------------------------------------------------------------
	// 
	// 							CALLBACK TYPES FOR FUNCTIONS
	// 							
	// -----------------------------------------------------------------------------
	
	// Definiremos los siguientes datos para nuestra clase de la siguiente orma.
	
	public :
		
		// -----------------------------------------------------------------------------
		
		// Primero tenemos primero nuestro respectivo mapping para las funciones que corresponden para un determinado proceso en general para esto necesitamos
		// guardar como llave el nombre del proceso y posteriormente el mapeo del mismo.
		
		using TProcessCallback = std::function <void (const std::string & , uint8_t)>;
		
		// Ahora lo que tendremos será una enumeración con los diferentes posibles estados que representan lo que ocurrio con el determinado proceso.
		
		enum Action : uint8_t {
			
			// -----------------------------------------------------------------------------
			
			// Tendremos primero el estado OPEN que significa que un proceso fue abierto.,
			
			OPENED ,
			
			// Ahora tendremos el siguiente que representa que un estado fue cerrado.
			
			CLOSED
			
			// -----------------------------------------------------------------------------
			
		};
		
		// -----------------------------------------------------------------------------
	
	// Tendremos ahora nuestros elementos privadops para pode rtener toda la información que necesitamos.
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							ELEMENTOS PRIVADOS
	// 							
	// -----------------------------------------------------------------------------
	
	// Tenemos lo siguiente que es para poder establecer los datos que necesitamos para el procesado.
	
	private :
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							ELEMENTOS FOR LOGGER
		// 							
		// -----------------------------------------------------------------------------
		
		// Tenemos lo siguiente para poder establecer la informacion respectiva en el archivo de LOG con el cual estaremos trabajando para nuestro caso actual.
		
		static constexpr size_t CYTTEK_LOGGER_IDX_PROCESS_MANAGER = GenerateHash ("XFS_PROCESS_MANAGER");

		// Ahora definiremos el tipo de Logger que estaremos utilizando.

		using TLogger = LOGGER <ProcessManager , CYTTEK_LOGGER_IDX_PROCESS_MANAGER>;

		// Inicializaremos de manera estatica lo siguiente.
		// Cargaremos el nuevo Logger para todas estas funcionalidades con la siguiente referencia.

		TLogger & LOG = TLogger::GetInstance ();
		
		// Mantendremos la referencia siempre a nuestras configuraciones.
		
		Configuration & config = Configuration::GetInstance ();
		
		// -----------------------------------------------------------------------------
		
		// Ahora lo que tenemos que hacer es lo siguiente para poder crear nuestro mapa de elementos.
		
		std::unordered_map <std::string , TProcessCallback> processListCallbacks;
		
		// Ahora para los atributos de nuestro monitoring.
		
		// -----------------------------------------------------------------------------
		
		// Priemro tenemos el respectivo timer para poder establecer el tiempo que tenemos que esperar para poder volver a validar los procesos, este valor
		// puede ser un entero que representa la cantidad de milisegunos a esperar.
		
		std::atomic <uint32_t> monitoringTimer;
		
		// Ahora para poder gestionar todo el funcionamiento tendremos que tener un hilo que se encargue de estar revisando en todo momento nuestro
		// total de procesos ejecutados en la busqueda de alguno que coincida con el nombre especificado.
		
		std::thread coreMonitoring;
		
		// Ahora un pequeño flag que indicará si nuestro proceso está corriendo o no y la forma en la que deberia correr.
		
		std::atomic <bool> isRunning;
		
		// Ahora para el procesado de nuestra corrida en el thread de busqueda tendremos lo siguiente.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							CORE MONITORING CALLBACK
		// 							
		// -----------------------------------------------------------------------------
		
		// Tendremos nuestra siguiente funcion para poder establecer lo que es nuestro codigo para la busqueda de procesos en la lista respectiva.
		
		void MonitoringCallback ();
		
		// Ahora para la parte de los constructores tendremos lo siguiente.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							CONSTRUCTORES
		// 							
		// -----------------------------------------------------------------------------
		
		// En primer luigar tenemos nuestro constructor por default para poder iniciar con la configuracion que tenemos ya pre-cargada de la siguiente forma.
		
		ProcessManager (Configuration & currentConfig);
		
		// -----------------------------------------------------------------------------
		
	// Ahora para lo siguiente tendremos nuestros elementos publicos para oder gestrionar la informacion en general de nuestro manager.
	
	// -----------------------------------------------------------------------------
	// 
	// 							ELEMENTOS PUBLICOS
	// 							
	// -----------------------------------------------------------------------------
	
	// Ahora definiremos todos los meetoods publicos para poder configurar nuestro administrador de proceso , crearlo y poderlo configurar de la siguiente forma.
	
	public :
		
		// Tendremos nuestros metodos para acceder a nuestro singleton y de la misma manera para dar inicio al monitoreo de la siguiente forma.
		
		// -----------------------------------------------------------------------------
		// 
		// 							GET INSTANCE AND INIT
		// 							
		// -----------------------------------------------------------------------------
		
		// Tendremos el siguiente metodo para poder obtener la referencia a nuestro singleton para el procesador de procesos de la siguiente forma.
		
		static ProcessManager & GetInstanceFromConfig (Configuration & currentConfig);
		
		// Ahora para lo siguiente es necesario haber inicializado los elementos de nuestro process manager para poder gestionar la lista de datos.
		
		// -----------------------------------------------------------------------------
		
		// Lo siguiente es la parte de la inicializacion formal y lanzamiento del monitoreo el cuál comienza a correr desde que todas las funciones quedan
		// registradas y comienza a iterar por cada proceso que está configurado para la busqueda de elementos.
		
		bool InitMonitoring ();
		
		// Ahora para poder consultar el estado de nuestro administrador de procesos tenemos lo siguiente para poer obtenmer el estado den uestro elemento,
		
		ALWAYS_INLINE bool IsRunning () const {
			
			// Devolveremos el siguietne valor para indicar si está o no corriendo actualmente.
			
			return isRunning.load ();
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora lo siguiente es para poder anexar todos los procesos y poder asociar con una función en especifica a realizar para el caso de que haya sido
		// abierto o cerrado según el caso.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							ADD PROCESS CALLBACKS
		// 							
		// -----------------------------------------------------------------------------
		
		// Para poder anexar lo siguiete tenemos que especificar el nombre del proceso a agregar a la lista de monitoreo y poder especificar la accion
		// que tomará lugar para poder establecer.
		
		void AddProcessMonitoring (const std::string & currentName , const TProcessCallback & currentCallback);
		
		// Finalmente para finalizar nuestro proceso tendremos que tener lo siguiente que nos permita indicar si terminar el proceso.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							CLOSING MONITORING
		// 							
		// -----------------------------------------------------------------------------
		
		// Tenemos el siguiente metodo para poder cerrar este monitoreo de la siguiente forma.
		
		void Close ();
		
		// -----------------------------------------------------------------------------
		
	// -----------------------------------------------------------------------------
	
};

// -----------------------------------------------------------------------------

// Ahora finalmente terminaremos la declaración de nuestro archivo de cabecera de la siguietne dorma.

#endif // PROCESS_MANAGER_UTILITY_HPP

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
