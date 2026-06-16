#ifndef MATERIAL_H
#define MATERIAL_H

#include <cstddef>
#include <string_view>
#include <vector>
#include <cctype>
#include <iostream>
#include <cstdlib>
#include <string>
#include <iterator>
#include <fstream>
#include <sstream>
#include <variant>

using Value = std::variant<long long,double,char,bool,std::string>;

enum class Tokentype {
    PLUS,MINUS,MUL,DIV,LPAREN,RPAREN,SEMICOLON,COLON,LBRACE,RBRACE,ASSIGN,COMMA,
    PRINT,TYPE_STR,TYPE_INT,TYPE_FLOAT,TYPE_BOOL,TYPE_CHAR,
    STR,INT,FLOAT,BOOL,CHAR,
    UNKNOWN,IDENTIFIER,
    END_OF_FILE
};

enum class JenisEsekusi {PRINT};

struct Token {
    Tokentype tipe;
    std::string_view nilai;
    std::size_t baris = 1;
    std::size_t kata_ke = 0;
};

struct kamus {
    Tokentype tipe_syntax;
    std::string_view syntax;
};

struct perintah {
    JenisEsekusi tipe;
    std::vector<Value> data;
};

const kamus kamus_syntax[] = {
{Tokentype::PRINT,"print"},
{Tokentype::TYPE_STR,"str"},
{Tokentype::TYPE_INT,"int"},
{Tokentype::TYPE_FLOAT,"float"},
{Tokentype::TYPE_BOOL,"bool"},
{Tokentype::TYPE_CHAR,"char"},
{Tokentype::BOOL,"true"},
{Tokentype::BOOL,"false"}
};

const std::size_t size_kamus = sizeof(kamus_syntax) / sizeof(kamus_syntax[0]);

#endif