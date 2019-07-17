#ifndef _HTTP_JSON_HANDLER_H_
#define _HTTP_JSON_HANDLER_H_

#include <boost/property_tree/ptree.hpp>
#include "http/reply.h"
#include "http/request.h"
#include "http/request_handler.h"

namespace http {
namespace server {

class json_handler : public request_handler {
public:
    virtual int get_priority() const;
    virtual bool can_handle(const request& req);
    virtual bool handle(const request& req, reply& rep);
    virtual ~json_handler() {}
    json_handler() {}

private:
    boost::property_tree::ptree GetMargin(boost::property_tree::ptree pt);
    boost::property_tree::ptree OpenOrder(boost::property_tree::ptree pt);
    boost::property_tree::ptree AddOrder(boost::property_tree::ptree pt);
    boost::property_tree::ptree UpdateOrder(boost::property_tree::ptree pt);
    boost::property_tree::ptree CloseOrder(boost::property_tree::ptree pt);
    boost::property_tree::ptree Deposit(boost::property_tree::ptree pt);
    boost::property_tree::ptree GetUserRecord(boost::property_tree::ptree pt);
    boost::property_tree::ptree UpdateUserRecord(boost::property_tree::ptree pt);
};
}  // namespace server
}  // namespace http
#endif  // !_HTTP_JSON_HANDLER_H_