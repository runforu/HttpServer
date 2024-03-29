#ifndef _HTTP_FILE_HANDLER_H_
#define _HTTP_FILE_HANDLER_H_

#include "http/reply.h"
#include "http/request.h"
#include "http/request_handler.h"

namespace http {
namespace server {
class file_handler : public request_handler {
public:
    virtual int get_priority() const;
    virtual bool can_handle(const request& req);
    virtual bool handle(const request& req, reply& rep);
    virtual ~file_handler() {}
    file_handler() {}

private:
    /// Perform URL-decoding on a string. Returns false if the encoding was
    /// invalid.
    static bool url_decode(const std::string& in, std::string& out);
};
}  // namespace server
}  // namespace http
#endif  // !_HTTP_FILE_HANDLER_H_
