#pragma once

#include <map>
#include <string>

class AppConfig
{
private:
	std::map<std::string, std::string> configData;

	const char* configFile;

	void writeToConfig();
	void parseConfigData();
public:
	AppConfig(const char* configFilePath);

	void addToConfig(const char* property, const char* setting);
	const char* readConfigData(const char* property);
};
