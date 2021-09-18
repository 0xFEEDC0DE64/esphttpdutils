#pragma once

// system includes
#include <string>
#include <string_view>

namespace esphttpdutils {

class HtmlTag
{
public:
    HtmlTag(std::string_view tagName, std::string &body);

    HtmlTag(std::string_view tagName, std::string_view attributes, std::string &body);

    ~HtmlTag();

private:
    const std::string_view m_tagName;
    std::string &m_body;
};

inline HtmlTag::HtmlTag(std::string_view tagName, std::string &body) :
    m_tagName{tagName},
    m_body{body}
{
    m_body += '<';
    m_body += m_tagName;
    m_body += '>';
}

inline HtmlTag::HtmlTag(std::string_view tagName, std::string_view attributes, std::string &body) :
    m_tagName{tagName},
    m_body{body}
{
    m_body += '<';
    m_body += m_tagName;
    if (!attributes.empty())
    {
        m_body += ' ';
        m_body += attributes;
    }
    m_body += '>';
}

inline HtmlTag::~HtmlTag()
{
    m_body += "</";
    m_body += m_tagName;
    m_body += '>';
}

} // namespace esphttpdutils
