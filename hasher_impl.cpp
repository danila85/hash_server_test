#include "hasher_impl.h"
#include <iostream>
#include <boost/functional/hash.hpp>
#include <string>

void StringHasher::AddData(const char* data)
{
    Data.emplace_back(data);
}

std::string StringHasher::GetHash() const
{
    std::stringstream stream;
    stream << std::hex << boost::hash_range(Data.begin(), Data.end()) << std::endl;
    return std::string(stream.str());
}
void StringHasher::Clear()
{
    Data.clear();
}
