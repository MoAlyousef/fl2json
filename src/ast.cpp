#include "ast.hpp"
#include "nlohmann/json_fwd.hpp"
#include <nlohmann/json.hpp>

template <typename>
constexpr bool is_optional = false;
template <typename T>
constexpr bool is_optional<std::optional<T>> = true;

template <class J, class T>
void optional_to_json(J &j, const char *name, const std::optional<T> &value) {
    if (value) {
        j[name] = *value;
    }
}

template <class J, class T>
void optional_from_json(const J &j, const char *name, std::optional<T> &value) {
    const auto it = j.find(name);
    if (it != j.end()) {
        value = it->template get<T>();
    } else {
        value = std::nullopt;
    }
}

template <typename T>
void extended_to_json(const char *key, nlohmann::json &j, const T &value) {
    if constexpr (is_optional<T>)
        optional_to_json(j, key, value);
    else
        j[key] = value;
}
template <typename T>
void extended_from_json(const char *key, const nlohmann::json &j, T &value) {
    if constexpr (is_optional<T>)
        optional_from_json(j, key, value);
    else
        j.at(key).get_to(value);
}

#define EXTEND_JSON_TO(v1) extended_to_json(#v1, nlohmann_json_j, nlohmann_json_t.v1);
#define EXTEND_JSON_FROM(v1) extended_from_json(#v1, nlohmann_json_j, nlohmann_json_t.v1);

#define NLOHMANN_JSONIFY_ALL_THINGS(Type, ...)                                                     \
    inline void to_json(nlohmann::json &nlohmann_json_j, const Type &nlohmann_json_t) {            \
        NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(EXTEND_JSON_TO, __VA_ARGS__))                     \
    }                                                                                              \
    inline void from_json(const nlohmann::json &nlohmann_json_j, Type &nlohmann_json_t) {          \
        NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(EXTEND_JSON_FROM, __VA_ARGS__))                   \
    }

NLOHMANN_JSONIFY_ALL_THINGS(WidgetProps, open, xywh, label, size_tuple, type, hide, deactivate,
                            resizable, visible, hotspot, divider, selected, color, selection_color,
                            tooltip, image, deimage, box, down_box, value, labeltype, labelfont,
                            labelsize, labelcolor, align, when, minimum, maximum, step, slider_size,
                            size, textfont, textsize, textcolor, klass, shortcut, code0, code1,
                            code2, code3, extra_code, gap, user_data, user_data_type, callback,
                            comment)

NLOHMANN_JSONIFY_ALL_THINGS(Widget, type, name, props, children)

NLOHMANN_JSON_SERIALIZE_ENUM(Visibility, {
                                             {PUBLIC, "public"},
                                             {PROTECTED, "protected"},
                                             {PRIVATE, "private"},
                                         })

NLOHMANN_JSONIFY_ALL_THINGS(FunctionProps, visibility, open, comment)

NLOHMANN_JSONIFY_ALL_THINGS(Function, name, props, widgets, code)

NLOHMANN_JSONIFY_ALL_THINGS(ClassProps, visibility, open, comment)

NLOHMANN_JSONIFY_ALL_THINGS(Class, name, props, functions)

NLOHMANN_JSONIFY_ALL_THINGS(CommentProps, in_source, in_header)

NLOHMANN_JSONIFY_ALL_THINGS(Comment, comment, props)

NLOHMANN_JSONIFY_ALL_THINGS(DeclProps, visibility, global, local)

NLOHMANN_JSONIFY_ALL_THINGS(Decl, decl, props)

NLOHMANN_JSONIFY_ALL_THINGS(Ast, version, header_name, code_name, classes, functions, comments,
                            decls)

std::string Ast::json_string() {
    nlohmann::json j = *this;
    return j.dump(2);
}