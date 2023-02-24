#include "lexer.hpp"
#include "parser.hpp"
#include "token.hpp"

int main(int argc, char **argv) try {
    char *s = nullptr;
    auto len = 0;
    if (argc == 2) {
        auto *f = fopen(argv[1], "r");
        if (f != nullptr) {
            fseek(f, 0, SEEK_END);
            len = ftell(f);
            fseek(f, 0, SEEK_SET);
            s = (char *)malloc(len + 1);
            if (s != nullptr) {
                fread(s, 1, len, f);
            }
            fclose(f);
        } else {
            return -1;
        }
    } else {
        return -1;
    }
    Lexer l(s, len);
    Parser p(l);
    auto a = p.parse();
    printf("%s\n", a.json_string().c_str());
    if (s != nullptr) {
        free(s);
    }
} catch (const std::exception &e) {
    (void)fprintf(stderr, "%s\n", e.what());
}