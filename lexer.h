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
                tokens.push_back({Tokentype::PLUS,std::string_view(&data[posisi],1),baris,kata_ke});
                posisi++;
                break;

                case '-':
                kata_ke++;
                tokens.push_back({Tokentype::MINUS,std::string_view(&data[posisi],1),baris,kata_ke});
                posisi++;
                break; 
                
                case '*':
                kata_ke++;
                tokens.push_back({Tokentype::MUL,std::string_view(&data[posisi],1),baris,kata_ke});
                posisi++;
                break;

                case '/':
                kata_ke++;
                tokens.push_back({Tokentype::DIV,std::string_view(&data[posisi],1),baris,kata_ke});
                posisi++;
                break;

                case '(':
                kata_ke++;
                tokens.push_back({Tokentype::LPAREN,std::string_view(&data[posisi],1),baris,kata_ke});
                posisi++;
                break;

                case ')':
                kata_ke++;
                tokens.push_back({Tokentype::RPAREN,std::string_view(&data[posisi],1),baris,kata_ke});
                posisi++;
                break;

                case ';':
                kata_ke++;
                tokens.push_back({Tokentype::SEMICOLON,std::string_view(&data[posisi],1),baris,kata_ke});
                posisi++;
                break;

                case ':': 
                kata_ke++;
                tokens.push_back({Tokentype::COLON,std::string_view(&data[posisi],1),baris,kata_ke});
                posisi++;
                break;

                case '{':
                kata_ke++;
                tokens.push_back({Tokentype::LBRACE,std::string_view(&data[posisi],1),baris,kata_ke});
                posisi++;
                break;

                case '}':
                kata_ke++;
                tokens.push_back({Tokentype::RBRACE,std::string_view(&data[posisi],1),baris,kata_ke});
                posisi++;
                break;

                case '=':
                kata_ke++;
                tokens.push_back({Tokentype::ASSIGN,std::string_view(&data[posisi],1),baris,kata_ke});
                posisi++;
                break;

                case ',':
                kata_ke++;
                tokens.push_back({Tokentype::COMMA,std::string_view(&data[posisi],1),baris,kata_ke});
                posisi++;
                break;

                case '"': {
                kata_ke++;
                std::size_t start_token = posisi;
                posisi++; // untuk melewati tanda '"'
                std::size_t start_konten = posisi;
                bool ditutup = false;

                while (posisi < data.size()) {
                    if (data[posisi] == '\"') {
                        ditutup = true;
                        break;
                    } else if (data[posisi] == '\\') {
                        posisi++;
                        if (posisi < data.size()) {posisi++;}
                    } else {
                        if (data[posisi] == '\n') baris++;
                        posisi++;
                    }
                }
                if (!ditutup) {
                    std::string_view str_error(&data[start_token],posisi - start_token );
                    tokens.push_back({Tokentype::UNKNOWN,str_error,baris,kata_ke});
                } else {
                    std::string_view str(&data[start_konten],posisi - start_konten);
                    tokens.push_back({Tokentype::STR,str,baris,kata_ke});
                    posisi++;
                }
                break;
                }

                case '\'': {
                kata_ke++;
                std::size_t start_token = posisi;
                posisi++;
                std::size_t start_konten = posisi;

                if (posisi < data.size() && data[posisi] == '\\') {
                    posisi++;
                    if (posisi < data.size()) {posisi++;}
                } else if (posisi < data.size() && data[posisi] != '\'') {
                    posisi++;
                }

                if (posisi < data.size() && data[posisi] == '\'') {
                    std::string_view char_psh(&data[start_konten], posisi - start_konten);
                    tokens.push_back({Tokentype::CHAR, char_psh, baris, kata_ke});
                    posisi++; // Lewati tanda '\'' penutup
                } else {
                    while (posisi < data.size() && data[posisi] != '\'' && data[posisi] != '\n') { posisi++; }
                    if (posisi < data.size() && data[posisi] == '\'') posisi++;
                    std::string_view view_error(&data[start_token], posisi - start_token);
                    tokens.push_back({Tokentype::UNKNOWN, view_error, baris, kata_ke});
                }
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
                        std::string_view tempat_sementara(&data[start],posisi - start);
                        tokens.push_back({Tokentype::UNKNOWN,tempat_sementara,baris,kata_ke});
                        break;
                    }

                    std::string_view tempat_sementara(&data[start],posisi - start);
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
                    std::string_view kata(&data[start],posisi - start);
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
                    tokens.push_back({Tokentype::UNKNOWN,std::string_view(&data[posisi],1),baris,kata_ke});
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