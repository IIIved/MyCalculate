#include "mainwindow.h"
#include "./ui_mainwindow.h"

double firstNum;
bool userIsTypingSecondNumber = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_zero,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9,SIGNAL(clicked()), this, SLOT(digits_numbers()));

    connect(ui->pushButton_plus_minus,SIGNAL(clicked()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_procent,SIGNAL(clicked()), this, SLOT(unary_operation_pressed()));

    connect(ui->pushButton_plus,SIGNAL(clicked()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_minus,SIGNAL(clicked()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_delit,SIGNAL(clicked()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_x,SIGNAL(clicked()), this, SLOT(binary_operation_pressed()));

    //Какая из них была нажата, врубаем ее
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_delit->setCheckable(true);
    ui->pushButton_x->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers(){
    QPushButton *button = (QPushButton*)sender(); //Объявляем кнопку и даем значение отправителя

    double labelNumber;
    QString newLabel;

    if((ui->pushButton_plus->isChecked() || ui->pushButton_minus->isChecked()
            || ui->pushButton_x->isChecked() || ui->pushButton_delit->isChecked()) && (!userIsTypingSecondNumber)){
        labelNumber = button->text().toDouble();
        userIsTypingSecondNumber = true;
    } else {
        labelNumber = (ui->label->text() + button->text()).toDouble();
    }

    newLabel = QString::number(labelNumber, 'g', 15);

    ui->label->setText(newLabel);

}

void MainWindow::on_pushButton_tochka_clicked()
{
    ui->label->setText(ui->label->text() + ".");
}

void MainWindow::unary_operation_pressed(){

    QPushButton * button = (QPushButton*)sender(); //Объявляем кнопку и даем значение отправителя
    double labelNumber;
    QString newLabel;

    if(button->text() == "+/-"){
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * - 1; //Делаем отрицательное число
        newLabel = QString::number(labelNumber, 'g', 15); //Максимум доступных чисел 15, далее сворачивается
        ui->label->setText(newLabel); //Задаем текст
    }

    if(button->text() == "%"){
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * 0.01;
        newLabel = QString::number(labelNumber, 'g', 15); //Максимум доступных чисел 15, далее сворачивается
        ui->label->setText(newLabel); //Задаем текст
    }
}

void MainWindow::on_pushButton_clear_released(){
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_x->setChecked(false);
    ui->pushButton_delit->setChecked(false);

    userIsTypingSecondNumber = false;

    ui->label->setText("0");
}

void MainWindow::on_pushButton_ravno_released(){

    QString newLabel;
    double labelNumber;
    double secondNum;
    secondNum = ui->label->text().toDouble();


    if(ui->pushButton_plus->isChecked()){
        labelNumber = firstNum + secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel); //Устанавливаем метку
        ui->pushButton_plus->setChecked(false);
    }
    else if(ui->pushButton_minus->isChecked()){
        labelNumber = firstNum - secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel); //Устанавливаем метку
        ui->pushButton_minus->setChecked(false);
    }
    else if(ui->pushButton_x->isChecked()){
        labelNumber = firstNum * secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel); //Устанавливаем метку
        ui->pushButton_x->setChecked(false);
    }
    else if(ui->pushButton_delit->isChecked()){
        labelNumber = firstNum / secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel); //Устанавливаем метку
        ui->pushButton_delit->setChecked(false);
    }

    userIsTypingSecondNumber = false;
}

void MainWindow::binary_operation_pressed(){
    QPushButton * button = (QPushButton*)sender();

    //Выяснить, какой номер указан
    //Сохраним это в переменной
    firstNum = ui->label->text().toDouble();

    button->setChecked(true); //Кнопка была нажата

}

