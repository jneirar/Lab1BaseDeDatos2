#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#include <string>
#include <vector>
using namespace std;

class Alumno{
public:
	char codigo [5];
	char nombre [11];
	char apellidos [20];
	char carrera [15];
};

ostream & operator << (ostream & stream, Alumno & p){
	stream << p.codigo;
	stream << p.nombre;
	stream << p.apellidos;
	stream << p.carrera;
	stream << "\n";
	stream << flush;
	return stream;
}

istream & operator >> (istream & stream, Alumno & p){
	stream.get(p.codigo, 5);
	stream.get(p.nombre, 11);
	stream.get(p.apellidos, 20);
	stream.get(p.carrera, 15);
	return stream;
}

class FixedRecord{
private:
	string fileName;
public:
	FixedRecord(string fileName){
		this->fileName = fileName;
	}
	vector<Alumno> load(){
		vector<Alumno> records;

		ifstream inFile;
		inFile.open(this->fileName);
		
		Alumno record;
		/*inFile.read(record.codigo, 5);
		inFile.read(record.nombre, 11);
		inFile.read(record.apellidos, 20);
		inFile.read(record.carrera, 15);*/
		
		inFile >> record;
		cout << record.codigo << "|\n";
		cout << record.nombre << "|\n";
		cout << record.apellidos << "|\n";
		cout << record.carrera << "|\n";
		
		cin.get();
		inFile >> record;
		cout << record.codigo << "|\n";
		cout << record.nombre << "|\n";
		cout << record.apellidos << "|\n";
		cout << record.carrera << "|\n";
		
		inFile.close();
		
		return records;
	}
	void add(Alumno record){
		
	}
	Alumno readRecord(int pos){
		Alumno a;
		return a;
	}
};



void readFromConsole(char buffer[], int size){
	string temp;			
	cin >> temp;
	for(int i=0; i<size; i++)		
		buffer[i] = (i < temp.size())? temp[i] : ' ';
	buffer[size-1] = '\0';
	cin.clear();
}

int main(){
	string fileName = "datos1.txt";
	FixedRecord fixedRecord(fileName);
	vector<Alumno> records = fixedRecord.load();
	cout << records.size() << endl;
	for(auto A : records)
		cout << A.codigo << " - " << A.nombre << " - " << A.apellidos << " - " << A.carrera << "\n";

	/*
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
	cout << endl;*/
	return 0;
}