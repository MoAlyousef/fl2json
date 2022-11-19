#pragma once

#include "ast.hpp"
#include "lexer.hpp"
#include <string>
#include <vector>

class Parser {
    std::vector<Token> tokens;
    size_t i = 0;
    Function consume_func();
    Widget consume_widget();
    Class consume_class();
    Comment consume_comment();
    Decl consume_decl();
    std::string consume_code();
    std::string consume_braced_string();

  public:
    Parser(Lexer lexer);
    Ast parse();
};