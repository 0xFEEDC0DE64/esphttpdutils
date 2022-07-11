#include "esphttpstatuscodes.h"

// system includes
#include <utility>

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <futurecpp.h>

namespace esphttpdutils {
namespace {
constexpr const char * const TAG = "ESPHTTPDUTILS";
} // namespace

const char *toString(ResponseStatus status)
{
    switch (status)
    {
    case ResponseStatus::Continue:                      return "100 Continue";
    case ResponseStatus::SwitchingProtocols:            return "101 Switching Protocols";
    case ResponseStatus::Processing:                    return "102 Processing";
    case ResponseStatus::EarlyHints:                    return "103 Early Hints";
    case ResponseStatus::Ok:                            return "200 OK";
    case ResponseStatus::Created:                       return "201 Created";
    case ResponseStatus::Accepted:                      return "202 Accepted";
    case ResponseStatus::NonAuthoritativeInformation:   return "203 Non-Authoritative Information";
    case ResponseStatus::NoContent:                     return "204 No Content";
    case ResponseStatus::ResetContent:                  return "205 Reset Content";
    case ResponseStatus::PartialContent:                return "206 Partial Content";
    case ResponseStatus::MultiStatus:                   return "207 Multi-Status";
    case ResponseStatus::AlreadyReported:               return "208 Already Reported";
    case ResponseStatus::IMUsed:                        return "226 IM Used";
    case ResponseStatus::MultipleChoices:               return "300 Multiple Choices";
    case ResponseStatus::MovedPermanently:              return "301 Moved Permanently";
    case ResponseStatus::Found:                         return "302 Found";
    case ResponseStatus::SeeOther:                      return "303 See Other";
    case ResponseStatus::NotModified:                   return "304 Not Modified";
    case ResponseStatus::UseProxy:                      return "305 Use Proxy";
    case ResponseStatus::SwitchProxy:                   return "306 Switch Proxy";
    case ResponseStatus::TemporaryRedirect:             return "307 Temporary Redirect";
    case ResponseStatus::PermanentRedirect:             return "308 Permanent Redirect";
    case ResponseStatus::BadRequest:                    return "400 Bad Request";
    case ResponseStatus::Unauthorized:                  return "401 Unauthorized";
    case ResponseStatus::PaymentRequired:               return "402 Payment Required";
    case ResponseStatus::Forbidden:                     return "403 Forbidden";
    case ResponseStatus::NotFound:                      return "404 Not Found";
    case ResponseStatus::MethodNotAllowed:              return "405 Method Not Allowed";
    case ResponseStatus::NotAcceptable:                 return "406 Not Acceptable";
    case ResponseStatus::ProxyAuthenticationRequired:   return "407 Proxy Authentication Required";
    case ResponseStatus::RequestTimeout:                return "408 Request Timeout";
    case ResponseStatus::Conflict:                      return "409 Conflict";
    case ResponseStatus::Gone:                          return "410 Gone";
    case ResponseStatus::LengthRequired:                return "411 Length Required";
    case ResponseStatus::PreconditionFailed:            return "412 Precondition Failed";
    case ResponseStatus::PayloadTooLarge:               return "413 Payload Too Large";
    case ResponseStatus::URITooLong:                    return "414 URI Too Long";
    case ResponseStatus::UnsupportedMediaType:          return "415 Unsupported Media Type";
    case ResponseStatus::RangeNotSatisfiable:           return "416 Range Not Satisfiable";
    case ResponseStatus::ExpectationFailed:             return "417 Expectation Failed";
    case ResponseStatus::ImATeapot:                     return "418 I'm a teapot";
    case ResponseStatus::MisdirectedRequest:            return "421 Misdirected Request";
    case ResponseStatus::UnprocessableEntity:           return "422 Unprocessable Entity";
    case ResponseStatus::Locked:                        return "423 Locked";
    case ResponseStatus::FailedDependency:              return "424 Failed Dependency";
    case ResponseStatus::TooEarly:                      return "425 Too Early";
    case ResponseStatus::UpgradeRequired:               return "426 Upgrade Required";
    case ResponseStatus::PreconditionRequired:          return "428 Precondition Required";
    case ResponseStatus::TooManyRequests:               return "429 Too Many Requests";
    case ResponseStatus::RequestHeaderFieldsTooLarge:   return "431 Request Header Fields Too Large";
    case ResponseStatus::UnavailableForLegalReasons:    return "451 Unavailable For Legal Reasons";
    default:
        ESP_LOGW(TAG, "unknown httpd_err_code_t(%i)", std::to_underlying(status));
    [[fallthrough]];
    case ResponseStatus::InternalServerError:           return "500 Internal Server Error";
    case ResponseStatus::NotImplemented:                return "501 Not Implemented";
    case ResponseStatus::BadGateway:                    return "502 Bad Gateway";
    case ResponseStatus::ServiceUnavailable:            return "503 Service Unavailable";
    case ResponseStatus::GatewayTimeout:                return "504 Gateway Timeout";
    case ResponseStatus::HTTPVersionNotSupported:       return "505 HTTP Version Not Supported";
    case ResponseStatus::VariantAlsoNegotiates:         return "506 Variant Also Negotiates";
    case ResponseStatus::InsufficientStorage:           return "507 Insufficient Storage";
    case ResponseStatus::LoopDetected:                  return "508 Loop Detected";
    case ResponseStatus::NotExtended:                   return "510 Not Extended";
    case ResponseStatus::NetworkAuthenticationRequired: return "511 Network Authentication Required";
    }
}

} // namespace esphttpdutils
