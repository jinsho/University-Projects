/*
Alunos:
Luiz Felipe Almeida Silva - 18/0023098
Leandro Vilela Matthias - 19/0062860
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

// registrador padrão
#define REG "esi"

// Diretivas
#define D_SECTION "section"
#define D_TEXT "text"
#define D_DATA "data"
#define D_SPACE "space"
#define D_CONST "const"
#define D_EQU "equ"
#define D_IF "if"
#define D_MACRO "macro"
#define D_ENDMACRO "endmacro"

// Erros
#define E_LINE "Linha "
#define E_LEXIC ": Erro Léxico - Caractere especial/Número em Rótulo"

#define E_SEM_LABEL ": Erro Semântico - Rótulo não definido - "
#define E_SEM_VAR ": Erro Semântico - Dado não definido - "

#define E_SIN_DLABEL ": Erro Sintático - Dois rótulos na mesma linha"
#define E_SIN_ARGS ": Erro Sintático - Número de argumentos errado para a instrução "
#define E_SIN_INSTR ": Erro Sintático - Instrução ou Diretiva inexistente"
#define E_SIN_TEXT ": Erro Sintático - Diretiva TEXT não encontrada"
#define E_SIN_DATA ": Erro Sintático - Diretiva DATA não encontrada"
#define E_SIN_SECTION ": Erro Sintático - Diretivas section erradas e/ou não encontradas"
#define E_SIN_CONST ": Erro Sintático - Argumento faltante para diretiva CONST"

// Instruções
#define i_ADD "add"
#define o_ADD "add"
#define i_SUB "sub"
#define o_SUB "sub"
#define i_MUL "mult"
#define o_MUL "imul"
#define i_DIV "div"
#define o_DIV "idiv"
#define i_JMP "jmp"
#define o_JMP "jmp "
#define i_JMPN "jmpn"
#define o_JMPN "\tsub ebx,ebx\n" "\tcmp " REG ",ebx\n" "\tjb "
#define i_JMPP "jmpp"
#define o_JMPP "\tsub ebx,ebx\n" "\tcmp " REG ",ebx\n" "\tjg "
#define i_JMPZ "jmpz"
#define o_JMPZ "\tsub ebx,ebx\n" "\tcmp " REG ",ebx\n" "\tjz "
#define i_COPY "copy"
#define o_COPY "\tmov ebx,[n1]\n" "\t mov dword[n2],ebx\n"
#define i_LOAD "load"
#define o_LOAD "mov"
#define i_STORE "store"
#define o_STORE "mov"
#define i_INPUT "input"
#define o_INPUT "\tpush eax\n" "\tcall input"
#define i_OUTPUT "output"
#define o_OUTPUT "\tpush eax\n" "\tcall output"
#define i_INPUT_C "input_c"
#define o_INPUT_C "\tpush eax\n" "\tcall input_c"
#define i_OUTPUT_C "output_c"
#define o_OUTPUT_C "\tpush eax\n" "\tcall output_c"
#define i_INPUT_S "input_s"
#define o_INPUT_S "\tpush eax\n" "\tpush ebx\n" "\tcall input_s"
#define i_OUTPUT_S "output_s"
#define o_OUTPUT_S "\tpush eax\n" "\tpush ebx\n" "\tcall output_s"
#define i_STOP "stop"
#define o_STOP "\tmov eax,1\n""\tmov ebx,0\n""\tint 0x80"

// Limites
#define S_TAM 3

//Do arquivo IA32
#define SEC_BSS "section .bss\n"
#define SEC_DATA "section .data\n"
#define SEC_TEXT "section .text\n\tglobal _start\n_start:\n"

// BSS
#define DIR_RESD " resd "
#define DIR_RESB " resb "
// DATA
#define DIR_DD " dd "
#define DIR_DB " db "
// nome do arquivo de dados extras
#define ARQUIVO_DATA "functions.s"
//#define DIR_TIMES " times "

// Tabelas
map<string, string> instructions = {{i_ADD, o_ADD}, {i_SUB, o_SUB}, {i_MUL, o_MUL}, {i_DIV, o_DIV}, {i_JMP, o_JMP}, {i_JMPN, o_JMPN},
{i_JMPP, o_JMPP}, {i_JMPZ, o_JMPZ}, {i_COPY, o_COPY}, {i_LOAD, o_LOAD}, {i_STORE, o_STORE}, {i_INPUT, o_INPUT}, {i_OUTPUT, o_OUTPUT},
{i_STOP, o_STOP}, {i_INPUT_C, o_INPUT_C}, {i_OUTPUT_C, o_OUTPUT_C}, {i_INPUT_S, o_INPUT_S}, {i_OUTPUT_S, o_OUTPUT_S} };

map<string, int> diretives = {{D_SECTION, 0}, {D_TEXT, 0}, {D_DATA, 0}, {D_SPACE, 0}, {D_CONST, 0},
{D_EQU, 0}, {D_IF, 0}};

map<string, int> sec_bss;
map<string, string> sec_data;
map<string, string> symbequ;

// Variáveis Globais
ifstream iFile;
ofstream oFile;

void Print_vect(string linha[S_TAM]){
    for(int i=0 ; i < S_TAM; i++){
        cout << "[" << linha[i] << "]" << " ";
    }
}

void Preprocess(string line[S_TAM], bool* in_if){
    string label = line[0];
    string str = line[1];
    string arg = line[2];

    if(str == D_EQU){
        label.erase(remove(label.begin(), label.end(), ':'), label.end());
        symbequ.insert({label, arg}); return;
    }
    if(str == D_IF){ if(symbequ[arg] == "0"){ *in_if = false; return; } else { *in_if = true; return; } }
    if(*in_if == false) { *in_if = true; return; }
    if(*in_if == true) {
        for(int i=0 ; i < 3; i++){
            if(!line[i].empty()){
                if(symbequ.find(line[i]) != symbequ.end()) { line[i] = symbequ[line[i]]; }
                oFile << line[i] << " ";
            }
        }
        oFile << endl;
    }
}

void Erase_vect(string linha[6]){
    for(int i=0 ; i < 6; i++){
        linha[i] = "";
    }
}

bool Not_char(char c){ return !(c>='a' && c<='z'); }
bool Is_number(char c){ return (c>='0' && c<='9'); }
bool Full_number(string str){
    for(int i=0; i<str.length(); i++){ if(!Is_number(str[i])){ return false; } }
    return true;
}
string Hex_to_int(string hex_str){
    int decimal = 0;
    int cont = 0;

    if(hex_str[0]!='0' && hex_str[1]!='x'){ return hex_str; }
    for(int i=hex_str.length()-1; i > 1; --i){
        if(hex_str[i] >= '0' && hex_str[i] <= '9'){ decimal += int(hex_str[i]-48)*int(pow(16, cont)); }
        else if(hex_str[i] >= 'a' && hex_str[i] <= 'f'){ decimal += int(hex_str[i]-87)*int(pow(16, cont)); }
        else { return "0x"; }
        cont++;
    }
    return to_string(decimal);
}

bool Search_char(string word, char letter){
    for(auto c : word){ if(c == letter){ return true; }}
    return false;
}

string Separator_Part1(string word, char letter){
    string aux;
    for(auto c : word){
        if(c == letter) { return aux; }
        else{ aux.push_back(c); }
    }
    return "";
}

string Separator_Part2(string word, char letter){
    string aux;
    for(auto c : word){
        if(c == letter) { aux.erase(); }
        else{ aux.push_back(c); }
    }
    return aux;
}

string Formatting_var(string var, bool* error){
    if(var[0]=='0' && var[1]=='x'){ var = Hex_to_int(var); }
    else if(!Full_number(var)){ if(Not_char(var[0])){ *error = true; } }
    if(var == "0x") { *error = true; }
    return var;
}

void Get_data(string linha[S_TAM], bool* in_data){
    string label = linha[0]; // label
    string str = linha[1]; // instrucao
    string arg = linha[2]; // argumentos
    string arg1, arg2;
    bool two_args = false;
    int qtd = 0;

    if(str.empty()){ return; } // Vetor vazio
    if(*in_data == false) { return; }
    if(Search_char(arg, '+')){
        arg1 = Separator_Part1(arg, '+');
        arg2 = Separator_Part2(arg, '+');
        two_args = true;
    }
    if(Search_char(arg, '-')){
        arg1 = Separator_Part1(arg, '-');
        arg2 = "-" + Separator_Part2(arg, '-');
        two_args = true;
    }
    if(str == D_SPACE){
        if(!arg.empty() && !two_args){ qtd = stoi(arg); }
        else if(two_args){ qtd = stoi(arg1) + stoi(arg2); }
        else{ qtd = 1; }

        if(!label.empty()){
            label.erase(remove(label.begin(), label.end(), ':'), label.end()); // Tira : do label
            sec_bss.insert({label, qtd});
        }
    }

    if(str == D_CONST){
        if(!label.empty()){
            label.erase(remove(label.begin(), label.end(), ':'), label.end()); // Tira : do label
            sec_data.insert({label, arg});
        }
    }
    return;
}

void Asm_setup(){
    map<string, int>::iterator it;
    map<string, string>::iterator it2;
    string temp;

    if(!sec_bss.empty()){
        oFile << SEC_BSS;
        for(it = sec_bss.begin(); it != sec_bss.end(); it++){
            oFile << "\t" << it->first << DIR_RESD << it->second << endl;
        }
    }
    if(!sec_data.empty()){
        oFile << SEC_DATA;
        for(it2 = sec_data.begin(); it2 != sec_data.end(); it2++){
            temp = it2->second;
            if(temp[0] == '\''){
                oFile << "\t" << it2->first << DIR_DB << it2->second << endl;
            }else{
                oFile << "\t" << it2->first << DIR_DD << it2->second << endl;
            }
        }
    }
    oFile << SEC_TEXT;
}

void Translate(string linha[S_TAM], int linecounter){
    string label = linha[0]; // label
    string str = linha[1]; // instrucao
    string arg = linha[2]; // argumentos

    if(str.empty() && label.empty()){ return; } // Vetor vazio
    if(!label.empty()){
        if(diretives.find(str) == diretives.end()){ oFile << label << endl; }
    }
    if(instructions.find(str) != instructions.end()){
        if(str == i_STOP){
            oFile << instructions[str] << endl;
        }
        else if(str == i_INPUT || str == i_INPUT_C || str == i_OUTPUT_C ){
            oFile << "\tmov eax," << arg << endl << instructions[str] << endl;
        }
        else if(str == i_OUTPUT){
            oFile << "\tmov eax,[" << arg << "]\n" << instructions[str] << endl;
        }
        else if(str == i_INPUT_S || str == i_OUTPUT_S){
            oFile << "\tmov eax," << Separator_Part1(arg, ',') << endl;
            oFile << "\tmov ebx," << Separator_Part2(arg, ',') << endl;
            oFile << instructions[str] << endl;
        }
        else if(str == i_MUL){
            oFile << "\tmov eax," << REG << endl;
            oFile << "\t" << instructions[str] << " dword[" << arg << "]" << endl;
            oFile << "\tmov " << REG << ",eax" << endl;
        }
        else if(str == i_DIV){
            oFile << "\tmov eax," << REG << endl;
            oFile << "\tcdq" << endl;
            oFile << "\t" << instructions[str] << " dword[" << arg << "]" << endl;
            oFile << "\tmov " << REG << ",eax" << endl;
        }
        else if(str == i_COPY){
            oFile << "\tmov ebx,[" << Separator_Part1(arg, ',') << "]" << endl;
            oFile << "\tmov dword[" << Separator_Part2(arg, ',') << "],ebx" << endl;
        }
        else if(str == i_STORE){
            oFile << "\t" << instructions[str] << " dword[" << arg << "]," << REG << endl;
        }
        else if(str == i_JMP){
            oFile << "\t" << instructions[str] << arg << endl;
        }
        else if(str == i_JMPN || str == i_JMPZ || str == i_JMPP){
            oFile << instructions[str] << arg << endl;
        }
        else{
            oFile << "\t" << instructions[str] << " " << REG << ",[" << arg << "]" << endl;
        }
    }

}

void Scan(int op, int out, int in, string file, bool* success){
    string str; string linha[6]; string ifile; string ofile;
    char c = 'a';
    int linecounter = 0; int cont = 1; int memcounter = 0;
    bool error = false; bool in_if = true;
    bool section_text = false; bool section_data = false;


    if(in == 0) { ifile = file + ".asm"; }
    if(in == 2) { ifile = file + ".pre"; }
    if(out == 0) { ofile = file + ".pre"; }
    if(out == 2) { ofile = file + ".s"; }

    iFile.open(ifile);
    if(!iFile.is_open()){
        cout << "Não foi possível abrir o arquivo " << ifile << endl;
        return;
    }

    if(out != 1){
        oFile.open(ofile);
        if(!oFile.is_open()){
            cout << "Não foi possível criar o arquivo" << ofile << endl;
            return;
        }
    }

    if(op == 2) { Asm_setup(); }

    while(true){ // Percorre o arquivo caractere por caractere.
        c = iFile.get(); // Próximo caractere
        if(c == EOF){ break; } // Fim do arquivo
        if(c == ';') { while(c != '\n') { c = iFile.get(); }} // Remove comments
        if(c == ' ' || c == '\n' || c == ':'){
            transform(str.begin(), str.end(), str.begin(), ::tolower);
            if(c == ':'){
                if(!linha[0].empty()){
                    linecounter++;
                    cout << E_LINE << linecounter << E_SIN_DLABEL << endl;
                    error = true;
                }
                str.push_back(c); linha[0]=str; cont--;
            } // Label
            if(c == ' ' && str.empty()){ continue; } // Espaço inútil
            if(c == ' '){ if(cont < S_TAM) { linha[cont]= str; }else{ error = true; *success = false; } } // Argumento ou instrução
            if(c == '\n'){ // Fim da linha
                if(!str.empty()){
                    if(cont < S_TAM ) { linha[cont]= str; }else{ error = true; *success = false; }
                }
                cont=1;
                linecounter++;
                if(op == 0) { Preprocess(linha, &in_if); } // Passagem 0, sem check
                if(op == 1) { Get_data(linha, &section_data); } // Passagem 1
                if(op == 2) { Translate(linha, linecounter); } // Passagem 2
                //Print_vect(linha); cout << endl;
                if(linha[1] == D_SECTION){
                    if(linha[2] == D_TEXT){ section_text = true; }
                    if(linha[2] == D_DATA){ if(section_text == true){ section_data = true; } }
                }
                Erase_vect(linha);
                str.erase();
                error = false; // mds do ceu pq isso aqui existe?
                continue;
            }
            str.erase();
            cont++;
            continue;
        }
        if(str.size() < 200 && c != ' ' && c!= '\n'){ str.push_back(c); }
    }

    if(out == 2){
        ifstream arquivo_data;
        bool bss = false;
        bool data = false;
        arquivo_data.open(ARQUIVO_DATA);
        if(!arquivo_data.is_open()){
            cout << "Não foi possível abrir o arquivo data.s " << endl;
            error = true;
        }
        else{
            oFile << "\n\n\n" << endl;
            oFile << ";##########################################" << endl;
            oFile << ";#PARTE DEDICADA A FUNCOES E DADOS EXTRAS.#" << endl;
            oFile << ";##########################################" << endl;
            for (string i; getline(arquivo_data, i); ){
                oFile << i << endl;
            }
        }
    }

    if(section_text == false){ cout << E_SIN_DATA << endl; error = true; }
    if(section_data == false){ cout << E_SIN_DATA << endl; error = true; }
    iFile.close();
    if(out != 1) { oFile.close(); }
    if(!*success) { cout << "Erros foram encontrados, arquivo de saída incorreto.\n"; }
}

int main(int argc, char** argv){
    bool success = true;
    string file;
    if(argc > 2) { cout << "Número de argumentos inválido." << endl; return 1; }
    if(argc < 2) { cout << "Entrada errada -> nome.exe arquivo_entrada.asm" << endl; return 1; }
    file = string(argv[1]);
    if(file.find(".") != string::npos) { cout << "Indique o nome do arquivo sem a extensão." << endl; return 1; }
    cout << "Arquivo de entrada: " << file << endl;
    if(argc == 2) { Scan(0, 0, 0, file, &success); Scan(1, 1, 2, file, &success); Scan(2, 2, 2, file, &success); }
    return 0;
}
