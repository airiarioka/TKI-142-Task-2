#include <gtest/gtest.h>

#include "../include/Angle.h"
#include "../include/Point.h"
#include "../include/ArcLength.h"

#include <numbers>
#include <cmath>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cstdlib>

TEST(AngleTest, ConstructorDegreesMinutesSeconds)
{
    Angle angle(12, 30, 15.0);
    ASSERT_EQ(angle.getDegrees(), 12);
    ASSERT_EQ(angle.getMinutes(), 30);
    ASSERT_DOUBLE_EQ(angle.getSeconds(), 15.0);
    ASSERT_NEAR(angle.ToDegrees(), 12.5041666667, 1e-9);
}

TEST(AngleTest, ConstructorTotalSeconds)
{
    Angle angle(5400.0);
    ASSERT_EQ(angle.getDegrees(), 1);
    ASSERT_EQ(angle.getMinutes(), 30);
    ASSERT_DOUBLE_EQ(angle.getSeconds(), 0.0);
    ASSERT_NEAR(angle.ToDegrees(), 1.5, 1e-9);
}

TEST(AngleTest, NegativeAngle)
{
    Angle angle(-1800.0);
    ASSERT_NEAR(angle.ToDegrees(), -0.5, 1e-9);
}

TEST(AngleTest, FromDegrees)
{
    Angle angle = Angle::FromDegrees(12.5);

    ASSERT_NEAR(angle.ToDegrees(), 12.5, 1e-9);
    ASSERT_EQ(angle.getDegrees(), 12);
    ASSERT_EQ(angle.getMinutes(), 30);
}

TEST(AngleTest, ToRadians)
{
    Angle angle(180, 0, 0.0);

    ASSERT_NEAR(angle.ToRadians(), std::numbers::pi, 1e-9);
}

TEST(AngleTest, InvalidMinutesAndSeconds)
{
    ASSERT_THROW(Angle(10, -1, 0.0), invalid_argument);
    ASSERT_THROW(Angle(10, 60, 0.0), invalid_argument);
    ASSERT_THROW(Angle(10, 0, -1.0), invalid_argument);
    ASSERT_THROW(Angle(10, 0, 60.0), invalid_argument);
}

TEST(AngleTest, Operators)
{
    Angle first(3600.0);
    Angle second(1, 0, 0.0);
    Angle third(2, 0, 0.0);
    ASSERT_TRUE(first == second);
    ASSERT_TRUE(first != third);
}

TEST(AngleTest, IOOperators)
{
    stringstream input("-0 30 0");
    Angle angle;
    input >> angle;
    ASSERT_FALSE(input.fail());
    ASSERT_NEAR(angle.ToDegrees(), -0.5, 1e-9);
    stringstream output;
    output << Angle(10, 20, 30.0);
    ASSERT_EQ(output.str(), "10 20 30");
}

TEST(AngleTest, IncorrectInput)
{
    stringstream input("10 60 0");

    Angle angle;
    input >> angle;

    ASSERT_TRUE(input.fail());
}

TEST(PointTest, ConstructorFromDoubles)
{
    Point point(55.5, 37.25);
    ASSERT_NEAR(point.getLatitude().ToDegrees(), 55.5, 1e-9);
    ASSERT_NEAR(point.getLongitude().ToDegrees(), 37.25, 1e-9);
}

TEST(PointTest, ConstructorFromAngles)
{
    Point point(Angle(10, 0, 0.0), Angle(20, 30, 0.0));
    ASSERT_NEAR(point.getLatitude().ToDegrees(), 10.0, 1e-9);
    ASSERT_NEAR(point.getLongitude().ToDegrees(), 20.5, 1e-9);
}

TEST(PointTest, InvalidCoordinates)
{
    ASSERT_THROW(Point(91.0, 0.0), out_of_range);
    ASSERT_THROW(Point(0.0, 181.0), out_of_range);
}

TEST(PointTest, Operators)
{
    Point first(10.0, 20.0);
    Point second(10.0, 20.0);
    Point third(10.0, 30.0);
    ASSERT_TRUE(first == second);
    ASSERT_TRUE(first != third);
}

TEST(PointTest, IOOperators)
{
    stringstream input("10.5 -20.25");
    Point point;
    input >> point;
    ASSERT_FALSE(input.fail());
    ASSERT_NEAR(point.getLatitude().ToDegrees(), 10.5, 1e-9);
    ASSERT_NEAR(point.getLongitude().ToDegrees(), -20.25, 1e-9);
    stringstream output;
    output << point;
    string result = output.str();
    ASSERT_NE(result.find("10.5"), string::npos);
    ASSERT_NE(result.find("-20.25"), string::npos);
}

TEST(PointTest, IncorrectInput)
{
    stringstream input("91 0");

    Point point;
    input >> point;

    ASSERT_TRUE(input.fail());
}

TEST(ArcLengthTest, ConstructorFromPoints)
{
    Point first(0.0, 0.0);
    Point second(0.0, 1.0);
    ArcLength arc(first, second);
    ASSERT_TRUE(arc.getFirstPoint() == first);
    ASSERT_TRUE(arc.getSecondPoint() == second);
}

TEST(ArcLengthTest, ConstructorFromDoubles)
{
    ArcLength arc(1.0, 2.0, 3.0, 4.0);
    ASSERT_NEAR(arc.getFirstPoint().getLatitude().ToDegrees(), 1.0, 1e-9);
    ASSERT_NEAR(arc.getSecondPoint().getLongitude().ToDegrees(), 4.0, 1e-9);
}

TEST(ArcLengthTest, ConstructorFromAngles)
{
    ArcLength arc(Angle(0, 0, 0.0), Angle(0, 0, 0.0),
                  Angle(0, 0, 0.0), Angle(1, 0, 0.0));
    ASSERT_NEAR(arc.getSecondPoint().getLongitude().ToDegrees(), 1.0, 1e-9);
}

TEST(ArcLengthTest, LengthOfOneDegree)
{
    ArcLength arc(0.0, 0.0, 0.0, 1.0);
    ASSERT_NEAR(arc.getLength(6371000.0), 6371000.0 * std::numbers::pi / 180.0, 1.0);
}

TEST(ArcLengthTest, ZeroLength)
{
    ArcLength arc(10.0, 20.0, 10.0, 20.0);
    ASSERT_NEAR(arc.getLength(), 0.0, 1e-9);
}

TEST(ArcLengthTest, NegativeRadius)
{
    ArcLength arc(0.0, 0.0, 0.0, 1.0);

    ASSERT_THROW(arc.getLength(-1.0), invalid_argument);
}

TEST(ArcLengthTest, AntipodalPoints)
{
    ArcLength arc(0.0, 0.0, 0.0, 180.0);
    ASSERT_NEAR(arc.getLength(6371000.0), std::numbers::pi * 6371000.0, 1.0);
}

TEST(ArcLengthTest, InvalidCoordinates)
{
    ASSERT_THROW(ArcLength(100.0, 0.0, 0.0, 0.0), out_of_range);
    ASSERT_THROW(ArcLength(0.0, 200.0, 0.0, 0.0), out_of_range);
}

TEST(ArcLengthTest, ToString)
{
    ArcLength arc(0.0, 0.0, 0.0, 1.0);
    stringstream output;
    arc.ToString(output);
    string result = output.str();
    ASSERT_NE(result.find("Информация о дуге"), string::npos);
    ASSERT_NE(result.find("Первая точка"), string::npos);
    ASSERT_NE(result.find("Вторая точка"), string::npos);
    ASSERT_NE(result.find("Длина дуги"), string::npos);
}

TEST(ArcLengthTest, IOOperators)
{
    stringstream input("0 0 0 1");
    ArcLength arc;
    input >> arc;
    ASSERT_FALSE(input.fail());
    ASSERT_NEAR(arc.getSecondPoint().getLongitude().ToDegrees(), 1.0, 1e-9);
}

TEST(ArcLengthTest, IncorrectInput)
{

    stringstream input("91 0 0 0");
    ArcLength arc;
    input >> arc;
    ASSERT_TRUE(input.fail());
}

int main(int argc, char** argv)
{
#ifdef _WIN32
    system("chcp 65001");
#endif

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}