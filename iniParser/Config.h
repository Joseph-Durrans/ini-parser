#pragma once

#include <string>
#include <map>

class Config
{
private:
	std::string configFile;
	std::string tempConfigFile;

	std::string readCat(std::ifstream& reader, std::string& line, std::string& property);
public:
	Config(std::string& configFileName, std::string& tempConfigFileName);

	static bool propFinder(std::string& line, std::string& property);
	static bool catFinder(std::string& line, std::string& category);

	void addToConfig(std::string& property, std::string& setting, std::string& category);
	std::string readPropertyData(std::string& property, std::string& category);
	std::map<std::string, std::string> getCategoryData(std::string& category);
	std::map<std::string, std::map<std::string, std::string>> getAllData();
};
