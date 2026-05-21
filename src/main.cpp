#include "../include/ClassPriorityDeque.h"

/**
* @brief Нумерация объектов выбора
* @param STR - выбор типа данных string
* @param CHR - выбор типа данных char
* @param DBL - выбор типа данных double
* @param INT - выбор типа данных int
* @param BOOL - выбор типа данных bool
*/
enum MyEnum
{
	STR = 1,
	CHR,
	DBL,
	INT,
	BOOL
};

/**
* @brief Считывает число типа int введённое с клавиатуры
* @return Число типа int
*/
int get_choice();

/**
* @brief Считывает приоритет элемента введённый с клавиатуры
* @return Приоритет элемента
*/
int get_priority();

/**
* @brief Выводит ошибку и завершает работу программы
* @param text - текст, выводимый на экран
*/
void ERROR(const string text);

/**
* @brief Область работы с очередью с приоритетом
* @param text - тип данных, участвующий в работе очереди
*/
template <typename Type>
void runPriorityDeque(const string text);

/**
* @brief Считывает элемент типа type введённый с клавиатуры
* @return Элемент типа type
*/
template <typename Type>
Type get_element();

/**
* @brief Точка входа в программу
* @return 0 если программа выполнена корректно, иначе 1
*/
int main()
{
	#ifdef _WIN32
	system("chcp 65001");
	#endif
	system("CLS");

	cout << "Выберите тип данных хранящихся в очереди с приоритетом: " << endl <<
		STR << " - слова" << endl <<
		CHR << " - буквы" << endl <<
		DBL << " - вещественные числа" << endl <<
		INT << " - целые числа" << endl <<
		BOOL << " - булевые числа [0,1]" << endl;
	int choice = get_choice();

	system("CLS");

	switch (choice)
	{
	case STR:
		runPriorityDeque<string>("string");
		break;
	case CHR:
		runPriorityDeque<char>("char");
		break;
	case DBL:
		runPriorityDeque<double>("double");
		break;
	case INT:
		runPriorityDeque<int>("int");
		break;
	case BOOL:
		runPriorityDeque<bool>("bool");
		break;
	default:
		ERROR("Ошибка выбора");
	}

	return 0;
}

int get_choice()
{
	int number = 0;
	cin >> number;
	if (cin.fail())
	{
		ERROR("Ошибка ввода");
	}
	return number;
}

int get_priority()
{
	int priority = 0;
	cin >> priority;
	if (cin.fail())
	{
		ERROR("Ошибка ввода");
	}
	return priority;
}

void ERROR(const string text)
{
	cerr << text;
	exit(1);
}

template <typename Type>
void runPriorityDeque(const string text)
{
	PriorityDeque<Type> First;
	cin >> First;
	system("CLS");

	cout << "Очередь с приоритетом: ";
	cout << First;
	First.printSize(cout);

	if (!First.empty())
	{
		cout << endl << "Элемент с наименьшим приоритетом: " << First.peek_min()
			<< " [приоритет: " << First.priority_min() << "]" << endl;
		cout << "Элемент с наибольшим приоритетом: " << First.peek_max()
			<< " [приоритет: " << First.priority_max() << "]" << endl;

		cout << endl << "Очередь после удаления элемента с наименьшим приоритетом: ";
		First.pop_min();
		cout << First;
		First.printSize(cout);
	}

	if (!First.empty())
	{
		cout << endl << "Очередь после удаления элемента с наибольшим приоритетом: ";
		First.pop_max();
		cout << First;
		First.printSize(cout);
	}

	cout << endl << "Введите элемент (c типом " << text << "), который будет добавлен в очередь: ";
	Type element = get_element<Type>();

	cout << "Введите приоритет элемента: ";
	int priority = get_priority();

	cout << endl << "Очередь после вставки элемента: ";
	First.push(element, priority);
	cout << First;
	First.printSize(cout);

	cout << endl << "Элемент с наименьшим приоритетом: " << First.peek_min()
		<< " [приоритет: " << First.priority_min() << "]" << endl;
	cout << "Элемент с наибольшим приоритетом: " << First.peek_max()
		<< " [приоритет: " << First.priority_max() << "]" << endl;
}

template <typename Type>
Type get_element()
{
	Type element{};
	cin >> element;
	if (cin.fail())
	{
		ERROR("Ошибка ввода");
	}
	return element;
}
