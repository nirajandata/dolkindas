#include "getenv.hpp"

std::tuple<std::string, std::string> trim(std::string &line) {
    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
    std::array<int, 4> locate;
    int count = 0;
    for (size_t i = 0; i < line.size(); i++) {
        if (line[i] == '\'' or line[i] == '"') {
            locate[count] = i + 1;
            if (count & 1)
                locate[count]--;

            count++;
        }
    }
    assert(
            ("Please! Only put quotes in the proper place, not inside key or value" &&
             count == 4));
    std::string key, value;
    key = line.substr(locate[0], locate[1] - locate[0]);
    value = line.substr(locate[2], locate[3] - locate[2]);
    return make_pair(key, value);
}
std::map<std::string, std::string> get_env_fromFile(std::string path) {
    std::ifstream file(path);
    // we store the key and value in dictionary called baniya
    std::map<std::string, std::string> baniya;
    std::string line;

    while (getline(file, line)) {
        std::string key, value;
        std::tie(key, value) = trim(line);
        baniya[key] = value;
        // std::cout << key << "|"<< value << std::endl;
    }

    file.close();
    return baniya;
}