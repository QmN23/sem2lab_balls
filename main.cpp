#include <SFML/Graphics.hpp>
#include <iostream>

class Ball {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float acceleration; 
    float damping; 
    float air_resistance;
    float mass;

public:
    // Конструктор
    Ball(float radius, sf::Color color, sf::Vector2f position, sf::Vector2f velocity, float acceleration, float damping, float air_resistance, float mass)
        : velocity(velocity), acceleration(acceleration), damping(damping), air_resistance(air_resistance), mass(mass)
    {
        shape.setRadius(radius);
        shape.setFillColor(color);
        shape.setPosition(position);
    }

    void update(float deltaTime) {
        // Вычисление ускорения с учетом ускорения свободного падения и сопротивления воздуха
        float force = mass * acceleration - mass * air_resistance * velocity.y;
        float a = force / mass;

        velocity.y += a * deltaTime;

        // Перемещение шара
        shape.move(velocity * deltaTime);

        if (shape.getPosition().y + shape.getRadius() * 2 >= 1000) {
            shape.setPosition(shape.getPosition().x, 1000 - shape.getRadius() * 2); 
            velocity.y = -velocity.y * damping; 
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1000), "Три шара");

    sf::Vector2f initialVelocity(0.f, 200.f); 
    float air_resistance = 0.1f;
    float acceleration = 15.f; // Ускорение свободного падения
    float damping = 0.5f; // Коэффициент затухания
    float mass1 = 1.0f; // Масса первого шара
    float mass2 = 2.0f; // Масса второго шара
    float mass3 = 3.0f; // Масса третьего шара
    Ball ball1(30.f, sf::Color::Red, sf::Vector2f(300.f, 100.f), initialVelocity, acceleration, damping, air_resistance, mass1);
    Ball ball2(60.f, sf::Color::Green, sf::Vector2f(700.f, 100.f), initialVelocity, acceleration, damping, air_resistance, mass2);
    Ball ball3(90.f, sf::Color::Blue, sf::Vector2f(1100.f, 100.f), initialVelocity, acceleration, damping, air_resistance, mass3);

    sf::Clock clock;
    // Основной игровой цикл
    while (window.isOpen()) {
        // Обработка событий
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Обновление шаров
        float deltaTime = clock.restart().asSeconds();
        ball1.update(deltaTime);
        ball2.update(deltaTime);
        ball3.update(deltaTime);

        // Очистка экрана
        window.clear(sf::Color::White);

        // Отрисовка шаров
        ball1.draw(window);
        ball2.draw(window);
        ball3.draw(window);

        // Обновление экрана
        window.display();
    }

    return 0;
}
