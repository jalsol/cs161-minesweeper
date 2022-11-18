#ifndef CONFIG_H
#define CONFIG_H

#include "settings_screen.h"
#include "yaml-cpp/yaml.h"

struct Config {
public:
    static Config& getConfigInstance();

    int number_of_bomb;
    int table_width;
    int table_height;
    YAML::Node config;

    void readConfig();
    void writeConfig();
private:
    Config();
    ~Config();

    Config(const Config&) = delete;
    Config(Config&&) = delete;
    Config& operator=(const Config&) = delete;
    Config& operator=(Config&&) = delete;
};

#endif  // CONFIG_H
