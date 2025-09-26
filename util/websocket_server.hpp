
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		SOCKET SERVER FOR CYTTEK
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Este archivo contendrá la definición y la implementación de nuestro websocket para utilizar como server en cuál permitirá realizar la asignacion y
// envio de informacion a otro recurso externo con la finalidad de que se puedan realizar pases de informacion.

// -----------------------------------------------------------------------------

// Guardaremos nuestro archivo de cabecera.

#pragma once

// Ahora definiremos el siguiente macroguard para poder resguardar este archivo.

#ifndef CYTTEK_WEBSOCKET_SERVER
#define CYTTEK_WEBSOCKET_SERVER

// Ahora pasaremos a incluir todas las bases necesarias para trabajar.

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

// Incluiremos las configuraciones.

#include "configuration.hpp"

// Incluiremos asi mismo las utilerias en general.

#include "utility.hpp"

// Incluiremos el siguiente.

#include "websocket_client.hpp"

// Ahora validaremos lo que tenemos para implementar los elementos de POCO.

#ifdef CYTTEK_ENABLE_POCO

// Ahora incluiremos todos los elemnetos del framework de poco para poder hacer el procesamiento necesario que tenemos que tener.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							POCO HTTP/HTTPS SERVER
// 							
// -----------------------------------------------------------------------------

// Incluiremos primero nuestro HTTP Server para poder utilizar los elementos de estee objeto.

#include <Poco/Net/HTTPServer.h>

// Para poder tener acceeso a nuestros elementos del request tenemos que incluir lo siguiente.

#include <Poco/Net/HTTPServerRequest.h>

// Ahora para poder conformar las respuestas que devolverá nuestro server tenemos que tener lo siugiente.

#include <Poco/Net/HTTPServerResponse.h>

// Ahora para el gestionador de responses tenemos que tener lo sisguiente para poder gestionar lo que responderá.

#include <Poco/Net/HTTPRequestHandler.h>

// Ahora para poder realizar la creacion de la factoria de responses tenemos que tener lo siguiente.

#include <Poco/Net/HTTPRequestHandlerFactory.h>

// Ahora para podere acceder a los atributos comunes del server socket tenemos lo siguiente.

#include <Poco/Net/ServerSocket.h>

// Ahora validaremos si tenemos el modo OpenSSL habilitado para lo siguiente.

#ifdef POCO_USE_OPENSSL

// Incluiremos los contextos normales para el modo con el Servidor.

#include <Poco/Net/Context.h>

// Incluireemos el modo de server socket seguro para usar con la capa de TLS.

#include <Poco/Net/SecureServerSocket.h>

// De igual forma para poder acceeder a funciones del SSLManager necesitamos de lo siguiente.

#include <Poco/Net/SSLManager.h>

// -----------------------------------------------------------------------------

#endif

// Ahora para el uso de ix web socket.

#else

// Incluiremos las dependencias para nuestros ix server de la siguiente forma.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							IX WEB SERVER CLASS
// 							
// -----------------------------------------------------------------------------

// Incluiremos la base para los ix servers de esta manera.

#include <ixwebsocket/IXSocketServer.h>

// Incluiremos los HTTP.

#include <ixwebsocket/IXHttp.h>

// Tenemos que incluir lo siguiente para hacer uso de web servers con HTTP de la siguiente forma.

#include <ixwebsocket/IXHttpServer.h>

// -----------------------------------------------------------------------------

#endif

// Ahora pasaremos con la clase principal para nuestro respectivo server.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		DECLARACION DE CLASE PARA SERVER
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Ahora pasaremos con la clase para el cliente de la siguiente forma.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							WEB SOCKET SERVER CLASS
// 							
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

// Tenemos entonces la siguiente clase para el tratamientoi de nuestro cliente web socket y poder enviar y transmitir mensajes a un determinado
// server , con un metodo para invocar cuando la respuesta sea devuelta.

class CYTTEK_API WebSocketServer {
	
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
		
		static constexpr size_t CYTTEK_LOGGER_IDX_WEBSOCKET_SERVER = GenerateHash ("WEBSOCKET_SERVER");

		// Ahora definiremos el tipo de Logger que estaremos utilizando.

		using TLogger = LOGGER <WebSocketServer , CYTTEK_LOGGER_IDX_WEBSOCKET_SERVER>;

		// Inicializaremos de manera estatica lo siguiente.
		// Cargaremos el nuevo Logger para todas estas funcionalidades con la siguiente referencia.

		TLogger & LOG = TLogger::GetInstance ();
		
		// Tendremos la referencia a nuestra configuracion para nuestro cliente actual en caso de que sea necesario crear alguna.
		
		Configuration & config = Configuration::GetInstance ();
		
		/// Ahora los atributos del server en común que tenemos.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							SERVER ATTRIBUTES
		// 							
		// -----------------------------------------------------------------------------
		
		// Tenemos nuestro end-point (IP) que estamos gestionando actualmente para abrir este puerto del server.
		
		std::string endPoint;
		
		// Tenemos el numero de puerto siguiente.
		
		int port = -1;
		
		// Tenemos asi mismo el estado de la conexión actual para nuestro cliente.
		
		bool connected = false;
		
		// Para saber si está escuchando en estos momentos.
		
		bool listening = false;
		
		// Ahora determinaremos lo que realizar mediante un elemento funcional que reciba determinada informacion.
		
		std::function <std::string (WebSocketMessage)> currentCallback;
		
		// Ahora para el caso del os callback para el modo de web socket tenemos lo siguiente.
		
		std::function <std::string (WebSocketMessage)> currentClientCallback;
		
		// Definiremos un pequeño mutex para el control entre diferentes hilos de ejecucion.
		
		std::mutex currentMutex;
		
		// Ahora validaremos si tenemos a ix web socket o a poco para poder continuar.
		
		#ifdef CYTTEK_ENABLE_POCO
		
		// Conformaremos los datos para nuestro manejador de respuestas en el caso de POCO de la siguiente forma.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							HTTP HANDLER REQUESTS
		// 							
		// -----------------------------------------------------------------------------
		
		// Para podere atender peticiones y procesar lo que llega y el dato que debemos de devolver tendremeos que crear una subclase del
		// manejador de peticiones y sobre-escribir el metodo respectivo para poder invocar a las funciones pertinentes.
		
		class ClientMessageHandler : public Poco::Net::HTTPRequestHandler {
			
			// Implementaremos los metodos publicos de la interfaz base para podeer trabajar con esto.
			
			// -----------------------------------------------------------------------------
			
			// -----------------------------------------------------------------------------
			// 
			// 							ATRIBUTOS PRIVADOS
			// 							
			// -----------------------------------------------------------------------------
			
			// Definiremos los siguientea atributos privados para nuestro manejador de mensaje.
			
			private :
				
				// -----------------------------------------------------------------------------
				
				// Definiremos la referencia a nuestro web socket server base para usar con los elementos privados.
				
				WebSocketServer * currentServer = nullptr;
				
				// -----------------------------------------------------------------------------
			
			// Ahora paral os elementos publicos tenemos lo siguiente.
			
			// -----------------------------------------------------------------------------
			
			// -----------------------------------------------------------------------------
			// 
			// 							METODOS PUBLICOS
			// 							
			// -----------------------------------------------------------------------------
			
			// Definiremos los metodos pubvlicos para esta clase base.
			
			public :
				
				// Crearemos el objeto WebSocketServer para nuestro elemento actual.
				
				// -----------------------------------------------------------------------------
				
				// -----------------------------------------------------------------------------
				// 
				// 							CONSTRUCTOR BASE WEB SOCKET
				// 							
				// -----------------------------------------------------------------------------
				
				// Definiremos el siguiente constructor para poder pasar la referencia a nuestro objeto WebSocketServer y que lo pueda
				// utilizar para diferentes fines.
				
				ClientMessageHandler (WebSocketServer * baseServer) : currentServer (baseServer) { /* Inicializado */ }
			
				// -----------------------------------------------------------------------------
				
				// -----------------------------------------------------------------------------
				// 
				// 							CLIENT MESSAGE HANDLER
				// 							
				// -----------------------------------------------------------------------------
				
				// Declaramos el metodo para la implementacion de la logica a aplicar para la llamada a las funciones de todos nuestras
				// peticiones entrantes de cliente de la siguiente forma.
				
				void handleRequest (Poco::Net::HTTPServerRequest & currentRequest , Poco::Net::HTTPServerResponse & currentResponse) override;
				
				// -----------------------------------------------------------------------------
			
		};
		
		// Ahora para lo siguiente teneemos que crear nuestra implementacion de la factoria que nos ayude a crear la instancia de dicha clase.
		
		class ClientMessageFactory : public Poco::Net::HTTPRequestHandlerFactory {
			
			// Definiremos los metodos publicos para la devolucion de nuestra instancia de la siguiente forma.
			
			// -----------------------------------------------------------------------------
			
			// -----------------------------------------------------------------------------
			// 
			// 							ATRIBUTOS PRIVADOS
			// 							
			// -----------------------------------------------------------------------------
			
			// Definiremos los siguientea atributos privados para nuestro manejador de mensaje.
			
			private :
				
				// -----------------------------------------------------------------------------
				
				// Definiremos la referencia a nuestro web socket server base para usar con los elementos privados.
				
				WebSocketServer * currentServer = nullptr;
				
				// -----------------------------------------------------------------------------
				
			// Ahora para los elementos publicos tenemos lo siguiente.
			
			// -----------------------------------------------------------------------------
			
			// -----------------------------------------------------------------------------
			// 
			// 							METODOS PUBLICOS
			// 							
			// -----------------------------------------------------------------------------
			
			// Definiremos el siguiente metodo.
			
			public :
			
				// Crearemos el objeto WebSocketServer para nuestro elemento actual.
				
				// -----------------------------------------------------------------------------
				
				// -----------------------------------------------------------------------------
				// 
				// 							CONSTRUCTOR BASE WEB SOCKET
				// 							
				// -----------------------------------------------------------------------------
				
				// Definiremos el siguiente constructor para poder pasar la referencia a nuestro objeto WebSocketServer y que lo pueda
				// utilizar para diferentes fines.
				
				ClientMessageFactory (WebSocketServer * baseServer) : currentServer (baseServer) { /* Inicializado */ }
				
				// Ahora para el siguiente metodo tenemos lo que continua.
				
				// -----------------------------------------------------------------------------
				
				// -----------------------------------------------------------------------------
				// 
				// 							MAKE MESSAGE HANDLER OBJECT
				// 							
				// -----------------------------------------------------------------------------
				
				// Definiremos el siguieente metodo par crear el manejador de peticiones que corresponde para la petición respectiva.
			
				Poco::Net::HTTPRequestHandler * createRequestHandler (const Poco::Net::HTTPServerRequest & currentRequest) override {
					
					// Devolveremos una nueva instancia de nuestra clase manejadora para estas peticiones.
					
					return new ClientMessageHandler (currentServer);
					
					// -----------------------------------------------------------------------------
					
				}
				
				// -----------------------------------------------------------------------------
			
		};
		
		// Ahora las propiedades para poder crear todos los elementos que necesitamos de Poco para nuestro server.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							POCO HTTP SERVER PROPERTIES
		// 							
		// -----------------------------------------------------------------------------
		
		// Comenzando primero por el respectivo ServerSocket el cual será nuestra sesion del lado del server para gestionar la conexión
		// respectiva y poder escuchar peticiones.
		
		std::shared_ptr <Poco::Net::ServerSocket> currentSocketHttp;
		
		// Para podere configurar los parametros de nuestro server tendremos una instancia a nuestros params de la siguiente forma.
		
		Poco::Net::HTTPServerParams::Ptr currentServerOptions;
		
		// Crearemos la instancia a nuestro server para gestionar todas las conexiones y poder controlar todo lo que necesitaremos.
		
		std::shared_ptr <Poco::Net::HTTPServer> currentServer;
		
		// Ahora para el caso de OpenSSL tendremos algunos atributos adicionalese que agregar.
		
		#ifdef POCO_USE_OPENSSL
		
		// Ahora para configurar opciones requerimos primordialmente de unas configuraciones que estén creadas de
		// un momento a otro.
		
		Poco::Net::Context::Params currentOptions;
		
		// Incluiremos nuestro contexto el cual tendrá información sobre el SSLManager para la gestión de certificados y llaves.
		
		Poco::Net::Context::Ptr currentContext;
		
		// Ahora definiremos lo siguiente que es el SecureServerSocket que determinaremos para poder asignar.
		
		std::shared_ptr <Poco::Net::SecureServerSocket> currentSocketHttps;
		
		// -----------------------------------------------------------------------------
		
		#endif
		
		// Ahora para el caso de ix teneemos lo siguieente.
		
		#else
		
		// Conformaremos lo siguiente que es el estado de la conexión siguiente para poder custimizar los ID's de los tipos de conexión
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							CONNECTION STATE CUSTOM
		// 							
		// -----------------------------------------------------------------------------
		
		// Tenemos lo siguiene para la clase que realizaremos para customizar nuestros id's de la siguiente forma.
		
		class CustomConnectionState : public ix::ConnectionState {
			
			// Tenemos los siguientes elementos privados.
			
			// -----------------------------------------------------------------------------
			// 
			// 							CURRENT ATTRIBUTE PRIVATE
			// 							
			// -----------------------------------------------------------------------------
			
			// Tenemos lo siguiente.
			
			private :
				
				// -----------------------------------------------------------------------------
				
				// Tenemos el siguiente campo para usar como contador de conexiones de la siguiente forma.
				
				int counter = 0;
				
				// -----------------------------------------------------------------------------
				
			// Ahora tenemos lo siguiente que son los elementos protegidos de la siguiente forma.
				
			// -----------------------------------------------------------------------------
			// 
			// 							ELEMENTS PUBLICOS
			// 							
			// -----------------------------------------------------------------------------
			
			public :
				
				// -----------------------------------------------------------------------------
				
				// Tenemos lo siguiente para poder realizar la asignación de nuestro ID de manera única de la siguiente forma.
				
				virtual void computeId () override {
					
					// Asignaremos el siguietne ID a nuestro respectiva conección de la siguietne forma.
					
					_id = StringPrintf ("ConnectionID|%i" , (counter ++));
					
					// -----------------------------------------------------------------------------
					
				}
				
				// -----------------------------------------------------------------------------
				
			// -----------------------------------------------------------------------------
			
		};
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							IX WEB SOCKET PROPERTIES
		// 							
		// -----------------------------------------------------------------------------
		
		// Para guardar nuestro mensaje de error tenemos que tener a la mano un string.
		
		std::string currentMsgError;
		
		// Ahora tendremos lo siguiente que es la parte de nuestro respectivo objeto de web socket con el que vamos a comunicarnos.
		
		std::shared_ptr <ix::HttpServer> currentSocket;
		
		// Para las opciones relacionadas con el TLS tendremos la siguiente instancia de la estructura de la siguiente forma.
		
		ix::SocketTLSOptions currentTLS;
		
		// Lo siguiente será definir los metodos auxiliares privados para poder atender.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							METODOS AUXILIARES PRIVADOS
		// 							
		// -----------------------------------------------------------------------------
		
		// Tenemos ahora nuestro respectivo metodo callback para atender peticiones de nuestro web socket client.
		
		void ClientMessageCallback (std::shared_ptr <ix::ConnectionState> currentState , ix::WebSocket & currentSocket , const ix::WebSocketMessagePtr & currentMsg); 
		
		// Tenemos nuestro metodo de callback para todos los mensajes que lleguen de parte de nuestro cliente.
		
		ix::HttpResponsePtr MessageCallback (ix::HttpRequestPtr currentRequest , std::shared_ptr <ix::ConnectionState> currentState);
		
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
		
		WebSocketServer ();
		
		// Ahora tenemos el siguiente que es el constructor para cuando tenemos ya la ruta principal a la cual vamos a hacer referencia de la siguiente manera.
		
		WebSocketServer (const std::string & currentEndPoint , int currentPort , bool webSocket = true);
		
		// Ahora para gestionar todas las configuraciones permitidas de una sola vez tenemos esta otra sobercarga.
		
		WebSocketServer (Configuration & currentConfig);
		
		// Ahora pasaremos a lo siguiente que son nuestros getters y setters para la clase actual.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							GETTERS AND SETTERS
		// 							
		// -----------------------------------------------------------------------------
		
		// Para obtener el actual HOST (EndPoint) que tiene nuestro server tenemos lo siguiente.
		
		ALWAYS_INLINE std::string GetEndPoint () const {
			
			// Devolveremos el valor de nuestro endpoint de la siguiente forma.
			
			return endPoint;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Tendremos el siguiente metodo para saber si nuestro actual server tiene un puerto y cual es el que tiene asignado.
		
		ALWAYS_INLINE int GetPort () const {
			
			// Devolveremos nuestro actual port.
			
			return port;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Para poder validar que nuestro server actualmente está escuchando activamente tenemos este otro metodo.
		
		ALWAYS_INLINE bool IsListening () const {
			
			// Devolveremos el siguiente estado.
			
			return listening;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Para validar si en estos momentos tiene conexiones nuestro server.
		
		ALWAYS_INLINE bool IsConnected () const {
			
			// Devolveremos el siguiente valor.
			
			return connected;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para poder establecer el callback de nuestro message normal tenemos lo siguiente.
		
		template <typename TFunction>
		requires requires (TFunction currentFunction) {
			
			// -----------------------------------------------------------------------------
			
			// Requerimos que se pueda construir nuestro respectiva funcion con base en lo que obtenemos.
			
			{ decltype (currentCallback) (currentFunction) };
			
			// -----------------------------------------------------------------------------
			
		}
		void SetMessageCallback (TFunction && currentFunction) {
			
			// Estableceremos el valor de nuestro callback respectivo.
			
			currentCallback = decltype (currentCallback) (std::forward <TFunction> (currentFunction));
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para poder establecer el callback que ocurrirá cuando se realice la respuesta de parte de nuestro server tenemos este.
		
		template <typename TFunction>
		requires requires (TFunction currentFunction) {
			
			// -----------------------------------------------------------------------------
			
			// Requerimos que se pueda construir nuestro respectiva funcion con base en lo que obtenemos.
			
			{ decltype (currentClientCallback) (currentFunction) };
			
			// -----------------------------------------------------------------------------
			
		}
		void SetClientMessageCallback (TFunction && currentFunction) {
			
			// Estableceremos el valor de nuestro callback respectivo.
			
			currentClientCallback = decltype (currentClientCallback) (std::forward <TFunction> (currentFunction));
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora los metodos para realizar conexiones y poder con esto definir el socket interno que manejara la informacion.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 						LISTENING AND MESSAGES
		// 							
		// -----------------------------------------------------------------------------
		
		// Tendremos un conjunto de elementos para poder levantar el server y poder comenzar a escuchar por un determinado puerto con la
		// configuracion como socket normal o como web socket de la siguiente forma.
		
		// -----------------------------------------------------------------------------
		
		// Definiremos el siguiente metodo para poder realiar una nueva coneccion a otro endPoint.
		
		bool Listen (int currentPort , bool webSocket = true);
		
		// Para redirigir el host a otra URL tenemos lo siguiente de esta forma.
		
		bool Redirect (const std::string & currentURL);
		
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
		
		// Ahora para poder cerrar el servidor tenemos otro metodo.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							CLOSING CURRENT SERVER
		// 							
		// -----------------------------------------------------------------------------
		
		// Definiremos nuestro metodo close de la siguiente forma.
		
		void Close ();
		
		// Ahora por ultimodefiniremos nuestro respectivo destructor.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							CURRENT DESTRUCTOR
		// 							
		// -----------------------------------------------------------------------------
		
		// Implementaremos el siguiente elemento para que sea nuestro destructor.
		
		~WebSocketServer ();
		
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

CYTTEK_API std::string GetCurrentIP ();

// -----------------------------------------------------------------------------

// Para finalizar nuestro web socket tenemos lo siguiente.

#endif // CYTTEK_WEBSOCKET_SERVER

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
