#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

#include "AppConfig.h"

AppConfig::AppConfig(const char* configFilePath)
{
	configFile = configFilePath;
	parseConfigData();
}

void AppConfig::addToConfig(const char* property, const char* setting)
{
	std::map<std::string, std::string>::iterator i;

	i = configData.find(property);
	if (i != configData.end())
	{
		std::string strSetting(setting);
		i->second = strSetting;
	}
	else
	{
		configData.insert(std::pair<std::string, std::string>(property, setting));
	}

	writeToConfig();
}

void AppConfig::writeToConfig()
{
	std::ofstream writer;

	std::map<std::string, std::string>::iterator it;

	writer.open(configFile);
	for (it = configData.begin(); it != configData.end(); it++)
	{
		writer << it->first << "=" << it->second << std::endl;
	}
	writer.close();

	parseConfigData();
}

void AppConfig::parseConfigData()
{
	if (std::filesystem::exists(configFile))
	{
		std::ifstream reader;
		std::string key, val;

		reader.open(configFile);
		while (std::getline(std::getline(reader, key, '=') >> std::ws, val))
		{
			configData.insert(std::pair<std::string, std::string>(key, val));
		}
		reader.close();
	}
}

const char* AppConfig::readConfigData(const char* property)
{
	std::map<std::string, std::string>::const_iterator i;

	i = configData.find(property);
	if (i != configData.end())
	{
		std::cout << "Key-value pair present : " << i->first << "=" << i->second << std::endl;

		return i->second.c_str();
	}
	else
	{
		std::cout << "Key-value pair not present in map" << std::endl;
	}

	return "error";
}
