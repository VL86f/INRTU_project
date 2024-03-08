#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QTextStream>
#include <QResizeEvent>

#include <string.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_OpenButton_clicked();

    void on_ActionButton_clicked();

    void resizeEvent(QResizeEvent*);

private:
    Ui::MainWindow *ui;
    //QTextStream *in();
};
#endif // MAINWINDOW_H
