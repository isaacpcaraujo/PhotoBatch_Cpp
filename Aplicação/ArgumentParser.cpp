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

bool ArgumentParser::GetFlag(const std::string& flag)
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

void ArgumentParser::Parse(int argc, char* argv[])
{
	if (argc > 1)
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

