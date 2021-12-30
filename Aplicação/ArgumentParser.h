#pragma once

#include <string>
#include <map>

/* Classe utilizada para ler os argumentos da linha de comando.
*
*	ArgumentParser argParser;
*	argParser.RegisterFlag("rename");
*	argParser.Parse(argc, argv);
*	std::cout << std::boolalpha << "Rename: " << argParser.GetFlag("rename") << std::endl;
*
*/
class ArgumentParser
{
public:
	// Registra uma Flag usada durante o parse.
	void RegisterFlag(const std::string& flag);

	// Registra uma Opção usada durante o parse.
	void RegisterOption(const std::string& option);

	// Obtem o valor de uma flag obtida durante o parse.
	bool GetFlag(const std::string& flag);

	// Obtem o valor de uma opção obtida durante o parse.
	const std::string& GetOption(const std::string& option) const;
	
	// Obtem o valor de uma opção convertida para float.
	float GetOptionAsFloat(const std::string& option) const;

	// Faz o parse da lista de argumentos em argv.
	void Parse(int argc, char* argv[]);

	
private:
	// Declarando Dicionários para nossas Flags e Options.
	std::map<std::string, bool> m_Flags;
	std::map<std::string, std::string> m_Options;
};