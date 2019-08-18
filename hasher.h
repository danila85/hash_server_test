#pragma once

#include <string>

class Hasher
{
public:
    virtual ~Hasher() = default;

    virtual void AddData(const char* data) = 0;
    virtual std::string GetHash() const = 0;
    virtual void Clear() = 0;

};
