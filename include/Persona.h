#include <string>
#include <iostream>

#include "StringHelper.h"

using namespace std;

class Persona{
	private:
		string cedula;
		string nombre;
		string apellido1;
		string apellido2;
		char genero;
		string nacimiento;
		string vencimiento;
	public:
		Persona(unsigned char* raw){
					
				
				cedula = get(raw,0,9);//tmp.substr(0,9);
				trim(cedula);
				
				apellido1 = get(raw,9,35);
				trim(apellido1);
				
				apellido2 = get(raw,35,61);
				trim(apellido2);
				
				nombre = get(raw,61,91);
				trim(nombre);
			
				genero = raw[91];
				
				nacimiento = get(raw,92,96)+"-"+get(raw,96,98)+"-"+get(raw,98,100);
				vencimiento = get(raw,100,104)+"-"+get(raw,104,106)+"-"+get(raw,106,108);
				
		}
		
		void print(){
			cout << cedula << endl << nombre << " " << apellido1 << " " << apellido2 << endl << nacimiento << endl << vencimiento << endl;
		}
};
