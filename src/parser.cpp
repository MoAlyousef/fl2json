#include "parser.hpp"
#include "ast.hpp"
#include "token.hpp"
#include <cstdlib>
#include <string>

std::string Parser::consume_braced_string() {
    i += 1;
    auto t = tokens[i];
    auto start = t.start;
    auto openbrace = 1;
    while (t.type != Token::Eof) {
        i += 1;
        t = tokens[i];
        if (t.type == Token::OpenBrace) {
            openbrace += 1;
        }
        if (t.type == Token::CloseBrace) {
            openbrace -= 1;
        }
        if (openbrace == 0) {
            break;
        }
    }
    auto end = tokens[i].end - 1;
    return std::string(&lexer.s[start], end - start);
}

std::string Parser::consume_code() {
    auto s = consume_braced_string();
    // skip last 2 braces
    i += 2;
    return s;
}

Widget Parser::consume_widget() {
    Widget w;
    w.type = tokens[i].get_word();
    i += 1;
    if (tokens[i].type == Token::OpenBrace) {
        i += 1;
    }
    w.name = tokens[i].get_word();
    while (tokens[i].type != Token::Eof) {
        i += 1;
        if (tokens[i].type == Token::CloseBrace)
            break;
        if (tokens[i].equals("open"))
            w.props.open = true;
        if (tokens[i].equals("hide"))
            w.props.hide = true;
        if (tokens[i].equals("deactivate"))
            w.props.deactivate = true;
        if (tokens[i].equals("divider"))
            w.props.divider = true;
        if (tokens[i].equals("resizable"))
            w.props.resizable = true;
        if (tokens[i].equals("visible"))
            w.props.visible = true;
        if (tokens[i].equals("hotspot"))
            w.props.hotspot = true;
        if (tokens[i].equals("xywh")) {
            i += 1;
            w.props.xywh = consume_braced_string();
        }
        if (tokens[i].equals("color")) {
            i += 1;
            w.props.color = strtoul(tokens[i].get_word().c_str(), nullptr, 10);
        }
        if (tokens[i].equals("selection_color")) {
            i += 1;
            w.props.selection_color = strtoul(tokens[i].get_word().c_str(), nullptr, 10);
        }
        if (tokens[i].equals("labelcolor")) {
            i += 1;
            w.props.labelcolor = strtoul(tokens[i].get_word().c_str(), nullptr, 10);
        }
        if (tokens[i].equals("textcolor")) {
            i += 1;
            w.props.textcolor = strtoul(tokens[i].get_word().c_str(), nullptr, 10);
        }
        if (tokens[i].equals("type")) {
            i += 1;
            w.props.type = tokens[i].get_word();
        }
        if (tokens[i].equals("labeltype")) {
            i += 1;
            w.props.labeltype = tokens[i].get_word();
        }
        if (tokens[i].equals("labelfont")) {
            i += 1;
            w.props.labelfont = atoi(tokens[i].get_word().c_str());
        }
        if (tokens[i].equals("textfont")) {
            i += 1;
            w.props.textfont = atoi(tokens[i].get_word().c_str());
        }
        if (tokens[i].equals("labelsize")) {
            i += 1;
            w.props.labelsize = atoi(tokens[i].get_word().c_str());
        }
        if (tokens[i].equals("textsize")) {
            i += 1;
            w.props.textsize = atoi(tokens[i].get_word().c_str());
        }
        if (tokens[i].equals("box")) {
            i += 1;
            w.props.box = tokens[i].get_word();
        }
        if (tokens[i].equals("down_box")) {
            i += 1;
            w.props.down_box = tokens[i].get_word();
        }
        if (tokens[i].equals("align")) {
            i += 1;
            w.props.align = atoi(tokens[i].get_word().c_str());
        }
        if (tokens[i].equals("when")) {
            i += 1;
            w.props.when = atoi(tokens[i].get_word().c_str());
        }
        if (tokens[i].equals("shortcut")) {
            i += 1;
            w.props.shortcut = atoi(tokens[i].get_word().c_str());
        }
        if (tokens[i].equals("gap")) {
            i += 1;
            w.props.gap = atoi(tokens[i].get_word().c_str());
        }
        if (tokens[i].equals("minimum")) {
            i += 1;
            w.props.minimum = strtod(tokens[i].get_word().c_str(), nullptr);
        }
        if (tokens[i].equals("maximum")) {
            i += 1;
            w.props.maximum = strtod(tokens[i].get_word().c_str(), nullptr);
        }
        if (tokens[i].equals("step")) {
            i += 1;
            w.props.step = strtod(tokens[i].get_word().c_str(), nullptr);
        }
        if (tokens[i].equals("slider_size")) {
            i += 1;
            w.props.slider_size = strtod(tokens[i].get_word().c_str(), nullptr);
        }
        if (tokens[i].equals("size")) {
            i += 1;
            w.props.size = strtod(tokens[i].get_word().c_str(), nullptr);
        }
        if (tokens[i].equals("label")) {
            i += 1;
            if (tokens[i].type == Token::OpenBrace) {
                w.props.label = consume_braced_string();
            } else {
                w.props.label = tokens[i].get_word();
            }
        }
        if (tokens[i].equals("class")) {
            i += 1;
            if (tokens[i].type == Token::OpenBrace) {
                w.props.klass = consume_braced_string();
            } else {
                w.props.klass = tokens[i].get_word();
            }
        }
        if (tokens[i].equals("tooltip")) {
            i += 1;
            if (tokens[i].type == Token::OpenBrace) {
                w.props.tooltip = consume_braced_string();
            } else {
                w.props.tooltip = tokens[i].get_word();
            }
        }
        if (tokens[i].equals("image")) {
            i += 1;
            if (tokens[i].type == Token::OpenBrace) {
                w.props.image = consume_braced_string();
            } else {
                w.props.image = tokens[i].get_word();
            }
        }
        if (tokens[i].equals("deimage")) {
            i += 1;
            if (tokens[i].type == Token::OpenBrace) {
                w.props.deimage = consume_braced_string();
            } else {
                w.props.deimage = tokens[i].get_word();
            }
        }
        if (tokens[i].equals("value")) {
            i += 1;
            if (tokens[i].type == Token::OpenBrace) {
                w.props.value = consume_braced_string();
            } else {
                w.props.value = tokens[i].get_word();
            }
        }
        if (tokens[i].equals("set_size_tuples")) {
            i += 1;
            std::string s = consume_braced_string();
            w.props.size_tuple = s;
        }
        if (tokens[i].equals("code0")) {
            i += 1;
            std::string s = consume_braced_string();
            w.props.code0 = s;
        }
        if (tokens[i].equals("code1")) {
            i += 1;
            std::string s = consume_braced_string();
            w.props.code1 = s;
        }
        if (tokens[i].equals("code2")) {
            i += 1;
            std::string s = consume_braced_string();
            w.props.code2 = s;
        }
        if (tokens[i].equals("code3")) {
            i += 1;
            std::string s = consume_braced_string();
            w.props.code3 = s;
        }
        if (tokens[i].equals("extra_code")) {
            i += 1;
            std::string s = consume_braced_string();
            w.props.extra_code = s;
        }
        if (tokens[i].equals("callback")) {
            i += 1;
            if (tokens[i].type == Token::OpenBrace) {
                w.props.callback = consume_braced_string();
            } else {
                w.props.callback = tokens[i].get_word();
            }
        }
        if (tokens[i].equals("user_data")) {
            i += 1;
            if (tokens[i].type == Token::OpenBrace) {
                w.props.user_data = consume_braced_string();
            } else {
                w.props.user_data = tokens[i].get_word();
            }
        }
        if (tokens[i].equals("user_data_type")) {
            i += 1;
            if (tokens[i].type == Token::OpenBrace) {
                w.props.user_data_type = consume_braced_string();
            } else {
                w.props.user_data_type = tokens[i].get_word();
            }
        }
        if (tokens[i].equals("comment")) {
            i += 1;
            if (tokens[i].type == Token::OpenBrace) {
                w.props.comment = consume_braced_string();
            } else {
                w.props.comment = tokens[i].get_word();
            }
        }
    }
    if (tokens[i + 1].type == Token::OpenBrace) {
        i += 1;
        while (tokens[i].type != Token::CloseBrace) {
            i += 1;
            while (tokens[i].starts_with("Fl_")
                || tokens[i].equals("MenuItem")
                || tokens[i].equals("Submenu"))
            {
                auto c = consume_widget();
                w.children.push_back(c);
                i += 1;
            }
        }
    }
    return w;
}

Class Parser::consume_class() {
    Class c;
    i += 1;
    if (tokens[i].type == Token::OpenBrace) {
        i += 2;
    }
    c.name = tokens[i].get_word();
    i += 1;
    // handle props
    while (tokens[i].type != Token::CloseBrace) {
        i += 1;
        if (tokens[i].equals("open"))
            c.props.open = true;
        if (tokens[i].equals("protected"))
            c.props.visibility = Visibility::PROTECTED;
        if (tokens[i].equals("private"))
            c.props.visibility = Visibility::PRIVATE;
        if (tokens[i].equals("comment")) {
            i += 1;
            if (tokens[i].type == Token::OpenBrace) {
                c.props.comment = consume_braced_string();
            } else {
                c.props.comment = tokens[i].get_word();
            }
        }
    }
    i += 1;
    if (tokens[i].type == Token::OpenBrace) {
        while (tokens[i].type != Token::CloseBrace) {
            i += 1;
            while (tokens[i].equals("Function")) {
                auto f = consume_func();
                c.functions.push_back(f);
            }
            if (tokens[i].equals("comment")) {
                i += 1;
                if (tokens[i].type == Token::OpenBrace) {
                    c.props.comment = consume_braced_string();
                } else {
                    c.props.comment = tokens[i].get_word();
                }
            }
        }
    }
    return c;
}

Function Parser::consume_func() {
    Function f;
    i += 1;
    i += 1;
    f.name = tokens[i].get_word();
    i += 1; // closing parens of function name
    i += 1; // opening parens of props
    while (tokens[i].type != Token::Eof) {
        i += 1;
        if (tokens[i].type == Token::CloseBrace) {
            break;
        }
        auto t = tokens[i];

        if (t.equals("open"))
            f.props.open = true;
        if (t.equals("C"))
            f.props.C = true;
        if (t.equals("protected"))
            f.props.visibility = Visibility::PROTECTED;
        if (t.equals("private"))
            f.props.visibility = Visibility::PRIVATE;
        if (t.equals("comment")) {
            i += 1;
            if (tokens[i].type == Token::OpenBrace) {
                f.props.comment = consume_braced_string();
            } else {
                f.props.comment = tokens[i].get_word();
            }
        }
        if (t.equals("return_type")) {
            i += 1;
            if (tokens[i].type == Token::OpenBrace) {
                f.props.return_type = consume_braced_string();
            } else {
                f.props.return_type = tokens[i].get_word();
            }
        }
    }
    i += 1; // close props parens
    if (tokens[i].type == Token::OpenBrace) {
        while (tokens[i].type != Token::CloseBrace) {
            i += 1;
            if (tokens[i].equals("code")) {
                i += 1;
                f.code = consume_code();
                i += 1;
            }
            if (tokens[i].starts_with("Fl_") || tokens[i].equals("MenuItem") ||
                tokens[i].equals("Submenu")) {
                auto w = consume_widget();
                f.widgets.push_back(w);
                i += 1;
            }
        }
    }
    i += 1;
    return f;
}

Comment Parser::consume_comment() {
    Comment c;
    i += 1;
    c.comment = consume_braced_string();
    while (tokens[i].type != Token::Eof) {
        i += 1;
        if (tokens[i].type == Token::CloseBrace) {
            break;
        }
        auto t = tokens[i];
        if (t.equals("in_source"))
            c.props.in_source = true;
        if (t.equals("in_header"))
            c.props.in_header = true;
    }
    return c;
}

Decl Parser::consume_decl() {
    Decl d;
    i += 1;
    d.decl = consume_braced_string();
    while (tokens[i].type != Token::Eof) {
        i += 1;
        if (tokens[i].type == Token::CloseBrace) {
            break;
        }
        auto t = tokens[i];
        if (t.equals("private"))
            d.props.visibility = Visibility::PRIVATE;
        if (t.equals("public"))
            d.props.visibility = Visibility::PUBLIC;
        if (t.equals("global"))
            d.props.global = true;
        if (t.equals("local"))
            d.props.local = true;
    }
    return d;
}

Parser::Parser(Lexer l) : lexer(l) {
    auto t = lexer.next();
    tokens.push_back(t);
    while (t.type != Token::Eof) {
        t = lexer.next();
        tokens.push_back(t);
    }
}

Ast Parser::parse() {
    Ast a;
    Token t;
    while (i < tokens.size()) {
        auto curr = tokens[i];
        switch (curr.type) {
        case Token::Eof:
            break;
        case Token::Word: {
            if (curr.equals("version")) {
                i += 1;
                a.version = strtod(tokens[i].get_word().c_str(), 0);
            }
            if (curr.equals("i18n_type")) {
                a.i18n_type = true;
                i += 2;
            }
            if (curr.equals("header_name")) {
                i += 1;
                a.header_name = consume_braced_string();
            }
            if (curr.equals("code_name")) {
                i += 1;
                a.code_name = consume_braced_string();
            }
            if (curr.equals("class")) {
                if (tokens[i].equals("class")) {
                    auto c = consume_class();
                    a.classes.push_back(c);
                }
            }
            if (curr.equals("Function")) {
                auto f = consume_func();
                a.functions.push_back(f);
            }
            if (curr.equals("comment")) {
                auto c = consume_comment();
                a.comments.push_back(c);
            }
            if (curr.equals("decl")) {
                auto d = consume_decl();
                a.decls.push_back(d);
            }
        };
        default: {
        }
        }
        i += 1;
    }
    return a;
}
