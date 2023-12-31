#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_sample_1.h"

QT_BEGIN_NAMESPACE
namespace Ui { class sample_1Class; };
QT_END_NAMESPACE

class sample_1 : public QMainWindow
{
    Q_OBJECT

public:
    sample_1(QWidget *parent = nullptr);
    ~sample_1();

private slots:
    void on_drawRect_triggered();
    void on_clearGraphic_triggered();
    void on_drawWireFrame_triggered();

private:
    Ui::sample_1Class *ui;
};
