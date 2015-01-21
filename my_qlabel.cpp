#include "my_qlabel.h"

my_qlabel::my_qlabel(QWidget *parent)
	: QLabel(parent)
{
	status = RELAX;
	mouse_press = false;
	scale = 1;
	theta = 0;
    viewer = new Viewer();
    viewer->setWindowTitle("Sketch Snapping 3D View");
    viewer->show();
}

my_qlabel::~my_qlabel()
{

}

QSize my_qlabel::openImage(const QString& fileName)
{
    image = imread("ok.jpg");

    Mat tem;
    cvtColor(image,tem,CV_BGR2RGB);
    QImage img = QImage(tem.data, tem.cols, tem.rows, tem.cols*3, QImage::Format_RGB888);
    this->setPixmap(QPixmap::fromImage(img));
    this->resize(this->pixmap()->size());
    return this->pixmap()->size();
}

void my_qlabel::whiteDraw()
{
    cur_curve.clear();
    s_curves.clear();
    p_curves.clear();
    s_label.clear();
    match_label.clear();
    p_label.clear();
    viewer->p_vector.clear();
	image = Mat(500,500,CV_8UC3);
	for(int i = 0; i < image.rows; i++)
	{
		for(int j = 0; j < image.cols; j++)
			image.at<Vec3b>(i,j) = Vec3b(255,255,255);
	}
	Mat tem;
	cvtColor(image,tem,CV_BGR2RGB);
	QImage img = QImage(tem.data, tem.cols, tem.rows, tem.cols*3, QImage::Format_RGB888);
	this->setPixmap(QPixmap::fromImage(img));
	this->resize(this->pixmap()->size());
}

void my_qlabel::my_update()
{
	if(status == SPHERE)
	{
		//we first draw the primitive and obtain its curves and label
		curve_sphere();
		//after than we do curve match, and draw the match line
        curve_match();
        Sphere s(Vec3d(cursor_pos[0], cursor_pos[1], 0), SPHERE_R * scale);
		//do optimization, get its 3D properties
        optimization_sphere(s);
	}
	else if(status == CYLINDER)
	{
		curve_cylinder();
		curve_match();
		cout<<"ok1"<<endl;
        //TO DO: pass the cylinder
		double cos_theta = cos(theta / 180.0 * PI);
		double sin_theta = sin(theta / 180.0 * PI);
		double x = scale * H_HEIGHT * sin_theta;
        double y = scale * (-H_HEIGHT) * cos_theta;
        Cylinder cylinder(Vec3d(x,y,0), Vec3d(cursor_pos[0], cursor_pos[1], 0), scale*CYLINDER_R);
        optimization_cylinder(cylinder);
		cout<<"ok2"<<endl;
	}
	else if(status == CONE)
	{
		curve_cone();
		curve_match();
        //TO DO: pass the CONE
		double cos_theta = cos(theta / 180.0 * PI);
		double sin_theta = sin(theta / 180.0 * PI);
		double x = scale * H_HEIGHT * sin_theta;
        double y = scale * (-H_HEIGHT) * cos_theta;
        Cone cone(Vec3d(x,y,0), Vec3d(cursor_pos[0], cursor_pos[1], 0), scale*CONE_R1, scale*CONE_R2);
        optimization_cone(cone);
	}
}

void my_qlabel::showImage(Mat& s_img)
{
	Mat tem;
	s_img.copyTo(tem);
	cvtColor(tem,tem,CV_BGR2RGB);
	QImage img = QImage(tem.data, tem.cols, tem.rows, tem.cols*3, QImage::Format_RGB888);
	this->setPixmap(QPixmap::fromImage(img));
}

void my_qlabel::draw_lines()
{
	Mat tem;
	image.copyTo(tem);
	for(int i = 0; i < tem.rows; i++)
	{
		for(int j = 0; j < tem.cols; j++)
			tem.at<Vec3b>(i,j) = Vec3b(255,255,255);
	}
    for(size_t i = 0; i < s_curves.size(); i++)
	{
        for(size_t j = 0; j < s_curves[i].size() - 1; j++)
		{
			Scalar color;
			if(s_label[i])
				color = Scalar(0,0,255);
			else
				color = Scalar(0,0,0);
			line(tem, Point(s_curves[i][j][0], s_curves[i][j][1]), Point(s_curves[i][j+1][0], s_curves[i][j+1][1]), color, 1, CV_AA);
		}
	}
	showImage(tem);
}
