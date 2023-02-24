#include "lexer.hpp"
#include "token.hpp"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

Lexer::Lexer(const char *source, size_t len) : s(source), size(len) {
    // ignore first line
    while (cursor < size && s[cursor] != '\n') {
        cursor++;
    }
}

Token Lexer::next() {
    Token t;
    t.type = Token::Unknown;
    if (cursor == size) {
        t.type = Token::Eof;
        t.start = size;
        t.end = size;
        return t;
    }
    while (cursor < size && (isspace(s[cursor]) != 0)) {
        cursor++;
    }
    switch (s[cursor]) {
    case '{': {
        t.type = Token::OpenBrace;
        t.start = cursor;
        t.end = cursor + 1;
        cursor++;
        return t;
    }
    case '}': {
        t.type = Token::CloseBrace;
        t.start = cursor;
        t.end = cursor + 1;
        cursor++;
        return t;
    }
    default: {
        t.type = Token::Word;
        t.word = &s[cursor];
        t.start = cursor;
        while (cursor < size && (isspace(s[cursor]) == 0) && s[cursor] != '}') {
            cursor++;
        }
        t.end = cursor;
        return t;
    }
    }
}
