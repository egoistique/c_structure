#include <iostream>
using namespace std;

struct printedPublications {
    printedPublications* Next;   // Указатель на следующую структуру в списке.
    char Case;
    union {
        struct { char Name[10], Format[10];} Magazine;
        struct { char Name[40]; char Author[10]; } Studentbook;
    };
    int Pages;
};


printedPublications *DataBase = NULL; // Указатель начала списка - базы данных:

printedPublications InpInfo(char cs){ // Ввод информации о телефонном абоненте варианта cs :
    printedPublications scb;
    if (scb.Case=cs){
        cout << "NAME: "; cin >> scb.Studentbook.Name;
        cout << "AUTHOR: "; cin >> scb.Studentbook.Author;
    }
    else {
        cout << "NAME: "; cin >> scb.Magazine.Name;
        cout << "FORMAT: "; cin >> scb.Magazine.Format;
    }
    cout << "PAGES: "; cin >> scb.Pages;
    return scb;
}

void OutSubscriberInfo(printedPublications scb){  // Вывод информации о телефонном абоненте:
    if (scb.Case){
        cout << scb.Studentbook.Name << " |";
        cout << scb.Studentbook.Author << " |";
    } else cout << scb.Magazine.Name << ' ' << scb.Magazine.Format;
    cout << " | " << scb.Pages << endl;
}


printedPublications* FoundSubscriberNum(int num){ /* Поиск в списке абонента с заданным порядковым номером num в списке (нумеруем, начиная с 0):   */
    printedPublications* p = DataBase;
    while (p!=NULL && num--)   // Пока не конец списка и не найден номер,
        p = p->Next;            // продвигаем указатель вдоль списка.
    return p;   // Возвращаем указатель на найденный элемент или NULL,
}              /* если элемент не найден. */

void AddSubscriber(int num, char cs) { //Добавить нового абонента в список за номером num:
    printedPublications* q = new printedPublications;// Создали новую структуру.
    *q = InpInfo(cs);    // Заполнили ее информацией.
    if (DataBase==NULL) num = 0;   // Если список пустой - добавим в начало.
    if (num) {
        printedPublications* p = DataBase;      // Ищем указатель
        while (p->Next!=NULL && --num) // на предыдущую структуру.
            p = p->Next;
        q->Next = p->Next;
        p->Next = q;// Вставляем новую структуру после *p
    }
    else {
        q->Next = DataBase;
        DataBase = q;
    } // Добавим в начало списка.
}

void DeleteSubscriber(int num){// Удалить абонента с номером num из списка:
    printedPublications* q;
    if (DataBase==NULL) return;
    if (num) {
        printedPublications* p = DataBase;// Ищем указатель на предыдущую структуру.
        while (p->Next!=NULL && --num)
            p = p->Next;
        if ((q=p->Next)!=NULL) {
            p->Next = q->Next;
            delete q;
        }
    }  else { // Удаляем начальный элемент:
        q = DataBase;
        DataBase = q->Next;
        delete q;
    }
}

int main()
{
    printedPublications* p;   int i,j;
    while (1)
    {
        cout << "    MENU SUBD:" << endl
             << "1. INPUT DATA." << endl
             << "2. OUTPUT DATA.." << endl
             << "3. OUTPUT ALL INFO." << endl
             << "4. DELETE DATA." << endl
             << "5. STOP." << endl
             << ">";
        cin >> i;
        switch (i)
        {
            case 1: cout << "NUMBER OF PRINTED EDITION: "; cin >> i;
                cout << "VARIANT (0-Magazine, 1-Studentbook): "; cin >> j;
                AddSubscriber(i,j); break;
            case 2: cout << "NUMBER OF PRINTED EDITION: "; cin >> i;
                if ((p=FoundSubscriberNum(i))!=NULL)
                    OutSubscriberInfo(*p);
                else cout << "NOT FOUND!" << endl;
                break;
            case 3: p = DataBase; i=0;
                while (p!=NULL) {
                    cout << "PRINTED EDITION No" << i++ << ':' << endl;
                    OutSubscriberInfo(*p); p = p->Next;
                }
                break;
            case 4: cout << "NUMBER OF PRINTED EDITION: "; cin >> i;
                DeleteSubscriber(i); break;
            case 5: return 0;

            default: cout << "Поторите ввод!" << endl;
        }
    }
}






















//using namespace std;
///*                   Б А З А   Д А Н Н Ы Х -
//      М А С С И В   С Т Р У К Т У Р   С   В А Р И А Н Т А М И
//*/
//
//// Два варианта телефонных абонентов: квартира и учреждение.
//struct printedPublications {
//    char Case;
//    union {
//        struct { char Name[10], Format[10]; int Number; } Magazine;
//        struct { char Name[40]; char Author[10]; char Subject[10]; } Studentbook;
//    };
//    int Pages;
//};
//
//// Ввод информации о телефонном абоненте варианта cs :
//printedPublications InpSubscriberInfo(char cs) {
//    printedPublications scb;
//    if (scb.Case=cs) {
//        cout << "NAME: "; cin >> scb.Studentbook.Name;
//        cout << "AUTHOR: "; cin >> scb.Studentbook.Author;
//        cout << "SUBJECT: "; cin >> scb.Studentbook.Subject;
//    }
//    else {
//        cout << "NAME: "; cin >> scb.Magazine.Name;
//        cout << "FORMAT: "; cin >> scb.Magazine.Format;
//        cout << "NUMBER: "; cin >> scb.Magazine.Number;
//    }
//    cout << "PAGES: "; cin >> scb.Pages;
//    return scb;
//}
//// Вывод информации о телефонном абоненте:
//void OutSubscriberInfo(printedPublications scb) {
//    if (scb.Case) {
//        cout << scb.Studentbook.Name << " |";
//        cout << scb.Studentbook.Author << " |";
//        cout << scb.Studentbook.Subject << " |";
//    } else cout << scb.Magazine.Name << ' ' << scb.Magazine.Format << " | "
//                << scb.Magazine.Number;
//    cout << " | " << scb.Pages << endl;
//}
////// Увеличить время разговора:
////printedPublications& AddTime(printedPublications& scb, int time) {
////    scb.Pages += time;
////    return scb;
////}
////// Уменьшить время разговора:
////printedPublications* SubTime(printedPublications* scb, int time){
////    scb->Pages -= time;
////    return scb;
////}
//bool remove1(printedPublications* DataBase, int  index, int* length){
//    if(0 <= index && index <= *length){
//        for (int i = index; i < *length; i++) {
//            DataBase[i] = DataBase[i + 1];
//        }
//        (*length)--;
//        return true;
//    }
//    return false;
//}
//
//void remove(printedPublications* DataBase, int  index, int length){
//    if(0 <= index && index <= length){
//        for (int i = index; i < length; i++) {
//            DataBase[i] = DataBase[i + 1];
//        }
//        length--;
//    }
//}
//
//int main() {
//    printedPublications DataBase[10],                  //   База данных.
//    scb = {0, {"null", "null", 0}, 0}; // Пустая структура.
//    int i,j, size = 0;                                  // Очистка базы данных.
//    for (i=0; i<sizeof(DataBase)/sizeof(printedPublications); i++)
//        DataBase[i] = scb;
//    while (1)
//    {
//        cout << "    MENU SUBD:" << endl
//             << "1. INPUT DATA." << endl
//             << "2. OUTPUT DATA." << endl
//             << "3. OUTPUT ALL INFO." << endl
//             << "4. DELETE DATA." << endl
//             << "5. STOP." << endl
//             << ">";
//        cin >> i;
//        switch (i)
//        {
//            case 1: cout << "NUMBER OF PRINTED EDITION: "; cin >> i;
//                cout << "VARIANT (0-Magazine, 1-Studentbook): "; cin >> j;
//                DataBase[i] = InpSubscriberInfo(j);
//                size++;
//                break;
//            case 2: cout << "NUMBER OF PRINTED EDITION: "; cin >> i;
//                OutSubscriberInfo(DataBase[i]); break;
//            case 3: for (i=0; i<sizeof(DataBase)/sizeof(printedPublications); i++){
//                        cout << "PRINTED EDITION No " << i << ':' << endl;
//                        OutSubscriberInfo(DataBase[i]);
//                    }
//                break;
//            case 4: cout << "NUMBER OF PRINTED EDITION: "; cin >> i;
//                remove(DataBase, i, size);
//                break;
//            case 5: return 0;
//
//            default: cout << "Поторите ввод!" << endl;
//        }
//    }
//    return 0;
//}
