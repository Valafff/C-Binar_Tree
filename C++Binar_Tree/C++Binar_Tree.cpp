#include <iostream>

using namespace std;

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int data, Element* pLeft = nullptr, Element* pRight = nullptr) : Data(data), pLeft(pLeft), pRight(pRight)
		{
			cout << "Element Constructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "Element Destructor:\t" << this << endl;
		}
		// Класс Tree видит, что в Elelement
		friend class Tree;
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
	~Tree()
	{
		cout << "Tree Destructor:\t" << this << endl;
	}

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
		int maxway=0, max=0, min=0;

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
			depth++;

		} while (true);

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

		cout << "Глубина дерева равна:\t" << depth_2/*depth ? depth_2 : depth*/;

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
	//tree.depth(tree.getRoot());



	tree.clear(tree.getRoot());

	cout << endl;

}


