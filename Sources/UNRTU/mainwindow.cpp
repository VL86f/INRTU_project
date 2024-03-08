#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include <QResizeEvent>
#include <QMessageBox>


#include <string.h>
#include <iostream>
#include <unistd.h>

QTextStream in;
QString intext = "";
QString wait = "Waiting";
int resid = 0;


int sim(std::string in, char ss) {
    int co = count(in.begin(), in.end(), ss);

    return co;
}

auto director(int unput) {
    QString Output;
    switch( unput) {
    case -1:
        Output = "*";
        break;
    case 45:
        Output = "↗";
        break;
    case 90:
        Output = "→";
        break;
    case 135:
        Output = "↘";
        break;
    case 180:
        Output = "↓";
        break;
    case 225:
        Output = "↙";
        break;
    case 270:
        Output = "←";
        break;
    case 315:
        Output = "↖";
        break;
    case 0:
        Output = "↑";
        break;
    default:
        Output = "?";
        break;
    }


    return Output;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                                    tr("Text Files (*.txt)"));

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        in.setDevice(&file);

        intext = in.readAll();
        ui->textView->setText(intext);
        file.close();
    }
}


void MainWindow::on_ActionButton_clicked()
{
    std::string incalc = intext.toStdString();





    QMessageBox::information(NULL,QObject::tr("Информация"),tr("Пошло поехало!!"));
    //sleep(2);

    //ui->ActionButton->setFlat(true);

    //ui->textView->clear();

    //std::cout<<incalc<<std::endl;

    int count = strlen(incalc.c_str());
    char sin[count];
    incalc.copy(sin, count);
    //int height = sim(incalc.c_str(), '\n');
    //int width = sim(incalc.c_str(), ';');
    //width=width/height;
    //std::cout<<width<<" "<<height<<std::endl;
    int z = 0;
    int zz=0;
    int vect;
    int min = 1;
    QString symbol;
    QString Outcalc = "";
    //ui->textView->setText("");
    for(int x=0; x < count; x++) {
        if (isdigit(sin[x])) {
            //cout<<"chislo"<<endl;
            z = sin[x]-'0';
            zz=zz*10+z;
        }
        else if (sin[x]=='-') {
            min = -1;
        }
        else if (sin[x]==39) {
            vect=zz*min;
            zz=0;
            min = 1;
            symbol = director(vect);
            Outcalc = Outcalc + symbol;
           // ui->textView->setText(Outcalc);
            //std::cout<<x<<std::endl;

        }
        else if (sin[x]=='\n') {
            //input[h][w]=y;
            //y=0;
            Outcalc = Outcalc + '\n';
            zz=0;
        }
        else if (sin[x]==' ') {
            zz=0;
            Outcalc = Outcalc + " ";
        }
        else {

            zz=0;
        }
        //ui->textView->setText(Outcalc);
    }
    ui->textView->setText(Outcalc);



    QMessageBox::information(NULL,QObject::tr("Информация"),tr("Готовенько"));
    //ui->ActionButton->setFlat(false);


}

void MainWindow::resizeEvent(QResizeEvent* event) {
    int widd = event->size().width();
    int heitt = event->size().height();
    int textwidgetspacedown = 180;
    int textwidgetspaceup = 10;
    int textwidgetspacelr = 10;

    int textviewnewheight = heitt - textwidgetspacedown - textwidgetspaceup;
    int textviewnewwidth = widd - textwidgetspacelr*2;

    int openbx = 10;
    int openby = heitt - 40 - (ui->OpenButton->size().height());

    int actionbx = widd - 10 - (ui->ActionButton->size().width());
    int actionby = heitt - 40 - (ui->ActionButton->size().height());

    ui->ActionButton->move(actionbx, actionby);

    ui->OpenButton->move(openbx, openby);

    ui->textView->resize(textviewnewwidth, textviewnewheight);

    //std::cout<<event->size().height()<<" "<<event->size().width()<<std::endl;

}
