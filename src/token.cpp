#include "token.hpp"
#include <stdio.h>
#include <string.h>

const char *Token::type_string() {
    switch (type) {
    case Unknown:
        return "Unknown";
    case Word:
        return "Word";
    case String:
        return "String";
    case OpenBrace:
        return "OpenBrace";
    case CloseBrace:
        return "CloseBrace";
    case Eof:
        return "Eof";
    }
    return 0;
}
void Token::print() {
    fprintf(stdout, "%s %.*s start:%ld end:%ld\n", type_string(), (int)(end - start), word, start,
            end);
}
void Token::print_word() {
    fprintf(stdout, "%.*s\n", (int)(end - start), word);
}
bool Token::equals(const char *other) {
    auto len = strlen(other);
    return end - start == len && !strncmp(word, other, len);
}

bool Token::starts_with(const char *other) {
    return !strncmp(word, other, strlen(other));
}