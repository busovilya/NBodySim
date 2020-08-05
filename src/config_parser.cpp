#include "config_parser.h"

ConfigParser::ConfigParser()
{
    isFileOpened = false;
}

ConfigParser::ConfigParser(std::string filename)
{
    isFileOpened = true;
    this->filename = filename;
}

std::vector<BodyData> ConfigParser::Parse()
{
    // TODO: bug when file is empty
    Yaml::Node root;
    Yaml::Parse(root, filename.c_str());
    
    std::vector<BodyData> result;
    
    if(root.Size() == 0)
    {
        return result;
    }


    for(auto it = root.Begin(); it != root.End(); it++)
    {
        Yaml::Node& node = (*it).second;
        result.push_back(BodyData{node["radius"].As<int>(),
                         node["mass"].As<int>(),
                         sf::Vector2f(node["position"]["x"].As<double>(), node["position"]["y"].As<double>()),
                         sf::Vector2f(node["speed"]["x"].As<double>(), node["speed"]["y"].As<double>())});
    }
    return result;
}