//
// Created by User on 21.10.2022.
//
#include <algorithm>
#include <string>
#include <iostream>

bool isLetter(char x) {
    return (x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z');
}

int priority(char &m) {
    if (m == '+' || m == '-') return 1;
    if (m == '*' || m == '/') return 2;
    if (m == '^' || m == '/') return 3;
    if (isLetter(m) && m != 'e') return 4;
    else return -1;
}

std::string viewchange(std::string &expr) {
    std::string buf;
    std::string expr1;
    bool ss = false;
    std::string x;
    int c = 0;
    int c1 = 0;
    int c2 = 0;
    bool c3 = false;
    for (char i : expr) if (std::isdigit(i) || i == 'x') c3 = true;
    if (!c3) return "Incorrect input!";
    for (int i = 0; i < expr.length(); i++) if (expr[i] == ' ') expr.erase(i, 1);
    for (int i = 0; i < expr.length(); i++) if (expr[i] == ',') expr.replace(i, 1, ".");
    for (int i = 0; i < expr.length(); i++)
        if (expr[i] == 'e' && expr[i + 1] == 'x' && expr[i + 2] == 'p') {
            expr.erase(i + 1, 2);
            expr.insert(i + 1, "^");
        }
    for (char i: expr) {
        if (i == '(') c1++;
        if (i == ')') c2++;
    }
    if (expr.find_first_not_of("sincotgex0123456789^+/()*-.") != std::string::npos) {
        return "Incorrect input!";
    }
    if (c1 != c2) return "Incorrect input!";
    for (int i = 0; i < expr.length(); i++) {
        if ((expr[i] == '/' || expr[i] == '*' || expr[i] == '+' || expr[i] == '-' || expr[i] == '^') &&
            expr[i] == expr[i + 1])
            return "Incorrect input!";
        else if (isLetter(expr[i]) && expr[i]!='e') {
            std::string buff;
            while (isLetter(expr[i])) {
                buff += expr[i];
                i++;
            }
            if ((buff == "ctg" || buff == "tg" || buff == "sin" || buff == "cos" || buff == "e" || buff == "ctgx" ||
                 buff == "tgx" ||
                 buff == "sinx" || buff == "cosx" || buff == "ex") &&
                (std::isdigit(expr[i]) || expr[i] == '(' || buff[buff.length() - 1] == 'x'))
                c++;
            else if (buff == "x" &&
                     (expr[i] == '/' || expr[i] == '*' || expr[i] == '+' || expr[i] == '-' || expr[i] == '^' ||
                      expr[i] == '('))
                c++;
            else return "Incorrect input!";
        }
        if (expr[i] == '/' || expr[i] == '*' || expr[i] == '+' || expr[i] == '-' ||
            expr[i] == '^' || expr[i] == '(' || expr[i] == ')' || expr[i] == 'c' || expr[i] == 's' || expr[i] == 'i' ||
            expr[i] == 'n' || expr[i] == 'g' || expr[i] == 't')
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
        if (expr[i] == '(' && std::isdigit(expr[i - 1]) && i != 0) expr.insert(i, "*");
        if (expr[i] == ')' && std::isdigit(expr[i + 1])) expr.insert(i + 1, "*");
    }
    if (c == 0) return "Incorrect input!";
    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == 'x' && expr[i - 1] != 'e') {
            if (x.empty()) {
                std::cout << "Enter x: " << std::endl;
                std::cin >> x;
            }
            for (char ll : x) {
                if (std::isdigit(ll) || ll == '.' || ll == '-') ss = true;
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
                while (std::isdigit(expr[i]) || expr[i] == '.' || (expr[i] == '-' && std::isdigit(expr[i+1]))) i++;
                expr.insert(i, ")");
            } else {
                expr.insert(expr.cbegin() + i, '0');
                expr.insert(expr.cbegin() + i, '(');
                i++;
                while (std::isdigit(expr[i]) || expr[i] == '.' || (expr[i] == '-' && std::isdigit(expr[i+1]))) i++;
                expr.insert(i, ")");
            }
        }
    }
    size_t bf = expr.length();
    for (int i = 0; i < bf; i++) {
        if (((expr[i] == 'n' && expr[i - 1] == 'i') || (expr[i] == 's' && expr[i - 1] == 'o') ||
             (expr[i] == 'g' && expr[i - 1] == 't'))) {
            if (expr[i + 1] == '(') {
                i++;
                while (expr[i] != ')' && i != expr.length() - 1) { i++; if(expr[i]=='-' && std::isdigit(expr[i-1])) break;}
            }
            else {
                i++;
                expr.insert(i, "(");
                i++;
                if(expr[i]=='-') expr.insert(i, "0");
                i++;
                while (std::isdigit(expr[i]) || expr[i] == '.' || (expr[i] == '-' && !std::isdigit(expr[i-1]))) i++;
                expr.insert(i, ")");
            }
        }
        bf=expr.length();
    }
    for (int i = 0; i < bf; i++) {
        if(std::isdigit(expr[i]) && (isLetter(expr[i-1]) || expr[i-1]==')')) {expr.insert(i-1,"*"); i++;}
        if(std::isdigit(expr[i]) && (isLetter(expr[i+1]) || expr[i+1]=='(')) {expr.insert(i+1,"*"); i++;}
        bf=expr.length();
    }
    for (int pos = 0; pos < expr.length(); pos++) {
        if (std::isdigit(expr[pos]) || expr[pos] == 'e') {
            if (pos != 0) expr1 += ' ';
            while (std::isdigit(expr[pos]) || expr[pos] == '.' || expr[pos] == 'e') {
                expr1 += expr[pos];
                pos++;
            }
            pos--;
            expr1 += ' ';
        } else if (expr[pos] == '(') buf += expr[pos];
        else if (expr[pos] == ')') {
            while (buf[buf.length() - 1] != '(' || buf.empty()) {
                if (isLetter(buf[buf.length() - 1])) {
                    expr1 += ' ';
                    if (isLetter(buf[buf.length() - 3])) {
                        expr1 += buf[buf.length() - 3];
                        expr1 += buf[buf.length() - 2];
                        expr1 += buf[buf.length() - 1];
                        buf.pop_back();
                        buf.pop_back();
                        buf.pop_back();
                        buf.pop_back();
                    }
                    else {
                        expr1 += buf[buf.length() - 2];
                        expr1 += buf[buf.length() - 1];
                        buf.pop_back();
                        buf.pop_back();
                        buf.pop_back();
                    }
                }
                else if(!buf.empty()){
                    expr1 += ' ';
                    expr1 += buf[buf.length() - 1];
                    buf.pop_back();
                }
                if(buf.empty()) break;
            }
            if(!buf.empty())buf.pop_back();
            if(expr[pos+1]==')') pos++;
        } else if (expr[pos] == '+' || expr[pos] == '-' || expr[pos] == '*' || expr[pos] == '/' || expr[pos] == '^') {
            if (buf.empty() || (buf.size() == 1 && buf[0] == '(')) buf += expr[pos];
            else {
                int j = priority(expr[pos]);
                if (priority(buf[buf.length() - 1]) == j) {
                    expr1 += ' ';
                    if (!isLetter(buf[buf.length() - 1])) {
                        expr1 += buf[buf.length() - 1];
                        buf.pop_back();
                        buf += expr[pos];
                    } else {
                        if (isLetter(buf[buf.length() - 3])) {
                            expr1 += buf[buf.length() - 3];
                            expr1 += buf[buf.length() - 2];
                            expr1 += buf[buf.length() - 1];
                            buf.pop_back();
                            buf.pop_back();
                            buf.pop_back();
                            buf += expr[pos];
                            buf += expr[pos + 1];
                            if (isLetter(expr[pos + 2]))buf += expr[pos + 2];
                        } else {
                            expr1 += buf[buf.length() - 2];
                            expr1 += buf[buf.length() - 1];
                            buf.pop_back();
                            buf.pop_back();
                            buf += expr[pos];
                            buf += expr[pos + 1];
                            if (isLetter(expr[pos + 2]))buf += expr[pos + 2];
                        }
                    }
                } else {
                    while (priority(buf[buf.length() - 1]) >= j) {
                        expr1 += ' ';
                        if (isLetter(buf[buf.length() - 1])) {
                            std::string b;
                            while (isLetter(buf[buf.length() - 1])) {
                                if (buf[buf.length() - 1] == '(') break;
                                b += buf[buf.length() - 1];
                                buf.pop_back();
                            }
                            std::reverse(b.begin(), b.end());
                            expr1 += b;
                        }
                        else {
                            expr1 += buf[buf.length() - 1];
                            buf.pop_back();
                        }
                    }
                    buf += expr[pos];
                }
            }
        }
        if (expr[pos] == 's' && expr[pos + 1] == 'i' && expr[pos + 2] == 'n' ||
            expr[pos] == 'c' && expr[pos + 1] == 'o' && expr[pos + 2] == 's' ||
            expr[pos] == 'c' && expr[pos + 1] == 't' && expr[pos + 2] == 'g') {
            buf += expr[pos];
            buf += expr[pos + 1];
            buf += expr[pos + 2];
        }
        if (expr[pos - 1] != 'c' && expr[pos] == 't' && expr[pos + 1] == 'g') {
            buf += expr[pos];
            buf += expr[pos + 1];
        }
    }
    for(int lll = 0; lll<buf.length()-1; lll++){
        if(buf[lll]=='(') buf.erase(lll,1);
    }
    if (!buf.empty()) {
        std::reverse(buf.begin(), buf.end());
        for (int lk = 0; lk < buf.size(); lk++) {
            if (buf[lk] == 'n' && buf[lk + 1] == 'i' && buf[lk + 2] == 's') {
                buf[lk] = 's';
                buf[lk + 2] = 'n';
                lk += 3;
            }
            else if (buf[lk] == 's' && buf[lk + 1] == 'o' && buf[lk + 2] == 'c') {
                buf[lk] = 'c';
                buf[lk + 2] = 's';
                lk += 3;
            }
            else if (buf[lk] == 'g' && buf[lk + 1] == 't' && buf[lk + 2] == 'c') {
                buf[lk] = 'c';
                buf[lk + 2] = 'g';
                lk += 3;
            }
            else if (buf[lk] == 'g' && buf[lk + 1] == 't' && buf[lk + 2] != 'c') {
                buf[lk] = 't';
                buf[lk + 1] = 'g';
                lk += 2;
            }
            if (!std::isdigit(buf[lk]) && !isLetter(buf[lk])) {
                buf.insert(lk, " ");
                lk++;
            }
        }
    }
    expr1 += ' ';
    expr1 += buf;
    return expr1;
}