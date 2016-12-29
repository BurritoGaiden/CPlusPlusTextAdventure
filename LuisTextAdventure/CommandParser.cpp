#include "CommandParser.h"
#include <vector>

TextAdventureCommand ParseAdventureCommand()
{
	TextAdventureCommand retCommand = {};
	retCommand.CommandType = CommandType_NONE;

	const unsigned int INPUT_CHAR_LIMIT = 256;
	char inputStr[INPUT_CHAR_LIMIT];

	char* pRet = fgets(inputStr, INPUT_CHAR_LIMIT, stdin);

	for (int i = 0; i < INPUT_CHAR_LIMIT; ++i)
	{
		inputStr[i] = tolower(inputStr[i]);
	}

	std::vector<std::string> tokens;
	char* next_token = nullptr;
	char *token = strtok_s(inputStr, " \t\n", &next_token);
	while (token)
	{
		tokens.push_back(token);
		token = strtok_s(nullptr, " \t\n", &next_token);
	}

	bool bParsed = false;
	if (tokens.size() >= 1)
	{
		std::string verbString = tokens[0];

		if (verbString == "quit")
		{
			bParsed = true;
			retCommand.CommandType = CommandType_QUIT;
		}
		else if (verbString == "look")
		{
			bParsed = true;
			retCommand.CommandType = CommandType_LOOK;
		}
		else if (verbString == "go")
		{
			retCommand.CommandType = CommandType_GO;
			if (tokens.size() >= 2)
			{
				retCommand.Parameter = tokens[1];
				bParsed = true;
			}
		}
		else if (verbString == "get")
		{
			retCommand.CommandType = CommandType_GET;
			if (tokens.size() >= 2)
			{
				retCommand.Parameter = tokens[1];
				bParsed = true;
			}
		}
		else if (verbString == "sleep")
		{
			retCommand.CommandType = CommandType_SLEEP;
			bParsed = true;
		}
		else if (verbString == "help")
		{
			retCommand.CommandType = CommandType_HELP;
		}
	}

	return retCommand;
}