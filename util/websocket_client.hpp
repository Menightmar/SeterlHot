
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		SOCKET CLIENT FOR CYTTEK
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Este archivo contendrá la definición y la implementación de nuestro websocket para utilizar como cliente en cuál permitirá realizar la asignacion y
// envio de informacion a otro recurso externo con la finalidad de que se puedan realizar pases de informacion.

// -----------------------------------------------------------------------------

// Guardaremos nuestro archivo de cabecera.

#pragma once

// Ahora definiremos el siguiente macroguard para poder resguardar este archivo.

#ifndef CYTTEK_WEBSOCKET_CLIENT
#define CYTTEK_WEBSOCKET_CLIENT

// Ahora pasaremos a incluir todas las bases necesarias para trabajar.

// -----------------------------------------------------------------------------

// Incluiremos las bases para poder realizar uso de las funciones de la biblioteca estandar asi como salida y entrada.

#include <stdio.h>
#include <stdlib.h>

// Incluiremos las bases para manejar los strings.

#include <string.h>
#include <string>

// Incluiremos los veectores.

#include <vector>

// Incluiremos elementos de utilerias para poder tarbajar con esto.

#include <utility>

// Incluiremos los mutex para sincronizar entre varios hilos de ejecución.

#include <mutex>

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

// Incluiremos las configuraciones.

#include "configuration.hpp"

// Incluiremos asi mismo las utilerias en general.

#include "utility.hpp"

// Incluiremos los sync-containers para poder crear una pila de request peendientes.

#include "sync_container.hpp"

// Ahora pasaremos a incluir los modulos respectivos para el procesamiento de un elemento con la libreria POCO
// y poder crear nuestro Api REST Cliente.

#ifdef CYTTEK_ENABLE_POCO

// Incluiremos las cabeceras más importantes que ocuparemos para nuestro cliente http actual.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							HTTP CLIENT POCO LIBRARY
// 							
// -----------------------------------------------------------------------------

// Incluiremos nuestro cliente sesion para el caso de que sea un http normal.

#include <Poco/Net/HTTPClientSession.h>

// Ahora lo siguiente que es un HTTP Request para el caso de que se trate de una peticion normal.

#include <Poco/Net/HTTPRequest.h>

// Incluiremos la clase para la reespuesta obtenida por el reeceptor.

#include <Poco/Net/HTTPResponse.h>

// Tenemos una utileria para podere copiar la respuesta a un flujo string de salida.

#include <Poco/StreamCopier.h>

// Ahora para el caso de que se use OpenSSL realizaremos lo siguiente.

#ifdef POCO_USE_OPENSSL

// Incluiremos el contexto global para poder crear.

#include <Poco/Net/Context.h>

// Incluiremos la sesion HTTPS Para el lado de nuestro clieente.

#include <Poco/Net/HTTPSClientSession.h>

// Incluiremos el SSL Manager para la gestion de atributos relacionados a openssl.

#include <Poco/Net/SSLManager.h>

// -----------------------------------------------------------------------------

#endif

// -----------------------------------------------------------------------------

#else

// Incluiremos nuestra dependencia de IXWEBSOCKET para poder trabajar con todo lo que necesitamos.

// ----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							IX WEB SOCKET LIBRARY
// 							
// -----------------------------------------------------------------------------

// Incluiremos los net systems.

#include <ixwebsocket/IXNetSystem.h>

// Incluiremos los sockets normales.

#include <ixwebsocket/IXSocket.h>

// Incluiremos la factoria de sockets.

#include <ixwebsocket/IXSocketFactory.h>

// Incliremos los agentes de usuario.

#include <ixwebsocket/IXUserAgent.h>

// Incluiremos los tipos de mensaje.

#include <ixwebsocket/IXWebSocketMessageType.h>

// Utilizaremos la clase socket , la factoria y el websocket para poder tener acceso a la clase y todos sus elementos.

#include <ixwebsocket/IXWebSocket.h>

// Incluiremos los HTTPclient de la siguiente forma.

#include <ixwebsocket/IXHttpClient.h>

// Incluiremos adicional a esto los parseadores de mensajes.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							HTTP PARSER FOR REQUEST/RESPONSE
// 							
// -----------------------------------------------------------------------------

// Incluiremos nuestros parser para peticiones.

#include <httprequestparser.h>

// Incluiremos el siguiente para los response.

#include <httpresponseparser.h>

// -----------------------------------------------------------------------------

#endif

// Ahora pasaremos con la clase principal para nuestro respectivo cliente.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		CLIENT WEB SOCKET CYTTEK
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Definiremos nuestra clase WEBSOCKET para poder trabajar con todo lo que tenemos a continuacion y poder transmitir de esta manera la informacion que
// necesitemos a la salida.

// -----------------------------------------------------------------------------

// Comenzaremos por implementar una funcion para inicializar en el caso de windows los elementos de net system.

extern CYTTEK_API void WebSocketInit (Configuration & config);

// Ahora para el caso de terminar la sesión requerimos otra funcion global que finalice todos los componentes o librerias con Net.

extern CYTTEK_API void WebSocketUninit (Configuration & config);

// Ahora pasaremos a la declaracion de valores comunes.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							WEB SOCKET MEESSAGE.
// 							
// -----------------------------------------------------------------------------

// Tenemos entonces la estructura con la informacion más importante para un tipo de mensaje , entre estos datos contaremos con un determinado tipo de mensaje
// para poder saber que tipo de mensaje se refiere.

// -----------------------------------------------------------------------------

// Crearemos primero una enumeracion para poder establecer la informacion respectiva.

#ifndef CYTTEK_ENABLE_POCO

// Declaramos nuestro respectivo enumeracion para todos los tipos de mensaje que pueden existir.

using enum ix::WebSocketMessageType;

// -----------------------------------------------------------------------------

#endif

// Tendremos nuestra estructura para guardar toda la informacion que neceesitemos de la siguiente forma.

struct WebSocketMessage {
	
	// Tendremos lo siguiente de esta forma.
	
	// -----------------------------------------------------------------------------
	// 
	// 							MESSAGE DATA FOR WEBSOCKET
	// 							
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	
	// Primero contaremos con el mensaje de datos que tenemos en nuestro respectiva comunicacion.
	
	std::string message;
	
	// Tendremos los headers en caso de que se tengan para las peticiones HTTP.
	
	std::unordered_map <std::string , std::string> headers;
	
	// Validaremeos lo siguiente.
	
	#ifndef CYTTEK_ENABLE_POCO
	
	// Ahora contaremos con el tipo de mensaje en particular.
	
	ix::WebSocketMessageType type;
	
	// -----------------------------------------------------------------------------
	
	#endif
	
	// -----------------------------------------------------------------------------
	
};

// Ahora pasaremos con la clase para el cliente de la siguiente forma.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							WEB SOCKET CLIENT CLASS
// 							
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

// Tenemos entonces la siguiente clase para el tratamientoi de nuestro cliente web socket y poder enviar y transmitir mensajes a un determinado
// server , con un metodo para invocar cuando la respuesta sea devuelta.

class CYTTEK_API WebSocketClient {
	
	// Tendremos varios elementos y metodos privados para la gestión de la información de nuestro actual web socket.
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							ELEMENTOS PRIVADOS
	// 							
	// -----------------------------------------------------------------------------
	
	// Tenemos entonces al siguiente declaracion.
	
	private :
		
		// Tenemos los siguientes atributos para nuiestra clase acftual.
		
		// -----------------------------------------------------------------------------
		
		// Lo siguiente es la declaracion de todos los elementos privados que necesitaremos para nuestro cliente.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							ATRIBUTOS DE LOGGER
		// 							
		// -----------------------------------------------------------------------------
		
		// Tenemos lo siguiente para poder establecer la informacion respectiva en el archivo de LOG con el cual estaremos trabajando para nuestro caso actual.
		
		static constexpr size_t CYTTEK_LOGGER_IDX_WEBSOCKET_CLIENT = GenerateHash ("WEBSOCKET_CLIENT");

		// Ahora definiremos el tipo de Logger que estaremos utilizando.

		using TLogger = LOGGER <WebSocketClient , CYTTEK_LOGGER_IDX_WEBSOCKET_CLIENT>;

		// Inicializaremos de manera estatica lo siguiente.
		// Cargaremos el nuevo Logger para todas estas funcionalidades con la siguiente referencia.

		TLogger & LOG = TLogger::GetInstance ();
		
		// Tendremos la referencia a nuestra configuracion para nuestro cliente actual en caso de que sea necesario crear alguna.
		
		Configuration & config = Configuration::GetInstance ();
		
		// Ahora declaramos elementos base para nuestro websocket client.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							CLIENT ATTRIBUTES
		// 							
		// -----------------------------------------------------------------------------
	
		// Declaramos nuestro string con la conexión actual a la cual estamos apuntando en formato : IP:PORT
		
		std::string endPoint;
		
		// Tenemos el puerto destino tambien.
		
		int port = -1;
		
		// Tenemos el path destino.
		
		std::string path;
		
		// Tenemos asi mismo el estado de la conexión actual para nuestro cliente.
		
		bool connected = false;
		
		// Ahora determinaremos lo que realizar mediante un elemento funcional que reciba determinada informacion.
		
		std::function <void (WebSocketMessage)> currentCallback;
		
		// Definiremos un pequeño mutex para el control entre diferentes hilos de ejecucion.
		
		std::mutex currentMutex;
		
		// Ahora para el caso de usar la libreria POCO tendremos la siguiente implementacion.
		
		#ifdef CYTTEK_ENABLE_POCO
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							POCO FRAMEWORK HTTP CLIENT
		// 							
		// -----------------------------------------------------------------------------
		
		// Crearemos el objeto de la sesión para el caso de nuestro HTTPClient.
		
		std::shared_ptr <Poco::Net::HTTPClientSession> currentSocketHttp;
		
		// Ahora para el caso de que tengamos tambien a nuestro HTTPS con OpenSSL Habilitado tendremos esto.
		
		#ifdef POCO_USE_OPENSSL
		
		// Ahora para configurar opciones requerimos primordialmente de unas configuraciones que estén creadas de
		// un momento a otro.
		
		Poco::Net::Context::Params currentOptions;
		
		// Declaramos lo que es nuestro contexto para la creacion de nuestro cliente de escucha de la siguieente manera.
		
		Poco::Net::Context::Ptr currentContext;
		
		// Crearemos el objeto HTTPSClient Sesion para manejar conexiones security con TLS.
		
		std::shared_ptr <Poco::Net::HTTPSClientSession> currentSocketHttps;
		
		// -----------------------------------------------------------------------------
		
		#endif
		
		// Declaramos el actual request que tendremos configurado para 
		
		std::shared_ptr <Poco::Net::HTTPRequest> currentRequest;
		
		// -----------------------------------------------------------------------------
		
		#else
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							IX WEB SOCKET PROPERTIES
		// 							
		// -----------------------------------------------------------------------------
		
		// Tenemos las opciones para nuestro tls server.
		
		ix::SocketTLSOptions currentOptions;
		
		// Para guardar nuestro mensaje de error tenemos que tener a la mano un string.
		
		std::string currentMsgError;
		
		// Ahora tendremos lo siguiente que es la parte de nuestro respectivo objeto de web socket con el que vamos a comunicarnos.
		
		std::shared_ptr <ix::Socket> currentSocket;
		
		// Ahora para tener acceso a los request y poderlos cancelar de forma asyncrona tendremos lo siguiente.
		
		SyncContainer <std::vector , std::pair <DWORD , ix::HttpRequestArgsPtr>> currentRequests;
		
		// Para tener acceso a peticiones directamente tenemos nuestro respectivo ejecutor de peticiones.
		
		std::shared_ptr <ix::HttpClient> currentSocketHttp;
		
		// Para el caso de un web socket tenemos este otro.
		
		std::shared_ptr <ix::WebSocket> currentWebSocket;
		
		// Lo siguiente será definir los metodos auxiliares privados para poder atender.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							METODOS AUXILIARES PRIVADOS
		// 							
		// -----------------------------------------------------------------------------
		
		// Tenemos el siguiente que será nuestro metodo de callback asociado directamente con el callback para nuestro socket de la siguiente forfmr.a
		
		void MessageCallback (const ix::WebSocketMessagePtr & message);
		
		// -----------------------------------------------------------------------------
		
		#endif
		
		// -----------------------------------------------------------------------------
	
	// Ahora continuaremos con los elementos publicos para poder realizar la configuracion de todo lo que se necesita.
	
	// -----------------------------------------------------------------------------
	// 
	// 							PUBLIC ELEMENTS
	// 							
	// -----------------------------------------------------------------------------
	
	// Tenemos por este ladxo los siguiente selementos puiblicos para poder continuar.
	
	public :
		
		// Contaremos primero con los constructores para nuestra clase en particular de la siguiente forma.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							CONSTRUCTORES
		// 							
		// -----------------------------------------------------------------------------
		
		// Tenemos nuestro constructor por default de la siguiente forma.
		
		WebSocketClient ();
		
		// Ahora tenemos el siguiente que es el constructor para cuando tenemos ya la ruta principal a la cual vamos a hacer referencia de la siguiente manera.
		
		WebSocketClient (const std::string & currentEndPoint , int currentPort , const std::string & currentPath , bool webSocket = true);
		
		// Ahora para gestionar todas las configuraciones permitidas de una sola vez tenemos esta otra sobercarga.
		
		WebSocketClient (Configuration & currentConfig);
		
		// Ahora pasaremos a lo siguiente que son nuestros getters y setters para la clase actual.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							GETTERS AND SETTERS
		// 							
		// -----------------------------------------------------------------------------
		
		// Tendremos primero nuestro getter para poder obtener el valor actual de nuestro currentEndPoint.
		
		ALWAYS_INLINE std::string GetEndPoint () const {
			
			// Devolveremos nuestro actual endPoint.
			
			return endPoint;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora otro para obtener el full end point usando el puerto y path especifico.
		
		ALWAYS_INLINE std::string GetFullEndPoint () const {
			
			// Devolveremos el siguiente string.
			
			return StringPrintf ("%s:%i%s" , endPoint.c_str () , port , path.c_str ());
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Para validar si está conectado en estos momentos tenemos este otro metodol..
		
		
		ALWAYS_INLINE bool IsConnected () const {
			
			// Devolveremos el siguiente valor.
			
			return connected;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para poder establecer el callback que ocurrirá cuando se realice la respuesta de parte de nuestro server tenemos este.
		
		template <typename TFunction>
		requires requires (TFunction currentFunction) {
			
			// -----------------------------------------------------------------------------
			
			// Requerimos que se pueda construir nuestro respectiva funcion con base en lo que obtenemos.
			
			{ decltype (currentCallback) (currentFunction) };
			
			// -----------------------------------------------------------------------------
			
		}
		void SetResponseCallback (TFunction && currentFunction) {
			
			// Estableceremos el valor de nuestro callback respectivo.
			
			currentCallback = std::function <void (WebSocketMessage)> (std::forward <TFunction> (currentFunction));
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora los metodos para realizar conexiones y poder con esto definir el socket interno que manejara la informacion.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 						CONNECTION AND MESSAGES
		// 							
		// -----------------------------------------------------------------------------
		
		// Tenemos nuestro metodo que relaiza la conexion a un endPoint determinado y en estos momentos si se establece la conexion correctamente
		// será posible la escritura y el envio de informacion.
		
		// -----------------------------------------------------------------------------
		
		// Definiremos el siguiente metodo para poder realiar una nueva coneccion a otro endPoint.
		
		bool Connect (const std::string & currentEndPoint , int currentPort , const std::string & currentPath , bool webSocket = true);
		
		// Para poderlo iniciar el thread tenemos este metodo que se encarga de realizar el inicio de nuestro thread para atender los mensajes.
		
		void Start ();
		
		// Ahora para poder cancelar el actual request enviado de forma asyncrona tendremos lo siguiente.
		
		bool Cancel ();
		
		// Ahora para la configuración de Ca-Certs para nuestra comunicación segura TLS de la siguiente forma.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							TLS OPTIONS FOR SERVER
		// 							
		// -----------------------------------------------------------------------------
		
		// Tenemos el siguiente elemento para poder establecer el contenido de un certificado de la siguiente forma.
		
		bool SetCert (const std::string & currentData , bool filename = false);
		
		// Se tiene lo siguiente para poder establecer la información referente a la configuracion de TLS de la siguiente forma.
		
		bool SetKey (const std::string & currentData , bool filename = false);
		
		// Ahora para colocar el concentrado de ca-certs para el cliente tendremos lo siguiente.
		
		bool SetCAFile (const std::string & currentData , bool filename = false);
		
		// Para poder finalizar tenemos lo siguiente que contempla el cierre de nuestro cliente.
		
		// -----------------------------------------------------------------------------
		// 
		// 							CLOSING CONNECTIONS
		// 							
		// -----------------------------------------------------------------------------
		
		// Tenemos el siguiente metodo para poder cerrar nuestro cliente.
		
		void Close ();
		
		// Ahora pasaremos a la parte del envio de mensajes , simplemente con un metodo para enviar una cadena tenemos lo siguiente.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							SENDING MESSAGES
		// 							
		// -----------------------------------------------------------------------------
		
		// Tenemos el siguiente metodo que se encarga de realizar el envio de mensajes desde este elemento.
		
		void Send (const std::string & currentMessage);
		
		// Ahora pasaremos con la implementacion de nuestro destructor.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							DESTRUCTOR FOR CLIENT.
		// 							
		// -----------------------------------------------------------------------------
		
		// Declaramos nuestro destructor respectivo que tenemos en estos momentos.
		
		virtual ~WebSocketClient ();
		
		// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	
};

// Ahora pasarmeos a realizar lo siguiente para el caso de las funciones para acceder a una IP normal de nuestro server.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							WEB SOCKET SERVER IP
// 							
// -----------------------------------------------------------------------------

// Definirenos la siguiente funcion para poder comunicar con el api de windows o del S.O para consultar la IP del cliente.

CYTTEK_API extern std::string GetCurrentIP ();

// -----------------------------------------------------------------------------

// Para finalizar nuestro web socket tenemos lo siguiente.

#endif // CYTTEK_WEBSOCKET_CLIENT

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
