module;
import std;

export module exo5;

export namespace exo5 {
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

    class Polygon : public Shape {
    public:
        Polygon(const std::initializer_list<double> sides)
            : sides{sides} {}

        double Perimeter() const override {
            return std::accumulate(sides.begin(), sides.end(), 0.0);
        }

        std::string ToString() const override {
            return std::format("Polygon(sides={}, perimeter={:.2f})", sides.size(), Perimeter());
        }

    protected:
        std::vector<double> sides;
    };

    class Rectangle : public Polygon {
    public:
        Rectangle(const double width, const double height)
            : Polygon{width, height, width, height} {}

        std::string ToString() const override {
            return std::format("Rectangle(width={:.2f}, height={:.2f}, perimeter={:.2f})",
                               sides[0], sides[1], Perimeter());
        }
    };

    class Square : public Rectangle {
    public:
        explicit Square(const double side)
            : Rectangle{side, side} {}

        std::string ToString() const override {
            return std::format("Square(side={:.2f}, perimeter={:.2f})", sides[0], Perimeter());
        }
    };

    class Application {
    public:
        Application() {
            const auto circle = Circle{1.2};
            const auto polygon = Polygon{1.0, 2.0, 3.0};
            const auto rectangle = Rectangle{1.0, 2.0};
            const auto square = Square{1.0};
            std::println("{}", circle.ToString());
            std::println("{}", polygon.ToString());
            std::println("{}", rectangle.ToString());
            std::println("{}", square.ToString());
        }
    };
}
