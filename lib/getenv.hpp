//
// Created by nirarara on 6/25/23.
//

#ifndef CPP_ENV_VAR_GETENV_H
#define CPP_ENV_VAR_GETENV_H

#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <tuple>

std::tuple<std::string, std::string> trim(std::string &line);
std::map<std::string, std::string> get_env_fromFile(std::string path = ".env");

// implementing for os version is very messy, so for this, just use
// std::getenv()

#endif // CPP_ENV_VAR_GETENV_H