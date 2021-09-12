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
//" sobrecarga {{{1
istream & operator >> (istream & stream, Alumno & p)
{	
	stream.read(p.codigo, sizeof(p.codigo));
	//stream.get();
	stream.read(p.nombre, sizeof(p.nombre));
	//stream.get();
	stream.read(p.apellidos,sizeof(p.apellidos));
	//stream.get();
	stream.read(p.carrera, sizeof(p.carrera));
	stream.get();
	//stream.get();
	
	p.codigo[4] = '\0';
  p.nombre[10] = '\0';
  p.apellidos[19] = '\0';
  p.carrera[14] = '\0';	
	return stream;
}

ostream & operator << (ostream & stream, Alumno & p)
{	
	stream.write(p.codigo, sizeof(p.codigo));
	stream.write(p.nombre, sizeof(p.nombre));
	stream.write(p.apellidos, sizeof(p.apellidos));
	stream.write(p.carrera, sizeof(p.carrera));
	stream << "\n";
	stream << flush;
	return stream;
}

//" FixedRecord {{{1
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
			outFile.open(fileName, ios::app);
			outFile << record;
			outFile.close();
		}
		Alumno readRecord(int pos){
			inFile.open(fileName);
			Alumno temp;
			inFile.seekg(pos * (sizeof(temp)+1), ios::beg);
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
	getline(cin,temp);
	for(size_t i=0; i<(size_t)size; i++)		
		buffer[i] = (i < temp.size())? temp[i] : ' ';
	buffer[size-1] = '\0';
	cin.clear();
}

//" main {{{1
int main()
{
	cout << "Antes del nuevo alumno" << endl;
	FixedRecord f("datos12.txt");
	vector<Alumno> vec = f.load();
	for(size_t i = 0; i < vec.size(); i++)
		cout<<vec[i].codigo <<" "<< vec[i].nombre <<" "<< vec[i].apellidos <<" "<< vec[i].carrera << endl;
	
	Alumno nuevo;
	cout<< "Agregar un alumno" << endl;
	cout<< "Ingresar codigo: ";
	readFromConsole(nuevo.codigo, sizeof(nuevo.codigo));
	cout<< "Ingresar nombre: ";
	readFromConsole(nuevo.nombre, sizeof(nuevo.nombre));
	cout<< "Ingresar apellidos: ";
	readFromConsole(nuevo.apellidos, sizeof(nuevo.apellidos));
	cout<< "Ingresar carrera: ";
	readFromConsole(nuevo.carrera, sizeof(nuevo.carrera));
	f.add(nuevo);

	cout << "Despues de nuevo alumno" << endl;
	vec = f.load();
	for(size_t i = 0; i < vec.size(); i++)
		cout<<vec[i].codigo <<" "<< vec[i].nombre <<" "<< vec[i].apellidos <<" "<< vec[i].carrera << endl;

	int pos;
	cout<< "Obtener registro en la posición: ";
	cin>> pos;
	Alumno r = f.readRecord(pos);
	cout<<r.codigo <<" "<< r.nombre <<" "<< r.apellidos <<" "<< r.carrera << endl;
	return 0;
}
