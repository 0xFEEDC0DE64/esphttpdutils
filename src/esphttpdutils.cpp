#include "esphttpdutils.h"

// esp-idf includes
#include <esp_log.h>
#include <http_parser.h>

// 3rdparty lib includes
#include <fmt/core.h>

// local includes
#include "futurecpp.h"
#include "espcppmacros.h"

namespace esphttpdutils {
namespace {
constexpr const char * const TAG = "ESPHTTPDUTILS";
}

void urldecode(char *dst, const char *src)
{
    while (*src)
    {
        char a, b;
        if ((*src == '%') && ((a = src[1]) && (b = src[2])) && (std::isxdigit(a) && std::isxdigit(b)))
        {
            if (a >= 'a')
                a -= 'a'-'A';
            if (a >= 'A')
                a -= ('A' - 10);
            else
                a -= '0';

            if (b >= 'a')
                b -= 'a'-'A';
            if (b >= 'A')
                b -= ('A' - 10);
            else
                b -= '0';

            *dst++ = 16*a+b;
            src+=3;
        }
        else if (*src == '+')
        {
            *dst++ = ' ';
            src++;
        }
        else
            *dst++ = *src++;
    }

    *dst++ = '\0';
}

tl::expected<void, std::string> urlverify(std::string_view str)
{
    http_parser_url puri;
    http_parser_url_init(&puri);
    if (const auto result = http_parser_parse_url(str.data(), str.size(), 0, &puri); result != 0)
        return tl::make_unexpected(fmt::format("http_parser_parse_url() failed with {}", result));
    return {};
}

const char *errorToStatus(httpd_err_code_t error)
{
    switch (error)
    {
    case HTTPD_501_METHOD_NOT_IMPLEMENTED:   return "501 Method Not Implemented";
    case HTTPD_505_VERSION_NOT_SUPPORTED:    return "505 Version Not Supported";
    case HTTPD_400_BAD_REQUEST:              return "400 Bad Request";
    case HTTPD_401_UNAUTHORIZED:             return "401 Unauthorized";
    case HTTPD_403_FORBIDDEN:                return "403 Forbidden";
    case HTTPD_404_NOT_FOUND:                return "404 Not Found";
    case HTTPD_405_METHOD_NOT_ALLOWED:       return "405 Method Not Allowed";
    case HTTPD_408_REQ_TIMEOUT:              return "408 Request Timeout";
    case HTTPD_414_URI_TOO_LONG:             return "414 URI Too Long";
    case HTTPD_411_LENGTH_REQUIRED:          return "411 Length Required";
    case HTTPD_431_REQ_HDR_FIELDS_TOO_LARGE: return "431 Request Header Fields Too Large";
    default:
        ESP_LOGW(TAG, "unknown httpd_err_code_t(%i)", std::to_underlying(error));
        [[fallthrough]];
    case HTTPD_500_INTERNAL_SERVER_ERROR:    return "500 Internal Server Error";
    }
}

esp_err_t webserver_resp_send_succ(httpd_req_t *req, const char *type, std::string_view body)
{
    CALL_AND_EXIT_ON_ERROR(httpd_resp_set_type, req, type)
    CALL_AND_EXIT_ON_ERROR(httpd_resp_send, req, body.data(), body.size())

    return ESP_OK;
}

esp_err_t webserver_resp_send_err(httpd_req_t *req, httpd_err_code_t error, const char *type, std::string_view body)
{
    CALL_AND_EXIT_ON_ERROR(httpd_resp_set_status, req, errorToStatus(error))
    CALL_AND_EXIT_ON_ERROR(httpd_resp_set_type, req, type)
    CALL_AND_EXIT_ON_ERROR(httpd_resp_send, req, body.data(), body.size())

    return ESP_OK;
}

} // namespace esphttpdutils

