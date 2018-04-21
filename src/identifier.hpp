#ifndef BRK_IDENTIFIER_HPP
#define BRK_IDENTIFIER_HPP

#include <string>

class Identifier {
public:
    Identifier(const std::string &t_value) : m_value(t_value) { }

    std::string m_value;
private:
};

#endif //BRK_IDENTIFIER_HPP