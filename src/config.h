#ifndef CONFIG_H
#define CONFIG_H

struct Config {
public:
    static Config& getConfigInstance();
    int number_of_sus;
    int table_width;
    int table_height;

private:
    Config();
    ~Config();

    Config(const Config&) = delete;
    Config(Config&&) = delete;
    Config& operator=(const Config&) = delete;
    Config& operator=(Config&&) = delete;

    void readConfig();
    void writeConfig();
};

#endif  // CONFIG_H
