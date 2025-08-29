#include "boot.hpp"
#include "configuration.hpp"
#include "json/value.h"
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <glog/logging.h>
#include <drogon/drogon.h>
#include "../migrations/migration.hpp"
#include "../misc/seeder.hpp"

Json::Value config;

namespace configuration 
{
    void setup_directories(const Json::Value &config)
    {
        LOG(INFO) << __FUNCTION__;
        for (const auto& dir: config) 
        {
            if (not std::filesystem::create_directories(dir.asString())) 
            {
                LOG(WARNING) << dir << " not created";
            }
        }
    }

    void setup_server(const Json::Value &config)
    {
        LOG(INFO) << __FUNCTION__;
        try {
            using namespace drogon;
            const auto addr = config["addr"].asString();
            const auto port = config["port"].asInt();
            LOG(INFO) << "access api at http://" << addr << ":" << port;
            app()
                .addListener(addr, port)
                .enableSession(300) // 5 minutes
                .run();
        } catch (const std::exception& e) {
            LOG(FATAL) << e.what();
        }
    }

    void boot() try
    {   
        load_config(config);

        setup_directories(config["directories"]);

        migration::migrate(config["migrations"]);
        misc::seeder(config["admin"]);

        LOG(INFO) << "starting api";

        setup_server(config["server"]);

        LOG(INFO) << "stoping api";
    } catch (const std::exception & e) {
        LOG(FATAL) << e.what();
    } 
}
