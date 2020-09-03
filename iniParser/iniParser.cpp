// iniParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Config.h"

int main()
{
    Config cfg("Config.ini", "tempConfig.ini");
    

    while (true)
    {
        int option = 0;

        std::cout << "0. Get All Data" << std::endl;
        std::cout << "1. Get Category Data" << std::endl;
        std::cout << "2. Read Property Data" << std::endl;
        std::cout << "3. Add to ini File" << std::endl;

        std::cin >> option;

        switch (option)
        {
        case 0: {
            std::map<std::string, std::map<std::string, std::string>> data = cfg.getAllData();

            std::map<std::string, std::map<std::string, std::string>>::iterator it;

            for (it = data.begin(); it != data.end(); it++)
            {
                std::map<std::string, std::string>::iterator innerIt;

                std::cout << it->first << ":" << std::endl;
                for (innerIt = it->second.begin(); innerIt != it->second.end(); innerIt++)
                {
                    std::cout << "  " << innerIt->first << "=" << innerIt->second << std::endl;
                }
            }
            std::cout << std::endl;
            break;
        }

        case 1: {
            std::string cat;

            std::cout << "Enter Category Name" << std::endl;
            std::cin >> cat;

            std::map<std::string, std::string> data = cfg.getCategoryData(cat);

            std::map<std::string, std::string>::iterator it;

            for (it = data.begin(); it != data.end(); it++)
            {
                std::cout << it->first << "=" << it->second << std::endl;
            }
            std::cout << std::endl;
            break;
        }

        case 2: {
            std::string prop;
            std::string cat;

            std::cout << "Enter Property Name" << std::endl;
            std::cin >> prop;
            std::cout << "Enter Category Name" << std::endl;
            std::cin >> cat;

            std::cout << cfg.readPropertyData(prop, cat) << std::endl;
            break;
        }

        case 3: {
            std::string prop;
            std::string set;
            std::string cat;

            std::cout << "Enter Property Name" << std::endl;
            std::cin >> prop;
            std::cout << "Enter Setting Name" << std::endl;
            std::cin >> set;
            std::cout << "Enter Category" << std::endl;
            std::cin >> cat;

            cfg.addToConfig(prop, set, cat);
            std::cout << std::endl;
            break;
        }

        default:
            break;
        }
    }
}

