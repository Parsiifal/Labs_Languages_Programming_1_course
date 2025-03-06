#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Tree
{
	int number;
	Tree* left, * right;
};

Tree* createNode(int number) // создание узла
{
	Tree* node = new Tree;
	node->number = number;
	node->left = node->right = NULL;
	return node;
}

void addNode(Tree*& root, Tree* node) // добавление узла в дерево
{
	if (root)
	{
		if (node->number <= root->number) // если меньше или равно корню
			addNode(root->left, node); // добавляем в левую ветку
		else
			addNode(root->right, node); // иначе в правую ветку
	}
	else
		root = node;
}

Tree* fileInputTree(const char* filename, vector<int>& treeElements) // чтение дерева из файла
{
	Tree* root = NULL;

	ifstream ifs(filename);
	int number;

	while (!ifs.eof())
	{
		ifs >> number;
		addNode(root, createNode(number)); // создаем и добавляем узел в дерево
		treeElements.push_back(number); // добавляем его значение в вектор значений узлов дерева
	}
	ifs.close();

	return root;
}

Tree* deleteNode(Tree*& node, int number, bool not_first_elem) // удаление узла
{
	if (node == NULL) // если узел пустой
	{
		return node;
	}

	if (number == node->number) // если значение равно значению узла инвертируем флаг проверки первого из повторяющихся элемента
	{
		not_first_elem = !not_first_elem;
	}

	if (number == node->number && not_first_elem) // если значение равно значению узла и это не первый элемент из повторяющихся
	{
		Tree* t;

		if (node->right == NULL) // если правого потомка нет
		{
			t = node->left;
		}
		else // иначе если правый потомок есть
		{
			Tree* child = node->right;

			if (child->left == NULL) // если у правого потомка нет левого потомка
			{
				child->left = node->left; // левый потомок правого потомка становится левым потомком узла
				t = child;
			}
			else // иначе если у правого потомка есть левый потомок
			{
				Tree* child_min = child->left;

				while (child_min->left != NULL) // пока левый потомок правого потомка существует
				{
					child = child_min; // правый потомок становится своим левым потомком
					child_min = child->left;
				}
				child->left = child_min->right; // левый потомок правого потомка становится правым потомком левого потомка правого потомка
				child_min->left = node->left; // левый потомок левого потомка правого потомка становится левым потомком
				child_min->right = node->right; // правый потомок левого потомка правого потомка становится правым потомком
				t = child_min;
			}

		}

		delete node;
		return t;
	}
	else if (number <= node->number) // иначе если значение меньше значения узла идем по левой ветке
	{
		node->left = deleteNode(node->left, number, not_first_elem);
	}
	else // в проивном случае по правой
	{
		node->right = deleteNode(node->right, number, not_first_elem);
	}
	return node;
}

void deleteRepeats(Tree*& T, vector<int> treeElements) // удаление повторяющихся узлов
{
	for (long unsigned int i = 0; i < treeElements.size(); i++)
	{
		for (long unsigned int j = 0; j < i; j++)
		{
			if (treeElements[i] == treeElements[j]) // если в векторе значений узлов обнаружены одинаковые значения, удаляем повторяющийся узел
			{
				deleteNode(T, treeElements[i], true);
			}
		}
	}
}

void outputNode(ofstream& ofs, Tree* root) // вывод узлов в обратном порядке
{
	if (root) // если узел существует
	{
		outputNode(ofs, root->left); // рекурсивный вызов левого поддерева
		outputNode(ofs, root->right); // рекурсивный вызов правого поддерева
		ofs << root->number << " ";
	}	
}

void outputTree(const char* filename, Tree* T) // вывод дерева в файл
{
	ofstream ofs(filename);
	outputNode(ofs, T);
	ofs.close();
}

void deleteTree(Tree*& node) // удаление дерева
{
	if (node)
	{
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}
}

int main()
{
	Tree* Tree; // объявление дерева

	vector<int> treeElements; // вектор, хранящий значения узлов дерева

	Tree = fileInputTree("input.txt", treeElements); // чтение дерева из файла

	deleteRepeats(Tree, treeElements); // удаление всех повторов в дереве

	outputTree("output.txt", Tree); // вывод дерева в файл

	deleteTree(Tree); // удаление дерева
}