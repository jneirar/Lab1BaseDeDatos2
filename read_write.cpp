#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
using namespace std;

class Alumno
{
public:
	char Nombre [12];
	char Apellidos [12];	
};

ostream & operator << (ostream & stream, Alumno & p)
{	
	stream << p.Nombre;
	stream << p.Apellidos;
	stream << "\n";
	stream << flush;
	return stream;
}

istream & operator >> (istream & stream, Alumno & p)
{	
	stream.get(p.Nombre, 12);		
	stream.get(p.Apellidos, 12);	
	return stream;
}

void readFromConsole(char buffer[], int size){
	string temp;			
	cin >> temp;
	for(int i=0; i<size; i++)		
		buffer[i] = (i < temp.size())? temp[i] : ' ';
	buffer[size-1] = '\0';
	cin.clear();
}

int main()
{
	ofstream outFile;
	ifstream inFile;

	//escribir
	outFile.open("fixedlength.txt");
	Alumno person1;	
	//leer desde consola datos para person1
	readFromConsole(person1.Nombre, 12);
	readFromConsole(person1.Apellidos, 12);
	outFile << person1;
	outFile.close();
	
	//leer
	inFile.open("fixedlength.txt");
	Alumno person2;	
	inFile >> person2;
	cout << person2.Nombre;
	cout << person2.Apellidos;
	cin.get();
	cout << endl;
	return 0;
}