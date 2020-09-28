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
		_matrix = new bool*[_size];
		for(int i = 0; i < _size; i++)
		{
			_matrix[i] = new bool[_size];
		}
		_namesVertex = new char[_size];
	}

	public:
	void DeleteVertex(int vertex)
	{
		/*if(vetex == )
		{

		}*/
		for(int i = 0; i < _size; i++)
		{
			if(vertex == i + 1)
			{

			}
		}
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

		getline(in, line);
		SetNamesVertex(line);

		int indexRows = 0;
		while(getline(in, line))
		{
			SetMatrix(line, indexRows);
			++indexRows;
		}
		in.close();
	}

	private:
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
		for(int j = 0; j < line.size(); j++)
		{
			if(line[j] == '1')
			{
				_matrix[indexRows][indexColums] = 1;
				indexColums;
				continue;
			}
			if(line[j] == '0')
			{
				_matrix[indexRows][indexColums] = 0;
				indexColums++;
				continue;
			}
			indexColums = 0;
		}
	}

	void SetNamesVertex(string namesVertex)
	{
		int index = 0;
		for(int i = 0; i < namesVertex.size(); i++)
		{
			if(namesVertex[i] != ' ')
			{
				_namesVertex[index] = _namesVertex[i];
				++index;
			}
		}
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	OrGrafOnMatrix grafMatrix(4);
	grafMatrix.ReadFromFile("fileWithMatrix.txt");

	return 0;
}