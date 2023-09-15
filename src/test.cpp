//
// Created by kira on 9/15/23.
//
#include "../lib/getenv.hpp"

int main(){
    std::map<std::string,std::string> h= get_env_fromFile();
    std:: cout << h["BOT"] <<'\n';
    std::cout <<h["CF_ID"];
    std::cout <<h["HOOK"];
}
