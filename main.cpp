#include "lexer.h"
#include "parser.h"

std::string baca_isi_file(const std::string& nama_file) {
    std::ifstream file(nama_file);
    if (!file.is_open()) {
        std::cerr << "ERROR : File " << nama_file << " tidak dapat dibuka atau tidak ada!" << std::endl;
        return "";
    }
    std::stringstream wadah;
    wadah << file.rdbuf();
    return wadah.str();
}


int main(int argc,char* argv[]) {
    std::string nama_file;

    if (argc < 2) {
        std::cerr << "Cara Penggunaan : " << argv[0] << " <nama_file.psh> " << std::endl;
        return 1;
    }
    nama_file = argv[1];
    if (nama_file.length() < 4 || nama_file.substr(nama_file.length() - 4) != ".psh") {
        std::cerr << "ERROR: File tidak cocok! Bahasa ini hanya mendukung file dengan ekstensi '.psh'" << std::endl;
        return 1;
    }
    std::string kode_psh = baca_isi_file(nama_file);
    if (kode_psh.empty()) {std::cerr << "file tidak berisi code apapun !" << std::endl; return 1;}
    LEXER lexer(kode_psh);
    std::vector<Token> tokens = lexer.tokenise();
    PARSER parser(tokens);
    if (parser.scan_code()) {
        parser.execute();
    }
    return 0;
}