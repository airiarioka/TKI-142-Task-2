#pragma once

#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <utility>

using namespace std;

/**
* @brief Класс Очередь с приоритетом с двусторонним доступом
*/
template<typename Type>
class PriorityDeque
{
private:
	/**
	* @brief Структура элемента очереди
	*/
	struct Element
	{
		/**
		* @param value - значение элемента очереди
		*/
		Type value;

		/**
		* @param priority - приоритет элемента очереди
		*/
		int priority;

		/**
		* @brief Конструктор структуры по-умолчанию
		*/
		Element(void) : value(Type()), priority(0) {}

		/**
		* @brief Конструктор структуры по заданным значению и приоритету
		* @param newValue - значение элемента очереди
		* @param newPriority - приоритет элемента очереди
		*/
		Element(const Type& newValue, const int newPriority) : value(newValue), priority(newPriority) {}
	};

	/**
	* @param data - элементы очереди с приоритетом
	*/
	Element* data;

	/**
	* @param count - размер очереди с приоритетом
	*/
	size_t count;

	/**
	* @brief Выводит ошибку и завершает работу программы
	* @param text - текст, выводимый на экран
	*/
	void ERROR(const string text)
	{
		cerr << text;
		exit(1);
	}

	/**
	* @brief Возвращает индекс элемента с наименьшим приоритетом
	* @return Индекс элемента с наименьшим приоритетом
	*/
	size_t getMinIndex()
	{
		if (count == 0)
		{
			ERROR("Очередь пуста");
		}

		size_t index = 0;
		for (size_t i = 1; i < count; i++)
		{
			if (data[i].priority < data[index].priority)
			{
				index = i;
			}
		}

		return index;
	}

	/**
	* @brief Возвращает индекс элемента с наибольшим приоритетом
	* @return Индекс элемента с наибольшим приоритетом
	*/
	size_t getMaxIndex()
	{
		if (count == 0)
		{
			ERROR("Очередь пуста");
		}

		size_t index = 0;
		for (size_t i = 1; i < count; i++)
		{
			if (data[i].priority > data[index].priority)
			{
				index = i;
			}
		}

		return index;
	}

	/**
	* @brief Удаляет элемент по индексу
	* @param index - индекс удаляемого элемента
	*/
	void removeByIndex(const size_t index)
	{
		if (index >= count)
		{
			ERROR("Выход за границы очереди");
		}

		size_t newsize = count - 1;
		Element* newdata = nullptr;

		if (newsize > 0)
		{
			newdata = new Element[newsize];
			for (size_t i = 0, j = 0; i < count; i++)
			{
				if (i != index)
				{
					newdata[j++] = data[i];
				}
			}
		}

		delete[] data;
		data = newdata;
		count = newsize;
	}

public:
	/**
	* @brief Конструктор класса по-умолчанию, задаёт пустую очередь с приоритетом
	*/
	PriorityDeque(void) : data(nullptr), count(0) {}

	/**
	* @brief Конструктор класса, задаёт очередь с приоритетом по списку инициализации
	* @param other - список пар значение-приоритет
	*/
	PriorityDeque(initializer_list<pair<Type, int>> other) : data(nullptr), count(other.size())
	{
		if (count > 0)
		{
			data = new Element[count];
			for (size_t i = 0; const auto& value : other)
			{
				data[i++] = Element(value.first, value.second);
			}
		}
	}

	/**
	* @brief Конструктор класса, задаёт очередь с приоритетом по переданному списку
	* @param other - список пар значение-приоритет
	*/
	PriorityDeque(list<pair<Type, int>>& other) : data(nullptr), count(other.size())
	{
		if (count > 0)
		{
			data = new Element[count];
			for (size_t i = 0; const auto& value : other)
			{
				data[i++] = Element(value.first, value.second);
			}
		}
	}

	/**
	* @brief Конструктор класса, задаёт очередь с приоритетом по переданной очереди
	* @param other - переданная очередь с приоритетом
	*/
	PriorityDeque(const PriorityDeque& other) : data(nullptr), count(other.count)
	{
		if (count > 0)
		{
			data = new Element[count];
			for (size_t i = 0; i < count; i++)
			{
				data[i] = other.data[i];
			}
		}
	}

	/**
	* @brief Конструктор класса, задаёт очередь с приоритетом по ссылке на очередь
	* @param other - ссылка на переданную очередь с приоритетом
	*/
	PriorityDeque(PriorityDeque&& other) : data(other.data), count(other.count)
	{
		other.data = nullptr;
		other.count = 0;
	}

	/**
	* @brief Добавление элемента в очередь с приоритетом
	* @param object - объект добавляемый в очередь
	* @param priority - приоритет добавляемого объекта
	*/
	void push(const Type& object, const int priority)
	{
		Element* newdata = new Element[count + 1];

		for (size_t i = 0; i < count; i++)
		{
			newdata[i] = data[i];
		}

		newdata[count] = Element(object, priority);

		delete[] data;
		data = newdata;
		count++;
	}

	/**
	* @brief Удаление элемента с наименьшим приоритетом
	*/
	void pop_min()
	{
		if (count > 0)
		{
			removeByIndex(getMinIndex());
		}
		else
		{
			cout << "Очередь пуста, удаление не выполнено" << endl;
		}
	}

	/**
	* @brief Удаление элемента с наибольшим приоритетом
	*/
	void pop_max()
	{
		if (count > 0)
		{
			removeByIndex(getMaxIndex());
		}
		else
		{
			cout << "Очередь пуста, удаление не выполнено" << endl;
		}
	}

	/**
	* @brief Поиск элемента с наименьшим приоритетом
	* @return Элемент с наименьшим приоритетом
	*/
	Type peek_min()
	{
		return data[getMinIndex()].value;
	}

	/**
	* @brief Поиск элемента с наибольшим приоритетом
	* @return Элемент с наибольшим приоритетом
	*/
	Type peek_max()
	{
		return data[getMaxIndex()].value;
	}

	/**
	* @brief Поиск наименьшего приоритета
	* @return Наименьший приоритет
	*/
	int priority_min()
	{
		return data[getMinIndex()].priority;
	}

	/**
	* @brief Поиск наибольшего приоритета
	* @return Наибольший приоритет
	*/
	int priority_max()
	{
		return data[getMaxIndex()].priority;
	}

	/**
	* @brief Проверка очереди с приоритетом на пустоту
	* @return true или false
	*/
	bool empty() const
	{
		return count == 0;
	}

	/**
	* @brief Очистка очереди с приоритетом
	*/
	void clear()
	{
		delete[] data;
		data = nullptr;
		count = 0;
	}

	/**
	* @brief Вывод размера очереди с приоритетом
	* @return Число - размер очереди с приоритетом
	*/
	size_t printSize() const
	{
		return count;
	}

	/**
	* @brief Вывод данных очереди с приоритетом
	* @return Указатель на область памяти, где хранятся данные очереди
	*/
	const void* printData() const
	{
		return data;
	}

	/**
	* @brief Вывод размера очереди с приоритетом
	* @param os - поток вывода
	* @return Текст
	*/
	ostream& printSize(ostream& os) const
	{
		if (count == 0)
		{
			os << "Очередь пуста!" << endl;
		}
		else
		{
			os << "Размер очереди: " << count << endl;
		}

		return os;
	}

	/**
	* @brief Вывод очереди с приоритетом в строку
	* @return Очередь с приоритетом, сериализованная в строку
	*/
	string toString() const
	{
		stringstream stream;
		stream << "{";
		for (size_t i = 0; i < count; i++)
		{
			stream << "(" << data[i].value << "; " << data[i].priority << ")";
			if (i != count - 1)
			{
				stream << ", ";
			}
		}
		stream << "}";
		return stream.str();
	}

	/**
	* @brief Оператор присваивания очереди с приоритетом
	* @param other - другая очередь с приоритетом
	* @return Очередь с приоритетом
	*/
	PriorityDeque& operator = (const PriorityDeque& other)
	{
		if (this != &other)
		{
			delete[] data;

			count = other.count;
			data = nullptr;

			if (count > 0)
			{
				data = new Element[count];
				for (size_t i = 0; i < count; i++)
				{
					data[i] = other.data[i];
				}
			}
		}

		return *this;
	}

	/**
	* @brief Оператор присваивания очереди с приоритетом
	* @param other - ссылка на другую очередь с приоритетом
	* @return Очередь с приоритетом
	*/
	PriorityDeque& operator = (PriorityDeque&& other)
	{
		if (this != &other)
		{
			delete[] data;

			data = other.data;
			count = other.count;

			other.data = nullptr;
			other.count = 0;
		}

		return *this;
	}

	/**
	* @brief Оператор сравнения очередей с приоритетом
	* @param other - другая очередь с приоритетом
	* @return true или false
	*/
	bool operator == (const PriorityDeque& other) const
	{
		if (count != other.count)
		{
			return false;
		}

		for (size_t i = 0; i < count; i++)
		{
			if (data[i].value != other.data[i].value || data[i].priority != other.data[i].priority)
			{
				return false;
			}
		}

		return true;
	}

	/**
	* @brief Оператор сравнения очередей с приоритетом
	* @param other - другая очередь с приоритетом
	* @return true или false
	*/
	bool operator != (const PriorityDeque& other) const
	{
		return !(*this == other);
	}

	/**
	* @brief Оператор, показывающий n-й элемент очереди с приоритетом
	* @param index - индекс элемента, который будет показан
	* @return n-й элемент очереди с приоритетом
	*/
	Type& operator [] (const size_t index)
	{
		if (index < count)
		{
			return data[index].value;
		}

		ERROR("Выход за границы очереди");
	}

	/**
	* @brief Оператор, показывающий n-й элемент очереди с приоритетом
	* @param index - индекс элемента, который будет показан
	* @return n-й элемент очереди с приоритетом
	*/
	const Type& operator [] (const size_t index) const
	{
		if (index < count)
		{
			return data[index].value;
		}

		cerr << "Выход за границы очереди";
		exit(1);
	}

	/**
	* @brief Вывод приоритета n-го элемента очереди с приоритетом
	* @param index - индекс элемента, приоритет которого будет показан
	* @return Приоритет n-го элемента очереди с приоритетом
	*/
	int getPriority(const size_t index)
	{
		if (index < count)
		{
			return data[index].priority;
		}

		ERROR("Выход за границы очереди");
	}

	/**
	* @brief Оператор вывода очереди с приоритетом в поток вывода
	* @param os - поток вывода
	* @param other - очередь с приоритетом
	* @return Очередь с приоритетом, сериализованная в строку
	*/
	friend ostream& operator << (ostream& os, PriorityDeque& other)
	{
		os << other.toString() << endl;
		return os;
	}

	/**
	* @brief Оператор ввода элементов очереди с приоритетом
	* @param is - поток ввода
	* @param other - очередь с приоритетом
	* @return Поток ввода
	*/
	friend istream& operator >> (istream& is, PriorityDeque& other)
	{
		int inputCount = 0;
		cout << "Введите количество элементов в очереди: ";
		is >> inputCount;

		if (is.fail() || inputCount < 0)
		{
			other.ERROR("Ошибка ввода");
		}

		delete[] other.data;
		other.data = nullptr;
		other.count = static_cast<size_t>(inputCount);

		if (other.count > 0)
		{
			other.data = new Element[other.count];
			for (size_t i = 0; i < other.count; i++)
			{
				cout << "Введите " << i + 1 << " элемент очереди: ";
				is >> other.data[i].value;

				if (is.fail())
				{
					other.ERROR("Ошибка ввода");
				}

				cout << "Введите приоритет " << i + 1 << " элемента очереди: ";
				is >> other.data[i].priority;

				if (is.fail())
				{
					other.ERROR("Ошибка ввода");
				}
			}
		}

		return is;
	}

	/**
	* @brief Деструктор класса по-умолчанию
	*/
	~PriorityDeque()
	{
		delete[] data;
	}
};
