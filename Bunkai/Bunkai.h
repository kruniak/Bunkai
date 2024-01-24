#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Bunkai.h"

class Bunkai : public QMainWindow
{
    Q_OBJECT

public:
    Bunkai(QWidget *parent = nullptr);
    ~Bunkai();

private slots:
    void on_actionOpen_triggered();

private:
    Ui::BunkaiClass ui;
};
