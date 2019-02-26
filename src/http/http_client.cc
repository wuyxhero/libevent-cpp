#include <http_client.hh>
#include <cassert>

namespace eve
{

http_client::http_client(std::shared_ptr<event_base>base)
{
    this->base = base;
}

http_client::~http_client()
{
}

int http_client::make_connection(const std::string &address, unsigned int port)
{
    auto conn = std::make_shared<http_client_connection>(base, shared_from_this());
    conn->servaddr = address;
    conn->servport = port;

    if (conn->connect() == -1)
        return -1;
    connections[conn->id] = conn;
    return conn->id;
}

int http_client::make_request(int connid, std::shared_ptr<http_request> req)
{
    if (connections.count(connid) <= 0)
    {
        std::cerr << __func__ << ":no connections in client with id=" << connid << std::endl;
        return -1;
    }

    auto conn = connections.at(connid);

    req->kind = REQUEST;
    req->conn = conn.get();

    req->remote_host = conn->servaddr;
    req->remote_port = conn->servport;

    conn->requests.push(req);
    conn->dispatch();

    return 0;
}

} // namespace eve
