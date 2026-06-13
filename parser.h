#ifndef PARSER_H
#define PARSER_H

#include "material.h"

class PARSER {
    private:
    std::vector<Token> tokens;
    std::size_t posisi = 0;
    std::vector<perintah> antrian_perintah;

    Token saat_ini() {
        if (posisi < tokens.size()) {
            return tokens[posisi];
        } else if (tokens.empty()) {
            return {Tokentype::END_OF_FILE,"",1,0};
        }
        return {Tokentype::END_OF_FILE,"",tokens.back().baris,tokens.back().kata_ke};
    }

    void maju() {
        if (posisi < tokens.size()) { posisi++; }
    }

    bool temukan(Tokentype label_data) {
        if (saat_ini().tipe == label_data) { maju(); return true; }
        return false;
    }

    bool parser_print() {
        if (!temukan(Tokentype::LPAREN)) {
            std::cout << "ERROR : [ line : " << saat_ini().baris << " Kata ke : " << saat_ini().kata_ke << " ] : Setelah print wajib ada '(' !" << std::endl;
            return false;
        }
        std::vector<std::string_view> data_print;
        while (true) {
            Token konten = saat_ini();
            if (konten.tipe == Tokentype::STR || konten.tipe == Tokentype::INT || konten.tipe == Tokentype::FLOAT || konten.tipe == Tokentype::CHAR || konten.tipe == Tokentype::BOOL ) {
                data_print.push_back(konten.nilai);
                maju();
            } else {
                std::cout << "ERROR : [ line : " << saat_ini().baris << " Kata ke : " << saat_ini().kata_ke << " ] : Data yang ingin ditampilkan tidak valid !" << std::endl;
                return false;
            }

            if (temukan(Tokentype::COMMA)) { continue; } else { break; }
        }
        if (!temukan(Tokentype::RPAREN)) {
            std::cout << "ERROR : [ line : " << saat_ini().baris << " Kata ke : " << saat_ini().kata_ke << " ] : Setelah data yang ingin di tampilkan wajib ada ')' !" << std::endl;
            return false;
        }
        if (!temukan(Tokentype::SEMICOLON)) {
            std::cout << "ERROR : [ line : " << saat_ini().baris << " Kata ke : " << saat_ini().kata_ke << " ] : Setelah perintah berakhir wajib ada ';' !" << std::endl;
            return false;
        }

        antrian_perintah.push_back({JenisEsekusi::PRINT,data_print});
        return true;
    }

    void cetak_mentah(std::string_view data_cetak) {
        for (std::size_t count_char = 0 ; count_char < data_cetak.size(); count_char++) {
            if (data_cetak[count_char] == '\\' && count_char + 1 < data_cetak.size()) {
                count_char++;
                switch (data_cetak[count_char]) {
                    case 'n':  std::cout << '\n'; break;
                    case 't':  std::cout << '\t'; break;
                    case '\\': std::cout << '\\'; break;
                    case '"':  std::cout << '"';  break;
                    case '\'': std::cout << '\''; break;
                    case 'r':  std::cout << '\r'; break;
                    case 'a':  std::cout << '\a'; break;
                    case '0':  std::cout << '\0'; break;
                    case 'b':  std::cout << '\b'; break;
                    case 'f':  std::cout << '\f'; break;
                    case 'v':  std::cout << '\v'; break;

                    default:   std::cout << '\\' << data_cetak[count_char]; break;
                }
            } else {
                std::cout << data_cetak[count_char];
            }
        }
    }

    public:
    PARSER(std::vector<Token> data) {
        tokens = data;
        posisi = 0;
    }

    bool scan_code() {
        while (saat_ini().tipe != Tokentype::END_OF_FILE) {
            if (temukan(Tokentype::PRINT)) {
                if (!parser_print()) {
                    return false;
                }
            } else {
                std::cout << "ERROR : [ line : " << saat_ini().baris << " Kata ke : " << saat_ini().kata_ke << " ] : Perintah tidak di kenali oleh sistem !" << std::endl;
                return false;
            }
        }
        return true;
    }

    void execute() {
        for (std::size_t i = 0; i < antrian_perintah.size();i++ ) {
            if (antrian_perintah[i].tipe == JenisEsekusi::PRINT) {
                for (std::size_t j = 0; j < antrian_perintah[i].data.size(); j++ ) {
                    cetak_mentah(antrian_perintah[i].data[j]);
                }
                std::cout << std::endl;
            }
        }
    }
};

#endif