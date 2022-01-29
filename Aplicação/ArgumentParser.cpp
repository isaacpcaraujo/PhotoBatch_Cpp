#include "ArgumentParser.h"
#include "Utils.h"

#include <algorithm>

void ArgumentParser::RegisterFlag(const std::string& flag)
{
	if (!flag.empty())
	{
		m_Flags[flag] = false;
	}
}

void ArgumentParser::RegisterOption(const std::string& option)
{
	if (!option.empty())
	{
		m_Options[option] = "";
	}
}

// Retorna se a Flag foi registrada
bool ArgumentParser::IsFlagRegistered(const std::string& flag) const
{
	if (!flag.empty())
	{
		return m_Flags.count(flag) == 1;
	}

	return false;
}


// Retorna se a Opção foi registrada
bool ArgumentParser::IsOptionRegistered(const std::string& option) const
{
	if (!option.empty())
	{
		return m_Options.count(option) == 1;
	}

	return false;
}


bool ArgumentParser::GetFlag(const std::string& flag) const
{
	if (!flag.empty())
	{
		// O termo "auto" deduz o tipo de retorno do método "find".
		auto flagIt = m_Flags.find(flag);
		if (flagIt != std::end(m_Flags))
		{
			// Retorna o valor associado ao mapa m_Flags.
			return flagIt->second;
		}
	}

	return false;
}

const std::string& ArgumentParser::GetOption(const std::string& option) const
{
	if (!option.empty())
	{
		// O termo "auto" deduz o tipo de retorno do método "find".
		auto optionIt = m_Options.find(option);
		if (optionIt != std::end(m_Options))
		{
			// Retorna o valor associado ao mapa m_Flags.
			return optionIt->second;
		}
	}

	static std::string EmptyOption = "";

	return EmptyOption;
}

float ArgumentParser::GetOptionAsFloat(const std::string& option) const
{
	const std::string& optionValue = GetOption(option);

	if (!optionValue.empty())
	{
		return std::stof(optionValue);
	}

	return -1;
}

int ArgumentParser::GetOptionAsInt(const std::string& option) const
{
	const std::string& optionValue = GetOption(option);

	if (!optionValue.empty())
	{
		return std::stoi(optionValue);
	}

	return -1;
}

void ArgumentParser::SetHelpMessage(const std::string& helpMessage)
{
	m_HelpMessage = helpMessage;
}

const std::string& ArgumentParser::GetHelpMessage() const
{
	return m_HelpMessage;
}

void ArgumentParser::Parse(int argc, char* argv[])
{
	if (argc > 1 && argv != nullptr)
	{
		for (int i = 1; i < argc; ++i)
		{
			std::string arg = Utils::ToLower(argv[i]);
			// Os aragumentos devem ter pelo menos 3 caracteres
			// O préfixo "--" e pelo menos um terceiro caracter
			if (arg.length() >= 3)
			{
				if (arg[0] == '-' && arg[1] == '-')
				{
					// Remove o préfixo "--" da string arg.
					arg = arg.substr(2);

					if (arg.find_first_of('=') != std::string::npos)
					{
						// Opções 
						const size_t equalSignPos = arg.find('=');
						if (equalSignPos != std::string::npos)
						{
							// Divide a opção em chave e valor
							std::string optionName = arg.substr(0, equalSignPos);
							std::string optionValue = arg.substr(equalSignPos + 1);

							auto optionIt = m_Options.find(optionName);
							if (optionIt != std::end(m_Options))
							{
								// Opção registrada.
								optionIt->second = optionValue;
							}
						}
					}

					else
					{
						// Flags
						auto flagIt = m_Flags.find(arg);
						if (flagIt != std::end(m_Flags))
						{
							// Caso encontre uma flag registrada, o valor booleano do mapa é alterado para true.
							flagIt->second = true;
						}
					}
				}
			}
		}
	}
}