
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include "http/connection.h"
#include "json_handler.h"
#include "json_wrapper.h"

namespace http {
namespace server {
int json_handler::get_priority() const {
    return 100;
}

bool json_handler::can_handle(const request& req) {
    return std::find_if(req.headers.begin(), req.headers.end(), [&](const http::server::header& h) {
               return h.name == "content-type" && h.value == "application/json";
           }) != req.headers.end();
}

boost::property_tree::ptree ParseJson(std::string json_str) {
    boost::property_tree::ptree tree;
    std::stringstream ss(json_str);
    try {
        read_json(ss, tree);
    } catch (boost::property_tree::ptree_error& e) {
    }
    return tree;
}

std::string ToJsonStr(boost::property_tree::ptree& pt) {
    std::stringstream ss;
    write_json(ss, pt);
    return ss.str();
}

bool json_handler::handle(const request& req, reply& rep) {
    //std::cout << req.body << std::endl;
    ptree pt = json_wrapper::parse_json(req.body);
    rep.status = reply::ok;
    ptree response;
    if (pt.get<std::string>("request", "").compare("GetMargin") == 0) {
        response = GetMargin(pt);
    } else {
        response.put("json_error", "Not supported json request");
    }

    std::string content = ToJsonStr(response);
    rep.content.append(content);

    rep.headers.resize(4);
    rep.headers[0].name = "Content-Type";
    rep.headers[0].value = "application/json";
    rep.headers[3].name = "Content-Length";
    rep.headers[3].value = std::to_string(rep.content.length());
    return true;
}

ptree json_handler::GetMargin(ptree& pt) {
    pt.add("connection", connection::total_connection());
    return pt;
}

}  // namespace server
}  // namespace http
