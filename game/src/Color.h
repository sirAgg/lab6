#ifndef __COLOR_H_
#define __COLOR_H_

struct Color
{
    unsigned char a,b,g,r;

    Color() {}
    Color(unsigned int c)
    {
        r = *((unsigned char*)&c+3);
        g = *((unsigned char*)&c+2);
        b = *((unsigned char*)&c+1);
        a = *((unsigned char*)&c+0);
    }

    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
        :r(r),g(g),b(b),a(a) {}

    unsigned int toInt() const
    {
        return *((unsigned int*)this);
    }

    Color scale(float s)
    {
        return Color{
            (unsigned char)(r * s), 
            (unsigned char)(g * s), 
            (unsigned char)(b * s), 
            (unsigned char)(a * s), 
        };
    }
};

#endif // __COLOR_H_
