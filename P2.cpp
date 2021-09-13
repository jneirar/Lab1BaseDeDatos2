#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#include <vector>

using namespace std;
//" Alumno {{{1
struct Alumno{
	char codigo[5];
	char nombre[11];
	char apellidos[20];
	char carrera[15];
	int ciclo;
	float mensualidad;
	int nextD = 0;
}; 
void printChar(char c[], int s){
	for(int i=0; i<s; i++)	cout << c[i];
}
void printAlumno(Alumno a){
	char sep = '|';
	printChar(a.codigo, 5);	cout << sep;
	printChar(a.nombre, 11);	cout << sep;
	printChar(a.apellidos, 20);	cout << sep;
	printChar(a.carrera, 15);	cout << sep;
	cout << a.ciclo << sep;
	cout << a.mensualidad << "\n";
}
void llenar(char conteiner[], int sizeCont, string data){
	for(int i=0; i<sizeCont; i++){
		if(i < data.size())
			conteiner[i] = data[i];
		else
			conteiner[i] = ' ';
	}
	conteiner[sizeCont - 1] = '\0';
}
//" sobrecarga {{{1
istream & operator >> (istream & stream, Alumno & p)
{	
	stream.read((char*) &p, sizeof(p));
	stream.seekg(sizeof(p));
	return stream;
}

ostream & operator << (ostream & stream, Alumno & p)
{	
	stream.write((char*) &p , sizeof(p));
	return stream;
}

//" FixedRecord {{{1
class FixedRecord{
	public:
		FixedRecord(string fileName){
			this->fileName = fileName;
			
		}

		vector<Alumno> load(){
			file.open(fileName, ios::in | ios::binary);
			vector<Alumno> temps;
			Alumno temp;
			int freeList;
			
			file.read((char*) &freeList, sizeof(freeList));
			
			int cursor = sizeof(freeList);
			file.seekg(cursor, ios::beg);
			
			while(file >> temp){
				if(temp.nextD == 0)
					temps.push_back(temp);
				cursor += sizeof(temp);
				file.seekg(cursor, ios::beg);
			}
			file.close();
			return temps;
		}

		void add(Alumno record){
			int freeList;
			file.open(fileName, ios::in | ios::out | ios::binary);
			file.read((char*) &freeList, sizeof(freeList));
			record.nextD = 0;
			if(freeList == -1){
				file.seekg(0, ios::end);
				file.write((char*) &record, sizeof(record));
			}else{
				Alumno tmp;
				int cursor = sizeof(freeList) + (freeList-1)*sizeof(record);
				file.seekg(cursor, ios::beg);
				file.read((char*) &tmp, sizeof(tmp));
				file.seekg(cursor, ios::beg);
				file.write((char*) &record, sizeof(record));
				freeList = tmp.nextD;
				file.seekg(0, ios::beg);
				file.write((char*) &freeList, sizeof(freeList));
			}
			file.close();
		}

		Alumno readRecord(int pos){
			file.open(fileName, ios::in | ios::binary);
			Alumno temp;
			int freeList;
			int cursor = sizeof(freeList) + (pos-1)*sizeof(temp);
			file.seekg(cursor, ios::beg);
			file.read((char*) &temp, sizeof(temp));
			if(temp.nextD == 0){
				file.close();
				return temp;
			}else{
				Alumno empty;
				cout << "Registro eliminado\n";
				file.close();
				return empty;
			}
		}

		bool _delete(int pos){
			int freeList;
			file.open(fileName, ios::in | ios::out | ios::binary);
			file.read((char*) &freeList, sizeof(freeList));

			Alumno temp;
			file.seekg(((pos-1) * sizeof(temp)) + sizeof(freeList), ios::beg);
			file.read((char*) &temp, sizeof(temp));
			if(temp.nextD != 0)
				return false;
			temp.nextD = freeList;
			file.seekg(((pos-1) * sizeof(temp)) + sizeof(freeList), ios::beg);
			file.write((char*) &temp, sizeof(temp));
			freeList = pos;
			file.seekg(0, ios::beg);
			file.write((char*) &freeList, sizeof(freeList));
			file.close();
			return true;
		}

	private:
		fstream file;
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
int main(){
	//Reiniciando archivo paul.dat
	int i = -1;
	fstream file;
	file.open("paul.dat", ios::out | ios::binary);
	file.write((char*) &i, sizeof(i));
	file.close();

	FixedRecord f("paul.dat");
	Alumno a;
	llenar(a.codigo, 5, "0001");
	llenar(a.nombre, 11, "Jorge");
	llenar(a.apellidos, 20, "Neira");
	llenar(a.carrera, 15, "CS");
	a.ciclo = 5;
	a.mensualidad = 1200.5;
	cout << "Añadir: ";
	printAlumno(a);
	f.add(a);

	llenar(a.codigo, 5, "0002");
	llenar(a.nombre, 11, "Juan");
	llenar(a.apellidos, 20, "Perez");
	llenar(a.carrera, 15, "Electronica");
	a.ciclo = 3;
	a.mensualidad = 2000.5;
	cout << "Añadir: ";
	printAlumno(a);
	f.add(a);

	llenar(a.codigo, 5, "0003");
	llenar(a.nombre, 11, "Pepe");
	llenar(a.apellidos, 20, "Ramirez");
	llenar(a.carrera, 15, "Abogado");
	a.ciclo = 1;
	a.mensualidad = 4500.0;
	cout << "Añadir: ";
	printAlumno(a);
	f.add(a);

	vector<Alumno> alumnos = f.load();
	cout << "\n----------------------------------------\n";
	cout << "Cantidad de registros: " << alumnos.size() << "\n";
	for(Alumno alumno : alumnos)
		printAlumno(alumno);
	
	cout << "\nEliminando registro 1 y 3\n";
	bool flag = f._delete(1);
	flag = f._delete(3);


	alumnos = f.load();
	cout << "\n----------------------------------------\n";
	cout << "Cantidad de registros: " << alumnos.size() << "\n";
	for(Alumno alumno : alumnos)
		printAlumno(alumno);
		
	llenar(a.codigo, 5, "0004");
	llenar(a.nombre, 11, "Nuevo");
	llenar(a.apellidos, 20, "Alumno");
	llenar(a.carrera, 15, "Car");
	a.ciclo = 10;
	a.mensualidad = 3200.0;
	cout << "\nAñadir: ";
	printAlumno(a);
	
	f.add(a);

	alumnos = f.load();
	cout << "\n----------------------------------------\n";
	cout << "Cantidad de registros: " << alumnos.size() << "\n";
	for(Alumno alumno : alumnos)
		printAlumno(alumno);

	a = f.readRecord(2);
	cout << "\nAlumno de la posición 2: \n";
	printAlumno(a);

	a = f.readRecord(3);
	cout << "\nAlumno de la posición 3: \n";
	printAlumno(a);

	cout << "\nAlumno de la posición 1: \n";
	a = f.readRecord(1);

	return 0;
}
