#ifndef POINT_2D
#define POINT_2D value

#include <string>

class Point2D
{
public:
    Point2D();
    Point2D(float nx, float ny);
    Point2D(const Point2D& other);

    float distance_to(Point2D& other);
    std::string to_string();

    Point2D operator+ (const Point2D& other);
    Point2D operator- (const Point2D& other);
    void operator= (const Point2D& other);
    bool operator== (const Point2D& other);

    inline float get_x() {return x;}
    inline float get_y() {return x;}

    inline void set_x(float _x) { x=_x; }
    inline void set_y(float _y) { y=_y; }

private:
    float x,y;
};

#endif /* ifndef POINT_2D */
