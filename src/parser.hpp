#pragma once

#include "ast.hpp"
#include "lexer.hpp"

class Parser {
    Lexer l;
    Function consume_func();
    Widget consume_widget();
    Class consume_class();
    Comment consume_comment();
    Decl consume_decl();
    std::string consume_code();
  public:
    Parser(Lexer lexer);
    Ast parse();
};