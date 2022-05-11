//
// Created by Mason on 2022/5/10.
//

#ifndef CONFIGREADER_CHAMELON_H
#define CONFIGREADER_CHAMELON_H

#include <string>

class Chameleon {
public:
    Chameleon() =default;
    explicit Chameleon(std::string );
    explicit Chameleon(double);
    explicit Chameleon(const char*);

    Chameleon(const Chameleon&);
    Chameleon& operator=(Chameleon const&);

    Chameleon& operator=(double );
    Chameleon& operator=(std::string const&);

public:
    operator std::string() const;
    operator double () const;
private:
    std::string _value;
};

#endif //CONFIGREADER_CHAMELON_H
