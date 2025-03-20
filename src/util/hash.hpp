#pragma once

#include "../../lib/SHA256.hpp"
#include <string>

namespace util 
{
namespace hash 
{
    std::string encode(const std::string& src);
}
}