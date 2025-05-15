#include "esphttpdutils.h"

// system includes
#include <utility>
#include <format>

// esp-idf includes
#include <esp_log.h>
#include <http_parser.h>

// 3rdparty lib includes
#include "espcppmacros.h"

namespace esphttpdutils {
namespace {
constexpr const char * const TAG = "ESPHTTPDUTILS";
} // namespace

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

std::expected<void, std::string> urlverify(std::string_view str)
{
    if (str.empty())
        return std::unexpected("empty url is not valid");

    http_parser_url puri;
    http_parser_url_init(&puri);
    if (const auto result = http_parser_parse_url(str.data(), str.size(), 0, &puri); result != 0)
        return std::unexpected(std::format("http_parser_parse_url() failed with {}", result));
    return {};
}

esp_err_t webserver_prepare_response(httpd_req_t *req)
{
    CALL_AND_EXIT_ON_ERROR(httpd_resp_set_hdr, req, "Connection", "close")
    CALL_AND_EXIT_ON_ERROR(httpd_resp_set_hdr, req, "Access-Control-Allow-Origin", "*")

    return ESP_OK;
}

esp_err_t webserver_resp_send(httpd_req_t *req, ResponseStatus error, const char *type, std::string_view body)
{
    CALL_AND_EXIT_ON_ERROR(httpd_resp_set_status, req, toString(error))
    CALL_AND_EXIT_ON_ERROR(httpd_resp_set_type, req, type)
    CALL_AND_EXIT_ON_ERROR(httpd_resp_send, req, body.data(), body.size())

    return ESP_OK;
}

std::expected<std::string, std::string> webserver_get_query(httpd_req_t *req)
{
    std::string query;

    if (const size_t queryLength = httpd_req_get_url_query_len(req))
    {
        query.resize(queryLength);
        if (const auto result = httpd_req_get_url_query_str(req, query.data(), query.size() + 1); result != ESP_OK)
            return std::unexpected(std::format("httpd_req_get_url_query_str() failed with {}", esp_err_to_name(result)));
    }

    return query;
}

#ifdef CONFIG_HTTPD_WS_SUPPORT
std::string toString(httpd_ws_type_t val)
{
    switch (val)
    {
    case HTTPD_WS_TYPE_CONTINUE: return "HTTPD_WS_TYPE_CONTINUE"; break;
    case HTTPD_WS_TYPE_TEXT:     return "HTTPD_WS_TYPE_TEXT";     break;
    case HTTPD_WS_TYPE_BINARY:   return "HTTPD_WS_TYPE_BINARY";   break;
    case HTTPD_WS_TYPE_CLOSE:    return "HTTPD_WS_TYPE_CLOSE";    break;
    case HTTPD_WS_TYPE_PING:     return "HTTPD_WS_TYPE_PING";     break;
    case HTTPD_WS_TYPE_PONG:     return "HTTPD_WS_TYPE_PONG";     break;
    }
    ESP_LOGW(TAG, "Unknown httpd_ws_type_t(%i)", std::to_underlying(val));
    return std::format("Unknown httpd_ws_type_t({})", std::to_underlying(val));
}
#endif // CONFIG_HTTPD_WS_SUPPORT

} // namespace esphttpdutils

