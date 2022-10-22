//
// Created by User on 18.10.2022.
//
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
bool isnum(std::string& k) {
    int c = 0;
    int buf = 0;
    while (std::isdigit(k[buf]) || k[buf] == '.') {c++; buf++;}
    if(buf==k.length()) return true;
    else return false;
}
std::string calc(std::string &l) {
    std::vector<std::string> result;
    std::vector<double> m;
    double buf;
    std::istringstream iss(l);
    for (std::string w; iss >> w;)
        result.push_back(w);
        for (int i = 0; i < result.size(); i++) {
            std::string buff = result[i];
            if(buff=="e") buff="2.7182818";
            if(isnum(buff)) m.push_back(std::stod(buff));
            else {
                if(buff == "+"){
                    double a,b;
                    a = m.at(m.size()-2);
                    b = m.at(m.size()-1);
                    buf = a+b;
                    m.pop_back();
                    m.pop_back();
                    m.push_back(buf);
                }
                else if(buff == "-"){
                        double a,b;
                        a = m.at(m.size()-2);
                        b = m.at(m.size()-1);
                        buf = a-b;
                        m.pop_back();
                        m.pop_back();
                        m.push_back(buf);
                    }
                else if(buff == "*"){
                    double a,b;
                    a = m.at(m.size()-2);
                    b = m.at(m.size()-1);
                    buf = a*b;
                    m.pop_back();
                    m.pop_back();
                    m.push_back(buf);
                }
                else if(buff == "/"){
                    double a,b;
                    a = m.at(m.size()-2);
                    b = m.at(m.size()-1);
                    if(b==0) return "Divide on 0 error!";
                    buf = a/b;
                    m.pop_back();
                    m.pop_back();
                    m.push_back(buf);
                }
                else if(buff == "^"){
                    double a,b;
                    a = m.at(m.size()-2);
                    b = m.at(m.size()-1);
                    buf = pow(a,b);
                    m.pop_back();
                    m.pop_back();
                    m.push_back(buf);
                }
                else if(buff == "sin"){
                    double a;
                    a = m.at(m.size()-1);
                    buf = sin(a);
                    m.pop_back();
                    m.push_back(buf);
                }
                else if(buff == "cos"){
                    double a;
                    a = m.at(m.size()-1);
                    buf = cos(a);
                    m.pop_back();
                    m.push_back(buf);
                }
                else if(buff == "tg"){
                    double a;
                    a = m.at(m.size()-1);
                    if(cos(a) == 0) return "Cos = 0 error!";
                    buf = sin(a)/cos(a);
                    m.pop_back();
                    m.push_back(buf);
                }
                else if(buff == "ctg"){
                    double a;
                    a = m.at(m.size()-1);
                    if(sin(a) == 0) return "Sin = 0 error!";
                    buf = cos(a)/sin(a);
                    m.pop_back();
                    m.push_back(buf);
                }
            }
        }
        if(m.at(0) == floor(m.at(0))){
            int b = m.at(0);
            return std::to_string(b);
        }
        return std::to_string(m.at(0));
}
