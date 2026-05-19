#include "../include/Angle.h"

#include <numbers>
#include <limits>
#include <cmath>
#include <stdexcept>
#include <string>
#include <exception>

void Angle::CheckAngle(void) const
{
    if (minutes < 0 || minutes >= 60)
    {
        throw invalid_argument("Минуты должны быть от 0 до 59.");
    }

    if (seconds < 0 || seconds >= 60 || !isfinite(seconds))
    {
        throw invalid_argument("Секунды должны быть от 0 до 59.");
    }
}

Angle::Angle(const double totalSeconds)
{
    if (!isfinite(totalSeconds))
    {
        throw invalid_argument("Угол должен быть конечным.");
    }

    negative = totalSeconds < 0;

    /**
    * @brief Модуль полного количества секунд.
    */
    double value = fabs(totalSeconds);

    /**
    * @brief Расчёт полного количества градусов.
    */
    degrees = static_cast<int>(value / 3600.0);

    /**
    * @brief Остаток секунд после выделения градусов.
    */
    value -= degrees * 3600.0;

    /**
    * @brief Расчёт полного количества минут из остатка.
    */
    minutes = static_cast<int>(value / 60.0);

    /**
    * @brief Остаток секунд после выделения минут.
    */
    seconds = value - minutes * 60.0;

    if (seconds >= 60.0)
    {
        seconds -= 60.0;
        minutes++;
    }

    if (minutes >= 60)
    {
        minutes -= 60;
        degrees++;
    }

    CheckAngle();
}

Angle::Angle(const int degrees, const int minutes, const double seconds)
{
    negative = degrees < 0;

    this->degrees = abs(degrees);
    this->minutes = minutes;
    this->seconds = seconds;

    CheckAngle();
}

Angle Angle::FromDegrees(const double decimalDegrees)
{
    return Angle(decimalDegrees * 3600.0);
}

int Angle::getDegrees(void) const
{

    if (negative)
    {
        return -degrees;
    }
    else
    {
        return degrees;
    }
}

int Angle::getMinutes(void) const
{
    return minutes;
}

double Angle::getSeconds(void) const
{
    return seconds;
}

double Angle::ToDegrees(void) const
{
    /**
    * @brief Угол в десятичных градусах без учёта знака.
    */
    double result = degrees + minutes / 60.0 + seconds / 3600.0;

    if (negative)
    {
        result = -result;
    }

    return result;
}

double Angle::ToRadians(void) const
{
    return ToDegrees() * std::numbers::pi / 180.0;
}

bool Angle::operator == (const Angle& other) const
{
    return fabs(ToDegrees() - other.ToDegrees()) < numeric_limits<double>::epsilon();
}

bool Angle::operator != (const Angle& other) const
{
    return !(*this == other);
}

ostream& operator << (ostream& output, const Angle& angle)
{
    if (angle.negative && (angle.degrees != 0 || angle.minutes != 0 || fabs(angle.seconds) > numeric_limits<double>::epsilon()))
    {
        output << '-';
    }
    output << angle.degrees << ' ' << angle.minutes << ' ' << angle.seconds;
    return output;
}

istream& operator >> (istream& input, Angle& angle)
{
    string textDegrees;
    int minutes;
    double seconds;

    input >> textDegrees >> minutes >> seconds;

    if (input.fail())
    {
        return input;
    }

    try
    {
        /**
        * @brief Позиция первого символа, который не удалось преобразовать в число.
        */
        size_t position = 0;

        /**
        * @brief Градусы, полученные из строки.
        */
        int degrees = stoi(textDegrees, &position);

        if (position != textDegrees.size())
        {
            throw invalid_argument("Неверно заданы градусы.");
        }

        /**
        * @brief Временный объект угла для безопасного чтения.
        */
        Angle temp;

        temp.negative = !textDegrees.empty() && textDegrees[0] == '-';
        temp.degrees = abs(degrees);
        temp.minutes = minutes;
        temp.seconds = seconds;
        temp.CheckAngle();
        angle = temp;
    }
    catch (const exception& error)
    {
        cerr << "Ошибка: " << error.what() << endl;
        input.setstate(ios::failbit);
    }

    return input;
}
