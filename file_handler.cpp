#include "file_handler.h"
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "http/mime_types.h"
#include "http/reply.h"
#include "http/request.h"
#include "http/server_property.h"
#include "Environment.h"

namespace http {
namespace server {
int file_handler::get_priority() const {
    return 0;
}

bool file_handler::can_handle(const request & req)
{
    return false;
}

bool file_handler::handle(const request& req, reply& rep) {
    // Decode url to path.
    std::string request_path;
    if (!url_decode(req.uri, request_path)) {
        rep = reply::stock_reply(reply::bad_request);
        return false;
    }
    std::cout << "request " << request_path << std::endl;

    // Request path must be absolute and not contain "..".
    if (request_path.empty() || request_path[0] != '/' || request_path.find("..") != std::string::npos) {
        rep = reply::stock_reply(reply::bad_request);
        return false;
    }

    // If path ends in slash (i.e. is a directory) then add "index.html".
    if (request_path[request_path.size() - 1] == '/') {
        request_path += "index.html";
    }

    // Determine the file extension.
    std::size_t last_slash_pos = request_path.find_last_of("/");
    std::size_t last_dot_pos = request_path.find_last_of(".");
    std::string extension;
    if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos) {
        extension = request_path.substr(last_dot_pos + 1);
    }

    // Open the file to send back.
    std::string full_path = Environment::s_doc_root + request_path;;
    std::cout << "request " << full_path << std::endl;
    std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
    if (!is) {
        rep = reply::stock_reply(reply::not_found);
        return false;
    }

    // Fill out the reply to be sent to the client.
    rep.status = reply::ok;
    char buf[512];
    while (is.read(buf, sizeof(buf)).gcount() > 0) {
        rep.content.append(buf, is.gcount());
    }
    rep.headers.resize(2);
    rep.headers[0].name = "Content-Length";
    rep.headers[0].value = boost::lexical_cast<std::string>(rep.content.size());
    rep.headers[1].name = "Content-Type";
    rep.headers[1].value = mime_types::extension_to_type(extension);
    return true;
}

bool file_handler::url_decode(const std::string& in, std::string& out) {
    out.clear();
    out.reserve(in.size());
    for (std::size_t i = 0; i < in.size(); ++i) {
        if (in[i] == '%') {
            if (i + 3 <= in.size()) {
                int value = 0;
                std::istringstream is(in.substr(i + 1, 2));
                if (is >> std::hex >> value) {
                    out += static_cast<char>(value);
                    i += 2;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else if (in[i] == '+') {
            out += ' ';
        } else {
            out += in[i];
        }
    }
    return true;
}
}  // namespace server
}  // namespace http
