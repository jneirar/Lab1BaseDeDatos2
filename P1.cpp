#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#include <vector>

using namespace std;

struct Alumno
{
	char codigo[5];
	char nombre [11];
	char apellidos [20];
	char carrera[15];
};

istream & operator >> (istream & stream, Alumno & p)
{	
	stream.get(p.codigo, 5);		
	stream.get(p.nombre, 11);
	stream.get(p.apellidos, 20);
	stream.get(p.carrera, 15);
	return stream;
}

ostream & operator << (ostream & stream, Alumno & p)
{	
	stream << p.codigo;
	stream << p.nombre;
	stream << p.apellidos;
	stream << p.carrera;
	stream << "\n";
	stream << flush;
	return stream;
}

class FixedRecord{
	public:
		FixedRecord(string fileName){
			this->fileName = fileName;
		}
		vector<Alumno> load(){
			inFile.open(fileName);
			Alumno temp;
			vector<Alumno> temps;
			while(inFile >> temp){
				temps.push_back(temp);
			}
			inFile.close();
			return temps;
		}
		void add(Alumno record){
			outFile.open(fileName);
			outFile << record;
			outFile.close();
		}
		Alumno readRecord(int pos){
			inFile.open(fileName);
			Alumno temp;
			inFile.seekg(pos * sizeof(Alumno), ios::beg);
			inFile >> temp; 
			return temp;
		}
	private:
		ofstream outFile;
		ifstream inFile;
		string fileName;
};

void readFromConsole(char buffer[], int size){
	string temp;			
	cin >> temp;
	for(size_t i=0; i<(size_t)size; i++)		
		buffer[i] = (i < temp.size())? temp[i] : ' ';
	buffer[size-1] = '\0';
	cin.clear();
}

int main()
{
	
	return 0;
}
