#pragma once

#include <string>
#include <map>

class Config
{
private:
	std::string configFile;
	std::string tempConfigFile;
public:
	Config(std::string configFileName, std::string tempConfigFileName);

	void addToConfig(std::string property, std::string setting, std::string category);
	void addCategory(std::string property);
	std::string readConfigData(std::string category, std::string category);
	std::map<std::string, std::string> getCategoryData(std::string category);
};
