// iniParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Config.h"

int main()
{
    Config cfg("Config.ini", "tempConfig.ini");
    
    cfg.addToConfig("wwwww", "AAAA", "popop");


    //cfg.addCategory("firstcat");

    //std::map<std::string, std::string> propertiesAndSettings = cfg.getCategoryData("firstcat");

    //std::map<std::string, std::string>::iterator it;
    //for (it = propertiesAndSettings.begin(); it != propertiesAndSettings.end(); it++)
    //{
    //    std::cout << it->first << "=" << it->second << std::endl;
    //}

}

