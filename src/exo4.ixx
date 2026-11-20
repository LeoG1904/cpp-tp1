module;
import std;

export module exo4;

export namespace exo4 {
    class Shape {
    public:
        virtual ~Shape() = default;
        virtual double Perimeter() const = 0;
        virtual std::string ToString() const = 0;
    };

    class Circle : public Shape {
    public:
        explicit Circle(const double radius)
            : radius{radius} {}

        double Perimeter() const override {
            return 2.0 * std::numbers::pi * radius;
        }

        std::string ToString() const override {
            return std::format("Circle(radius={:.2f}, perimeter={:.2f})", radius, Perimeter());
        }

    private:
        double radius;
    };

    class Application {
    public:
        Application() {
            const auto circle = Circle{1.2};
            std::println("{}", circle.ToString());
        }
    };
}
