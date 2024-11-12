// Lab 10.1.B

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <Windows.h>

using namespace std;

enum Specialization 
{
    ComputerScience,
    Informatics,
    MathEconomics,
    PhysicsInformatics,
    LaborEducation
};

struct Student 
{
    string lastName;
    int course;
    Specialization spec;
    int physicsGrade;
    int mathGrade;
    union {
        int programmingGrade;
        int numericalMethodsGrade;
        int pedagogyGrade;
    };
};

double calculateAverage(const vector<Student>& students, int(Student::* subject)) 
{
    double sum = 0;
    int count = 0;
    for (const auto& student : students) 
    {
        sum += student.*subject;
        count++;
    }
    return count > 0 ? sum / count : 0;
}

int countHighPhysicsGrades(const vector<Student>& students) 
{
    int count = 0;
    for (const auto& student : students) 
    {
        if (student.physicsGrade == 4 || student.physicsGrade == 5) 
        {
            count++;
        }
    }
    return count;
}

string specializationToString(Specialization spec) 
{
    switch (spec) 
    {
    case ComputerScience: return "����'����� �����";
    case Informatics: return "�����������";
    case MathEconomics: return "���������� �� ��������";
    case PhysicsInformatics: return "Գ���� �� �����������";
    case LaborEducation: return "������� ��������";
    default: return "������� ������������";
    }
}

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int numStudents;
    cout << "������ ������� ��������: ";
    cin >> numStudents;
    vector<Student> students(numStudents);

    for (int i = 0; i < numStudents; ++i) 
    {
        cout << "\n������� #" << (i + 1) << ":\n";
        cout << "�������: ";
        cin >> students[i].lastName;
        cout << "����: ";
        cin >> students[i].course;
        int spec;
        cout << "������������ (0 - ����'����� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������): ";
        cin >> spec;
        students[i].spec = static_cast<Specialization>(spec);
        cout << "������ � ������: ";
        cin >> students[i].physicsGrade;
        cout << "������ � ����������: ";
        cin >> students[i].mathGrade;

        if (students[i].spec == ComputerScience) 
        {
            cout << "������ � �������������: ";
            cin >> students[i].programmingGrade;
        }
        else if (students[i].spec == Informatics) 
        {
            cout << "������ � ��������� ������: ";
            cin >> students[i].numericalMethodsGrade;
        }
        else 
        {
            cout << "������ � ���������: ";
            cin >> students[i].pedagogyGrade;
        }
    }

    cout << "\n������ ��������:\n";
    cout << setw(5) << "�" << setw(15) << "�������" << setw(8) << "����" << setw(25) << "������������"
        << setw(10) << "Գ����" << setw(10) << "����������" << setw(15) << "�������������"
        << setw(15) << "������� ������" << setw(15) << "���������" << endl;

    for (int i = 0; i < numStudents; ++i) 
    {
        cout << setw(5) << (i + 1)
            << setw(15) << students[i].lastName
            << setw(8) << students[i].course
            << setw(25) << specializationToString(students[i].spec)
            << setw(10) << students[i].physicsGrade
            << setw(10) << students[i].mathGrade;

        if (students[i].spec == ComputerScience) 
        {
            cout << setw(15) << students[i].programmingGrade << setw(15) << "-" << setw(15) << "-";
        }
        else if (students[i].spec == Informatics) 
        {
            cout << setw(15) << "-" << setw(15) << students[i].numericalMethodsGrade << setw(15) << "-";
        }
        else 
        {
            cout << setw(15) << "-" << setw(15) << "-" << setw(15) << students[i].pedagogyGrade;
        }
        cout << endl;
    }

    double avgPhysics = calculateAverage(students, &Student::physicsGrade);
    double avgMath = calculateAverage(students, &Student::mathGrade);

    cout << "\n������� ��� � ������: " << avgPhysics;
    cout << "\n������� ��� � ����������: " << avgMath;

    int highPhysicsGrades = countHighPhysicsGrades(students);
    cout << "\nʳ������ �������� � ������� '4' ��� '5' � ������: " << highPhysicsGrades << endl;

    return 0;
}
