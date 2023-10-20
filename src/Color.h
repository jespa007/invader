#pragma once

struct Color{
    uint8_t r,g,b;
    Color(){
        r=0;
        g=0;
        b=0;
    }
    friend bool operator==(const Color & _c1, const Color & _c2){
        return _c1.r==_c2.r
               && _c1.g==_c2.g
               && _c1.b==_c2.b;
    }

    friend bool operator!=(const Color & _c1, const Color & _c2){
        return !(_c1==_c2);
    }

};