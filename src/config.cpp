#include "config.h"

Config::Config() { readConfig(); }

Config::~Config() { writeConfig(); }

void Config::readConfig() {
    // TODO:
    // if no config file to read then write
    // else read
}

void Config::writeConfig() {}

Config& Config::getConfigInstance() {
    static Config config;
    return config;
}
