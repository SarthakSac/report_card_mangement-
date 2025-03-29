#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int flag = 0;

struct Student {
    char name[50];
    char sec;
    char status[10];
    int clas, roll, m, p, c, e;
    float per;
} s;

int Check_only(char n[]) {
    int found = 0;
    fstream h;
    h.open("rep", ios::in); 

    if (!h) {
        cout << "File doesn't exist.\n";
        return 0;
    }

    while (h.read((char*)&s, sizeof(s))) { 
        if (s.roll == atoi(n) || strcmpi(s.name, n) == 0) { 
            found = 1;
            break;
        }
    }
    h.close();
    return found;
}

void Check_view() {
    char n[50];

    cout << "\n Enter name of student or roll no: ";
    cin.ignore();
    cin.getline(n, 50);

    if (!Check_only(n)) {
        cout << "Record doesn't exist.\n";
        return;
    }

    fstream h;
    h.open("rep", ios::in);

    if (!h) {
        cout << "File doesn't exist.\n";
        return;
    }

    while (h.read((char*)&s, sizeof(s))) {
        if (s.roll == atoi(n) || strcmpi(s.name, n) == 0) {
            cout << "Record found. Displaying details:\n";
            cout << "Name: " << s.name << "\nClass: " << s.clas << "\nSection: " << s.sec;
            cout << "\nRoll No: " << s.roll << "\nMarks - Maths: " << s.m << ", Physics: " << s.p 
                 << ", Chemistry: " << s.c << ", English: " << s.e;
            cout << "\nPercentage: " << s.per << "%\nStatus: " << s.status << endl;
            break;
        }
    }
    h.close();
}

void AddReport() {
    char choice;
    fstream n, h;

    start:
    n.open("rep", ios::app);

    if (!n) {
        h.open("rep", ios::out);
        h.close();
        goto start;
    } else {
        do {
            cout << "\n Enter name of student: ";
            cin.ignore();
            cin.getline(s.name, 50);

            cout << "\n Enter class of student: ";
            cin >> s.clas;

            cout << "\n Enter section of student: ";
            cin >> s.sec;

            cout << "\n Enter roll no. of student: ";
            cin >> s.roll;

            cout << "\n Enter marks in:\n Maths: ";
            cin >> s.m;

            cout << "\n Enter marks in:\n Physics: ";
            cin >> s.p;

            cout << "\n Enter marks in:\n Chemistry: ";
            cin >> s.c;

            cout << "\n Enter marks in:\n English: ";
            cin >> s.e;

            s.per = ((s.m + s.p + s.c + s.e) / 400.0) * 100;

            if (s.per >= 50)
                strcpy(s.status, "Pass");
            else
                strcpy(s.status, "Fail");

            n.write((char*)&s, sizeof(s));

            s:
            cout << "\n Want to enter more reports (y/n): ";
            cin >> choice;

            if (choice == 'y' || choice == 'Y') { }
            else if (choice == 'n' || choice == 'N') break;
            else {
                cout << "Enter valid choice";
                goto s;
            }

        } while (1);

        n.close();
    }
}

void search() {
    int choice;

    start:
    cout << "\n Check Only(1)";
    cout << "\n Check and view(2)";
    cout << "\n Exit(3)";

    cin >> choice;

    if (choice == 3)
        return;
    else if (choice == 1) {
        char n[50];
        cout << "\n Enter name of student or roll no: ";
        cin.ignore();
        cin.getline(n, 50);

        if (Check_only(n))
            cout << "Record exists.\n";
        else
            cout << "Record doesn't exist.\n";
    }
    else if (choice == 2)
        Check_view();
    else {
        cout << "Enter valid choice";
        goto start;
    }
}

void report_menu() {
    int choice;
    cout << "\n\n\n\n\t\tReport Card Menu";
    cout << "\n\t 1.ADD";
    cout << "\n\t 2.SEARCH";
    cout << "\n\t 3.EXIT";

    cin >> choice;

    if (choice == 1)
        AddReport();
    else if (choice == 2)
        search();
    else if (choice == 3)
        return;
    else {
        cout << "Enter valid choice";
        flag = 1;
    }
}

int main() {
    start:
    report_menu();
    if (flag == 1)
        goto start;

    return 0;
}
