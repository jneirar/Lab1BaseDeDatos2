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
	int nextD = -2;
}; 
//" sobrecarga {{{1
istream & operator >> (istream & stream, Alumno & p)
{	
	stream.read((char*) &p, sizeof(p));		
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
			int freeList = -1;
			file.open(fileName, ios::out | ios::binary);
			file << freeList;
			file.close();
		}

		vector<Alumno> load(){

			file.open(fileName, ios::in | ios::binary);
			vector<Alumno> temps;
			Alumno temp;
			int freeList;
			file.read((char*) &freeList, sizeof(freeList));
			while(file >> temp){
				if(temp.nextD == -2)
					temps.push_back(temp);
			}
			file.close();
			return temps;

		}

		void add(Alumno record){
			
			int freeList;
			Alumno temp;
			
			//if(freeList == -1){

				file.open(fileName, ios::app | ios::binary);
				file.read((char*) &freeList, sizeof(freeList));
				file << record;
			//}
			/*else{
				file.seekg((freeList * sizeof(record)) + sizeof(freeList), ios::beg);
				file >> temp;
				file.seekg((freeList * sizeof(record)) + sizeof(freeList), ios::beg);
				freeList = temp.nextD;
				file << record;
				file.seekg(0, ios::beg);
				file << freeList;
			}*/
			file.close();
		}

		Alumno readRecord(int pos){
			file.open(fileName, ios::in | ios::binary);
			Alumno temp;
			int freeList;
			int posr = 0;
			file.read((char*) &freeList, sizeof(freeList));
			while(file >> temp){
				
				if(pos == posr)
					break;			
				if(temp.nextD == -2)
					posr++;
			}
			file.close();
			return temp;
		}

		bool _delete(int pos){
			file.open(fileName, ios::in | ios::out | ios::binary);
			int freeList;
			file.read((char*) &freeList, sizeof(freeList));
			Alumno temp;
			file.seekg((pos * sizeof(temp)) + sizeof(freeList), ios::beg);
			file >> temp;
			if(temp.nextD != -2)
				return false;
			temp.nextD = freeList;
			freeList = pos;
			file.seekg(0, ios::beg);
			file << freeList;
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
	cout << "Antes del nuevo alumno" << endl;
	FixedRecord f("paul.dat");
	vector<Alumno> vec = f.load();
	for(size_t i = 0; i < vec.size(); i++)
		cout<<vec[i].codigo <<" "<< vec[i].nombre <<" "<< vec[i].apellidos <<" "<< vec[i].carrera <<" "<<vec[i].ciclo <<" "<< vec[i].mensualidad <<" "<< vec[i].nextD <<" "<<endl;
	
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
	cout << "ciclo: ";
	cin >> nuevo.ciclo;
	cout << "mensualidad :";
	cin >> nuevo.mensualidad;
	f.add(nuevo);

	cout << "Despues de nuevo alumno" << endl;
	vec = f.load();
	for(size_t i = 0; i < vec.size(); i++)
		cout<<vec[i].codigo <<" "<< vec[i].nombre <<" "<< vec[i].apellidos <<" "<< vec[i].carrera <<" "<<vec[i].ciclo <<" "<< vec[i].mensualidad <<" "<< vec[i].nextD <<" "<<endl;
	

	int pos;
	cout<< "Obtener registro en la posición: ";
	cin>> pos;
	Alumno r = f.readRecord(pos);
	cout<<r.codigo <<" "<< r.nombre <<" "<< r.apellidos <<" "<< r.carrera << " "<< r.ciclo << " "<< r.mensualidad << " "<< r.nextD << " "<<endl;
	return 0;
}
