#include "config.h"

#include <fstream>

#include "yaml-cpp/yaml.h"

Config::Config() {
    if (!std::ifstream("config.yaml")) {
        std::ofstream config_file("config.yaml");
        config_file << "";
    }

    m_config = YAML::LoadFile("config.yaml");
    readConfig();
}

Config::~Config() { writeConfig(); }

void Config::readConfig() {
    if (m_config["TableWidth"]) {
        m_table_width = m_config["TableWidth"].as<int>();
    } else {
        m_table_width = 20;
    }

    if (!(3 <= m_table_width && m_table_width <= 20)) {
        m_table_width = 20;
    }

    if (m_config["TableHeight"]) {
        m_table_height = m_config["TableHeight"].as<int>();
    } else {
        m_table_height = 10;
    }

    if (!(3 <= m_table_height && m_table_height <= 10)) {
        m_table_height = 10;
    }

    if (m_config["NumberOfBombs"]) {
        m_number_of_bomb = m_config["NumberOfBombs"].as<int>();
    } else {
        m_number_of_bomb = 20;
    }

    if (!(1 <= m_number_of_bomb &&
          m_number_of_bomb <= m_table_width * m_table_height)) {
        m_number_of_bomb = m_table_width;
    }

    writeConfig();
}

void Config::writeConfig() {
    m_config["TableWidth"] = m_table_width;
    m_config["TableHeight"] = m_table_height;
    m_config["NumberOfBombs"] = m_number_of_bomb;

    std::ofstream fout("config.yaml");
    fout << m_config;
}

Config& Config::getConfigInstance() {
    static Config config;
    return config;
}

int Config::getTableWidth() const { return m_table_width; }
int Config::getTableHeight() const { return m_table_height; }
int Config::getNumberOfBombs() const { return m_number_of_bomb; }
