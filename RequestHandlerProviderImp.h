#ifndef _REQUESTHANDLERPROVIDERIMP_H_
#define _REQUESTHANDLERPROVIDERIMP_H_

#include <vector>
#include "http/request_handler_provider.h"
#include "http/request_handler.h"

class RequestHandlerProviderImp : public http::server::request_handler_provider {
public:
    RequestHandlerProviderImp();
    ~RequestHandlerProviderImp();
    std::vector<http::server::request_handler*> get_handlers();
    http::server::request_handler* get_default_handlers() override;
private:
    std::vector<http::server::request_handler*> m_request_handlers;


};

#endif  // !_REQUESTHANDLERPROVIDERIMP_H_
