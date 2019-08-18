#pragma once

#include "server.h"

class ServerImpl: public Server
{
public:
    ServerImpl(int port);
    ~ServerImpl();

    bool Run() override;
    std::string GetErrorText() const override;

private:
    int Port = 54000;
    int ListenSocket = 0;
    std::string TextError;
};
