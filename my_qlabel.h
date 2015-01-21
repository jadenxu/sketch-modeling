#ifndef MY_QLABEL_H
#define MY_QLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QSize>

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<vector>

#include "view.h"
#include "primitive.h"

using namespace std;
using namespace cv;

enum Status {DRAW,SEMANTIC,RELAX,SPHERE,CYLINDER,CONE};
#define CYLINDER_R 10
#define H_HEIGHT 20
#define CONE_R1 8
#define CONE_R2 14
#define SPHERE_R 10
#define PI 3.1415927

class my_qlabel : public QLabel
{
	Q_OBJECT

public:
	my_qlabel(QWidget *parent);
	~my_qlabel();
	QSize openImage(const QString& fileName);
	void whiteDraw();
	void mousePressEvent(QMouseEvent* ev);
	void mouseMoveEvent(QMouseEvent* ev);
	void mouseReleaseEvent(QMouseEvent* ev);
	void showImage(Mat& s_img);
	double distance(Vec2i p1, Vec2i p2);
	void draw_lines();
	void curve_sphere();
	void curve_cone();
	void curve_cylinder();
	void curve_sphere(Sphere sphere);
	void curve_cone(Cone cone);
	void curve_cylinder(Cylinder cylinder);
	void curve_match();
	void optimization_sphere(Sphere s);
  void optimization_cone(Cone s);
  void optimization_cylinder(Cylinder s);
	void my_update();
	double curve_distance(vector<Vec2i>& sc, vector<Vec2d>& pc);
	void draw_match();
	vector<Vec2i> get4points();
	Status status;
	int scale;
	int theta;
	Mat image;

private:
  vector< vector< Vec2i> > s_curves;
	vector<bool> s_label;
  vector< vector< Vec2d> > p_curves;
  vector<bool> p_label;
	vector<Vec2i> cur_curve;
  vector<Vec2i> match_label;
  Viewer* viewer;
	Vec2i cursor_pos;
	bool mouse_press;
	Mat image_tem;
};

#endif // MY_QLABEL_H
