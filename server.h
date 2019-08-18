#include <memory>

class Server
{
public:
    using ServerPtr = std::unique_ptr<Server>;
    virtual ~Server() = default;

    virtual bool Run() = 0;
    virtual std::string GetErrorText() const = 0;
};

Server::ServerPtr CreateServer(int port);
