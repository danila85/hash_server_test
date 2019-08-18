#include "server_impl.h"
#include "hasher_impl.h"

Server::ServerPtr CreateServer(int port)
{
    return Server::ServerPtr(new ServerImpl(port));
}
