//////////////////////////
//                      //
//      LOCO LANG       //
//                      //
//     Created by:      //
//     SeniorLoco       //
//                      //
//////////////////////////


#include <iostream>
#include <fstream>

using namespace std;

string extension = ".loco";

bool endsWith(const string& mainStr, const string& toMatch) {

    if (mainStr.size() >= toMatch.size() && mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0) return true;
    else return false;

}

void interpret(const string code) {

    cout << "interpreting " + code + "\n\n";
    ifstream file(code);

    string tok;
    string cmd;
    string logOp;

    int length;

    char numbers[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

    char c = ' ';

    if (file.is_open()) {

        file.seekg(0, ios::end);
        length = file.tellg();
        file.seekg(0, ios::beg);

        for (int i = 0; i < length; ++i) {

            c = file.get();
            tok += c;

            if (c == ' ') {

                tok = "";

            }

            if (tok == "log") {

                cmd = tok;
                tok = "";
                c = file.get();

            }

            while (cmd == "log") {

                if (c == '(') {

                    c = file.get();

                    if (c == '"') {

                        c = file.get();

                        while (c != '"') {

                            tok += c;
                            c = file.get();

                        }

                        logOp = tok;
                        tok = "";

                        if (c == '"') {

                            c = file.get();

                            if (c != ')') {

                                cout << "error... expected ')' at char : ";
                                cout << int(file.tellg())+1;
                                return;

                            }

                            else if (c == ')') {

                                c = file.get();

                                if (c == ';') {

                                    cout << logOp;
                                    cmd = "";

                                }

                                else {

                                    cout << "error... expected ';' at char : ";
                                    cout << int(file.tellg()) + 1;
                                    return;

                                }
                            }
                        }

                        else {

                            cout << "error... at char : ";
                            cout << int(file.tellg()) + 1;
                            return;

                        }
                    }
                    
                    else if (c != '"') {

                        if (c == numbers[0] || c == numbers[1] || c == numbers[2] || c == numbers[3] || c == numbers[4] || c == numbers[5] || c == numbers[6] || c == numbers[7] || c == numbers[8] || c == numbers[9]) {

                            while (c != ')') {

                                if (c != numbers[0] && c != numbers[1] && c != numbers[2] && c != numbers[3] && c != numbers[4] && c != numbers[5] && c != numbers[6] && c != numbers[7] && c != numbers[8] && c != numbers[9]) {

                                    cout << "error... not an integer, at char : ";
                                    cout << int(file.tellg()) + 1;
                                    return;

                                }

                                tok += c;
                                c = file.get();

                            }

                            logOp = tok;
                            c = file.get();

                            if (c != ';') {

                                cout << "error... expected ';' at char : ";
                                cout << int(file.tellg()) + 1;
                                return;

                            }

                            else {

                                cmd = "";
                                cout << logOp;

                            }
                        }
                        else {

                            cout << "error... not an integer or string, at char : ";
                            cout << int(file.tellg()) + 1;
                            return;

                        }
                    }

                    else {

                        cout << "unknown error... at char : ";
                        cout << int(file.tellg()) + 1;
                        return;

                    }
                }
            }  
        }
    }

    else cout << "\nSomething went wrong... Unable to find file or there is an error!\n\n";
    file.close();

}

int main(int argc, char* argv[])
{
    string file = "";
    if (argc > 1) { file = argv[1]; }
    if (endsWith(file, extension)) {
        interpret(file);
    }
    else cout << "invalid file type.";
}