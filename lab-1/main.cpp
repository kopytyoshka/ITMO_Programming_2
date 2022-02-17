#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

double const pi = 3.14159265358979;

struct IPerimeterComputable {
    virtual double perimeter() const = 0;
};

struct IAreaComputable {
    virtual double area() const = 0;
};

class Point {
    double _x;
    double _y;

public:
    Point(double x = 0.0, double y = 0.0) : _x{ x }, _y{ y } {} //constructor
    Point(const Point& point) : _x{ point._x }, _y{ point._y } {} //copying constructor
    Point& operator=(const Point& point) {
        _x = point._x;
        _y = point._y;
        return *this;
    }

    double x() const {
        return _x;
    }
    double y() const {
        return _y;
    }

    bool operator==(const Point& other) const {
        return _x == other._x and _y == other._y;
    }
    bool operator!=(const Point& other) const {
        return !operator==(other);
    }

    Point operator-(const Point& other) const {
        return Point{ _x - other._x, _y - other._y };
    }
    Point operator+(const Point& other) const {
        return Point{ _x + other._x, _y + other._y };
    }

    friend std::ostream& operator<<(std::ostream& out, const Point& point);
};
using PointList = std::vector<Point>;

std::ostream& operator<<(std::ostream& out, const Point& point) {
    return out << "(" << point._x << ";" << point._y << ")";
}

class Vector {
    double _x;
    double _y;

public:
    Vector(double x, double y)
            : _x{ x }
            , _y{ y } {
    }

    Vector(const Point& point)
            : _x{ point.x() }
            , _y{ point.y() } {
    }
    Vector(const Point& first, const Point& second)
            : _x{ (second - first).x() }
            , _y{ (second - first).y() } {
    }


    Vector(const Vector&) = default;
    ~Vector() = default;

    double x() const {
        return _x;
    }
    double y() const {
        return _y;
    }

    [[nodiscard]] double length() const {
        return std::sqrt(std::pow(_x, 2) + std::pow(_y, 2));
    }

    friend std::ostream& operator<<(std::ostream& out, const Vector& vector);
};

std::ostream& operator<<(std::ostream& out, const Vector& vector) {
    return out << "(" << vector._x << ";" << vector._y << ")";
}

class Polyline : public IPerimeterComputable {
protected:
    PointList m_points;
    static double distance(const Point& a, const Point& b) {
        return sqrt(pow((a.x() - b.x()), 2) + pow((a.y() - b.y()), 2));
    };
public:
    Polyline(const PointList& list) : m_points{ list } {
    }
    Polyline(const Polyline& other) : m_points{ other.m_points } {
    }
    Polyline& operator=(const Polyline& other) {
        m_points = other.m_points;
        return *this;
    }

    double perimeter() const override {
        double value = 0.;
        if (m_points.empty())
            return value;

        for (size_t i = 0; i < m_points.size() - 1; ++i) {
            value += Vector{ m_points[i], m_points[i + 1] }.length();
        }
        return value;
    }
};

class ClosedPolyline : public Polyline {
public:
    ClosedPolyline(const PointList& points) : Polyline{ points } {
    }
    ClosedPolyline(const ClosedPolyline& other) : Polyline(other.m_points) {
    }
    ClosedPolyline& operator=(const ClosedPolyline& other) {
        m_points = other.m_points;
        return *this;
    }

    double perimeter() const override {
        return Polyline::perimeter() + Vector{ m_points.back() - m_points.front() }.length();
    }
};

class Polygon : public ClosedPolyline {
public:
    Polygon(const PointList& points) : ClosedPolyline{ points } {
        std::vector<std::pair<Vector, Vector>> angles_points;

        double sum_angles = 0;
        for (auto& pair : angles_points) {
            double const value = (pair.first.x() * pair.second.x() + pair.first.y() * pair.second.y());
            double const lengths = (pair.first.length() * pair.second.length());
            double const cos = -(value / lengths);

            double const angle = std::acos(cos) * 180 / pi;

            sum_angles += angle;
        }

    }
    Polygon(const Polygon& other) : Polygon{ other.m_points } {
    }
    Polygon& operator=(const Polygon& other) {
        m_points = other.m_points;
        return *this;
    }

protected:
    inline static std::vector<double> angles(const PointList& points) {
        std::vector<std::pair<Vector, Vector>> angles_points;
        angles_points.emplace_back(std::make_pair(points.front() - points.back(), points[1] - points.front()));
        for (size_t i = 1; i < points.size() - 1; ++i) {
            angles_points.emplace_back(std::make_pair(points[i] - points[i - 1], points[i + 1] - points[i]));
        }
        angles_points.emplace_back(std::make_pair(points.back() - points[points.size() - 2], points.front() - points.back()));

        std::vector<double> angles;
        for (auto& pair : angles_points) {
            double const value = (pair.first.x() * pair.second.x() + pair.first.y() * pair.second.y());
            double const lengths = (pair.first.length() * pair.second.length());
            double const cos = -(value / lengths);

            double const angle = std::acos(cos) * 180 / pi;

            angles.push_back(angle);
        }
        return angles;
    }
};

class Triangle : public Polygon, public IAreaComputable, public IPerimeterComputable {
public:
    Triangle(const PointList& points)
            : Polygon{ points } {
        if (points.size() != 3) {
            throw std::logic_error{ "Triangle has only 3 vertices" };
        }
    }

    double perimeter() const override {
        std::vector<Vector> edges;
        for (size_t i = 0; i < m_points.size() - 1; ++i) {
            edges.emplace_back(m_points[i] - m_points[i + 1]);
        }
        edges.emplace_back(m_points.front() - m_points.back());

        double perimeter = 0;
        for (auto& edge : edges) {
            perimeter += edge.length();
        }
        return perimeter;
    }

    double area() const override {
        std::vector<Vector> edges;
        for (size_t i = 0; i < m_points.size() - 1; ++i) {
            edges.emplace_back(m_points[i] - m_points[i + 1]);
        }
        edges.emplace_back(m_points.front() - m_points.back());

        double p = 0;
        std::vector<double> lengths;
        for (auto& edge : edges) {
            lengths.push_back(edge.length());
            p += edge.length();
        }
        p = p / 2;
        return std::sqrt(p * (p - lengths[0]) * (p - lengths[1]) * (p - lengths[2]));
    }
};

static bool equal(double first, double second) {
    return std::fabs(first - second) < 0.001;
}

class Trapeze : public Polygon, public IAreaComputable {

public:
    Trapeze(const PointList& points) : Polygon{ points } {
        if (points.size() != 4)
            throw std::logic_error{ "Trapeze must have 4 vertices" };

        std::vector<double> angles = Polygon::angles(points);
        //        assert(angles.size() == 4);
        bool const check1 = equal(angles[0] + angles[1], 180) && equal(angles[2] + angles[3], 180);
        bool const check2 = equal(angles[1] + angles[2], 180) && equal(angles[3] + angles[0], 180);
        if (!(check1 || check2))
            throw std::logic_error{ "Failed to construct a trapeze" };

    }

    double area() const override {
        double value = 0;
        value += Triangle{ PointList{ m_points.begin(), m_points.begin() + 3 } }.area();
        value += Triangle{ PointList{ m_points[0], m_points[3], m_points[2] } }.area();
        return value;
    }
};

class CompletePolygon : public Polygon, IAreaComputable {
public:
    CompletePolygon(const PointList& points)
            : Polygon{ points }
    {
        double const angleValue = (points.size() - 2) * 180 / points.size();

        std::vector<double> angles = Polygon::angles(points);
        for (double angle : angles)
            if (!equal(angle, angleValue))
                throw std::logic_error{ "Failed to construct complete polygon" };

    }

    double area() const override {
        int const count = m_points.size();
        double const length = Vector{ m_points[1] - m_points[0] }.length();

        return count * length * length / (4 * std::tan(pi / count));
    }
};

int main() {
    PointList points{ Point{ 0, 0 }, Point{ 1, 1 }, Point{ 3, 1 }, Point{ 2, 0 } };
    {
        Polyline polyline{ points };
        std::cout << "Polyline::perimeter: " << polyline.perimeter() << std::endl;
    }
    {
        ClosedPolyline closedPolyline{ points };
        std::cout << "ClosedPolyline::perimeter: " << closedPolyline.perimeter() << std::endl;
    }
    {
        PointList points{ Point{ 0, 0 }, Point{ 1, 1 }, Point{ 3, 1 }, Point{ 2, 0 } };
        Polygon polygon{ points };
        std::cout << "Polygon::perimeter: " << (polygon.perimeter()) << std::endl;
    }
    {
        PointList points{ Point{ 0, 0 }, Point{ 0, 1 }, Point{ 1, 0 } };
        Triangle triangle{ points };
        std::cout << "Triangle::perimeter: " << triangle.perimeter() << std::endl;
        std::cout << "Triangle::area: " << triangle.area() << std::endl;
    }
    {
        PointList points{ Point{ 0, 0 }, Point{ 0, 1 }, Point{ 3, 1 }, Point{ 2, 0 } };
        Trapeze trapeze{ points };
        std::cout << "Trapeze::perimeter: " << trapeze.perimeter() << std::endl;
        std::cout << "Trapeze::area: " << trapeze.area() << std::endl;
    }
    {
        PointList points{ Point{ 0, 0 }, Point{ 0, 1 }, Point{ 1, 1 }, Point{ 1, 0 } };
        CompletePolygon polygon{ points };
        std::cout << "CompletePolygon::perimeter: " << polygon.perimeter() << std::endl;
        std::cout << "CompletePolygon::area: " << polygon.area() << std::endl;
    }
    return 0;
}
