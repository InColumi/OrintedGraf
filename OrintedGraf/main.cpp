#include <iostream>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class OrGrafOnMatrix
{
	private:

	int _size;
	bool** _matrix;
	char* _namesVertex;
	
	public:
	
	OrGrafOnMatrix()
	{
		_size = 0;
		Initialization();
	}

	void ReadFromFile(string fileName)
	{
		ifstream in;
		in.open(fileName);
		if(in.is_open() == false)
		{
			cout << "Не удалось найти указанный файл.\n";
		}
		
		string line;
		getline(in, line);
		_size = stoi(line);
		Initialization();

		getline(in, line);
		SetNamesVertex(line);

		int indexRows = 0;
		while(getline(in, line))
		{
			SetMatrix(line, indexRows++);
		}
		in.close();
	}

	void DeleleVertex(char name)
	{
		cout << "Матрица смежности имеет вид:\n";
		ShowMatrix();
		DeleteVertexByName(name);
		cout << "После удаление вершин, которые не могут достичь вершины " << name << " матрица смежности имеет вид:\n";
		ShowMatrix();
	}

	private:

	void Initialization()
	{
		_matrix = AllocationMemory(_size);
		_namesVertex = new char[_size];
	}

	void DeleteVertexByName(char name)
	{
		int sizeIndexes = 0;
		int* indexesVertexesForDeleting = GetIndexesVertexesForDeleting(name, sizeIndexes);
		for(int i = 0; i < sizeIndexes; i++)
		{
			cout << "В вершину " << name << " нельзя попасть из " << _namesVertex[indexesVertexesForDeleting[i]] << "\n";
		}
		ResizeMatrix(indexesVertexesForDeleting, sizeIndexes);
	}

	void ResizeMatrix(int* indexes, int sizeIndexes)
	{
		int newSize = _size - sizeIndexes;
		bool** newMatrix = AllocationMemory(newSize);
		int countRow = 0;
		int countColumn = 0;
		int indexI = 0;
		int indexJ = 0;
		for(int i = 0; i < _size; i++)
		{
			if(indexes[indexI] == i)
			{
				indexI++;
				continue;
			}
			for(int j = 0; j < _size; j++)
			{
				if(indexes[indexJ] == j)
				{
					indexJ++;
					continue;
				}
				newMatrix[countRow][countColumn] = _matrix[i][j];
				countColumn++;
			}
			countColumn = 0;
			countRow++;

		}
		_size -= sizeIndexes;
		_matrix = newMatrix;
	}

	int* GetIndexesVertexesForDeleting(char name, int& sizeIndexes)
	{
		if(IsCorrectName(name))
		{
			int size = 0;
			int* indexesForDelete = new int[size];
			int index = GetIndexByNameVertex(name);
			for(int i = 0; i < _size; i++)
			{
				if(name != _namesVertex[i])
				{

					if(_matrix[i][index] == 0)
					{
						indexesForDelete = AddToArray(indexesForDelete, size, GetIndexByNameVertex(_namesVertex[i]));
					}
				}
			}
			sizeIndexes = size;
			return indexesForDelete;
		}
		cout << "Вершины с таким именем - нет!";
		exit(0);
	}

	void ShowMatrix()
	{
		for(int i = 0; i < _size; i++)
		{
			for(int j = 0; j < _size; j++)
			{
				cout << _matrix[i][j] << " ";
			}
			cout << endl;
		}
	}

	void SetMatrix(string line, int indexRows)
	{
		int indexColums = 0;
		for(int i = 0; i < line.size(); i++)
		{
			if(line[i] == '1')
			{
				_matrix[indexRows][indexColums++] = 1;
				
				continue;
			}
			if(line[i] == '0')
			{
				_matrix[indexRows][indexColums++] = 0;
				continue;
			}
		}
	}

	void SetNamesVertex(string namesVertex)
	{
		int index = 0;
		for(int i = 0; i < namesVertex.size(); i++)
		{
			if(namesVertex[i] != ' ')
			{
				_namesVertex[index] = namesVertex[i];
				++index;
			}
		}
	}

	bool IsCorrectName(char name)
	{
		for(int i = 0; i < _size; i++)
		{
			if(_namesVertex[i] == name)
			{
				return true;
			}
		}
		return false;
	}

	int GetIndexByNameVertex(char name)
	{
		for(int i = 0; i < _size; i++)
		{
			if(_namesVertex[i] == name)
			{
				return i;
			}
		}
		cout << "Вершины с таким индексом - нет!";
		exit(0);
	}

	int* AddToArray(int *arr, int& size, int newElement)
	{
		size += 1;
		int* newArray = new int[size];
		for(int i = 0; i < size - 1; i++)
		{
			newArray[i] = arr[i];
		}
		newArray[size - 1] = newElement;
		return newArray;
	}

	bool** AllocationMemory(int size)
	{
		bool** arr = new bool* [size];
		for(int i = 0; i < size; i++)
		{
			arr[i] = new bool[size];
		}
		return arr;
	}
};

class Node
{
	private:
	char _name;
	char* _values;
	int _countValue;
	public:

	Node()
	{
		_name = ' ';
		_countValue = 0;
		_values = new char[_countValue];
	}

	Node(int name)
	{
		_name = name;
		_countValue = 0;
		_values = new char[_countValue];
	}

	void AddValue(char newValue)
	{
		char* newValues = new char[_countValue + 1];
		for(int i = 0; i < _countValue; i++)
		{
			newValues[i] = _values[i];
		}
		newValues[_countValue] = newValue;
		++_countValue;
		_values = newValues;
	}

	char GetName()
	{
		return _name;
	}

	char* GetValues()
	{
		return _values;
	}

	int GetCountValues()
	{
		return _countValue;
	}

	void ShowInfo()
	{
		cout << _name << " => ";
		for(int i = 0; i < _countValue - 1; i++)
		{
			cout << _values[i] << ',';
		}
		cout << _values[_countValue - 1] << '\n';
	}
};

class OrGrafOnList
{
	private:
	Node* _nodes;
	int _countNodes;
	public:

	OrGrafOnList()
	{
		_countNodes = 0;
		_nodes = new Node[_countNodes];
	}

	
	void ReadFromFile(string fileName)
	{
		ifstream in;
		in.open(fileName);
		if(in.is_open() == false)
		{
			cout << "Не удалось найти указанный файл.\n";
		}

		string line;
		getline(in, line);
		_countNodes = stoi(line);
		Initialization();

		int countNodes = 0;
		while(getline(in, line))
		{
			for(int i = 0; i < line.size(); i++)
			{
				if(i == 0)
				{
					_nodes[countNodes] = Node(line[0]);
					continue;
				}
				if(line[i] != ' ' && line[i] != ',')
				{
					_nodes[countNodes].AddValue(line[i]);
				}
			}
			++countNodes;
		}
		in.close();
	}
	
	void DeleteVertex(char name)
	{
		if(IsCorrectName(name))
		{
			cout << "Граф имеет следующий список смежности:\n";
			ShowNodes();
			DeleteVertexByName(name);
			cout << "После удаление вершин, которые не могут достичь вершины " << name << " список смежности имеет вид:\n";
			ShowNodes();
		}
		exit(0);
		cout << "Введеной вершины с таким именем - нет!";
	}
	private:

	void DeleteVertexByName(char name)
	{
		int countNodesForDeleting = 0;
		Node* nodesForDeleting = GetNodesForDeleting(name, countNodesForDeleting);
		ShowNodes();
	}

	Node* GetNodesForDeleting(char name, int& countNodesForDeleting)
	{
		Node* nodesForDeleting = new Node[countNodesForDeleting];
		for(int i = 0; i < _countNodes; i++)
		{
			if(_nodes[i].GetName() != name)
			{
				char* tempValue = _nodes[i].GetValues();
				bool isGoodVertex = false;

				for(int j = 0; j < _nodes[i].GetCountValues(); j++)
				{
					if(tempValue[j] == name)
					{
						isGoodVertex == true;
					}
				}
				if(isGoodVertex == false)
				{
					nodesForDeleting = AddNode(nodesForDeleting, _nodes[i], countNodesForDeleting);
					countNodesForDeleting++;
				}
			}
		}
		return nodesForDeleting;
	}

	Node* AddNode(Node* nodes, Node newNode, int size)
	{
		Node* newNodes = new Node[size + 1];
		for(int i = 0; i < size; i++)
		{
			newNodes[i] = nodes[i];
		}
		newNodes[size] = newNode;
		return newNodes;
	}

	void Initialization()
	{
		_nodes = new Node[_countNodes];
	}

	void SetNamesVertex(string line)
	{
		int countNewNodes = 0;
		for(int i = 0; i < line.size(); i++)
		{
			if(line[i] != ' ')
			{
				_nodes[countNewNodes] = Node(line[i]);
				++countNewNodes;
			}
		}
	}

	void ShowNodes()
	{
		for(int i = 0; i < _countNodes; i++)
		{
			_nodes[i].ShowInfo();
		}
	}

	bool IsCorrectName(char name)
	{
		for(int i = 0; i < _countNodes; i++)
		{
			if(_nodes[i].GetName() == name)
			{
				return true;
			}
		}
		return false;
	}
};


void Matrix()
{
	OrGrafOnMatrix grafMatrix;
	grafMatrix.ReadFromFile("fileWithMatrix.txt");

	cout << "Введите название вершины: ";
	char nameVertex;
	cin >> nameVertex;
	grafMatrix.DeleleVertex(nameVertex);
}

void List()
{
	OrGrafOnList grafOnList;
	grafOnList.ReadFromFile("fileWithList.txt");
	
	cout << "Введите название вершины: ";
	char nameVertex;
	cin >> nameVertex;
	grafOnList.DeleteVertex(nameVertex);
}

int main()
{
	setlocale(LC_ALL, "rus");
	//Matrix();
	List();
	return 0;
}