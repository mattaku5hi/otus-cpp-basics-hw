#include <cmath>
#include <iostream>

#include "Ball.hpp"


/* easy ctor */
Ball::Ball() :
            m_center(Point{0.0, 0.0}), m_velocity(Velocity{0.0, 0.0}), m_color(Color{0.0, 0.0, 0.0}),
            m_radius{0.0}, m_isCollidable{false}
{

}

/* complete ctor */
Ball::Ball(Point& center, Velocity& velocity, Color& color, double radius, const bool isCollidable) :
                m_center(center), m_velocity(velocity), m_color(color), m_radius(radius), m_isCollidable(isCollidable)
{

}


/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) {
    this->m_velocity = velocity;
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    // TODO: место для доработки
    return this->m_velocity;
}

bool Ball::getIsCollidable() const
{
    return this->m_isCollidable;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    // TODO: место для доработки
    painter.draw(m_center, m_radius, m_color);
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    // TODO: место для доработки
    this->m_center = center;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    // TODO: место для доработки
    return this->m_center;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
    // TODO: место для доработки
    return this->m_radius;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    // TODO: место для доработки
    double mass = M_PI * std::pow(this->m_radius, 3) * 4.00 / 3.00;     
    return mass;
}


std::istream& operator>>(std::istream& stream, Ball& ball)
{
    Point center;
    Velocity velocity;
    Color color;
    double radius;
    bool isCollidable;

    if(stream >> center >> velocity >> color >> radius >> std::boolalpha >> isCollidable)
    {
        ball = Ball(center, velocity, color, radius, isCollidable);
    }
    else
    {
        stream.setstate(std::ios::failbit);
    }

    return stream;
}
