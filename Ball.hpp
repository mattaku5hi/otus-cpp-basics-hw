#pragma once
#include <fstream>
#include <vector>

#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball
{
private:
    Point m_center;
    Velocity m_velocity;
    Color m_color;
    double m_radius;
    bool m_isCollidable;
public:
    Ball();
    Ball(Point& center, Velocity& velocity, Color& color, double radius, const bool isCollidable);
    // Ball& operator=(const Ball&)=Ball(Point center, Velocity velocity, Color color, double radius, const bool isCollidable);
    ~Ball() = default;
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool getIsCollidable(void) const;
};

std::istream& operator>>(std::istream& stream, Ball& ball);
