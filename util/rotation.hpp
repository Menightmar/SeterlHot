
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																	ROTATION OF FILES UTILITY
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// El siguiente es un codigo para poder establecer y programar la rotación y temporización de archivos en nuestros sistemas con la finalidad de que se permitan
// respaldar y asu vez evitar el crecimiento de archivos de datos secuencialmente y permitir moverlos o borrarlos cada cierto tiempo.

#pragma once

// Ahora definiremos lo siguiente para poder trabajar con nuestro archivo de encabezado de la siguiente forma.

#ifndef ROTATION_UTILITY_HPP
#define ROTATION_UTILITY_HPP

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

// Ahora pasaremos a definir la interfaz para la rotacion de elementos programada mediante el uso de metodos respectivos.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		ROTATION INTERFAZ
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Declaramos la interfaz de la rotación de nuestros archivos para poder establecer la información necesario y el mecanismo para poder realizar el cambio
// de archivo desde un origen a un destino especificado.

// -----------------------------------------------------------------------------

// Definiremos la siguiente interfaz auxiliar que permitirá seleccionar los metodos necesarios para iniciar el rotado de archivos de forma que no afecte.

class Rotable {
	
	// Tenemos los siguientes elementos publicos de la siguiente forma.
	
	// -----------------------------------------------------------------------------
	// 
	// 							ELEMENTOS PUBLICOS
	// 							
	// -----------------------------------------------------------------------------
	
	// Ahora para definir la interfaz tendremos que colocar primero los metodos que necesitaremos de forma publica para este caso.
	
	public :
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							COMPORTAMIENTOS PUBLICOS
		// 							
		// -----------------------------------------------------------------------------
		
		// Tenemos el siguiente metodo para copiar desde un punto inicial hasta un punto final de la siguiente forma.
		
		virtual bool CopyElement (const std::string & origin , const std::string & target) = 0;
		
		// Tenemos el siguiente metodo para poder mover un archivo de un inicio a un fin de la siguiente forma.
		
		virtual bool MoveElement (const std::string & origin , const std::string & target) = 0;
		
		// Finalmente para poder eliminar un elemento tenemos lo siguiente.
		
		virtual bool DeleteElement (const std::string & origin) = 0;
		
		// -----------------------------------------------------------------------------
	
};

// Ahora definiremos nuestra interfaz para poder construir nuestra rotacion de archivos por default.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							IMPLEMENT ROTATION FILES
// 							
// -----------------------------------------------------------------------------

// Crearemos una clase encargada del desplazamiento de archivos con los elementos de rotacion que se definen en la interfaz.

class CYTTEK_API FilesRotation : public Rotable {
	
	// Tenemos los siguientes elementos publicos de la siguiente forma.
	
	// -----------------------------------------------------------------------------
	// 
	// 							ELEMENTOS PUBLICOS
	// 							
	// -----------------------------------------------------------------------------
	
	// Tenemos la siguiente información.
	
	public :
	
		// Definiremos todos los metodo publicos que tiene nuestra interfaz para darles las funciones de la rotacion de archivos.
	
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							ROTATING FILES
		// 							
		// -----------------------------------------------------------------------------
		
		// Definiremos los siguientes metodos para poder realizar la rotación de nuestros archivos con base en nuestro algoritmo de desplazamiento
		// de la siguiente forma.
		
		// -----------------------------------------------------------------------------
		
		// Definiremos el metodo para poder copiar elemento de un lugar a otro.
		
		virtual bool CopyElement (const std::string & origin , const std::string & target) override;
			
		// Tenemos el siguiente metodo para poder mover un archivo de un inicio a un fin de la siguiente forma.

		virtual bool MoveElement (const std::string & origin , const std::string & target) override;

		// Finalmente para poder eliminar un elemento tenemos lo siguiente.

		virtual bool DeleteElement (const std::string & origin) override;
		
		// -----------------------------------------------------------------------------
		
	// -----------------------------------------------------------------------------
	
};

// Ahora crearemos una clase para poder coordinar asi mismo un respectivo logger al momento de tener que rotar de la siguiente forma.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							LOGGER ROTATION CLASS
// 							
// -----------------------------------------------------------------------------

// Definiremos una clase para poder establecer la clase necesitaremos derivar de Rotable e implementar los metodos virtual para poder hacer la rotacion
// de forma correcta.

class CYTTEK_API LoggerRotation : public Rotable {
	
	// Definiremos los siguientes elementos publicos de la siguiente forma.
	
	// -----------------------------------------------------------------------------
	// 
	// 							ELEMENTOS PUBLICOS
	// 							
	// -----------------------------------------------------------------------------
	
	// Tenemos la siguiente información.
	
	public :
	
		// Implementaremos todo los metodos para poder establecer la información respectiva.
	
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							ROTATING LOGGER
		// 							
		// -----------------------------------------------------------------------------
		
		// Definiremos los siguientes metodos para poder realizar la rotación de logs mediante el uso de los mutex para bloquear los hilos que sigan
		// escribiendo en los logs actualmente.
		
		// -----------------------------------------------------------------------------
		
		// Definiremos el metodo para poder copiar elemento de un lugar a otro.
		
		virtual bool CopyElement (const std::string & origin , const std::string & target) override;
			
		// Tenemos el siguiente metodo para poder mover un archivo de un inicio a un fin de la siguiente forma.

		virtual bool MoveElement (const std::string & origin , const std::string & target) override;

		// Finalmente para poder eliminar un elemento tenemos lo siguiente.

		virtual bool DeleteElement (const std::string & origin) override;
		
		// -----------------------------------------------------------------------------
		
	// -----------------------------------------------------------------------------
	
};

// Ahora pasaremos a nuestro contenido para nuestra clase para poder realizar los respaldos de archivos con la información necesaria.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		ROTATION CLASS DECLARATION
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Ahora para lo siguient tenemos que definir la clase siguiente para establecer los elementos que estaremos utilizando para realizar el respaldo en todo
// momento mientras los archivos se realizan en respaldo y se rotan para el tiempo indicado.

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// 
// 							CLASE ROTATION
// 							
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// Ahora definiremos lo que será la clase especializada para el respaldo de archivos y generacion de respaldos de la siguiente manera.

class CYTTEK_API Rotation {
	
	// Declaramos la clase siguiente con todos los elementos necesarios.
	
	// -----------------------------------------------------------------------------
	// 
	// 							ROTATION CLASS ELEMENTOS
	// 							
	// -----------------------------------------------------------------------------
	
	// Tenemos nuestros siguientes elementos privados a utilizar.
	
	private :
	
		// Declaramos los atributos para nuestra clase que necesitaremos par poder crear el listado de archivos a respaldar , el alias para la salida de
		// respaldo a crear y por ende nuestro timer para poder saber si el archivo ya está listo para borrar o si todavía no tenemos salida.
		
		// -----------------------------------------------------------------------------
		
		// Crearemos una asociación para desplazar archivos usando diferentes tipos de rotaciones.
		
		using TRotationMode = std::pair <std::string , std::shared_ptr <Rotable>>;
		
		// Tenemos lo siguiente que es el listado de nuestros archivos (filenames) que estaremos usando para poder gestionar con el limitador de
		// tiempo respectivo.
		
		std::vector <TRotationMode> currentFiles;
		
		// Necesitaremos también saber el key donde se estará guardando el registro de rotacion de nuestro programa.
		
		std::string currentKey;
		
		// Neceesitaremos saber el suffijo que tomará nuestro log cada vez que va rotando.
		
		std::string currentSuffix;
		
		// Ahora para poder asignar el tiempo , constituido por la fecha diaria necesitaremos controlarlo mediante un chrono duration.
		
		std::chrono::seconds currentDateRotate;
		
		// Ahora para determinar el tiempo que será la fecha en la que se borre el respaldo del archivo necesitaremos otro tiempo.
		
		std::chrono::seconds currentDateDelete;
		
		// Ahora para poder validar si ya está inicializado nuestro clock timer.
		
		std::atomic <bool> isInit;
		
		// Ahora para validar si ya ha sido rotado pero todavia falta de eliminar los respaldos tendremos lo siguiente.
		
		std::atomic <bool> isRotated;
		
		// Ahora para saber si los archivos ya han sido borrados por lo menos una vez tenemos lo siguiente.
		
		std::atomic <bool> isDeleted;
		
		// Ahora los datos para saber perfectamente cuantos archivos van a cortarse y si está habilitado o no este mecanismo.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							LOG CUTTER SETTINGS
		// 							
		// -----------------------------------------------------------------------------
		
		// Primero necesitaremos nuestro valor que define si está en modo cutter o no.
		
		std::atomic <bool> cutterEnable;
		
		// Ahora el valor que determina cuantos cachos van a cortarse los logs.
		
		std::atomic <int> cutterCount;
		
		// Para poder saber en que parte estamos actualmente tenemos lo siguiente.
		
		std::atomic <int> cutterIndex;
		
		// Ahora crearemos algunas funciones y metodos auxiliares para poder usarlo.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							AUX METHODS FOR THIS
		// 							
		// -----------------------------------------------------------------------------
		
		// Crearemos un metodo que guarda el registro con el tiempo actual que tenemos y permite tomar salida de cuando debe borrarse el proximo rotado
		// de archivos y cuando deben borrarse los de respaldo.
		
		void SaveDateRotateRegister (const std::chrono::seconds & currentTimer = 
			std::chrono::duration_cast <std::chrono::seconds> (std::chrono::system_clock::now ().time_since_epoch ()));
		
		// Ahora para poder establecer el registro de eliminacion tenemos el siguiente.
		
		void SaveDateDeleteRegister (const std::chrono::seconds & currentOrigin);
		
		// Ahora para poder extraer los registros y obtener el respectivo tiempo actual a cual comparar tenemos el siguiente metodo.
		
		std::chrono::seconds ExtractSaveDateRotate ();
		
		// De igual forma para poder extraer el tiempo de eliminacion dependiendo los registros tenemos este otro.
		
		std::chrono::seconds ExtractSaveDateDelete ();
		
		// Asu vez para poder realizar el rotado de nuestros archivos necesitaremos usar una funcion que haga dicho proceso.
		
		void RotateFiles ();
		
		// Para borrar los archivos que estén en los respaldos necesitareos el siguient emetodo.
		
		void DeleteFiles ();
		
		// Ahora pasaremos adefinir los siguientes elemnentos.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							CONSTRUCTORES
		// 							
		// -----------------------------------------------------------------------------
		
		// Tendremos el sigueinte constructor para poder crear nuestro elemento de rotacion y poder configurarlo a nuestra manera de la siguiente forma.
		
		Rotation (Configuration & currentConfig);
		
		// -----------------------------------------------------------------------------
	
	// Ahora pasaremos a los metodos publicos para poder crear la clase y configurar dichos valores que necesitaremos.
	
	// -----------------------------------------------------------------------------
	// 
	// 							METODOS PUBLICOS Y SETTERS
	// 							
	// -----------------------------------------------------------------------------
	
	// Definiremos lo siguientes elementos publicos para nuestra clase.
	
	public :
		
		// Comenzaremos por el respectivo metodo constructor que realiza la tarea de poder establecer la construccion de nuestro objeto rotador para
		// crear todos los elementos que dependen del mismo y configurarlo adecuadamente.
		
		// -----------------------------------------------------------------------------
		// 
		// 							BUILD INSTANCE SINGLETON
		// 							
		// -----------------------------------------------------------------------------
		
		// Declaramos nuerstgro metodo para poder construir el objeto y obtener la instancia respectiva de enuestro objeto de rotador.
		
		static Rotation & GetInstanceFromConfig (Configuration & currentConfig);
		
		// Ahora los getters and setters para poder configurar el rotador de archivos de la siguiente forma.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							GETTERS AND SETTERS
		// 							
		// -----------------------------------------------------------------------------
		
		// Tenemos primero el siguiente metodo para poder validar si es valido o no el rotador.
		
		ALWAYS_INLINE bool IsValid () const {
			
			// Devolveremos el estado actual.
			
			return (!currentFiles.empty () && isInit.load ());
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Para revisar si el estado de rotacion es valido tenemos lo siguiente.
		
		ALWAYS_INLINE bool IsRotated () const {
			
			// Devolveremos lo siguiente.
			
			return isRotated.load ();
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Para revisar si el estado de eliminacion es valido tenemos lo siguiente.
		
		ALWAYS_INLINE bool IsDeleted () const {
			
			// Devolveremos lo siguiente.
			
			return isDeleted.load ();
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora tenedremos que pasar a la parte de nuestros elementos para poder configurar como el tiempo para rotar , la fecha de eliminacion y poder
		// establecer todos los datos necesarios para dicho proceso mediante el uso de templates de duracion respectiva que habría que usar a la fecha
		// por defecto.
		
		template <typename TDuration>
		requires requires (TDuration currentTime) {
			
			// Debe ser un tipo que al sumar con el elemento pueda compilar.
			
			(currentDateRotate + currentTime);
			
			// -----------------------------------------------------------------------------
			
		}
		void AddDateRotation (const TDuration & currentTime) {
			
			// Anexaremos el tiempo actual a la fecha actual para la rotacion en estos momentos.
			
			currentDateRotate = std::chrono::duration_cast <decltype (currentDateRotate)> (currentDateRotate + currentTime);
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para resetear nuestra duracion tendremos lo siguiente.
		
		void ResetDateRotation ();
		
		// Ahora par poder realizar lo mismo pero con el timpo de finalizacion de nuestro respaldo sobre el tiempo de rotacion tendremos lo siguiente.
		
		template <typename TDuration>
		requires requires (TDuration currentTime) {
			
			// Debe ser un tipo que al sumar con el elemento pueda compilar.
			
			(currentDateRotate + currentTime);
			
			// -----------------------------------------------------------------------------
			
		}
		void AddDateDelete (const TDuration & currentTime) {
			
			// Anexaremos el tiempo actual a la fecha actual para la rotacion en estos momentos.
			
			currentDateDelete = std::chrono::duration_cast <decltype (currentDateDelete)> (currentDateDelete + currentTime);
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Ahora para resetear nuestra duracion tendremos lo siguiente.
		
		void ResetDateDelete ();
		
		// Ahora para poder establecer la clave del registro de windows donde guardaremos nuestro respectivo elemento tendremos el siguiente metodo.
		
		void SetRegisterKey (const std::string & saveRegisterKey);
		
		// Ahora para poder gestionar nuestros archivos que vamos a rotar tenemos lo siguiiente.
		
		// -----------------------------------------------------------------------------
		// 
		// 							ROTATING FILES MANAGER
		// 							
		// -----------------------------------------------------------------------------
		
		// Ahora para poder anexar un archivo a nuestro listado de archivos de respaldo.
		
		void AddFile (const std::string & currentFile);
		
		// Ahora para anexar un determinado archivo y su respectivo elemento de rotacion tenemos lo siguiente.
		
		void AddElement (const std::string & currentFile , const std::shared_ptr <Rotable> currentRotable);
		
		// Para poder eliminar algún archivo en particular en la lista tenemos lo siguiente.
		
		void RemoveFile (const std::string & currentFile);
		
		// Ahora para poder limpiar toda la lista tenemos lo siguiente.
		
		void ClearFiles ();
		
		// Pasaremos a los metodos respectivos para poder rotar y borrar segun sea el caso.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							CHECK ROTATION
		// 							
		// -----------------------------------------------------------------------------
		
		// Primero inicializaremos nuestro timer de rotacion en cuanto se invoque nuestro metodo siguiente.
		
		void InitRotation ();
		
		// Tendremos lo siguiente para poder chekar nuestros archivos de rotacion respectivos y poder operar lo que sea necesario de acuerdo a la hora actual.
		
		bool CheckRotation ();
		
		// Ahora para poder borrar los archivos temporales hay que revisar la eliminacion por aparte.
		
		bool CheckDeletion ();
		
		// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	
};

// -----------------------------------------------------------------------------

// Ahora finalmente terminaremos la declaración de nuestro archivo de cabecera de la siguietne dorma.

#endif // ROTATION_UTILITY_HPP

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
