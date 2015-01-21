#include "snapping.h"

snapping::snapping(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	setCentralWidget(ui.label);
	this->setWindowTitle("Sketch Snapping 2D View");
	this->resize(500,500);

	createActions();
}

void snapping::createActions()
{
	connect(ui.actionOpen, SIGNAL(triggered()),this, SLOT(openImage()));
	connect(ui.actionSketch_Snapping, SIGNAL(triggered()),this, SLOT(about()));
	connect(ui.actionSphere, SIGNAL(triggered()), this, SLOT(sphere()));
	connect(ui.actionCone, SIGNAL(triggered()), this, SLOT(cone()));
	connect(ui.actionCylinder, SIGNAL(triggered()), this, SLOT(cylinder()));
	connect(ui.actionDraw, SIGNAL(triggered()), this, SLOT(my_draw()));
	connect(ui.actionForward, SIGNAL(triggered()), this, SLOT(forward()));
}

void snapping::sphere()
{
    if (ui.label->status == SEMANTIC||ui.label->status == CYLINDER || ui.label->status == CONE)
    {
        ui.label->status = SPHERE;
        ui.label->scale = 1;
        ui.label->theta = 0;
        if(ui.actionCone->isChecked())
            ui.actionCone->toggle();
        if(ui.actionCylinder->isChecked())
            ui.actionCylinder->toggle();
    }
}

void snapping::cone()
{
    if (ui.label->status == SEMANTIC || ui.label->status == SPHERE || ui.label->status == CYLINDER)
    {
        ui.label->status = CONE;
        ui.label->scale = 1;
        ui.label->theta = 0;
        if(ui.actionCylinder->isChecked())
            ui.actionCylinder->toggle();
        if(ui.actionSphere->isChecked())
            ui.actionSphere->toggle();
    }
}

void snapping::cylinder()
{
    if (ui.label->status == SEMANTIC || ui.label->status == SPHERE || ui.label->status == CONE)
    {
        ui.label->status = CYLINDER;
        ui.label->scale = 1;
        ui.label->theta = 0;
        if(ui.actionCone->isChecked())
            ui.actionCone->toggle();
        if(ui.actionSphere->isChecked())
            ui.actionSphere->toggle();
     }
}

void snapping::initial_set()
{
	
}

void snapping::openImage()
{
	
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
	if(fileName.isEmpty())
		ui.statusBar->showMessage(QString("Cannot load image"));
	else
	{
		initial_set();
		this->resize(ui.label->openImage(fileName));
	}
}

void snapping::my_draw()
{
	ui.label->status = DRAW;
	ui.label->whiteDraw();
}

void snapping::forward()
{
	if(ui.label->status == DRAW)
		ui.label->status = SEMANTIC;

    else if(ui.label->status == CYLINDER ||ui.label->status == CONE||ui.label->status == SPHERE )
    {
        ui.label->status = RELAX;
    }
}

void snapping::about()
{
	QMessageBox::about(this, tr("About Sketch Snapping"), 
		tr("<p>This program is used to build 3D model from sketch.</p>"));
}

void snapping::keyPressEvent(QKeyEvent * e)
{
	if(e->key() == Qt::Key_A)
	{
		ui.label->theta  = (ui.label->theta - 15 + 360) % 360;
	}
	else if(e->key() == Qt::Key_D)
	{
		ui.label->theta  = (ui.label->theta + 15) % 360;
	}
	else if(e->key() == Qt::Key_Q)
	{
		ui.label->scale  = (ui.label->scale == 1)?1:ui.label->scale - 1;
	}
	else if(e->key() == Qt::Key_E)
	{
		ui.label->scale++;
	}
	ui.label->my_update();
}

snapping::~snapping()
{

}

