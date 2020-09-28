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
	OrGrafOnMatrix(int size)
	{
		_size = size;
		_matrix = AllocationMemory(_size);
		_namesVertex = new char[_size];
	}

	public:

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

		getline(in, line);
		SetNamesVertex(line);

		int indexRows = 0;
		while(getline(in, line))
		{
			SetMatrix(line, indexRows++);
		}
		in.close();
	}

	void DeleleVertex(char nameVertex)
	{
		cout << "Матрица смежности имеет вид:\n";
		ShowMatrix();
		DeleteVertexByName(nameVertex);
		cout << "После удаление вершин, которые не могут достичь вершины " << nameVertex << " матрица смежности имеет вид:\n";
		ShowMatrix();
	}

	private:

	void DeleteVertexByName(char nameVertex)
	{
		int sizeIndexes = 0;
		int* indexesVertexesForDeleting = GetIndexesVertexesForDeleting(nameVertex, sizeIndexes);
		for(int i = 0; i < sizeIndexes; i++)
		{
			cout << "В вершину " << nameVertex << " нельзя попасть из " << _namesVertex[indexesVertexesForDeleting[i]] << "\n";
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

	int* GetIndexesVertexesForDeleting(char nameVertex, int& sizeIndexes)
	{
		if(IsCorrectNameVertex(nameVertex))
		{
			int size = 0;
			int* indexesForDelete = new int[size];
			int index = GetIndexByNameVertex(nameVertex);
			for(int i = 0; i < _size; i++)
			{
				if(nameVertex != _namesVertex[i])
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

	bool IsCorrectNameVertex(char nameVertex)
	{
		for(int i = 0; i < _size; i++)
		{
			if(_namesVertex[i] == nameVertex)
			{
				return true;
			}
		}
		return false;
	}

	int GetIndexByNameVertex(char nameVertex)
	{
		for(int i = 0; i < _size; i++)
		{
			if(_namesVertex[i] == nameVertex)
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

int main()
{
	setlocale(LC_ALL, "rus");
	OrGrafOnMatrix grafMatrix(4);
	grafMatrix.ReadFromFile("fileWithMatrix.txt");

	cout << "Введите название вершины: ";
	char nameVertex;
	cin >> nameVertex;
	grafMatrix.DeleleVertex(nameVertex);
	
	return 0;
}