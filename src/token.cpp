#include "token.hpp"
#include <stdio.h>
#include <string.h>

const char *Token::type_string() const {
    switch (type) {
    case Unknown:
        return "Unknown";
    case Word:
        return "Word";
    case OpenBrace:
        return "OpenBrace";
    case CloseBrace:
        return "CloseBrace";
    case Eof:
        return "Eof";
    }
    return nullptr;
}
void Token::print() const {
    fprintf(stdout, "%s %.*s start:%ld end:%ld\n", type_string(), (int)(end - start), word, start,
            end);
}
void Token::print_word() const {
    fprintf(stdout, "%.*s\n", (int)(end - start), word);
}
bool Token::equals(const char *other) const {
    auto len = strlen(other);
    return end - start == len && (strncmp(word, other, len) == 0);
}

bool Token::starts_with(const char *other) const {
    return get_word().find(other) == 0;
}

std::string Token::get_word() const {
    if (word == nullptr) {
        return "";
    }
    return std::string(word, end - start);
}