#include "sample_1.h"

sample_1::sample_1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::sample_1Class())
{
    ui->setupUi(this);
    setCentralWidget(ui->openGLWidget);
}

sample_1::~sample_1()
{
    delete ui;
}
