#pragma once

#include <cmath>
#include <istream>

#include "Point.hpp"

class Velocity {
  public:
    inline Velocity() = default;

    // TODO: комментарии
    inline Velocity(double abs, double angle) {
        const double x = std::cos(angle);
        const double y = std::sin(angle);
        vec = Point{x, y} * abs;
    }

    inline Velocity(const Point& vector) {
        setVector(vector);
    }

    inline void setVector(const Point& vector) {
        vec = vector;
    }

    inline Point vector() const {
        return vec;
    }

    friend std::istream& operator>>(std::istream& is, Velocity& velocity)
    {
        Point velocityVector{0.0, 0.0};
        is >> velocityVector.x >> velocityVector.y;
        velocity.setVector(velocityVector);
        return is;
    }

  private:
    Point vec;
};
