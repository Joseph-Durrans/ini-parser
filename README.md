# iniParser

A simple ini file parser that can read, write and replace data in an ini file.

It also supports categories for data so you may for example get all the data in a certain category.

Methods:

```c++
Config::Config(std::string configFileName, std::string tempConfigFileName);
```
Input the name you want your config file to have and another name for a temporary file that is written to when declaring a config object.

This will automatically create the config file, if the file already exists it will find it.

```c++
void addToConfig(std::string property, std::string setting, std::string category);
```
Input the property and setting you want in you ini file. Also Input a category.

If the category already exists it will put your newly created property and setting in that category.

If the property already exists within the category it will replace the setting with you new value.

```c++
std::string readPropertyData(std::string property, std::string category);

```