#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include "lexical_analyzer.h"
using namespace std;

stack <Node*> stackOfTreeNodes;
string className = "";
string source = "";
string tokenText = "";
string fileContent;
int position;
string file = "/Users/tiffanydevlindrye/CLionProjects/COP4020/tiny_25";
ofstream outputFile;
string outputFileString;

class Token{

public:
    string T_class;
    string T_text;
    int T_source;

    Token(){
        T_class = "";
        T_text = "";
        T_source = -1;
    }
    Token(string passed_class, string passed_text, int passed_source){
        T_class = passed_class;
        T_text = passed_text;
        T_source = passed_source;
    }
};

bool isIdentifier(string s){

    //Any sequence of characters which may contain alphabets,
    //digits from 0 to 9 or an underscore. The sequence must
    //start with an alphabet or an underscore.

    if(isalpha(s[0]) || s[0] == '_') {

        for (int i = 1; i < s.size(); i++) {

            if (isalpha(s[i]) || isnumber(s[i]) || s[i] == '_') {
                continue;
            } else
                return false;
        }
        return true;
    }
    else
    return false;
}

bool isInt(string s){

    //A sequence of characters which may contain any combination of digits from 0 to 9.

    for (char i : s) {

        if (isnumber(i)) {
            continue;
        } else
            return false;
    }
    return true;
}

bool isWhiteSpace(string s){

    //Any sequence of characters containing any combination of
    //single space, form feed, horizontal tab and vertical tab.

    for (int i = 0; i < s.size(); i++) {

        if (s[i] == ' ' || s[i] == '\f' || s[i] == '\t' || s[i] == '\v') {
            continue;
        } else
            return false;
    }
    return true;

}

bool isChar(string s){

    //A sequence of three characters which contains a single character
    //between two single quotes. The single character between the two
    //quotes can be any character except a single quote itself.
    //For example, ‘’’ is an invalid character.

    if (s.size() != 3 || (s[0]!= '\'') || (s[1]== '\'') || (s[2]!= '\'')){
        return false;
    }

    else{
        return true;
    }


}

bool isString(string s){

    //A sequence of characters which contains any number of characters
    //between two double quotes. The character sequence between the two
    //double quotes can be any character except a double quote itself.
    //For example, “Hello”how” is an invalid string.

    if (s.size() < 2 || s[0]!= '\"' || s[s.size()-1]!= '\"'){
        return false;
    }

    else{
        for (int i = 1; i < s.size()-1; i++) {

            if (s[i] != '\"') {
                continue;
            } else
                return false;
        }
    }
    return true;

}

bool isComment(string s){

    //Type 1: a sequence of characters which starts with # and ends with
    //a newline.  Type2: begins with ‘{‘, continues with any character
    //(including end-of-line),  and ends with ‘}’.

    if(s[0] == '#' && s[s.size()-1] == '\n'){
        for (int i = 1; i < s.size()-1; i++) {

            if (s[i] != '\n') {
                continue;
            } else
                return false;
        }
        return true;
    }
    else if(s[0] == '{' && s[s.size()-1] == '}'){
        return true;
    }
    else{
        return false;
    }
}

bool isKeyword(string s){

    if (s == "\\n"      || s == "program" || s == "var"      || s == "const" || s == "type" || s == "function"
        || s == "return"|| s == "begin"   || s == "end"      || s == ":=:"   || s == ":="   || s == "output"
        || s == "if"    || s == "then"    || s == "else"     || s == "while" || s == "do"   || s == "case"
        || s == "of"    || s == ".."      || s == "otherwise"|| s == "repeat"|| s == "for"  || s == "until"
        || s == "loop"  || s == "pool"    || s == "exit"     || s == "<="    || s == "<>"   || s == "<"
        || s == ">="    || s == ">"       || s == "="        || s == "mod"   || s == "and"  || s == "or"
        || s == "not"   || s == "read"    || s == "succ"     || s == "pred"  || s == "chr"  || s == "ord"
        || s == "eof"   || s == "{"       || s == ":"        || s == ";"     || s == "."    || s == ","
        || s == "("     || s == ")"       || s == "+"        || s == "-"     || s == "*"    || s == "/"){
        return true;
    }

    else{
        return false;
        }
    }

string fileToString(string filename){

    ifstream ifs(filename);
    string content( (istreambuf_iterator<char>(ifs) ),
                    (istreambuf_iterator<char>()) );

    return content;

    /*for (int i = 0; i < content.size(); ++i) {
        cout << content[i];
    }*/

}

Token scan(string filename) {

    fileContent = fileToString(filename);
    //cout << "fileContent[position] is : " << fileContent[position] << endl;

    while (fileContent[position] == '\n' || fileContent[position] == ' '
           || fileContent[position] == '\f' || fileContent[position] == '\t'
           || fileContent[position] == '\v') {

        position++;
    }

        //string fileContent = filename;

        if (isalpha(fileContent[position]) || fileContent[position] == '_') {

            for (int i = 0; i < fileContent.size(); i++) {

                if (isalpha(fileContent[position]) || isnumber(fileContent[position]) || fileContent[position] == '_') {
                    tokenText += fileContent[position];
                    position++;
                    //cout << "tokenText is " << tokenText << endl;
                    //cout << "position is " << position << endl;

                } else {
                    break;
                }

            }

            if (isKeyword(tokenText)) {
                className = "<";
                className += tokenText;
                className += ">";
            } else {
                className = "<identifier>";
                build_Tree(tokenText, 0);
                build_Tree("<identifier>", 1);
            }
        }

        else if (isnumber(fileContent[position])) {

            for (int i = 0; i < fileContent.size(); i++) {

                if (isnumber(fileContent[position])) {
                    tokenText += fileContent[position];
                    position++;

                } else {
                    break;
                }

            }

            className = "<integer>";
            build_Tree(tokenText, 0);
            build_Tree("<integer>", 1);

        }

            /*else if(fileContent[position] == ' ' || fileContent[position] == '\f'
                || fileContent[position] == '\t' || fileContent[position] == '\v'){

                for(int i = 0; i < fileContent.size(); i++){

                    if(fileContent[position] == ' ' || fileContent[position] == '\f'
                       || fileContent[position] == '\t' || fileContent[position] == '\v'){
                        tokenText += fileContent[position];
                        position++;
                        //cout << "tokenText is " << tokenText << endl;
                        //cout << "position is " << position << endl;

                    } else{
                        break;
                    }

                }

                className = "<whiteSpace>";
                cout << className << endl;

            }*/

        else if (fileContent[position] == '\'') {
            for (int i = 0; i < 3; i++) {
                tokenText += fileContent[position];
                position++;
            }
            if (isChar(tokenText)) {
                className = "<char>";
                build_Tree(tokenText, 0);
                build_Tree("<char>", 1);
            } else {
                cout << "There has been an error" << endl;
            }
        }

        else if (fileContent[position] == '\"') {

            tokenText = "\"";
            position++;

            for (int i = 0; i < fileContent.size(); i++) {

                if (fileContent[position] != '\"') {
                    tokenText += fileContent[position];
                    position++;

                } else {
                    tokenText += "\"";
                    position++;
                    break;
                }

            }

            className = "<string>";
            build_Tree(tokenText, 0);
            build_Tree("<string>", 1);

        }

        else if(fileContent[position] == '#'){

            for(int i = 0; i < fileContent.size(); i++){

                if(fileContent[position] != '\n'){
                    tokenText += fileContent[position];
                    position++;

                } else{
                    tokenText += "\n";
                    position++;
                    break;
                }

            }

            className = "<comment>";
            tokenText = "";
        }

        else if (fileContent[position] == '{') {

            for (int i = 0; i < fileContent.size(); i++) {

                if (fileContent[position] != '}') {
                    //tokenText += fileContent[position];
                    position++;

                } else {
                    //tokenText += "}";
                    position++;
                    //cout << "tokenText is " << tokenText << endl;
                    //cout << "position is " << position << endl;
                    break;
                }

            }

            className = "<comment>";
            //cout << "className is " << className << endl;

        } else if (fileContent[position] == '\\') {

            if (fileContent[position + 1] == 'n') {
                tokenText += "\\n";
                position += 2;
                className = "<\\n>";
                //cout << "tokenText is " << tokenText << endl;
                //cout << "className is " << className << endl;

            } else {
                cout << "There has been an error" << endl;
                position += 2;
                cout << "tokenText is " << tokenText << endl;
            }

        } else if (fileContent[position] == ':' && fileContent[position + 1] != '=') {

            tokenText += ":";
            position++;
            className = "<:>";
            //cout << "tokenText is " << tokenText << endl;
            //cout << "className is " << className << endl;
        } else if (fileContent[position] == ':' && fileContent[position + 1] == '=' &&
                   fileContent[position + 2] != ':') {

            tokenText += ":=";
            position += 2;
            className = "<:=>";
            //cout << "tokenText is " << tokenText << endl;
            //cout << "className is " << className << endl;
        } else if (fileContent[position] == ':' && fileContent[position + 1] == '=' &&
                   fileContent[position + 2] == ':') {

            tokenText += ":=:";
            position += 3;
            className = "<:=:>";
            //cout << "tokenText is " << tokenText << endl;
            //cout << "className is " << className << endl;
        } else if (fileContent[position] == '.' && fileContent[position + 1] != '.') {

            tokenText += ".";
            position++;
            className = "<.>";
            //cout << "tokenText is " << tokenText << endl;
            //cout << "className is " << className << endl;
        } else if (fileContent[position] == '.' && fileContent[position + 1] == '.') {

            tokenText += "..";
            position += 2;
            className = "<..>";
            //cout << "tokenText is " << tokenText << endl;
            //cout << "className is " << className << endl;
        } else if (fileContent[position] == '<' && fileContent[position + 1] != '=' &&
                   fileContent[position + 1] != '>') {

            tokenText += "<";
            position++;
            className = "<<>";
            //cout << "tokenText is " << tokenText << endl;
            //cout << "className is " << className << endl;
        } else if (fileContent[position] == '<' && fileContent[position + 1] == '=') {

            tokenText += "<=";
            position += 2;
            className = "<<=>";
            //cout << "tokenText is " << tokenText << endl;
            //cout << "className is " << className << endl;
        } else if (fileContent[position] == '<' && fileContent[position + 1] == '>') {

            tokenText += "<>";
            position += 2;
            className = "<<>>";
            //cout << "tokenText is " << tokenText << endl;
            //cout << "className is " << className << endl;
        } else if (fileContent[position] == '>' && fileContent[position + 1] != '=') {

            tokenText += ">";
            position++;
            className = "<>>";
            //cout << "tokenText is " << tokenText << endl;
            //cout << "className is " << className << endl;
        } else if (fileContent[position] == '>' && fileContent[position + 1] == '=') {

            tokenText += ">=";
            position += 2;
            className = "<>=>";
            //cout << "tokenText is " << tokenText << endl;
            //cout << "className is " << className << endl;
        } else if (fileContent[position] == ';' || fileContent[position] == ','
                   || fileContent[position] == '(' || fileContent[position] == ')'
                   || fileContent[position] == '+' || fileContent[position] == '-'
                   || fileContent[position] == '*' || fileContent[position] == '/'
                   || fileContent[position] == '=') {

            tokenText += fileContent[position];
            position++;
            className = "<";
            className += tokenText;
            className += ">";
            //cout << "tokenText is " << tokenText << endl;
            //cout << "className is " << className << endl;
        }

        if(className == "<comment>"){
            scan(filename);
        }
    Token myTok = Token(className, tokenText, position);
        return myTok;

}

Token current_token = scan(file);

void read(string expected_class){

    if(expected_class == current_token.T_class){
        cout << "We got what we expected - "  << current_token.T_text << " is a "
        << expected_class << " in char position " << current_token.T_source << endl;

        outputFileString += "We got what we expected - "  + current_token.T_text + " is a "
                + expected_class + " in char position " + to_string(current_token.T_source) + "\n";
    }
    else{
        cout << current_token.T_text << " in char position " << current_token.T_source <<
        " is not a " << expected_class << endl;
    }

    tokenText = "";
    current_token = scan(file);

}

void Tiny(){
    //Tiny       -> 'program' Name ':' Consts Types Dclns
    //SubProgs Body Name '.' 			=> "program";

    read("<program>");
    Name();
    read("<:>");
    Consts();
    Types();
    Dclns();
    SubProgs();
    Body();
    Name();
    read("<.>");

    build_Tree("program", 7);

}


void Consts() {
//Consts     -> 'const' Const list ',' ';'			=> "consts"
//-> 							=> "consts";

    if(current_token.T_text == "const") {
        read("<const>");

        int num = 1;
        Const();

        while (current_token.T_text == ",") {
            read("<,>");
            num++;
            Const();
        }

        read("<;>");
        build_Tree("consts", num);
    }
    else{
        build_Tree("consts", 0);
    }

}

void Const() {
//Const      -> Name '=' ConstValue				=> "const";

    Name();
    read("<=>");
    ConstValue();

    build_Tree("const", 2);

}

void ConstValue() {
//ConstValue -> '<integer>'
//-> '<char>'
//-> Name;

    if(current_token.T_class == "<integer>"){
        build_Tree(current_token.T_text, 0);
        build_Tree("<integer>", 1);
        read("<integer>");
    }

    else if(current_token.T_class == "<char>"){
        //build_Tree(current_token.T_text, 0);
        //build_Tree("<char>", 1);
        read("<char>");
    }

    else if(current_token.T_class == "<identifier>"){
        Name();
    }

    else{
        cout << "There's a problem with ConstValue at char position: " << position << endl;
    }

}

void Types() {
//Types      -> 'type' (Type ';')+				=> "types"
//-> 							=> "types";


    if(current_token.T_class == "<type>"){
        int num = 1;
        read("<type>");
        Type();
        read("<;>");

        while(current_token.T_class == "<identifier>"){
            num++;
            Type();
            read("<;>");
        }
        build_Tree("types", num);
    }

    else{
        build_Tree("types", 0);
    }

}

void Type() {
//Type       -> Name '=' LitList				=> "type";

    Name();
    read("<=>");
    LitList();

    build_Tree("type", 2);

}

void LitList() {
//LitList    -> '(' Name list ',' ')' 			=> "lit";

    read("<(>");
    int num = 1;
    Name();

    while(current_token.T_text == ","){
        read("<,>");
        num++;
        Name();
    }
    read("<)>");
    build_Tree("lit", num);
}

void SubProgs() {
//SubProgs   -> Fcn*						=> "subprogs";

    int num = 0;
    while(current_token.T_text == "function"){
        num++;
        Fcn();
    }

    build_Tree("subprogs", num);

}

void Fcn() {
//Fcn        -> 'function' Name '(' Params ')' ':' Name
//';' Consts Types Dclns Body Name ';'	=> "fcn";

    read("<function>");
    Name();
    read("<(>");
    Params();
    read("<)>");
    read("<:>");
    Name();
    read("<;>");
    Consts();
    Types();
    Dclns();
    Body();
    Name();
    read("<;>");

    build_Tree("fcn", 8);

}

void Params() {
//Params     -> Dcln list ';'					=> "params";

    int num = 1;
    Dcln();
    while(current_token.T_text == ";"){
        read("<;>");
        num++;
        Dcln();
    }

    build_Tree("params", num);
}

void Dclns() {
//Dclns      -> 'var' (Dcln ';')+				=> "dclns"
//-> 							=> "dclns";

    if(current_token.T_text == "var"){

        read("<var>");
        int num = 1;
        Dcln();
        read("<;>");

        while(current_token.T_class == "<identifier>"){
            num++;
            Dcln();
            read("<;>");
        }

        build_Tree("dclns", num);
    }


    else {
        build_Tree("dclns", 0);
    }
}

void Dcln() {
//Dcln       -> Name list ',' ':' Name			=> "var";

    int num = 1;
    Name();
    while(current_token.T_text == ","){
        read("<,>");
        num++;
        Name();
    }
    read("<:>");
    num++;
    Name();

    build_Tree("var", num);

}

void Body() {
//Body       -> 'begin' Statement list ';' 'end'		=> "block";

    read("<begin>");
    int num = 1;
    Statement();

    if(current_token.T_text != ";"){
        build_Tree("block", num);
        read("<end>");
    }

    else if(current_token.T_text == ";") {
        while (current_token.T_text == ";") {
            read("<;>");
            num++;
            Statement();
        }
        build_Tree("block", num);
        read("<end>");
    }

    else {
        //build_Tree("block", num);
    }
}

void Statement() {
//Statement  -> Assignment
//-> 'output' '(' OutExp list ',' ')'		=> "output"
//-> 'if' Expression 'then' Statement
//('else' Statement)?		=> "if"
//-> 'while' Expression 'do' Statement		=> "while"
//-> 'repeat' Statement list ';' 'until'
//Expression        				=> "repeat"
//-> 'for' '(' ForStat ';' ForExp ';'
//ForStat ')' Statement			=> "for"
//-> 'loop' Statement list ';' 'pool'		=> "loop"
//-> 'case' Expression 'of' Caseclauses
//        OtherwiseClause 'end'			=> "case"
//-> 'read' '(' Name list ',' ')'		=> "read"
//-> 'exit'						=> "exit"
//-> 'return' Expression				=> "return"
//-> Body
//->							=> "<null>";

    if(current_token.T_class == "<identifier>"){

        Assignment();

    }

    else if(current_token.T_text == "output"){

        read("<output>");
        read("<(>");
        int num = 1;
        OutExp();
        while(current_token.T_text == ","){
            read("<,>");
            num++;
            OutExp();
        }
        read("<)>");

        build_Tree("output", num);

    }

    else if(current_token.T_text == "if"){

        read("<if>");
        int num =1;
        Expression();
        read("<then>");
        num++;
        Statement();

        if(current_token.T_text == "else"){
            read("<else>");
            num++;
            Statement();
        }

        else{

        }

        build_Tree("if", num);

    }

    else if(current_token.T_text == "while"){

        read("<while>");
        Expression();
        read("<do>");
        Statement();


        build_Tree("while", 2);
    }

    else if(current_token.T_text == "repeat"){

        read("<repeat>");
        int num = 1;
        Statement();
        while(current_token.T_text == ";"){
            read("<;>");
            num++;
            Statement();
        }
        read("<until>");
        num++;
        Expression();

        build_Tree("repeat", num);

    }

    else if(current_token.T_text == "for"){

        read("<for>");
        read("<(>");
        ForStat();
        read("<;>");
        ForExp();
        read("<;>");
        ForStat();
        read("<)>");
        Statement();

        build_Tree("for", 4);

    }

    else if(current_token.T_text == "loop"){

        read("<loop>");
        int num = 1;
        Statement();
        while(current_token.T_text == ";"){
            read("<;>");
            num++;
            Statement();
        }
        read("<pool>");

        build_Tree("loop", num);

    }

    else if(current_token.T_text == "case"){

        int num = 1;
        read("<case>");
        Expression();
        read("<of>");
        num += Caseclauses();
        num += OtherwiseClause();
        read("<end>");

        build_Tree("case", num); //this may be a problem
    }

    else if(current_token.T_text == "read"){

        read("<read>");
        read("<(>");
        int num = 1;
        Name();
        while(current_token.T_text == ","){
            read("<,>");
            num++;
            Name();
        }
        read("<)>");

        build_Tree("read", num);

    }

    else if(current_token.T_text == "exit"){

        read("<exit>");

        build_Tree("exit", 0);

    }

    else if(current_token.T_text == "return"){

        read("<return>");
        Expression();

        build_Tree("return", 1);

    }

    else if(current_token.T_text == "begin"){

        Body();

    }

    else{
        build_Tree("<null>", 0);
    }

}

void OutExp() {
//OutExp     -> Expression					=> "integer"
//-> StringNode					=> "string";
//Might have a problem here if the input is incorrect (not Expression or string)


    if(current_token.T_class == "<string>"){
        StringNode();
        build_Tree("string", 1);
    }

    else{
        Expression();
        build_Tree("integer", 1);
    }

}

void StringNode() {
//StringNode -> '<string>';

    read("<string>");
    //build_Tree(current_token.T_text, 0);
    //build_Tree("<string>", 1);

}

int Caseclauses() {
//Caseclauses-> (Caseclause ';')+;

    int num = 1;
    Caseclause();
    read("<;>");
    while(current_token.T_class == "<identifier>" || current_token.T_class == "<char>"
        || current_token.T_class == "<integer>"){
        Caseclause();
        num++;
        read("<;>");
    }
    return num;
//may need to return an int here to keep track of tree nodes for Caseclause
}

void Caseclause() {
//Caseclause -> CaseExpression list ',' ':' Statement	=> "case_clause";

    int num = 1;
    CaseExpression();

    if(current_token.T_text != ","){

        read("<:>");
        Statement();
        build_Tree("case_clause", num+1);
    }

    else if (current_token.T_text == ","){
        while(current_token.T_text == ","){
            read("<,>");
            num++;
            CaseExpression();
        }

        read("<:>");
        Statement();
        build_Tree("case_clause", num+1);
    }

    else{

    }

}

void CaseExpression() {
//CaseExpression
//-> ConstValue
//-> ConstValue '..' ConstValue			=> "..";

    ConstValue();
    if(current_token.T_text == ".."){
        read("<..>");
        ConstValue();
        build_Tree("..", 2);
    }

}

int OtherwiseClause() {
//OtherwiseClause
//-> 'otherwise' Statement				=> "otherwise"
//-> ;

    if(current_token.T_text == "otherwise") {
        read("<otherwise>");
        Statement();
        build_Tree("otherwise", 1);
        return 1;
    }
    else if(current_token.T_text == ";"){
        read("<;>");
        return 0;
    }
    else{
        return 0;
    }

}

void Assignment() {
//Assignment -> Name ':=' Expression  			=> "assign"
//-> Name ':=:' Name					=> "swap";

    Name();
    if(current_token.T_text == ":="){
        read("<:=>");
        Expression();
        build_Tree("assign", 2);
    }
    else if(current_token.T_text == ":=:"){
        read("<:=:>");
        Name();
        build_Tree("swap", 2);
    }

}

void ForStat() {
//ForStat    -> Assignment
//-> 							=> "<null>";

    if(current_token.T_class == "<identifier>"){
        Assignment();
    }
    else{
        build_Tree("<null>", 0);
    }

}

void ForExp() {
//ForExp     -> Expression
//-> 							=> "true";

    if(current_token.T_text == "-" || current_token.T_text == "+"    || current_token.T_text == "not" ||
     current_token.T_text == "eof" || current_token.T_text == "succ" || current_token.T_text == "pred"||
     current_token.T_text == "chr" || current_token.T_text == "ord"  || current_token.T_text == "("   ||
     current_token.T_class == "<identifier>" || current_token.T_class == "<integer>" ||
     current_token.T_class == "<char>") {
        Expression();
    }

    else{
        build_Tree("true", 0);
    }

}

void Expression() {
//Expression -> Term
//-> Term '<=' Term					=> "<="
//-> Term '<' Term					=> "<"
//-> Term '>=' Term					=> ">="
//-> Term '>' Term					=> ">"
//-> Term '=' Term					=> "="
//-> Term '<>' Term					=> "<>";

    Term();

    if(current_token.T_text == "<="){

        read("<<=>");
        Term();
        build_Tree("<=", 2);
    }

    else if(current_token.T_text == "<"){

        read("<<>");
        Term();
        build_Tree("<", 2);
    }

    else if(current_token.T_text == ">="){

        read("<>=>");
        Term();
        build_Tree(">=", 2);
    }

    else if(current_token.T_text == ">"){

        read("<>>");
        Term();
        build_Tree(">", 2);
    }

    else if(current_token.T_text == "="){

        read("<=>");
        Term();
        build_Tree("=", 2);
    }

    else if(current_token.T_text == "<>"){

        read("<<>>");
        Term();
        build_Tree("<>", 2);
    }

    else{

    }

}

void Term() {
//Term       -> Factor
//-> Term '+' Factor					=> "+"
//-> Term '-' Factor					=> "-"
//-> Term 'or' Factor				=> "or";


    Factor();
    while(current_token.T_text == "+" || current_token.T_text == "-" || current_token.T_text == "or"){

        if(current_token.T_text == "+"){

            read(current_token.T_class);
            Factor();
            build_Tree("+", 2);
        }

        if(current_token.T_text == "-"){

            read(current_token.T_class);
            Factor();
            build_Tree("-", 2);
        }

        if(current_token.T_text == "or"){

            read(current_token.T_class);
            Factor();
            build_Tree("or", 2);
        }

    }

}

void Factor() {
//Factor     -> Factor '*' Primary				=> "*"
//-> Factor '/' Primary				=> "/"
//-> Factor 'and' Primary				=> "and"
//-> Factor 'mod' Primary				=> "mod"
//-> Primary;

    Primary();
    while(current_token.T_text == "*" || current_token.T_text == "/" ||
        current_token.T_text == "and" || current_token.T_text == "mod"){

        if(current_token.T_text == "*"){

            read(current_token.T_class);
            Primary();
            build_Tree("*", 2);
        }

        if(current_token.T_text == "/"){

            read(current_token.T_class);
            Primary();
            build_Tree("/", 2);
        }

        if(current_token.T_text == "and"){

            read(current_token.T_class);
            Primary();
            build_Tree("and", 2);
        }

        if(current_token.T_text == "mod"){

            read(current_token.T_class);
            Primary();
            build_Tree("mod", 2);
        }

    }

}

void Primary() {
//Primary    -> '-' Primary					=> "-"
//-> '+' Primary
//-> 'not' Primary					=> "not"
//-> 'eof'						=> "eof"
//-> Name
//-> '<integer>'
//-> '<char>'
//-> Name '(' Expression list ',' ')'		=> "call"
//-> '(' Expression ')'
//-> 'succ' '(' Expression ')' 			=> "succ"
//-> 'pred' '(' Expression ')' 			=> "pred"
//-> 'chr' '(' Expression ')' 			=> "chr"
//-> 'ord' '(' Expression ')' 			=> "ord";

    if(current_token.T_text == "-"){
        read("<->");
        Primary();
        build_Tree("-", 1);
    }

    else if(current_token.T_text == "+"){
        read("<+>");
        Primary();
    }

    else if(current_token.T_text == "not"){
        read("<not>");
        Primary();
        build_Tree("not", 1);
    }

    else if(current_token.T_text == "eof"){
        read("<eof>");
        build_Tree("eof", 0);
    }

    else if(current_token.T_class == "<identifier>"){
        int num = 1;
        Name();

        if(current_token.T_text == "("){
            read("<(>");
            num++;
            Expression();
            while(current_token.T_text == ","){
                read("<,>");
                num++;
                Expression();
            }
            read("<)>");
            build_Tree("call", num);
        }
    }

    else if(current_token.T_class == "<integer>"){
        read("<integer>");
        //build_Tree(current_token.T_text, 0);
        //build_Tree("<integer>", 1);
    }

    else if(current_token.T_class == "<char>"){
        read("<char>");
        build_Tree(current_token.T_text, 0);
        build_Tree("<char>", 1);
    }

    else if(current_token.T_text == "("){
        read("<(>");
        Expression();
        read("<)>");
    }

    else if(current_token.T_text == "succ"){
        read("<succ>");
        read("<(>");
        Expression();
        read("<)>");
        build_Tree("succ", 1);
    }

    else if(current_token.T_text == "pred"){
        read("<pred>");
        read("<(>");
        Expression();
        read("<)>");
        build_Tree("pred", 1);
    }

    else if(current_token.T_text == "chr"){
        read("<chr>");
        read("<(>");
        Expression();
        read("<)>");
        build_Tree("chr", 1);
    }

    else if(current_token.T_text == "ord"){
        read("<ord>");
        read("<(>");
        Expression();
        read("<)>");
        build_Tree("ord", 1);
    }

}

void Name() {
//Name       -> '<identifier>';

    read("<identifier>");
    //build_Tree(current_token.T_text, 0);
    //build_Tree("<identifier>", 1);


}

void build_Tree(string nodeName, int functionCalls) {

    //not doing anything yet.

    Node* root = new Node(nodeName, functionCalls);

    Node* temp = NULL;
    for(int i = 0; i < functionCalls; i++){
        Node* x_node = stackOfTreeNodes.top();

            if(stackOfTreeNodes.empty()){
                cout << "Error, the tree is empty" << endl;
            }

            else {
                stackOfTreeNodes.pop();
                x_node->sibling = temp;
                temp = x_node;
            }
    }
    root->child = temp;
    root->sibling = NULL;
    stackOfTreeNodes.push(root);
}

void preorder(Node* root){

    if(root == NULL){
        return;
    }

    cout << root->nodeName << endl;

    preorder(root->child);
    preorder(root->sibling);

}

void print_Tree_standard(Node* root, int numDots){

    if(root == NULL){
        return;
    }

    for(int i = 0; i < numDots; i++){
        outputFileString += ". ";
        cout << ". ";
    }

    cout << root->nodeName << "(" << root->nodeChildren << ")" << endl;
    print_Tree_standard(root->child, numDots+1);
    print_Tree_standard(root->sibling, numDots+1);

}

void print_Tree(Node* root, int numDots){

    if(root == NULL){
        return;
    }

    for(int i = 0; i < numDots; i++){
        outputFileString += ". ";
        cout << ". ";
    }

    outputFileString += root->nodeName + "(" + to_string(root->nodeChildren) + ")" + '\n';
    cout << root->nodeName << "(" << root->nodeChildren << ")" << endl;
    print_Tree(root->child, numDots+1);
    //print_Tree(child->sibling, numDots);
    print_Tree(root->sibling, numDots);

}

int main() {

    /*token = "succ";

    if(isKeyword(token)) {
        cout << "It is" << endl;
        cout << token;
    }

    if(!isKeyword(token)) {
        cout << "It is NOT" << endl;
        cout << token;
    }*/

    /*cout << token[0] << " is token[0]" << endl;
    cout << token[token.size() -1] << " is token[token.size() -1]" << endl;*/

    /*ifstream ifs("/Users/tiffanydevlindrye/CLionProjects/COP4020/tiny_02");
    string content( (istreambuf_iterator<char>(ifs) ),
                         (istreambuf_iterator<char>()) );


    for (int i = 0; i < content.size(); ++i) {

        cout << content[i];
    }*/

    //readAndPrint("/Users/tiffanydevlindrye/CLionProjects/COP4020/tiny_01.txt");

    /*Token *testTok = new Token();
    testTok->tokenClass = "<identifier>";
    testTok->tokenSource = "L12C2";
    testTok->tokenText = "cherry";

    cout << testTok->tokenSource << endl;*/

    /*Token myTokFromScan = scan("/Users/tiffanydevlindrye/CLionProjects/COP4020/tdd_testing.txt");

    cout << "tokenText is: " << tokenText << endl;
    cout << "className is " << className << endl;
    cout << "position is " << position << endl;

    cout << "myTok->T_class is: " << myTokFromScan.T_class << endl;
    cout << "myTok->T_text is: " << myTokFromScan.T_text << endl;
    cout << "myTok->T_source is: " << myTokFromScan.T_source << endl;

    tokenText = "";

    myTokFromScan = scan("/Users/tiffanydevlindrye/CLionProjects/COP4020/tdd_testing.txt");

    cout << "tokenText is: " << tokenText << endl;
    cout << "className is " << className << endl;
    cout << "position is " << position << endl;

    cout << "myTok->T_class is: " << myTokFromScan.T_class << endl;
    cout << "myTok->T_text is: " << myTokFromScan.T_text << endl;
    cout << "myTok->T_source is: " << myTokFromScan.T_source << endl;

    tokenText = "";

    myTokFromScan = scan("/Users/tiffanydevlindrye/CLionProjects/COP4020/tdd_testing.txt");

    cout << "tokenText is: " << tokenText << endl;
    cout << "className is " << className << endl;
    cout << "position is " << position << endl;

    cout << "myTok->T_class is: " << myTokFromScan.T_class << endl;
    cout << "myTok->T_text is: " << myTokFromScan.T_text << endl;
    cout << "myTok->T_source is: " << myTokFromScan.T_source << endl;

    tokenText = "";

    myTokFromScan = scan("/Users/tiffanydevlindrye/CLionProjects/COP4020/tdd_testing.txt");

    cout << "tokenText is: " << tokenText << endl;
    cout << "className is " << className << endl;
    cout << "position is " << position << endl;

    cout << "myTok->T_class is: " << myTokFromScan.T_class << endl;
    cout << "myTok->T_text is: " << myTokFromScan.T_text << endl;
    cout << "myTok->T_source is: " << myTokFromScan.T_source << endl;

    tokenText = "";

    myTokFromScan = scan("/Users/tiffanydevlindrye/CLionProjects/COP4020/tdd_testing.txt");

    cout << "tokenText is: " << tokenText << endl;
    cout << "className is " << className << endl;
    cout << "position is " << position << endl;

    cout << "myTok->T_class is: " << myTokFromScan.T_class << endl;
    cout << "myTok->T_text is: " << myTokFromScan.T_text << endl;
    cout << "myTok->T_source is: " << myTokFromScan.T_source << endl;

    tokenText = "";

    myTokFromScan = scan("/Users/tiffanydevlindrye/CLionProjects/COP4020/tdd_testing.txt");

    cout << "tokenText is: " << tokenText << endl;
    cout << "className is " << className << endl;
    cout << "position is " << position << endl;

    cout << "myTok->T_class is: " << myTokFromScan.T_class << endl;
    cout << "myTok->T_text is: " << myTokFromScan.T_text << endl;
    cout << "myTok->T_source is: " << myTokFromScan.T_source << endl;

    tokenText = "";

    myTokFromScan = scan("/Users/tiffanydevlindrye/CLionProjects/COP4020/tdd_testing.txt");

    cout << "tokenText is: " << tokenText << endl;
    cout << "className is " << className << endl;
    cout << "position is " << position << endl;

    cout << "myTok->T_class is: " << myTokFromScan.T_class << endl;
    cout << "myTok->T_text is: " << myTokFromScan.T_text << endl;
    cout << "myTok->T_source is: " << myTokFromScan.T_source << endl;

    tokenText = "";

    myTokFromScan = scan("/Users/tiffanydevlindrye/CLionProjects/COP4020/tdd_testing.txt");

    cout << "tokenText is: " << tokenText << endl;
    cout << "className is " << className << endl;
    cout << "position is " << position << endl;

    cout << "myTok->T_class is: " << myTokFromScan.T_class << endl;
    cout << "myTok->T_text is: " << myTokFromScan.T_text << endl;
    cout << "myTok->T_source is: " << myTokFromScan.T_source << endl;

    tokenText = "";

    myTokFromScan = scan("/Users/tiffanydevlindrye/CLionProjects/COP4020/tdd_testing.txt");

    cout << "tokenText is: " << tokenText << endl;
    cout << "className is " << className << endl;
    cout << "position is " << position << endl;

    cout << "myTok->T_class is: " << myTokFromScan.T_class << endl;
    cout << "myTok->T_text is: " << myTokFromScan.T_text << endl;
    cout << "myTok->T_source is: " << myTokFromScan.T_source << endl;

    tokenText = "";

    myTokFromScan = scan("/Users/tiffanydevlindrye/CLionProjects/COP4020/tdd_testing.txt");

    cout << "tokenText is: " << tokenText << endl;
    cout << "className is " << className << endl;
    cout << "position is " << position << endl;

    cout << "myTok->T_class is: " << myTokFromScan.T_class << endl;
    cout << "myTok->T_text is: " << myTokFromScan.T_text << endl;
    cout << "myTok->T_source is: " << myTokFromScan.T_source << endl;

    tokenText = "";

    myTokFromScan = scan("/Users/tiffanydevlindrye/CLionProjects/COP4020/tdd_testing.txt");

    cout << "tokenText is: " << tokenText << endl;
    cout << "className is " << className << endl;
    cout << "position is " << position << endl;

    cout << "myTok->T_class is: " << myTokFromScan.T_class << endl;
    cout << "myTok->T_text is: " << myTokFromScan.T_text << endl;
    cout << "myTok->T_source is: " << myTokFromScan.T_source << endl;*/

    //cout << "tokenText is: " << tokenText << endl;
    //Primary();

    //Tiny();
    /*build_Tree("test1", 0);
    build_Tree("test2", 0);
    build_Tree("test3", 0);
    build_Tree("test4", 0);
    build_Tree("test5", 0);
    build_Tree("test6", 0);

    cout << stackOfTreeNodes.top()->nodeName << endl;
    cout << stackOfTreeNodes.top()->nodeChildren << endl;
    stackOfTreeNodes.pop();
    cout << stackOfTreeNodes.top()->nodeName << endl;
    cout << stackOfTreeNodes.top()->nodeChildren << endl;
    stackOfTreeNodes.pop();
    cout << stackOfTreeNodes.top()->nodeName << endl;
    cout << stackOfTreeNodes.top()->nodeChildren << endl;
    stackOfTreeNodes.pop();
    cout << stackOfTreeNodes.top()->nodeName << endl;
    cout << stackOfTreeNodes.top()->nodeChildren << endl;
    stackOfTreeNodes.pop();
    cout << stackOfTreeNodes.top()->nodeName << endl;
    cout << stackOfTreeNodes.top()->nodeChildren << endl;
    stackOfTreeNodes.pop();
    cout << stackOfTreeNodes.top()->nodeName << endl;
    cout << stackOfTreeNodes.top()->nodeChildren << endl;
    stackOfTreeNodes.pop();*/

    Tiny();
    //print_Tree(stackOfTreeNodes.top(), 0);

    //print_Tree_standard(stackOfTreeNodes.top(), 0);
    outputFile.open("parsingOutput_25.txt");
    //cout << outputFileString;
    outputFile << outputFileString;


return 0;
}