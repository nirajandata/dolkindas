module;
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>

export module modenv;

[[nodiscard]] auto trim(std::string &line) noexcept {

    std::string key, value;
    size_t i=1;
    for(int j=0; j<4; j++) {
        while(i<line.size()-1 && line[i]!='"' && line[i]!='\'') {
            if(line[i]=='=' || line[i]==' '){
                i++;
                continue;
            }
            value+=line[i];
            i++;
        }
        if(j==1)
            std::swap(key,value);
        i++;
    }
    return std::array<std::string, 2>{key, value};
}

export namespace env {
    [[nodiscard]] std::map<std::string,std::string> getenv(std::string path = ".env") noexcept {
        std::ifstream file(path);
        // we store the key and value in dictionary called baniya
        std::map<std::string, std::string> baniya;
        std::string line;

        while (getline(file, line)) {
            std::array<std::string, 2> temp{trim(line)};
            baniya.emplace(temp[0], temp[1]);
        }
        return baniya;
    }
}; // namespace env