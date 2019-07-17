#ifndef _AUTOTEST_H_
#define _AUTOTEST_H_

#include <process.h>
#include <windows.h>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "http/server.h"


namespace http {
    namespace server {
        class server;
    }
}  // namespace http

class Processor {
public:
    static Processor& Instance();

    void Initialize();

    void Shutdown();

private:
    Processor() : m_http_server(NULL) {}
    ~Processor() {};
    Processor(Processor const&) {}
    void operator=(Processor const&) {}

    void StartServer(const char* port, const char* num_threads);

private:
    http::server::server* m_http_server;
    boost::thread m_thread;
    // Synchronizer m_synchronizer;
};

#endif  // !_AUTOTEST_H_