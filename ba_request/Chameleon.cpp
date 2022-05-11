//
// Created by Mason on 2022/5/10.
//
#include <string>

#include "Chamelon.h"

Chameleon::Chameleon(std::string value):_value(std::move(value)) {

}

Chameleon::Chameleon(const char *c):_value(c){

}

Chameleon::Chameleon(double d):_value(std::to_string(d)) {
}

Chameleon::Chameleon(const Chameleon &other) {
    _value = other._value;
}

Chameleon &Chameleon::operator=(double d) {
    _value = std::to_string(d);
    return *this;
}

Chameleon &Chameleon::operator=(const std::string & s) {
    _value = s;
    return *this;
}


Chameleon& Chameleon::operator=(Chameleon const& other) = default;

Chameleon::operator std::string() const {
    return _value;
}

Chameleon::operator double() const {
    return std::stod(_value);
}