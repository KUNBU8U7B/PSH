#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "material.h"
#include <string>

int uji_lexer() {
    std::string input = R"(
    int x = 10
    int y = 20
    float z = 30.5
    float w = 0.75

    str nama = "Budi Santoso"
    str kosong = ""
    char opsi = 'Y'
    char escape = 'X'
    bool kondisi1 = benar
    bool kondisi2 = salah

    print(x)
    print(x + y)
    print(z * w - x / y)

    {
        int temp = x
        x = y
        y = temp
    }

    int a, b, c
    a = 1
    b = 2
    c = 3

    print(a:b:c)

    int hasil=a+b*c(x-y)
    str gabung="Teks A"+"Teks B"

    999999
    0.00001
    .5
    5.
    12.34.56
    78.90__22
    123a
    _id123
    a_b_c_1_2_3

    "string tunggal
    "string dengan petik 'di dalam'"
    'abc'
    ''
    'a

    ++++----****////(((())))====::::;;;;,,,,{{}}
    x+y-z*w/a(b){c}=d:e;f,g
    )" ;
    LEXER lexer(input);
    std::vector<Token> tokens = lexer.tokenise();

    for (const auto& token : tokens) {
        std::cout << "Token: " << token.nilai ;
        switch (token.tipe) {
            case Tokentype::PLUS: std::cout << " : PLUS "; break;
            case Tokentype::MINUS: std::cout << " : MINUS "; break;
            case Tokentype::MUL: std::cout << " : MUL "; break;
            case Tokentype::DIV: std::cout << " : DIV "; break;
            case Tokentype::LPAREN: std::cout << " : LPAREN "; break;
            case Tokentype::RPAREN: std::cout << " : RPAREN "; break;
            case Tokentype::SEMICOLON: std::cout << " : SEMICOLON "; break;
            case Tokentype::COLON: std::cout << " : COLON "; break;
            case Tokentype::LBRACE: std::cout << " : LBRACE "; break;
            case Tokentype::RBRACE: std::cout << " : RBRACE "; break;
            case Tokentype::ASSIGN: std::cout << " : ASSIGN "; break;
            case Tokentype::COMMA: std::cout << " : COMMA "; break;
            case Tokentype::STR: std::cout << " : STR "; break;
            case Tokentype::CHAR: std::cout << " : CHAR "; break;
            case Tokentype::INT: std::cout << " : INT "; break;
            case Tokentype::FLOAT: std::cout << " : FLOAT "; break;
            case Tokentype::BOOL: std::cout << " : BOOL "; break;
            case Tokentype::UNKNOWN: std::cout << " : UNKNOWN "; break;
            case Tokentype::IDENTIFIER: std::cout << " : IDENTIFIER "; break;
            case Tokentype::END_OF_FILE: std::cout << " : END_OF_FILE "; break;
            case Tokentype::PRINT: std::cout << " : PRINT "; break;
            case Tokentype::TYPE_STR: std::cout << " : TYPE_STR "; break;
            case Tokentype::TYPE_INT: std::cout << " : TYPE_INT "; break;
            case Tokentype::TYPE_FLOAT: std::cout << " : TYPE_FLOAT "; break;
            case Tokentype::TYPE_BOOL: std::cout << " : TYPE_BOOL "; break;
            case Tokentype::TYPE_CHAR: std::cout << " : TYPE_CHAR "; break;
        }
        std::cout << std::endl;
    }
    return 0;
}

int uji_parser() {
    std::string input = R"(print("Hello, World!,\n this is a test of the PSH parser.", 123, 45.67, true, false, 'A');
    )";
    LEXER lexer(input);
    std::vector<Token> tokens = lexer.tokenise();
    PARSER parser(tokens);
    if (!parser.scan_code()) {
        std::cout << std::endl;
    } else {
        parser.execute();
    }
    return 0;
}

int main() {
    //uji_lexer();
    uji_parser();
    return 0;
}