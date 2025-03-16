#include "configuration.hpp"
#include "json/reader.h"
#include "json/value.h"
#include <fstream>
#include <glog/logging.h>

extern Json::Value config;

namespace configuration 
{
    void load_config(Json::Value &config)
    {
        LOG(INFO) << __FUNCTION__;
        const std::string config_filename = "configurations.json";
        std::ifstream stream(config_filename);
        if (not stream.is_open())
        {
            LOG(WARNING) << "Failed to open configuration file: " << config_filename;
        }
        Json::Value config_json;
        Json::Reader reader;
        reader.parse(stream, config_json);
        config = config_json["config"];   
    }

    std::string get_db_filename()
    {
        return config["database"]["path"].asString();
    }
}