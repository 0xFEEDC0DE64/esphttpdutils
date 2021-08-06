set(headers
    src/esphttpdutils.h
)

set(sources
    src/esphttpdutils.cpp
)

set(dependencies
    esp_http_server
    nghttp

    cpputils
    espchrono
    espcpputils
    expected
    fmt
)

idf_component_register(
    INCLUDE_DIRS
        src
    SRCS
        ${headers}
        ${sources}
    REQUIRES
        ${dependencies}
)

target_compile_options(${COMPONENT_TARGET}
    PRIVATE
        -fstack-reuse=all
        -fstack-protector-all
        -Wno-unused-function
        -Wno-deprecated-declarations
        -Wno-missing-field-initializers
        -Wno-parentheses
)