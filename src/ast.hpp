#pragma once

#include <optional>
#include <string>
#include <vector>

struct WidgetProps {
    std::optional<bool> open;
    std::string xywh;
    std::optional<std::string> label;
    std::optional<std::string> type;
    std::optional<bool> hide;
    std::optional<bool> deactivate;
    std::optional<bool> visible;
    std::optional<bool> resizable;
    std::optional<bool> hotspot;
    std::optional<bool> divider;
    std::optional<bool> selected;
    std::optional<unsigned int> color;
    std::optional<unsigned int> selection_color;
    std::optional<std::string> tooltip;
    std::optional<std::string> image;
    std::optional<std::string> deimage;
    std::optional<std::string> box;
    std::optional<std::string> down_box;
    std::optional<std::string> value;
    std::optional<std::string> labeltype;
    std::optional<int> labelfont;
    std::optional<int> labelsize;
    std::optional<unsigned int> labelcolor;
    std::optional<int> align;
    std::optional<int> when;
    std::optional<double> minimum;
    std::optional<double> maximum;
    std::optional<double> step;
    std::optional<double> slider_size;
    std::optional<double> size;
    std::optional<int> textfont;
    std::optional<int> textsize;
    std::optional<unsigned int> textcolor;
    std::optional<std::string> klass;
    std::optional<int> shortcut;
    std::optional<std::string> code0;
    std::optional<std::string> code1;
    std::optional<std::string> code2;
    std::optional<std::string> code3;
    std::optional<std::string> extra_code;
    std::optional<std::string> size_tuple;
    std::optional<int> gap;
    std::optional<std::string> user_data;
    std::optional<std::string> user_data_type;
    std::optional<std::string> callback;
    std::optional<std::string> comment;
};

struct Widget {
    std::string type;
    std::string name;
    WidgetProps props;
    std::vector<Widget> children;
};

enum Visibility {
    PUBLIC,
    PRIVATE,
    PROTECTED,
};

struct FunctionProps {
    std::optional<Visibility> visibility;
    std::optional<bool> open;
    std::optional<bool> C;
    std::optional<std::string> return_type;
    std::optional<std::string> comment;
};

struct Function {
    std::string name;
    FunctionProps props;
    std::vector<Widget> widgets;
    std::optional<std::string> code;
};

struct ClassProps {
    std::optional<Visibility> visibility;
    std::optional<bool> open;
    std::optional<std::string> comment;
};

struct Class {
    std::string name;
    ClassProps props;
    std::vector<Function> functions;
};

struct DeclProps {
    Visibility visibility;
    std::optional<bool> global;
    std::optional<bool> local;
};
struct Decl {
    std::string decl;
    DeclProps props;
};

struct CommentProps {
    std::optional<bool> in_source;
    std::optional<bool> in_header;
};

struct Comment {
    std::string comment;
    CommentProps props;
};

struct Ast {
    double version = 0.0;
    std::string header_name;
    std::string code_name;
    std::optional<bool> i18n_type;
    std::vector<Class> classes;
    std::vector<Function> functions;
    std::vector<Comment> comments;
    std::vector<Decl> decls;
    std::string json_string();
};
