#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

int numRecords(string fileName){
    ifstream file;
    file.open(fileName);
    int begin = file.tellg();
    file.seekg(0, ios::end);
    int end = file.tellg();
    int size = end - begin;
    file.close();
    return size/4;
}
struct Matricula{
    string codigo = "";
    int ciclo = 0;
    float mensualidad = 0.0;
    string observaciones = "";
};

void printMatricula(Matricula &matricula){
    cout << matricula.codigo << "|";
    cout << matricula.ciclo << "|";
    cout << fixed << setprecision(2) << matricula.mensualidad << "|";
    cout << matricula.observaciones << "|\n";
}
istream & operator >> (istream & stream, Matricula & p)
{	
	stream.read((char*) &p, sizeof(p));
	stream.seekg(sizeof(p));
	return stream;
}

ostream & operator << (ostream & stream, Matricula & p)
{	
	stream.write((char*) &p , sizeof(p));
	return stream;
}
class VariableRecord{
	public:
		VariableRecord(string fileDatos, string fileCabecera){
			this->fileDatos = fileDatos;
            this->fileCabecera = fileCabecera;
		}

		vector<Matricula>  load(){
            Matricula matricula;
            vector<Matricula> matriculas;
            int n = numRecords(this->fileCabecera);
            cout << "Hay " << n-1 << " registros\n";
            for(int i=0; i<n-1; i++){
                matricula = readRecord(i);
                matriculas.push_back(matricula);
            }
            return matriculas;
        }

		void add(Matricula matricula){
            int pos = 0;
            file.open(fileCabecera, ios::in | ios::out | ios::binary);
            file.seekg(-sizeof(pos), ios::end);
            //pos guarda la última posición
            file.read((char*) &pos, sizeof(pos));
            //Guardo la posición siguiente
            int posNew = pos + sizeof(matricula);

            file.seekg(0, ios::end);
            file.write((char*) &posNew, sizeof(posNew));
            file.close();

            file.open(fileDatos, ios::app | ios::binary);
            file.write((char*) &matricula, sizeof(matricula));
            file.close();
		}

		Matricula readRecord(int pos){
            int posFisica;
            int posFisicaNext;
            file.open(fileCabecera, ios::in | ios::binary);
            file.seekg((pos-1)*(sizeof(pos)), ios::beg);
            file.read((char*) &posFisica, sizeof(posFisica));
            file.seekg((pos)*(sizeof(pos)), ios::beg);
            file.read((char*) &posFisicaNext, sizeof(posFisicaNext));
            file.close();

            Matricula temp;
            file.open(fileDatos, ios::in | ios::binary);
            file.seekg(posFisica, ios::beg);
            file.read((char*) &temp, posFisicaNext - posFisica);
            file.close();
            
			return temp;
		}
	private:
		fstream file;
		string fileDatos;
        string fileCabecera;
};

int main()
{
    //Borrando archivos
    ofstream ofs;
    ofs.open("datos.txt", ofstream::out | ofstream::trunc);
    ofs.close();
    ofs.open("cabecera.dat", ofstream::out | ofstream::trunc);
    ofs.close();
    fstream f;
    int i = 0;
    f.open("cabecera.dat", ios::in | ios::out | ios::binary);
    f.write((char*) &i, sizeof(i));
    f.close();

    cout << "\n------------Test add--------------\n";
	VariableRecord variableRecord("datos.txt", "cabecera.dat");
    Matricula m;
    m.codigo = "0003";
    m.ciclo = 2;
    m.mensualidad = 1500.50;
    m.observaciones = "Alumno 1";
    printMatricula(m);

    variableRecord.add(m);

    m.codigo = "0005";
    m.ciclo = 5;
    m.mensualidad = 2300.50;
    m.observaciones = "Alumno 2";
    printMatricula(m);

    variableRecord.add(m);

    /*cout << "\n------------Test readRecord 1--------------\n";
    Matricula m2 = variableRecord.readRecord(1);
    printMatricula(m1);*/
    
    cout << "\n------------Test readRecord 2--------------\n";
    Matricula m1 = variableRecord.readRecord(2);
    printMatricula(m1);

    cout << "\n------------Test load--------------\n";
    auto tmp = variableRecord.load();
    cout << tmp.size() << "\n";
    for(auto mat : tmp)
        printMatricula(mat);
	return 0;
}
