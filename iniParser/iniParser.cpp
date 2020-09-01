// iniParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Config.h"

int main()
{
    Config cfg("Config.ini", "tempConfig.ini");
    
    std::string a = cfg.readConfigData("asdwww");

       std::cout << a << std::endl;
}

