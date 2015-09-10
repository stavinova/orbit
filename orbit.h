#include <vector>

//вектор положения в пространстве
struct vec
{
    double x, y, z;
};

//кватернион
struct quaternion
{
    double w, x, y, z;
};

//вектор вращения в пространстве
struct Rotation
{
    double rotationAroundX, rotationAroundY, rotationAroundZ;
};

typedef vec Orient; //вектор ориентации в пространстве
typedef vec Position; //вектор положения в пространстве
typedef Rotation RotationSpeed; //вектор скорости вращения вокруг трех осей

//начальные положение, ориентация и скорость корабля
struct ShipPosition
{
    Position position;
    Orient orientation;
    vec speedFirst;
};

//команды, доступные пользователю
struct PartOfFlightPlan
{
    int delayTime; //время задержки
    double impulseValue; //уровень массового расхода топлива
    Rotation rotateValue; //момент вращения вокруг каждой из осей
};

//параметры корабля
struct ShipParams
{
    double shipEdgeLength; //длина
    double shipMass; //масса без топлива
    double fuelMass; //масса топлива
    Rotation maxRotation; //максимальные моменты вращения
    double maxFuelUsagePerSec; //максимальный массовый расход топлива
    double impulsePerFuel; //удельный импульс двигателя
    std::vector<PartOfFlightPlan> flightPlan; //массив команд
    double maxOverload; //предельная перегрузка
    double maxHeating; //максимальный перегрев
};

struct Quants
{
    int numberOfQuants; //количество отрезков времени
    double quantSizeOfSec; //размер отрезка в секундах
};

//возвращаемые значения положения и скорости
struct ReturnValues
{
    Position position;
    vec speed;
};

std::vector <ReturnValues> computeFlightPlan(ShipPosition initialPosition,
                                             ShipParams shipParams,
                                             Quants quants);