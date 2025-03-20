#include "hash.hpp"

namespace util 
{
namespace hash 
{
    std::string encode(const std::string &src)
    {
        sha256 sha;
        sha.update(src);
        auto digest = sha.digest();
        return sha256::toString(digest);
    }
}
}