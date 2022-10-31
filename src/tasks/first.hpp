#pragma once
#include <fstream>
#include "../containers/forward_list.hpp"
#include <sstream>
LMP::forward_list read_and_sort(std::stringstream& ss);

void task_1(LMP::forward_list& forward_list, std::stringstream& out);