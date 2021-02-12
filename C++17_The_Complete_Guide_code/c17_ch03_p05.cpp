#include <iostream>
#include <vector>
#include <string>
#include <variant>

class Coord
{
private:
    int x;     // x coordinate
    int y;     // y coordinate
public:
    // default constructor:
    Coord() : x{0}, y{0}
    {
    }
    // other constructor:
    Coord(int newx, int newy) : x{newx}, y{newy}
    {
    }

    friend Coord operator+ (Coord c1, Coord c2)    // plus
    {
        return Coord{c1.x + c2.x, c1.y + c2.y};
    }
    friend Coord operator- (Coord c1, Coord c2)    // diff
    {
        return Coord{c1.x - c2.x, c1.y - c2.y};
    }
    Coord operator- () const                       // negate
    {
        return Coord{-x, -y};
    }
    void operator+= (Coord c)                      // +=
    {
        *this = *this + c;  // or: x+=c.x, y+=c.y
    }
    void operator-= (Coord c)                      // +=
    {
        operator+=(-c);     // or as above
    }

    int getX() const
    {
        return x;
    }
    int getY() const
    {
        return y;
    }
    friend std::ostream &operator<< (std::ostream &strm, Coord c)
    {
        return strm << '(' << c.x << ',' << c.y << ')';
    }
};

class Line
{
private:
    Coord from;
    Coord to;
public:
    Line (Coord f, Coord t)
        : from{f}, to{t}
    {
    }

    void move(const Coord &c)
    {
        from += c;
        to += c;
    }

    void draw() const
    {
        std::cout << "line from " << from
                  << " to " << to << '\n';
    }
};

class Rectangle
{
private:
    Coord from;
    Coord to;
public:
    Rectangle (Coord f, Coord t)
        : from{f}, to{t}
    {
    }

    void move(const Coord &c)
    {
        from += c;
        to += c;
    }

    void draw() const
    {
        std::cout << "rectangle from " << from
                  << " to " << to << '\n';
    }
};

class Circle
{
private:
    Coord center;
    int rad;
public:
    Circle (Coord c, int r)
        : center{c}, rad{r}
    {
    }

    void move(const Coord &c)
    {
        center += c;
    }

    void draw() const
    {
        std::cout << "circle at " << center
                  << " with radius " << rad << '\n';
    }
};

// common type of all geometric object types:
using GeoObj = std::variant<Line, Circle, Rectangle>;

// create and initialize a collection of geometric objects:
std::vector<GeoObj> createFigure()
{
    std::vector<GeoObj> f;
    f.push_back(Line{Coord{1, 2}, Coord{3, 4}});
    f.push_back(Circle{Coord{5, 5}, 2});
    f.push_back(Rectangle{Coord{3, 3}, Coord{6, 4}});
    return f;
}

template<typename... Ts>
struct overload : Ts...
{
    using Ts::operator()...;
};

template<typename... Ts>
overload(Ts...) -> overload<Ts...>;

int main()
{
    std::vector<GeoObj> figure = createFigure();
    for (const GeoObj &geoobj : figure)
    {
        std::visit([] (const auto & obj)
        {
            obj.draw();  // polymorphic call of draw()
        },
        geoobj);
    }
}

