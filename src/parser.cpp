#include "parser.hpp"
#include "ast.hpp"
#include "token.hpp"
#include <cstdlib>
#include <string>

std::string consume_word(Token &t) {
    return t.get_word();
}

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
    // auto t = l.next();
    // if (t.type == Token::OpenBrace) {
    //     t = l.next();
    // }
    // if (t.get_word())
    //     w.name = consume_word(t);
    // else
    //     w.name = "";
    // while (t.type != Token::Eof) {
    //     t = l.next();
    //     if (t.type == Token::CloseBrace)
    //         break;
    //     if (t.get_word()) {
    //         if (t.equals("open"))
    //             w.props.open = true;
    //         if (t.equals("hide"))
    //             w.props.hide = true;
    //         if (t.equals("deactivate"))
    //             w.props.deactivate = true;
    //         if (t.equals("divider"))
    //             w.props.divider = true;
    //         if (t.equals("resizable"))
    //             w.props.resizable = true;
    //         if (t.equals("visible"))
    //             w.props.visible = true;
    //         if (t.equals("hotspot"))
    //             w.props.hotspot = true;
    //         if (t.equals("xywh")) {
    //             l.next();
    //             w.props.xywh = consume_braced_string(l);
    //         }
    //         if (t.equals("color")) {
    //             t = l.next();
    //             w.props.color = strtoul(consume_word(t).c_str(), nullptr, 10);
    //         }
    //         if (t.equals("selection_color")) {
    //             t = l.next();
    //             w.props.selection_color = strtoul(consume_word(t).c_str(), nullptr, 10);
    //         }
    //         if (t.equals("labelcolor")) {
    //             t = l.next();
    //             w.props.labelcolor = strtoul(consume_word(t).c_str(), nullptr, 10);
    //         }
    //         if (t.equals("textcolor")) {
    //             t = l.next();
    //             w.props.textcolor = strtoul(consume_word(t).c_str(), nullptr, 10);
    //         }
    //         if (t.equals("type")) {
    //             t = l.next();
    //             w.props.type = consume_word(t);
    //         }
    //         if (t.equals("labeltype")) {
    //             t = l.next();
    //             w.props.labeltype = consume_word(t);
    //         }
    //         if (t.equals("labelfont")) {
    //             t = l.next();
    //             w.props.labelfont = atoi(consume_word(t).c_str());
    //         }
    //         if (t.equals("textfont")) {
    //             t = l.next();
    //             w.props.textfont = atoi(consume_word(t).c_str());
    //         }
    //         if (t.equals("labelsize")) {
    //             t = l.next();
    //             w.props.labelsize = atoi(consume_word(t).c_str());
    //         }
    //         if (t.equals("textsize")) {
    //             t = l.next();
    //             w.props.textsize = atoi(consume_word(t).c_str());
    //         }
    //         if (t.equals("box")) {
    //             l.next();
    //             w.props.box = consume_word(t);
    //         }
    //         if (t.equals("down_box")) {
    //             l.next();
    //             w.props.down_box = consume_word(t);
    //         }
    //         if (t.equals("align")) {
    //             t = l.next();
    //             w.props.align = atoi(consume_word(t).c_str());
    //         }
    //         if (t.equals("when")) {
    //             t = l.next();
    //             w.props.when = atoi(consume_word(t).c_str());
    //         }
    //         if (t.equals("shortcut")) {
    //             t = l.next();
    //             w.props.shortcut = atoi(consume_word(t).c_str());
    //         }
    //         if (t.equals("gap")) {
    //             t = l.next();
    //             w.props.gap = atoi(consume_word(t).c_str());
    //         }
    //         if (t.equals("minimum")) {
    //             t = l.next();
    //             w.props.minimum = strtod(consume_word(t).c_str(), nullptr);
    //         }
    //         if (t.equals("maximum")) {
    //             t = l.next();
    //             w.props.maximum = strtod(consume_word(t).c_str(), nullptr);
    //         }
    //         if (t.equals("step")) {
    //             t = l.next();
    //             w.props.step = strtod(consume_word(t).c_str(), nullptr);
    //         }
    //         if (t.equals("slider_size")) {
    //             t = l.next();
    //             w.props.slider_size = strtod(consume_word(t).c_str(), nullptr);
    //         }
    //         if (t.equals("size")) {
    //             t = l.next();
    //             w.props.size = strtod(consume_word(t).c_str(), nullptr);
    //         }
    //         if (t.equals("label")) {
    //             t = l.next();
    //             if (t.type == Token::OpenBrace) {
    //                 w.props.label = consume_braced_string(l);
    //             } else {
    //                 w.props.label = consume_word(t);
    //             }
    //         }
    //         if (t.equals("class")) {
    //             t = l.next();
    //             if (t.type == Token::OpenBrace) {
    //                 w.props.klass = consume_braced_string(l);
    //             } else {
    //                 w.props.klass = consume_word(t);
    //             }
    //         }
    //         if (t.equals("tooltip")) {
    //             t = l.next();
    //             if (t.type == Token::OpenBrace) {
    //                 w.props.tooltip = consume_braced_string(l);
    //             } else {
    //                 w.props.tooltip = consume_word(t);
    //             }
    //         }
    //         if (t.equals("image")) {
    //             t = l.next();
    //             if (t.type == Token::OpenBrace) {
    //                 w.props.image = consume_braced_string(l);
    //             } else {
    //                 w.props.image = consume_word(t);
    //             }
    //         }
    //         if (t.equals("deimage")) {
    //             t = l.next();
    //             if (t.type == Token::OpenBrace) {
    //                 w.props.deimage = consume_braced_string(l);
    //             } else {
    //                 w.props.deimage = consume_word(t);
    //             }
    //         }
    //         if (t.equals("value")) {
    //             t = l.next();
    //             if (t.type == Token::OpenBrace) {
    //                 w.props.value = consume_braced_string(l);
    //             } else {
    //                 w.props.value = consume_word(t);
    //             }
    //         }
    //         if (t.equals("set_size_tuples")) {
    //             l.next();
    //             std::string s = consume_braced_string(l);
    //             w.props.size_tuple = s;
    //         }
    //         if (t.equals("code0")) {
    //             l.next();
    //             std::string s = consume_braced_string(l);
    //             w.props.code0 = s;
    //         }
    //         if (t.equals("code1")) {
    //             l.next();
    //             std::string s = consume_braced_string(l);
    //             w.props.code1 = s;
    //         }
    //         if (t.equals("code2")) {
    //             l.next();
    //             std::string s = consume_braced_string(l);
    //             w.props.code2 = s;
    //         }
    //         if (t.equals("code3")) {
    //             l.next();
    //             std::string s = consume_braced_string(l);
    //             w.props.code3 = s;
    //         }
    //         if (t.equals("extra_code")) {
    //             l.next();
    //             std::string s = consume_braced_string(l);
    //             w.props.extra_code = s;
    //         }
    //         if (t.equals("callback")) {
    //             t = l.next();
    //             if (t.type == Token::OpenBrace) {
    //                 w.props.callback = consume_braced_string(l);
    //             } else {
    //                 w.props.callback = consume_word(t);
    //             }
    //         }
    //         if (t.equals("user_data")) {
    //             t = l.next();
    //             if (t.type == Token::OpenBrace) {
    //                 w.props.user_data = consume_braced_string(l);
    //             } else {
    //                 w.props.user_data = consume_word(t);
    //             }
    //         }
    //         if (t.equals("user_data_type")) {
    //             t = l.next();
    //             if (t.type == Token::OpenBrace) {
    //                 w.props.user_data_type = consume_braced_string(l);
    //             } else {
    //                 w.props.user_data_type = consume_word(t);
    //             }
    //         }
    //         if (t.equals("comment")) {
    //             t = l.next();
    //             if (t.type == Token::OpenBrace) {
    //                 w.props.comment = consume_braced_string(l);
    //             } else {
    //                 w.props.comment = consume_word(t);
    //             }
    //         }
    //     }
    // }
    // t = l.next();
    // // We have children
    // if (t.type == Token::OpenBrace) {
    //     int OpenBrace = 1;
    //     while (t.type != Token::Eof) {
    //         t = l.next();
    //         if (t.type == Token::OpenBrace)
    //             OpenBrace++;
    //         if (t.type == Token::CloseBrace)
    //             OpenBrace--;
    //         if (OpenBrace == 0)
    //             break;
    //         if (t.get_word())
    //             if (t.starts_with("Fl_") || t.equals("MenuItem") || t.equals("Submenu")) {
    //                 auto c = consume_widget();
    //                 c.type = consume_word(t);
    //                 w.children.push_back(c);
    //             }
    //     }
    // }
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
            if (tokens[i].starts_with("Fl_") || tokens[i].equals("MenuItem") ||
                tokens[i].equals("Submenu")) {
                auto w = consume_widget();
                f.widgets.push_back(w);
                i += 1;
            }
            if (tokens[i].equals("code")) {
                i += 1;
                f.code = consume_code();
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
                i+=1;
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
