#include <gtest/gtest.h>

#include "../include/ClassPriorityDeque.h"

/**
* @brief Тест конструкторов
*/
TEST(ClassPriorityDeque, TestConstructors)
{
	PriorityDeque<int> Zero;
	EXPECT_EQ(Zero.printData(), nullptr);
	EXPECT_EQ(Zero.printSize(), 0);
	EXPECT_TRUE(Zero.empty());

	PriorityDeque<int> One{ {1, 10}, {2, 5}, {3, 15} };
	EXPECT_EQ(One.printSize(), 3);
	EXPECT_EQ(One[0], 1);
	EXPECT_EQ(One[1], 2);
	EXPECT_EQ(One[2], 3);
	EXPECT_EQ(One.getPriority(0), 10);
	EXPECT_EQ(One.getPriority(1), 5);
	EXPECT_EQ(One.getPriority(2), 15);

	list<pair<int, int>> a = { {4, 40}, {5, 20}, {6, 60} };
	PriorityDeque<int> Two(a);
	EXPECT_EQ(Two.printSize(), 3);
	EXPECT_EQ(Two[0], 4);
	EXPECT_EQ(Two[1], 5);
	EXPECT_EQ(Two[2], 6);
	EXPECT_EQ(Two.getPriority(0), 40);
	EXPECT_EQ(Two.getPriority(1), 20);
	EXPECT_EQ(Two.getPriority(2), 60);

	PriorityDeque<int> Three(Two);
	EXPECT_EQ(Three.printSize(), 3);
	EXPECT_EQ(Three[0], 4);
	EXPECT_EQ(Three[1], 5);
	EXPECT_EQ(Three[2], 6);
	EXPECT_EQ(Three.getPriority(0), 40);
	EXPECT_EQ(Three.getPriority(1), 20);
	EXPECT_EQ(Three.getPriority(2), 60);

	PriorityDeque<int> Original{ {7, 70}, {8, 80} };
	PriorityDeque<int> Moved(move(Original));
	EXPECT_EQ(Original.printSize(), 0);
	EXPECT_EQ(Original.printData(), nullptr);
	EXPECT_EQ(Moved.printSize(), 2);
	EXPECT_EQ(Moved[0], 7);
	EXPECT_EQ(Moved[1], 8);
	EXPECT_EQ(Moved.getPriority(0), 70);
	EXPECT_EQ(Moved.getPriority(1), 80);
}

/**
* @brief Тест оператора индекса
*/
TEST(ClassPriorityDeque, Index_Operator)
{
	PriorityDeque<int> One;
	EXPECT_EXIT(One[20], ::testing::ExitedWithCode(1), "Выход за границы очереди");

	PriorityDeque<int> Two{ {5, 1}, {7, 2}, {10, 3}, {9, 4} };
	EXPECT_EQ(Two[2], 10);
}

/**
* @brief Тест вывода приоритета элемента
*/
TEST(ClassPriorityDeque, GetPriority)
{
	PriorityDeque<int> One;
	EXPECT_EXIT(One.getPriority(20), ::testing::ExitedWithCode(1), "Выход за границы очереди");

	PriorityDeque<int> Two{ {5, 1}, {7, 2}, {10, 3}, {9, 4} };
	EXPECT_EQ(Two.getPriority(2), 3);
}

/**
* @brief Тест операторов сравнения
*/
TEST(ClassPriorityDeque, EQ_Operators)
{
	PriorityDeque<int> One{ {1, 10}, {2, 20}, {3, 30} };
	PriorityDeque<int> Two{ {1, 10}, {2, 20}, {3, 30} };
	PriorityDeque<int> Three{ {1, 10}, {2, 50}, {3, 30} };
	PriorityDeque<int> Four{ {1, 10}, {2, 20} };

	EXPECT_TRUE(One == Two);
	EXPECT_TRUE(One != Three);
	EXPECT_TRUE(One != Four);
	EXPECT_FALSE(One == Three);
	EXPECT_FALSE(One == Four);
}

/**
* @brief Тест операторов присваивания
*/
TEST(ClassPriorityDeque, Assign_Operators)
{
	PriorityDeque<int> One;
	PriorityDeque<int> Two{ {1, 10}, {2, 20}, {3, 30} };
	One = Two;
	EXPECT_EQ(One.printSize(), 3);
	EXPECT_EQ(One[0], 1);
	EXPECT_EQ(One[1], 2);
	EXPECT_EQ(One[2], 3);
	EXPECT_EQ(One.getPriority(0), 10);
	EXPECT_EQ(One.getPriority(1), 20);
	EXPECT_EQ(One.getPriority(2), 30);

	PriorityDeque<int> Three;
	Three = move(Two);
	EXPECT_EQ(Two.printSize(), 0);
	EXPECT_EQ(Two.printData(), nullptr);
	EXPECT_EQ(Three.printSize(), 3);
	EXPECT_EQ(Three[0], 1);
	EXPECT_EQ(Three[1], 2);
	EXPECT_EQ(Three[2], 3);
}

/**
* @brief Тест операторов ввода и вывода
*/
TEST(ClassPriorityDeque, IO_Operators)
{
	stringstream input("2 10 20 30 40");
	PriorityDeque<int> One;
	input >> One;

	EXPECT_EQ(One.printSize(), 2);
	EXPECT_EQ(One[0], 10);
	EXPECT_EQ(One.getPriority(0), 20);
	EXPECT_EQ(One[1], 30);
	EXPECT_EQ(One.getPriority(1), 40);

	stringstream output;
	output << One;
	EXPECT_EQ(output.str(), "{(10; 20), (30; 40)}\n");
}

/**
* @brief Тест функций вставки и удаления
*/
TEST(ClassPriorityDeque, Push_And_Pop)
{
	PriorityDeque<int> First{ {1, 10}, {2, 5}, {3, 15} };

	First.pop_min();
	EXPECT_EQ(First.printSize(), 2);
	EXPECT_EQ(First[0], 1);
	EXPECT_EQ(First[1], 3);
	EXPECT_EQ(First.getPriority(0), 10);
	EXPECT_EQ(First.getPriority(1), 15);

	First.pop_max();
	EXPECT_EQ(First.printSize(), 1);
	EXPECT_EQ(First[0], 1);
	EXPECT_EQ(First.getPriority(0), 10);

	First.push(50, 1);
	EXPECT_EQ(First.printSize(), 2);
	EXPECT_EQ(First[1], 50);
	EXPECT_EQ(First.getPriority(1), 1);
}

/**
* @brief Тест поиска элементов с наименьшим и наибольшим приоритетом
*/
TEST(ClassPriorityDeque, Peek_Min_And_Max)
{
	PriorityDeque<int> First{ {1, 10}, {2, 5}, {3, 15}, {4, 1} };

	EXPECT_EQ(First.peek_min(), 4);
	EXPECT_EQ(First.priority_min(), 1);
	EXPECT_EQ(First.peek_max(), 3);
	EXPECT_EQ(First.priority_max(), 15);
}

/**
* @brief Тест проверки очереди на пустоту
*/
TEST(ClassPriorityDeque, Empty)
{
	PriorityDeque<int> First;
	EXPECT_TRUE(First.empty());

	First.push(10, 5);
	EXPECT_FALSE(First.empty());
}

/**
* @brief Тест очистки очереди
*/
TEST(ClassPriorityDeque, Clear)
{
	PriorityDeque<int> First{ {1, 10}, {2, 20} };
	First.clear();

	EXPECT_EQ(First.printSize(), 0);
	EXPECT_EQ(First.printData(), nullptr);
	EXPECT_TRUE(First.empty());
}

/**
* @brief Тест вывода очереди в строку
*/
TEST(ClassPriorityDeque, ToString)
{
	PriorityDeque<int> First{ {1, 10}, {2, 20}, {3, 30} };
	EXPECT_EQ(First.toString(), "{(1; 10), (2; 20), (3; 30)}");
}

/**
* @brief Тест функций при пустой очереди
*/
TEST(ClassPriorityDeque, Empty_Errors)
{
	PriorityDeque<int> First;
	EXPECT_EXIT(First.peek_min(), ::testing::ExitedWithCode(1), "Очередь пуста");
	EXPECT_EXIT(First.peek_max(), ::testing::ExitedWithCode(1), "Очередь пуста");
	EXPECT_EXIT(First.priority_min(), ::testing::ExitedWithCode(1), "Очередь пуста");
	EXPECT_EXIT(First.priority_max(), ::testing::ExitedWithCode(1), "Очередь пуста");
}

int main(int argc, char** argv)
{
#ifdef _WIN32
	system("chcp 65001");
#endif

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}