
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																	MODULO DE REGISTROS WINDOWS PARA CYTTEK
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

/// @author José Raúl Moreno Acero
/// @date 14/05/2024
/// @brief Archivo con todas las funciones , clases , variables , etc; Para poder gestionar todo sobre los registros del sistema windows , mediante el uso de
/// la api de winreg en el sistema operativo conforme lo establecido.
/// @details
/// 
/// Los registros de windows es una pequeña base de datos almacenada que contiene claves - valores para gestionar información sobre el sistema operativo y todos
/// los programas que quieren guardar configuraciones asi como valores que pueden ser importantes para los aplicativos como sus versiones y elementos adicionales.
/// 

// Definiremos lo siguiente para poder guardar el archivo de encabezado.

#pragma once

// Definiremos la macro guard para poder asegurar que no se repita nuestro codigo.

#ifndef CYTTEK_REGISTER
#define CYTTEK_REGISTER

// Incluiremos las bases para poder comenzar y poder iniciar a realizar la lectura 

// -----------------------------------------------------------------------------

// Incluiremos los elementos base para los printf , scant , cin y cout para pintar sobre la salida estandar de nuestro aplicativo.

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Incluiremos nuestro modulo Core para poder establecer comunicación con lo necesario para implementar lo que necesitamos.

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

// Ahora una inclusión para los winreg de windows de la siguiente forma.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							WINDOWS REGISTERS
// 							
// -----------------------------------------------------------------------------

// Incluiremos la siguiente cabecera para poder hacer uso de las funciones necesarias.

#include <winreg.h>

// Ahora pasaremos a la parter de la definición de las funciones para la manipulación de registros.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		REGISTER WINDOWS MANAGER
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Para poder pintar en los registros requerimos manejar el regedit de windows y establecer diferentes tipos de opciones viables mediante templates para
// poder reutilizar todo el codigo necesario.

// -----------------------------------------------------------------------------

// Para poderlo lograr tenemos que tener en cuenta lo siguiente.

// -----------------------------------------------------------------------------
// 
// 							ALIAS DE TIPOS ENTRE REGISTROS
// 							
// -----------------------------------------------------------------------------

// Para poder realizar la meta en este caso necesitamos mapear los tipos de datos de registros de windos a tipos de datos de variables para poder asociar
// unos con otros y poder hacer las conversiones necesarias.

// -----------------------------------------------------------------------------

// Crearemos un pequeño alias para el tipo de dato que se está tratando internamente y poder con esto definir el tipo de dato asociado al registro
// que debemos de tomar en cuenta.

template <typename TValue>
struct RegisterTypeAlias {
	
	// -----------------------------------------------------------------------------
	
	// Definiremos el alias para el tipo de dato que se está tratando internamente.
	
	typedef TValue value_type;
	
	// El valor tendrá el siguiente por defecto.
	
	static constexpr unsigned long long int value = REG_NONE;
	
	// -----------------------------------------------------------------------------
			
};

// Ahora pasaremos con las especializacionesa de esta plantilla para poder asociar los diferentes tipos de datos respectivos a cada dato en común que
// se comparta en estos momentos.

template <>
struct RegisterTypeAlias <WORD> : 						std::integral_constant <unsigned long int , REG_DWORD> { /* Implementado */ };

// -----------------------------------------------------------------------------

// De igual forma pero para el caso del DWORD tenemos lo siguiente de esta forma.

template <>
struct RegisterTypeAlias <DWORD> : 						std::integral_constant <unsigned long int , REG_DWORD> { /* Implementado */ };

// -----------------------------------------------------------------------------

// Tenemos el caso para el valor de tipo BOOL.

template <>
struct RegisterTypeAlias <BOOL> : 						std::integral_constant <unsigned long int , REG_DWORD> { /* Implementado */ };

// -----------------------------------------------------------------------------

// Tenemos el caso para el valor de tipo integral menor de 4 bytes.

template <typename TValue>
requires std::is_integral_v <TValue>
struct RegisterTypeAlias <TValue> :						std::integral_constant <unsigned long int , REG_DWORD> { /* Implementado */ };

// -----------------------------------------------------------------------------

// Ahora para poder establecer el valor con un QWORD requerimos que la cantidad de bytes de la variable sea 64 y de tipo integral.

template <typename TValue>
requires ((sizeof (TValue) == sizeof (uint64_t)) and std::is_integral_v <TValue>)
struct RegisterTypeAlias <TValue> : 					std::integral_constant <unsigned long int , REG_QWORD> { /* Implementado */ };

// -----------------------------------------------------------------------------

// Para poder valiodar que un tipo es un std::string tendremos el siguiente para asociarlo con el tipo REG_SZ.

template <>
struct RegisterTypeAlias <std::string> : 				std::integral_constant <unsigned long int , REG_SZ> { /* Implementado */ };

// -----------------------------------------------------------------------------

// Para poder valiodar que un tipo de dato es un CHAR array o un LPSTR.

template <>
struct RegisterTypeAlias <LPSTR> : 						std::integral_constant <unsigned long int , REG_SZ> { /* Implementado */ };

// -----------------------------------------------------------------------------

// Para poder asociar los tipos binarios necesitamos de un respectivo valor de size para este caso y un array.

template <typename TValue>
struct RegisterTypeAlias <TValue *> : 					std::integral_constant <unsigned long int , REG_BINARY> { /* Implementado */ };

// -----------------------------------------------------------------------------

// Ahora para el caso de los diferentes tipos de contenedores tendremos el siguiente  alias para poder asociarlo al tipo REG_MULTI_SZ.

template <template <typename ...> typename TTemplate , typename ... TValues>
requires IsValidContainer <TTemplate , TValues ...> and (not std::is_same_v <TTemplate <TValues ...> , std::string>)
struct RegisterTypeAlias <TTemplate <TValues ...>> : 	std::integral_constant <unsigned long int , REG_MULTI_SZ> {
	
	// -----------------------------------------------------------------------------
	
	// Definiremos el administrador de continainer interno.
	
	typedef AlterContainer <TTemplate , TValues ...> alter_container_type;
	
	// -----------------------------------------------------------------------------
	
};

// Ahora definiremos algunos conceptos

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							CONCEPTS FOR TEMPLATES
// 							
// -----------------------------------------------------------------------------

// Crearemos un concept para poder validar que el tipo de dato que se está enviando es compatible con algún tipo de alias en especifico.

template <typename TValue>
concept TRegister = (RegisterTypeAlias <TValue>::value != REG_NONE);

// Ahora pasaremos a la parte de las funciones relacionadas con la manipulacin de registros mediante las funciones que tenemos.

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// 
// 							REGISTER MANAGER
// 							
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// Primero tenemos lo siguiente para poder validar que un determinado registros eexisten.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							VALIDACION DE REGISTROS
// 							
// -----------------------------------------------------------------------------

// Para validar que un determinado key de registro existe tenemos lo siguiente.

template <typename TSubKey>
bool RegisterExists (HKEY parentKey , const TSubKey * subKey) {
	
	// -----------------------------------------------------------------------------
	
	// Realizaremos la apertura de la nueva llave para poder guardar lo que necesitamos.
	
	HKEY keyResult = 0;
	
	// Asignaremos el valor siguiente.
	
	const bool result = (RegOpenKeyExA (parentKey , subKey , 0 , KEY_READ , &keyResult) == ERROR_SUCCESS);
	
	// Validamos si cerrar nuestro handle.
	
	if (result && keyResult) RegCloseKey (keyResult);
	
	// Realizaremos el cierre del mismo.
	
	return result;
	
	// -----------------------------------------------------------------------------
	
}

// Asi mismo tendremos otro concepto auxiliar que permite determinar si un valor de tipo puntero es compatible con la conversión a LPSTR.

// -----------------------------------------------------------------------------
// 
// 							APERTURA DE REGISTROS
// 							
// -----------------------------------------------------------------------------

// Lo primero que debemos realizar es la apertura de un registro , para esto se tiene la siguiente funcionalidad que permite realizarlo y solamente hay
// que especificarle 

template <typename TSubKey>
HKEY RegisterOpenKey (HKEY parentKey , const TSubKey * subKey , REGSAM options) {
	
	// -----------------------------------------------------------------------------
	
	// Realizaremos la apertura de la nueva llave para poder guardar lo que necesitamos.
	
	HKEY keyResult = 0;
	
	// Ahora vamos a realizar la apertura primero realizando la funcionalidad siguiente.
	
	if (RegOpenKeyExA (parentKey , subKey , 0 , options , &keyResult) != ERROR_SUCCESS) {
		
		// -----------------------------------------------------------------------------
		
		// Lanzaremos una excepcion que lo valide todo.
		
		throw std::runtime_error (StringPrintf ("Error al abrir llave : %s " , subKey));
		
		// -----------------------------------------------------------------------------
		
	}
	
	// Devolveremos finalmente la llave resultante keyResult.
	
	return keyResult;
	
	// -----------------------------------------------------------------------------
	
}

// Para poder realizar la creación de nuevos registros tendremos la siguiente template.

// -----------------------------------------------------------------------------
// 
// 							CREACION DE REGISTROS
// 							
// -----------------------------------------------------------------------------

// Tenemos lo siguiente que es la parte de realizar la creación de nuestro nuevo registro.

// -----------------------------------------------------------------------------

// Para poder leer un registro necesitamos de algunas funciones que nos den todo el soporte para poderlo lograr.

template <typename TSubKey>
bool RegisterCreateKey (HKEY parentKey , const TSubKey * subKey , PHKEY resultKey = NULL) {
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							CREANDO NUEVA LLAVE
	// 							
	// -----------------------------------------------------------------------------
	
	// Realizaremos la creación de nuestro nuevo registro de la siguiente manera para poder establecer la información que necesitemos.
	
	// -----------------------------------------------------------------------------
	
	// Estableceremos una variable temporal de salida.
	
	HKEY keyResult;
	
	// Asignaremos la memoria ya sea de esta o la variable establecida en el parametro para poder asignar.
	
	PHKEY currentKeyOutput = (resultKey ? resultKey : &keyResult);
	
	// Ahora crearemos el registro con la función especifica RegCreateKeyExA de windows.h.
	// Estableceremos el modo de acceso para ALL_ACCESS asi como WOW64 para compatibilidad con sistemas de 64 bits.
	
	if (RegCreateKeyExA (parentKey , subKey , 0 , NULL , REG_OPTION_NON_VOLATILE , (KEY_ALL_ACCESS | KEY_WOW64_32KEY) , NULL ,
	                     currentKeyOutput , NULL) != ERROR_SUCCESS) {
		
		// -----------------------------------------------------------------------------
		
		// Un error ha ocurrido por lo que tendremos que realizar el informe.
		
		throw std::runtime_error (StringPrintf ("Error al crear Llave para subkey [%s] " , subKey));
		
		// -----------------------------------------------------------------------------
		
	}
	
	// Finalmente y si el resultado es diferente a null entonces cerraremos la llave.
	
	if (currentKeyOutput) RegCloseKey (*currentKeyOutput);
	
	// Finalmente devolveremos true.
	
	return true;
	
	// -----------------------------------------------------------------------------
	
}

// Para establecer los valores en los registros tendremos alguna función de template.

// -----------------------------------------------------------------------------
// 
// 							SET REGISTER VALUES
// 							
// -----------------------------------------------------------------------------

// Definiremos una función template para poder asignar un respectivo valor que a un determinado registro y poderlo establecer.

template <TRegister TData , typename TSubKey , typename TValue>
bool RegisterSetValue (HKEY parentKey , const TSubKey * subKey , const TValue * value , const TData & data , const bool keyOpened = false) {
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							GUARDANDO VALORES EN REGISTRO
	// 							
	// -----------------------------------------------------------------------------
	
	// Para guardar el valor necesitaremos de crear un alias para el tipo de dato interno que ocuparemos actualmente.
	
	using TRegisterAlias = RegisterTypeAlias <std::decay_t <TData>>;
	
	// Asignaremos un status por default en invalido.
		
	LSTATUS currentResult = ERROR_INVALID_FUNCTION;
	
	// Ahora vamos a realizar la asignación del valor respectivo.
	
	try {
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							OBTENIENDO VALOR REGISTROS
		// 							
		// -----------------------------------------------------------------------------
		
		// Pasaremos primero a abrir nuestro respectivo registro utilizando los datos del parrent key , el sub key.
		// Si la llave que se proporciona como parent está actualmente abierta con el parametro keyOpened en true entonces no realizaremos
		// la apertura de la nueva sub-llave.
		
		const auto currentOpenedKey = (keyOpened ? parentKey : RegisterOpenKey (parentKey , subKey , KEY_SET_VALUE));
		
		// Asignaremos un valor de datos en la direccion de los datos por default.
		
		const BYTE * currentData = reinterpret_cast <const BYTE *> (std::addressof (data));
		
		// Ahora un tamaño de datos en el tamaño de la variable por default.
		
		DWORD currentDataSize = sizeof (TData);
		
		// Tendremos el output general para poder establecer datos temporales.
		
		std::string output;
		
		// Validaremos si el tipo es un Multi ZString.
		
		if constexpr (TRegisterAlias::value == REG_MULTI_SZ) {
			
			// -----------------------------------------------------------------------------
			
			// Destokenizaremos los elementos del vector y lo separamos con un espacio.
			
			output = std::move (data <DTokens <std::vector>> '\0');
			
			// Asignaremos los datos respectivos.
			
			currentData = reinterpret_cast <const BYTE *> (output.c_str ());
			
			// Ahora vamos a realizar la asignación de nuestro tamaño con 2 por los terminadores null.
			
			currentDataSize = (output.size () + 2);
			
			// -----------------------------------------------------------------------------
			
		}
		else if constexpr (TRegisterAlias::value == REG_SZ) {
			
			// -----------------------------------------------------------------------------
			
			// Ahora asignaremos el valor respectivo de los datos de la cadena.
			
			if constexpr (std::is_same_v <std::string , std::decay_t <TData>>) {
				
				// Asignaremos lo siguiente.
				
				currentData = reinterpret_cast <const BYTE *> (data.c_str ());
				
				// Para el tamaño tenemos lo siguiente.
				
				currentDataSize = (data.size () + 1);
				
				// -----------------------------------------------------------------------------
				
			}
			else if constexpr (std::is_same_v <LPSTR , std::decay_t <TData>>) {
				
				// Conformaremos un ajuste para hacer un ajuste a nuestros valores que son terminados en NULL y el ultimo en dos null mediante espacios.
				
				std::string currentOutput;
				
				// Realizaremos la iteración por los datos.
				
				// -----------------------------------------------------------------------------
				
				// -----------------------------------------------------------------------------
				// 
				// 							ITERATION FOR LPSTR
				// 							
				// -----------------------------------------------------------------------------
				
				// Definiremos el size limite de la siguiente forma.
				
				constexpr size_t bufferLimit = 1024u;
				
				// Realizaremos la valiidacion de punteero y posteriormente vvalidacion de iteración de todo el elemento de la siguiente forma.
				
				if (const auto bufferSizeLimit = ValidatePTR (data)) {
					
					// Determinaremos el resultado de validacion y sacaremos el limite maximo de letras a leer permitidas.
					
					const size_t indexLimit = std::min (bufferLimit , bufferSizeLimit);
					
					// Reservaremos ese espacio.
					
					currentOutput.reserve (indexLimit + 1u);
					
					// Ahora iteramos por sobree el array de elementos y comparamos hasta acabar con el string.
					
					for (size_t index = 0u ; ((index < indexLimit) && ((data [index] != '\0') || (data [index + 1u] != '\0'))) ; ++ index) {
						
						// Ahora la validacion respectiva para el caracter respectivo que tenemos.
						
						char currentCaracter = data [index];
						
						// Si el caracter es un terminador , que lo sustituya por un espacio.
						
						if (currentCaracter == '\0') currentCaracter = ' ';
						
						// Asignaremos el siguiente caracter a la salida temporal.
						
						if (isprint (currentCaracter) || isspace (currentCaracter)) currentOutput += currentCaracter;
						
						// -----------------------------------------------------------------------------
						
					}
					
					// -----------------------------------------------------------------------------
					
				}
				
				// Asignaremos el resultado a nuestro output temporal.
				
				output = std::move (currentOutput);
				
				// Ahora asignaremos el valor respectivo.
				
				currentData = reinterpret_cast <const BYTE *> (output.c_str ());
				
				// Ahora vamos a realizar la asignación de nuestro tamaño con 2 por los terminadores null.
				
				currentDataSize = (output.size () + 1);
				
				// -----------------------------------------------------------------------------
				
			}
			
			// -----------------------------------------------------------------------------
			
		}
		else if constexpr (TRegisterAlias::value == REG_BINARY) {
			
			// Asignaremos el valor de data directamente.
			
			currentData = reinterpret_cast <const BYTE *> (data);
			
			// Asignaremos el tamaño de la variable a la que apunta y no al puntero.
			
			currentDataSize = sizeof (std::remove_pointer_t <TData>);
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
		
		// Asignaremos el valor resultante de la siguiente forma.
		
		currentResult = RegSetValueExA (currentOpenedKey , value , 0 , TRegisterAlias::value , currentData , currentDataSize);
		
		// Finalmente cerraremos el registro.
		
		if (!keyOpened) RegCloseKey (currentOpenedKey);
		
		// -----------------------------------------------------------------------------
		
	}
	catch (const std::exception & error) {
		
		// -----------------------------------------------------------------------------
		
		// Devolveremos el error.
		
		return false;
		
		// -----------------------------------------------------------------------------
		
	}
	
	// Finalmente devolveremos true si fue exitoso.
	
	return (currentResult == ERROR_SUCCESS);
	
	// -----------------------------------------------------------------------------
	
}

// Ahora para la consulta de los registros tendremos el siguiente template.

// -----------------------------------------------------------------------------
// 
// 							LECTURA DE REGISTROS
// 							
// -----------------------------------------------------------------------------

// Tenemos la consulta de valores de registros con lo siguiente.

// -----------------------------------------------------------------------------

// Ahora vamos a realizar la función para la lectura de nuestro respectivo registro y poder devolver el tipo de valor que requiere , para esto
// necesitamos establecer lo siguiente.

// Validaremos que el tipo de retorno seleccionado sea un alias para un tipo de dato asociado con un tipo de registro en windows.

template <TRegister RType , typename TSubKey , typename TValue>
RType RegisterGetValue (HKEY parentKey , const TSubKey * subKey , const TValue * value , LPDWORD typeOutput = NULL) {
	
	// -----------------------------------------------------------------------------
	
	// Crearemos la salida en el siguiente valor temporal.
	
	RType result;
	
	// Tenemos el valor de resultado por default de la siguiente forma.
	
	try {
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							OBTENIENDO VALOR REGISTROS
		// 							
		// -----------------------------------------------------------------------------
		
		// Para poder determinar el registro del cuál queremos recuperar el valor primero vamos a abrir la llave y poder determinar el resultado.
		
		const auto currentOpenedKey = RegisterOpenKey (parentKey , subKey , KEY_QUERY_VALUE);
		
		// Ahora pasaremos a realizar la asignación del tamaño de nuestra variable de salida en bytes para poder informar a la función.
		
		DWORD resultSize = sizeof (result);
		
		// Para poder determinar si el tipo de dato alias es para un REG_SZ o MULTI_SZ entonces tendremos lo siguiente.
		
		if constexpr ((RegisterTypeAlias <RType>::value == REG_SZ) or (RegisterTypeAlias <RType>::value == REG_MULTI_SZ)) {
			
			// Crearemos un pequeño buffer de salida para almacenar los datos.
			
			char bufferResult [1024 * 1024] = { '\0' };
			
			// Asignaremos el tamaño de buffer.
			
			resultSize = sizeof (bufferResult);
			
			// Limpiaremos el buffer.
			
			memset (bufferResult , '\0' , resultSize);
			
			// Ahora asignaremos el valor de la consulta.
			
			RegGetValueA (currentOpenedKey , NULL , value , RRF_RT_ANY , typeOutput , bufferResult , &resultSize);
			
			// Ahora para asignar el resultado tenemos lo siguiente.
			
			if constexpr (RegisterTypeAlias <RType>::value == REG_MULTI_SZ) {
				
				// Asignaremos el valor tokenizado al resultado quitando los elementos '\0' de la derecha y 2 ultimos para poder
				// tener la cadena limpia en estos momentos.
				
				result = (std::string (bufferResult , (resultSize - 2)) <RTrim> "\0" <STokens <std::vector>> '\0');
				
				// -----------------------------------------------------------------------------
				
			}
			else {
				
				// Asignaremos el valor del buffer.
				
				result = std::move (std::string (bufferResult));
				
				// -----------------------------------------------------------------------------
				
			}
			
			// -----------------------------------------------------------------------------
			
		}
		else {
			
			// Ahora vamos a realizar la asignación de nuestro respectivo valor con los parametros especificos.
			
			RegGetValueA (currentOpenedKey , NULL , value , RRF_RT_ANY , typeOutput , &result , &resultSize);
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Finalmente cerraremos el registro.
		
		RegCloseKey (currentOpenedKey);
		
		// -----------------------------------------------------------------------------
		
	}
	catch (const std::exception & error) {
		
		/* Deteccion de errores */
		
		// -----------------------------------------------------------------------------
		
	}
	
	// -----------------------------------------------------------------------------
	
	// Devolveremos el valor que tenemos en estos momentos.
	
	return result;
	
}

// Ahora para poder borrar un registro tendremos el siguiente elemento.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							BORRAR REGISTRO WINDOWS
// 							
// -----------------------------------------------------------------------------

// Tenemos por otro lado este template que se encarga de realizar el borrado de un determinado registro de windows de la siguiente forma.

template <typename TSubKey>
ALWAYS_INLINE bool RegisterDeleteKey (HKEY parentKey , const TSubKey * subKey , bool recursive = false) {
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							BORRANDO CLAVE ACTUAL.
	// 							
	// -----------------------------------------------------------------------------
	
	// Tendremos dos macro defs para definir un valor a establecer.
	
	#ifdef _WIN64
	
	// Establecemos la flag de la siguiente forma.
	
	constexpr REGSAM currentFlag = KEY_WOW64_64KEY;
	
	// -----------------------------------------------------------------------------
	
	#else
	
	// Definiremos la bandera con wow32.
	
	constexpr REGSAM currentFlag = KEY_WOW64_32KEY;
	
	// -----------------------------------------------------------------------------
	
	#endif
	
	// Para este caso bastará simplemente con llamar a la siguiente función y validar que la llave esté válidada para poder eliminarlo.
	
	return ((recursive ? RegDeleteTreeA (parentKey , subKey) : RegDeleteKeyExA (parentKey , subKey , currentFlag , 0)) == ERROR_SUCCESS);
	
	// -----------------------------------------------------------------------------
	
}

// -----------------------------------------------------------------------------

// Finalizamos el guardador de archivo.

#endif // CYTTEK_REGISTER

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
