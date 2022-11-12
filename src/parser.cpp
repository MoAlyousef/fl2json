#include "parser.hpp"
#include "ast.hpp"
#include "token.hpp"
#include <cstdlib>
#include <string>

std::string consume_word(Token &t) {
    return std::string(t.word, t.end - t.start);
}

std::string consume_braced_string(Lexer &l) {
    auto t = l.next();
    const char *word = t.word;
    unsigned long start = t.start;
    unsigned long end;
    int openbrace = 1;
    while (t.type != Token::Eof) {
        t = l.next();
        if (t.type == Token::OpenBrace)
            openbrace++;
        if (t.type == Token::CloseBrace)
            openbrace--;
        if (openbrace == 0)
            break;
    }
    end = t.end - 1;

    if (!word)
        return std::string("");
    return std::string(word, end - start);
}

std::string Parser::consume_code() {
    auto s = consume_braced_string(l);
    // skip last 2 braces
    l.next();
    l.next();
    return s;
}

Widget Parser::consume_widget() {
    Widget w;
    auto t = l.next();
    if (t.type == Token::OpenBrace) {
        t = l.next();
    }
    if (t.word)
        w.name = consume_word(t);
    else
        w.name = "";
    while (t.type != Token::Eof) {
        t = l.next();
        if (t.type == Token::CloseBrace)
            break;
        if (t.word) {
            if (t.equals("open"))
                w.props.open = true;
            if (t.equals("hide"))
                w.props.hide = true;
            if (t.equals("deactivate"))
                w.props.deactivate = true;
            if (t.equals("divider"))
                w.props.divider = true;
            if (t.equals("resizable"))
                w.props.resizable = true;
            if (t.equals("visible"))
                w.props.visible = true;
            if (t.equals("hotspot"))
                w.props.hotspot = true;
            if (t.equals("xywh")) {
                l.next();
                w.props.xywh = consume_braced_string(l);
            }
            if (t.equals("color")) {
                t = l.next();
                w.props.color = strtoul(consume_word(t).c_str(), nullptr, 10);
            }
            if (t.equals("selection_color")) {
                t = l.next();
                w.props.selection_color = strtoul(consume_word(t).c_str(), nullptr, 10);
            }
            if (t.equals("labelcolor")) {
                t = l.next();
                w.props.labelcolor = strtoul(consume_word(t).c_str(), nullptr, 10);
            }
            if (t.equals("textcolor")) {
                t = l.next();
                w.props.textcolor = strtoul(consume_word(t).c_str(), nullptr, 10);
            }
            if (t.equals("type")) {
                t = l.next();
                w.props.type = consume_word(t);
            }
            if (t.equals("labeltype")) {
                t = l.next();
                w.props.labeltype = consume_word(t);
            }
            if (t.equals("labelfont")) {
                t = l.next();
                w.props.labelfont = atoi(consume_word(t).c_str());
            }
            if (t.equals("textfont")) {
                t = l.next();
                w.props.textfont = atoi(consume_word(t).c_str());
            }
            if (t.equals("labelsize")) {
                t = l.next();
                w.props.labelsize = atoi(consume_word(t).c_str());
            }
            if (t.equals("textsize")) {
                t = l.next();
                w.props.textsize = atoi(consume_word(t).c_str());
            }
            if (t.equals("box")) {
                l.next();
                w.props.box = consume_word(t);
            }
            if (t.equals("down_box")) {
                l.next();
                w.props.box = consume_word(t);
            }
            if (t.equals("align")) {
                t = l.next();
                w.props.align = atoi(consume_word(t).c_str());
            }
            if (t.equals("when")) {
                t = l.next();
                w.props.when = atoi(consume_word(t).c_str());
            }
            if (t.equals("shortcut")) {
                t = l.next();
                w.props.shortcut = atoi(consume_word(t).c_str());
            }
            if (t.equals("gap")) {
                t = l.next();
                w.props.gap = atoi(consume_word(t).c_str());
            }
            if (t.equals("minimum")) {
                t = l.next();
                w.props.minimum = strtod(consume_word(t).c_str(), nullptr);
            }
            if (t.equals("maximum")) {
                t = l.next();
                w.props.maximum = strtod(consume_word(t).c_str(), nullptr);
            }
            if (t.equals("step")) {
                t = l.next();
                w.props.step = strtod(consume_word(t).c_str(), nullptr);
            }
            if (t.equals("slider_size")) {
                t = l.next();
                w.props.slider_size = strtod(consume_word(t).c_str(), nullptr);
            }
            if (t.equals("size")) {
                t = l.next();
                w.props.size = strtod(consume_word(t).c_str(), nullptr);
            }
            if (t.equals("label")) {
                t = l.next();
                if (t.type == Token::OpenBrace) {
                    w.props.label = consume_braced_string(l);
                } else {
                    w.props.label = consume_word(t);
                }
            }
            if (t.equals("class")) {
                t = l.next();
                if (t.type == Token::OpenBrace) {
                    w.props.klass = consume_braced_string(l);
                } else {
                    w.props.klass = consume_word(t);
                }
            }
            if (t.equals("tooltip")) {
                t = l.next();
                if (t.type == Token::OpenBrace) {
                    w.props.tooltip = consume_braced_string(l);
                } else {
                    w.props.tooltip = consume_word(t);
                }
            }
            if (t.equals("image")) {
                t = l.next();
                if (t.type == Token::OpenBrace) {
                    w.props.image = consume_braced_string(l);
                } else {
                    w.props.image = consume_word(t);
                }
            }
            if (t.equals("deimage")) {
                t = l.next();
                if (t.type == Token::OpenBrace) {
                    w.props.deimage = consume_braced_string(l);
                } else {
                    w.props.deimage = consume_word(t);
                }
            }
            if (t.equals("value")) {
                t = l.next();
                if (t.type == Token::OpenBrace) {
                    w.props.value = consume_braced_string(l);
                } else {
                    w.props.value = consume_word(t);
                }
            }
            if (t.equals("set_size_tuples")) {
                l.next();
                std::string s = consume_braced_string(l);
                w.props.size_tuple = s;
            }
            if (t.equals("code0")) {
                l.next();
                std::string s = consume_braced_string(l);
                w.props.code0 = s;
            }
            if (t.equals("code1")) {
                l.next();
                std::string s = consume_braced_string(l);
                w.props.code1 = s;
            }
            if (t.equals("code2")) {
                l.next();
                std::string s = consume_braced_string(l);
                w.props.code2 = s;
            }
            if (t.equals("code3")) {
                l.next();
                std::string s = consume_braced_string(l);
                w.props.code3 = s;
            }
            if (t.equals("extra_code")) {
                l.next();
                std::string s = consume_braced_string(l);
                w.props.extra_code = s;
            }
            if (t.equals("callback")) {
                t = l.next();
                if (t.type == Token::OpenBrace) {
                    w.props.callback = consume_braced_string(l);
                } else {
                    w.props.callback = consume_word(t);
                }
            }
            if (t.equals("user_data")) {
                t = l.next();
                if (t.type == Token::OpenBrace) {
                    w.props.user_data = consume_braced_string(l);
                } else {
                    w.props.user_data = consume_word(t);
                }
            }
            if (t.equals("user_data_type")) {
                t = l.next();
                if (t.type == Token::OpenBrace) {
                    w.props.user_data_type = consume_braced_string(l);
                } else {
                    w.props.user_data_type = consume_word(t);
                }
            }
            if (t.equals("comment")) {
                t = l.next();
                if (t.type == Token::OpenBrace) {
                    w.props.comment = consume_braced_string(l);
                } else {
                    w.props.comment = consume_word(t);
                }
            }
        }
    }
    t = l.next();
    // We have children
    if (t.type == Token::OpenBrace) {
        int OpenBrace = 1;
        while (t.type != Token::Eof) {
            t = l.next();
            if (t.type == Token::OpenBrace)
                OpenBrace++;
            if (t.type == Token::CloseBrace)
                OpenBrace--;
            if (OpenBrace == 0)
                break;
            if (t.word)
                if (t.starts_with("Fl_") || t.equals("MenuItem")) {
                    auto c = consume_widget();
                    c.type = consume_word(t);
                    if (!w.children)
                        w.children = std::vector<Widget>{};
                    w.children->push_back(c);
                }
        }
    }
    return w;
}

Class Parser::consume_class() {
    Class c;
    auto t = l.next();
    if (t.type == Token::OpenBrace) {
        t = l.next();
        l.next();
    }
    c.name = consume_word(t);
    l.next();
    // handle props
    while (t.type != Token::Eof) {
        t = l.next();
        if (t.type == Token::CloseBrace)
            break;
        if (t.word) {
            if (t.equals("open"))
                c.props.open = true;
            if (t.equals("protected"))
                c.props.visibility = PROTECTED;
            if (t.equals("private"))
                c.props.visibility = PRIVATE;
            if (t.equals("comment")) {
                t = l.next();
                if (t.type == Token::OpenBrace) {
                    c.props.comment = consume_braced_string(l);
                } else {
                    c.props.comment = consume_word(t);
                }
            }
        }
    }
    t = l.next();
    if (t.type == Token::OpenBrace) {
        int OpenBrace = 1;
        while (t.type != Token::Eof) {
            t = l.next();
            if (t.type == Token::OpenBrace)
                OpenBrace++;
            if (t.type == Token::CloseBrace)
                OpenBrace--;
            if (OpenBrace == 0)
                break;
            if (t.word)
                if (t.equals("Function")) {
                    auto f = consume_func();
                    c.functions.push_back(f);
                }
        }
    }
    return c;
}

Function Parser::consume_func() {
    Function f;
    l.next();
    auto t = l.next();
    f.name = consume_word(t);
    l.next(); // closing parens of function name
    l.next(); // opening parens of props
    while (t.type != Token::Eof) {
        t = l.next();
        if (t.type == Token::CloseBrace)
            break;
        if (t.word) {
            if (t.equals("open"))
                f.props.open = true;
            if (t.equals("C"))
                f.props.C = true;
            if (t.equals("protected"))
                f.props.visibility = PROTECTED;
            if (t.equals("private"))
                f.props.visibility = PRIVATE;
            if (t.equals("comment")) {
                t = l.next();
                if (t.type == Token::OpenBrace) {
                    f.props.comment = consume_braced_string(l);
                } else {
                    f.props.comment = consume_word(t);
                }
            }
            if (t.equals("return_type")) {
                t = l.next();
                if (t.type == Token::OpenBrace) {
                    f.props.return_type = consume_braced_string(l);
                } else {
                    f.props.return_type = consume_word(t);
                }
            }
        }
    }
    t = l.next(); // close props parens
    if (t.type == Token::OpenBrace) {
        int OpenBrace = 1;
        while (t.type != Token::Eof) {
            t = l.next();
            if (t.type == Token::OpenBrace)
                OpenBrace++;
            if (t.type == Token::CloseBrace)
                OpenBrace--;
            if (OpenBrace == 0)
                break;
            if (t.word) {
                if (t.starts_with("Fl_") || t.equals("MenuItem")) {
                    auto w = consume_widget();
                    w.type = consume_word(t);
                    f.widgets.push_back(w);
                }
                if (t.equals("code")) {
                    l.next();
                    f.code = consume_code();
                }
            }
        }
    }
    return f;
}

Comment Parser::consume_comment() {
    Comment c;
    auto t = l.next();
    c.comment = consume_braced_string(l);
    while (t.type != Token::Eof) {
        t = l.next();
        if (t.type == Token::CloseBrace)
            break;
        if (t.word) {
            if (t.equals("in_source"))
                c.props.in_source = true;
            if (t.equals("in_header"))
                c.props.in_header = true;
        }
    }
    return c;
}

Decl Parser::consume_decl() {
    Decl d;
    auto t = l.next();
    d.decl = consume_braced_string(l);
    while (t.type != Token::Eof) {
        t = l.next();
        if (t.type == Token::CloseBrace)
            break;
        if (t.word) {
            if (t.equals("private"))
                d.props.visibility = PRIVATE;
            if (t.equals("public"))
                d.props.visibility = PUBLIC;
            if (t.equals("global"))
                d.props.global = true;
            if (t.equals("local"))
                d.props.local = true;
        }
    }
    return d;
}

Parser::Parser(Lexer lexer) : l(std::move(lexer)) {
}

Ast Parser::parse() {
    Ast a;
    Token t;
    while (t.type != Token::Eof) {
        t = l.next();
        if (t.type == Token::Eof)
            break;
        switch (t.type) {
        case Token::Eof:
            break;
        case Token::Word: {
            if (t.equals("version")) {
                a.version = strtod(l.next().word, 0);
            }
            if (t.equals("header_name")) {
                l.next();
                auto t = l.next();
                a.header_name = consume_word(t);
            }
            if (t.equals("code_name")) {
                l.next();
                auto t = l.next();
                a.code_name = consume_word(t);
            }
            if (t.equals("class")) {
                auto c = consume_class();
                a.classes.push_back(c);
            }
            if (t.equals("Function")) {
                auto f = consume_func();
                a.functions.push_back(f);
            }
            if (t.equals("comment")) {
                auto c = consume_comment();
                a.comments.push_back(c);
            }
            if (t.equals("decl")) {
                auto d = consume_decl();
                a.decls.push_back(d);
            }
        }
        default:
            continue;
        }
    }
    return a;
}