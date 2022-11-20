#pragma once

#include <string>

struct Token {
    enum TokenType {
        Unknown,
        Word,
        OpenBrace,
        CloseBrace,
        Eof,
    };
    TokenType type = Word;
    const char *word = 0;
    unsigned long start = 0;
    unsigned long end = 0;
    const char *type_string();
    void print();
    void print_word();
    bool equals(const char *other);
    bool starts_with(const char *other);
    std::string get_word();
};