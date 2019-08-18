#pragma once

#include "hasher.h"

#include <vector>

class StringHasher: public Hasher
{
public:
    void AddData(const char* data) override;
    std::string GetHash() const override;
    void Clear() override;
private:
    std::vector<std::string> Data;
};
