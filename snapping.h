#ifndef SNAPPING_H
#define SNAPPING_H

#include <QMainWindow>
#include <QWidget>
#include <QMessageBox>
#include "ui_snapping.h"
#include "my_qlabel.h"

class snapping : public QMainWindow
{
	Q_OBJECT

public:
    snapping(QWidget *parent = 0, Qt::WFlags flags = 0);
	~snapping();
	void createActions();
	void initial_set();
	void keyPressEvent(QKeyEvent * e);

public slots:
	void openImage();
	void forward();
	void sphere();
	void cylinder();
	void cone();
	void my_draw();
	void about();

private:
	Ui::snappingClass ui;
};

#endif // SNAPPING_H
