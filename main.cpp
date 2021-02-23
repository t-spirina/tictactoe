#include <iostream>

using namespace std;

int main()
{
   //1 создать и инициализировать переменные пройденных типов

   int intVal; //целочисленный типы данных 4б
   char charVal; //представляет один символ в кодировке ASCII
   long longVal; //целочисленный типы данных 4б
   long long lLongVal;//целочисленный типы данных 8б
   float fltVal;//вещественное число с плавающей точкой 4б
   double dVal;//вещественное число с плавающей точкой 8б
   bool boolVal;//логический тип, принимающий значение истина (значение отличное от 0, обычно 1) или ложь (как правило = 0)
   intVal = 10;
   charVal = 'A';
   longVal = 0x1111222;
   lLongVal = 0x11112222333344;
   fltVal = -3.14;
   dVal = 3.141592;
   boolVal = true;
   cout << "Integer " << intVal << endl;
   cout << "Long integer 0x" << hex <<longVal << endl;
   cout << "Long long integer 0x" << hex << lLongVal << endl;
   cout << "Char " << charVal << endl;
   cout << "Float " << dec << fltVal << endl;
   cout << "Double " << dVal << endl;
   cout << "Bool " << boolVal << endl;

   //2 создать перечисление с возможными вариантами символов для игры в крестики-нолики
   enum ticTacPlay{
       zero, //если в поле нолик
       cross,//если в поле крестик
       empty // в поле пусто
   };

   //3 создать массив, способный содержать значения такого перечисления и инициализировать его
   //размер поля для игры, пока констаната
   const int FieldSize = 3;
   ticTacPlay playField[FieldSize][FieldSize] = {{empty, empty, empty} , {empty, empty, empty} , {empty, empty, empty}};

   //4 создать структуру данных "поле для игры в крестики-нолики" и снабдить его всеми необходимыми свойствами
   enum gameSatus{
       isntStarted,//игра не начата
       inProgress, //игра идет
       crossWin,   //игра завершена выиграли крестики
       zeroWin,    //игра завершена выиграли нолики
       draw        //игра завершена - ничья
   };
   typedef struct{
     ticTacPlay playField[FieldSize][FieldSize];
     gameSatus staus;
   } ticTacToe;

   //5 создать объединение и структуру с битовыми флагами указывающими какого типа значение в данный момент содержится в объединении
   typedef struct{
        int  id:3,
             status:8;
        string msg;
   } msgClnt1; //пусть будет сообщение типа 1

   typedef struct{
        int id:3,
            staus:8;
        string name;
        char buf[100];
   } msgCltn2; // сообщение типа 2
    //допустим, где-то можем получить сообщение двух разных типов, тогда по битовым полям id и status поймем от кого сообщение (id)
    //и нужно ли что-то делать (status)
   union msgFormClnt{
       msgClnt1 Clnt1;
       msgCltn2 Clnt2;
   };
    return 0;
}
