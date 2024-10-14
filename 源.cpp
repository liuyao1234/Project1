#include <iostream>
#include <string>
#include "student.h"
#include "teacher.h"
#include <fstream>
using namespace std;

void menu2() {
    cout << "*****登录成功！*****\n";
}

void menu1() {
    int p, m, l, t;
    string ID, password, name, subject, classes;

    cout << "\n\t******************\n";
    while (true) {
        cout << "\t******  0.注册  *******\n";
        cout << "\t******  1.登录  *******\n";
        cout << "\t******************\n";
        cout << "请输入数字: ";
        cin >> p;

        if (p == 0) {
            ofstream file("s.txt", ios::app | ios::binary); // 追加写入
            ofstream file2("t.txt", ios::app | ios::binary);

            if (!file) {
                cout << "无法打开学生文件进行写入操作" << endl;
                continue;
            }
            if (!file2) {
                cout << "无法打开老师文件进行写入操作" << endl;
                continue;
            }

            cout << "\t******  0.我是老师  *******\n";
            cout << "\t******  1.我是学生  *******\n";
            cin >> t;

            if (t == 0) {
                cout << "请输入您的姓名: ";
                cin >> name;
                cout << "请输入账号: ";
                cin >> ID;
                cout << "请输入密码: ";
                cin >> password;
                cout << "请输入您教学的科目: ";
                cin >> subject;

                teacher t(name, ID, password, subject);
                file2.write(reinterpret_cast<char*>(&t), sizeof(teacher));
            }
            else if (t == 1) {
                cout << "请输入您的姓名: ";
                cin >> name;
                cout << "请输入您的班级: ";
                cin >> classes;
                cout << "请输入账号: ";
                cin >> ID;
                cout << "请输入密码: ";
                cin >> password;

                student s(name, classes, ID, password);
                file.write(reinterpret_cast<char*>(&s), sizeof(student));
            }
            else {
                cout << "输入错误" << endl;
                continue;
            }

            file.close();
            file2.close();
        }
        else if (p == 1) {
            ifstream file("s.txt", ios::binary);
            ifstream file2("t.txt", ios::binary);

            if (!file) {
                cout << "无法打开学生文件进行读取操作" << endl;
                continue;
            }
            if (!file2) {
                cout << "无法打开老师文件进行读取操作" << endl;
                continue;
            }

            cout << "\t******  0.我是老师  *******\n";
            cout << "\t******  1.我是学生  *******\n";
            cout << "请输入数字: ";
            cin >> m;

            if (m == 0) { // 老师
                cout << "请输入您的姓名: ";
                cin >> name;
                cout << "请输入账号: ";
                cin >> ID;
                cout << "请输入密码: ";
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

                    cout << "\t******  0.查询课表 *******\n";
                    cout << "\t******  1.录入学生成绩  *******\n";
                    cin >> l;

                    if (l == 0) {
                        cout << t.subject << endl;
                    }
                    else if (l == 1) {
                        cout << "请输入学生账号: ";
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
                            cout << "请输入成绩: ";
                            cin >> s.grade;

                            // 重新打开文件以更新学生成绩
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
                            cout << "学生未找到" << endl;
                        }
                    }
                }
                else {
                    cout << "登录信息错误" << endl;
                }
            }
            else if (m == 1) { // 学生
                cout << "请输入您的姓名: ";
                cin >> name;
                cout << "请输入您的班级: ";
                cin >> classes;
                cout << "请输入账号: ";
                cin >> ID;
                cout << "请输入密码: ";
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
                    cout << s.name << " " << s.classes << " 高数 " << s.grade << endl;
                }
                else {
                    cout << "登录信息错误" << endl;
                }
            }
            else {
                cout << "输入错误" << endl;
            }

            file.close();
            file2.close();
        }
        else {
            cout << "输入错误" << endl;
        }
    }
}

int main() {
    menu1();
    return 0;
}