#include "mainwindow.h"
#include "data.h"
#include "bitree.h"
#include <string>
#include <iostream>
#include <vector>
#include <assert.h>

#include <QApplication>

using namespace std;

void testTree(const string& nameFile){

    Data data1(1, 2, 20);
    Data data2(2, 2, 20);

    BiTree<class Data, string> treeN;
    treeN.fromFile(nameFile);
    BiTree<class Data, string> treeConstryktor(treeN);


    assert(treeN[data1] == "Гравитационная линза");
    assert(treeConstryktor[data1]== "Гравитационная линза");
    assert((treeN==treeConstryktor));

    assert(treeN.isKey(data1) == true);
    assert(treeN.isKey(data2) == false);

    vector<string> minMax = treeN.fromMinToMax();
    assert(minMax[0] == "Резонанс Лидова — Козаи");
    assert(minMax[minMax.size()-1] == "Затмение");

    treeN.push(data2, "Предварение равноденствий");
    assert(treeN.isKey(data2) == true);
    assert(treeN[data2] == "Предварение равноденствий");

    treeN.del(data1);
    assert(treeN.isKey(data1) == false);

    BiTree<class Data, string> empty;
    treeN.delAll();
    assert((empty==treeN));

    treeConstryktor.toFile("/Users/kirillpadalica/HSE/2nd_year/OOP/Laboratory/Lab2/testWrite.txt");
    treeN.fromFile("/Users/kirillpadalica/HSE/2nd_year/OOP/Laboratory/Lab2/testWrite.txt");
    assert((treeN==treeConstryktor));
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

//int main(){
//    testTree("/Users/kirillpadalica/HSE/2nd_year/OOP/Laboratory/Lab2/testData.txt");
//    cout << "Успешно!" << endl;
//    return 0;
//}
