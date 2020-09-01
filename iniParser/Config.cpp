#include <iostream>
#include <filesystem>
#include <fstream>
#include <stdio.h>

#include "Config.h"

Config::Config(std::string configFileName, std::string tempConfigFileName)
{
	configFile = configFileName;
	tempConfigFile = tempConfigFileName;
}

void Config::addToConfig(std::string property, std::string setting)
{
	std::ifstream reader(configFile);
	std::ofstream writer(tempConfigFile);

	bool replaced = false;

	std::string line;

	while (std::getline(reader, line) >> std::ws)
	{
		if (line.find(property) != std::string::npos)
		{
			std::size_t findValue = line.find('=') + 1;
			line.replace(findValue, line.length() - findValue, setting);
			replaced = true;
		}
		std::cout << line << std::endl;
		writer << line << std::endl;
	}

	if (!replaced)
	{
		writer << property << "=" << setting << std::endl;
	}

	reader.close();
	writer.close();

	remove(configFile.c_str());
	rename(tempConfigFile.c_str(), configFile.c_str());
}

std::string Config::readConfigData(std::string property)
{
	std::ifstream reader(configFile);

	std::string line;

	while (std::getline(reader, line) >> std::ws)
	{
		if (line.find(property) != std::string::npos)
		{
			std::size_t findValue = line.find('=') + 1;
			std::string foundPropertySetting = line.substr(findValue, line.length() - findValue);
			return foundPropertySetting;
		}
	}

	reader.close();

	return "Property Not Found";
}