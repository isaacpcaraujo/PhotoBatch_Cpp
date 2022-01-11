#include <iostream>
#include <iomanip>
#include <array>
#include <filesystem>

#include "ArgumentParser.h"

namespace Args
{
	namespace Flags
	{
		static constexpr const char* Rename = "rename";
		static constexpr const char* Convert = "convert";
		static constexpr const char* Resize = "resize";
		static constexpr const char* Scale = "scale";
	}

	namespace Opts
	{
		static constexpr const char* Folder = "folder";
		static constexpr const char* Filter = "filter";
		static constexpr const char* Width = "width";
		static constexpr const char* Height = "height";
	}

}

void ValidateArguments(const ArgumentParser& argParser)
{
	// Ter as flags que o ArgumentParser identificou

	const bool bRenameMode = argParser.GetFlag(Args::Flags::Rename);
	const bool bConvertMode = argParser.GetFlag(Args::Flags::Convert);
	const bool bResizeMode = argParser.GetFlag(Args::Flags::Resize);
	const bool bScaleMode = argParser.GetFlag(Args::Flags::Scale);

	
	// Cria um array com os modos: std::array e std::count.
	const std::array<bool, 4> modes = { bRenameMode , bConvertMode, bResizeMode, bScaleMode };
	const std::ptrdiff_t numActiveModes = std::count(std::begin(modes), std::end(modes), true);

	// Verifica se somente um modo do PhotoBatch foi selecionado.

	if (numActiveModes!=1)
	{
		// Se houver mais de um modo ativo, lança uma exceção.
		throw std::invalid_argument("Somente um modo pode estar ativo!");
	}

	
	// Obtem as opções a serem validadas 
	const std::string folder = argParser.GetOptionAs<const std::string&>(Args::Opts::Folder);
	const std::string filter = argParser.GetOptionAs<const std::string&>(Args::Opts::Filter);
	
	// Verifica se a string da pasta de arquivos está vazia.
	if (folder.empty())
	{
		throw std::invalid_argument("É necessário uma pasta de arquivos!");
	}

	// Verifica se a pasta de arquivos existe.
	if (!std::filesystem::exists(folder))
	{
		throw std::invalid_argument("A pasta de arquivos não existe!");
	}

	// Verifica se a string da pasta de arquivos está vazia.
	if (!filter.empty())
	{
		const std::string invalidCharacters = "\\/*?\"<>|:";
		if (filter.find_first_of(invalidCharacters) != std::string::npos)
		{
			throw std::invalid_argument("O filtro não pode conter " + invalidCharacters);
		}
	}
	
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "pt_BR");
	setlocale(LC_NUMERIC, "en_US");

	ArgumentParser argParser;
	argParser.RegisterFlag(Args::Flags::Rename);
	argParser.RegisterFlag(Args::Flags::Convert);
	argParser.RegisterFlag(Args::Flags::Resize);
	argParser.RegisterFlag(Args::Flags::Scale);
	argParser.RegisterOption(Args::Opts::Folder);
	argParser.RegisterOption(Args::Opts::Filter);
	argParser.RegisterOption(Args::Opts::Width);
	argParser.RegisterOption(Args::Opts::Height);

	argParser.Parse(argc, argv);

	try
	{
		ValidateArguments(argParser);
	}
	catch (const std::exception& exception)
	{
		std::cerr << exception.what() << std::endl;
	}

	return 0;
}