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
		static constexpr const char* Amount = "amount";
		static constexpr const char* Prefix = "prefix";
		static constexpr const char* StartNumber = "startnumber";
		static constexpr const char* From = "from";
		static constexpr const char* To = "to";
	}

}

const std::string& GetInvalidCharacters()
{
	static const std::string invalidCharacters = "\\/*?\"<>|:";
	return invalidCharacters;
}

bool HasInvalidChars(const std::string& str)
{
	const bool bHasInvalidChars = str.find_first_of(GetInvalidCharacters()) != std::string::npos;
	return bHasInvalidChars;
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
	if (!filter.empty() && HasInvalidChars(filter))
	{
		throw std::invalid_argument("O filtro não pode conter " + GetInvalidCharacters());
	}

	// Valida o modo Resize
	if (bResizeMode)
	{
		int width = 0;
		int height = 0;

		try
		{
			width = argParser.GetOptionAs<int>(Args::Opts::Width);
			height = argParser.GetOptionAs<int>(Args::Opts::Height);
		}
		catch (const std::invalid_argument& exception)
		{
			throw std::invalid_argument("O valor informado para Width ou Height não são números válidos!");
		}

		if (width <= 0 || height <= 0)
		{
			throw std::invalid_argument("Width e Height devem ser maiores que 0!");
		}

		if (filter.empty())
		{
			throw std::invalid_argument("O filter não pode estar vazio no modo Resize!");
		}

	}

	// Valida o modo Scale.
	if (bScaleMode)
	{
		float amount = 0.0f;

		try
		{
			amount = argParser.GetOptionAs<float>(Args::Opts::Amount);
		}
		catch (const std::invalid_argument& exception)
		{
			throw std::invalid_argument("O valor informado para Amount não é um número válido!");
		}

		if (amount <= 0.0f)
		{
			throw std::invalid_argument("O Amount deve ser maior que 0!");
		}

		if (filter.empty())
		{
			throw std::invalid_argument("O filter não pode estar vazio no modo Scale!");
		}
	}
	
	if (bRenameMode)
	{
		int startNumber = -1;
		const std::string prefix = argParser.GetOptionAs<const std::string&>(Args::Opts::Prefix);

		try
		{
			startNumber = argParser.GetOptionAs<int>(Args::Opts::StartNumber);
		}
		catch (const std::invalid_argument& exception)
		{
			throw std::invalid_argument("O valor informado para StartNumber não é um número válido!");
		}

		if (startNumber < 0)
		{
			throw std::invalid_argument("O StartNumber deve ser maior ou igual a 0!");
		}

		if (filter.empty() || HasInvalidChars(prefix))
		{
			throw std::invalid_argument("O prefix não pode estar vazio, nem conter " + GetInvalidCharacters());
		}
	}

	// Validar o modo Convert
	if (bConvertMode)
	{
		const std::string from = argParser.GetOptionAs<const std::string&>(Args::Opts::From);
		const std::string to = argParser.GetOptionAs<const std::string&>(Args::Opts::To);
		const std::array<std::string, 2> convertOptions = { "png", "jpg" };

		const bool bIsFromValid = std::find(std::begin(convertOptions), std::end(convertOptions), from) != std::end(convertOptions);
		const bool bIsToValid = std::find(std::begin(convertOptions), std::end(convertOptions), to) != std::end(convertOptions);

		if (!bIsFromValid || !bIsToValid)
		{
			throw std::invalid_argument("From e To devem ser diferentes");
		}
	}

}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "pt_BR");
	setlocale(LC_NUMERIC, "en_US");

	// Instanciando a Classe ArgumentParser
	ArgumentParser argParser;

	// Registra as Flags do PhotoBatch
	argParser.RegisterFlag(Args::Flags::Rename);
	argParser.RegisterFlag(Args::Flags::Convert);
	argParser.RegisterFlag(Args::Flags::Resize);
	argParser.RegisterFlag(Args::Flags::Scale);

	// Registra as Opções do PhotoBatch
	argParser.RegisterOption(Args::Opts::Folder);
	argParser.RegisterOption(Args::Opts::Filter);
	argParser.RegisterOption(Args::Opts::Width);
	argParser.RegisterOption(Args::Opts::Height);
	argParser.RegisterOption(Args::Opts::Amount);
	argParser.RegisterOption(Args::Opts::Prefix);
	argParser.RegisterOption(Args::Opts::StartNumber);
	argParser.RegisterOption(Args::Opts::From);
	argParser.RegisterOption(Args::Opts::To);

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