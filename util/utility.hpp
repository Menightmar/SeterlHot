
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		CYTTEK UTILITY ADVANCED
/// 
/// @defgroup Utilerias Utilerias de proposito General
/// 
/// @brief Conjunto de funciones , clases , variables , etc. De apoyo para utilizar de manera concurrente en codigos de programas para proyectos Cyttek.
/// 
/// @section UtileriasGenerales Utilerias Generales
/// 
/// @details
/// 
/// Archivo de cabecera para la declaración e implementación de elementos de extensión adicionales para reutilizar dentro de los distintos modulos
/// que componen a los sistemas de cyttek tanto para su uso principal en cyttek como también para su utilización en algún otro modulo 
/// que asi lo requiera.
/// 
/// @mainpage Cyttek Multivendor Switch Documentacion
/// 
/// <div>
/// 	<img id="logo" src="logo.png" alt="Picture" class="imagen" style="width: 40%; margin-top: 10px; margin-botton: 10px;">
/// </div>
/// 
/// @section Introduccion Introducción
/// 
/// Tendremos 
/// 
/// @section Utilerias Utilerias
/// 
/// Las utilerias de CYTTEK son un conjunto de <b> Clases , Estructuras , Metodos , Funciones , Operadores , etc.. </b> que conforman una pequeña biblioteca
/// para uso común en cualquier proyecto donde se desee utilizar. Puesto que <b> no tienen dependencia </b> alguna con otra API de terceros se puede importar fácilmente 
/// en cualquier proyecto de C++ que se requiera , solamente se incluyen los encabezados de los <b>modulos</b> que se quieran utilizar.
/// 
/// El único requisito es tener un <b>compilador</b> que soporte el estandar <b style="font-size: 18.2px;"> C++20 </b> que es la versión como fue diseñada y hecha esta biblioteca.
/// 
/// Adicionalmente si se tiene instalado <a href="https://cmake.org/"> <b style="color: var(--primary-color);font-size: 19px;"> CMake </b> </a> , servirá de ayuda
/// para la generación de los <b> Makefiles </b> propios de nuestro sistema y compilador que estemos utilizando.
/// 
/// @section Motivacion Motivación y Antecedentes
/// 
/// El proyecto Cyttek Multivendor Utility surge a partir de un pequeño archivo de cabecera que estaba diseñado para reutilizar codigo y como herramientas de apoyo y soporte
/// para los diferentes modulos en los que esstabamos desarrollando.
/// 
/// Sin embargo debido a la gran necesidad de tener esta gamma de funciones abierta para cualquier proposito en general , es como se decide llevarlo a conformar una pequeña API para 
/// ser reutilizada en cualquier proyecto donde sea necesario , entre estos proyectos se encuentra el proyecto
/// <span style="color: var(--primary-color);font-size: 18px;"> <b> @ref GEN3XFS </b> </span> .
/// 
/// @section Componentes Módulos de las Utilerias
/// 
/// La biblioteca de Utilerias se divide en varios modulos que conforman diferentes propositos para los cuales puede utilizarse. Cada modulo
/// está declarado y definido en archivos separados por lo que no es necesario importar todos los modulos si solamente se quieren utilizar un determinado
/// número de funciones en especifico.
/// 
/// Los módulos que componen a UTILERIAS GENERICAS son los siguientes categorias :
/// 	<ul>
/// 		<li>@ref Core</li>
/// 		<li>@ref Utilerias</li>
/// 		<li>@ref Logger</li>
/// 		<li>@ref Configuracion</li>
/// 		<li>@ref ContainerTraits "Gestionador de Containers"</li>
/// 		<li>@ref Operadores</li>
/// 		<li>@ref Registros de Windows</li>
/// 		<li>@ref ModuleLoader "Cargador de Modulos"</li>
/// 	</ul>
/// 
/// @author José Raúl Moreno Acero , José Armando Luna
/// @date 20/05/2024
/// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Insertaremos nuestro primer candado de seguridad de headers de la siguiente manera.

#pragma once

// -----------------------------------------------------------------------------
/// 
/// @file utility.hpp
/// 
/// @brief Archivo con varias funciones de utilerias que sirven para realizar operaciones con cadenas principalmente , ajustes a cadenas , paddings , fillers ,
/// asi como también funciones de tiempo , modificadores , logs , etc.
/// 
/// @details
/// 
/// La finalidad es la de poder utilizarlas en cualquier codigo para poder eficientar el mantenimiento al mismo codigo y hacerlo de forma
/// dinámica y con alta escalabilidad y manteniendo siempre seguro el codigo cumpliendo con los estandares ISO para CWS , OWASP , SANS , etc.
/// Se respetan las buenas prácticas de programación para facilitar su mantenibilidad y remediaciones de codigo , haciendo esto un código más limpio y
/// seguro que a largo plazo puede expandirse con mucha facilidad.
/// 
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// @addtogroup Utilerias
/// @{
// -----------------------------------------------------------------------------

// Definiremos el siguiente macro para unificar la inclusión de este archivo.

#ifndef CYTTEK_UTILITY
#define CYTTEK_UTILITY

// Incluiremos las cabeceras principales.

#include <stdio.h>

// Incluiremos las cadebas para el C-Style.

#include <string.h>

// Los streams de c++ para cadenas.

#include <sstream>

// Incluiremos el tiempo en C/C++ (chrono).

#include <time.h>
#include <chrono>

// Incluiremos los algoritmos para utilizar.

#include <algorithm>

// Tenemos el tipo de dato arbitrario.

#include <any>

// Incluiremos los funcionales.

#include <functional>

// Incluiremos los gestionadores de memoria.

#include <memory>

// Inlcuiremos las utilerias para C++ 17.

#include <utility>

// Incluiremos también type_traits para meta-programming.

#include <type_traits>
#include <random>

// Ahora tenemos que incluir primero nuestro coresito para poder reutilizar en todos.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 								CORE
// 							
// -----------------------------------------------------------------------------

// Tenemos lo siguiente que es la inclusión de nuestro core para incluir las bases.

#include "core.hpp"

// Ahora incluiremos algunos modulos adicionales para usarlos con operadores establecidos.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							CONTAINER TRAITS
// 							
// -----------------------------------------------------------------------------

// Incluiremos nuestros modulo de container traits con todos los elementos para la validación
// y gestión de contenedores en tiempo de compilación.

#include "container_traits.hpp"

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							NAMED OPERATORS
// 							
// -----------------------------------------------------------------------------

// Incluiremos el modulo respectivo para poder importar nuestros named operators.

#include "named_operators.hpp"

// Utilizaremos el espacio de nombres respectivo para los operadores.
	
using namespace Operators;

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// 
// RM : 	10/05/2024 			Creamos los modulos para poder establecer los wrapper de las funciones de Impresión , concatenación , fill , copiar y pegar de
// una cadena a otra.
// 							
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		CString Secure Code Functions
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

/// 
/// @name Funciones Base C-Style
/// 
/// @brief Sub-conjunto de funciones para las operaciones base de cadenas tales como : StringCat , StringCpy , StringPrintf , etc.
/// 
/// @details
/// 
/// Tenemos el siguiente conjunto de funciones para la gestión de cadenas con operaciones comunes como la impresión de formato en cadenas , la longitud de cadenas
/// , la concatenación asi como las operaciones para llenar , limpiar , copiar y mover cadenas de una a otra.
/// 
/// En general se cuenta con la siguiente lista de funcionalidades.
/// 	<ul>
/// 		<li><span style="font-size: 120%;">Copiar una cadena (CopyString)</span>
/// 		<li><span style="font-size: 120%;">Concatenar una cadena (CatString)</span>
/// 		<li><span style="font-size: 120%;">Imprimir sobre una cadena (PrintfString) al estilo de C</span>
/// 	</ul>
/// 
/// Se declaran la siguiente lista de funciones.
/// 
/// <h2 class="groupheader">Funciones</h2>
/// 
/// @{
/// 

// -----------------------------------------------------------------------------
// 
// RM : 	10/05/2024		Definiremos la función Printf para imprimir con formato en un buffer de char establecido y propiamente
// asignado en tamaño (el cuál debe haber sido anteriormente repartido con malloc o new)
// 							
// -----------------------------------------------------------------------------

/// @brief Función para imprimir en un buffer (anteriormente repartido) un formato de estilo Printf con los parametros variadic establecidos
/// en la plantilla.
/// 
/// @tparam			TVars					Tipos de datos arbitrarios capturados con los parametros pasados a la función.
/// 
/// @param[out] 	BufferOutput			Buffer de chars para imprimir la salida.
/// @param[in] 		Format 					Formato estilo C-Style.
/// @param 			Arguments 				Argumentos variables pasados a la función.
/// @return 		Cantidad de Caracteres escritos en el buffer de salida especificado.

template <typename ... TVars>
ALWAYS_INLINE int CStringPrintf 
	(char *  const BufferOutput , const char *  const Format , TVars ... Arguments) {
		
	// Determinaremos el tamaño en caracteres que nos devuelve el aplicar el formato especifico con los argumentos establecidos
	// y asi mismo escribiremos sobre el buffer de salida utilizando dicha cantidad + 1 por el terminador de cadena '\0'.
	
	return snprintf (BufferOutput , (snprintf (NULL , 0 , Format , Arguments ...) + 1) , Format , Arguments ...);
	
}

// -----------------------------------------------------------------------------
// 
// RM : 	10/05/2024		Definiremos las función para poder concatenar dos buffers de entrada utilizando la longitud de la segunda
// cadena para determinar el correcto número de caracteres a concatenar en la cadena de resultado.
// 							
// -----------------------------------------------------------------------------

/// @brief Función para poder concatenar dos cadenas y devolver el resultado asi como también se asigna a este mismo buffer por convención.
/// @param 			BufferDestination 		Buffer de salida donde se concatena la cadena fuente.
/// @param 			BufferSource 			Buffer de entrada para concatenar en la cadena destino.
/// @return 		Devuelve el buffer destino (parametro 1).

ALWAYS_INLINE char * CStringCat (char * const BufferDestination , const char *  const BufferSource) {
	
	// Concatenaremos todos los caracteres del buffer entrada , al buffer de salida y lo asignaremos al buffer destino.
	
	#ifdef __GNUC__
	
	// Devolveremos lo siguiente
	
	return strncat (BufferDestination , BufferSource , strlen (BufferSource));
	
	// -----------------------------------------------------------------------------
	
	#else
	
	// Concatenaremos todos los caracteres del buffer entrada , al buffer de salida y lo asignaremos al buffer destino.
	
	strncat_s (BufferDestination , strlen (BufferSource) , BufferSource , strlen (BufferSource));
	
	// Devolvemos el buffer.

	return BufferDestination;
	
	// -----------------------------------------------------------------------------}	
	#endif

}

// -----------------------------------------------------------------------------
// 
// RM : 	10/05/2024		Definiremos las función para poder copiar todos los caracteres de la cadena fuente en la cadena
// destino en la cantidad especificada por el tamaño de la cadena fuente.
// 							
// -----------------------------------------------------------------------------

/// @brief Función para planchar toda una cadena fuente en un buffer de salida (reemplaza todos los caracteres que tiene la fuente).
/// @param[out] 	BufferDestination 		Buffer de salida donde se copia la cadena fuente.
/// @param[in] 		BufferSource 			Buffer de entrada para concatenar en la cadena destino.
/// @return 		Devuelve el buffer destino (parametro 1).
///
/// @warning 		El buffer destino debe tener espacio igual al número de caracteres de la fuente + 1 (\0).

ALWAYS_INLINE char * CStringCpy (char * const BufferDestination , const char *  const BufferSource) {
	
	// Copiaremos todos los caracteres del buffer entrada , al buffer de salida.
	
	#ifdef __GNUC__
	
	// 	Devolveremos lo siguiente para el caso de GNU.
	
	return strncpy (BufferDestination , BufferSource , strlen (BufferSource));
	
	// -----------------------------------------------------------------------------
	
	#else
	
	// Devolveremos la copia de nuestras cadenas de la siguiente manera.
	
	strncpy_s (BufferDestination , strlen (BufferSource) , BufferSource , strlen (BufferSource));
	
	// Devolvemos resultado.

	return BufferDestination;
	
	// -----------------------------------------------------------------------------
	
	#endif
	
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		FORMAT STRING
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Adicional a lo anterior tenemos también una función conveniente para formar un string con formato de estilo Printf de la siguiente forma.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Conversor de Printf Format a un String std.
///
/// @param[in]  Format     C-Printf style formato para pintar en una cadena de STD.
/// @param  	Arguments  Argumentos variables para el printf del formato establecido.
///
/// @tparam     TVars      Conjunto de tipos variables.
///
/// @return     Cadena STD con todos los valores impresos con el formato establecido y los args indicados.
/// 
// -----------------------------------------------------------------------------

template <typename ... TVars>
std::string StringPrintf (const char * const Format , TVars ... Arguments) {
	
	// -----------------------------------------------------------------------------
	// 
	// 							Buffer de Memoria
	// 							
	// -----------------------------------------------------------------------------
	
	// Crearemos nuestro string resultante vacio de momento.
	
	std::string Output;
	
	// Intentaremos realizar la localización de memoria.
	
	try {
		
		// Crearemos primero un buffer de memoria temporal para almacenar todo lo que se escriba de la cadena con una longitud determinada por lo siguiente.
		
		const size_t BufferSize = (snprintf (NULL , 0 , Format , Arguments ...) + 1);
		
		// Asignaremos una memoria para este tamaño especifico.
	
		// char * Buffer = new char [BufferSize];
		
		std::unique_ptr <char []> Buffer (new char [BufferSize]);
		
		// Limpiaremos el buffer de memoria.
		
		memset (Buffer.get () , '\0' , BufferSize);
		
		// Realizamos el formateo respectivo con los argumentos respectivos.
		
		CStringPrintf (Buffer.get () , Format , std::forward <TVars> (Arguments)...);
		
		// Asignaremos el nuevo string con la memoria contenida.
		
		Output = std::move (std::string (Buffer.get ()));
		
		// Liberamos la memoria respectiva;
		
		// delete [] (Buffer);
		
		// -----------------------------------------------------------------------------
		
	}
	catch (...) {
		
		// Algún error ocurrió.
		
	}
	
	// -----------------------------------------------------------------------------
	
	// Finalmente devolvemos el resultado.
	
	return Output;
	
}

/// @}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		Enmascaramiento
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

/// ----------------------------------------------------------------------------
/// 
/// @name Enmascaramiento (String Mask)
/// 
/// @brief Conjunto de funciones para el ocultamiento/enmascaramiento de cadenas mediante simbolos especificados para poder ocultar información confidencial.
/// 
/// @details
/// 
/// Se define un conjunto de funciones para ocultar una cadena con cualquier tipo de simbolo , esto con la finalidad de que no se muestre una cadena con información
/// delicada y privada como por ejemplo una password , un pinblock , etc.
/// 
/// Se tiene el siguiente ejemplo para mostrar el uso de la misma.
/// @code{.cpp}
/// 	
/// 	// Crearemos la cadena enmascarada desde el centro hasta un total de 8 caracteres.
/// 	
/// 	const std::string MaskedString (StringMask ("Cadena de ejemplo" , 8 , '*'));
/// 	
/// 	// MaskedString = "Cade********emplo"
/// 
/// @endcode
/// 
/// Ahora las funciones que se tienen son las siguientes :
/// 
/// <h2 class="groupheader">Funciones</h2>
/// 
/// @{
/// 
// -----------------------------------------------------------------------------

// Declaramos entonces las plantillas de función para enmascarar (ocultar) una cadena con algún elemento simbolico.

// -----------------------------------------------------------------------------
// 
// RM : 	10/05/2024		Definición de la función para ocultar una cadena completa con un determinado tipo de simbolo.
// 							
// -----------------------------------------------------------------------------

/// @brief Enmascara toda una cadena utilizando un determinado caracter para sustituir en toda la cadena , pudiendo tener la opción de
/// respaldo con el parametro back si es diferente a Null.
/// @param[out] 		Buffer 			Cadena en la cual ocultar información.
/// @param 				BufferSize 		Tamaño del buffer en bytes.
/// @param 				Symbol 			Simbolo para ocultar.
/// @param[out]			BufferBackup 	Memoria en la cual respaldar la información (opcional).
/// 
/// @details
/// Se realiza la ocultación de toda la cadena completamente con todos los simbolos especificados en el parametro <b class="paramname">Symbol</b>.
/// 
/// @warning
/// Si <b class="paramname">BufferBackup</b> es distinto a nullptr entonces se almacena el respaldo , la memoría utilizada tuvo que ser repartida anteriormente
/// con algun gestionador de memoria (new , malloc , etc).

template <typename TBuffer>
TBuffer * CStringMask (TBuffer *  const Buffer , int BufferSize , const char Symbol = '*' , TBuffer *  const BufferBackup = nullptr) {
	
	// Validaremos si el buffer de respaldo es true para poder copiar entonces el buffer fuente.
	
	if (BufferBackup) {
		
		// Respaldamos el buffer en el respaldo para poder tener una copia de seguridad del mensaje original.
		
		CStringCpy (BufferBackup , Buffer);
		
		// -----------------------------------------------------------------------------
		
	}
	
	// -----------------------------------------------------------------------------
	
	// Ahora llenaremos el buffer original con los simbolos que se especificarón dejando un byte para el terminador.
	
	memset (Buffer , static_cast <int> (Symbol) , (BufferSize - 1));
	
	// -----------------------------------------------------------------------------
	
	// Devolvemos el buffer de salida.
	
	return Buffer;
	
}

// -----------------------------------------------------------------------------
// 
// RM : 	10/05/2024		Definición de la función para ocultar una cadena completa con un determinado tipo de simbolo.
// 							
// -----------------------------------------------------------------------------

/// @brief Enmascara toda una cadena utilizando un determinado caracter para sustituir en toda la cadena , pudiendo tener la opción de
/// respaldo con el parametro back si es diferente a Null.
/// @param[out] 	Buffer 			Cadena en la cual ocultar información.
/// @param 			BufferSize 		Tamaño del buffer en bytes.
/// @param 			Umbral 			Cantidad de elementos a ocultar desde el centro.
/// @param 			Symbol 			Simbolo para ocultar.
/// @param[out] 	BufferBackup 	Memoria en la cual respaldar la información (opcional).
/// 
/// @details
/// Se realiza el enmascaramiento de toda la cadena de entrada propuesta , ocultando hasta una cantidad determinada de caracteres igual al valor que tiene
/// el parametro <b class="paramname">Umbral</b> y si opcionalmente el parametro <b class="paramname">BufferBackup</b> es distinto a nullptr entonces se
/// almacena la Cadena original en el buffer.
/// 
/// @note
/// Oculta la cadena de buffer con los simbolos especificados , desde el centro hacia los costados la cantida determinada por <b class="paramname">Umbral</b>. Siendo
/// este un valor mayor a 0 para poder ocultar algo.
/// 
/// @warning
/// Si <b class="paramname">BufferBackup</b> es distinto a nullptr entonces se almacena el respaldo , la memoría utilizada tuvo que ser repartida anteriormente
/// con algun gestionador de memoria (new , malloc , etc).

// Declaramos y definiremos la función para poder realizar el enmascaramiento.

template <typename TBuffer>
TBuffer * CStringMask (TBuffer *  const Buffer , int BufferSize , int Umbral , const char Symbol = '*' , TBuffer *  const BufferBackup = nullptr) {
	
	// Validaremos si el buffer de respaldo es true para poder copiar entonces el buffer fuente.
	
	if (BufferBackup) {
		
		// Respaldamos el buffer en el respaldo para poder tener una copia de seguridad del mensaje original.
		
		CStringCpy (BufferBackup , Buffer);
		
		// -----------------------------------------------------------------------------
		
	}
	
	// -----------------------------------------------------------------------------
	// 
	// 							ENMASCARAMIENTO STRING
	// 							
	// -----------------------------------------------------------------------------
	
	// Ahora se limita al size de la cadena valido.
	
	BufferSize = (std::min (BufferSize , static_cast <decltype (BufferSize)> (strlen (Buffer) + 1)));
	
	// -----------------------------------------------------------------------------
	
	// Para continuar hace falta validar que el Umbral no sea mayor a la cantidad de elementos en el buffer sin contar el terminador.
	
	if (Umbral <= (BufferSize - 1)) {
		
		// A partir del tamaño del buffer tenemos que determinar la cantidad de valores que se ocultarán a partir del centro y dejando
		// a los costados elementos sin ocultar , por lo que obtenemos el indice origen para a partir de ahi determinar donde comenzar
		// a enmascarar.
		
		int Origen = ((BufferSize - 1) / 2) - (Umbral / 2);
		
		// Iteramos por cada uno de los elementos a partir del Origen hasta la cantidad de elementos (Umbral) ocultar , se irán anexando
		// los simbolos especificados.
		
		for (int Indice = Origen ; Indice < (Origen + Umbral) ; ++ Indice) {
			
			// Ocultamos este valor de la cadena.
			
			Buffer [Indice] = Symbol;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
		
	}
	
	// -----------------------------------------------------------------------------
	
	// Devolvemos el buffer de salida.
	
	return Buffer;
	
}

// Ahora tenemos una implementación para una cadena de string para c++ de igual forma con los parametros especificos.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Enmascara una cadena determinada utilizando una cantidad de caracteres a ocultar por el Umbral y el Simbolo a utilizar.
///
/// @param[in]  Input   Cadena de entrada a ocultar.
/// @param  	Umbral  Cantidad de simbolos a ocultar desde el centro hacia los extremos de la cadena.
/// @param  	Symbol  Simbolo a utilizar para intercambio de caracter.
///
/// @tparam     TChar   Tipo de Caracter a utilizar.
///
/// @return     Cadena std con los valores de la entrada enmascarados con el umbral especificado y el simbolo de intercambio.
/// 
// -----------------------------------------------------------------------------

template <typename TChar>
std::basic_string <TChar> StringMask (const std::basic_string <TChar> & Input , int Umbral , const char Symbol = '*') {
	
	// Lo que haremos será crear una nueva cadena con la copia de nuestro INPUT actual.
	
	std::basic_string <TChar> Output (Input);
	
	// Ahora lo que haremos será invocar a nuestra función para ocultamiento con los parametros especificos.
	
	CStringMask (Output.data () , (Output.size () + 1u) , Umbral , Symbol);
	
	// -----------------------------------------------------------------------------
	
	// Finalmente devolvemos la cadena.
	
	return Output;
	
}

/// ----------------------------------------------------------------------------
/// 
/// @brief      Enmascara una cadena determinada utilizando una cantidad de caracteres a ocultar por el Umbral y el Simbolo a utilizar.
///
/// @param[in]  	Input   Cadena de entrada a ocultar (c-string).
/// @param  		Umbral  Cantidad de simbolos a ocultar desde el centro hacia los extremos de la cadena.
/// @param  		Symbol  Simbolo a utilizar para intercambio de caracter.
///
/// @return     Cadena std con los valores de la entrada enmascarados con el umbral especificado y el simbolo de intercambio.
/// 
// -----------------------------------------------------------------------------

// Ahora una implementacipon con un const char en linea para parametrizar.

ALWAYS_INLINE std::string StringMask (const char * const Input , int Umbral , const char Symbol = '*') {
	
	// Devolvemos la llamada a la función anterior.
	
	return StringMask (std::string (Input) , Umbral , Symbol);
	
	// -----------------------------------------------------------------------------
	
}

/// @}
/// @}

// Ahora la implementación del operador Mask

// -----------------------------------------------------------------------------
// 
// 							OPERADOR MASK
// 							
// -----------------------------------------------------------------------------

// Estableceremos un espacio en linea para guardar los operadores especificos de las utilerias.

/// 
/// @ingroup Operadores
/// @defgroup UtilOperators Operadores Predefinidos
/// 
/// @brief Conjunto de operadores predefinidos para poderlos utilizar en combinación con la sintaxis <Operator>.
/// 
/// @details
/// 
/// Este conjunto de operadores están diseñados para utilizarse en combinación mediante la sintaxis especial de operadores < y >. Por ejemplo tendriamos
/// un ejemplo con un caso para manejo de cadenas mediante estas operaciones.
/// 
/// <b style="font-size: 19px">Ejemplo :</b>
/// 
/// @code{.cpp}
/// 
/// 	// Declaramos nuestra cadena de ejemplo.
/// 	
/// 	const std::string Cadena ("Esta cadena es un Ejemplo  ");
/// 	
/// 	// Quitaremos el sobrante derecho de espacios y la llenamos con simbolos '>' a la izquierda hasta completar 30.
/// 	
/// 	const auto Result = Cadena <RTrim> TRIM_ESPACIOS <LPad <'>'>> 30;
/// 	
/// 	// Result = ">>>>>ESTA CADENA ES UN EJEMPLO"
/// 
/// @endcode
/// 

/// 
/// @addtogroup UtilOperators
/// @{
/// 

/// 
/// @brief Espacio de nombres que contiene una serie de Operadores Nombrados pre-definidos para su utilización directa.
/// 
/// @details
/// 
/// Se incluye una serie de implementaciones de operadores de sintaxis <operador> para poderlos utilizar , estas implementaciones incluyen en general
/// los siguientes operadores y sus funciones.
/// 
/// <ul>
/// 	<li>Mask : Enmascaramiento</li>
/// 	<li>Trim : Recorte de Strings</li>
/// 	<li>L/RPad : Padding a la derecha o izquierda de un String</li>
/// </ul>
/// 

inline namespace UtilityOperators {
	
	/// 
	/// @addtogroup UtilOperators
	/// @{
	/// 
	
	// Implementaremos una función que realiza el enmascarado con el umbral especifico mediante simbolos *.
	
	/// @cond OperatorInternal
	
	ALWAYS_INLINE std::string OperatorMask (const std::string & Input , int Umbral) {
		
		// Devolvemos la respuesta de aplicar el enmascarado respectivo.
		
		return ::StringMask (Input , Umbral);
		
		// -----------------------------------------------------------------------------
		
	}
	
	/// @endcond
	
	// Definiremos el operador especifico para el enmascaramiento respectivo.
	
	/// 
	/// @brief Operador <Mask> para aplicar función de enmascaramiento a cadenas std. Utiliza el valor de Simbolo '*'
	/// 
	/// @param "CADENA A ESNMASCARAR" <Mask> UMBRAL
	/// 
	/// @details
	/// Realiza el enmascaramiento mediante el uso del operador <Mask> . Ejemplo :
	/// @code{.cpp}
	/// 
	/// 	const auto MaskedString = "Cadena a Enmascarar" <Mask> 10;
	/// 	
	/// 	// Result : Cade**********carar
	/// 	
	/// @endcode
	/// 	
	/// @note Por default utiliza el simbolo '*' para enmascarar la cadena.
	/// 
	
	inline auto Mask = MakeNamedOperator (OperatorMask);
	
	// Ahora una template para poder establecer el simbolo enmascarador.
	
	/// 
	/// @brief Operador <SMask> para aplicar función de enmascaramiento a cadenas std con un determinado simbolo.
	/// 
	/// @param "CADENA A ESNMASCARAR" <SMask <<span class="charliteral">'SYMBOL'</span>>> <span class="paramname">UMBRAL</span>
	/// 
	/// @details
	/// Realiza el enmascaramiento mediante el uso del operador <SMask> utilizando el <b>simbolo enmascarador</b> que se especifique. Ejemplo :
	/// @code{.cpp}
	/// 
	/// 	const auto MaskedString = "Cadena a Enmascarar" <SMask <'$'>> 10;
	/// 	
	/// 	// Result : Cade$$$$$$$$$$carar
	/// 	
	/// @endcode
	/// 
	
	template <char Symbol = '*'>
	inline auto SMask = MakeNamedOperator (std::bind (StringMask <char> , std::placeholders::_1 , std::placeholders::_2 , Symbol));
	
	/// @}
	
	// -----------------------------------------------------------------------------
	
}

/// @}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																	UPPERCASE & LOWECASE
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Ahora con las funciones para poder convertir las cadenas a mayusculas o minusculas.

// -----------------------------------------------------------------------------
/// @addtogroup Utilerias
/// @{
// -----------------------------------------------------------------------------

/// ----------------------------------------------------------------------------
/// 
/// @name Upper/Lower Case Strings
/// 
/// @brief Funciones para pasar a UpperCase o LowerCase cualquier cadena.
/// 
/// @details
/// 
/// Tendremos un par de funciones que realiza la conversión respectiva de una cadena de entrada a una cadena con 
/// todos los caracteres en mayusculas o minusculas respectivamente para poder comparar de manera igual.
/// 
/// 
/// Las funciones son las siguientes :
/// 
/// <h2 class="groupheader">Funciones</h2>
/// 
/// @{
/// 
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Implementaremos la siguiente función para la asignación de Upper a todo un string mediante cambio de cada simbolo en el array.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Convierte toda la cadena a mayusculas. Cada caracter convertible , el resto se queda igual al original.
///
/// @param[in]  Input  Cadena de entrada a colocar en mayusculas
///
/// @tparam     TChar  Tipo de caracter.
///
/// @return 	STD cadena con el resultado de pasar toda la cadena de entrada a mayusculas.
///
/// @details     Pasa todos los caracteres a mayusculas sobre la cadena y obtiene una copia de la cadena resultante.
/// 
// -----------------------------------------------------------------------------

template <typename TChar>
std::basic_string <TChar> ToUpper (const std::basic_string <TChar> & Input) {
	
	// -----------------------------------------------------------------------------
	// 
	// 							TO UPPER CASE
	// 							
	// -----------------------------------------------------------------------------
	
	// Creaermos una copia con el resultado de nuestra entrada.
	
	std::basic_string <TChar> Output (Input);
	
	// Iteramos por cada caracter en el respectivo string de cadena y vamos a convertir cada caracter a mayusculas.
	
	for (auto & Caracter : Output) {
		
		// Asignaremos el respectivo equivalente de nuestro caracter.
		
		Caracter = static_cast <char> (toupper (static_cast <int> (Caracter)));
		
		// -----------------------------------------------------------------------------
		
	}
	
	// -----------------------------------------------------------------------------
	
	// Devolvemos el resultado repectivo.
	
	return Output;
	
}

/// ----------------------------------------------------------------------------
/// 
/// @brief      Convierte toda la cadena a mayusculas. Cada caracter convertible , el resto se queda igual al original.
///
/// @param[in]  Input  Cadena de entrada a colocar en mayusculas , mediante c-style string.
///
/// @tparam     TChar  Tipo de caracter.
///
/// @return 	STD cadena con el resultado de pasar toda la cadena de entrada a mayusculas.
///
/// @details     Pasa todos los caracteres a mayusculas sobre la cadena y obtiene una copia de la cadena resultante.
/// 
// -----------------------------------------------------------------------------

// Ahora una especialización para un const char que se quiera pasar a upper.

ALWAYS_INLINE std::string ToUpper (const char * const Input) {
	
	// Devolvemos el resultado de la conversión anterior.
	
	return ToUpper (std::string (Input));
	
	// -----------------------------------------------------------------------------
	
}

// Implementaremos la siguiente función para la asignación de Lower a todo un string mediante cambio de cada simbolo en el array.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Convierte toda la cadena a minusculas. Cada caracter convertible , el resto se queda igual al original.
///
/// @param[in]  Input  Cadena de entrada a colocar en minusculas
///
/// @tparam     TChar  Tipo de caracter.
/// 
/// @return 	STD cadena con el resultado de pasar toda la cadena de entrada a minusculas.
///
/// @details     Pasa todos los caracteres a minusculas sobre la cadena y obtiene una copia de la cadena resultante.
/// 
// -----------------------------------------------------------------------------

template <typename TChar>
std::basic_string <TChar> ToLower (const std::basic_string <TChar> & Input) {
	
	// -----------------------------------------------------------------------------
	// 
	// 							TO LOWER CASE
	// 							
	// -----------------------------------------------------------------------------
	
	// Creaermos una copia con el resultado de nuestra entrada.
	
	std::basic_string <TChar> Output (Input);
	
	// Iteramos por cada caracter en el respectivo string de cadena y vamos a convertir cada caracter a minusculas.
	
	for (auto & Caracter : Output) {
		
		// Asignaremos el respectivo equivalente de nuestro caracter.
		
		Caracter = static_cast <char> (tolower (static_cast <int> (Caracter)));
		
		// -----------------------------------------------------------------------------
		
	}
	
	// -----------------------------------------------------------------------------
	
	// Devolvemos el resultado repectivo.
	
	return Output;
	
}

/// ----------------------------------------------------------------------------
/// 
/// @brief      Convierte toda la cadena a minusculas. Cada caracter convertible , el resto se queda igual al original.
///
/// @param[in]  Input  Cadena de entrada a colocar en minusculas mediante c-style const char.
///
/// @tparam     TChar  Tipo de caracter.
///
/// @return 	STD cadena con el resultado de pasar toda la cadena de entrada a minusculas.
///
/// @details     Pasa todos los caracteres a minusculas sobre la cadena y obtiene una copia de la cadena resultante.
/// 
// -----------------------------------------------------------------------------

// Ahora una especialización para un const char que se quiera pasar a upper.

ALWAYS_INLINE std::string ToLower (const char * const Input) {
	
	// Devolvemos el resultado de la conversión anterior.
	
	return ToLower (std::string (Input));
	
	// -----------------------------------------------------------------------------
	
}

/// @}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																	ENCODE/DECODE BASE 64
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Añadiremos una función para realizar la codificación base 64.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Codificador Base64 para una cadena de entrada.
///
/// @param[in]  Input  Cadena de entrada a Codificar en Base64.
/// 
/// @tparam 	TChar  Tipo de Caracter utilizado para el basic_string. (Por defecto es char).
///
/// @return     STD cadena codificada mediante el algoritmo para base 64.
/// 
/// @details
/// 
/// Este simple algoritmo realiza la codificación de una cadena de texto , a una cadena en base 64.
/// 
// -----------------------------------------------------------------------------

template <typename TChar = char>
std::basic_string <TChar> Base64Encode (const std::basic_string <TChar> & Input) {
	
	// -----------------------------------------------------------------------------
	// 
	// 							Tabla de Codificación.
	// 							
	// -----------------------------------------------------------------------------
	
	// Tenemos la tabla para codificar a base 64 que nos permitirá tener todos los simbolos permitidos.
	
	static constexpr TChar TablaEncode [] = {
		
		// Tenemos la tabla con todos los caracteres que se involucran en base 64.
		
		// -----------------------------------------------------------------------------
		
		'A' , 'B' , 'C' , 'D' , 'E' , 'F' , 'G' , 'H' ,
		'I' , 'J' , 'K' , 'L' , 'M' , 'N' , 'O' , 'P' ,
		'Q' , 'R' , 'S' , 'T' , 'U' , 'V' , 'W' , 'X' ,
		'Y' , 'Z' , 'a' , 'b' , 'c' , 'd' , 'e' , 'f' ,
		'g' , 'h' , 'i' , 'j' , 'k' , 'l' , 'm' , 'n' ,
		'o' , 'p' , 'q' , 'r' , 's' , 't' , 'u' , 'v' ,
		'w' , 'x' , 'y' , 'z' , '0' , '1' , '2' , '3' ,
		'4' , '5' , '6' , '7' , '8' , '9' , '+' , '/'
		
		// -----------------------------------------------------------------------------
		
    };
    
    // -----------------------------------------------------------------------------
    
    // Obtenemos la cantidad de caracteres de la entrada.
    
    const size_t LenghtInput = Input.size ();
    
    // Ahora con este valor calculamos la cantidad de caracteres para la salida con la formula :
    //		Salida = 4 * ((Input + 2) / 3)
    
	const size_t LenghtOutput = 4 * ((LenghtInput + 2) / 3);
	
	// Crearemos nuestro string de salida para tenerlo de momento en 0.
	
	std::basic_string <TChar> Output (LenghtOutput , '\0');
	
	// -----------------------------------------------------------------------------
	
	// Obtememos la información de nuestra cadena de salida para iterar.
	
	TChar * Data = Output.data ();
	
	// Tenemos ahora el indice para iterar por cada elemento.
	
	int Indice = 0;
	
	// Mediante el siguiente ciclo asignaremos los valores respectivos.
	
	for (Indice ; Indice < (LenghtInput - 2) ; Indice += 3) {
		
		// Aplicamos el algoritmo para asignar los siguientes 4 elementos en el resultado.
		
		*(Data ++) = TablaEncode [(Input [Indice] >> 2) & 0x3F];
		*(Data ++) = TablaEncode [((Input [Indice] & 0x3) << 4) 	| ((int) (Input [Indice + 1] & 0xF0) >> 4)];
		*(Data ++) = TablaEncode [((Input [Indice + 1] & 0xF) << 2) | ((int) (Input [Indice + 2] & 0xC0) >> 6)];
		*(Data ++) = TablaEncode [Input [Indice + 2] & 0x3F];
		
		// -----------------------------------------------------------------------------
		
	}
	
	// Ahora tenemos la siguiente validación.
	
	if (Indice < LenghtInput) {
		
		// -----------------------------------------------------------------------------
		
		// Asignaremos el siguiente valor de la tabla.
		
		*(Data ++) = TablaEncode [(Input [Indice] >> 2) & 0x3F];
		
		// Validamos si el indice ya es igual a la longitud de la entrada - 1.
		
		if (Indice == (LenghtInput - 1)) {
			
			// Asignaremos el siguiente valor.
			
			*(Data ++) = TablaEncode [((Input [Indice] & 0x3) << 4)];
			
			// Asignaremos finalmente el simbolo '='.
			
			*(Data ++) = '=';
			
			// -----------------------------------------------------------------------------
			
		}
		else {
			
			// -----------------------------------------------------------------------------
			
			// Ahora asignaremos el siguiente valor.
			
			*Data++ = TablaEncode [((Input [Indice] & 0x3) << 4) | ((int) (Input [Indice + 1] & 0xF0) >> 4)];
			
			// Asignaremos otro dato adicional a la cadena.
			
			*Data++ = TablaEncode [((Input [Indice + 1] & 0xF) << 2)];
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Por ultimo anexamos el simbolo '=' a nuestro resultado.
		
		*(Data ++) = '=';
		
	}
	
	// -----------------------------------------------------------------------------
	
	// Ahora solamente devolvemos la salida.
	
    return Output;
    
}

// De la misma manera tenemos la función para decodificar base 64.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Decodificador Base64 para una cadena de entrada.
///
/// @param[in]  Input  Cadena de entrada a Decodificar en Base64.
/// 
/// @tparam 	TChar  Tipo de Caracter utilizado para el basic_string. (Por defecto es char).
///
/// @return     STD cadena decodificada mediante el algoritmo para base 64.
/// 
/// @details
/// 
/// Este simple algoritmo realiza el parseo de una cadena de texto que está codificada en base 64 a una cadena resultante que puede ser leída de manera
/// normal. @see Base64Encode
/// 
// -----------------------------------------------------------------------------

template <typename TChar = char>
std::basic_string <TChar> Base64Decode (const std::basic_string <TChar> & Input) {
	
	// -----------------------------------------------------------------------------
	// 
	// 							Tabla de Decodificación
	// 							
	// -----------------------------------------------------------------------------
	
	// Declaramos nuestra tabla auxiliar que nos permitirá decodificar.
	
	static constexpr uint8_t TablaDecode [] = {
		
		// Declaramos todos los valores para nuestra tabla decodificadora.
		
		// -----------------------------------------------------------------------------
		
		64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 ,
		64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 ,
		64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 62 , 64 , 64 , 64 , 63 ,
		52 , 53 , 54 , 55 , 56 , 57 , 58 , 59 , 60 , 61 , 64 , 64 , 64 , 64 , 64 , 64 ,
		64 ,  0 ,  1 ,  2 ,  3 ,  4 ,  5 ,  6 ,  7 ,  8 ,  9 , 10 , 11 , 12 , 13 , 14 ,
		15 , 16 , 17 , 18 , 19 , 20 , 21 , 22 , 23 , 24 , 25 , 64 , 64 , 64 , 64 , 64 ,
		64 , 26 , 27 , 28 , 29 , 30 , 31 , 32 , 33 , 34 , 35 , 36 , 37 , 38 , 39 , 40 ,
		41 , 42 , 43 , 44 , 45 , 46 , 47 , 48 , 49 , 50 , 51 , 64 , 64 , 64 , 64 , 64 ,
		64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 ,
		64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 ,
		64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 ,
		64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 ,
		64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 ,
		64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 ,
		64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 ,
		64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 , 64
		
		// -----------------------------------------------------------------------------
		
	};
	
	// -----------------------------------------------------------------------------
	
	// Ahora obtendremos la cantidad de caracteres en la entrada que tenemos.
	
	size_t LenghtInput = Input.size ();
	
	// -----------------------------------------------------------------------------
	
	// Para continuar requerimos que el número de letras sea multiplo de 4.
	
	if ((LenghtInput % 4) == 0) {
		
		// -----------------------------------------------------------------------------
		// 
		// 							Decodificando.
		// 							
		// -----------------------------------------------------------------------------
		
		// Declaramos el tamaño tentativo para la salida decodificada.
		
		size_t LengthOutput = LenghtInput / 4 * 3;
		
		// Si se tiene el simbolo '=' en los ultimos caracteres de nuestra entrada entonces los quitaremos para el resultado.
		
		if (Input [LenghtInput - 1] == '=') { -- LengthOutput; }
		if (Input [LenghtInput - 2] == '=') { -- LengthOutput; }
		
		// -----------------------------------------------------------------------------
		
		// Crearemos la cadena resultado decodificada con la cantidad determinada de caracteres , inicializados en 0.
		
		std::basic_string <TChar> Output (LengthOutput , '\0');
		
		// Comenzaremos con la iteración de todos los elementos , declaramos e iniciamos dos indices.
		
		for (size_t Indice = 0 , Indice_2 = 0 ; Indice < LenghtInput ; ) {
			
			// -----------------------------------------------------------------------------
			
			// Ahora conforme a la formula general realizaremos la asignación de los valores A , B , C y D conforme la tabla
			// de decodificación que tenemos.
			
			uint32_t A = ((Input [Indice] == '=') ? (0 & (Indice ++)) : (TablaDecode [static_cast <int> (Input [Indice ++])]));
			uint32_t B = ((Input [Indice] == '=') ? (0 & (Indice ++)) : (TablaDecode [static_cast <int> (Input [Indice ++])]));
			uint32_t C = ((Input [Indice] == '=') ? (0 & (Indice ++)) : (TablaDecode [static_cast <int> (Input [Indice ++])]));
			uint32_t D = ((Input [Indice] == '=') ? (0 & (Indice ++)) : (TablaDecode [static_cast <int> (Input [Indice ++])]));
			
			// Crearemos nuestro numero de 4 bytes a partir de estos 4 elementos obtenidos desde la tabla de decodificación y los desplazamos
			// la cantidad de digitos indicados.
			
			uint32_t Triple = ((A << 3 * 6) + (B << 2 * 6) + (C << 1 * 6) + (D << 0 * 6));
			
			// -----------------------------------------------------------------------------
			
			// Validamos si el Indice 2 es menor a la longitud de la cadena resultante decodificada para anexar algunos elementos.
			
			if (Indice_2 < LengthOutput) { Output [Indice_2 ++] = (Triple >> 2 * 8) & 0xFF; }
			if (Indice_2 < LengthOutput) { Output [Indice_2 ++] = (Triple >> 1 * 8) & 0xFF; }
			if (Indice_2 < LengthOutput) { Output [Indice_2 ++] = (Triple >> 0 * 8) & 0xFF; }
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
		
		// Finalmente devolvemos el resultado.
		
		return Output;
		
	}
    
    // -----------------------------------------------------------------------------
    
	return std::string ();
	
}

// Ahora tendremos algunas funciones para llenar y Reemplazar Letras en cadenas de String.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																FILL & REPLACE STRING
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

/// ----------------------------------------------------------------------------
/// 
/// @name Fill y Replace Strings
/// 
/// @brief Funciones para rellenar cadenas o reemplazar los caracteres dentro de las mismas.
/// 
/// @details
/// 
/// Por medio de funciones como @ref LFillString es posible rellenar una cadena con una determinada cantidad de simbolos los cuales pueden ser especificados
/// mediante el parametro adecuado. Asi mismo también es posible reemplazar cadenas y sustituir las letras que se desee por cualquier otra letra o incluso
/// poder quitar la letra completa de la cadena. Observando el siguiente ejemplo :
/// @code{.cpp}
/// 
/// 	// Crearemos una cadena rellena con 6 ceros a la izquierda y reemplazamos lo puntos por commas.
/// 	
/// 	const std::string Result = LFillString (ReplacingString ("1000.40" , '.' , ',') , 6 , '0');
/// 	
/// 	// Result = 0000001000,40
/// 
/// @endcode
/// 
/// Las funciones en esta sección son las siguientes. 
/// 
/// <h2 class="groupheader">Funciones</h2>
/// 
/// @{
/// 
// -----------------------------------------------------------------------------

// Tenemos una pequeña función de ayuda que permite llenar a la Izquierda con un determinado simbolo la cadena establecida.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Rellena a la Izquierda la cadena de entrada con la cantidad N de Simbolos.
///
/// @param[in]  Input  	Cadena a rellenar.
/// @param 		Number 	Cantidad de Simbolos a concatenar.
/// @param 		Symbol 	Caracter a repetir N-veces y anexar a la cadena.
///
/// @return     Cadena de entrada con la concatenación de los Symbolos hasta el número establecido por la parte de la izquierda de la cadena.
/// 
/// @details
/// 
/// Concatena a la cadena resultante todos los Symbol que sean necesarios hasta Number.
/// 
// -----------------------------------------------------------------------------

template <typename TChar = char>
ALWAYS_INLINE std::basic_string <TChar> LFillString (const std::basic_string <TChar> & Input , size_t Number , TChar Symbol = '0') {
	
	// -----------------------------------------------------------------------------
	// 
	// 							RELLENAR IZQUIERDA SIMBOLOS
	// 							
	// -----------------------------------------------------------------------------
	
	// Crearemos un string con el número de simbolos a rellenar y devolvemos la concatenación de ambos strings.
		
	return (std::basic_string <TChar> (Number , Symbol) + Input);
	
	// -----------------------------------------------------------------------------
	
}

// De igual forma tenemos una sobrecarga para const char *.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Rellena a la Izquierda la cadena de entrada con la cantidad N de Simbolos.
///
/// @param[in]  Input  	Cadena a rellenar c-style string.
/// @param 		Number 	Cantidad de Simbolos a concatenar.
/// @param 		Symbol 	Caracter a repetir N-veces y anexar a la cadena.
///
/// @return     Cadena de entrada con la concatenación de los Symbolos hasta el número establecido por la parte de la izquierda de la cadena.
/// 
/// @details
/// 
/// Concatena a la cadena resultante todos los Symbol que sean necesarios hasta Number.
/// 
// -----------------------------------------------------------------------------

ALWAYS_INLINE std::string LFillString (const char * const Input , size_t Number , char Symbol = '0') {
	
	// Devolvemos la cadena respectiva.
	
	return (std::string (Number , Symbol) + Input);
	
	// -----------------------------------------------------------------------------
	
}

// Tenemos una pequeña función de ayuda que permite llenar a la Derecha con un determinado simbolo la cadena establecida.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Rellena a la Derecha la cadena de entrada con la cantidad N de Simbolos.
///
/// @param[in]  Input  	Cadena a rellenar.
/// @param 		Number 	Cantidad de Simbolos a concatenar.
/// @param 		Symbol 	Caracter a repetir N-veces y anexar a la cadena.
///
/// @return     Cadena de entrada con la concatenación de los Symbolos hasta el número establecido por la parte de la derecha de la cadena.
/// 
/// @details
/// 
/// Concatena a la cadena resultante todos los Symbol que sean necesarios hasta Number.
/// 
// -----------------------------------------------------------------------------

template <typename TChar = char>
ALWAYS_INLINE std::basic_string <TChar> RFillString (const std::basic_string <TChar> & Input , size_t Number , TChar Symbol = '0') {
	
	// -----------------------------------------------------------------------------
	// 
	// 							RELLENAR DERECHA SIMBOLOS
	// 							
	// -----------------------------------------------------------------------------
	
	// Crearemos un string con todos los valores a rellenar y devolvemos la concatenación de dichos simbolos.
	
	return (Input + std::basic_string <TChar> (Number , Symbol));
	
	// -----------------------------------------------------------------------------
	
}

/// ----------------------------------------------------------------------------
/// 
/// @brief      Rellena a la Derecha la cadena de entrada con la cantidad N de Simbolos.
///
/// @param[in]  Input  	Cadena a rellenar c-style string.
/// @param 		Number 	Cantidad de Simbolos a concatenar.
/// @param 		Symbol 	Caracter a repetir N-veces y anexar a la cadena.
///
/// @return     Cadena de entrada con la concatenación de los Symbolos hasta el número establecido por la parte de la derecha de la cadena.
/// 
/// @details
/// 
/// Concatena a la cadena resultante todos los Symbol que sean necesarios hasta Number.
/// 
// -----------------------------------------------------------------------------

// Ahora para el caso de la derecha.

ALWAYS_INLINE std::string RFillString (const char * const Input , size_t Number , char Symbol = '0') {
	
	// Devolvemos la cadena respectiva.
	
	return (std::string (Input) + std::string (Number , Symbol));
	
	// -----------------------------------------------------------------------------
	
}

// -----------------------------------------------------------------------------

// Tenemos primero nuestro reemplazador para todas los caracteres (elementos) que cumplan con determinada condición establecida.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Reemplaza todos los carácteres de la cadena Input que cumplan <b>Una condición Establecida</b> por medio de una función.
///
/// @param[in]  Input  		Cadena de entrada a modificar.
/// @param[in]  Condition 	Función que determina si el caracter debe reemplazarse.
/// @param[in]  S_New 		Nuevo Caracter a Colocar.
///
/// @tparam     TFunction  	Tipo de Función Predicado para válidar qué reemplazar (Función Objeto , lambda , metodo , etc).
/// @tparam     TChar  		Tipo de Caracter para el tipo de cadena utilizado (por defecto es char).
///
/// @return     Nueva cadena STD con todos los carácteres espécificados reemplazados.
/// 
/// @details
/// Esta función permite reemplazar y también <b>eliminar</b> todos los caracteres que cumplan con una determinada condición establecida
/// con una función de <b>Predicado</b>.
/// 
/// @pre
/// La función <b class="paramname">Condition</b> debe devolver un valor convertible a bool para poder ser válida.
/// @note
/// Si el nuevo caracter <b class="paramname">S_New</b> se establece en <span class="charliteral">'\0'</span> entonces todas las letras encontradas serán eliminadas de la cadena.
/// 
// -----------------------------------------------------------------------------

template <typename TFunction , typename TChar = char>
requires requires (TFunction Condition) {
	
	// Es requerido que la expresión siguiente sea válida para el predicado.
	
	{ Condition (TChar ()) } -> std::convertible_to <bool>;
	
	// -----------------------------------------------------------------------------
	
}
std::basic_string <TChar> ReplacingStringIf (const std::basic_string <TChar> & Input , TFunction Condition , TChar S_New) {
	
	// -----------------------------------------------------------------------------
	// 
	// 							REEMPLAZANDO SIMBOLOS
	// 							
	// -----------------------------------------------------------------------------
	
	// Crearemos un string con la copia de nuestra entrada.
	
	std::basic_string <TChar> Output (Input);
	
	// Si el caracter a sustituir es el '\0' entonces removemos.
	
	if (S_New == '\0') {
		
		// Buscaremos eliminar todos los caracteres.
		
		Output.erase (std::remove_if (Output.begin () , Output.end () , Condition) , Output.end ());
		
		// -----------------------------------------------------------------------------
		
	}
	else {
		
		// Ahora vamos a iterar por todo el String y reemplazar donde corresponda.
		
		for (TChar & CurrentChar : Output) {
			
			// Si el valor actual cumple la condición entonces lo reemplazaremos.
			
			if (Condition (CurrentChar)) {
				
				// Asignaremos el nuevo caracter de reemplazdo.
				
				CurrentChar = S_New;
				
				// -----------------------------------------------------------------------------
				
			}
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
		
	}
	
	// -----------------------------------------------------------------------------
	
	// Devolvemos el resultado.
	
	return Output;
	
}

// Por otro lado para poder reemplazar todas las ocurrencias de un determinado simbolo por otro simbolo distinto.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Reemplaza todas las coincidencias de un carácter en especifico dentro de la cadena de entrada por otro carácter especificado.
///
/// @param[in]  Input  Cadena de entrada a modificar.
/// @param[in]  S_Old  Caracter a Reemplazar.
/// @param[in]  S_New  Nuevo Caracter a Colocar.
///
/// @tparam     TChar  Tipo de Caracter para el tipo de cadena utilizado (por defecto es char).
///
/// @return     Nueva cadena STD con todos los carácteres espécificados reemplazados.
/// 
/// @details
/// Esta función permite reemplazar y también <b>eliminar</b> todas las ocurrencias de un determinado caracter en la cadena de entrada.
/// 
/// @note
/// Si el nuevo caracter <b class="paramname">S_New</b> se establece en <span class="charliteral">'\0'</span> entonces todas las letras encontradas serán eliminadas de la cadena.
/// 
// -----------------------------------------------------------------------------

template <typename TChar = char>
ALWAYS_INLINE std::basic_string <TChar> ReplacingString (const std::basic_string <TChar> & Input , 
                                                                                      TChar S_Old , TChar S_New) {
	
	// Devolvemos la cadena respectiva aplicando el reemplazo con la condición de ser iguales.
	
	return ReplacingStringIf (std::string (Input) , [S_Old] (TChar Simbolo) -> bool {
		
		// True si es igual al caracter a reemplazar.
		
		return (Simbolo == S_Old);
		
		// -----------------------------------------------------------------------------
		
	} , S_New);
	
	// -----------------------------------------------------------------------------
	
}

// Implementamos el reemplazador de cadenas con const char.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Reemplaza todas las coincidencias de un carácter en especifico dentro de la cadena de entrada por otro carácter especificado.
///
/// @param[in]  Input  Cadena de entrada a modificar C-Style.
/// @param[in]  S_Old  Caracter a Reemplazar.
/// @param[in]  S_New  Nuevo Caracter a Colocar.
///
/// @return     Nueva cadena STD con todos los carácteres espécificados reemplazados.
/// 
/// @details
/// Esta función permite reemplazar y también <b>eliminar</b> todas las ocurrencias de un determinado caracter en la cadena de entrada.
/// 
/// @note
/// Si el nuevo caracter <b class="paramname">S_New</b> se establece en <span class="charliteral">'\0'</span> entonces todas las letras encontradas serán eliminadas de la cadena.
/// 
// -----------------------------------------------------------------------------

ALWAYS_INLINE std::string ReplacingString (const char * const Input , char S_Old , char S_New) {
	
	// Devolvemos la cadena respectiva.
	
	return ReplacingString (std::string (Input) , S_Old , S_New);
	
	// -----------------------------------------------------------------------------
	
}

// Ahora para poder reemplazar multi strings.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Reemplaza todas las coincidencias de un "std::string" en el Input mediante un mapper (mapa / container).
/// que tenga valores de tipo pair / tuple o un unordered map.
///
/// @param[in]  Input  Cadena de entrada a modificar C-Style.
/// @param[in]  Mapper Contenedor con los valores en pareja (Old , New) para reemplazar en la cadena de entrada.
///
/// @return     Nueva cadena STD con todos los strings espécificados reemplazados.
/// 
/// @details
/// Esta función permite reemplazar todas las <b>Sub-Cadenas</b> que se le indiquen por medio de cualquier container. El mapper es el
/// conjunto de <b>Pairs</b> donde el primer valor indica el OLD value y el segundo establece el NEW value para cada string a buscar
/// y reemplazar en el Input establecido.
/// 
/// @note
/// La expresión y el tipo de dato (TContainer <TValues...>::value_type) debe ser <b>Un std::pair ó un std::tuple de 2 elementos ó más</b> los
/// cuales deben ser <b>Convertibles</b> al tipo de cadena ingresada.
/// 
// -----------------------------------------------------------------------------

template <template <typename , typename ...> typename TContainer , typename TChar = char , typename ... TValues>
requires IsValidContainer <TContainer , TValues ...> std::basic_string <TChar> ReplacingMultiString (const std::basic_string <TChar> & Input ,
                                                                                                     const TContainer <TValues ...> & Mapper) {
	
	// Se tiene un tipo de cadena resultado establecido.
	
	using TString = std::basic_string <TChar>;
	
	// Se tiene el tipo de dato del container actual.
	
	using TValue = typename ContainerType <TContainer , TValues ...>::value_type;
	
	// Se valida que el tipo de valor sea un pair (o una tupla) mediante el requerimiento siguiente.
	
	static constexpr bool IsValidPairValue = requires (const TValue & Value) {
		
		// Se valida que la expresión (std::get <0> (Value)) devuelva un valor convertible a TString.
		
		{ std::get <0> (Value) } -> std::convertible_to <TString>;
		
		// Se valida que la expresión (std::get <1> (Value)) devuelva un valor convertible a TString.
		
		{ std::get <1> (Value) } -> std::convertible_to <TString>;
		
		// -----------------------------------------------------------------------------
		
	};
	
	// Daremos un assert con esta validación.
	
	static_assert (IsValidPairValue , "TValue (value_type) del Container NO Compatible");
	
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------
	// 
	// 							REEMPLAZANDO STRINGS
	// 							
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------
	
	// Se crea el string resultado.
	
	TString Resultado (Input);
	
	// Continuamos si la expresión de requerimiento se cumple.
	
	if constexpr (IsValidPairValue) {
		
		// Se valida cada valor en el mapa y lo reemplaza.
		
		for (const TValue & CurrentValue : Mapper) {
			
			// Crearemos los bindings para los tipos de valores (0 y 1) en el elemento actual.
			
			const auto & [CurrentOld , CurrentNew] = std::tie (std::get <0> (CurrentValue) , std::get <1> (CurrentValue));
			
			// -----------------------------------------------------------------------------
			
			// Se busca el siguiente key y en caso de encontrarlo se mapea.
			
			auto FindIterator = Resultado.find (CurrentOld);
			
			// Validamos para continuar.
			
			while (FindIterator != TString::npos) {
				
				// Se tiene lo siguiente. Se toma la cadena hasta el iterador.
				
				const std::string A (Resultado.begin () , (Resultado.begin () + FindIterator));
				
				// -----------------------------------------------------------------------------
				
				// Obtenemos el dato B.
				
				const std::string B ((Resultado.begin () + FindIterator + CurrentOld.size ()) , Resultado.end ());
				
				// Le asignamos a nuestro resultado el nuevo valor.
				
				Resultado = std::move (A + CurrentNew + B);
				
				// -----------------------------------------------------------------------------
				
				// Buscaremos la siguiente coincidencia.
				
				FindIterator = Resultado.find (CurrentOld);
				
				// -----------------------------------------------------------------------------
				
			}
			
			// -----------------------------------------------------------------------------
			
		}
	
		// -----------------------------------------------------------------------------
		
	}
	
	// Devolvemos el valor.
	
	return Resultado;
	
	// -----------------------------------------------------------------------------
	
}

/// @}
/// @}

// Implementaremos operadores auxiliares para realizar la eliminación de caracteres.

// -----------------------------------------------------------------------------
// 
// 							OPERADOR REPLACING/REMOVE
// 							
// -----------------------------------------------------------------------------

// Estableceremos un espacio en linea para guardar los operadores especificos de las utilerias.

inline namespace UtilityOperators {
	
	/// 
	/// @addtogroup UtilOperators
	/// @{
	/// 
	
	// Utilizaremos los placeholders.
	
	using namespace std::placeholders;
	
	// Definiremos el operador RemoveIf para poder efectuar el borrado de elementos que cumplan una determinada condición establecida.
	
	/// 
	/// @brief Operador <ReplacingIf (Condition)> para aplicar función que reemplaza todos los caracteres que cumplan una condición.
	/// 
	/// @param "CADENA A MODIFICAR" <Replacing (Condition)> 'CARACTER A COLOCAR'
	/// 
	/// @tparam 	TFunction 	Tipo de la función ó expresión para válidar si un caracter es candidato para ser reemplazado.
	/// 
	/// @details
	/// Este operador es un Wrapper sobre la función general StringReplacingIf utilizando como argumento la función de <b>Condición</b> la cuál
	/// devuelve <b style="color:var(--fragment-keyword);">true</b> si el caracter que se está validando debe ser reemplazado por el caracter
	/// especificado en el operando <b class="paramname">CARACTER A COLOCAR</b>. Por ejemplo :
	/// @code{.cpp}
	/// 	
	/// 	// Declaramos nuestro lambda que reemplaza todos los elementos que son iguales a '_' ó a un '@'.
	/// 	
	/// 	const auto Validation = [] (char Literal) -> bool { return ((Literal == '_' || Literal == '@')); };
	/// 	
	/// 	// Utilizando el operador y la función lambda vamos a reemplazar los elementos de la cadena por un espacio en blanco.
	/// 	
	/// 	const auto ReplacedString = "C@dena @ reemplaz@r_con_espacios"s <ReplacingIf (Validation)> ' ';
	/// 	
	/// 	// Result : "C dena   reemplaz r con espacios"
	/// 	
	/// @endcode
	/// @pre
	/// La <b>Condición</b> puede ser cualquier tipo de función que sea <b>Invocable</b> y que permita realizar la validación con un caracter al
	/// devolver un valor bool.
	/// 
	
	template <typename TFunction>
	constexpr inline auto ReplacingIf (TFunction Condition) {
		
		// -----------------------------------------------------------------------------
		
		// Devolvemos la construcción del actual operador ReplacingIf utilizando los argumentos de tipo obtenidos con el
		// parametro indicado.
		
		return MakeNamedOperator (std::bind (ReplacingStringIf <TFunction , char> , _1 , Condition , _2));
		
		// -----------------------------------------------------------------------------
		
	}
	
	// Definiremos el operador para reemplazar cualquier string dentro de una cadena mediante el pase de un mapeador
	// de valores directamente.
	
	/// 
	/// @brief Operador <Replacing (exp)> para aplicar función que reemplaza todos los elementos actuales en la cadena de Entrada.
	/// 
	/// @param "CADENA A MODIFICAR" <Replacing (expression)> CONTAINER_MAPEADOR
	/// 
	/// @tparam 	TContainer 	Tipo de contenedor que tiene los valores de paridad a reemplazar en la Entrada.
	/// @tparam 	TValues 	Tipo de Valores de argumento de plantilla para el TContainer.
	/// 
	/// @details
	/// Este operador es un Wrapper sobre la función @ref ReplacingMultiString donde se recibe como operando Izquierdo la <b>Cadena a Modificar</b>
	/// mientras que en el operando derecho tendremos al <b>Mapeador/Mapping</b> que es un contenedor de valores (Old , New) en pares donde se
	/// tendrá la lista de valores que se reemplazarán en la cadena y el valor nuevo a colocar.
	/// @code{.cpp}
	/// 	
	/// 	// Declaramos nuestro Mapeador de letras P.
	/// 	
	/// 	const std::array <std::pair <std::string , std::string> , 1> Mapeador = { { "p" , "_" } }; // Pares (Old_Value , New_Value)
	/// 	
	/// 	// Utilizando el operador y el Mapeador realizamos la modificación.
	/// 	
	/// 	const auto ReplacedString = "(Cadena a reemplazar la letra 'p')"s <Replacing (Mapeador)> Mapeador;
	/// 	
	/// 	// Result : Cadena a reem_lazar la letra '_'
	/// 	
	/// @endcode
	/// @pre
	/// La <b>expression</b> determina el tipo de Container asi como los TValues aplicados con la finalidad de tener como referencia para
	/// fines de <b>Deducción de Tipo (deduction guide)</b>. Pudiendo ser incluso el mismo valor que el <b class="paramname">CONTAINER_MAPEADOR</b>.
	/// @note
	/// El <b class="paramname">CONTAINER_MAPEADOR</b> debe cumplir la condición de tener <b>value_type</b> en formato de std::pair o std::tuple
	/// de al menos <b>2 elementos<b>.
	/// 
	
	template <template <typename , typename ...> typename TContainer , typename ... TValues>
	requires IsValidContainer <TContainer , TValues ...> constexpr inline auto Replacing (const TContainer <TValues ...> &) {
		
		// -----------------------------------------------------------------------------
		
		// Devolvemos la construcción del actual operador Replacing utilizando los argumentos de tipo obtenidos con el
		// parametro indicado como referencia.
		
		return MakeNamedOperator (ReplacingMultiString <TContainer , char , TValues ...>);;
		
		// -----------------------------------------------------------------------------
		
	}
	
	// Definiremos el operador especifico para el recorte de la cadena por el lado izquierdo.
	
	/// 
	/// @brief Operador <Remove> para aplicar función que remueve todos los caracteres determinados en la cadena de entrada.
	/// 
	/// @param "CADENA A MODIFICAR" <Remove> 'CARACTER A REMOVER'
	/// 
	/// @details
	/// Elimina todas las ocurrencias de un determinado caracter en la cadena de entrada , el equivalente a utilizar la función @ref ReplacingString con el
	/// valor del parametro <b class="paramname">S_New</b> en <b><span class="charliteral">'\0'</span></b>. Ejemplo :
	/// @code{.cpp}
	/// 
	/// 	const auto NewString = "Cadena donde Remover la letra e" <Remove> 'e';
	/// 	
	/// 	// Result : Cadna dond Rmovr la ltra
	/// 	
	/// @endcode
	/// 
	
	constexpr inline auto Remove = MakeNamedOperator (std::bind (ReplacingString <char> , _1 , _2 , '\0'));
	
	/// @}
	
	// -----------------------------------------------------------------------------
	
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Tenemos ahora una serie de funciones para poder recortar una cadena (TRIM) de cualquier tipo a una cadena
// sin espacios , tabulaciones , saltos de linea , etc.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																	TRIM STRINGS
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// @addtogroup Utilerias
/// @{
// -----------------------------------------------------------------------------

// Empezamos por la declaración de las variables de entorno para la configuración de los recortes con las funciones de TrimString.

// -----------------------------------------------------------------------------
// 
// 							VARIABLES CONST TRIM
// 							
// -----------------------------------------------------------------------------

// Tenemos una declaración para la const char de los espacios que se consideran cuando se realiza un trim.

/// @brief      Constante que define todo el conjunto de caracteres considerados como espacios para las funciones especificas. @see LTrimString RTrimString TrimString

static constexpr const char * TRIM_ESPACIOS = " \n\r\t\f\v";

// Tenemos para el caso de los ceros a la izquierda un trim de zeros.

/// @brief      Constante que define el valor de 0 para poder utilizar con las funciones y operadores de eliminación de Caracteres. @see LTrimString RTrimString TrimString

static constexpr const char * TRIM_ZEROS = "0";

/// ----------------------------------------------------------------------------
/// 
/// @name String Trim
/// 
/// @brief Funciones y variables de entorno para el <b>Recorte</b> de cadenas por los bordes dependiendo el contenido de la misma.
/// 
/// @details
/// 
/// Las cadenas pueden ser recortadas mediante el conjunto de funciones y operadores de <b>TrimString</b>. Mediante estas funciones es posible por ejemplo :
/// Eliminar todos los Zeros a la izquierda de una cadena númerica que no sirvan , o eliminar los espacios adicionales en los bordes izquierdo y derecho de
/// cualquier cadena para dejar solo el contenido central.
/// 
/// Para ejemplificar todo esto veamos el siguiente código de ejemplo :
/// @code{.cpp}
/// 
/// 	// Tenemos la siguiente cadena númerica.
/// 	
/// 	const char * const NumberString = "000010.3035  ";
/// 	
/// 	// Quitaremos los espacios de la derecha que están sobrando y los zeros a la izquierda de la misma.
/// 	
/// 	const std::string Result = LTrimString (RTrimString (NumberString , TRIM_ESPACIOS) , TRIM_ZEROS);
/// 	
/// 	// Result = "10.3035"
/// 
/// @endcode
/// 
/// Ahora lo que tenemos a continuación es la lista de variables y funciones que realizan estas acciones en cadenas de cualquier tipo.
/// 
/// @note
/// Para utilizar los operadores <b>Trim</b> vea la referencia para la lista de estos : @ref LTrim @ref RTrim @ref Trim
/// @see LTrim , RTrim , Trim
/// 
/// <h2 class="groupheader">Funciones</h2>
/// 
/// @{
/// 
// -----------------------------------------------------------------------------

// Ahora vamos a declarar nuestra función para realizar nuestro respectivo recorte primero con el lado derecho y después con el lado izquierdo.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Corta el sobrante de una cadena por la izquierda.
///
/// @param[in]  Input    Cadena de entrada a modificar.
/// @param[in]  Symbols  Conjunto de Caracteres a eliminar del Costado Izquierdo.
///
/// @tparam     TChar    Tipo de caracter utilizado , por defecto es char.
///
/// @return     Cadena STD recortada con todos los caracteres sobrantes por la <b>Izquierda</b>
/// 
/// @details
/// 
/// El sobrante de una cadena son todos los caracteres que están adicionales al contenido en general de la cadena , por ejemplo los espacios
/// adicionales a los costados de algún valor númerico. Este tipo de caracter se puede especificar mediante el parametro <b class="paramname">Symbols</b>
/// donde se establecen todos los caracteres a considerar para eliminar.
/// 
/// @note
/// Se puede utilizar las constantes @ref TRIM_ESPACIOS para recortar los espacios adicionales , mientras que con @ref TRIM_ZEROS se pueden quitar los
/// ceros adicionales por el lado izquierdo de la cadena.
/// 
// -----------------------------------------------------------------------------

template <typename TChar = char>
std::basic_string <TChar> LTrimString (const std::basic_string <TChar> & Input , const char * const Symbols = TRIM_ESPACIOS) {
	
	// -----------------------------------------------------------------------------
	// 
	// 							RECORTE LADO IZQUIERDO
	// 							
	// -----------------------------------------------------------------------------
	
	// Primero vamos a realizar un trim para el lado izquierdo , para esto buscaremos el primer elemento
	// que sea distinto a nuestros Symbolos determinados.
	
	const size_t Inicio = Input.find_first_not_of (Symbols);
	
	// -----------------------------------------------------------------------------
	
	// Ahora con esta posición devolvemos una subcadena conformada por la posición de origen y hasta
	// el final de dicha cadena.
	
	return ((Inicio == std::string::npos) ? std::string () : Input.substr (Inicio));
	
	// -----------------------------------------------------------------------------
	
}

// Implementaremos la función para poder establece el recorte de la cadena con un const char *.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Corta el sobrante de una cadena por la Izquierda.
///
/// @param[in]  Input    Cadena de entrada a modificar C-Style.
/// @param[in]  Symbols  Conjunto de Caracteres a eliminar del Costado Izquierdo.
///
/// @return     Cadena STD recortada con todos los caracteres sobrantes por la <b>Izquierda</b>
/// 
/// @details
/// 
/// Elimina toda la secuencia de caracteres especificados en el parametro <b class="paramname">Symbols</b> mediante el uso de la cadena de tipo
/// C. El recorte se realiza por el costado izquierdo.
/// 
// -----------------------------------------------------------------------------

ALWAYS_INLINE std::string LTrimString (const char * const Input , const char * const Symbols = TRIM_ESPACIOS) {
	
	// Devolvemos el resultado de la función anterior.
	
	return LTrimString (std::string (Input) , Symbols);
	
	// -----------------------------------------------------------------------------
	
}

// Ahora pasaremos con nuestra función para realizar el recorde del lado derecho de la cadena.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Corta el sobrante de una cadena por la derecha.
///
/// @param[in]  Input    Cadena de entrada a modificar.
/// @param[in]  Symbols  Conjunto de Caracteres a eliminar del Costado Derecho.
///
/// @tparam     TChar    Tipo de caracter utilizado , por defecto es char.
///
/// @return     Cadena STD recortada con todos los caracteres sobrantes por la <b>Derecho</b>
/// 
/// @details
/// 
/// El sobrante de una cadena son todos los caracteres que están adicionales al contenido en general de la cadena , por ejemplo los espacios
/// adicionales a los costados de algún valor númerico. Este tipo de caracter se puede especificar mediante el parametro <b class="paramname">Symbols</b>
/// donde se establecen todos los caracteres a considerar para eliminar.
/// 
/// @note
/// Se puede utilizar las constantes @ref TRIM_ESPACIOS para recortar los espacios adicionales , mientras que con @ref TRIM_ZEROS se pueden quitar los
/// ceros adicionales por el lado derecho de la cadena.
/// 
// -----------------------------------------------------------------------------

template <typename TChar = char>
std::basic_string <TChar> RTrimString (const std::basic_string <TChar> & Input , const char * const Symbols = TRIM_ESPACIOS) {
	
	// -----------------------------------------------------------------------------
	// 
	// 							RECORTE LADO DERECHO
	// 							
	// -----------------------------------------------------------------------------
	
	// Buscaremos la ultima posición donde se encuentra el último caracter que no es un simbolo determinado.
	
	const size_t Final = Input.find_last_not_of (Symbols);
	
	// -----------------------------------------------------------------------------
	
	// Ahora con esta posición devolvemos una subcadena conformada por el origen en la cadena y
	// hasta la última posición del caracter válido + 1. De lo contrario se devuelve la cadena vacía.
	
	return ((Final == std::string::npos) ? std::string () : Input.substr (0 , (Final + 1)));
	
	// -----------------------------------------------------------------------------
	
}

// Tenemos la función para realizarlo de modo directo con el const char.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Corta el sobrante de una cadena por la Derecha.
///
/// @param[in]  Input    Cadena de entrada a modificar C-Style.
/// @param[in]  Symbols  Conjunto de Caracteres a eliminar del Costado Izquierdo.
///
/// @return     Cadena STD recortada con todos los caracteres sobrantes por la <b>Derecha</b>
/// 
/// @details
/// 
/// Elimina toda la secuencia de caracteres especificados en el parametro <b class="paramname">Symbols</b> mediante el uso de la cadena de tipo
/// C. El recorde se realiza por el costado derecho.
/// 
// -----------------------------------------------------------------------------

ALWAYS_INLINE std::string RTrimString (const char * const Input , const char * const Symbols = TRIM_ESPACIOS) {
	
	// Devolvemos la cadena recortada por la derecha.
	
	return RTrimString (std::string (Input) , Symbols);
	
	// -----------------------------------------------------------------------------
	
}

// Finalmente tenemos la función en linea parametrizable para poder obtener el respectivo string
// recortado tanto de los lados izquierdo como el derecho.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Corta el sobrante de una cadena por la derecha y por la izquierda.
///
/// @param[in]  Input    Cadena de entrada a modificar.
/// @param[in]  Symbols  Conjunto de Caracteres a eliminar por ambos lados de una cadena.
///
/// @tparam     TChar    Tipo de caracter utilizado , por defecto es char.
///
/// @return     Cadena STD recortada con todos los caracteres sobrantes en <b>Ambos Costados</b>.
/// 
/// @details
/// 
/// Esta función utiliza tanto el recorde Izquierdo como el recorde Derecho sobre la cadena especificada. Devuelve la cadena recortada por
/// ambos lados con el conjunto de caracteres a considerar para el recorte.
/// 
// -----------------------------------------------------------------------------

template <typename TChar = char>
ALWAYS_INLINE std::basic_string <TChar> TrimString (const std::basic_string <TChar> & Input , const char * const Symbols = TRIM_ESPACIOS) {
	
	// -----------------------------------------------------------------------------
	// 
	// 							RECORTANDO CADENA
	// 							
	// -----------------------------------------------------------------------------
	
	// Recortaremos la cadena por la izquierda y por la derecha.
	
	return RTrimString (LTrimString (Input , Symbols) , Symbols);
	
	// -----------------------------------------------------------------------------
	
}

// Tenemos de la misma manera la función para realizar la sobrecarga con un const char *,

/// ----------------------------------------------------------------------------
/// 
/// @brief      Corta el sobrante de una cadena por la derecha y por la izquierda.
///
/// @param[in]  Input    Cadena de entrada a modificar C-Style.
/// @param[in]  Symbols  Conjunto de Caracteres a eliminar por ambos lados de una cadena.
///
/// @return     Cadena STD recortada con todos los caracteres sobrantes en <b>Ambos Costados</b>.
/// 
/// @details
/// 
/// Esta función utiliza tanto el recorde Izquierdo como el recorde Derecho sobre la cadena especificada. Devuelve la cadena recortada por
/// ambos lados con el conjunto de caracteres a considerar para el recorte.
/// 
// -----------------------------------------------------------------------------

ALWAYS_INLINE std::string TrimString (const char * const Input , const char * const Symbols = TRIM_ESPACIOS) {
	
	// Devolvemos el resultado de aplicar tanto el recorte izquierdo y derecho.
	
	return RTrimString (LTrimString (std::string (Input) , Symbols) , Symbols);
	
	// -----------------------------------------------------------------------------
	
}

/// @}
/// @}

// Implementaremos operadores auxiliares para realizar el Trim de cadenas.

// -----------------------------------------------------------------------------
// 
// 							OPERADOR TRIM
// 							
// -----------------------------------------------------------------------------

// Estableceremos un espacio en linea para guardar los operadores especificos de las utilerias.

inline namespace UtilityOperators {
	
	/// 
	/// @addtogroup UtilOperators
	/// @{
	///
	
	// Definiremos el operador especifico para el recorte de la cadena por el lado izquierdo.
	
	/// 
	/// @brief Operador <LTrim> para aplicar función que acorta los espacios a la Izquierda.
	/// 
	/// @param "CADENA A MODIFICAR" <LTrim> "SIMBOLOS A RECORTAR"
	/// 
	/// @details
	/// Elimina toda la secuencia de Simbolos (char) que se encuentran a la Izquierda de la Cadena de entrada. @see Trim
	///
	
	inline auto LTrim = MakeNamedOperator (LTrimString <char>);
	
	// Definiremos el operador especifico para el recorte de la cadena por el lado derecho.
	
	/// 
	/// @brief Operador <RTrim> para aplicar función que acorta los espacios a la Derecha.
	/// 
	/// @param "CADENA A MODIFICAR" <RTrim> "SIMBOLOS A RECORTAR"
	/// 
	/// @details
	/// Elimina toda la secuencia de Simbolos (char) que se encuentran a la Derecha de la Cadena de entrada. @see Trim
	///
	
	inline auto RTrim = MakeNamedOperator (RTrimString <char>);
	
	// Definiremos el operador especifico para el recorte de la cadena por ambos lados.
	
	/// 
	/// @brief Operador <Trim> para aplicar función que acorta los espacios a los costados de una cadena determinada.
	/// 
	/// @param "CADENA A MODIFICAR" <Trim> "SIMBOLOS A RECORTAR"
	/// 
	/// @details
	/// Elimina toda la secuencia de Simbolos que se encuentran tanto a la izquierda como a la derecha de la cadena. Es la combinación de aplicar
	/// tanto @ref RTrim y @ref LTrim sobre una cadena especificada. En el parametro se especifica las cadenas con el conjunto de Simbolos a considerar
	/// para el recorde de la cadena. Ejemplo : 
	/// @code{.cpp}
	/// 
	/// 	// Declaramos la cadena a modificar.
	/// 	
	/// 	std::string TrimedString = " Cadena a eliminar espacios        \n"
	/// 	
	/// 	// Aplicamos el trim sobre esta cadena.
	/// 	
	/// 	TrimedString <Trim>= TRIM_ESPACIOS;
	/// 	
	/// 	// Result : "Cadena a eliminar espacios"
	/// 	
	/// @endcode
	/// @see TRIM_ESPACIOS TRIM_ZEROS
	///
	
	inline auto Trim = MakeNamedOperator (TrimString <char>);
	
	// -----------------------------------------------------------------------------
	
	/// @}
	
}

// Los siguientes serán para cortar la cadena a diferentes tramos.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		CUTTING STRINGS
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Implementaremos todas las funciones para el recorte de cadenas por el inicio y por el final.

// -----------------------------------------------------------------------------
/// @addtogroup Utilerias
/// @{
// -----------------------------------------------------------------------------

/// ----------------------------------------------------------------------------
/// 
/// @name String Cutting
/// 
/// @brief Funciones para realizar el <b>Recorte</b> de una cadena determinada y obtener el sobrante o la parte cortada de la misma.
/// 
/// @details
/// 
/// El <i>String Cutting</i> consiste en cortar una cadena la cantidad de <b>Caracteres</b> especificada por la derecha o por la izquierda y recuperar el
/// valor cortado de la cadena o el sobrante de la misma. Por esto las funciones tienen un parametro llamado <b class="paramname">Spare</b> el cuál
/// determina si devolverá la parte cortada o la parte restante de la cadena de entrada. Por ejemplo :
/// @code{.cpp}
/// 
/// 	// Recortaremos la siguiente cadena y obtendremos la parte recortada.
/// 	
/// 	const std::string StringCutted = LCutString ("Palabras Normales" , 9 , false);
/// 	
/// 	// StringCutted = 	"Palabras";
/// 	// Parte Sobrante = " Normales";
/// 
/// @endcode
/// 
/// Las funciones que conforman esta sección son las siguientes :
/// 
/// <h2 class="groupheader">Funciones</h2>
/// 
/// @{
/// 
// -----------------------------------------------------------------------------

// Implementaremos la función para poder realizar el corte de una cadena por el lado izquierdo de la misma , ya sea con el recorte o con el sobrante.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Recorta la cantidad especifica de una cadena por la Izquierda y devuelve la cadena cortada ó el sobrante.
///
/// @param[in]  Input   Cadena de entrada a recortar.
/// @param  	Count  	Cantidad de letras a recortar de la cadena.
/// @param  	Spare  	<b style="color:var(--fragment-keyword);">true</b> si se quiere obtener el sobrante de la cadena. <b style="color:var(--fragment-keyword);">false</b> para obtener lo cortado.
///
/// @tparam     TChar    Tipo de caracter utilizado , por defecto es char.
///
/// @return     Cadena STD recortada o el sobrante de la cadena recortada.
/// 
/// @details
/// 
/// Esta función permite recortar una cantidad determinada de letras de una cadena de entrada y devolver : 
/// <ul>
/// <li>La cadena Recortada si el parametro <b class="paramname">Spare</b> es igual a <b style="color:var(--fragment-keyword);">false</b>.
/// <li>La cadena Sobrante si el parametro <b class="paramname">Spare</b> es igual a <b style="color:var(--fragment-keyword);">true</b>.
/// </ul>
/// 
/// @warning
/// El valor <b class="paramname">Count</b> debe ser <b>mayor</b> a la longitud de la cadena , de lo contrario devuelve la misma cadena de entrada.
/// 
/// @see RCutString
/// 
// -----------------------------------------------------------------------------

template <typename TChar = char>
ALWAYS_INLINE std::basic_string <TChar> LCutString (const std::basic_string <TChar> & Input , size_t Count , bool Spare = false) {
	
	// Devolvemos la subcadena que se genera desde 0 hasta la cantidad determinada por el lado izquierdo de la cadena , o el sobrante
	// de cortar esa cantidad de datos si el parametro es true.
	
	return ((Input.size () > Count) ? (Spare ? Input.substr (Count) : Input.substr (0 , Count)) : Input);
	
	// -----------------------------------------------------------------------------
	
}

// Implementaremos la sobrecarga con el c-style const char.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Recorta la cantidad especifica de una cadena por la Izquierda y devuelve la cadena cortada ó el sobrante.
///
/// @param[in]  Input   Cadena de entrada a recortar C-Style.
/// @param  	Count  	Cantidad de letras a recortar de la cadena.
/// @param  	Spare  	<b style="color:var(--fragment-keyword);">true</b> si se quiere obtener el sobrante de la cadena. <b style="color:var(--fragment-keyword);">false</b> para obtener lo cortado.
///
/// @return     Cadena STD recortada o el sobrante de la cadena recortada.
/// 
/// @details
/// 
/// Esta función permite recortar una cantidad determinada de letras de una cadena de entrada y devolver : 
/// <ul>
/// <li>La cadena Recortada si el parametro <b class="paramname">Spare</b> es igual a <b style="color:var(--fragment-keyword);">false</b>.
/// <li>La cadena Sobrante si el parametro <b class="paramname">Spare</b> es igual a <b style="color:var(--fragment-keyword);">true</b>.
/// </ul>
/// 
/// @see RCutString
/// 
// -----------------------------------------------------------------------------

ALWAYS_INLINE std::string LCutString (const char * const Input , size_t Count , bool Spare = false) {
	
	// Devolvemos el resultado de la llamada anterior.
	
	return LCutString (std::string (Input) , Count , Spare);
	
	// -----------------------------------------------------------------------------
	
}

// Implementaremos la función para poder realizar el corte de la cadena por el lado derecho.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Recorta la cantidad especifica de una cadena por la Derecha y devuelve la cadena cortada ó el sobrante.
///
/// @param[in]  Input   Cadena de entrada a recortar.
/// @param  	Count  	Cantidad de letras a recortar de la cadena.
/// @param  	Spare  	<b style="color:var(--fragment-keyword);">true</b> si se quiere obtener el sobrante de la cadena. <b style="color:var(--fragment-keyword);">false</b> para obtener lo cortado.
///
/// @tparam     TChar    Tipo de caracter utilizado , por defecto es char.
///
/// @return     Cadena STD recortada o el sobrante de la cadena recortada.
/// 
/// @details
/// 
/// Esta función permite recortar una cantidad determinada de letras de una cadena de entrada y devolver : 
/// <ul>
/// <li>La cadena Recortada si el parametro <b class="paramname">Spare</b> es igual a <b style="color:var(--fragment-keyword);">false</b>.
/// <li>La cadena Sobrante si el parametro <b class="paramname">Spare</b> es igual a <b style="color:var(--fragment-keyword);">true</b>.
/// </ul>
/// 
/// @warning
/// El valor <b class="paramname">Count</b> debe ser <b>mayor</b> a la longitud de la cadena , de lo contrario devuelve la misma cadena de entrada.
/// 
/// @see RCutString
/// 
// -----------------------------------------------------------------------------

template <typename TChar = char>
ALWAYS_INLINE std::basic_string <TChar> RCutString (const std::basic_string <TChar> & Input , size_t Count , bool Spare = false) {
	
	// Definiremos el tipo de cadena a trabajar.
	
	using TString = std::basic_string <TChar>;
	
	// Devolvemos la subcadena que se genera desde 0 hasta la cantidad determinada por el lado derecho de la cadena , o el sobrante
	// de cortar esa cantidad de datos si el parametro es true.
	
	return ((Input.size () > Count) ? (Spare ? Input.substr (0 , (Input.size () - Count)) : Input.substr (Input.size () - Count)) : Input);
	
	// -----------------------------------------------------------------------------
	
}

// Implementaremos la sobrecarga con el c-style const char.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Recorta la cantidad especifica de una cadena por la Derecha y devuelve la cadena cortada ó el sobrante.
///
/// @param[in]  Input   Cadena de entrada a recortar C-Style.
/// @param  	Count  	Cantidad de letras a recortar de la cadena.
/// @param  	Spare  	<b style="color:var(--fragment-keyword);">true</b> si se quiere obtener el sobrante de la cadena. <b style="color:var(--fragment-keyword);">false</b> para obtener lo cortado.
///
/// @return     Cadena STD recortada o el sobrante de la cadena recortada.
/// 
/// @details
/// 
/// Esta función permite recortar una cantidad determinada de letras de una cadena de entrada y devolver : 
/// <ul>
/// <li>La cadena Recortada si el parametro <b class="paramname">Spare</b> es igual a <b style="color:var(--fragment-keyword);">false</b>.
/// <li>La cadena Sobrante si el parametro <b class="paramname">Spare</b> es igual a <b style="color:var(--fragment-keyword);">true</b>.
/// </ul>
/// 
/// @see LCutString
/// 
// -----------------------------------------------------------------------------

ALWAYS_INLINE std::string RCutString (const char * const Input , size_t Count , bool Spare = false) {
	
	// Devolvemos el resultado de la llamada anterior.
	
	return RCutString (std::string (Input) , Count , Spare);
	
	// -----------------------------------------------------------------------------
	
}

/// @}
/// @}

// Implementaremos operadores auxiliares para los recortes de cadenas

// -----------------------------------------------------------------------------
// 
// 							OPERADORES CUT
// 							
// -----------------------------------------------------------------------------

// Estableceremos un espacio en linea para guardar los operadores especificos de las utilerias.

inline namespace UtilityOperators {
	
	/// 
	/// @addtogroup UtilOperators
	/// @{
	/// 
	
	// Utilizaremos los placeholders.
	
	using namespace std::placeholders;
	
	// Definiremos el operador especifico para el recorte de la cadena por el lado izquierdo.
	
	/// 
	/// @brief Operador <LCut <SPARE>> para aplicar función que remueve todos los caracteres determinados en la cadena de entrada.
	/// 
	/// @param "CADENA A RECORTAR" <LCut <<b class="paramname" style="color:var(--fragment-keyword);">SPARE(true|false)</b>>><b class="paramname">COUNT</b>
	/// 
	/// @tparam 	BSpare 		<b style="color:var(--fragment-keyword);">true</b> para utilizar el sobrante , <b style="color:var(--fragment-keyword);">false</b> para 
	/// 						utitilizar lo recortado.
	/// 
	/// @tparam 	TChar 		Tipo de caracter a utilizar. Por defecto es char.
	/// 
	/// @return 	Cadena STD recortada por el lado <b>izquierdo</b>.
	/// 
	/// @details
	/// Esta función se encarga de recortar la cadena de entrada la cantidad de letras igual al valor que tiene el parametro <b class="paramname">COUNT</b>.
	/// El valor de <b class="paramname">SPARE</b> se especifica en el parametro de la plantilla. Ejemplo :
	/// @code{.cpp}
	/// 
	/// 	const auto CuttedString = "Cadena a cortar 6 caracteres de la izquierda" <LCut <true>> 6;
	/// 	
	/// 	// Result : " a cortar 6 caracteres de la izquierda"
	/// 	
	/// @endcode
	/// 
	/// @see RCut
	/// 
	
	template <bool BSpare = false , typename TChar = char>
	inline auto LCut = MakeNamedOperator (std::bind (LCutString <TChar> , _1 , _2 , BSpare));
	
	// Ahora el operador para el caso de RCut tendremos lo siguiente.
	
	/// 
	/// @brief Operador <RCut <SPARE>> para aplicar función que remueve todos los caracteres determinados en la cadena de entrada.
	/// 
	/// @param "CADENA A RECORTAR" <RCut <<b class="paramname" style="color:var(--fragment-keyword);">SPARE(true|false)</b>>><b class="paramname">COUNT</b>
	/// 
	/// @tparam 	BSpare 		<b style="color:var(--fragment-keyword);font-size: 120%;">true</b> para utilizar el sobrante ,
	/// 						<b style="color:var(--fragment-keyword);font-size: 120%;">false</b> para utitilizar lo recortado.
	/// 
	/// @tparam 	TChar 		Tipo de caracter a utilizar. Por defecto es char.
	/// 
	/// @return 	Cadena STD recortada por el <b>lado derecho</b>.
	/// 
	/// @details
	/// Esta función se encarga de recortar la cadena de entrada la cantidad de letras igual al valor que tiene el parametro <b class="paramname">COUNT</b>.
	/// El valor de <b class="paramname">SPARE</b> se especifica en el parametro de la plantilla. Ejemplo :
	/// @code{.cpp}
	/// 
	/// 	const auto CuttedString = "Cadena a cortar 6 caracteres de la derecha" <RCut <true>> 10;
	/// 	
	/// 	// Result : "Cadena a cortar 6 caracteres de la"
	/// 	
	/// @endcode
	/// 
	
	template <bool BSpare = false , typename TChar = char>
	inline auto RCut = MakeNamedOperator (std::bind (RCutString <TChar> , _1 , _2 , BSpare));
	
	/// @}
	
	// -----------------------------------------------------------------------------
	
}

// -----------------------------------------------------------------------------

// Pasamos a la siguiente funcionalidad de strings.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		PADDING STRINGS
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// @addtogroup Utilerias
/// @{
// -----------------------------------------------------------------------------

/// ----------------------------------------------------------------------------
/// 
/// @name String Padding
/// 
/// @brief Funciones para realizar el <b>Paddeo</b> con el caracter especificado sobre una cadena de entrada.
/// 
/// @details
/// 
/// El <i>String Padding</i> consiste en rellenar con un determinado caracter , la cadena de entrada hasta completar una determinada longitud de la cadena.
/// Por ejemplo :
/// @code{.cpp}
/// 
/// 	// Acompletamos la cadena de número hasta llenar 10 caracteres.
/// 	
/// 	const std::string StringPadded = LPadString ("10.0" , 10 , '0');
/// 	
/// 	// StringPadded = "00000010.0"
/// 
/// @endcode
/// 
/// Las funciones que conforman esta sección son las siguientes :
/// 
/// <h2 class="groupheader">Funciones</h2>
/// 
/// @{
/// 
// -----------------------------------------------------------------------------

// Ahora una combinación de ambas funciones para poder hacer un pad a cualquier cadena con cualquier cantidad
// de caracteres y rellenarlo con cualquier simbolo.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Rellena con un Caracter especifico toda la cadena de entrada hasta llegar a un tamaño total establecido del lado izquierdo de la cadena.
///
/// @param[in]  Input      Cadena de Entrada.
/// @param[in]  TotalSize  Cantidad de Letras en total de la cadena resultante.
/// @param[in]  Symbol     Caracter a rellenar la cadena.
///
/// @tparam     TChar      Tipo de Caracter de la cadena de entrada y salida. Por defecto es igual a char.
///
/// @return     Cadena STD rellenada hasta la cantidad total determinada por el parametro <b class="paramname">TotalSize</b>.
/// 
/// @details
/// 
/// Esta función toma la cadena de entrada y dependiendo el tamaño. Si es menor a la longitud total especificada entonces la cantidad de letras
/// faltante son <b>rellenadas</b> con los caracteres especificados en el parametro <b class="paramname">Symbol</b>.
/// 
/// Esta función rellena por el lado <b>Izquierdo</b> de la cadena. @see RPadString
/// 
// -----------------------------------------------------------------------------

template <typename TChar = char>
std::basic_string <TChar> LPadString (const std::basic_string <TChar> & Input , size_t TotalSize , TChar Symbol) {
	
	// Realizaremos primero el recorte de nuestra cadena para poder rellenar posteriormente.
	
	const auto CurrentInput (TrimString (Input));
	
	// Ahora simplemente rellenaremos a la izquierda hasta la cantidad efectuada (si es mayor a la cadena).
	
	return ((TotalSize > CurrentInput.length ()) ? LFillString (CurrentInput , (TotalSize - CurrentInput.length ()) , Symbol) : CurrentInput);
	
	// -----------------------------------------------------------------------------
	
}

/// ----------------------------------------------------------------------------
/// 
/// @brief      Rellena con un Caracter especifico toda la cadena de entrada hasta llegar a un tamaño total establecido del lado izquierdo de la cadena.
///
/// @param[in]  Input      Cadena de Entrada C-Style.
/// @param[in]  TotalSize  Cantidad de Letras en total de la cadena resultante.
/// @param[in]  Symbol     Caracter a rellenar la cadena.
///
/// @return     Cadena STD rellenada hasta la cantidad total determinada por el parametro <b class="paramname">TotalSize</b>.
/// 
/// @details
/// 
/// Esta función toma la cadena de entrada y dependiendo el tamaño. Si es menor a la longitud total especificada entonces la cantidad de letras
/// faltante son <b>rellenadas</b> con los caracteres especificados en el parametro <b class="paramname">Symbol</b>.
/// 
/// Esta función rellena por el lado <b>Izquierdo</b> de la cadena. @see RPadString
/// 
// -----------------------------------------------------------------------------

// Tenemos una sobrecarga para poder efectuarlo con un const char.

ALWAYS_INLINE std::string LPadString (const char * const Input , size_t TotalSize , char Symbol = '0') {
	
	// Devolvemos la llamada a nuestra función anterior.
	
	return LPadString (std::string (Input) , TotalSize , Symbol);
	
	// -----------------------------------------------------------------------------
	
}

/// ----------------------------------------------------------------------------
/// 
/// @brief      Rellena con un Caracter especifico toda la cadena de entrada hasta llegar a un tamaño total establecido del lado derecho de la cadena.
///
/// @param[in]  Input      Cadena de Entrada.
/// @param[in]  TotalSize  Cantidad de Letras en total de la cadena resultante.
/// @param[in]  Symbol     Caracter a rellenar la cadena.
///
/// @tparam     TChar      Tipo de Caracter de la cadena de entrada y salida. Por defecto es igual a char.
///
/// @return     Cadena STD rellenada hasta la cantidad total determinada por el parametro <b class="paramname">TotalSize</b>.
/// 
/// @details
/// 
/// Esta función toma la cadena de entrada y dependiendo el tamaño. Si es menor a la longitud total especificada entonces la cantidad de letras
/// faltante son <b>rellenadas</b> con los caracteres especificados en el parametro <b class="paramname">Symbol</b>.
/// 
/// Esta función rellena por el lado <b>Derecho</b> de la cadena. @see LPadString
/// 
// -----------------------------------------------------------------------------

// Ahora la versión para rellenar a la derecha.

template <typename TChar = char>
std::basic_string <TChar> RPadString (const std::basic_string <TChar> & Input , size_t TotalSize , TChar Symbol) {
	
	// Realizaremos primero el recorte de nuestra cadena para poder rellenar posteriormente.
	
	const auto CurrentInput (TrimString (Input));
	
	// Ahora simplemente rellenaremos a la izquierda hasta la cantidad efectuada (si es mayor a la cadena).
	
	return ((TotalSize > CurrentInput.length ()) ? RFillString (CurrentInput , (TotalSize - CurrentInput.length ()) , Symbol) : CurrentInput);
	
	// -----------------------------------------------------------------------------
	
}

/// ----------------------------------------------------------------------------
/// 
/// @brief      Rellena con un Caracter especifico toda la cadena de entrada hasta llegar a un tamaño total establecido del lado derecho de la cadena.
///
/// @param[in]  Input      Cadena de Entrada C-Style.
/// @param[in]  TotalSize  Cantidad de Letras en total de la cadena resultante.
/// @param[in]  Symbol     Caracter a rellenar la cadena.
///
/// @return     Cadena STD rellenada hasta la cantidad total determinada por el parametro <b class="paramname">TotalSize</b>.
/// 
/// @details
/// 
/// Esta función toma la cadena de entrada y dependiendo el tamaño. Si es menor a la longitud total especificada entonces la cantidad de letras
/// faltante son <b>rellenadas</b> con los caracteres especificados en el parametro <b class="paramname">Symbol</b>.
/// 
/// Esta función rellena por el lado <b>Derecho</b> de la cadena. @see RPadString
/// 
// -----------------------------------------------------------------------------

// Tenemos una sobrecarga para poder efectuarlo con un const char.

ALWAYS_INLINE std::string RPadString (const char * const Input , size_t TotalSize , char Symbol = '0') {
	
	// Devolvemos la llamada a nuestra función anterior.
	
	return RPadString (std::string (Input) , TotalSize , Symbol);
	
	// -----------------------------------------------------------------------------
	
}

/// @}
/// @}

// Ahora definiremos operadores nombrados para realizar ciertas operaciones base de las utilerias.

// -----------------------------------------------------------------------------
// 
// 						OPERADOR REMOVE / PAD / FILL
// 							
// -----------------------------------------------------------------------------

// Estableceremos un espacio en linea para guardar los operadores especificos de las utilerias.

inline namespace UtilityOperators {
	
	/// 
	/// @addtogroup UtilOperators
	/// @{
	///
	
	// -----------------------------------------------------------------------------
	// 
	// 							FILL / PAD SYMBOL
	// 							
	// -----------------------------------------------------------------------------
	
	// Definiremos el tipo de alias para las funciones de relleno asi como de padding que respetan la misma estructura.
	
	/// 
	/// @brief Tipo de función utilizada como wrapped para los modificadores de cadena (RFIllString y RPadString)
	/// 
	
	template <typename TChar = char>
	using TypeFunction = std::function <std::basic_string <TChar> (const std::basic_string <TChar> , size_t , TChar)>;
	
	// Utilizaremos los placeholders para asignar huecos a la función del operador.
	
	using namespace std::placeholders;
	
	// -----------------------------------------------------------------------------
	
	// Implementaremos una función para rellenar o paddear a cualquier dirección , de una cadena mediante el uso del operador respectivo.
	
	/// @cond FunctionInternal
	
	template <typename TChar = char>
	inline std::basic_string <TChar> OperatorFillPad (const TypeFunction <TChar> & Funcion , const std::string & Input , size_t Number , char Symbol) {
		
		// Devolemos una invocacción a la función conformada por la cadena de entrada , el numero y un valor de symbolo establecido.
		
		return Funcion (Input , Number , Symbol);
		
		// -----------------------------------------------------------------------------
		
	}
	
	/// @endcond
	
	// -----------------------------------------------------------------------------
	
	// Definiremos el operador especifico para el rellenado a la izquierda.
	
	/// 
	/// @brief Operador de plantilla <LFill> para aplicar función que rellena la cadena especificada a la izquierda con el Caracter indicado en el parametro de plantilla.
	/// 
	/// @param "CADENA A MODIFICAR" <LFill <<b class="paramname">'SIMBOLO A UTILIZAR'</b>>> <b class="paramname">CANTIDAD A RELLENAR</b>
	/// 
	/// @tparam 	FSymbol 	Caracter a utilizar para rellenar la cadena.
	/// @tparam 	TChar 		Tipo de caracter a utilizar. Por defecto es char.
	/// 
	/// @details
	/// Esta función se encarga de rellenar la cadena de entrada con el Caracter (<b class="paramname">SIMBOLO A UTILIZAR</b>) la cantidad de letras igual al valor que
	/// tiene el parametro <b class="paramname">CANTIDAD A RELLENAR</b>. El caracter a utilizar se especifica en el parametro de la plantilla. Ejemplo :
	/// @code{.cpp}
	/// 
	/// 	const auto PaddedString = "Cadena a llenar con espacios a la izquierda" <LFill <' '>> 4;
	/// 	
	/// 	// Result : "    Cadena a llenar con espacios a la izquierda"
	/// 	
	/// @endcode
	/// 
	/// @see LFillString RFillString
	/// 
	
	template <char FSymbol , typename TChar = char>
	inline auto LFill = MakeNamedOperator (std::bind (OperatorFillPad <TChar> , LFillString <TChar> , _1 , _2 , static_cast <TChar> (FSymbol)));
	
	// Definiremos el operador especifico para rellenar a la derecha.
	
	/// 
	/// @brief Operador de plantilla <RFill> para aplicar función que rellena la cadena especificada a la derecha con el Caracter indicado en el parametro de plantilla.
	/// 
	/// @param "CADENA A MODIFICAR" <RFill <<b class="paramname">'SIMBOLO A UTILIZAR'</b>>> <b class="paramname">CANTIDAD A RELLENAR</b>
	/// 
	/// @tparam 	FSymbol 	Caracter a utilizar para rellenar la cadena.
	/// @tparam 	TChar 		Tipo de caracter a utilizar. Por defecto es char.
	/// 
	/// @details
	/// Esta función se encarga de rellenar la cadena de entrada con el Caracter (<b class="paramname">SIMBOLO A UTILIZAR</b>) la cantidad de letras igual al valor que
	/// tiene el parametro <b class="paramname">CANTIDAD A RELLENAR</b>. El caracter a utilizar se especifica en el parametro de la plantilla. Ejemplo :
	/// @code{.cpp}
	/// 
	/// 	const auto PaddedString = "Cadena a llenar con espacios a la derecha" <RFill <' '>> 4;
	/// 	
	/// 	// Result : "Cadena a llenar con espacios a la derecha    "
	/// 	
	/// @endcode
	///  
	/// @see LFillString RFillString
	/// 
	
	template <char FSymbol , typename TChar = char>
	inline auto RFill = MakeNamedOperator (std::bind (OperatorFillPad <TChar> , RFillString <TChar> , _1 , _2 , static_cast <TChar> (FSymbol)));
	
	// Definiremos el operador especifico para paddear a la izquierda.
	
	/// 
	/// @brief Operador de plantilla <LPad> para aplicar función que completar la cadena especificada a la izquierda con el Caracter indicado en el parametro de plantilla.
	/// Hasta la cantidad de caracteres indicado.
	/// 
	/// @param "CADENA A MODIFICAR" <LPad <<b class="paramname">'SIMBOLO A UTILIZAR'</b>>> <b class="paramname">CANTIDAD TOTAL</b>
	/// 
	/// @tparam 	FSymbol 	Caracter a utilizar para rellenar la cadena.
	/// @tparam 	TChar 		Tipo de caracter a utilizar. Por defecto es char.
	/// 
	/// @details
	/// Esta función se encarga de completar la cadena de entrada con el Caracter (<b class="paramname">SIMBOLO A UTILIZAR</b>) la cantidad de letras igual al valor que
	/// tiene el parametro <b class="paramname">CANTIDAD TOTAL</b>. El caracter a utilizar se especifica en el parametro de la plantilla. Ejemplo :
	/// @code{.cpp}
	/// 
	/// 	const auto PaddedString = "Cadena para acompletar" <LPad <' '>> 25;
	/// 	
	/// 	// Result : "   Cadena para acompletar"
	/// 	
	/// @endcode
	/// 
	/// @see LPadString RPadString
	/// 
	
	template <char FSymbol , typename TChar = char>
	inline auto LPad = MakeNamedOperator (std::bind (OperatorFillPad <TChar> , LPadString <TChar> , _1 , _2 , static_cast <TChar> (FSymbol)));
	
	// Asi como el operador para paddear a la derecha.
	
	/// 
	/// @brief Operador de plantilla <RPad> para aplicar función que completar la cadena especificada a la derecha con el Caracter indicado en el parametro de plantilla.
	/// Hasta la cantidad de caracteres indicado.
	/// 
	/// @param "CADENA A MODIFICAR" <RPad <<b class="paramname">'SIMBOLO A UTILIZAR'</b>>> <b class="paramname">CANTIDAD TOTAL</b>
	/// 
	/// @tparam 	FSymbol 	Caracter a utilizar para rellenar la cadena.
	/// @tparam 	TChar 		Tipo de caracter a utilizar. Por defecto es char.
	/// 
	/// @details
	/// Esta función se encarga de completar la cadena de entrada con el Caracter (<b class="paramname">SIMBOLO A UTILIZAR</b>) la cantidad de letras igual al valor que
	/// tiene el parametro <b class="paramname">CANTIDAD TOTAL</b>. El caracter a utilizar se especifica en el parametro de la plantilla. Ejemplo :
	/// @code{.cpp}
	/// 
	/// 	const auto PaddedString = "Cadena para acompletar" <RPad <' '>> 25;
	/// 	
	/// 	// Result : "Cadena para acompletar   "
	/// 	
	/// @endcode
	/// 
	/// @see LPadString RPadString
	/// 
	
	template <char FSymbol , typename TChar = char>
	inline auto RPad = MakeNamedOperator (std::bind (OperatorFillPad <TChar> , RPadString <TChar> , _1 , _2 , static_cast <TChar> (FSymbol)));
	
	/// @}
	
	// -----------------------------------------------------------------------------
	
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Tendremos una función que nos permitirá realizar la respectiva conversión de fechas a un formato especifico.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																DATE FORMAT CORRESPONSAL
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// @addtogroup Utilerias
/// @{
// -----------------------------------------------------------------------------

/// ----------------------------------------------------------------------------
/// 
/// @name Formatos de Fecha
/// @brief Funciones para gestionar fechas y horas utilizando las funciones de la biblioteca estandar de C/C++.
/// 
/// @details
/// 
/// Para obtener la hora actual con el formato de duración especifico se puede usar CurrentTime , para poder darle formato a un tiempo establecido se puede
/// realizar mediante la función FormatDateAPI.
/// 
/// <h2 class="groupheader">Funciones</h2>
/// 
/// @{
/// 
// -----------------------------------------------------------------------------

// Tendremos nuestra función formateadora de datos a un formato respectivo establecido para las cadenas de consulta.

/// ----------------------------------------------------------------------------
//
/// @brief      Formatea la fecha establecida a un formato global establecido por el estandar de C.
///
/// @param[in]  Formato  Formato de la fecha de salida a generar , vease <a href="https://en.cppreference.com/w/cpp/chrono/c/strftime">Reference C++</a>.
/// @param[in]  Tiempo   Tiempo a utilizar para el formateo , por defecto es igual a la hora actual , std::chrono::system_clock::now ().
///
/// @tparam     TClock   Tipo de Sistema de tiempo actual , por defecto system_clock.
///
/// @return     Genera una fecha formateada
/// 
/// @details
/// 
/// Esta función permite realizar el formateo del tiempo especificado utilizando las nuevas utilerias para la gestión del tiempo mediante la clase
/// de system_clock en el espacio de nombres de std::chrono. Para visualizar los comantos para darle formato a la hora se tiene la siguiente tablita :
/// 
/// <b style="font-size: 150%">Formato de Horas : </b>
/// 
/// <img id="fechas_formato" class="fecha-formato" src="fechas_formato_light.jpg" />
/**
@htmlonly
<script type="text/javascript">
	
	// Obtenemos la imagen de las fechas formato.
	
	var ImgFechas = document.getElementById ("fechas_formato")

	// Crearemos y configuramos el viewer para la imágen de las fechas del formato.
		
    const viewer = new Viewer (ImgFechas , {
    	
      inline: false ,
      
      show () {
      	
      	if (document.documentElement.classList.contains ("dark-mode")) {
      	
      		ImgFechas.src = "../../fechas_formato_dark.jpg"
      	
      	}
      	else {
      	
      		ImgFechas.src = "../../fechas_formato_light.jpg"
      	
      	}
	    
	  }
      
    })
    
</script>
@endhtmlonly
**/

template <typename TClock = std::chrono::system_clock>
std::string FormatDateAPI (const std::string & Formato , const std::chrono::time_point <TClock> & Tiempo = std::chrono::system_clock::now ()) {
	
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------
	// 
	// 							Creando Tiempo Formateado
	// 							
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------
	
	// Obtenemos la respectiva conversión al formato de tiempo de C.
	
	time_t CurrentTime = std::chrono::system_clock::to_time_t (Tiempo);
	
	// Ahora crearemos una instancia de un tiempo definido (struct tm) para la conversión del tiempo actual.
	
	struct tm CurrentTime_T;
	
	// Asignaremos el valor.
	
	localtime_s (&CurrentTime_T , &CurrentTime);
	
	// Crearemos un buffer suficientemente grande para almacenar el dato.
	
	char BufferDate [125];
	
	// Limpiaremos el buffer actual.
	
	memset (BufferDate , '\0' , sizeof (BufferDate));
	
	// Imprimiremos el tiempo actual en el formato especificado en nuestro Buffer.
	
	strftime (BufferDate , sizeof (BufferDate) , Formato.c_str () , &CurrentTime_T);
	
	// -----------------------------------------------------------------------------
	
	// Finalmente devolvemos la cadena resultante.
	
	return std::string (BufferDate);
	
	// -----------------------------------------------------------------------------
	
}

// Ahora pasaremos a declarar una función para recuperar nuestro Actual Tiempo en el tipo de duracion que se especifique.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Obtiene la Hora actual en el formato de duración especificado.
///
/// @tparam     TDuration      Tipo de duración al cuál convertir la hora actual (std::chrono::duration). Por default es std::chrono::milliseconds.
///
/// @return     Hora actual en el formato de tiempo especificado.
/// 
/// @details
/// 
/// Esta función utiliza las nuevas funciones de c++ 14 para la gestión del tiempo mediante el espacio de nombres de std::chrono y la clase
/// para la duración (std::chrono::duration).
/// 
// -----------------------------------------------------------------------------

template <typename TDuration = std::chrono::milliseconds>
ALWAYS_INLINE TDuration CurrentTime () {
	
	// Devolvemos la conversión de nuestro tiempo actual al formato de duracion especificado.
	
	return std::chrono::duration_cast <TDuration> (std::chrono::system_clock::now ().time_since_epoch ());
	
	// -----------------------------------------------------------------------------
	
}

/// @}

// Tendremos la seccción para los tratamientos númericos que nos permitirán realizar procesamientos directamente con
// valores de tipo aritmetico.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																			NUMERIC TRAITS
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Dispondremos de un conjunto de operaciones que manipulan cantidades y valores númericos.

/// ----------------------------------------------------------------------------
/// 
/// @defgroup NumericTraits Tratamientos Númericos
/// 
/// @brief Conjunto de funciones para manipular valores númericos , validar y operar en <b>tiempo de compilación</b>.
/// 
/// @details
/// 
/// Se tienen un conjunto de elementos para el tratamiento de tipos en <b>tiempo de compilación</b> , de esta forma se pueden realizar validaciones adicionales
/// que conlleven realizar comparaciones principalmente para determinar si algún conjunto de valores cumple o no con determinado criterio de selección al
/// momento de aplicar en alguna función de todo el repertorio en los distintos módulos de las utilerias.
/// 
/// @subsection Validadores Variables de Validación
/// 
/// Entre los <i>númeric traits</i> se tienen <n>>variables parametrizables</b las cuales tienen como finalidad la de determinar si algún tipo de dato tiene 
/// definido entre sus metodos alguna sobrecarga para determinados operadores.
/// 
/// Para antes de los conceptos de c++ 20 se tienen estas plantillas que realizan validación en tiempo de compilación permitiendo así habilitar o deshabilitar
/// implementaciones en las funciones que utilicen tipos de datos genericos.
/// 
/// En total se cuenta con la siguiente lista de variables de validación :
/// 	<ul>
/// 		<li>@ref IsGEComparable</li>
/// 		<li>@ref IsLEComparable</li>
/// 		<li>@ref IsGComparable</li>
/// 		<li>@ref IsLComparable</li>
/// 		<li>@ref IsEComparable</li>
/// 		<li>@ref IsNEComparable</li>
/// 	</ul>
/// 
/// Para observar la utilidad de estas variables tenemos el siguiente ejemplo donde se define una función que anexa valores que están dentro del rango especificado
/// por el parametro respectivo a un vector resultado.
/// @code{.cpp}
/// 	
/// 	// Función generadora de la sub-lista.
/// 	
/// 	template <typename TNumeric , std::enable_if_t <IsGEComparable <TNumeric> && IsLEComparable <TNumeric> , bool> = true>
/// 	static std::vector <TNumeric> GenerateList (const std::initializer_list <TNumeric> Values , const TLimits <TNumeric> Rango) {
/// 		
/// 		// Vector de números en el rango definido.
/// 		
/// 		std::vector <TNumeric> Numbers;
/// 		
/// 		// Ciclo por cada valor en la lista de valores.
/// 		
/// 		for (auto & Value : Values) {
/// 			
/// 			// Se valida si está en el rango establecido con la función Border.
/// 			
/// 			if (Border (Value , Rango)) {
/// 				
/// 				// Se anexa al vector.
/// 				
/// 				Numbers.push_back (Value);
/// 				
/// 			}
/// 			
/// 		}
/// 		
/// 		// Se devuelve la lista.
/// 		
/// 		return Numbers;
/// 		
/// 	}
/// 	
/// 	// Crearemos la lista con todos los números que están en el rango [1 , 40].
/// 	
/// 	const auto Numeros = GenerateList ({ 0 , 203 , 5304 , 35 , 15 , 05 , 700 , 58 , 20 } , { 1 , 40 });
/// 	
/// 	// Numeros = { 35 , 15 , 5 , 20 };
/// 
/// @endcode
/// 
/// @{
/// 
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							LIMIT TRAITS
// 							
// -----------------------------------------------------------------------------

// Definiremos un tipo de dato para la paridad de limites entre valores.

/// ----------------------------------------------------------------------------
/// 
/// @brief Tipo de dato de paridad para guardar dos valores que representan los Limites <b>Inferior</b> y <b>Superior</b>
/// respectivamente para las funciones de los númeric traits.
/// 
/// @tparam 	TNumeric 		Tipo de dato a utilizar (cualquier dato operable).
/// 
/// @details
/// 
/// Este tipo de dato parametrizable sirve para conjuntar un par de números que representen los limites para operaciones de
/// validación de rangos.
/// 
/// @see Border Between
/// 
// -----------------------------------------------------------------------------

template <typename TNumeric>
using TLimits = std::pair <TNumeric , TNumeric>;

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 					COMPARABLES FUNCTIONS TRAITS
// 							
// -----------------------------------------------------------------------------

// Tendremos unas plantillas de validación para saber si los tipos que tenemos asignados a las funciones de numeric traits
// cumplen con ciertas condiciones.

// -----------------------------------------------------------------------------

// Implementaremos la variable de expresión constante para poder validar si un determinado tipo es comparable con
// el operador >=.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que válida en tiempo de compilación si un tipo de dato es <b>Comparable</b> utilizando
/// el operador respecitvo <b style="color: var(--fragment-keyword);font-size: 120%;">>=</b> (Mayor o igual qué).
/// 
/// @tparam 		TNumeric 		Tipo de dato a validar.
/// @tparam 		Validation 		[opcional] No se utiliza , solamente se reserva para la especialización de la plantilla.
/// 
/// @details
/// 
/// Por medio de esta variable parametrizable es posible conocer si un tipo de dato tiene definido el operador
/// de comparación <b style="color: var(--fragment-keyword);font-size: 120%;">>=</b> en <b>tiempo de compilación</b>.
/// 
/// @note
/// <b class="paramname">TNumeric</b> puede ser cualquier tipo de dato que tenga definida la sobrecarga para el operador
/// de comparación respectivo.
/// 
// -----------------------------------------------------------------------------

template <typename TNumeric , typename Validation = void>
constexpr bool IsGEComparable = false;

// Ahora la versión para comparar con el valor mayor qué.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que válida en tiempo de compilación si un tipo de dato es <b>Comparable</b> utilizando
/// el operador respecitvo <b style="color: var(--fragment-keyword);font-size: 120%;">></b> (Mayor qué).
/// 
/// @tparam 		TNumeric 		Tipo de dato a validar.
/// @tparam 		Validation 		[opcional] No se utiliza , solamente se reserva para la especialización de la plantilla.
/// 
/// @details
/// 
/// Por medio de esta variable parametrizable es posible conocer si un tipo de dato tiene definido el operador
/// de comparación <b style="color: var(--fragment-keyword);font-size: 120%;">></b> en <b>tiempo de compilación</b>.
/// 
/// @note
/// <b class="paramname">TNumeric</b> puede ser cualquier tipo de dato que tenga definida la sobrecarga para el operador
/// de comparación respectivo.
/// 
// -----------------------------------------------------------------------------

template <typename TNumeric , typename Validation = void>
constexpr bool IsGComparable = false;

// Ahora para la variable que determina si es comparable con el operador <=

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que válida en tiempo de compilación si un tipo de dato es <b>Comparable</b> utilizando
/// el operador respecitvo <b style="color: var(--fragment-keyword);font-size: 120%;"><=</b> (Menor o igual qué).
/// 
/// @tparam 		TNumeric 		Tipo de dato a validar.
/// @tparam 		Validation 		[opcional] No se utiliza , solamente se reserva para la especialización de la plantilla.
/// 
/// @details
/// 
/// Por medio de esta variable parametrizable es posible conocer si un tipo de dato tiene definido el operador
/// de comparación <b style="color: var(--fragment-keyword);font-size: 120%;"><=</b> en <b>tiempo de compilación</b>.
/// 
/// @note
/// <b class="paramname">TNumeric</b> puede ser cualquier tipo de dato que tenga definida la sobrecarga para el operador
/// de comparación respectivo.
/// 
// -----------------------------------------------------------------------------

template <typename TNumeric , typename Validation = void>
constexpr bool IsLEComparable = false;

// De la misma manra para el operador respectivo <.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que válida en tiempo de compilación si un tipo de dato es <b>Comparable</b> utilizando
/// el operador respecitvo <b style="color: var(--fragment-keyword);font-size: 120%;"><</b> (Menor qué).
/// 
/// @tparam 		TNumeric 		Tipo de dato a validar.
/// @tparam 		Validation 		[opcional] No se utiliza , solamente se reserva para la especialización de la plantilla.
/// 
/// @details
/// 
/// Por medio de esta variable parametrizable es posible conocer si un tipo de dato tiene definido el operador
/// de comparación <b style="color: var(--fragment-keyword);font-size: 120%;"><</b> en <b>tiempo de compilación</b>.
/// 
/// @note
/// <b class="paramname">TNumeric</b> puede ser cualquier tipo de dato que tenga definida la sobrecarga para el operador
/// de comparación respectivo.
/// 
// -----------------------------------------------------------------------------

template <typename TNumeric , typename Validation = void>
constexpr bool IsLComparable = false;

// Ahora para las comparaciones del operador de igualdad.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que válida en tiempo de compilación si un tipo de dato es <b>Comparable</b> utilizando
/// el operador respecitvo <b style="color: var(--fragment-keyword);font-size: 120%;">==</b> (Igual qué).
/// 
/// @tparam 		TNumeric 		Tipo de dato a validar.
/// @tparam 		Validation 		[opcional] No se utiliza , solamente se reserva para la especialización de la plantilla.
/// 
/// @details
/// 
/// Por medio de esta variable parametrizable es posible conocer si un tipo de dato tiene definido el operador
/// de comparación <b style="color: var(--fragment-keyword);font-size: 120%;">==</b> en <b>tiempo de compilación</b>.
/// 
/// @note
/// <b class="paramname">TNumeric</b> puede ser cualquier tipo de dato que tenga definida la sobrecarga para el operador
/// de comparación respectivo.
/// 
// -----------------------------------------------------------------------------

template <typename TNumeric , typename Validation = void>
constexpr bool IsEComparable = false;

// De la misma manera para el operador Not Equal.

/// ----------------------------------------------------------------------------
/// 
/// @brief Variable de Plantilla que válida en tiempo de compilación si un tipo de dato es <b>Comparable</b> utilizando
/// el operador respecitvo <b style="color: var(--fragment-keyword);font-size: 120%;">!=</b> (Distinto qué).
/// 
/// @tparam 		TNumeric 		Tipo de dato a validar.
/// @tparam 		Validation 		[opcional] No se utiliza , solamente se reserva para la especialización de la plantilla.
/// 
/// @details
/// 
/// Por medio de esta variable parametrizable es posible conocer si un tipo de dato tiene definido el operador
/// de comparación <b style="color: var(--fragment-keyword);font-size: 120%;">!=</b> en <b>tiempo de compilación</b>.
/// 
/// @note
/// <b class="paramname">TNumeric</b> puede ser cualquier tipo de dato que tenga definida la sobrecarga para el operador
/// de comparación respectivo.
/// 
// -----------------------------------------------------------------------------

template <typename TNumeric , typename Validation = void>
constexpr bool IsNEComparable = false;

// Tenemos ahora las especializaciones de las plantillas para cuando se cumple la condición.

// -----------------------------------------------------------------------------

/// @cond NumeritTraitsSpecialization

// Implementaremos la especialización para cuando es comparable con el operador >=.

template <typename TNumeric>
constexpr bool IsGEComparable <TNumeric ,
	std::void_t <decltype (std::declval <TNumeric> () >= std::declval <TNumeric> ())>> = true;

// Implementaremos la especialización para cuando es comparable con el operador >.

template <typename TNumeric>
constexpr bool IsGComparable <TNumeric ,
	std::void_t <decltype (std::declval <TNumeric> () > std::declval <TNumeric> ())>> = true;

// Implementaremos la especialización para cuando es comparable con el operador <=.

template <typename TNumeric>
constexpr bool IsLEComparable <TNumeric ,
	std::void_t <decltype (std::declval <TNumeric> () <= std::declval <TNumeric> ())>> = true;

// Implementaremos la especialización para cuando es comparable con el operador <.

template <typename TNumeric>
constexpr bool IsLComparable <TNumeric ,
	std::void_t <decltype (std::declval <TNumeric> () < std::declval <TNumeric> ())>> = true;

// Tenemos especialización especifica para el operador de igualdad.

template <typename TNumeric>
constexpr bool IsEComparable <TNumeric ,
	std::void_t <decltype (std::declval <TNumeric> () == std::declval <TNumeric> ())>> = true;

// Tenemos la especialización especifica para el operador de desigualdad.

template <typename TNumeric>
constexpr bool IsNEComparable <TNumeric ,
	std::void_t <decltype (std::declval <TNumeric> () != std::declval <TNumeric> ())>> = true;


/// @endcond

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							RANGE COMPARISON
// 							
// -----------------------------------------------------------------------------

// Implementaremos funciones para realizar validación de rangos de números para saber si están dentro del rango o fuera de el
// considerando o no los limites.

// -----------------------------------------------------------------------------

// Tendremos la siguiente función para realizar la validación en tiempo de compilación de los rangos de valores con >=.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Determina si un valor Númerico está dentro del rango [LimitInferior , LimitSuperior] (Contando estos limites).
///
/// @param[in]  Value      Valor a válidar.
/// @param[in]  Limites    Rango de Limites <b>Inferior</b> y <b>Superior</b> respectivamente : [Inferior , Superior]
///
/// @tparam     TNumeric   Tipo de dato Númerico que tenga los operadores (>= y <=) definidos.
///
/// @return     <b style="color: var(--fragment-keyword);font-size: 120%;">True</b> si <b class="paramname">Value</b> está
/// 			dentro del rango detminado por <b class="paramname">Limites</b>.
/// 
/// @details
/// 
/// Es por medio de esta función que es posible saber de manera constante en tiempo de compilación si el valor especificado
/// , está dentro del rango [Inferior , Superior] determinado por el parametro <b class="paramname">Limites</b>.
/// 
/// @note
/// La validación se aplica para el rango [Inferior , Superior] tomando en cuenta estos limites.
/// 
/// @warning
/// El tipo de dato <b class="paramname">TNumeric</b> debe tener definidos los operadores <b>>=</b> y <b><=</b>.
/// 			
// -----------------------------------------------------------------------------

template <typename TNumeric , std::enable_if_t <IsGEComparable <TNumeric> && IsLEComparable <TNumeric> , bool> = true>
static constexpr bool Border (const TNumeric & Value , const TLimits <TNumeric> & Limites) {
	
	// Devolvemos el resultado de comparar el valor con los limites especificados.
	
	return ((Value >= Limites.first) && (Value <= Limites.second));
	
	// -----------------------------------------------------------------------------
	
}

/// ----------------------------------------------------------------------------
/// 
/// @brief      Determina si un valor Númerico está dentro del rango (LimitInferior , LimitSuperior).
///
/// @param[in]  Value      Valor a válidar.
/// @param[in]  Limites    Rango de Limites <b>Inferior</b> y <b>Superior</b> respectivamente : (Inferior , Superior)
///
/// @tparam     TNumeric   Tipo de dato Númerico que tenga los operadores (> y <) definidos.
///
/// @return     <b style="color: var(--fragment-keyword);font-size: 120%;">True</b> si <b class="paramname">Value</b> está
/// 			dentro del rango detminado por <b class="paramname">Limites</b>.
/// 
/// @details
/// 
/// Es por medio de esta función que es posible saber de manera constante en tiempo de compilación si el valor especificado
/// , está dentro del rango (Inferior , Superior) determinado por el parametro <b class="paramname">Limites</b>.
/// 
/// @note
/// La validación se aplica para el rango (Inferior , Superior) , sin tomar en cuenta estos limites.
/// 
/// @warning
/// El tipo de dato <b class="paramname">TNumeric</b> debe tener definidos los operadores <b>></b> y <b><</b>.
/// 			
// -----------------------------------------------------------------------------

template <typename TNumeric , std::enable_if_t <IsGComparable <TNumeric> && IsLComparable <TNumeric> , bool> = true>
static constexpr bool Between (const TNumeric & Value , const TLimits <TNumeric> & Limites) {
	
	// Devolvemos el resultado de comparar el valor con los limites indicados.
	
	return ((Value > Limites.first) && (Value < Limites.second));
	
	// -----------------------------------------------------------------------------
	
}

/// ----------------------------------------------------------------------------
/// 
/// @brief      Determina si un valor Númerico está fuera del rango (LimitInferior , LimitSuperior).
///
/// @param[in]  Value      Valor a válidar.
/// @param[in]  Limites    Rango de Limites <b>Inferior</b> y <b>Superior</b> respectivamente : (Inferior , Superior)
///
/// @tparam     TNumeric   Tipo de dato Númerico que tenga los operadores (> y <) definidos.
///
/// @return     <b style="color: var(--fragment-keyword);font-size: 120%;">True</b> si <b class="paramname">Value</b> está
/// 			fuera del rango detminado por <b class="paramname">Limites</b>.
/// 
/// @details
/// 
/// Es por medio de esta función que es posible saber de manera constante en tiempo de compilación si el valor especificado
/// , está fuera del rango (Inferior , Superior) determinado por el parametro <b class="paramname">Limites</b>.
/// 
/// @note
/// La validación se aplica para el rango (Inferior , Superior) , sin tomar en cuenta estos limites.
/// 
/// @warning
/// El tipo de dato <b class="paramname">TNumeric</b> debe tener definidos los operadores <b>></b> y <b><</b>.
/// 			
// -----------------------------------------------------------------------------

template <typename TNumeric , std::enable_if_t <IsGComparable <TNumeric> && IsLComparable <TNumeric> , bool> = true>
static constexpr bool Outside (const TNumeric & Value , const TLimits <TNumeric> & Limites) {
	
	// Devolvemos el resultado de comparar el valor con los limites indicados.
	
	return ((Value < Limites.first) || (Value > Limites.second));
	
	// -----------------------------------------------------------------------------
	
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

/// @}

// Ahora pasaremos a las utilerias para formateo de numeros.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		NUMBER FORMAT CORRESPONSAL
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// 
/// @name Formatos Númericos
/// @brief Funciones para convertir Cadenas a valores númericos con un formato establecido , y viceversa , converir números a cadenas especificando
/// la cantidad de enteros y decimales.
/// 
/// @details
/// 
/// Con la finalidad de tener un formato númerico especificado se requiere establecer una función para parsear un número
/// desde su expresón númerica y devolver el valor númerico.
///
/// Formato Numerico Entrada : xxxxx.xx
/// Formato Numerico Salida :  xxxxxxxx
///
/// Declaramos e implementaremos la función respectiva para convertir un valor númerico en forma de cadena a un valor numerico
/// en cualquier tipo de dato aceptado.
/// 
/// <h2 class="groupheader">Funciones</h2>
/// 
/// @{
//
// -----------------------------------------------------------------------------

/// ----------------------------------------------------------------------------
/// 
/// @brief      Convierte una cadena STD a un valor númerico de cualquier tipo aritmético.
///
/// @param[in]  Input      Cadena de entrada a Convertir.
/// @param[in]  Default    [Opcional] Valor númerico por defecto en caso de que no se pueda convertir la cadena.
///
/// @tparam     TCast      Tipo de dato al cual Convertir.
///
/// @return     Valor númerico que representa el valor de la cadena de entrada.
/// 
/// @details
/// 
/// Esta función se encarga de convertir una cadena a un valor númerico , lo que puede lograrse con funciones como stod y stof pero de
/// manera generica para cualquier tipo de dato.
/// 
/// @note
/// En caso de que no se pueda convertir la cadena de entrada , se devuelve el valor del parametro <b class="paramname">Default</b> por defecto
/// inicializado en 0.
/// 
/// @see NumberToString
/// 
// -----------------------------------------------------------------------------

template <typename TCast , std::enable_if_t <std::is_arithmetic_v <std::decay_t <TCast>> , bool> = true>
auto StringToNumber (const std::string & Input ,
                                const std::decay_t <TCast> Default = static_cast <std::decay_t <TCast>> (0)) -> std::decay_t <TCast> {
	
	// -----------------------------------------------------------------------------
	// 
	// 							CONVERSION STRING -> NUMERO
	// 							
	// -----------------------------------------------------------------------------
	
	// Tenemos el conversor seguro para cadenas a números aritmeticos de cualquier tipo.
	
	// -----------------------------------------------------------------------------
	
	// Definiremos el tipo de dato sin modificadores.
	
	using TypeNumer = std::decay_t <TCast>;
	
	// -----------------------------------------------------------------------------
	
	// Validamos si la cadena de entrada no está vacia.
	
	if (!Input.empty ()) {
		
		// -----------------------------------------------------------------------------
		// 
		// 							BOOL CAST STRING
		// 							
		// -----------------------------------------------------------------------------
		
		// Validamos si es un tipo aritmetico bool.
		
		if constexpr (std::is_same_v <TypeNumer , bool>) {
			
			// Válidaremos primero si es igual a true para poder especializar en este ambito.
		
			return (ToLower (Input) == "true");
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
		
		// Devolvemos la conversión al tipo especificado.
		
		try {
			
			// -----------------------------------------------------------------------------
			
			// Validaremos si es de tipo integral para realizar lo siguiente.
			
			if constexpr (std::is_integral_v <TypeNumer>) {
				
				// Devolvemos lo siguiente.
				
				return static_cast <TypeNumer> (std::stoll (Input));
				
				// -----------------------------------------------------------------------------
				
			}
			else if constexpr (std::is_floating_point_v <TypeNumer>) {
				
				// Devolvemos lo siguiente.
				
				return static_cast <TypeNumer> (std::stod (Input));
				
				// -----------------------------------------------------------------------------
				
			}
			
			// -----------------------------------------------------------------------------
			
		} catch (...) {
			
			// Devolvemos el valor por default.
			
			return Default;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
		
	}
	
	// -----------------------------------------------------------------------------
	
	// De otro modo devolvemos default.
	
	return Default;
	
}

// -----------------------------------------------------------------------------

// Ahora vamos a constituir la función opuesta la cuál nos convierte cualquier número a su representación en cadena
// con sus respectivos elementos para presentar el punto , numero de decimales y numero de enteros.

/// ----------------------------------------------------------------------------
/// 
/// @brief      Convierte cualquier expresión Númerica a una cadena STD con el formato especifico.
///
/// @param[in]  Input      	Expresión númerica a convertir a una Cadena.
/// @param  	Enteros    	[Opcional] Define cuantos enteros presentar para la representación en cadena.
/// @param  	Decimales   [Opcional] Define cuantos decimales presentar para la representación en cadena.
/// @param  	Punto    	[Opcional] Indica si mostrar el punto decimal en la cadena o no.
///
/// @tparam     TNumber 	Tipo de dato númerico en la entrada. (Aritmetico ó String)
///
/// @return     Cadena STD con la conversión del valor númerico.
/// 
/// @details
/// 
/// Esta función es bastante útil para mostrar números enteros o flotantes en forma de cadena con la cantidad de enteros y decimales que se
/// requiera. Si el valor de enteros supera lo que realmente tiene de valor entero entonces se llena con <b>Ceros a la Izquierda</b>; De la misma
/// manera para los decimales , si se especifican más decimales de los que tiene el número entonces se llena con <b>Ceros a la Derecha</b>.
/// 
/// @note
/// Si el parametro <b class="paramname">Punto</b> es igual a <b style="color: var(--fragment-keyword); font-size: 120%;">true</b> entonces
/// se muestra el punto decimal , en caso contrario no se presenta el punto en la cadena resultado.
/// 
/// @see StringToNUMBER
/// 
// -----------------------------------------------------------------------------

template <typename TNumber>
std::string NumberToString (const TNumber & Input , size_t Enteros = 0u , size_t Decimales = 0u , bool Punto = true) {
	
	// -----------------------------------------------------------------------------
	// 
	// 							CONVERSION NUMERO -> STRING
	// 							
	// -----------------------------------------------------------------------------
	
	// Tenemos el conversor seguro numeros a cadenas de cualquier tipo.
	
	// -----------------------------------------------------------------------------
	
	// Definiremos el tipo de dato sin modificadores.
	
	using TypeNumer = std::decay_t <TNumber>;
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							CONVERSION BOOL
	// 							
	// -----------------------------------------------------------------------------
	
	// Si se tiene un tipo de entrada bool entonces la cadena resultante puede ser true o false.
	
	if constexpr (std::is_same_v <TypeNumer , bool>) {
		
		// Devolvemos true o false , según el caso.
		
		return (Input ? "true" : "false");
		
		// -----------------------------------------------------------------------------
		
	}
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							DESCOMPONER NUMERO
	// 							
	// -----------------------------------------------------------------------------
	
	// Tendremos que descomponer el número que convertiremos primero a cadena mediante el siguiente buffer.
	
	std::stringstream BufferCompuesto;
	
	// Ahora vamos a concatenar nuestro número para poder obtener la cadena del número.
	
	BufferCompuesto << Input;
	
	// Ahora vamos a generar la cadena con el número actual , de la siguiente manera.
	
	const std::string InputString (BufferCompuesto.str ());
	
	// Obtendremos la busqueda de nuestro simbolo separador de enteros y decimales , '.'
	
	const auto Separator = InputString.find_first_of ('.');
	
	// Ahora vamos a separar las partes de acuerdo a este separador para poder asignar lo que serán nuestra
	// cadena de enteros.
	
	const std::string StringEnteros = InputString.substr (0 , Separator);
	
	// Ahora para la parte decimal tendremos la siguiente cadena.
	
	const std::string StringDecimales = ((Separator != std::string::npos) ? InputString.substr (Separator + 1) : std::string ());
		
	// -----------------------------------------------------------------------------
	
	// Finalmente devolvemos las cadenas combinadas y con Pad para la parte izquierda y derecha.
	
	return (LPadString (StringEnteros , Enteros , '0') + (Punto ? "." : "") + RPadString (StringDecimales , Decimales , '0'));
	
	// -----------------------------------------------------------------------------
	
}

// Tenemos una utileria que nos permitirá obtener la salida de ejecutar diferentes comandos de la siguiente manera.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							CURRENT CMD OUTPUT
// 							
// -----------------------------------------------------------------------------

// La siguiente función permitirá realizar la obtención de la salida de un comando ejecutado en el CMD.

template <typename TChar = char , size_t BuffSize = 1024u>
std::basic_string <TChar> CMDOutput (const std::basic_string <TChar> & CurrentCommand , bool cmdPipen = false) {
	
	// Ejecutamos un comando y devolvemos la salida en un tring.
	
	// -----------------------------------------------------------------------------
	// 
	// 								CMD COMMAND PIPEN
	// 							
	// -----------------------------------------------------------------------------
	
	// Validaremos el sistema operativo.
	
	#ifndef _WIN32
	
	// Primero crearemos lo que es nuestro buffer para alojar la salida de nuestro comando.
	
	TChar BufferCMD [BuffSize];
	
	// Limpiaremos la memoria que tenemos.
	
	memset (BufferCMD , '\0' , sizeof (BufferCMD));
	
	// Tenemos el buffer para la salida.
	
	std::basic_stringstream <TChar> BufferOutput;
	
	// Realizaremos un envio diferente
	
	std::unique_ptr <FILE , decltype (&pclose)> CurrentStream (popen (CurrentCommand.c_str () , "r") , pclose);
	
	// Validamos si está abierto correctamente la tuberia.
	
	if (CurrentStream) {
		
		// -----------------------------------------------------------------------------
		
		// Realizaremos la lectura del buffer para poder almacenar los datos leidos.
		
		while (fgets (BufferCMD , sizeof (BufferCMD) , CurrentStream.get ()) != nullptr) {
			
			// Anexaremos el buffer a nuestro buffer de salida.
			
			BufferOutput << BufferCMD;
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
		
	}
	
	// -----------------------------------------------------------------------------
	
	// Finalmente devolvemos el resultado.
	
	return BufferOutput.str ();
	
	// -----------------------------------------------------------------------------
	
	#else
	
	// -----------------------------------------------------------------------------
	
	// Devolveremos la variable de entorno respectiva.
	
	#ifdef _MSC_VER
	
	// Si el compilador es de MSVC entonces creamos el buffer de salida.
	
	char * BufferOutput = nullptr;
	
	// Asignaremos tamaño por default en 0.
	
	size_t BufferSize = 0u;
	
	// Ahora obtendremos el valor de nuestra variable de entorno respectiva.
	
	auto Result = _dupenv_s (&BufferOutput , &BufferSize , CurrentCommand.c_str ());
	
	// Validaremos para continuar.
	
	if ((Result == 0) && BufferOutput) {
	
	// Ahora para el otro caso.
	
	#else
	
	// Validamos con lo siguiente.
	
	if (cmdPipen) {
		
		// -----------------------------------------------------------------------------
		// 
		// 							COMMAND EXECUTER WIN32
		// 							
		// -----------------------------------------------------------------------------
		
		// Para el caso de windows tendremos una utileria que nos permitirá realiza la consulta rápida para la salida de comandos ejecutados en el CMD
		// siendo este proceso de la siguiente forma.
		
		std::stringstream output;
		
		// Crearemos el buffer de salida para poder realizar la escritura de nuestros datos y poder iterar sobre el mismo.
		
		std::array <char , 128u> buffer;
		
		// Limpiaremos el buffer.
		
		memset (buffer.data () , '\0' , buffer.size ());
		
		// Crearemos el puntero para el descriptor de archivo y crearemos una tuberia para poder abrir el cmd y ejecutar el comando en modo lectura.
		
		std::unique_ptr <FILE , decltype (&pclose)> piper (popen (CurrentCommand.c_str () , "r") , pclose);
		
		// Ahora validaremos lo siguiente para poder continuar y leer el siguiente caracter hasta terminar la lectura.
		
		if (piper) while (fgets (buffer.data () , buffer.size () , piper.get ())) output << buffer.data ();
		
		// Finalmente devolveremos nuestro buffer de salida.
		
		return output.str ();
		
		// -----------------------------------------------------------------------------
		
	}
	else if (const char * BufferOutput = std::getenv (CurrentCommand.c_str ())) {
	
	// -----------------------------------------------------------------------------
	
	#endif // _MSC_VER
		
		// Devolveremos el valor respectivo.
		
		return std::string (BufferOutput);
		
		// -----------------------------------------------------------------------------
		
	}
	
	// De otro modo devolveremos algo vacio.
	
	return std::string ();
	
	// -----------------------------------------------------------------------------
	
	#endif // _WIN32
	
}

// Ahora para el tratamiento de los paths tenemos esto.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// 
// 							CURRENT SYSTEM PATH
// 							
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// Tenemos una función encargada de devolver un string a partir de una cadena que determina el path actual o la variable
// de entorno que se tega en función de su respectivo.

// -----------------------------------------------------------------------------

// Tenemos la clase para las excepciones que determina el error a presentar cuando un path no existe o algo relacionado
// a la variable de entorno.

class PathException : public std::exception {
	
	// -----------------------------------------------------------------------------
	// 
	// 							PATH PRIVADOS
	// 							
	// -----------------------------------------------------------------------------
	
	// Tenemos los siguientes elementos privados.
	
	private :
	
		// Tenemos lo siguiente que será la parte de los datos para la variable establecida.
		
		std::string CurrentPath;
		
		// Ahora tenemos el mensaje actual que estaremos asignand.
		
		std::string CurrentMessage;
		
		// Tenemos ahora lo publico.
		
		// -----------------------------------------------------------------------------
	
	// Tenemos lo siguiente para establecer lo reference a los datos publicos.
	
	// -----------------------------------------------------------------------------
	// 
	// 							PATH PUBLICOS
	// 							
	// -----------------------------------------------------------------------------
	
	// Tenemos lo siguiente que es la parte de los metodos sobreescritos.
	
	public :
		
		// -----------------------------------------------------------------------------
		
		// Tenemos lo siguiente que será el constructor para nuestro respectiva excepción.
		
		PathException (const std::string & ErrorPath) : CurrentPath (ErrorPath) {
			
			// Asignaremos el mensaje respectivo para esta excepción.
			
			CurrentMessage = StringPrintf (" >>| Error con el Path [%s] \n" , CurrentPath.c_str ());
			
			// -----------------------------------------------------------------------------
			
		}
		
		// Tenemos ahora lo que es respectivametne la parte de deducir el mensaje.
		
		const char * what () const noexcept override {
			
			// Devolveremos los datos internos del mensaje.
			
			return CurrentMessage.c_str ();
			
			// -----------------------------------------------------------------------------
			
		}
		
		// -----------------------------------------------------------------------------
	
};

// Tenemos lo siguiente para poder determinar el string que representa la variable de entorno y en caso de no
// existir mandaría la excepción.

template <typename TChar = char>
std::basic_string <TChar> GetEnviromentPath (const std::basic_string <TChar> & CurrentEnviroment) {
	
	// Tenemos lo siguiente para poder el entorno.
	
	// -----------------------------------------------------------------------------
	
	// Obtendremos el path desglozado de nuestra variable de entorno.
	
	#ifdef __GNUC__
	
	// Tenemos el siguiente comando.
	
	std::basic_string <TChar> CurrentCommand (StringPrintf (R"(echo $%s)" , CurrentEnviroment.c_str ()));
	
	// -----------------------------------------------------------------------------
	
	#else
	
	// Asignaremos simplemente la referencia.
	
	const auto & CurrentCommand = CurrentEnviroment;
	
	// -----------------------------------------------------------------------------
	
	#endif // __GNUC__
	
	// const char * CurrentEnviromentPath = std::getenv (CurrentEnviroment.c_str ());
	
	const std::basic_string <TChar> CurrentEnviromentPath (CMDOutput (CurrentCommand));
	
	// Validaremos el siguiente entorno para poder continuar.
	
	if (CurrentEnviromentPath.empty ()) {
		
		// -----------------------------------------------------------------------------
		
		// Tenemos lo siguiente para poder lanzar la excepción de la siguiente manera.
		
		throw PathException (CurrentEnviroment);
		
		// -----------------------------------------------------------------------------
		
	}
	
	// Devolveremos el path referente a esta variable de entorno en caso de especificarse.
	
	return CurrentEnviromentPath;
	
	// -----------------------------------------------------------------------------
	
}

// Tenemos un alias para poder hacerlo con un const std::string normal.

ALWAYS_INLINE std::string GetEnviromentPath (const char * const CurrentEnviroment) {
	
	// Devolveremos  la llamada a nuestro entorno.
	
	return GetEnviromentPath (std::string (CurrentEnviroment));
	
	// -----------------------------------------------------------------------------
	
}

// Ahora definiremos una utileria para poder crear un hash a partir de un determinado string de la siguiente forma.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// 
// 							HASH CODING SETTER
// 							
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// Tenemos lo siguiente que es un template para poder aplicar y obtener un respectivo hash dependiendo lo que estemos mandando.

template <typename TClass>
requires requires (TClass Value) {
	
	// -----------------------------------------------------------------------------
	
	// Requerimos que sea default-constructible.
	
	requires std::is_default_constructible_v <TClass>;
	
	// Aplicaremos el hash sobre el valor para saber que existe.
	
	{ std::hash <TClass> { } (Value) } -> std::convertible_to <size_t>;
	
	// -----------------------------------------------------------------------------
	
}
ALWAYS_INLINE static size_t GetHash (const TClass & Value = TClass ()) {
	
	// -----------------------------------------------------------------------------
	
	// Devolveremos un hash a nuestro respectivo tipo de dato.
	
	return std::hash <TClass> { } (Value);
	
	// -----------------------------------------------------------------------------
	
}

// Ahora vamos a realizar una función en tiempo de compilación que nos permita realizar un pequeño algoritmo de XOR para poder
// generar un hash a partir de un array de datos.

template <std::convertible_to <size_t> TChar = char>
static constexpr size_t GenerateHash (TChar * Array , size_t ArraySize = 0u) {
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							GENERATE HASH XOR
	// 							
	// -----------------------------------------------------------------------------
	
	// El resultado de la salida será guardado en el siguiente.
	
	size_t Output = 0u;
	
	// Ahora tenemos el siguiente que es el limite establecido para este array si tenemos el valor en 0 entonces aplicaremos un
	// char_traits sobre el array para encontrar el terminador y contabilizar los elementos en ese array.
	
	const size_t CurrentLimit = (ArraySize ? ArraySize : std::char_traits <TChar>::length (Array));
	
	// Ahora vamos a realizar el algoritmo sobre el array entero.
	
	for (size_t i = 0 ; i < CurrentLimit ; ++ i) {
		
		// Vamos a aplicar un XOR y asignarlo a la salida con el valor del array.
		
		Output ^= static_cast <size_t> (Array [i]);
		
		// -----------------------------------------------------------------------------
		
	}
	
	// Finalmente devolveremos el resultado.
	
	return Output;
	
	// -----------------------------------------------------------------------------
	
}

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							UTILERIAS MISCELANEAS
// 							
// -----------------------------------------------------------------------------

// Generador de cadenas aleatorio.

CYTTEK_API std::string GenerateRandomStrings (int minValue , int maxValue, int minLength , int maxLength , bool addLetters = false);

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Finalizamos el modulo para el caso del doxygen.

/// @}

// -----------------------------------------------------------------------------

// Finalizamos la definición del contenido del include.

#endif // CYTTEK_UTILITY

/// @}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
