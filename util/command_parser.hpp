
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		MODULO UTILITY : PARSEADOR DE COMANDOS
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Este modulo de utilerias contempla una herramienta de apoyo que es el parseador de comandos el cuál será de ayuda para poder realizar acciones conforme se
// parseen los comandos de la linea de entrada de un programa. Para esto tenemos lo siguiente.

// -----------------------------------------------------------------------------

// Primero declaramos nuestro elemento para la seguridad de nuestro aplitcativo de la siguiente forma.

#pragma once

// Ahora declara nuestra macro guard para nuestro archivo de cabecera actual.

#ifndef CYTTEK_COMMAND_PARSER
#define CYTTEK_COMMAND_PARSER

// Ahora vamos a realizar la inclusión de todos los elementos base para poder utilizar nuestro parseador de comandos.

// -----------------------------------------------------------------------------
// 
// 							INCLUDES STD ESTANDAR
// 							
// -----------------------------------------------------------------------------

// Incluiremos primero nuestra sbases para la entrada y ssalida estandar de c.

#include <stdio.h>
#include <stdlib.h>

// Ahora para el manejo y contro lde cadenas strings tenemos lo siguiente.

#include <string.h>
#include <string>

// Ahora vamos a incluir algunos erncabezados normales para las utilerias de c++ 20

#include <utility>
#include <type_traits>

// Incluiremos las experesiones regulares para poder conformar nuestro validador de tokens.

#include <regex>

// Incluiremos el vector de elementos y el inicializador de lista para poder crear el contenido de una cierta forma.

#include <initializer_list>
#include <vector>

// Ahora pasaremos a incluir lo siguiente para poder continuar de la siguiente maner.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 
// 							CYTTEK CORE UTILITY
// 							
// -----------------------------------------------------------------------------

// Incluiremos nuestras utilerias del core para realizar lo siguiente.

#include "core.hpp"

// Ahora pasaremos a incluir las utilerias de nuestro respectivo cyttek para poder hacer uso de funciones auxiliares.

#include "utility.hpp"

// Ahora lo siguiente será definir los elementos para nuestra clase virtual del parser de comandos.

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//																		CLASE PARA PARSER COMMAND
// 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Para poder realizar nuestro parseador de comandos requerimos hacer una clase que nos permita contener los metodos virtuales para cuando cada comando que
// se desee parsear se vaya obteniendo de la cadena de entrada. De la siguiente manera estaremos realizando una invocación a este metodo por cada coamdno
// de la linea de argumentos que estemos pasando.

// -----------------------------------------------------------------------------

// Ahora lo que haremos será declararnos una estructura simple que contendrá toda la información necesaria para que el metodo respectivo contenga su respectiva
// info y pueda validar como proceder con el comando.

// -----------------------------------------------------------------------------
// 
// 							COMMAND TOKEN STRUCT
// 							
// -----------------------------------------------------------------------------

// Declaremos nuestra respectiva estructura que contedrá valores importantes para validar cuando se realice la implementación en las subclases y por cada
// comando que exista en la linea de aregumentos enviada a nuestro metodo rparse.

struct CommandArgument {
	
	// Tenemos los siguientes atributos para un comando determinado.
	
	// -----------------------------------------------------------------------------
	// 
	// 							COMMAND ATTRIBUTES
	// 							
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	
	// El primer elemento es una bandear que nos permite saber si el elemento actual puede contar como válido o no según el criterio de cada clase.
	
	bool valid = false;
	
	// Tenemos como siguiente elemento el contador del argumento respectivo.
	
	int tokenCount = 0;
	
	// Ahora tenemos como siguiente elemento la cadena de información general de todo el token que tiene todo el string con los datos contenidos.
	
	std::string tokenFull;
	
	// Ahora el siguiente es la cadena que contempla únicamente el valor.
	
	std::string tokenValue;
	
	// Ahora para el caso de que contemos con un token de estilo "camp=value" entonces pasaremos a generar lo siguiente.
	
	std::string tokenCampFull;
	
	// Ahora para el token del campo con su respectivo valor tenemos esto.
	
	std::string tokenCampValue;
	
	// Y asi mismo tendremos la lista de los elementos en ese token delimitados por el cortador de valores respectivo.
	
	std::vector <std::string> tokenCampDatas;
	
	// Ahora algunos operadores auxiliares para poder valida rápidamente lo siguiente.
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							METODOS AUXILIARES
	// 							
	// -----------------------------------------------------------------------------
	
	// Para poder validar rápidamente si el comando es válido o no tenemos la sobrecarga al operador bool de la siguiente forma.
	
	ALWAYS_INLINE operator bool () const noexcept {
		
		// Devolveremos el valor de nuestro campo respectivo.
		
		return (valid && !tokenFull.empty ());
		
		// -----------------------------------------------------------------------------
		
	}
	
	// -----------------------------------------------------------------------------
	
};

// Declaramos entonces la siguiente clase para poder tener este elemento a la mano.

// -----------------------------------------------------------------------------
// 
// 							CLASE PARSER COMMAND
// 							
// -----------------------------------------------------------------------------

// Declaramos la clase del parser command de la siguiente forma.

class CYTTEK_API ParserCommand {
	
	// Comenzaremos primero por la declaración de nuestros elementos privados para esta clase que necesitaremos tener a la mano cuando parseamos los comandos-
	
	// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	// 
	// 							PROPIEDADES PRIVADAS
	// 							
	// -----------------------------------------------------------------------------
	
	// Declaramos las variables y propiedades que estaremos utilizando cuando el parser esté funciuonando.
	
	private :
		
		// -----------------------------------------------------------------------------
		
		// Para empezar necesitaremos registrar cual será nuestra lista de elementos para identificar cuando un respectivo token es un comando valido.
		
		std::vector <std::string> commandPrefix;
		
		// Ahora para poder realizar la creación o asignación de nuestra experesión regular tendremos lo siguiente para poder validar.
		
		std::regex commandExpression;
		
		// Algunos valores por defecto para nuestro parseador de comandos son los siguientes.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							CURRENT PREFIX DEFAULT.
		// 							
		// -----------------------------------------------------------------------------
		
		// Tenemos el prefijo por default que utiliza nuestra clase si no se le especifica alguno.
		
		static constexpr const char * commandPrefixDefault = R"(--)";
		
		// Para el separador de campos tenemos esto.
		
		char commandCampSeparator = '-';
		
		// Para poder asignar un valor necesitamos un cacter que indique que la expresión va a establecer un valor de un campo.
		
		char commandValueOperator = '=';
		
		// Ahora para separar valores de campos en el caso de que nuestra expresión a evaluar contenga varios valores de resultado tenemos esto.
		
		char commandCampValueSeparator = ',';
		
		// Tendremos una expresión en formato de c-printf para conformar el regex por default que se está manejando.
		
		static constexpr const char * regexFormat = R"((?:%s)([[:alnum:]_.]+)([%c]([[:alnum:]_.-]*)%c([[:print:]_. \[\]\{\}\<\>\:%c]+))*)";
		
		// -----------------------------------------------------------------------------
	
	// Ahora pasaremos a la definición de los elementos publicos para poder continuar.
	
	// -----------------------------------------------------------------------------
	// 
	// 							ELEMENTOS PUBLICOS
	// 							
	// -----------------------------------------------------------------------------
	
	// Realizaremos lo siguiente para poder establecer la información.
	
	public :
		
		// -----------------------------------------------------------------------------
		
		// Ahora vamos con la declaración de todos los constructores y metodos publicos para nuestra clase actual.
		
		// -----------------------------------------------------------------------------
		// 
		// 							CONSTRUCTORES
		// 							
		// -----------------------------------------------------------------------------
		
		// Tenemos primero nuestro constructor vacio para poder inicializar nuestro elemento por default.
		
		ParserCommand ();
		
		// Declaramos nuestro siguiente constructor para poder construir nuestra lista de inicialización con los elementos para considerar.
		
		ParserCommand (std::initializer_list <std::string> currentPrefix , char campSeparator = '-' , char valueOperator = '=' , char campValueSeparator = ',');
		
		// Ahora el constructor que recibe el respectivo regular expression para con este elemento poder parsear los comandos respectivos.
		
		ParserCommand (const std::regex & commandRegex);
		
		// Ahora pasaremos a la función principal a ejecutar para el parseo de comandos respectivos.
		
		// -----------------------------------------------------------------------------
		
		// -----------------------------------------------------------------------------
		// 
		// 							MAIN PROCCESSS
		// 							
		// -----------------------------------------------------------------------------
		
		// Declaramos nuestro procesador de elementos para poder iterar por todos los que conlleva nuestra clase de la siguiente forma.
		
		int Parse (size_t argumentSize , char ** argumentValues);
		
		// -----------------------------------------------------------------------------
		
	// Tendremos un metodos protegido virtual el cuál será implementado por la subclase para cada comando que el parser encuentre.
	
	// -----------------------------------------------------------------------------
	// 
	// 							COMANDOS VIRTUALES
	// 							
	// -----------------------------------------------------------------------------
	
	// Implementaremos la parte protegida para ser implementada en las clases que deriven directamente de esta.
	
	protected :
		
		// -----------------------------------------------------------------------------
		
		// Declaramos nuestros metodos respectivos que deberan ser implementados por las subclases con la finalidad de darle funciones
		// a cada comando en especifico que se vaya obteniendo.
		
		// -----------------------------------------------------------------------------
		// 
		// 							PARSE COMMAND RESULT
		// 							
		// -----------------------------------------------------------------------------
		
		// Tenemos primero nuestro metodo abstracto que se invoca cada vez que nuestro parser se encuentra con un comando nuevo.
		
		virtual bool ExecuteCommand (const CommandArgument & commandData) {
			
			// Devolveremos simplemente un false.
			
			return false;
			
			// -----------------------------------------------------------------------------
			
		}
	
		// Ahora lo siguiente que tenemos es un metodo para parseo de regex mathches , este es opciónal pero si se quiere personalizar
		// la manera en la que se generan los command arguments entonces es necesario implementarlo en cada sub clase.
		
		virtual CommandArgument CreateCommand (const std::smatch & currentResult);
		
		// -----------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------
	
};

// Ahora tendremos una funcion auxiliar que nos permita realizar el parseo de un string al formato char ** de salida y con el contador establecido en la cantidad
// de elementos leidos desde dicho string de la siguiente forma.

CYTTEK_API size_t ConformCommands (const std::string & currentString , char *** argumentListOutput = nullptr);

// -----------------------------------------------------------------------------

// Finalmente cerraremos nuestro command parser de la siguiente forma.

#endif // CYTTEK_COMMAND_PARSER

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
