#include "config.h"

#include <fstream>

#include "yaml-cpp/yaml.h"

Config::Config() {
    if (!std::ifstream("config.yaml")) {
        std::ofstream config_file("config.yaml");
        config_file << "";
    }

    config = YAML::LoadFile("config.yaml");
    readConfig();
}

Config::~Config() { writeConfig(); }

void Config::readConfig() {
    if (config["TableWidth"]) {
        table_width = config["TableWidth"].as<int>();
    } else {
        table_width = 20;
    }

    if (!(3 <= table_width && table_width <= 20)) {
        table_width = 20;
    }

    if (config["TableHeight"]) {
        table_height = config["TableHeight"].as<int>();
    } else {
        table_height = 10;
    }

    if (!(3 <= table_height && table_height <= 10)) {
        table_height = 10;
    }

    if (config["NumberOfBombs"]) {
        number_of_bomb = config["NumberOfBombs"].as<int>();
    } else {
        number_of_bomb = 20;
    }

    if (!(1 <= number_of_bomb &&
          number_of_bomb <= table_width * table_height)) {
        number_of_bomb = table_width;
    }

    writeConfig();
}

void Config::writeConfig() {
    config["TableWidth"] = table_width;
    config["TableHeight"] = table_height;
    config["NumberOfBombs"] = number_of_bomb;

    std::ofstream fout("config.yaml");
    fout << config;
}

Config& Config::getConfigInstance() {
    static Config config;
    return config;
}

// int Config::getTableWidth() const { return table_width; }
// int Config::getTableHeight() const { return table_height; }
// int Config::getNumberOfBombs() const { return number_of_bomb; }
