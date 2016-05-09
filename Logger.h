#pragma once

#include <iostream>

#define LOG(chain) std::cout << chain << " [" << __FILE__ << ":" << __LINE__ << "]" << std::endl;
