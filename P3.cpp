#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Alumno
{  
  string Nombre = "";
  string Apellidos = "";
  string Carrera = "";
  float mensualidad = 0.0;
};

void printAlumno(Alumno alumno){
    cout << alumno.Nombre << "|";
    cout << alumno.Apellidos << "|";
    cout << alumno.Carrera << "|";
    cout << fixed << setprecision(2) << alumno.mensualidad << "\n";
	return;
}
istream & operator >> (istream & stream, Alumno & p){
	p.Nombre = "";
    p.Apellidos = "";
    p.Carrera = "";
    p.mensualidad = 0.0;
    string record;
    string strmensualidad = "";
    int field = 0;
    getline(stream, record);
    for(int i=0; i<record.length(); i++){
        if(record[i] == '|'){
            field++;
            i++;
        }    
        switch (field){
            case 0:{
                p.Nombre += record[i];
                break;
            }
            case 1:{
                p.Apellidos += record[i];
                break;
            }
            case 2:{
                p.Carrera += record[i];
                break;
            }
            case 3:{
                strmensualidad += record[i];
                break;
            }
            default:
                break;
        }
    }
    if(strmensualidad != "")
        p.mensualidad = stof(strmensualidad);
	return stream;
}

ostream & operator << (ostream & stream, Alumno & p)
{	
    stream << p.Nombre << "|";
    stream << p.Apellidos << "|";
    stream << p.Carrera << "|";
    stream << fixed << setprecision(2) << p.mensualidad;
	stream << flush;
	return stream;
}

class VariableRecord{
	public:
		VariableRecord(string fileName){
			this->fileName = fileName;
		}
		vector<Alumno> load(){
			inFile.open(fileName);
            string tmp;
            getline(inFile, tmp);

			Alumno temp;
			vector<Alumno> temps;
			while(inFile >> temp)
				temps.push_back(temp);
			inFile.close();
			return temps;
		}
		void add(Alumno record){
			outFile.open(fileName, ios_base::app);
			outFile << "\n";
			outFile << record;
			outFile.close();
		}
		Alumno readRecord(int pos){
			inFile.open(fileName);
			Alumno temp;
            string str;
			for(int i=0; i<pos+1; i++)
                getline(inFile, str);
            inFile >> temp;
            inFile.close();
			return temp;
		}
	private:
		ofstream outFile;
		ifstream inFile;
		string fileName;
};

void readFromConsole(char buffer[], int size){
	string temp;
	getline(cin, temp);
	for(size_t i=0; i<(size_t)size; i++)		
		buffer[i] = (i < temp.size())? temp[i] : ' ';
	buffer[size-1] = '\0';
	cin.clear();
}


int main()
{
	VariableRecord variableRecord("datos2.txt");

    cout << "\n------------Test load--------------\n";
	vector<Alumno> records = variableRecord.load();
	cout << "Número de registros leídos: " << records.size() << "\n";
	for(Alumno record : records)
		printAlumno(record);
	
    cout << "\n------------Test add--------------\n";
    Alumno alumno;
    alumno.Nombre = "Juan";
    alumno.Apellidos = "Perez Galvez";
    alumno.Carrera = "Ciencias";
    alumno.mensualidad = 2000.00;
    variableRecord.add(alumno);

    records = variableRecord.load();
	cout << "Número de registros leídos: " << records.size() << "\n";
	for(Alumno record : records)
		printAlumno(record);

    cout << "\n------------Test readRecord--------------\n";
    alumno = variableRecord.readRecord(0);
    cout << "Alumno 0: ";
    printAlumno(alumno);
    alumno = variableRecord.readRecord(1);
    cout << "\nAlumno 1: ";
    printAlumno(alumno);
    alumno = variableRecord.readRecord(3);
    cout << "\nAlumno 3: ";
    printAlumno(alumno);

	return 0;
}
