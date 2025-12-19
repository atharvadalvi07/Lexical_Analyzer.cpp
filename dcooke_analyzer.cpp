#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string getString(char x) {
    string s(1, x);
    return s;
}

bool isSpecial(char character) {
    return (character == ':' || character == '<' || character == '>' || character == '=' ||
            character == '+' || character == '-' || character == '*' || character == '/' ||
            character == '(' || character == ')' || character == ';' || character == '{' ||
            character == '}' || character == '_' );
}

bool isTwoCharSpecial(string word) {
    return (word == ":=" || word == "!=" || word == ">=" || word == "<=" || word == "==" || word == "++" || word == "--");
}

int getSpecialCharIndex(string word) {
    if (word == ":=") {
        return 0;
    } else if (word == "!=") {
        return 1;
    } else if (word == ">=") {
        return 2;
    } else if (word == "<=") {
        return 3;
    } else if (word == "==") {
        return 4;
    } else if (word == "++") {
        return 5;
    } else if (word == "--") {
        return 6;
    }
    return -1;
}

int getReservedKeywordIndex(string word) {
    if (word == "read") {
        return 0;
    } else if (word == "write") {
        return 1;
    } else if (word == "while") {
        return 2;
    } else if (word == "do") {
        return 3;
    } else if (word == "od") {
        return 4;
    }
    return -1;
}

bool isAllLower(string word) {
    for (size_t i = 0; i < word.length(); ++i) {
        if (!islower(word[i])) {
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv) {
    if (argc == 2) {
        string line;
        ifstream myfile(argv[1]);

        if (myfile.is_open()) {
            cout << "DCooke Analyzer :: " << endl;

            while (getline(myfile, line)) {
                int pointer = 0;
                int lineLength = line.length();

                while (pointer < lineLength) {
                    char sub_string = line[pointer];

                    if (isdigit(sub_string)) {
                        int digitCounter = 0;
                        int digitNumber = 0;

                        while (isdigit(line[pointer + digitCounter])) {
                            int num = static_cast<int>(line[pointer + digitCounter]) - 48;
                            digitNumber = digitNumber * 10 + num;
                            digitCounter++;
                        }
                        cout << digitNumber << "      " << "INT_LIT" << endl;
                        pointer += digitCounter;
                    } else if (isalpha(sub_string) || sub_string == '_') {
                        string currentString = "";
                        int stringCounter = 0;

                        while (isalpha(line[pointer + stringCounter]) || line[pointer + stringCounter] == '_') {
                            currentString += line[pointer + stringCounter];
                            stringCounter++;
                        }

                        if (!isAllLower(currentString)) {
                            cout << currentString << "      " << "UNKNOWN" << endl;
                        }

                        int reservedKeywordIndex = getReservedKeywordIndex(currentString);

                        switch (reservedKeywordIndex) {
                            case 0:
                                cout << currentString << "      " << "KEY_READ" << endl;
                                break;
                            case 1:
                                cout << currentString << "      " << "KEY_WRITE" << endl;
                                break;
                            case 2:
                                cout << currentString << "      " << "KEY_WHILE" << endl;
                                break;
                            case 3:
                                cout << currentString << "      " << "KEY_DO" << endl;
                                break;
                            case 4:
                                cout << currentString << "      " << "KEY_OD" << endl;
                                break;
                            default:
                                cout << currentString << "      " << "IDENT" << endl;
                                break;
                        }
                        pointer += stringCounter;
                    } else if (isSpecial(sub_string)) {
                        string specialString = getString(sub_string);

                        if (pointer + 1 < lineLength) {
                            specialString += line[pointer + 1];
                            if (isTwoCharSpecial(specialString)) {
                                int specialStringIndex = getSpecialCharIndex(specialString);
                                
                                switch (specialStringIndex) {
                                    case 0:
                                        cout << specialString << "      " << "ASSIGN_OP" << endl;
                                        break;
                                    case 1:
                                        cout << specialString << "      " << "NEQUAL_OP" << endl;
                                        break;
                                    case 2:
                                        cout << specialString << "      " << "GEQUAL_OP" << endl;
                                        break;
                                    case 3:
                                        cout << specialString << "      " << "LEQUAL_OP" << endl;
                                        break;
                                    case 4:
                                        cout << specialString << "      " << "EQUAL_OP" << endl;
                                        break;
                                    case 5:
                                        cout << specialString << "      " << "INC_OP" << endl;
                                        break;
                                    case 6:
                                        cout << specialString << "      " << "DEC_OP" << endl;
                                        break;
                                    default:
                                        cout << specialString << "      " << "UNKNOWN" << endl;
                                        break;      
                                    }
                                pointer += 2;
                            } else {
                                switch (sub_string) {
                                    case '<':
                                        cout << sub_string << "      " << "LESSER_OP" << endl;
                                        break;
                                    case '>':
                                        cout << sub_string << "      " << "GREATER_OP" << endl;
                                        break;
                                    case '=':
                                        cout << sub_string << "      " << "ASSIGN_OP" << endl;
                                        break;
                                    case '+':
                                        cout << sub_string << "      " << "ADD_OP" << endl;
                                        break;
                                    case '-':
                                        cout << sub_string << "      " << "SUB_OP" << endl;
                                        break;
                                    case '*':
                                        cout << sub_string << "      " << "MULT_OP" << endl;
                                        break;
                                    case '/':
                                        cout << sub_string << "      " << "DIV_OP" << endl;
                                        break;
                                    case '(':
                                        cout << sub_string << "      " << "LEFT_PAREN" << endl;
                                        break;
                                    case ')':
                                        cout << sub_string << "      " << "RIGHT_PAREN" << endl;
                                        break;
                                    case '{':
                                        cout << sub_string << "      " << "LEFT_CBRACE" << endl;
                                        break;
                                    case '}':
                                        cout << sub_string << "      " << "RIGHT_CBRACE" << endl;
                                        break;
                                    case ';':
                                        cout << sub_string << "      " << "SEMICOLON" << endl;
                                        break;
                                    default:
                                        cout << sub_string << "      " << "UNKNOWN" << endl;
                                        break;
                                }
                                pointer++;
                            }
                        } else {
                            switch (sub_string) {
                                case '<':
                                    cout << sub_string << "      " << "LESSER_OP" << endl;
                                    break;
                                case '>':
                                    cout << sub_string << "      " << "GREATER_OP" << endl;
                                    break;
                                case '=':
                                    cout << sub_string << "      " << "EQUAL_OP" << endl;
                                    break;
                                case '+':
                                    cout << sub_string << "      " << "ADD_OP" << endl;
                                    break;
                                case '-':
                                    cout << sub_string << "      " << "SUB_OP" << endl;
                                    break;
                                case '*':
                                    cout << sub_string << "      " << "MULT_OP" << endl;
                                    break;
                                case '/':
                                    cout << sub_string << "      " << "DIV_OP" << endl;
                                    break;
                                case '(':
                                    cout << sub_string << "      " << "LEFT_PAREN" << endl;
                                    break;
                                case ')':
                                    cout << sub_string << "      " << "RIGHT_PAREN" << endl;
                                    break;
                                case '{':
                                    cout << sub_string << "      " << "LEFT_CBRACE" << endl;
                                    break;
                                case '}':
                                    cout << sub_string << "      " << "RIGHT_CBRACE" << endl;
                                    break;
                                case ';':
                                    cout << sub_string << "      " << "SEMICOLON" << endl;
                                    break;
                                default:
                                    cout << sub_string << "      " << "UNKNOWN" << endl;
                                    break;
                            }
                            pointer++;
                        }
                    } else if (sub_string == ' ' || sub_string == '\t' ||
                               sub_string == '\n' || sub_string == '\v' ||
                               sub_string == '\f' || sub_string == '\r') {
                        pointer++;
                    } else {
                        cout << sub_string << "      " << "UNKNOWN" << endl;
                        pointer++;
                    }
                }
            }
            myfile.close();
        } else {
            cout << "Unable to open file" << endl;
        }
    } else {
        cout << "Not enough arguments passed" << endl;
    }
    return 0;
}
