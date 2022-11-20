#pragma once

#include "token.hpp"
#include <cstddef>
#include <stdio.h>
#include <stdlib.h>

struct Lexer {
    const char *s = nullptr;
    size_t size = 0;
    size_t cursor = 0;
    Lexer(const char *source, size_t len);
    Token next();
};