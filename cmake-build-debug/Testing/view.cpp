//
// Created by User on 18.10.2022.
//
#include <algorithm>
#include <string>
#include <iostream>

bool isLette1r(char x) {
    return (x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z');
}

std::string viewchan1ge(std::string &expr) {
    std::string buf;
    std::string expr1;
    bool b = false;
    bool ss = false;
    int s = 0;
    std::string x;
    int count = 0;
    int c = 0;
    int c1 = 0;
    int c2 = 0;
    bool c3 = false;
    for (int i = 0; i < expr.length(); i++) if (std::isdigit(expr[i]) || expr[i]=='x') c3= true;
    if(!c3) return "Incorrect input!";
    for (int i = 0; i < expr.length(); i++) if (expr[i] == ' ') expr.erase(i, 1);
    for (int i = 0; i < expr.length(); i++) if (expr[i] == ',') expr.replace(i, 1, ".");
    for (int i = 0; i < expr.length(); i++) if ( expr[i] == 'e' && expr[i + 1] == 'x' && expr[i + 2] == 'p') {expr.erase(i+1,2); expr.insert(i+1,"^");}
    for (char i: expr) {
        if (i == '(') c1++;
        if (i == ')') c2++;
    }
    if (expr.find_first_not_of("sincotgex0123456789^+/()*-") != std::string::npos)
    {
        return "Incorrect input!";
    }
    if (c1 != c2) return "Incorrect input!";
    for (int i = 0; i < expr.length(); i++) {
        if ((expr[i] == '/' || expr[i] == '*' || expr[i] == '+' || expr[i] == '-' || expr[i] == '^') &&
            expr[i] == expr[i + 1])
            return "Incorrect input!";
        else if (isLetter(expr[i])) {
            std::string buff;
            while (isLetter(expr[i])) {
                buff += expr[i];
                i++;
            }
            if ((buff == "ctg" || buff == "tg" || buff == "sin" || buff == "cos" || buff == "e" ||buff == "ctgx" || buff == "tgx" ||
                 buff == "sinx" || buff == "cosx" || buff == "ex") &&
                (std::isdigit(expr[i]) || expr[i] == '(' || buff[buff.length() - 1] == 'x'))
                c++;
            else if (buff == "x" &&
                     (expr[i] == '/' || expr[i] == '*' || expr[i] == '+' || expr[i] == '-' || expr[i] == '^' ||
                      expr[i] == '('))
                c++;
        }
        if (expr[i] == '/' || expr[i] == '*' || expr[i] == '+' || expr[i] == '-' ||
            expr[i] == '^' || expr[i] == '(' || expr[i] == ')' || expr[i] == 'c' || expr[i] == 's' || expr[i] == 'i' || expr[i] == 'n' || expr[i] == 'g' || expr[i] == 't')
            c++;
        if ((expr[i] == '/' || expr[i] == '*' || expr[i] == '+' || expr[i] == '-' ||
             expr[i] == '^' || expr[i] == '(') &&
            (!std::isdigit(expr[i + 1]) && expr[i + 1] != 'x' && expr[i + 1] != '(' && expr[i + 1] != '-'
             && expr[i + 1] != 's' && expr[i + 1] != 'c' && expr[i + 1] != 't' && expr[i + 1] != 'e'))
            return "Incorrect input!";
        if (expr[0] == '/' || expr[0] == '*' || expr[0] == '+' ||
            expr[0] == '^')
            return "Incorrect input!";
        if (expr[i] == '.' && !std::isdigit(expr[i - 1]) || expr[i] == '.' && !std::isdigit(expr[i + 1]))
            return "Incorrect input!";
        if (expr[i] == '(' && std::isdigit(expr[i - 1]) && i!=0) expr.insert(i, "*");
        if (expr[i] == ')' && std::isdigit(expr[i + 1])) expr.insert(i + 1, "*");
    }
    if (c == 0) return "Incorrect input!";
    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == 'x' && expr[i - 1] != 'e') {
            if(x.empty()){std::cout << "Enter x: ";
            std::cin >> x;}
            for (int i = 0; i < x.length(); i++) {
                if (std::isdigit(x[i]) || x[i] == '.' || x[i] == '-') ss = true;
                else ss = false;
            }
            if (ss) {
                expr.erase(i, 1);
                expr.insert(i, x);
            } else return "Incorrect input!";
        }
    }
    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == '-' && std::isdigit(expr[i + 1]) &&
            (i == 0 || expr[i - 1] == '(' || expr[i - 1] == '/' || expr[i - 1] == '*' || expr[i - 1] == '+' ||
             expr[i - 1] == '-' ||
             expr[i - 1] == '^')) {
            if (i == 0) {
                expr.insert(expr.cbegin(), '0');
                expr.insert(expr.cbegin(), '(');
                i++;
                while (std::isdigit(expr[i]) || expr[i] == '.' || expr[i] == '-') i++;
                expr.insert(i, ")");
            } else {
                expr.insert(expr.cbegin() + i, '0');
                expr.insert(expr.cbegin() + i, '(');
                i++;
                while (std::isdigit(expr[i]) || expr[i] == '.' || expr[i] == '-') i++;
                expr.insert(i, ")");
            }
        }
    }
    for (int i = 0; i < expr.length(); i++) {
        if (((expr[i] == 'n' && expr[i - 1] == 'i') || (expr[i] == 's' && expr[i - 1] == 'o') ||
             (expr[i] == 'g' && expr[i - 1] == 't')) && expr[i + 1] != '(') {
            i++;
            expr.insert(i, "(");
            i++;
            while (std::isdigit(expr[i]) || expr[i] == '.' || expr[i] == '-') i++;
            expr.insert(i, ")");
        }
        if (expr[i] == '^') {
            if (expr[i + 1] == '(') {
                s = i;
                i = i - 1;
                while (std::isdigit(expr[i]) || expr[i] == '(' || expr[i] == ')' || expr[i] == '.' || expr[i] == '-' || isLetter(expr[i]))
                    {i--; if(i==0) break;}
                expr.insert(i+1, "(");
                i = s + 1;
                i += 1;
                while (expr[i] != ')')i++;
                if(expr[i-1] == 'n' || expr[i-1] == 's' || expr[i-1] == 'g') i+=3;
                if(expr[i-3] != 'c' && expr[i-1] == 'g') i--;
                expr.insert(i, ")");
                i = s + 1;
            } else if (expr[i - 1] == ')') {
                s = i;
                i = i - 1;
                while (expr[i] != '(') i--;
                if(expr[i-1] == 'n' || expr[i-1] == 's' || expr[i-1] == 'g') i-=3;
                if(expr[i-3] != 'c' && expr[i-1] == 'g') i++;
                expr.insert(i+1, "(");
                i = s + 1;
                i += 1;
                while (std::isdigit(expr[i]) || expr[i] == '(' || expr[i] == ')' || expr[i] == '.' || expr[i] == '-' || isLetter(expr[i]))
                {i++; if(expr[i] == '-' && std::isdigit(expr[i]-1)) break;}
                expr.insert(i, ")");
                i = s + 1;
            } else {
                s = i;
                i = i - 1;
                while (std::isdigit(expr[i]) || expr[i] == '(' || expr[i] == ')' || expr[i] == '.' || expr[i] == '-' || isLetter(expr[i]))
                    {i--; if(i==0) break;}
                expr.insert(i+1, "(");
                i = s + 1;
                i += 1;
                while (std::isdigit(expr[i]) || expr[i] == '(' || expr[i] == ')' || expr[i] == '.' || expr[i] == '-' || isLetter(expr[i]))
                {i++; if(expr[i] == '-' && std::isdigit(expr[i-1])) break;}
                expr.insert(i, ")");
                i = s + 1;
            }
        }
    }
    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == '*' || expr[i] == '/') {
            if (expr[i + 1] == '(') {
                s = i;
                i = i - 1;
                while (std::isdigit(expr[i]) || expr[i] == '(' || expr[i] == ')' || expr[i] == '.' || expr[i] == '-' || isLetter(expr[i]))
                    {i--; if(i==0) break;}
                expr.insert(i+1, "(");
                i = s + 1;
                i += 1;
                while (expr[i] != ')') i++;
                if(expr[i-1] == 'n' || expr[i-1] == 's' || expr[i-1] == 'g') i+=3;
                if(expr[i-3] != 'c' && expr[i-1] == 'g') i--;
                expr.insert(i, ")");
                i = s + 1;
            } else if (expr[i - 1] == ')') {
                s = i;
                i = i - 1;
                while (expr[i] != '(') i--;
                if(expr[i-1] == 'n' || expr[i-1] == 's' || expr[i-1] == 'g') i-=3;
                if(expr[i-3] != 'c' && expr[i-1] == 'g') i++;
                expr.insert(i+1, "(");
                i = s + 1;
                i += 1;
                while (std::isdigit(expr[i]) || expr[i] == '(' || expr[i] == ')' || expr[i] == '.' || expr[i] == '-' || isLetter(expr[i]) )
                {i++; if(expr[i] == '-' && std::isdigit(expr[i-1])) break;}
                expr.insert(i, ")");
                i = s + 1;
            } else {
                s = i;
                i = i - 1;
                while (std::isdigit(expr[i]) || expr[i] == '(' || expr[i] == ')' || expr[i] == '.' || expr[i] == '-' || isLetter(expr[i]))
                    {i--; if(i==0) break;}
                expr.insert(i+1, "(");
                i = s + 1;
                i += 1;
                while (std::isdigit(expr[i]) || expr[i] == '(' || expr[i] == ')' || expr[i] == '.' || expr[i] == '-' || isLetter(expr[i]))
                {i++; if(expr[i] == '-' && std::isdigit(expr[i-1])) break;}
                expr.insert(i, ")");
                i = s + 1;
            }
        }
    }
    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == '(' && expr[i + 1] == ')') expr.erase(i, 2);
        else if (expr[i] == '(' && expr[i + 2] == ')' && !isLetter(expr[i - 1])) {
            expr.erase(i, 1);
            expr.erase(i + 1, 1);
        }
    }
    for (int pos = 0; pos < expr.length(); pos++) {
        if (buf.find('(') != std::string::npos && buf[0] == '(') {
            while (expr[pos] != ')') {
                if (!std::isdigit(expr[pos]) && expr[pos] != ')' && expr[pos] != 'e') {
                    buf += expr[pos];
                    pos++;
                }
                if (std::isdigit(expr[pos]) || expr[pos]=='e') {
                    count++;
                    expr1 += ' ';
                    while (std::isdigit(expr[pos]) || expr[pos] == '.' || expr[pos] == 'e') {
                        expr1 += expr[pos];
                        pos++;
                    }
                    expr1 += ' ';
                }
                if (count == 2) {
                    if (buf[buf.size() - 1] != '(') {
                        expr1 += buf[buf.size() - 1];
                        expr1 += ' ';
                        buf.erase(buf.size() - 1, 2);
                    }
                    count = 1;
                }
            }
            if (expr[pos] == 's' && expr[pos + 1] == 'i' && expr[pos + 2] == 'n' ||
                expr[pos] == 'c' && expr[pos + 1] == 'o' && expr[pos + 2] == 's' ||
                expr[pos] == 'c' && expr[pos + 1] == 't' && expr[pos + 2] == 'g') {
                buf += ' ';
                buf += expr[pos];
                buf += expr[pos + 1];
                buf += expr[pos + 2];
            }
            if (expr[pos - 1] != 'c' && expr[pos] == 't' && expr[pos + 1] == 'g') {
                buf += ' ';
                buf += expr[pos];
                buf += expr[pos + 1];
            }
            if (expr[pos] == ')') {
                if (buf[0] != '(' && buf.size() == 2 && buf[1] == '(') {
                    expr1 += ' ';
                    expr1 += buf[0];
                    buf.erase();
                }
                if (buf.size() == 2 && !buf.empty() && buf[0] == '(') {
                    expr1 += ' ';
                    expr1 += buf;
                    buf.erase();
                }
                else {int sl = buf.size() - 1;
                if (buf.size() != 1 && buf[sl] != '(') {
                    expr1 += buf[sl];
                    buf.erase(sl, 1);
                    if (buf[0] != '(' && buf.size() != 2)
                        while (buf[sl] != '(') {
                            expr1 += buf[sl];
                            buf.erase(sl, 1);
                            sl--;
                        }
                    else {
                        expr1 += ' ';
                        expr1 += buf[1];
                        buf.erase();
                    }
                } else if (buf[sl] == '(') {
                    if (buf[sl - 1] != '(' && buf.size() != 1) {
                        expr1 += ' ';
                        expr1 += buf[sl - 1];
                        buf.erase(sl - 1, 1);
                    }
                    buf.pop_back();
                } else {
                    expr1 += buf[sl];
                    buf.erase();
                }
                count = 0;
                }
            }
        }
        if (std::isdigit(expr[pos]) || expr[pos]=='e') {
            if (expr[pos - 1] != ' ') expr1 += ' ';
            while (std::isdigit(expr[pos]) || expr[pos] == '.' || expr[pos] == 'e') {
                expr1 += expr[pos];
                pos++;
            }
            if (b) {
                expr1 += ' ';
                expr1 += buf[buf.length() - 1];
                buf.erase(buf.length() - 1, 1);
                expr1 += ' ';
                b = false;
            }
            count++;
            expr1 += ' ';
        }
        if (expr[pos] == 's' && expr[pos + 1] == 'i' && expr[pos + 2] == 'n' ||
            expr[pos] == 'c' && expr[pos + 1] == 'o' && expr[pos + 2] == 's' ||
            expr[pos] == 'c' && expr[pos + 1] == 't' && expr[pos + 2] == 'g'
            ) {
            buf += ' ';
            buf += expr[pos];
            buf += expr[pos + 1];
            buf += expr[pos + 2];
        }
        if (expr[pos - 1] != 'c' && expr[pos] == 't' && expr[pos + 1] == 'g') {
            buf += ' ';
            buf += expr[pos];
            buf += expr[pos + 1];
        }
        if (expr[pos] == '(') {
            while (expr[pos] != ')') {
                if (std::isdigit(expr[pos]) || expr[pos]=='e') {
                    count++;
                    expr1 += ' ';
                    while (std::isdigit(expr[pos]) || expr[pos] == '.' || expr[pos]=='e') {
                        expr1 += expr[pos];
                        pos++;
                    }
                    expr1 += ' ';
                }
                if (count == 2) {
                    if (buf[buf.size() - 1] != '(') {
                        expr1 += buf[buf.length() - 1];
                        buf.erase(buf.size() - 1, 1);
                    }

                    count = 1;
                }
                if (!std::isdigit(expr[pos]) && expr[pos] != ')' && expr[pos] != 'e') {
                    if (expr[pos] == 's' && expr[pos + 1] == 'i' && expr[pos + 2] == 'n' ||
                        expr[pos] == 'c' && expr[pos + 1] == 'o' && expr[pos + 2] == 's' ||
                        expr[pos] == 'c' && expr[pos + 1] == 't' && expr[pos + 2] == 'g'
                        ) {
                        buf += ' ';
                        buf += expr[pos];
                        buf += expr[pos + 1];
                        buf += expr[pos + 2];
                        pos += 3;
                    }
                    if (expr[pos - 1] != 'c' && expr[pos] == 't' && expr[pos + 1] == 'g') {
                        buf += ' ';
                        buf += expr[pos];
                        buf += expr[pos + 1];
                        pos += 2;
                    }
                    else buf += expr[pos];
                    pos++;
                }
            }
            if (expr[pos] == ')') {
                if (!std::isdigit(expr[pos + 1]) && std::isdigit(expr[pos + 2])) { b = true; }
                if (buf[0] != '(' && buf.size() == 2 && buf[1] == '(') {
                    if (!buf.empty()) {
                        expr1 += ' ';
                        expr1 += buf;
                        buf.erase();
                    }
                    expr1 += ' ';
                    expr1 += buf[0];
                    buf.erase();
                } else {
                    int sl = buf.size() - 1;
                    if (buf.size() != 1 && buf[sl] != '(') {
                        expr1 += buf[sl];
                        buf.erase(sl, 1);
                        if (buf[sl - 1] != '(')
                            while (buf[sl] != '(') {
                                expr1 += buf[sl];
                                buf.erase(sl, 1);
                                sl--;
                            }
                        buf.erase(sl, 1);
                    } else if (buf[sl] == '(') {
                        if (buf[sl - 1] != '(' && buf.size() != 1) {
                            expr1 += ' ';
                            expr1 += buf[sl - 1];
                            buf.erase(sl - 1, 1);
                        }
                        buf.pop_back();
                    } else {
                        expr1 += buf[sl];
                        buf.erase();
                    }
                }
                count = 0;
            }
        }
        if (count == 2) {
            if (buf[buf.size() - 1] != '(') {
                expr1 += buf[buf.size() - 1];
                expr1 += ' ';
                buf.erase(buf.size() - 1, 1);
            }
            count = 1;
        }
        if (expr[pos] == '/' || expr[pos] == '*' || expr[pos] == '+' || expr[pos] == '-' || expr[pos] == '^') {
            if (buf[pos - 1] != ' ' && !buf.empty()) buf += ' ';
            buf += expr[pos];
            buf += ' ';
        }
        for (int pos2 = 0; pos2 < expr1.length(); pos2++)
            if (expr1[pos2] == ' ' && expr1[pos2 + 1] == ' ' || expr1[pos2] == '\000' || expr1[pos2] == '(')
                expr1.erase(pos2, 1);
        for (int pos1 = 0; pos1 < buf.length(); pos1++)
            if ((buf[pos1] == ' ' || buf[pos1] == '\000') && pos1!=buf.length()-1)
                buf.erase(pos1, 1);
    }
    if (expr1[0] == ' ') expr1.erase(0, 1);
    for (int pos1 = 0; pos1 < buf.length(); pos1++) {
        if (buf[pos1] == ' ' || buf[pos1] == '\000' || buf[pos1] == '(') {
            buf.erase(pos1, 1);
            buf.insert(pos1, " ");
        }
    }
    if(buf.size()==1 && buf[0] == ' ') buf.erase();
    for (int pos1 = 0; pos1 < buf.length(); pos1++) {
        if (buf[pos1] == ' ' || buf[pos1] == '\000' && !buf.empty()) {
            buf.erase(pos1, 1);
            buf.insert(pos1, " ");
        }
    }
    if(!buf.find('s') && !buf.find('t')) std::reverse(buf.begin(), buf.end());
    expr1 += ' ';
    expr1 += buf;
    for (int pos1 = 0; pos1 < expr1.length(); pos1++) {
        if ((expr1[pos1] == '/' || expr1[pos1] == '*' || expr1[pos1] == '+' || expr1[pos1] == '-' || expr1[pos1] == '^'
        || expr1[pos1] == 'n' || expr1[pos1] == 's' || expr1[pos1] == 'g')
            && (expr1[pos1 + 1] == '/' || expr1[pos1 + 1] == '*' || expr1[pos1 + 1] == '+' || expr1[pos1 + 1] == '-' ||
                expr1[pos1 + 1] == '^' || expr1[pos1+1] == 's' || expr1[pos1+1] == 'c' || expr1[pos1+1] == 't'))
            expr1.insert(pos1+1, " ");
    }
    for (int pos1 = 0; pos1 < expr1.length(); pos1++) {
        if(expr1[pos1] == ' ' && expr1[pos1+1] == ' ') expr1.erase(pos1, 1);
    }
    return expr1;
}