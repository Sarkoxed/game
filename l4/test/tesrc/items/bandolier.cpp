// sarkoxed //
#include "bandolier.hpp"
#include <stdexcept>

void Bandolier::operator-=(const unsigned int right){
    if(right > a_cursize){
        throw std::invalid_argument("not enough ammo");
    }
    a_cursize -= right;
}

void Bandolier::operator+=(Bandolier& right){
    if(a_bullets == right.a_bullets){
        unsigned int ext = a_cursize + right.a_cursize;
        a_cursize = (ext >= a_maxsize) ? a_maxsize : ext;
        
        right.a_cursize = 0;
        return;
    }
    throw std::invalid_argument("wrong bullets");
}

void Bandolier::operator+=(const unsigned int right){
    unsigned int ext = a_cursize + right;
    a_cursize = (ext >= a_maxsize)?a_maxsize:ext;
}

