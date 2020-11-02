#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>

#include "Config.h"

bool Config::propFinder(std::string& line, std::string& property)
{
	int characters = 0;
	std::string foundProperty;

	for (char& c : line)
	{
		if (c == '=')
		{
			break;
		}

		foundProperty += c;
		++characters;
	}

	if (characters == property.length())
	{
		if (foundProperty == property)
		{
			std::cout << "found" << std::endl;
			return true;
		}
	}
	
	std::cout << "not found" << std::endl;
	return false;
}

bool Config::catFinder(std::string& line, std::string& category)
{
	int characters = 0;
	std::string foundCategory;

	for (char& c : line){
	
		if (c == '[')
		{
			continue;
		}
		else if(c == ']')
		{
			break;
		}

		foundCategory += c;
		++characters;
	}

	if (characters == category.length())
	{
		if (foundCategory == category)
		{
			std::cout << "found" << std::endl;
			return true;
		}
	}
	std::cout << "not found" << std::endl;
	return false;
}


Config::Config(std::string& configFileName, std::string& tempConfigFileName)
{
	std::stringstream nameStream;
	nameStream << configFileName << ".ini";	
	std::string amendedConfigFileName = nameStream.str();

	std::stringstream tempNameStream;
	tempNameStream << tempConfigFileName << ".ini";
	std::string amendedTempConfigFileName = tempNameStream.str();

	configFile = amendedConfigFileName;
	tempConfigFile = amendedTempConfigFileName;
}

void Config::addToConfig(std::string& property, std::string& setting, std::string& category)
{
	std::ifstream reader(configFile);
	std::ofstream writer(tempConfigFile);

	bool foundCat = false;
	bool foundCatOnce = false;
	bool replaced = false;
	bool startOfFile = true;

	std::stringstream ss;
	ss << "[" << category << "]";
	std::string amendedCategory = ss.str();

	std::string line;

	while (std::getline(reader, line) >> std::ws)
	{
		if (line.find(amendedCategory) != std::string::npos)
		{
			writer << line << std::endl;
			foundCat = true;
			foundCatOnce = true;
			startOfFile = false;
			continue;
		}

		if (line.find(property) != std::string::npos && foundCat)
		{
			std::size_t findValue = line.find('=') + 1;
			line.replace(findValue, line.length() - findValue, setting);
			replaced = true;
			foundCat = false;
		}
		else if (line.find("[") != std::string::npos && foundCat && !replaced && !startOfFile || foundCat && !replaced && !startOfFile && reader.eof())
		{
			writer << property << "=" << setting << std::endl;
			foundCat = false;
		}

		startOfFile = false;
		writer << line << std::endl;
	}

	if (!foundCatOnce)
	{
		writer << amendedCategory << std::endl;
		writer << property << "=" << setting << std::endl;
	}

	reader.close();
	writer.close();

	remove(configFile.c_str());
	if (rename(tempConfigFile.c_str(), configFile.c_str()))
	{
		std::cout << "File Re-Written" << std::endl;
	}
}

std::map<std::string, std::string> Config::getCategoryData(std::string& category)
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
		else if (line.find("[") != std::string::npos && inCat)
		{
			inCat = false;
			break;
		}

		if (inCat)
		{
			std::size_t findValue = line.find('=') + 1;
			std::size_t findKey = 0;
			std::string foundProperty = line.substr(findKey, line.find('='));
			std::string foundSetting = line.substr(findValue, line.length() - findValue);
			propertiesAndSettings.insert(std::pair<std::string, std::string>(foundProperty, foundSetting));
		}
	}

	reader.close();

	return propertiesAndSettings;
}

std::map<std::string, std::map<std::string, std::string>> Config::getAllData()
{
	std::ifstream reader(configFile);

	std::map<std::string, std::map<std::string, std::string>> maps;

	std::string line;

	while (std::getline(reader, line) >> std::ws)
	{
		if (line.find("[") != std::string::npos)
		{
			std::string foundProperty = line.substr(1, line.length() - 2);
			std::map<std::string, std::string> map = getCategoryData(foundProperty);
			maps[foundProperty].insert(map.begin(), map.end());	
		}
	}

	reader.close();

	return maps;
}

std::string Config::readCat(std::ifstream& reader, std::string& line, std::string& property)
{
	while (std::getline(reader, line) >> std::ws)
	{
		if (line.find(property) != std::string::npos)
		{
			std::size_t findValue = line.find('=') + 1;
			std::string foundPropertySetting = line.substr(findValue, line.length() - findValue);
			return foundPropertySetting;
		}
		else if (line.find("[") != std::string::npos)
		{
			break;
		}
	}

	return "Property Not Found";
}

std::string Config::readPropertyData(std::string& property, std::string& category)
{
	std::ifstream reader(configFile);

	bool foundCat = false;

	std::stringstream ss;
	ss << "[" << category << "]";
	std::string amendedCategory = ss.str();

	std::string line;

	std::string response = "No Category Found";

	while (std::getline(reader, line) >> std::ws)
	{
		if (line.find(amendedCategory) != std::string::npos)
		{
			response = readCat(reader, line, property);
			break;
		}
	}

	reader.close();

	return response;
}

