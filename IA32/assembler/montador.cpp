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
#define S_ADD "add"
#define S_SUB "sub"
#define S_MUL "mult"
#define S_DIV "div"
#define S_JMP "jmp"
#define S_JMPN "jmpn"
#define S_JMPP "jmpp"
#define S_JMPZ "jmpz"
#define S_COPY "copy"
#define S_LOAD "load"
#define S_STORE "store"
#define S_INPUT "input"
#define S_OUTPUT "output"
#define S_STOP "stop"

// Limites
#define S_TAM 3
#define MACROS_NUMAX 2 // N maximo de macros
#define MACROS_LINEMAX 10 // Max linhas por macro
#define MACROS_NARGS 3 // Max args por macro

// Tabelas
map<string, int> instructions = {{S_ADD, 1}, {S_SUB, 2}, {S_MUL, 3}, {S_DIV, 4}, {S_JMP, 5}, {S_JMPN, 6},
{S_JMPP, 7}, {S_JMPZ, 8}, {S_COPY, 9}, {S_LOAD, 10}, {S_STORE, 11}, {S_INPUT, 12}, {S_OUTPUT, 13}, {S_STOP, 14}};
map<string, int> diretives = {{D_SECTION, 0}, {D_TEXT, 0}, {D_DATA, 0}, {D_SPACE, 0}, {D_CONST, 0},
{D_EQU, 0}, {D_IF, 0}};
map<string, int> symbtab;
map<string, string> symbequ;
map<string, int> mnt; // Macro name table
string mdt[MACROS_NUMAX][MACROS_LINEMAX][S_TAM]; // Macro definition table
// Funcionamento: mdt[numero da macro][linha][campos da linha]
string mat[MACROS_NUMAX][MACROS_NARGS]; // Macro arg table
// Functionamento: mat[numero da macro][arg da macro]

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

void Verify(string linha[S_TAM], int* memcounter, int linecounter, bool error){
    bool isinstr = false; bool isdir = false;
    string label = linha[0]; // label
    string str = linha[1]; // instrucao
    string arg = linha[2]; // argumentos
    string arg1; string arg2;

    if(str.empty()){ // Vetor vazio
        if(!label.empty()){
            label.erase(remove(label.begin(), label.end(), ':'), label.end()); // Tira : do label
            // Tabela de símbolos
            symbtab.insert({label, *memcounter});
            return;
        }
        else { return; }
    }
    if(error) { cout << E_LINE << linecounter << E_SIN_ARGS << str << endl; return; }
    if(str == D_SECTION && linha[2] != D_TEXT && linha[2] != D_DATA ){ // Diretiva invalida
        cout << E_LINE << linecounter << E_SIN_SECTION << endl;
        return;
    }
    if(instructions.find(str) != instructions.end()) { isinstr = true; }
    if(diretives.find(str) != diretives.end()) { isdir = true; }
    if(!isinstr && !isdir){ cout << E_LINE << linecounter << E_SIN_INSTR << endl; return; }
    // Instrucao ou Diretiva invalida

    if(Search_char(arg, '+')){
        arg1 = Separator_Part1(arg, '+');
        arg2 = Separator_Part2(arg, '+');
        arg1 = Formatting_var(arg, &error);
        arg2 = Formatting_var(arg, &error);
    }
    if(Search_char(arg, '-')){
        arg1 = Separator_Part1(arg, '-');
        arg2 = Separator_Part2(arg, '-');
        arg1 = Formatting_var(arg, &error);
        arg2 = Formatting_var(arg, &error);
    }
    else { arg = Formatting_var(arg, &error); }
    if(error == true){
        cout << E_LINE << linecounter << E_LEXIC << endl; // Rotulo ou variavel no formato errado
        return;
    }
    if(str != D_SECTION){
        if(!label.empty()){
            label.erase(remove(label.begin(), label.end(), ':'), label.end()); // Tira : do label
            // Tabela de símbolos
            symbtab.insert({label, *memcounter});
        }
        if(instructions.find(str) != instructions.end()){
            // Contador de instruções
            if(str == S_COPY){ *memcounter += 3; }
            else if(str == S_STOP){ *memcounter += 1; }
            else{ *memcounter += 2; }
        }
        if(str == D_SPACE || str == D_CONST){ *memcounter += 1; }
    }
    return;
}

void Macro_resolve(string linha[S_TAM], bool* inmacro, int* macro_line, int* macro_counter){
    string label = linha[0]; // label
    string str = linha[1]; // instrucao
    string arg = linha[2]; string arg1; string arg2;
    string marg[3]; string aux;
    map<string, string> called_stored; // Map pra pegar os args chamados e puxar da macro guardada
    bool args = false;
    int margs = 0; int macro_number = 0;

    if(str.empty()){ return; } // Vetor vazio
    if(str == D_MACRO) {
        margs = 0; // Contador de macro args
        label.erase(remove(label.begin(), label.end(), ':'), label.end()); // Tira : do label
        mnt.insert({label, *macro_counter}); // Coloca macro na MNT com seu numero
        macro_number = mnt[label];
        // Se tem args, pega cada um e bota na MAT da Macro definida em MNT
        for(auto c : arg){ // Pega args sem espaço
            if(c == ',' && aux[0] == '&') { marg[margs] = aux; aux.erase(); margs++; } else { aux.push_back(c); }
        }
        if(!aux.empty()) { marg[margs] = aux; margs++; aux.erase(); } // Último arg
        for(int n_arg = 0; n_arg < MACROS_NARGS; n_arg++){ // Coloca cada arg na MAT
            if(!marg[n_arg].empty()) { mat[macro_number][n_arg] = marg[n_arg]; }
        }
        *inmacro = true;
        *macro_line = 0;
        return;
    }
    if(*inmacro) { 
        if(str == D_ENDMACRO ) { mdt[*macro_counter][*macro_line][0] = D_ENDMACRO; *inmacro = false; *macro_counter += 1; return; }
        for(int i = 0; i < 3; i++){ mdt[*macro_counter][*macro_line][i] = linha[i]; }
        *macro_line += 1;
        return; 
    }
    if(mnt.find(str) != mnt.end() && *inmacro == false){
        macro_number = mnt[str]; // Recupera o numero da macro na MNT

        if(!arg.empty()) { // Chamou macro com arg.
            for(auto c : arg){ // Pega args sem espaço
                if(c == ',') { marg[margs] = aux; aux.erase(); margs++; } else { aux.push_back(c); }
            }
            if(!aux.empty()) { marg[margs] = aux; margs++; aux.erase(); }
            for(int n_arg = 0; n_arg < MACROS_NARGS; n_arg++){ // Coloca cada arg na MAT
                // Associa cada arg chamado com o arg correspondente que foi guardado.
                if(!marg[n_arg].empty()) { called_stored.insert({mat[macro_number][n_arg], marg[n_arg]}); }
            }
        }

        for(int line = 0; line < MACROS_LINEMAX; line++){ // Percorre a macro linha a linha
            if(mdt[macro_number][line][0] == D_ENDMACRO) { break; } // Se o primeiro campo do vetor é fim, então sai
            for(int instr_field = 0 ; instr_field < S_TAM; instr_field++){ // Percorre a linha atual campo a campo (o vetor)
                args = false; // Atualiza var
                /*
                if(mnt.find(mdt[macro_number][line][1]) != mnt.end()){ // Achou macro dentro de macro
                    cout << "Encontrado macro em macro" << endl;
                    string newline[3]; int tmp;
                    newline[0] = mdt[macro_number][line][0];
                    newline[1] = mdt[macro_number][line][1];
                    newline[2] = mdt[macro_number][line][2];
                    tmp = *macro_counter;
                    *macro_counter = mnt[newline[1]];
                    Macro_resolve(newline, inmacro, macro_line, macro_counter);
                    *macro_counter = tmp;
                    break;
                }*/
                if(mdt[macro_number][line][instr_field] == S_COPY){
                    oFile << mdt[macro_number][line][instr_field] << " "; // Coloca o copy
                    arg1 = Separator_Part1(mdt[macro_number][line][2], ','); // Pegando os args do copy guardado na macro
                    arg2 = Separator_Part2(mdt[macro_number][line][2], ',');
                    // Substituindo os args se eles forem encontrados
                    if(called_stored.find(arg1) != called_stored.end()) { aux = called_stored[arg1]+","; }
                    else{ aux = arg1+","; }

                    if(called_stored.find(arg2) != called_stored.end()){ aux += called_stored[arg2]; }
                    else{ aux += arg2; }
                    oFile << aux << " "; break; // Próxima linha
                }
                if(mdt[macro_number][line][instr_field] == S_STOP){ oFile << S_STOP << " "; break; }
                if(called_stored.find(mdt[macro_number][line][instr_field]) != called_stored.end()){
                    oFile << called_stored[mdt[macro_number][line][instr_field]] << " ";
                    args = true;
                    break;
                }
                // Para a linha atual, coloca no arquivo .mcr cada campo do vetor
                if(!args && !mdt[macro_number][line][instr_field].empty()){ oFile << mdt[macro_number][line][instr_field] << " "; } // Se não tem args iguais, só coloca o que tiver
            }
            // Terminou a linha, vai pra próxima linha
            oFile << endl; 
        }
        return;
    }
    for(int i=0 ; i < 3; i++){
        if(!linha[i].empty()){ 
            oFile << linha[i] << " "; 
        }
    }
    oFile << endl; 
}

void Translate(string linha[S_TAM], int linecounter){
    string buffer[3]; // 3 colunas, código escrito de 3 em 3.
    string label = linha[0]; // label
    string str = linha[1]; // instrucao
    string arg = linha[2]; // argumentos
    string arg1; string arg2; // Args do copy

    //faz a soma final
    if(Search_char(arg, '+')){
        arg1 = Separator_Part1(arg, '+');
        arg2 = Separator_Part2(arg, '+');
        if(symbtab.find(arg1) != symbtab.end()){
            if(symbtab.find(arg2) != symbtab.end()){ arg = to_string(symbtab[arg1] + symbtab[arg2]); }
            else { arg = to_string(symbtab[arg1] + stoi(arg2)); }
        }
        symbtab.insert({"aux", stoi(arg)});
        arg = "aux";
    }
    //faz a subtracao final
    if(Search_char(arg, '-')){
        arg1 = Separator_Part1(arg, '-');
        arg2 = Separator_Part2(arg, '-');
        if(symbtab.find(arg1) != symbtab.end()){
            if(symbtab.find(arg2) != symbtab.end()){ arg = to_string(symbtab[arg1] - symbtab[arg2]); }
            else { arg = to_string(symbtab[arg1] - stoi(arg2)); }
        }
        symbtab.insert({"aux", stoi(arg)});
        arg = "aux";
    }

    if(str.empty()){ return; } // Vetor vazio
    if(diretives.find(str) != diretives.end()){
        if(str == D_CONST){
            if(arg.empty()){
                cout << E_LINE << linecounter << E_SIN_CONST << endl;
                return;
            }
            else{
                arg = Hex_to_int(arg);
                buffer[0] = arg;
                oFile << buffer[0] << " ";
            }
        }
        if(str == D_SPACE){
            buffer[0] = to_string(diretives[D_SPACE]);
            for(int i=0; i<1; i++){
                oFile << buffer[0] << " ";
                cout << buffer[0] << " ";
            }
        }

    }
    if(instructions.find(str) != instructions.end()){
        if(symbtab.find(arg) == symbtab.end() && str != S_STOP && str != S_COPY){
            if(str == S_JMP || str == S_JMPN || str == S_JMPP || str == S_JMPZ){
                cout << E_LINE << linecounter << E_SEM_LABEL << arg << endl;
            }else{
                cout << E_LINE << linecounter << E_SEM_VAR << arg << endl;
            }
            return;
        }
        if(str == S_STOP){
            buffer[0] = to_string(instructions[str]);
            oFile << buffer[0] << " ";
        }
        if(str == S_COPY){
            if(!linha[3].empty()) { cout << E_LINE << linecounter << E_SIN_ARGS << str << endl; return; }
            arg1 = Separator_Part1(arg, ',');
            arg2 = Separator_Part2(arg, ',');
            if(symbtab.find(arg1) == symbtab.end()){
                cout << E_LINE << linecounter << E_SEM_VAR << arg1 << endl;
                return;
            }
            if(symbtab.find(arg2) == symbtab.end()){
                cout << E_LINE << linecounter << E_SEM_VAR << arg2 << endl;
                return;
            }
            buffer[0] = to_string(instructions[str]);
            buffer[1] = to_string(symbtab[arg1]);
            buffer[2] = to_string(symbtab[arg2]);
            oFile << buffer[0] << " " << buffer[1] << " " << buffer[2] << " ";
        }
        if(str != S_COPY && str != S_STOP){
            buffer[0] = to_string(instructions[str]);
            buffer[1] = to_string(symbtab[arg]);
            oFile << buffer[0] << " " << buffer[1] << " ";
        }
    }
    if(str == D_CONST){
        cout << buffer[0] << " ";
    }
    if(instructions.find(str) != instructions.end()){
        if(str == S_STOP){
            cout << buffer[0] << " ";
        }
        else if(str == S_COPY){
            cout << buffer[0] << " " << buffer[1] << " " << buffer[2] << " ";
        }
        else{
            cout << buffer[0] << " " << buffer[1] << " ";
        }
    }
    return;
}

void Scan(int op, int out, int in, string file, bool* success){
    string str; string linha[6]; string ifile; string ofile;
    char c = 'a';
    int linecounter = 0; int cont = 1; int memcounter = 0;
    bool error = false; bool in_if = true;
    bool section_text = false; bool section_data = false;
    bool inmacro = false; int macro_line = 0; int macro_counter = 0;

    if(in == 0) { ifile = file + ".asm"; }
    if(in == 1) { ifile = file + ".pre"; }
    if(in == 2) { ifile = file + ".mcr"; }
    if(out == 0) { ofile = file + ".pre"; }
    if(out == 1) { ofile = file + ".mcr"; }
    if(out == 2) { ofile = file + ".obj"; }

    iFile.open(ifile);
    if(!iFile.is_open()){
        cout << "Não foi possível abrir o arquivo " << ifile << endl;
        return;
    }

    oFile.open(ofile);
    if(!oFile.is_open()){
        cout << "Não foi possível criar o arquivo" << ofile << endl;
        return;
    }

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
                if(op == 1) { Verify(linha, &memcounter, linecounter, error); } // Passagem 1
                if(op == 2) { Translate(linha, linecounter); } // Passagem 2
                if(op == 3) { Macro_resolve(linha, &inmacro, &macro_line, &macro_counter); }
                //Print_vect(linha); cout << endl;
                if(linha[1] == D_SECTION){
                    if(linha[2] == D_TEXT){ section_text = true; }
                    if(linha[2] == D_DATA){ if(section_text == true){ section_data = true; } }
                }
                Erase_vect(linha);
                str.erase();
                error = false;
                continue;
            }
            str.erase();
            cont++;
            continue;
        }
        if(str.size() < 200 && c != ' ' && c!= '\n'){ str.push_back(c); }
    }
    if(section_text == false){ cout << E_SIN_DATA << endl; error = true; }
    if(section_data == false){ cout << E_SIN_DATA << endl; error = true; }
    iFile.close();
    oFile.close();
    if(!*success) { cout << "Erros foram encontrados, arquivo de saída incorreto.\n"; }
}

int main(int argc, char** argv){
    bool Pre = false; bool Mac = false; bool Out = false; // Var pros 3 modos de operação P, M e O.
    bool success = true;
    string file;
    int args_qtd = 0;
    if(argc > 3) { cout << "Número de argumentos inválido." << endl; return 1; }
    for(int i = 1; i < argc; ++i){ //Varre os argumentos e decide o que fazer quando tem cada um.
        if(strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "-P") == 0) { Pre = true; args_qtd++; }
        else if(strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "-M") == 0) { Mac = true; args_qtd++; }
        else if(strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "-O") == 0) { Out = true; args_qtd++; }
        else{
            if((Pre || Mac || Out) == false){ cout << "Uso: -op nome do arquivo" << endl; return 1; }
        }
    }
    if(argc < 3) { cout << "Entrada errada -> nome.exe -op arquivo_entrada" << endl; return 1; }
    if(args_qtd > 1) { cout << "Número de argumentos (-o -p -m) maior que 1." << endl; return 1; }
    file = string(argv[2]);
    if(file.find(".") != string::npos) { cout << "Indique o nome do arquivo sem a extensão." << endl; return 1; }
    cout << "Arquivo de entrada: " << file << endl;
    if(Pre == true) { Scan(0, 0, 0, file, &success); }
    if(Mac == true) { Scan(3, 1, 1, file, &success); }
    if(Out == true) { Scan(1, 2, 2, file, &success); Scan(2, 2, 2, file, &success); }
    return 0;
}
