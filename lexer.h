#ifndef LEXER_H
#define LEXER_H

#include "material.h"

class LEXER {
    private:
    std::string_view data;
    std::size_t posisi = 0 , baris = 1 , kata_ke = 0 ;

    public: 

    LEXER(std::string_view text) {
        data = text;
        posisi = 0;
        baris = 1;
        kata_ke = 0;
    }

    std::vector<Token> tokenise() {
        std::vector<Token> tokens;
        tokens.reserve(data.size() / 2);

        while (posisi < data.size()) {
            char current = data[posisi];

            switch (current) {
                case '+':
                kata_ke++;
                tokens.push_back({Tokentype::PLUS,data.substr(posisi,1),baris,kata_ke});
                posisi++;
                break;

                case '-':
                kata_ke++;
                tokens.push_back({Tokentype::MINUS,data.substr(posisi,1),baris,kata_ke});
                posisi++;
                break; 
                
                case '*':
                kata_ke++;
                tokens.push_back({Tokentype::MUL,data.substr(posisi,1),baris,kata_ke});
                posisi++;
                break;

                case '/':
                kata_ke++;
                tokens.push_back({Tokentype::DIV,data.substr(posisi,1),baris,kata_ke});
                posisi++;
                break;

                case '(':
                kata_ke++;
                tokens.push_back({Tokentype::LPAREN,data.substr(posisi,1),baris,kata_ke});
                posisi++;
                break;

                case ')':
                kata_ke++;
                tokens.push_back({Tokentype::RPAREN,data.substr(posisi,1),baris,kata_ke});
                posisi++;
                break;

                case ';':
                kata_ke++;
                tokens.push_back({Tokentype::SEMICOLON,data.substr(posisi,1),baris,kata_ke});
                posisi++;
                break;

                case ':': 
                kata_ke++;
                tokens.push_back({Tokentype::COLON,data.substr(posisi,1),baris,kata_ke});
                posisi++;
                break;

                case '{':
                kata_ke++;
                tokens.push_back({Tokentype::LBRACE,data.substr(posisi,1),baris,kata_ke});
                posisi++;
                break;

                case '}':
                kata_ke++;
                tokens.push_back({Tokentype::RBRACE,data.substr(posisi,1),baris,kata_ke});
                posisi++;
                break;

                case '=':
                kata_ke++;
                tokens.push_back({Tokentype::ASSIGN,data.substr(posisi,1),baris,kata_ke});
                posisi++;
                break;

                case ',':
                kata_ke++;
                tokens.push_back({Tokentype::COMMA,data.substr(posisi,1),baris,kata_ke});
                posisi++;
                break;

                case '"': {
                kata_ke++;
                posisi++;
                std::size_t start = posisi;
                while (posisi < data.size() && data[posisi] != '"') {
                    posisi++;
                }
                if (posisi >= data.size()) {
                    tokens.push_back({Tokentype::UNKNOWN,data.substr(start - 1, posisi - (start - 1)),baris,kata_ke});
                } else {
                    tokens.push_back({Tokentype::STR,data.substr(start, posisi - start),baris,kata_ke});
                }
                if (posisi < data.size()) posisi++;
                break;
                }

                case '\'':
                kata_ke++;
                if (posisi + 2 < data.size() && data[posisi + 2] == '\'') {
                    tokens.push_back({Tokentype::CHAR,data.substr(posisi + 1, 1),baris,kata_ke});
                    posisi += 3;
                    break;
                } else {
                    tokens.push_back({Tokentype::UNKNOWN,data.substr(posisi,1),baris,kata_ke});
                    posisi++;
                    break;
                }

                default:
                if (std::isspace(static_cast<unsigned char>(current))) {
                    if (current == '\n') {
                        baris++;
                    }
                    posisi++;
                    break;
                } else if (std::isdigit(static_cast<unsigned char>(current))) {
                    std::size_t start = posisi , titik = 0;
                    kata_ke++;

                    while (posisi < data.size()) {
                        char c = data[posisi];

                        if (std::isdigit(static_cast<unsigned char>(c))) {
                            posisi++;
                        } else if ( c == '.') {
                            titik++; posisi++;
                        } else {
                            break;
                        }
                    }

                    if (posisi < data.size() && (std::isalpha(static_cast<unsigned char>(data[posisi])) || data[posisi] == '_')) {
                        while (posisi < data.size() && (std::isalnum(static_cast<unsigned char>(data[posisi])) || data[posisi] == '_')) {
                            posisi++;
                        }
                        std::string_view tempat_sementara = data.substr(start,posisi - start);
                        tokens.push_back({Tokentype::UNKNOWN,tempat_sementara,baris,kata_ke});
                        break;
                    }

                    std::string_view tempat_sementara = data.substr(start,posisi - start);
                    if (titik == 0) {
                        tokens.push_back({Tokentype::INT,tempat_sementara,baris,kata_ke});
                    } else if (titik == 1) {
                        if (tempat_sementara[tempat_sementara.size() - 1] == '.') {
                            tokens.push_back({Tokentype::UNKNOWN,tempat_sementara,baris,kata_ke});
                        } else {
                            tokens.push_back({Tokentype::FLOAT,tempat_sementara,baris,kata_ke});
                        }
                    } else {
                        tokens.push_back({Tokentype::UNKNOWN,tempat_sementara,baris,kata_ke});
                    }
                    break;
                    
                } else if (std::isalpha(static_cast<unsigned char>(current)) || current == '_') {
                    kata_ke++;
                    std::size_t start = posisi;
                    while (posisi < data.size() && (std::isalnum(static_cast<unsigned char>(data[posisi])) || data[posisi] == '_')) { posisi++; }
                    std::string_view kata = data.substr(start,posisi - start);
                    Tokentype tipe_kata = Tokentype::UNKNOWN;
                    bool ketemu_kata = false;

                    for (std::size_t i = 0; i < size_kamus; i++) {
                        if (kata == kamus_syntax[i].syntax) {
                            tipe_kata = kamus_syntax[i].tipe_syntax;
                            ketemu_kata = true;
                            break;
                        }
                    }
                    if (!ketemu_kata) {
                        tipe_kata = Tokentype::IDENTIFIER;
                    }
                    tokens.push_back({tipe_kata,kata,baris,kata_ke});
                    break;
                    
                } else {
                    kata_ke++;
                    tokens.push_back({Tokentype::UNKNOWN,data.substr(posisi,1),baris,kata_ke});
                    posisi++;
                    break;
                }
            }
        }

        tokens.push_back({Tokentype::END_OF_FILE,"",baris,kata_ke});
        return tokens;
    }

};

#endif