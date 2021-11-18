#ifndef DATE_H
#define DATE_H
#include <string>
using namespace std;


//Funcion Metes fecha en formato dd/mm/yyyy y devuelve el numero de dias que han pasado desde 01/01/1990
int dateToInt(string date);

//Funcion Metes fecha en nDias desde 01.01.1990 y devuelve en formato dd/mm/yyyy
string intToDate(int daysSince1990);

//Funcion Comprueba que el formato de fecha esta bien y que esta existe en el calendario
bool isDateFormatOk(string date);
//Devuelve la fecha de hoy en int (El numero de dias que hace hoy desde 1990)
int today();

//Devuelve si la fecha esta en el pasado, si es hoy devuelve false
bool inThePast(string date);


//Funciones auxiliares
int  getNumberOfDaysInMonth(int month, int year);
bool isLeapYear(int year);

#endif 