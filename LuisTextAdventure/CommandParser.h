#pragma once
#include <string>

enum TextAdventureCommandType
{
	CommandType_NONE,
	CommandType_QUIT,
	CommandType_LOOK,
	CommandType_GO,
	CommandType_GET,
	CommandType_SLEEP,
	CommandType_HELP
};

struct TextAdventureCommand
{
	TextAdventureCommandType CommandType;
	std::string Parameter;
};

TextAdventureCommand ParseAdventureCommand();