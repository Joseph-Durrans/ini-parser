// iniParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "AppConfig.h"

int main()
{
    std::cout << "Hello World!\n";

    AppConfig cfg("Config.ini");

    cfg.addToConfig("propertyExample", "SettingExample");

    //cfg.addToConfig("property", "setting");
    //cfg.readConfigData("property");
}

