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

void sample_1::on_drawRect_triggered()
{
    ui->openGLWidget->drawShape(MyOpenGLWidget::Rect);
}

void sample_1::on_clearGraphic_triggered()
{
    ui->openGLWidget->drawShape(MyOpenGLWidget::None);
}

void sample_1::on_drawWireFrame_triggered()
{
    ui->openGLWidget->setWireFrame(ui->drawWireFrame->isChecked());
}
