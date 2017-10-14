#pragma once
#ifndef framing_h
#define framing_h

#include <string>;
#include <vector>;

std::string::size_type width(const std::vector<std::string>& v);
std::vector<std::string> frame(const std::vector<std::string>& v);

#endif
