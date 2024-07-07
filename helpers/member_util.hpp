#ifndef MEMBER_UTIL_HPP
#define MEMBER_UTIL_HPP

#include <tuple>
#include <vector>
#include <string>

#define GENERATE_MEMBER_FUNCTIONS(...)                                        \
public:                                                                       \
    auto getMembers() const {                                                 \
        return std::tie(__VA_ARGS__);                                         \
    }                                                                         \
    std::vector<std::string> getMemberNames() const {                         \
        return split(# __VA_ARGS__);                                          \
    }                                                                         \
private:                                                                      \
    static std::vector<std::string> split(const std::string &s) {             \
        std::vector<std::string> names;                                       \
        std::string temp;                                                     \
        for (char c : s) {                                                    \
            if (c == ',') {                                                   \
                names.push_back(temp);                                        \
                temp.clear();                                                 \
            } else if (!std::isspace(c)) {                                    \
                temp += c;                                                    \
            }                                                                 \
        }                                                                     \
        if (!temp.empty()) {                                                  \
            names.push_back(temp);                                            \
        }                                                                     \
        return names;                                                         \
    }

#endif // MEMBER_UTIL_HPP
