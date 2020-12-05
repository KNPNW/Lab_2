#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bitree.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_action_4_triggered();

    void on_pushButton_2_clicked();

    void on_action_triggered();

    void on_action_3_triggered();

private:

    Ui::MainWindow *ui;
    BiTree<class Data, string> mainTree;

    void treatment();
};
#endif // MAINWINDOW_H
