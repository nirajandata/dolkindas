module;
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>

export module modenv;

[[nodiscard]] auto trim(std::string &line) noexcept {
    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
    std::array<int, 4> locate;
    size_t count = 0;
    for (size_t i = 0; i < line.size(); i++) {
        if (line[i] == '\'' || line[i] == '"') {
            locate[count] = i + 1;
            if (count & 1)
                locate[count]--;

            count++;
        }
    }
    std::string key, value;
    key = line.substr(locate[0], locate[1] - locate[0]);
    value = line.substr(locate[2], locate[3] - locate[2]);
    return std::array<std::string, 2>{key, value};
}

export namespace env {
    [[nodiscard]] auto getenv(std::string path = ".env") noexcept {
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