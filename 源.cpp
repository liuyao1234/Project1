#include <iostream>
#include <string>
#include "student.h"
#include "teacher.h"
#include <fstream>
using namespace std;

void menu2() {
    cout << "*****��¼�ɹ���*****\n";
}

void menu1() {
    int p, m, l, t;
    string ID, password, name, subject, classes;

    cout << "\n\t******************\n";
    while (true) {
        cout << "\t******  0.ע��  *******\n";
        cout << "\t******  1.��¼  *******\n";
        cout << "\t******************\n";
        cout << "����������: ";
        cin >> p;

        if (p == 0) {
            ofstream file("s.txt", ios::app | ios::binary); // ׷��д��
            ofstream file2("t.txt", ios::app | ios::binary);

            if (!file) {
                cout << "�޷���ѧ���ļ�����д�����" << endl;
                continue;
            }
            if (!file2) {
                cout << "�޷�����ʦ�ļ�����д�����" << endl;
                continue;
            }

            cout << "\t******  0.������ʦ  *******\n";
            cout << "\t******  1.����ѧ��  *******\n";
            cin >> t;

            if (t == 0) {
                cout << "��������������: ";
                cin >> name;
                cout << "�������˺�: ";
                cin >> ID;
                cout << "����������: ";
                cin >> password;
                cout << "����������ѧ�Ŀ�Ŀ: ";
                cin >> subject;

                teacher t(name, ID, password, subject);
                file2.write(reinterpret_cast<char*>(&t), sizeof(teacher));
            }
            else if (t == 1) {
                cout << "��������������: ";
                cin >> name;
                cout << "���������İ༶: ";
                cin >> classes;
                cout << "�������˺�: ";
                cin >> ID;
                cout << "����������: ";
                cin >> password;

                student s(name, classes, ID, password);
                file.write(reinterpret_cast<char*>(&s), sizeof(student));
            }
            else {
                cout << "�������" << endl;
                continue;
            }

            file.close();
            file2.close();
        }
        else if (p == 1) {
            ifstream file("s.txt", ios::binary);
            ifstream file2("t.txt", ios::binary);

            if (!file) {
                cout << "�޷���ѧ���ļ����ж�ȡ����" << endl;
                continue;
            }
            if (!file2) {
                cout << "�޷�����ʦ�ļ����ж�ȡ����" << endl;
                continue;
            }

            cout << "\t******  0.������ʦ  *******\n";
            cout << "\t******  1.����ѧ��  *******\n";
            cout << "����������: ";
            cin >> m;

            if (m == 0) { // ��ʦ
                cout << "��������������: ";
                cin >> name;
                cout << "�������˺�: ";
                cin >> ID;
                cout << "����������: ";
                cin >> password;

                teacher t;
                bool found = false;
                while (file2.read(reinterpret_cast<char*>(&t), sizeof(teacher))) {
                    if (t.name == name && t.ID == ID && t.password == password) {
                        found = true;
                        break;
                    }
                }

                if (found) {
                    menu2();

                    cout << "\t******  0.��ѯ�α� *******\n";
                    cout << "\t******  1.¼��ѧ���ɼ�  *******\n";
                    cin >> l;

                    if (l == 0) {
                        cout << t.subject << endl;
                    }
                    else if (l == 1) {
                        cout << "������ѧ���˺�: ";
                        cin >> ID;
                        student s;
                        bool student_found = false;
                        while (file.read(reinterpret_cast<char*>(&s), sizeof(student))) {
                            if (s.ID == ID) {
                                student_found = true;
                                break;
                            }
                        }

                        if (student_found) {
                            cout << "������ɼ�: ";
                            cin >> s.grade;

                            // ���´��ļ��Ը���ѧ���ɼ�
                            ofstream tempFile("temp.txt", ios::binary);
                            ifstream origFile("s.txt", ios::binary);
                            student temp;
                            while (origFile.read(reinterpret_cast<char*>(&temp), sizeof(student))) {
                                if (temp.ID == s.ID) {
                                    temp = s;
                                }
                                tempFile.write(reinterpret_cast<char*>(&temp), sizeof(student));
                            }
                            origFile.close();
                            tempFile.close();
                            remove("s.txt");
                            rename("temp.txt", "s.txt");
                        }
                        else {
                            cout << "ѧ��δ�ҵ�" << endl;
                        }
                    }
                }
                else {
                    cout << "��¼��Ϣ����" << endl;
                }
            }
            else if (m == 1) { // ѧ��
                cout << "��������������: ";
                cin >> name;
                cout << "���������İ༶: ";
                cin >> classes;
                cout << "�������˺�: ";
                cin >> ID;
                cout << "����������: ";
                cin >> password;

                student s;
                bool found = false;
                while (file.read(reinterpret_cast<char*>(&s), sizeof(student))) {
                    if (s.name == name && s.classes == classes && s.ID == ID && s.password == password) {
                        found = true;
                        break;
                    }
                }

                if (found) {
                    cout << s.name << " " << s.classes << " ���� " << s.grade << endl;
                }
                else {
                    cout << "��¼��Ϣ����" << endl;
                }
            }
            else {
                cout << "�������" << endl;
            }

            file.close();
            file2.close();
        }
        else {
            cout << "�������" << endl;
        }
    }
}

int main() {
    menu1();
    return 0;
}