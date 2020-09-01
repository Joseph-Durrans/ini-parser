#pragma once

#include <map>
#include <string>

class AppConfig
{
private:
	std::map<std::string, std::string> configData;

	std::string configFile;

	void writeToConfig();
	void parseConfigData();
public:
	AppConfig(std::string configFilePath);

	void addToConfig(std::string property, std::string setting);
	std::string readConfigData(std::string property);
};
