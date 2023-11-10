#include <iostream>
#include <ctime>
#include <time.h>
#include<Windows.h>//	Sleep;
#include<conio.h>
#include <chrono>

using namespace std;
using std::cin;
using std::cout;
using std::endl;

//Суповой набор от Эммы
enum Color
{
	Black, Blue, Green, Cyan, Red, Magenta, Brown,
	LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//получаем дискриптор активного окна
void setColor(Color text, Color background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
enum Direction { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, esc = 27 };
void setCursor(int x, int y)
{
	COORD myCoords = { x,y };//инициализируем передаваемыми значениями объект координат
	SetConsoleCursorPosition(hStdOut, myCoords);
}


//#define SMOKER_TREE
#define HEALTHY_MAN_TREE

#define BASE_CHECK // базовое дерево с псевдослучайным наполнением
#define NOT_RANDOM_TREE

#ifdef SMOKER_TREE
using namespace std;

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int data, Element* pLeft = nullptr, Element* pRight = nullptr) : Data(data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "Element Constructor:\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "Element Destructor:\t" << this << endl;
#endif // DEBUG

		}
		// Класс Tree видит, что в Elelement
		friend class Tree;
		friend class UnicTree;
	}*Root;//Создали указатель на объект Root - корневой элемент

public:
	Element* getRoot()
	{
		return Root;
	}
	Tree()
	{
		Root = nullptr;
		cout << "Tree Constructor:\t " << this << endl;
	}
	Tree(initializer_list<int> il) :Tree()
	{

		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			insert(*it, Root);
		}

	}
	~Tree()
	{
		//clear(Root);
		cout << "Tree Destructor:\t" << this << endl;
	}

	//Обертка для упрощения вызова методов классов
	//void insert(int Data)
	//{
	//	(Data, Root);
	//}

	//double avg() const
	//{
	//	print(Root);
	//	cout << endl;
	//}

	//void print()
	//{
	//	print(Root);
	//	cout << endl;
	//}



	//int minvalue()const
	//{
	//	return minValue(Root);
	//}

	//int sum()const
	//{
	//	return sum(Root);
	//}

	//int	maxValue(Element* Root) const
	//{
	//	if (Root == nullptr)return 0;
	//	if (Root->pRight == nullptr)return Root->Data;
	//	else return maxValue(Root->pRight);
	//}
	//int maxValue()
	//{
	//	maxValue(Root);
	//}

	//int minValue(Element* Root)
	//{
	//	if (Root == nullptr)return 0;
	//	if (Root->pLeft == nullptr)return Root->Data;
	//	else return minValue(Root->pLeft);
	//}

	//int count() 
	//{
	//	return count(Root);
	//}


	void insert(int Data, Element* Root)
	{
		// Если нулевой корень дерева пуст - создаем новый элемент и записываем его в нулевой корень со значением Data
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
			// Применительно к текущей задаче - достаточно return в текущем if-е. Условие выхода из рекурсии не требуется
			return;
		}
		//Условие выхода из рекурсии Если pLeft или pRight == nulptr (у элемента нет детей) - выходим из метода =>> из рекурсии
		//if (Root == nullptr) return;

		//Если корень хранит данные, то сравниваем значения с данными текущего корня и пришедшими данными
		if (Data < Root->Data)
		{
			//Если левй элемент отсутствует - создаем его и записываем дуда значение Data 
			if (Root->pLeft == nullptr)
			{
				Root->pLeft = new Element(Data);
			}
			//Иначе вызываем рекурсивный метод, где аргументами будут являться Data(пришла аргументом ранее) и указатель на левый элемент корня. и так пока не будет найдено место куда можно записать Data. В рекурсии Data может попасть и в правый элемент
			else
			{
				insert(Data, Root->pLeft);
			}
		}
		else
		{
			if (Root->pRight == nullptr)
			{
				Root->pRight = new Element(Data);
			}
			else
			{
				insert(Data, Root->pRight);
			}
		}
	}

	//eraseздорового человека
	//void erase(int Data, Element* Root)
	//{

	//	if (Root == nullptr)return;
	//	if (Data == Root->Data)
	//	{
	//		if (Root->pLeft == Root->pRight)
	//		delete Root;
	//		Root = nullptr;
	//	}
	//	else
	//	{
	//		if (count(Root->pLeft) > count(Root->pRight))
	//		{

	//			Root->Data = maxValue(Root.pLeft;
	//			erase(maxValue(Root.pLeft), Root->pRight);
	//		}
	//	}


	//}
	//if (Root)erase(Data, Root.pLeft);
	//if (Root)erase(Dat)


	void print(Element* Root)const
	{
		//Элементы дерева по возрастанию
		if (Root == nullptr)return;
		//Доходим до самого основания пирамиды(листьев дерева)-наполняем стэк, потом поднимаемя извлекаем элементы из стэка
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
	// Минимальное значение
	int minValue() const
	{
		if (Root == nullptr)return 0;
		int min = Root->Data;
		Element* tempelement = Root->pLeft;
		do
		{
			if (tempelement != nullptr)
			{
				if (min >= tempelement->Data)
				{
					min = tempelement->Data;
					tempelement = tempelement->pLeft;
				}
			}
			else
			{
				break;
			}
		} while (true);
		return min;
	}
	// Максимальное значение
	int maxValue() const
	{
		if (Root == nullptr)return 0;
		int max = Root->Data;
		Element* tempelement = Root->pRight;
		do
		{
			if (tempelement != nullptr)
			{
				if (max <= tempelement->Data)
				{
					max = tempelement->Data;
					tempelement = tempelement->pRight;
				}
			}
			else
			{
				break;
			}

		} while (true);
		return max;
	}
	// Подсчет суммы всех элементов
	int sum(Element* Root, int& arg_sum)
	{
		if (Root == nullptr)return arg_sum;
		sum(Root->pLeft, arg_sum);
		arg_sum += Root->Data;
		sum(Root->pRight, arg_sum);
		return arg_sum;
	}

	//int sum(Element* Root) const
	//{
	//	if (Root == nullptr)return 0;
	//	else sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	// 
	//return Root == nulptr ? 0 : sum(Root.pLef) + sum(Root.pRight) + Root.Data;
	//}

	//int count(Element* Root)
	//{
	//	return Root == nullptr ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	//}


	// Подсчет количества элементов дерева
	int count(Element* Root, int& arg_count)
	{
		if (Root == nullptr)return arg_count;
		count(Root->pLeft, arg_count);
		arg_count++;
		count(Root->pRight, arg_count);
		return arg_count;
	}
	// Подсчет среднего арифметического
	double avg(Element* Root, int& count, int& sum, bool is_reset = false)
	{
		if (!is_reset)
		{
			count = 0;
			sum = 0;
			is_reset = true;
		}
		if (Root == nullptr)return 0;
		avg(Root->pLeft, count, sum, is_reset);
		count++;
		sum += Root->Data;
		avg(Root->pRight, count, sum, is_reset);
		return (double)sum / count;
	}
	//Очистка дерева
	void clear(Element* arg_Root)
	{
		Element* tempelement_left = arg_Root;
		Element* tempelement_right = arg_Root;
		Element* Parent_1 = nullptr;
		Element* Parent_2 = nullptr;
		if (arg_Root == nullptr)return;
		do
		{
			//Удаление слева
			if (tempelement_left->pLeft != nullptr)
			{
				Parent_1 = tempelement_left;
				tempelement_left = tempelement_left->pLeft;
				if (tempelement_left->pLeft == nullptr and tempelement_left->pRight == nullptr)
				{
					delete tempelement_left;
					Parent_1->pLeft = nullptr;
					tempelement_left = arg_Root;
				}
			}
			else if (tempelement_left->pLeft == nullptr and tempelement_left->pRight != nullptr and tempelement_left != arg_Root)
			{
				Parent_1 = tempelement_left;
				tempelement_left = tempelement_left->pRight;
			}
			else if (tempelement_left->pLeft == nullptr and tempelement_left->pRight == nullptr and tempelement_left != arg_Root)
			{
				delete tempelement_left;
				Parent_1->pLeft = nullptr;
				if (Parent_1->pRight != nullptr)
				{
					Parent_1->pRight = nullptr;
				}
				tempelement_left = arg_Root;
			}
			//Удаление справа
			if (tempelement_right->pRight != nullptr)
			{
				Parent_2 = tempelement_right;
				tempelement_right = tempelement_right->pRight;
				if (tempelement_right->pLeft == nullptr and tempelement_right->pRight == nullptr)
				{
					delete tempelement_right;
					Parent_2->pRight = nullptr;
					tempelement_right = arg_Root;
				}
			}
			else if (tempelement_right->pRight == nullptr and tempelement_right->pLeft != nullptr and tempelement_right != arg_Root)
			{
				Parent_2 = tempelement_right;
				tempelement_right = tempelement_right->pLeft;
			}
			else if (tempelement_right->pRight == nullptr and tempelement_right->pLeft == nullptr and tempelement_right != arg_Root)
			{
				delete tempelement_right;
				Parent_2->pRight = nullptr;
				if (Parent_2->pLeft != nullptr)
				{
					Parent_2->pLeft = nullptr;
				}
				tempelement_right = arg_Root;
			}
			//Кирдык корню
			if (arg_Root->pLeft == nullptr and arg_Root->pRight == nullptr)
			{
				delete arg_Root;
				this->Root = nullptr;
				break;
			}
		} while (true);
	}
	//// Clear здрового человека
	//void clear(Element* Root)
	//{
	//	if (Root == nullptr)return;
	//	clear(Root->pLeft);
	//	clear(Root->pRight);
	//	delete Root;
	//	Root == nullptr;

	//}


	//Удаление элемента в бинарном дереве
	void erase(Element* arg_Root, int arg_number)
	{

		bool not_bingo = false;
		bool right = false;
		Element* tempelement = arg_Root;
		Element* data_1, * data_2;
		Element* Parent = arg_Root;

		do
		{
			right = false;
			if (tempelement->Data == arg_number)
			{
				break;
			}
			else if (tempelement->Data > arg_number)
			{
				Parent = tempelement;
				tempelement = tempelement->pLeft;
			}
			else if (tempelement->Data < arg_number)
			{
				Parent = tempelement;
				tempelement = tempelement->pRight;
				right = true;
			}
			if (tempelement->pLeft == nullptr and tempelement->pRight == nullptr and tempelement->Data != arg_number)
			{
				cout << "Не бинго:(" << endl;
				not_bingo = true;
				return;
			}


		} while (tempelement->Data != arg_number);


		if (!not_bingo)
		{
			//Если лист
			if (tempelement->pLeft == nullptr and tempelement->pRight == nullptr)
			{
				if (right)
				{
					Parent->pRight = nullptr;
				}
				else
				{
					Parent->pLeft = nullptr;
				}
				delete tempelement;
			}
			//Если корень
			else if (tempelement->pLeft != nullptr and tempelement->pRight != nullptr)
			{
				data_1 = tempelement->pLeft;
				data_2 = tempelement->pRight;
				// Если левая 
				if (data_1->Data >= data_2->Data)
				{
					this->Root = data_1;
					//Поиск максимума
					Element* temp = data_1->pRight;
					do
					{
						if (temp != nullptr)
						{
							if (data_1->Data <= temp->Data)
							{
								data_1 = temp;
								temp = temp->pRight;
							}
						}
						else
						{
							break;
						}

					} while (true);

					data_1->pRight = tempelement->pRight;
					Parent->pLeft = data_1;
					if (tempelement == this->Root)
					{
						this->Root = data_1;
					}
				}
				else
				{
					this->Root = data_2;
					//Поиск минимума в подветке
					Element* temp = data_2;
					do
					{
						if (temp != nullptr)
						{
							if (data_2->Data >= temp->Data)
							{
								data_2 = temp;
								temp = temp->pLeft;
							}
						}
						else
						{
							break;
						}
					} while (true);

					data_2->pLeft = tempelement->pLeft;

					Parent->pRight = data_2;
					if (tempelement == this->Root)
					{
						this->Root = data_2;
					}
				}
				//Parent->pLeft = data_1;
				//Parent->pRight = data_2;
				delete tempelement;
			}
			//Если есть элемент справа
			else if (tempelement->pLeft == nullptr and tempelement->pRight != nullptr)
			{
				data_1 = tempelement;
				if (right)
				{
					Parent->pRight = data_1->pRight;
				}
				else
				{
					Parent->pLeft = data_1->pRight;
				}
				delete tempelement;
			}
			//Если есть элемент слева
			else
			{
				data_1 = tempelement;
				if (right)
				{
					Parent->pRight = data_1->pLeft;
				}
				else
				{
					Parent->pLeft = data_1->pLeft;
				}
				delete tempelement;
			}

		}
	}
	//Определение глубины
	void depth(Element* arg_Root)
	{
		Element* temp = Root;
		int depth = 0;
		int depth_2 = 0;
		int maxway = 0, max = 0, min = 0;

		do
		{
			if (temp != nullptr)
			{
				if (max <= temp->Data)
				{
					max = temp->Data;
					temp = temp->pRight;
				}
			}
			else
			{
				break;
			}

		} while (true);
		temp = Root;
		min = temp->Data;
		do
		{
			if (temp != nullptr)
			{
				if (min >= temp->Data)
				{
					min = temp->Data;
					temp = temp->pLeft;
				}
			}
			else
			{
				break;
			}
		} while (true);



		Element* tempelement = arg_Root;

		do
		{
			depth++;
			if (tempelement->Data == min)
			{
				break;
			}
			else if (tempelement->Data > min)

			{
				tempelement = tempelement->pLeft;
			}
			else if (tempelement->Data < min)
			{
				tempelement = tempelement->pRight;
			}
			if (tempelement->pLeft == nullptr and tempelement->pRight == nullptr)
			{
				break;
			}


		} while (true);

		tempelement = arg_Root;
		do
		{
			depth_2++;
			if (tempelement->Data == max)
			{
				break;
			}
			else if (tempelement->Data > max)

			{
				tempelement = tempelement->pLeft;
			}
			else if (tempelement->Data < max)
			{
				tempelement = tempelement->pRight;
			}
			if (tempelement->pLeft == nullptr and tempelement->pRight == nullptr)
			{
				break;
			}


		} while (true);

		if (depth > depth_2)
		{
			cout << "Глубина дерева равна:\t" << depth << endl;
		}
		else
		{
			cout << "Глубина дерева равна:\t" << depth_2 << endl;
		}

	}
};


class UnicTree :public Tree
{




	void insert(int Data, Element* Root)
	{
		// Если нулевой корень дерева пуст - создаем новый элемент и записываем его в нулевой корень со значением Data
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
			// Применительно к текущей задаче - достаточно return в текущем if-е. Условие выхода из рекурсии не требуется
			//return;
		}
		if (Root == nullptr)return;
		//Условие выхода из рекурсии Если pLeft или pRight == nulptr (у элемента нет детей) - выходим из метода =>> из рекурсии
		//if (Root == nullptr) return;

		//Если корень хранит данные, то сравниваем значения с данными текущего корня и пришедшими данными
		if (Data < Root->Data)
		{
			//Если левй элемент отсутствует - создаем его и записываем дуда значение Data 
			if (Root->pLeft == nullptr)
			{
				Root->pLeft = new Element(Data);
			}
			//Иначе вызываем рекурсивный метод, где аргументами будут являться Data(пришла аргументом ранее) и указатель на левый элемент корня. и так пока не будет найдено место куда можно записать Data. В рекурсии Data может попасть и в правый элемент
			else
			{
				insert(Data, Root->pLeft);
			}
		}
		// Доделать.
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)
			{
				Root->pRight = new Element(Data);
			}
			else
			{
				insert(Data, Root->pRight);
			}
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};


int main()
{
	setlocale(LC_ALL, "");

	int n;
	int sum = 0, count = 0;
	cout << "Введите размер дерева: "; cin >> n;
	Tree tree;

	count = 0;

	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100, tree.getRoot()); // getroot -передает адрес корня
	}
	cout << "Элементы дерева:\t";
	// Печать рекурсией
	tree.print(tree.getRoot());

	//Поиск минимального значения
	cout << "\nМинимальное знаение бинарного дерева:\t" << tree.minValue() << endl;
	cout << "Максимальное знаение бинарного дерева:\t" << tree.maxValue() << endl;

	cout << "Сумма элементов бинарного дерева:\t" << tree.sum(tree.getRoot(), sum) << endl;
	cout << "Количество элементов бинарного дерева:\t" << tree.count(tree.getRoot(), count) << endl;
	cout << "Среднее арифметическое элементов бинарного дерева:\t" << tree.avg(tree.getRoot(), count, sum) << endl;
	cout << "Введите число для удаления: ";
	cin >> n;
	tree.erase(tree.getRoot(), n);

	cout << "\n Элементы дерева после удаления:\t";
	// Печать рекурсией
	tree.print(tree.getRoot());
	cout << endl;
	tree.depth(tree.getRoot());


	tree.clear(tree.getRoot());
	cout << endl;

	UnicTree u_tree;
	for (size_t i = 0; i < n; i++)
	{
		tree.insert(rand() % 100, tree.getRoot()); // getroot -передает адрес корня
	}
}
#endif // SMOKER_TREE


class Tree
{
	//protected Позволяет видеть поля классу наследнику
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;

public:
	Element* getRoot()
	{
		return Root;
	}
	Tree()
	{
		Root = nullptr;
		cout << "TConstructor:\t" << this << endl;
	}
	//			type		  name
	Tree(initializer_list<int> il) :Tree()
	{
		//begin() - возвращает итератор на начало контейнера;
		//end()   - возвращает итератор на конец контейнера;
		for (int const* it = il.begin(); it != il.end(); ++it)
			insert(*it, Root);
	}
	~Tree()
	{
		clear(Root);
		cout << "TDestructor:\t" << this << endl;
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int sum()const
	{
		return sum(Root);
	}
	int count()const
	{
		return count(Root);
	}
	double avg()const
	{
		return (double)sum(Root) / count(Root);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}

	//Максимальная глубина дерева
	int depth() const
	{
		return depth(Root);
	}

	int depth(Element* Root) const
	{

		if (Root == nullptr)
		{
			return 0;
		}
		//if (depth(Root->pLeft) + 1 > depth(Root->pRight) + 1)
		//{
		//	return depth(Root->pLeft) + 1;
		//}
		//else
		//{
		//	return depth(Root->pRight) + 1;
		//}
		int l_depth = depth(Root->pLeft) + 1;
		int r_depth = depth(Root->pRight) + 1;
		return l_depth > r_depth ? l_depth : r_depth;

	}

	//Вывод элементов дерева на заданной глубине //depth - глубина
	void PrintDepth(int var)
	{
		PrintDepth(Root, var);
	}
	void PrintDepth(Element* Root, int var)
	{
		static int sdcount = 1;
		if (Root == nullptr)
		{
			return;
		}
		sdcount++;
		PrintDepth(Root->pLeft, var);
		PrintDepth(Root->pRight, var);
		sdcount--;

		if (sdcount == var)
		{
			cout << Root->Data << "\t";
		}
	}

	//Отрисовка дерева
	void PrintTree(int X, int Y)
	{
		PrintTree(Root, X, Y);
	}
	int size = 4;
	void PrintTree(Element* Root, int X, int Y)
	{
		int tempX = X;
		int tempY = Y;
		if (Root == nullptr)return;
		if (Root->pRight == nullptr && Root->pLeft == nullptr)
		{
			setColor(Black, LightGreen);
		}
		else setColor(Black, Brown);
		setCursor(X, Y);
		cout << Root->Data << endl;
		if (Root->pLeft != nullptr)
		{
			setColor(Red, Black);
			for (size_t i = 0; i < size; i++)
			{
				setCursor(X - 1, Y + 1);
				cout << "/" << endl;
				X--;
				Y++;
			}
			setCursor(X, Y + 1);
			setColor(White, Black);
		}
		if (Root->pRight != nullptr)
		{
			setColor(Red, Black);
			for (size_t i = 0; i < size; i++)
			{
				setCursor(tempX + 1, tempY + 1);
				cout << "\\" << endl;
				tempX++;
				tempY++;
			}
			setCursor(tempX, tempY + 1);
			setColor(White, Black);
		}
		size = 6;
		PrintTree(Root->pLeft, X, Y);
		PrintTree(Root->pRight, tempX, tempY);
		size--;
		if (size == 1) size = 6;
		setColor(White, Black);
	}

	void TreeBalance()
	{
		TreeBalance(Root);
	}
	void TreeBalance(Element*& Root)//ВЕРНОЕ РЕШЕНИЕ
	{
		int temp = Root->Data;
		while (abs(count(Root->pLeft) - count(Root->pRight)) > 1)
		{
			temp = Root->Data;
			if (Root == nullptr) return;
			if (abs(count(Root->pLeft) - count(Root->pRight)) < 2) return;
			else
			{
				erase(temp);
				insert(temp);
			}
			TreeBalance(Root->pRight);
			TreeBalance(Root->pLeft);
		}
	}

	//Счетчик времени выполнения метода в секундах
	double m_Counter(Tree* obj, int (Tree::* ptr)()const)
	{
		clock_t start = clock();
		(obj->*ptr)();
		clock_t end = clock();
		return double(end - start) / CLOCKS_PER_SEC;
	}
	double double_m_Counter(Tree* obj, double (Tree::* ptr)()const)
	{
		clock_t start = clock();
		(obj->*ptr)();
		clock_t end = clock();
		return double(end - start) / CLOCKS_PER_SEC;
	}
	double void_m_Counter(Tree* obj, void (Tree::* ptr)()const)
	{
		clock_t start = clock();
		(obj->*ptr)();
		clock_t end = clock();
		return double(end - start) / CLOCKS_PER_SEC;
	}


private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
		if (Root)erase(Data, Root->pLeft);
		if (Root)erase(Data, Root->pRight);
	}
	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
		Root = nullptr;
	}
	int minValue(Element* Root)const
	{
		if (Root == nullptr)return 0;
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		if (Root == nullptr)return 0;
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/
		return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
		//return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int sum(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		else return sum(Root->pLeft) + sum(Root->pRight) + Root->Data;*/
		return Root == nullptr ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}
	int count(Element* Root)const
	{
		return Root == nullptr ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}

};

//Унаследованный класс - уникальное дерево - отсутствуют повторяющиеся элементы - модифицирован метод insert
class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};



void main()
{
	setlocale(LC_ALL, "");
	int d = 3;
	int (Tree:: * ptr)()const;
	double(Tree:: * dptr)()const;
	void(Tree:: * vptr)()const;
#ifdef BASE_CHECK
	int n;

	cout << "Введите размер дерева: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	setColor(Green, Black);
	cout << "Значения псевдослучайного дерева:" << endl;
	setColor(White, Black);
	tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	ptr = &Tree::minValue;
	cout << "Время выполнения minValue: " <<  tree.m_Counter(&tree, ptr) << " секунд" << endl;

	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	ptr = &Tree::maxValue;
	cout << "Время выполнения maxValue: " << tree.m_Counter(&tree, ptr) << " секунд" << endl;

	cout << "Сумма элементов дерева: " << tree.sum() << endl;
	ptr = &Tree::sum;
	cout << "Время выполнения sum: " << tree.m_Counter(&tree, ptr) << " секунд" << endl;

	cout << "Количество элементов дерева: " << tree.count() << endl;
	ptr = &Tree::count;
	cout << "Время выполнения count: " << tree.m_Counter(&tree, ptr) << " секунд" << endl;

	cout << "Среднее-арифметическое элементов дерева: " << tree.avg() << endl;
	dptr = &Tree::avg;
	cout << "Время выполнения avg: " << tree.double_m_Counter(&tree, dptr) << " секунд" << endl;

	cout << "Глубина дерева: " << tree.depth() << endl;
	ptr = &Tree::depth;
	cout << "Время выполнения depth: " << tree.m_Counter(&tree, ptr) << " секунд" << endl;


	cout << "Значения на заданной глубине " << d <<" :  ";
	tree.PrintDepth(d);
	cout << endl;

	tree.PrintTree(20, 20);

	_getch();
	setCursor(0, 30+n);

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	setColor(Red, Black);
	cout << "\nЗначения псевдослучайного дерева с уникальными значениями:" << endl;
	setColor(White, Black);
	u_tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << u_tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << u_tree.maxValue() << endl;
	cout << "Сумма элементов дерева: " << u_tree.sum() << endl;
	cout << "Количество элементов дерева: " << u_tree.count() << endl;
	cout << "Среднее-арифметическое элементов дерева: " << u_tree.avg() << endl;
	cout << "Глубина уникального дерева: " << u_tree.depth() << endl;
	cout << "Значения на заданной глубине:  ";
	u_tree.PrintDepth(d);
	cout << endl;



	int value;
	cout << "Введите удаляемое значение: "; cin >> value;
	u_tree.erase(value);
	u_tree.print();


#endif // BASE_CHECK



#ifdef NOT_RANDOM_TREE
	_getch();
	system("cls");
	Tree handle_tree =
	{
						1,

			2,						3,

		4,		5,				6,		7,
		8
	};
	setColor(Magenta, Black);
	cout << "Дерево со строго заданными значениями: ";
	setColor(White, Black);
	handle_tree.print();
	
	int handle_value;

	cout << "Введите удаляемое значение: "; cin >> handle_value;
	handle_tree.erase(handle_value);
	setColor(Magenta, Black);
	cout << "Дерево со строго заданными значениями после удаления элемента: ";
	setColor(White, Black);
	handle_tree.print();
	cout << "Глубина дерева: " << handle_tree.depth() << endl;
	handle_tree.PrintTree(20, 5);
	handle_tree.TreeBalance();
	handle_tree.PrintTree(20, 30);
	setCursor(0, 50);

	_getch();
	system("cls");
	setCursor(0, 0);
	Tree test_tree;
	cout << "Введите размер дерева: "; cin >> n;
	for (int i = 0; i < n; i++)
	{
		test_tree.insert(rand() % 100);
	}
	test_tree.print();
	vptr = &Tree::print;
	cout << "Время выполнения print: " << tree.void_m_Counter(&tree, vptr) << " секунд" << endl;
#endif // NOT_RANDOM_TREE


}