#include <iostream>
#include <filesystem>
#include <fstream>
#include <stdio.h>
#include <sstream>

#include "Config.h"

Config::Config(std::string configFileName, std::string tempConfigFileName)
{
	configFile = configFileName;
	tempConfigFile = tempConfigFileName;
}

void Config::addToConfig(std::string property, std::string setting, std::string category)
{
	if (std::filesystem::exists(configFile))
	{
		std::ifstream reader(configFile);
		std::ofstream writer(tempConfigFile);

		bool foundCat = false;
		bool foundToReplacement = false;
		bool endOfCategory = false;
		bool startOfFile = true;

		std::stringstream ss;
		ss << "[" << category << "]";
		std::string amendedCategory = ss.str();

		std::string line;

		while (std::getline(reader, line) >> std::ws)
		{
			if (line.find(amendedCategory) != std::string::npos)
			{
				std::cout << "dound cat" << std::endl;
				writer << line << std::endl;
				foundCat = true;
				continue;
			}

			if (line.find(property) != std::string::npos && foundCat)
			{
				foundToReplacement = true;
				std::size_t findValue = line.find('=') + 1;
				line.replace(findValue, line.length() - findValue, setting);
				std::cout << "Replaced" << std::endl;
			}

			if (foundCat && line.find("[") != std::string::npos && !startOfFile)
			{
				writer << property << "=" << setting << std::endl;
				endOfCategory = true;
				std::cout << "added to end" << std::endl;
			}

			startOfFile = false;
			writer << line << std::endl;
		}

		if (!foundCat)
		{
			writer << amendedCategory << std::endl;
			writer << property << "=" << setting << std::endl;
			std::cout << "created to end" << std::endl;
		}

		reader.close();
		writer.close();

		remove(configFile.c_str());
		if (rename(tempConfigFile.c_str(), configFile.c_str()))
		{
			std::cout << "File Re-Written" << std::endl;
		}
	}
}

void Config::addCategory(std::string category)
{
	if (std::filesystem::exists(configFile))
	{
		std::ifstream reader(configFile);
		std::ofstream writer(tempConfigFile);

		bool found = false;

		std::stringstream ss;
		ss << "[" << category << "]";
		std::string amendedCategory = ss.str();

		std::string line;

		while (std::getline(reader, line) >> std::ws)
		{
			if (line.find(amendedCategory) != std::string::npos)
			{
				found = true;
			}
			writer << line << std::endl;
		}

		if (!found)
		{
			writer << amendedCategory << std::endl;
		}

		reader.close();
		writer.close();

		remove(configFile.c_str());
		if (rename(tempConfigFile.c_str(), configFile.c_str()))
		{
			std::cout << "File Re-Written" << std::endl;
		}
	}
}

std::map<std::string, std::string> Config::getCategoryData(std::string category)
{
	std::map<std::string, std::string> propertiesAndSettings;

	std::ifstream reader(configFile);

	bool inCat = false;

	std::stringstream ss;
	ss << "[" << category << "]";
	std::string amendedCategory = ss.str();

	std::string line;

	while (std::getline(reader, line) >> std::ws)
	{

		if (line.find(amendedCategory) != std::string::npos)
		{
			inCat = true;
			continue;
		}
		else if (line.find("[") != std::string::npos)
		{
			inCat = false;
			break;
		}

		if (inCat)
		{
			std::size_t findValue = line.find('=') + 1;
			std::size_t findKey = 0;
			std::string foundProperty = line.substr(findKey, line.find('=') - 1);
			std::string foundSetting = line.substr(findValue, line.length() - findValue);
			propertiesAndSettings.insert(std::pair<std::string, std::string>(foundProperty, foundSetting));
		}

	}

	reader.close();

	return propertiesAndSettings;
}
	

std::string Config::readConfigData(std::string property, std::string category)
{
	std::ifstream reader(configFile);

	std::stringstream ss;
	ss << "[" << category << "]";
	std::string amendedCategory = ss.str();

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

	//add category filtered search

	reader.close();

	return "Property Not Found";
}



