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
    cout << matricula.codigo << "\n";
    cout << matricula.ciclo << "\n";
    cout << fixed << setprecision(2) << matricula.mensualidad << "\n";
    cout << matricula.observaciones << "\n\n";
}

class VariableRecord{
	public:
		VariableRecord(string fileName, string metaData){
			this->fileName = fileName;
            this->metaData = metaData;
		}

		vector<Matricula>  load(){
            Matricula matricula;
            vector<Matricula> matriculas;
            int n = numRecords(this->metaData);
            for(int i=0; i<n-1; i++){
                matricula = readRecord(i);
                matriculas.push_back(matricula);
            }
            return matriculas;
        }

		void add(Matricula matricula){
            int pos = 0;
            inFile.open(this->metaData, ios::in | ios::binary);
            //Si está vacío guarda 0
            if(inFile.peek() == ifstream::traits_type::eof()){
                inFile.close();
                outFile.open(this->metaData, ios::in | ios::binary);
                outFile.write((char*) &pos, sizeof(pos));
                outFile.close();
            }else
                inFile.close();
            
            //Lee la última posición
            int n = numRecords(this->metaData);
            int lastPos;
            inFile.open(this->metaData, ios::in | ios::binary);
            inFile.seekg((sizeof(lastPos))*(n-1), ios::beg);
            inFile.read((char*) &lastPos, sizeof(lastPos));
            inFile.close();
            
            //Suma la última posición con el tamaño del registro a guardar
            //y se guarda como última posición
            outFile.open(this->metaData, ios::app | ios::binary);
            pos = sizeof(matricula) + lastPos;
            outFile.write((char*) &pos, sizeof(pos));
            outFile.close();

            //Guardo el registro
            outFile.open(this->fileName, ios::app | ios::binary);
			outFile.write((char*) &matricula, sizeof(matricula));
            outFile.close();
            
		}

		Matricula readRecord(int pos){
            Matricula temp;
			int posFisica, posFisicaNext;
            inFile.open(this->metaData, ios::in | ios::binary);
            inFile.seekg(sizeof(int)*pos, ios::beg);
            inFile.read((char*) &posFisica, sizeof(posFisica));
            
            inFile.seekg(sizeof(int)*(pos+1), ios::beg);
            inFile.read((char*) &posFisicaNext, sizeof(posFisicaNext));

            inFile.close();
            
            inFile.open(this->fileName, ios::in | ios::binary);            
            inFile.seekg(posFisica, ios::beg);
            inFile.read((char*) &temp, posFisicaNext - posFisica);
            inFile.close();
            
			return temp;
		}
	private:
		ofstream outFile;
		ifstream inFile;
		string fileName;
        string metaData;
};

int main()
{
    //Borrando archivos
    ofstream ofs;
    ofs.open("datos.txt", ofstream::out | ofstream::trunc);
    ofs.close();
    ofs.open("cabecera.dat", ofstream::out | ofstream::trunc);
    ofs.close();

    cout << "\n------------Test add--------------\n";
	VariableRecord variableRecord("datos.txt", "cabecera.dat");
    Matricula m;
    m.codigo = "0003";
    m.ciclo = 2;
    m.mensualidad = 1500.50;
    m.observaciones = "Alumno 1";
    variableRecord.add(m);

    m.codigo = "0004";
    m.ciclo = 6;
    m.mensualidad = 2100.50;
    m.observaciones = "Alumno 2";
    variableRecord.add(m);

    
    cout << "\n------------Test load--------------\n";
    //auto tmp = variableRecord.load();
    //cout << tmp.size() << "\n";
    //for(auto mat : tmp)
    //    printMatricula(mat);
    cout << "\n------------Test readRecord--------------\n";
    Matricula mat;
    mat = variableRecord.readRecord(1);   
    printMatricula(mat);
    //auto mat1 = variableRecord.readRecord(1);
    //printMatricula(mat1);
    
	return 0;
}
