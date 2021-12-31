#include <iostream>
#include <iomanip>

#include "ArgumentParser.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "pt_BR");
	setlocale(LC_NUMERIC, "en_US");

	ArgumentParser argParser;
	argParser.RegisterFlag("rename");
	argParser.RegisterFlag("convert");
	argParser.RegisterFlag("resize");
	argParser.RegisterFlag("scale");
	argParser.RegisterOption("folder");
	argParser.RegisterOption("amount");

	argParser.Parse(argc, argv);

	std::cout << std::boolalpha << "Rename: " << argParser.GetFlag("rename") << std::endl;
	std::cout << std::boolalpha << "Convert: " << argParser.GetFlag("convert") << std::endl;
	std::cout << std::boolalpha << "Resize: " << argParser.GetFlag("resize") << std::endl;
	std::cout << std::boolalpha << "Scale: " << argParser.GetFlag("scale") << std::endl;
	std::cout << std::boolalpha << "Folder: " << argParser.GetOptionAs<const std::string&>("folder") << std::endl;
	std::cout << std::boolalpha << "Amount: " << argParser.GetOptionAs<const std::string&>("amount") << std::endl;
	std::cout << "Amount(Float): " << argParser.GetOptionAs<float>("amount") << std::endl;
	std::cout << "Amount(Int): " << argParser.GetOptionAs<int>("amount") << std::endl;

	return 0;
}