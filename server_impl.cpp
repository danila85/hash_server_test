#include "server_impl.h"
#include "hasher_impl.h"

#include <arpa/inet.h>
#include <sys/socket.h>

#include <boost/thread.hpp>
#include <functional>


ServerImpl::ServerImpl(int port)
{
    Port = port;
}

ServerImpl::~ServerImpl()
{
    close(ListenSocket);
}

std::string ServerImpl::GetErrorText() const
{
    return TextError;
}

void start_connection(int socket, Hasher* hasherRawPtr)
{
    std::unique_ptr<Hasher> hasher(hasherRawPtr);
    char buf[1000];
    while (true)
    {
        int real_b = read(socket, buf, sizeof(buf)-1);
        if (real_b <= 0)
            break;
        buf[real_b]='\0';
        char* endL = std::find(buf, buf + real_b, '\n');
        if (endL != buf + real_b)
        {
            *endL='\0';
            hasher->AddData(buf);
            auto hash = hasher->GetHash();
            hasher->Clear();
            write(socket, hash.c_str(), hash.length());
        }
    }
}


bool ServerImpl::Run()
{
    if ((ListenSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        TextError = "Can't create socket";
        return false;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(Port);
    addr.sin_addr.s_addr = INADDR_ANY;
    std::vector< std::shared_ptr<boost::thread> > threads;
    if (bind(ListenSocket, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        TextError = "Can't bind socket on port " + std::to_string(Port);
        return false;
    }

    if (listen(ListenSocket, 1) < 0)
    {
        TextError = "Can't listen socket";
        return false;
    }

    while (true)
    {
        int clientSocket = accept(ListenSocket, NULL, NULL);
        if (clientSocket < 0)
        {
            TextError = "Can't accept connection";
            for (auto it: threads)
            {
                it->join();
            }
            return -1;
        }
        threads.push_back(std::make_shared<boost::thread>(start_connection, clientSocket,
                                                          new StringHasher));
    }
    return true;
}
