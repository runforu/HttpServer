
#include "json_handler.h"
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include "json_wrapper.h"

namespace http {
namespace server {
int json_handler::get_priority() const {
    return 100;
}

bool json_handler::can_handle(const request & req)
{
    return true;
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
    if (std::find_if(req.headers.begin(), req.headers.end(), [&](const header& h) { return h == header::json_content_type; }) !=
        req.headers.end()) {
        // std::cout << "body: " << req.body << "\n";
        ptree pt = json_wrapper::parse_json(req.body);
        rep.status = reply::ok;
        ptree response;
        if (pt.get<std::string>("request", "").compare("OpenOrder") == 0) {
            response = OpenOrder(pt);
        } else if (pt.get<std::string>("request", "").compare("AddOrder") == 0) {
            response = AddOrder(pt);
        } else if (pt.get<std::string>("request", "").compare("UpdateOrder") == 0) {
            response = UpdateOrder(pt);
        } else if (pt.get<std::string>("request", "").compare("CloseOrder") == 0) {
            response = CloseOrder(pt);
        } else if (pt.get<std::string>("request", "").compare("Deposit") == 0) {
            response = Deposit(pt);
        } else if (pt.get<std::string>("request", "").compare("GetUserRecord") == 0) {
            response = GetUserRecord(pt);
        } else if (pt.get<std::string>("request", "").compare("UpdateUserRecord") == 0) {
            response = UpdateUserRecord(pt);
        } else if (pt.get<std::string>("request", "").compare("GetMargin") == 0) {
            response = GetMargin(pt);
        } else {
            response.put("json_error", "Not supported json request");
        }

        rep.headers.push_back(header::json_content_type);
        std::string content = ToJsonStr(response);
        rep.headers.push_back(header("Content-Length", std::to_string(content.length())));
        rep.content.append(content);
        return true;
    }

    return false;
}

ptree json_handler::GetMargin(ptree pt) {
    return pt;
}

ptree json_handler::OpenOrder(ptree pt) {
    return pt;
}

ptree json_handler::AddOrder(ptree pt) {
    return pt;
}

ptree json_handler::UpdateOrder(ptree pt) {
    return pt;
}

ptree json_handler::CloseOrder(ptree pt) {
    return pt;
}

ptree json_handler::Deposit(ptree pt) {
    return pt;
}

ptree json_handler::GetUserRecord(ptree pt) {
    return pt;
}

ptree json_handler::UpdateUserRecord(ptree pt) {
    return pt;
}
}  // namespace server
}  // namespace http
