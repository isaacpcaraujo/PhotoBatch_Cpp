#include <iostream>
#include <iomanip>
#include <array>

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