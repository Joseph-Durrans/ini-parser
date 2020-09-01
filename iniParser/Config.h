#pragma once

#include <string>

class Config
{
private:
	std::string configFile;
	std::string tempConfigFile;
public:
	Config(std::string configFileName, std::string tempConfigFileName);

	void addToConfig(std::string property, std::string setting);
	std::string readConfigData(std::string property);
};
