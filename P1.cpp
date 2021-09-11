#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
#define test codigo
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
		inFile.get(record.codigo, sizeof(record.codigo)+1);
		inFile.get(record.nombre, sizeof(record.nombre)+1);
		inFile.get(record.apellidos, sizeof(record.apellidos)+1);
		inFile.get(record.carrera, sizeof(record.carrera)+1);
		
		string enter;
		getline(inFile, enter);
		cout << "enter: " << enter << " -> " << sizeof(enter) << "\n";


		string data;
		getline(inFile, data);
		cout << data << "\n";
		/*
		Alumno record2;
		inFile.get(record2.codigo, sizeof(record2.codigo)+1);
		inFile.get(record2.nombre, sizeof(record2.nombre)+1);
		inFile.get(record2.apellidos, sizeof(record2.apellidos)+1);
		inFile.get(record2.carrera, sizeof(record2.carrera)+1);
		
		cout << record2.test << "\n";
		cout << sizeof record2.test << "\n";
		for(int i=0; i<sizeof record2.test; i++){
			cout << i << " : " << record2.test[i] << "\n";
		}
		
*/
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
	cout << "\n" << records.size() << endl;
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