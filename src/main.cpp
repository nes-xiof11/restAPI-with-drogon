#include "configurations/boot.hpp"
#include <glog/logging.h>

int main(int argc, char** argv)
{
    google::InitGoogleLogging(argv[0]);
    google::SetStderrLogging(google::LogSeverity::GLOG_INFO);
    configuration::boot();
    return 0;
}