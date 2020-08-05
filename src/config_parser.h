#include <cstring>
#include <vector>
#include "SFML/Graphics.hpp"
#include "yaml/Yaml.hpp"

struct BodyData
{
    int radius;
    int mass;
    sf::Vector2f position;
    sf::Vector2f speed;
};

class ConfigParser
{
private:
    std::string filename;
    bool isFileOpened;
public:
    ConfigParser();
    ConfigParser(std::string filename);
    std::vector<BodyData> Parse();
};