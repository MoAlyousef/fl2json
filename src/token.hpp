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
    const char *type_string() const;
    void print() const;
    void print_word() const;
    bool equals(const char *other) const;
    bool starts_with(const char *other) const;
    std::string get_word() const;
};