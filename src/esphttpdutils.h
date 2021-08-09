#pragma once

// system includes
#include <string>
#include <string_view>

// esp-idf includes
#include <esp_http_server.h>

// 3rdparty lib includes
#include <tl/expected.hpp>

namespace esphttpdutils {

template<typename T> T htmlentities(const T &val) { return val; } // TODO
template<typename T> T htmlentities(T &&val) { return val; } // TODO

void urldecode(char *dst, const char *src);

tl::expected<void, std::string> urlverify(std::string_view str);

const char *errorToStatus(httpd_err_code_t error);

esp_err_t webserver_prepare_response(httpd_req_t *req);

esp_err_t webserver_resp_send_succ(httpd_req_t *req, const char *type, std::string_view body);
esp_err_t webserver_resp_send_err(httpd_req_t *req, httpd_err_code_t error, const char *type, std::string_view body);

} // namespace esphttpdutils
