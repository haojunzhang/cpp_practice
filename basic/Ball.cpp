#include <iostream>
#include <string>
#include "Ball.h"
using namespace std;

Ball::Ball()
{
    color = "BLACK";
    radius = 10.5;
}

Ball::Ball(string color, double radius)
{
    this->color = color;
    this->radius = radius;
}

void Ball::set_color(string color)
{
    this->color = color;
}

string Ball::get_color()
{
    return color;
}

void Ball::set_radius(double radius)
{
    this->radius = radius;
}

double Ball::get_radius()
{
    return radius;
}

double Ball::get_area()
{
    return radius * radius * 3.14;
}

void Ball::show_info()
{
    cout << "Ball info" << endl;
    cout << "Color is " << get_color() << endl;
    cout << "Radius is " << get_radius() << endl;
    cout << "Area is " << get_area() << endl;
}