
#include <fstream>
#include <iostream>

#include "Ball.hpp"
#include "Painter.hpp"
#include "World.hpp"

// Длительность одного тика симуляции.
// Подробнее см. update()
// Изменять не следует
static constexpr double timePerTick = 0.001;

/**
 * Конструирует объект мира для симуляции
 * @param worldFilePath путь к файлу модели мира
 */
World::World(const std::string& worldFilePath) {

    std::ifstream stream(worldFilePath);
    /**
     * TODO: хорошее место для улучшения.
     * Чтение границ мира из модели
     * Обратите внимание, что здесь и далее мы многократно
     * читаем в объект типа Point, последовательно
     * заполняя координаты x и у. Если что-то делаем
     * многократно - хорошо бы вынести это в функцию
     * и не дублировать код...
     */
    // stream >> topLeft.x >> topLeft.y >> bottomRight.x >> bottomRight.y;
    Point topLeft{0.0, 0.0};
    Point bottomRight{0.0, 0.0};
    stream >> topLeft >> bottomRight;
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
    physics.setWorldBox(topLeft, bottomRight);

    while(stream >> std::ws && stream.eof() == false)
    {
        Ball ball;
        if(stream >> ball)
        {
            balls.push_back(ball);
        }
        else if(stream.eof() == true)
        {
            /* Ok, we've just reached the end of file */
            break;
        }
        else
        {
            std::cerr << "Error: failed to completely parse input stream in function: " << __func__ << std::endl;
            stream.clear();
            stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            /* Better to raise an exception but we won't do it here */
            return;
        }
    }
}

/// @brief Отображает состояние мира
void World::show(Painter& painter) const {
    // Рисуем белый прямоугольник, отображающий границу
    // мира
    painter.draw(topLeft, bottomRight, Color(1, 1, 1));

    // Вызываем отрисовку каждого шара
    for (const Ball& ball : balls) {
        ball.draw(painter);
    }
}

/// @brief Обновляет состояние мира
void World::update(double time) {
    /**
     * В реальном мире время течет непрерывно. Однако
     * компьютеры дискретны по своей природе. Поэтому
     * симуляцию взаимодействия шаров выполняем дискретными
     * "тиками". Т.е. если с момента прошлой симуляции
     * прошло time секунд, time / timePerTick раз обновляем
     * состояние мира. Каждое такое обновление - тик -
     * в physics.update() перемещаем шары и обрабатываем
     * коллизии - ситуации, когда в результате перемещения
     * один шар пересекается с другим или с границей мира.
     * В общем случае время не делится нацело на
     * длительность тика, сохраняем остаток в restTime
     * и обрабатываем на следующей итерации.
     */

    // учитываем остаток времени, который мы не "доработали" при прошлом update
    time += restTime;
    const auto ticks = static_cast<size_t>(std::floor(time / timePerTick));
    restTime = time - double(ticks) * timePerTick;

    physics.update(balls, ticks);
}