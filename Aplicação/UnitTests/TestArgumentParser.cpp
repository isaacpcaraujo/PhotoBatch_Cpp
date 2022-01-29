#include <gtest/gtest.h>
#include <ArgumentParser.h>
#include <Utils.h>
#include <array>


// TESTANDO O MÉTODO REGISTER FLAG
TEST(TestArgumentParser, RegisterFlag)
{
	// Criar um objeto do Argument Parser
	ArgumentParser argParser;

	// Verificar o estado antes da operação
	EXPECT_FALSE(argParser.IsFlagRegistered("MyFlag"));

	// Registrar a Flag
	// Chamar a função sendo testada
	argParser.RegisterFlag("MyFlag");

	// Verifica o estado depois da operação
	EXPECT_TRUE(argParser.IsFlagRegistered("MyFlag"));
}

TEST(TestArgumentParser, RegisterFlag_Whitespace)
{
	// Criar um objeto do Argument Parser
	ArgumentParser argParser;

	// Registrar a Flag
	// Chamar a função sendo testada
	argParser.RegisterFlag("My Flag");

	// Verifica o estado depois da operação
	EXPECT_TRUE(argParser.IsFlagRegistered("My Flag"));
}

// TESTANDO O MÉTODO REGISTER OPTION
TEST(TestArgumentParser, RegisterOption)
{
	// Criar um objeto do Argument Parser
	ArgumentParser argParser;

	// Verificar o estado antes da operação
	EXPECT_FALSE(argParser.IsOptionRegistered("MyOption"));

	// Registrar a Option
	// Chamar a função sendo testada
	argParser.RegisterOption("MyOption");

	// Verifica o estado depois da operação
	EXPECT_TRUE(argParser.IsOptionRegistered("MyOption"));
}

TEST(TestArgumentParser, RegisterOption_Whitespace)
{
	// Criar um objeto do Argument Parser
	ArgumentParser argParser;

	// Registrar a Option
	// Chamar a função sendo testada
	argParser.RegisterOption("My Option");

	// Verifica o estado depois da operação
	EXPECT_TRUE(argParser.IsOptionRegistered("My Option"));
}


// TESTANDO O MÉTODO PARSE
TEST(TestArgumentParser, Parse)
{
	// Criar um objeto do Argument Parser
	ArgumentParser argParser;

	std::array<char*, 5> args =
	{
		"TestArgumentParser",
		"--flag",
		"--string=AaBbCcDd",
		"--number=42",
		"--float=4.2"
	};

	argParser.RegisterFlag("flag");
	argParser.RegisterOption("string");
	argParser.RegisterOption("number");
	argParser.RegisterOption("float");

	argParser.Parse(static_cast<int>(args.size()), args.data());

	EXPECT_FALSE(argParser.GetFlag("unregisteredFlag"));
	EXPECT_TRUE(argParser.GetFlag("flag"));
	EXPECT_EQ(argParser.GetOptionAs<const std::string&>("string"), "aabbccdd");
	EXPECT_EQ(argParser.GetOptionAs<int>("number"), 42);
	EXPECT_EQ(argParser.GetOptionAs<float>("float"), 4.2f);
}

TEST(TestArgumentParser, Parse_InvalidArguments)
{
	// Criar um objeto do Argument Parser
	ArgumentParser argParser;

	argParser.Parse(0, nullptr);
	argParser.Parse(42, nullptr);
	argParser.Parse(-1, nullptr);
}