#ifndef CONFIG_H
#define CONFIG_H

#include "settings_screen.h"
#include "yaml-cpp/yaml.h"

struct Config {
public:
    static Config& getConfigInstance();

    int getNumberOfBombs() const;
    int getTableWidth() const;
    int getTableHeight() const;

    friend struct SettingsScreen;

private:
    Config();
    ~Config();

    Config(const Config&) = delete;
    Config(Config&&) = delete;
    Config& operator=(const Config&) = delete;
    Config& operator=(Config&&) = delete;

    int m_number_of_bomb;
    int m_table_width;
    int m_table_height;
    YAML::Node m_config;

    void readConfig();
    void writeConfig();
};

#endif  // CONFIG_H
