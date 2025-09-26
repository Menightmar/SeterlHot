
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		CORE PARA PROYECTO EN GENERAL
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

/// @defgroup Core Core
/// @author José Raúl Moreno Acero
/// @date 10/05/2024
/// @brief Core con todas las bases para el proyecto , contiene funciones , constantes , macros , etc. Para uso en general de todo el proyecto
/// @details
/// La finalidad de tener separado el core del resto de utilerias es que para este caso se genera un dll monolitico que conlleva todas las funciones cuya
/// dependencia únicamente consiste en la libreria estandar stdc++ libgcc , STL , winapi , etc. Por consiguiente es el dll más pesado ya que de ser enlazada
/// estaticamente a la libreria estandar se copian todas las funcionalidades del estandar. 
/// 
/// Por lo tanto es un archivo de codigo que no debe tocarse a menudo para evitar reemplazar el archivo dll pesado cada vez que se hagan pequeños cambios.

// Definiremos lo siguiente

#pragma once

// -----------------------------------------------------------------------------
/// 
/// @file core.hpp
/// 
/// @brief Archivo con la declaración de utilerias principales y de uso común para todos los modulos y el proyecto en general. Contiene macro-definiciones
/// para el uso de API , modulos , atributos de compilador , etc.
/// 
/// @details
/// 
/// Este archivo de cabecera es la base principal de todo el proyecto para cyttek y para cualquier modulo y sub-modulo que están contenidos dentro de
/// este conjunto de herramientas.
/// 
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// @addtogroup Core
/// @{
// -----------------------------------------------------------------------------

// Definiremos la macro def para proteger este archivo.

#ifndef CYTTEK_CORE
#define CYTTEK_CORE

// Declaramos algunas cosas que pueden ser utilizadas para el proposito en general de todo el proyecto.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							VALIDACION DE MACROS
// 							
// -----------------------------------------------------------------------------

// Realizaremos una serie de validaciones para poder determinar elementos especificos de compilador.

// -----------------------------------------------------------------------------

// Validamos la macro de nuestro elemento para la compilación dependiente.

#ifdef __GNUC__

	// Estableceremos la siguiente condicional para poder validar si no está definido el siguiente keyword.
	
	#ifndef ALWAYS_INLINE

		/// @brief Esta macro define un atributo de compilador para poder <b>forzar</b> a una función/metodo a ser siempre inline.
		
		#define ALWAYS_INLINE __attribute__ ((__always_inline__)) inline

		// -----------------------------------------------------------------------------
		
	#endif // ALWAYS_INLINE

	// Ahora vamos a pasar a lo siguiente que es parte de poder definir la banderita para saber si es un import o un export de la siguiente forma.
	
	#ifndef CYTTEK_API

		// Ahora se valida de la siguiente manera.

		#ifndef CYTTEK_UTILITY_EXPORT
			
			// Aplicaremos el import por default.

			#define CYTTEK_API __attribute__ ((dllimport)) 

			// -----------------------------------------------------------------------------

		#else

			// Aplicaremos de otro modo el export.

			#define CYTTEK_API __attribute__ ((dllexport))

			// -----------------------------------------------------------------------------

		#endif // CYTTEK_UTILITY_EXPORT

		// -----------------------------------------------------------------------------
		
	#endif // CYTTEK_API

// -----------------------------------------------------------------------------

#else // __GNUC__

	// Estableceremos la siguiente condicional para poder validar que compilador estamos utilizando.

	#ifndef ALWAYS_INLINE

		// Definiremos lo siguiente.

		#define ALWAYS_INLINE inline

		// -----------------------------------------------------------------------------

	#endif // ALWAYS_INLINE

	// Ahora vamos a pasar a lo siguiente que es parte de poder definir la banderita para saber si es un import o un export de la siguiente forma.

	#ifndef CYTTEK_API

		// Ahora se valida de la siguiente manera.

		#ifndef CYTTEK_UTILITY_EXPORT

			// Aplicaremos el import por default.

			#define CYTTEK_API __declspec (dllimport)

			// -----------------------------------------------------------------------------

		#else

			// Aplicaremos de otro modo el export.

			#define CYTTEK_API __declspec (dllexport)

			// -----------------------------------------------------------------------------

		#endif // CYTTEK_UTILITY_EXPORT

		// -----------------------------------------------------------------------------

	#endif // CYTTEK_API

	// -----------------------------------------------------------------------------

#endif // __GNUC__

// Ahora para el caso de windows definiremos lo siguiente.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// 
// 							DEFAULT DEF FOR WINDOWS
// 							
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// Validaremos lo siguiente.

#if defined (_WIN32) && !defined (__GNUC__)

	// Validaremos lo siguiente.

	#ifndef _CRT_SECURE_NO_WARNINGS

		// Definiremos nuestra macro siguiente

		#define _CRT_SECURE_NO_WARNINGS

		// -----------------------------------------------------------------------------

	#endif //_CRT_SECURE_NO_WARNINGS

	// Ahora para que no muestren mensajes de funciones obsoletas.

	#ifndef _CRT_NONSTDC_NO_DEPRECATE

		// Definiremos el siguiente macro.

		#define _CRT_NONSTDC_NO_DEPRECATE

		// -----------------------------------------------------------------------------
		
	#endif //_CRT_NONSTDC_NO_DEPRECATE
	
	// Para evitar que usen la macro para las funciones de std::min y std::max tenemos este.
	
	#ifndef NOMINMAX
		
		// Definiremos la macro siguiente.
		
		#define NOMINMAX
		
		// -----------------------------------------------------------------------------
		
	#endif // NOMINMAX

	// -----------------------------------------------------------------------------

#endif // _WIN32 and MSVC

// Ahora incluiremos las bases para poder comenzar a programar cualquier modulo que esté basado con este mismo core.

// -----------------------------------------------------------------------------

// Incluiremos los elementos base para los printf , scant , cin y cout para pintar sobre la salida estandar de nuestro aplicativo.

#include <stdio.h>
#include <stdlib.h>

// Incluiremos los strings , cstrings y string_view.

#include <string.h>
#include <string>
#include <string_view>

// Incluiremos los streams para abrir archivos.

#include <iostream>
#include <fstream>
#include <sstream>

// Algunas exceptions.

#include <stdexcept>

// Incluiremos el sistema de archivos incorporado en c++ 17.

#include <system_error>
#include <filesystem>

// Incluiremos las excepciones estandar.

#include <stdexcept>

// Incluiremos los concepts.

#include <concepts>

// Incluiremos nuestros rangos de c++ 20.

#include <ranges>

// Como contenedores para utilizar tenemos el unordered_map y el vector de elementos.

#include <map>
#include <unordered_map>
#include <vector>
#include <array>

// Ahora pasamos a incluir la api de windows nativa para el manejo de elementos.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							WINDOWS NATIVE API
// 							
// -----------------------------------------------------------------------------

// Incluiremos el include más importante.

#include <windows.h>

// Ahora tendremos que realizar la incorporación de un determinado elemento que nos permita a nosotros establecer elementos printables.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		PRINTABLE META-INTERFACE
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Tenemos una meta interfaz que nos permite realizar la validacion para elementos que pueden pintarse ya sea con la funcion print o con la funcion printf.

// -----------------------------------------------------------------------------

// Crearemos el concepto que determina esta meta-interfaz.

template <typename TCallable>
concept Printable = requires (TCallable element) {
	
	// -----------------------------------------------------------------------------
	
	// Tenemos que validar que el elemento actual puede invocar a una función printf con varios elementos.
	
	{ element ("ejemplo") };
	
	// Requerimos que también pinte con los argumentos variables.
	
	{ element ("ejemplo" , 100 , 200 , 300) };
	
	// -----------------------------------------------------------------------------
	
};

// Pasaremos ahora al siguiente que esla definición del metaprint.

// -----------------------------------------------------------------------------
// 
// 								METAPRINTF
// 							
// -----------------------------------------------------------------------------

// De la siguiente mnaera tenemos lo siguiente ue es la definición del metaprintf para poder pintar usando el estandar de c++ moderno.

template <typename ... TArgs>
struct metaprintf {
	
	// -----------------------------------------------------------------------------
	
	// Pintaremos lo que es nuestro respectivo formato con los argumentos variables.
	
	void operator () (const std::string & format , TArgs ... elements) {
		
		// -----------------------------------------------------------------------------
		
		// Invocaremos a nuestro respectivo printf para pintar esta info.
		
		printf (format.c_str () , elements ...);
		
		// -----------------------------------------------------------------------------
		
	}
	
	// Tenemos el siguiente para pintar datos con un callable.
	
	template <Printable TCallable>
	void operator () (TCallable && printer , const std::string & format , TArgs ... elements) {
		
		// -----------------------------------------------------------------------------
		
		// Invocaremos a nuestro respectivo printf para pintar esta info.
		
		printer (format.c_str () , elements ...);
		
		// -----------------------------------------------------------------------------
		
	}
	
	// -----------------------------------------------------------------------------
	
};

// Lo siguiente será definir nuestro propio mecanismo para poder realizar el parseo para los tipos de alias que necesitaremos para poder reflejar
// de mejor manera todo lo que necesitemos.

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// 
// 							TYPE ID ALIAS FOR CYTTEK
// 							
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// Requerimos primero definir una funcionalidad que se encargue de poder establecer un alias para los tipos de datos de nuestros logs de forma que podamos realizar
// diferentes tipos de datos.

// -----------------------------------------------------------------------------

// Tendremos primero lo siguiente para poder realizar nuestro acomodo de un determinado conjunto de caracteres a un 

template <size_t ... NIndexes>
static constexpr auto GetTypeArrayString (const char * const stringType , std::index_sequence <NIndexes ...>) {
	
	// Devolveremos un array con base en el strin type obtenido de la siguiente forma anexandole nuestro terminador de linea.
	
	return std::array <char , (sizeof ... (NIndexes) + 1u)> { stringType [NIndexes] ... , '\0' };
	
	// -----------------------------------------------------------------------------
	
}

// Ahora tendremos la funcionalidad que nos permite devolver lo que será nuestro respectivo string del tipo de dato con datos mediante el uso de funciones de compilador.

template <typename Type>
static constexpr auto GetTypeString () {
	
	// Tendremos varios constexpr en tiempo de compilacion que nos ayudarán a definir un string con el formato que tenemos para nuestro respectivo chekador de tipos.
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							FUNC TEMPLATE TYPE CHEKER
	// 							
	// -----------------------------------------------------------------------------
	
	// Cada tipo de compilador tiene su mecanismo en macro para poder determinar el tipo de valor de los templates en el caso de funciones , por lo que tenemos
	// que hacer uso especifico del que corresponda a nuestro compilador para poder devolver nuestro index.
	
	// -----------------------------------------------------------------------------
	
	// Comenzaremos para el caso de MINGW de la siguiente forma.
	
	#if defined (__GNUC__)
		
		// -----------------------------------------------------------------------------
		
		// Estableceremos nuestro respectivo string view con base en un formato para este compilador que usaremos como base.
		
		constexpr std::string_view typeFuncData (__PRETTY_FUNCTION__);
		
		// Tenemos el siguiente valor como prefijo para buscar.
		
		constexpr std::string_view typeFuncPrefix (" = ");
		
		// Declaramos ahora el terminador para este elemento.
		
		constexpr std::string_view typeFuncTerminator ("]");
		
		// -----------------------------------------------------------------------------
		
	#elif defined (_MSC_VER)
		
		// -----------------------------------------------------------------------------
		
		// Para el caso de nuestro compilador de visual studio tenemos otro tipo de nomenclatura la cual es la siguiente para la funcion.
		
		constexpr std::string_view typeFuncData (__FUNCSIG__);
		
		// Tenemos el siguiente valor como prefijo para buscar.
		
		constexpr std::string_view typeFuncPrefix ("<");
		
		// Declaramos ahora el terminador para este elemento.
		
		constexpr std::string_view typeFuncTerminator (">(void)");
		
		// -----------------------------------------------------------------------------
	
	#else
		
		// -----------------------------------------------------------------------------
		
		// Para el caso de nuestro compilador de visual studio tenemos otro tipo de nomenclatura la cual es la siguiente para la funcion.
		
		constexpr std::string_view typeFuncData;
		
		// Tenemos el siguiente valor como prefijo para buscar.
		
		constexpr std::string_view typeFuncPrefix;
		
		// Declaramos ahora el terminador para este elemento.
		
		constexpr std::string_view typeFuncTerminator;
		
		// -----------------------------------------------------------------------------
		
	#endif
	
	// Buscaremos donde empieza el valor "[" y donde termina para poder enviar a nuestra funcion y saber con certeza cuanto equivale.
	
	constexpr size_t typeIndexOrigin = typeFuncData.find (typeFuncPrefix);
	
	// Obtendremos el valor resultante en caso de ser diferente a lo que ya se tiene.
	
	if constexpr (!typeFuncData.empty () && (typeIndexOrigin != std::string_view::npos)) {
		
		// Obtendremos el origen del inicio desde donde comenzar.
		
		constexpr size_t typeIndexBegin = (typeIndexOrigin + typeFuncPrefix.size ());
		
		// Ahora para el caso del finalizador tenemos.
		
		constexpr size_t typeIndexEnd = typeFuncData.find (typeFuncTerminator);
		
		// Ahora empezaremos atrabajar con esto enviando el valor devuelto.
		
		return GetTypeArrayString ((typeFuncData.data () + typeIndexBegin) , std::make_index_sequence <(typeIndexEnd - typeIndexBegin)> ());
		
		// -----------------------------------------------------------------------------
		
	}
	else {
		
		// Declaramos un valor por defecto.
		
		constexpr std::string_view typeDefault ("__no_def__");
		
		// De cualquier otro modo devolveremos un string vacio.
		
		return GetTypeArrayString (typeDefault.data () , std::make_index_sequence <typeDefault.size ()> ());
		
		// -----------------------------------------------------------------------------
		
	}
	
	// -----------------------------------------------------------------------------
	
}

// Ahora declaramos un template para una estructura que se encargará de mantener un valor constante de tipo array en tiempo de compilacion.

template <typename Type>
struct TypeString {
	
	// Tendremos la siguiente definición.
	
	// -----------------------------------------------------------------------------
	// 
	// 							TYPE ALIAS IN STRING
	// 							
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	
	// Ahora definiremos uin alias para el tipo de dato devuelto por la funcion de busqueda de tipo.
	
	using type = decltype (GetTypeString <Type> ());
	
	// Definiremos lo siguiente para el caso de que truene.
	
	static_assert (not std::is_void_v <type> , "Type no es valido");
	
	// Ahora definiremos lo que es nuestro campo de valor para poder obtener lo que necesitamos.
	
	static constexpr auto value = GetTypeString <Type> ();
	
	// Ahora una funcion estatica para poder devolver este dicho valor convertido a un respectivo data.
	
	static constexpr const char * c_str () {
		
		// Devolveremos nuestro value convertido a c_string.
		
		return value.data ();
		
		// -----------------------------------------------------------------------------
		
	}
	
	// -----------------------------------------------------------------------------
	
};

// Ahora pasaremos a la determinación de una metainterfaz para poder gestionar de manera eficiente los Strings y poderles dar tratamiento
// para cuando sea necesario utiliarlos.

// -----------------------------------------------------------------------------
// 
// 							META STRING INTERFAZ
// 							
// -----------------------------------------------------------------------------

// Para poder realizarlo necesitamos primero que definir algunos conceptos para poder determinar si la cadena en cuestión es una cadena
// de tipo convertible o construible a partir de lo que determinamos con el string.

// -----------------------------------------------------------------------------

// Declaramos nuestro concepto para poder validar que un string sea construible a partir de un tipo de dato que estamos estableciendo.

template <typename TString>
concept CStringContructible = std::is_constructible_v <std::string , TString>;

// Ahora el siguiente concepto es para validar que nuestro string se puede construir a partir de cualquier otro valor por medio del uso de la función
// de conversión establecida con el std::to_string.

template <typename TInput>
concept CStringConvertible = requires (const TInput & value) {
	
	// -----------------------------------------------------------------------------
	
	// Requerimos que la función devuelva un valor que es convertible a un std::string de la siguiente forma.
	
	{ std::to_string (value) } -> std::convertible_to <std::string>;
	
	// -----------------------------------------------------------------------------
	
};

// Ahora aplicaremos ambos casos en un solo concepto para poder asi tener cualquiera de las dos opciones disponibles.

template <typename TValue>
concept CStringValue = CStringContructible <TValue> or CStringConvertible <TValue>;

// Una vez hecho esto lo siguiente es la definición de una función de plantilla que nos parmita realizar la conversión (en caso de ser necesario)
// al tipo de dato que se requiere para poder devolver el valor respectivo.

template <CStringValue TString>
ALWAYS_INLINE static decltype (auto) MakeString (TString && value) {
	
	// Validaremos varios casos de uso en tiempo de compilación para poder asi saber que devolver en este caso.
	
	// -----------------------------------------------------------------------------
	// 
	// 							VALIDATION TYPE STRING
	// 							
	// -----------------------------------------------------------------------------
	
	// El primero sera validar si el tipo de dato que estamos recibiendo es ya un simple string.
	
	if constexpr (std::is_same_v <std::decay_t <TString> , std::string>) {
		
		// Si es el mismo tipo de cadena entonces devolveremos el valor respectivo convertido de la siguiente forma.
		
		return std::forward <TString> (value);
		
		// -----------------------------------------------------------------------------
		
	}
	else if constexpr (CStringContructible <TString>) {
		
		// Ahora para este caso vamos a requerir construir un nuevo string con el valor que nos están enviando.
		
		return std::string (std::forward <TString> (value));
		
		// -----------------------------------------------------------------------------
		
	}
	else {
		
		// Finalmente para este otro caso tenemos que devolver la conversión respectiva al tipo de dato que tenemos.
		
		return std::to_string (value);
		
		// -----------------------------------------------------------------------------
		
	}
	
	// -----------------------------------------------------------------------------
	
}

// Ahora pasaremos a declarar lo siguiente.

// -----------------------------------------------------------------------------
// 
// 							STATIC CONST EMPTY_STRING
// 							
// -----------------------------------------------------------------------------

// Ahora para poder tener a la mano un respectivo STRING_EMPTY que exista en todo momento para el que lo necesite tendremos el siguiente
// valor estatico para este proposito.

extern CYTTEK_API const std::string CYTTEK_EMPTY_STRING;

// Ahora pasaremos para las conversiones a diferentes tipos de datos.

// -----------------------------------------------------------------------------
	
// -----------------------------------------------------------------------------
// 
// 							CASOS DE USO DE CONVERSION
// 							
// -----------------------------------------------------------------------------

// Tenemos los siguientes casos de uso para la conversión.

// -----------------------------------------------------------------------------

// CASO 1 : Quitar qualificador const a un determinado valor.

template <typename TA , typename TB>
concept ConvertConst = requires {
	
	// -----------------------------------------------------------------------------
	
	// Requerimos que el tipo de dato sea un puntero para ambos extremos de la siguiente manera.
	
	requires (std::is_pointer_v <TA> and std::is_pointer_v <TB>);
	
	// Si el operador B NO es constante tenemos que validar eso.
	
	requires not std::is_const_v <std::remove_pointer_t <TB>>;
	
	// Tenemos que validar que el operador A SI es constante.
	
	requires std::is_const_v <std::remove_pointer_t <TA>>;
	
	// -----------------------------------------------------------------------------
	
};

// CASO 2 : Conversión estatica entre un tipo de dato derivado directo o 

template <typename TA , typename TB>
concept ConvertStatic = requires {
	
	// -----------------------------------------------------------------------------
	
	// Requerimos que sean convertibles entre si.
	
	requires std::is_convertible_v <std::decay_t <std::remove_pointer_t <TA>> , std::decay_t <std::remove_pointer_t <TB>>>;
	
	// Que tampoco sea un puntero void.
	
	requires not std::is_void_v <std::decay_t <std::remove_pointer_t <TA>>>;
	
	// -----------------------------------------------------------------------------
	
};

// Ahora vamos por el siguiente caso de uso para poder validar que el tipo de dato en cuestión pertenece a
// los tipos de datos derivables.

// CASO 3 : Conversión dinamica entre una clase y otra clase que no sea una derivación directa.

template <typename TA , typename TB>
concept ConvertDynamic = requires {
	
	// -----------------------------------------------------------------------------
	
	// Requerimos tener el valor derivado de la clase base y también que no sea el mismo.
	
	requires not std::is_same_v <std::decay_t <std::remove_pointer_t <TA>> , std::decay_t <std::remove_pointer_t <TB>>>;
	
	// Requerimos que no sea base de ese tipo de dato.
	
	requires not std::is_base_of_v <std::decay_t <std::remove_pointer_t <TB>> , std::decay_t <std::remove_pointer_t <TA>>>;
	
	// Que tampoco sea un puntero void.
	
	requires not std::is_void_v <std::decay_t <std::remove_pointer_t <TA>>>;
	
	// -----------------------------------------------------------------------------
	
};

// CASO 4 : Conversión reinterpretada entre un puntero a otro tipo de puntero distinto.

template <typename TA , typename TB>
concept ConvertReinterpret = requires {
	
	// -----------------------------------------------------------------------------
	
	// Requerimos que el tipo de dato a convertir sea un puntero.
	
	requires std::is_pointer_v <TA>;
	
	// Requerimos que no sean el mismo tipo de dato base sin el puntero.
	
	requires not std::is_same_v <std::decay_t <TA> , std::decay_t <TB>>;
	
	// -----------------------------------------------------------------------------
	
};

// Ahora implementaremos la meta-función que realiza la conversión a cualquier tipo de dato que se requiere

template <typename TOutput , typename TInput> requires std::is_default_constructible_v <TOutput>
static constexpr TOutput Convert (TInput && value) {
	
	// -----------------------------------------------------------------------------
	
	// Validamos el estilo de la conversión de la siguiente manera.
	
	if constexpr (ConvertConst <std::remove_reference_t <TInput> , std::remove_reference_t <TOutput>>) {
		
		// -----------------------------------------------------------------------------
		
		// Tenemos lo siguiente que es para la parte de convertir con el const cast.
		
		return const_cast <TOutput> (value);
		
		// -----------------------------------------------------------------------------
		
	}
	else if constexpr (ConvertStatic <std::remove_reference_t <TInput> , std::remove_reference_t <TOutput>>) {
		
		// -----------------------------------------------------------------------------
		
		// Devolveremos la conversion estatica  respectiva.
		
		return static_cast <TOutput> (value);
		
		// -----------------------------------------------------------------------------
		
	}
	else if constexpr (ConvertDynamic <std::remove_reference_t <TInput> , std::remove_reference_t <TOutput>>) {
		
		// -----------------------------------------------------------------------------
		
		// Devolveremos la conversion dinamica respectiva.
		
		return dynamic_cast <TOutput> (value);
		
		// -----------------------------------------------------------------------------
		
	}
	else if constexpr (ConvertReinterpret <std::remove_reference_t <TInput> , std::remove_reference_t <TOutput>>) {
		
		// -----------------------------------------------------------------------------
		
		// Devolveremos la conversion reinterpretada respectiva.
		
		return reinterpret_cast <TOutput> (value);
		
		// -----------------------------------------------------------------------------
		
	}
	
	// Devolvemos lo siguiente por default.
	
	return TOutput ();
	
	// -----------------------------------------------------------------------------
	
}

// Tenemos lo siguiente que es para poder establecer diferentes macro auxiliares que nos faciliten algunas labores.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							MACROS PARA CASTEOS
// 							
// -----------------------------------------------------------------------------

// Con la finalidad de poder transformar una cadena a un formato valido tenemos una función de conversión que realiza perfectamente
// dicha conversión.

// -----------------------------------------------------------------------------

// Primero pasaremos a definir la macro para poder convertir un LPCSTR a un LPSTR utilizando esta simple macro.

#define 			CYTTEK_LPSTR(TEXTO) 				Convert <LPSTR> (TEXTO)

// Para poder definir una version menor con un DWORD tenenemos lo siguiente.

#define 			CYTTEK_MINOR(MINOR) 				LOWORD (MINOR)

// Para poder definir una version mayor con un DWORD tenemos lo siguiente.

#define 			CYTTEK_MAYOR(MAYOR) 				HIWORD (MAYOR)

// Para poder establecer la version con base en el valor menor.

#define 			CYTTEK_WORD_MINOR(MINOR) 			((WORD) (MINOR << 8))

// Para hacer la version con base en el valor mayor.

#define 			CYTTEK_WORD_MAYOR(MAYOR) 			((WORD) CYTTEK_MINOR (MAYOR))

// Para conformar la version con WORD de longitud.

#define 			CYTTEK_WORD_VERSION(MAYOR , MINOR) 	(CYTTEK_WORD_MAYOR (MAYOR) | CYTTEK_WORD_MINOR (MINOR))

// Para poder definir una versión con un MAKELONG mediante el uso respectivo de la version mayor y menor tenemos lo siguiente.

#define  			CYTTEK_VERSION(BEGIN , END) 		MAKELONG (BEGIN , END) 



// Ahora pasaremos con las utilerias para el copiado , borrado de archivos así como también para poder realizar la resolución de nombres en los paths
// que se indicen con simbolos $ como si fueran variables de entorno.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// 
// 							RESOLVE DIRS AND PATHS CORE
// 							
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// Para estas funcionalidades requerimos usar de igual forma el filesystem por lo que utilizaremos el siguiente using para poder incorporar dicho
// namespace de esta manera.

namespace CyttekFS = std::filesystem;

// Ahora vamos con las funciones para poder copiar archivos/carpetas , moverlos o eliminarlos , tenemos lo siguiente.

// -----------------------------------------------------------------------------

// Tendremos una función para poder realizar la validación de un archivo para poder comprobar si existe o no de la siguiente forma.

template <CStringValue TString>
ALWAYS_INLINE static bool ExistPath (const TString & currentPath) {
	
	// Realizaremos la validación sensilla para saber si el path a nuestro actual archivo o directorio existe en estos momentos.
	
	return CyttekFS::exists (CyttekFS::path (MakeString (currentPath)));
	
	// -----------------------------------------------------------------------------
	
}

// Definiremos la función para poder crear un directorio o arbol de directorios que se le especifiquen mediante '/' por lo cual tendremos esto.

template <CStringValue TString>
static bool CreateDirectories (const TString & currentTree) {
	
	// -----------------------------------------------------------------------------
	
	// Recuperamos nuestro valor actual.
	
	const auto & currentTreeString = MakeString (currentTree);
	
	// Lo primero a validar será que el actual parametro tenga algo para poder continuar.
	
	if (!currentTreeString.empty () && !ExistPath (currentTreeString)) try {
		
		// -----------------------------------------------------------------------------
		
		// Ahora pasaremos a realizar la creación de nuestro arbol de directorios de la siguiente manera.
		
		return CyttekFS::create_directories (currentTreeString);
		
		// -----------------------------------------------------------------------------
		
	}
	catch (const std::exception & currentError) {
		
		// Tenemos un error entonces lo propagaremos.
		
		throw;
		
		// -----------------------------------------------------------------------------
		
	}
	
	// Finalmente devolveremos true de cualquier otro modo.
	
	return true;
	
	// -----------------------------------------------------------------------------
	
}

// Ahora tenemos la siguiente utileria para poder realizar la eliminación de archivos o directorios que están en alguna ubicación que se tenga definida.

template <CStringValue TString>
static bool RemovePath (const TString & currentPath , bool removeAll = true) {
	
	// -----------------------------------------------------------------------------
	
	// Recuperamos nuestro valor actual.
	
	const auto & currentString = MakeString (currentPath);
	
	// Validaremos que tengamos lo siguiente para poder avanzar.
	
	if (!currentString.empty () && ExistPath (currentString)) try {
		
		// -----------------------------------------------------------------------------
		
		// Ahora realizaremos la eliminación de dicho archivo de la siguiente manera.
		
		return (removeAll ? static_cast <bool> (CyttekFS::remove_all (currentString)) : CyttekFS::remove (currentString));
		
		// -----------------------------------------------------------------------------
		
	}
	catch (const std::exception & currentError) {
		
		// Tenemos un error entonces lo propagaremos.
		
		throw;
		
		// -----------------------------------------------------------------------------
		
	}
	
	// De cualquier modo devolveremos false.
	
	return false;
	
	// -----------------------------------------------------------------------------
	
}

// Ahora para poder mover un path de un lugar a otro tendremos lo siguiente.

template <CStringValue TStringCurrent , CStringValue TStringMove>
static bool MovePath (const TStringCurrent & currentPath , const TStringMove & newPath , bool ovewrite = true) {
	
	// -----------------------------------------------------------------------------
	
	// Recuperamos nuestro valor actual.
	
	const auto & currentStringPath = MakeString (currentPath);
	
	// Ahora para el caso del segundo path a donde mover.
	
	const auto & currentStringNew = MakeString (newPath);
	
	// Validaremos que tengamos lo siguiente para poder avanzar.
	
	if (!currentStringPath.empty () && ExistPath (currentStringPath)) try {
		
		// Ahora validaremos si el archivo o path destino existe y si es asi y lo está indicando entonces lo borraremos.
		
		if (ovewrite && ExistPath (currentStringNew)) {
			
			// Realizaremos el borrado de nuestr respectivo archivo o directorio destinos.
			
			RemovePath (currentStringNew , true);
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
		
		// Ahora realizaremos la eliminación de dicho archivo de la siguiente manera.
		
		CyttekFS::rename (currentStringPath , currentStringNew);
		
		// Devolveremos true.
		
		return true;
		
		// -----------------------------------------------------------------------------
		
	}
	catch (const std::exception & currentError) {
		
		// Tenemos un error entonces lo propagaremos.
		
		throw;
		
		// -----------------------------------------------------------------------------
		
	}
	
	// De cualquier modo devolveremos false.
	
	return false;
	
	// -----------------------------------------------------------------------------
	
}

// Ahora para poder realizar el copiado de directorios o archivos tendremos lo siguiente. Tendremos también un conjunto de propiedades
// para poder especificar el comportamiento que tendremos al copiar de esa forma.

template <CStringValue TStringCurrent , CStringValue TStringCopy>
static bool CopyPath (const TStringCurrent & currentPath , const TStringCopy & copyPath ,
                      CyttekFS::copy_options currentOptions = CyttekFS::copy_options::none) {
	
	// -----------------------------------------------------------------------------
	
	// Recuperamos nuestro valor actual.
	
	const auto & currentStringPath = MakeString (currentPath);
	
	// Ahora para el caso del para el path destino.
	
	const auto & currentStringCopy = MakeString (copyPath);
	
	// Validaremos que tengamos lo siguiente para poder avanzar.
	
	if (!currentStringPath.empty () && ExistPath (currentStringPath)) try {
		
		// Condición especial para Mingw para poder sobre-escribir archivos.
		
		#if defined (__GNUC__) || defined (__MINGW32__)
			
		// -----------------------------------------------------------------------------
		
		// Validaremos si hay que reemplazar el archivo existente.
		
		if (ExistPath (currentStringCopy) &&
		   (static_cast <bool> (currentOptions & CyttekFS::copy_options::overwrite_existing) ||
		   (static_cast <bool> (currentOptions & CyttekFS::copy_options::update_existing) && 
		   (CyttekFS::last_write_time (currentStringPath) > CyttekFS::last_write_time (currentStringCopy))))) {
			
			// Removeremos el archivo al cual estaremos copiando antes de copiar.
			
			RemovePath (currentStringCopy , true);
			
			// ------------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
		
		#endif
		
		// Ahora validamos que se trata de un directorio o un archivo.
		
		if (CyttekFS::is_directory (currentStringPath)) {
			
			// -----------------------------------------------------------------------------
			
			// Ahora copiaremos el directorio actual en el otro campo con las opciones establecidas.
			
			CyttekFS::copy (currentStringPath , currentStringCopy , currentOptions);
			
			// -----------------------------------------------------------------------------
			
		}
		else {
			
			// -----------------------------------------------------------------------------
			
			// Ahora realizaremos la copia de dicho archivo al path destino de la siguiente forma.
			
			CyttekFS::copy_file (currentStringPath , currentStringCopy , currentOptions);
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Devolveremos true.
		
		return true;
		
		// -----------------------------------------------------------------------------
		
	}
	catch (const std::exception & currentError) {
		
		// Tenemos un error entonces lo propagaremos.
		
		throw;
		
		// -----------------------------------------------------------------------------
		
	}
	
	// De cualquier modo devolveremos false.
	
	return false;
	
	// -----------------------------------------------------------------------------
	
}

// Ahora pasaremos a lo siguiente.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		MANEJADOR DE ARCHIVOS
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Tenemos lo que es nuestras funciones para la lectura de archivos de diferentes formatos de la siguiente manera.

// -----------------------------------------------------------------------------

// Se tiene la implementación del mecanismo para el control y manejo de las configuraciones de nuestro programa actual. Se puede utilizar para cualquier
// proposito mediante el uso de un Contenedor de Configuraciones que permita establecer todos los TAGS a considerar para el config actual.

// Primero tendremos una pequeña función general que se encarga de dar lectura a un archivo de Texto y por consiguiente devuelve la cadena resultante.

/// ----------------------------------------------------------------------------
/// @brief      Realiza la lectura de un archivo de Texto plano mediante la biblioteca estandar (ifstream).
///
/// @param[in]  Filename  Ruta (filename) del archivo a leer.
///
/// @tparam     TChar     Tipo de caracter para la cadena (por defecto es char)
///
/// @return     Devuelve el string con todo lo que está dentro del archivo de texto.
/// 
/// @details
/// 
/// Simplemente realiza la lectura del archivo de texto y devuelve un string con todo lo que se leyó.
/// 
// -----------------------------------------------------------------------------

template <typename TChar = char>
static std::basic_string <TChar> ReadFile (const std::basic_string <TChar> & Filename) {
	
	// Tenemos nuestra cadena resultante después de haber leído el archivo de la siguiente manera.
	
	std::basic_string <TChar> CurrentResult;
	
	// Ahora validaremos si el filename actual existe para poder continuar.
	
	if (!Filename.empty () && CyttekFS::exists (Filename)) {
		
		// Realizamos la lectura de nuestro actual archivo.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							LECTURA DEL ARCHIVO
		// 							
		// -----------------------------------------------------------------------------
		
		// Realizaremos el parseo del archivo de configuración actual , para esto realizamos primero al apertura del mismo.
			
		std::basic_ifstream <TChar> CurrentInput (Filename);
		
		// Crearemos un nuevo elemento de StringStream para almacenar lo leído.
		
		std::basic_stringstream <TChar> Input;
		
		// -----------------------------------------------------------------------------
		
		// Validamos que no se haya llegado al final del archivo para continuar.
		
		if (CurrentInput.is_open () && !CurrentInput.eof ()) {
			
			// Realizamos la lectura desde el ifstream hacia el buffer interno del stringstream hasta acabar de leer.
			
			Input << CurrentInput.rdbuf ();
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Cerraremos el archivo de configuración.
		
		CurrentInput.close ();
		
		// -----------------------------------------------------------------------------
		
		// Asignaremos el resultado del buffer a la cadena del resultado.
		
		CurrentResult = Input.str ();
		
		// -----------------------------------------------------------------------------
		
	}
	
	// Finalmente devolvemos nuestra cadena resultante.
	
	return CurrentResult;
	
	// -----------------------------------------------------------------------------
	
}

// Ahora una función para poder poner el const char como alias.

ALWAYS_INLINE static std::string ReadFile (const char * const Filename) {
	
	// Devolveremos lo que es el texto para este filename.
	
	return ReadFile (std::string (Filename));
	
	// -----------------------------------------------------------------------------
	
}

// Ahora para poder guardar un string en un archivo json tenemos lo siguiente.

template <typename TValue , typename TChar = char>
requires requires (const TValue & Input , std::ofstream Output) {
	
	// Requerimos que el valor sea de tipo valido para asignar a un ofstream.
	
	Output << Input;
	
	// -----------------------------------------------------------------------------
	
}
static void WriteFile (const TValue & Input , const std::basic_string <TChar> & Filename , bool ovewrite = true) {
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							WRITING JSON FILE
	// 							
	// -----------------------------------------------------------------------------
	
	// Validaremos primero que no sea vacio el filename.
	
	if (!Filename.empty ()) {
		
		// Validaremos nuestro current path antes de escribir en el archivo.
		
		CyttekFS::path currentPath (Filename);
		
		// Validaremos si no existe nuestra carpeta anterior para crear los directorios necesarios primero.
		
		if (!CyttekFS::exists (currentPath.parent_path ())) CreateDirectories (currentPath.parent_path ().generic_string ());
		
		// -----------------------------------------------------------------------------
		
		// Crearemos las flags para el modo de operacion.
		
		auto currentFlags = std::ios::out;
		
		// Ahora validaremos si el flag está activado para mandar el flag de trunc respectivo.
		
		if (ovewrite) 	currentFlags |= std::ios::trunc;
		else 			currentFlags |= std::ios::app;
		
		// Pasaremos a escribir el archivo json para poder establecer lo que vamos a realizar.
		
		std::ofstream currentStream (Filename , currentFlags);
		
		// Validamos si el stream está abierto para poder comenzar a escribir.
		
		if (currentStream.is_open ()) {
			
			// -----------------------------------------------------------------------------
			
			// Ahora vamos a realizar la escritura en ese archivo para poder terminar.
			
			currentStream << Input;
			
			// Cerraremos el flujo.
			
			currentStream.close ();
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
		
	}
	
	// -----------------------------------------------------------------------------
	
}

// Ahora una función para poder poner el const char como alias.

template <typename TValue>
requires requires (const TValue & Input , std::ofstream Output) {
	
	// Requerimos que el valor sea de tipo valido para asignar a un ofstream.
	
	Output << Input;
	
	// -----------------------------------------------------------------------------
	
}
ALWAYS_INLINE static void WriteFile (const TValue & Input , const char * const Filename) {
	
	// Devolvemos la llamada a la función anterior.
	
	WriteFile (Input , std::string (Filename));
	
	// -----------------------------------------------------------------------------
	
}

// Ahora pasaremos a algunas funcions para la gestión de memoria y validación de la misma.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		VALIDACION DE MEMORIA
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Para poder utilizar el sistema de validación de memoria virtual ocupamos tener en cuenta que el sistema de memoria virtual va a gestionarse por paginas
// por lo que es indispensable saber que tipo de validacion y permisos queremos validar.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							VALIDATION PTR
// 							
// -----------------------------------------------------------------------------

// Para validar que un puntero es valido para escribir tendremos lo siguiente.

static constexpr DWORD PTR_PROTECT_READ = 			(PAGE_READWRITE 	| PAGE_READONLY 	| PAGE_EXECUTE_READ 		| PAGE_EXECUTE_READWRITE);

// Para validar que una pagina de memoria sea valida para escribir tendremos lo siguiente.

static constexpr DWORD PTR_PROTECT_WRITE = 			(PAGE_WRITECOPY 	| PAGE_READWRITE 	| PAGE_EXECUTE_READWRITE 	| PAGE_EXECUTE_WRITECOPY);

// Ahora para validar que se pueda ejecutar la pagina de memoria tendremos lo siguiente.

static constexpr DWORD PTR_PROTECT_EXECUTE = 		(PAGE_EXECUTE 		| PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE 	| PAGE_EXECUTE_WRITECOPY);

// Ahora para combinar las anteriores validaciones tendremos lo siguiiente.

static constexpr DWORD PTR_PROTECT_ALL = 			(PTR_PROTECT_READ 	| PTR_PROTECT_WRITE | PTR_PROTECT_EXECUTE);

// Declaramos la función para la validación de un dato de memoria donde recibimos la memoria misma y si tiene permisos de esctitura lectura o el tipo de acceso
// que se quiera validar que tenga este espacio de memoria.

size_t CYTTEK_API ValidatePTR (const void * pointer , size_t pointerSize = sizeof (void *) , const DWORD protectMask = PTR_PROTECT_READ);

// -----------------------------------------------------------------------------

// Finalizaremos el grupo de documentación del Core.

// -----------------------------------------------------------------------------
/// @}
// -----------------------------------------------------------------------------

// Finalizamos el guardador de archivo.

#endif // CYTTEK_CORE

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
