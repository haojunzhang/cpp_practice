#include <string>
using namespace std;

class Ball
{ // 2D ball
private:
    string color;
    double radius;

public:
    Ball();
    Ball(string, double);

    void set_color(string);
    string get_color();

    void set_radius(double);
    double get_radius();

    double get_area();

    void show_info();
};