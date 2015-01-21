#include "my_qlabel.h"

void my_qlabel::curve_sphere()
{
    image.copyTo(image_tem);
    circle(image_tem, Point(cursor_pos[0], cursor_pos[1]) , SPHERE_R * scale , Scalar(255,0,255), 1, CV_AA);
    showImage(image_tem);

    // x = a + rcos(t); y = b + rsin(t)
    p_curves.clear();
    p_label.clear();
    vector<Vec2d> my_curve;
    my_curve.resize(100);
    double t;
    for(int i = 0; i < 100; i++)
    {
        t = 2 * PI * i / 100.0;
        my_curve[i][0] = cursor_pos[0] + SPHERE_R * scale * cos(t);
        my_curve[i][1] = cursor_pos[1] + SPHERE_R * scale * sin(t);
    }
    p_curves.push_back(my_curve);
    p_label.push_back(true);
}

void my_qlabel::curve_cone()
{
    image.copyTo(image_tem);
    Vec2i pts[4];
    pts[0] = Vec2i(-CONE_R1 * scale, -H_HEIGHT * scale); // top_left
    pts[1] = Vec2i(CONE_R1 * scale, -H_HEIGHT * scale); // top_right
    pts[2] = Vec2i(CONE_R2 * scale, H_HEIGHT * scale);// bottom_right
    pts[3] = Vec2i(-CONE_R2 * scale, H_HEIGHT * scale); // bottom_left
    double cos_theta = cos(theta / 180.0 * PI);
    double sin_theta = sin(theta / 180.0 * PI);
    for(int i = 0; i < 4; i++)
    {
        double x = pts[i][0], y = pts[i][1];
        pts[i][0] = x * cos_theta - y * sin_theta;
        pts[i][1] = x * sin_theta + y * cos_theta;
        pts[i] += cursor_pos;
    }
    for(int i = 0; i < 4; i++)
    {
        line(image_tem, Point(pts[i][0], pts[i][1]), Point(pts[(i+1)%4][0], pts[(i+1)%4][1]), Scalar(255,0,255), 1, CV_AA);
    }
    showImage(image_tem);

    p_curves.clear();
    p_label.clear();
    for(int i = 0; i < 4; i++)
    {
        vector<Vec2d> my_curve;
        my_curve.resize(100);
        double t;
        for(int j = 0; j < 100; j++)
        {
            t = j / 100.0;
            my_curve[j] = t * Vec2d(pts[i][0], pts[i][1]) + (1.0 - t) * Vec2d(pts[(i+1)%4][0], pts[(i+1)%4][1]);
        }
        p_curves.push_back(my_curve);
        p_label.push_back((i%2) == 0);
    }
}

void my_qlabel::curve_cylinder()
{
    image.copyTo(image_tem);
    Vec2i pts[4];
    pts[0] = Vec2i(-CYLINDER_R * scale, -H_HEIGHT * scale); // top_left
    pts[1] = Vec2i(CYLINDER_R * scale, -H_HEIGHT * scale); // top_right
    pts[2] = Vec2i(CYLINDER_R * scale, H_HEIGHT * scale);// bottom_right
    pts[3] = Vec2i(-CYLINDER_R * scale, H_HEIGHT * scale); // bottom_left
    double cos_theta = cos(theta / 180.0 * PI);
    double sin_theta = sin(theta / 180.0 * PI);
    for(int i = 0; i < 4; i++)
    {
        double x = pts[i][0], y = pts[i][1];
        pts[i][0] = x * cos_theta - y * sin_theta;
        pts[i][1] = x * sin_theta + y * cos_theta;
        pts[i] += cursor_pos;
    }
    for(int i = 0; i < 4; i++)
    {
        line(image_tem, Point(pts[i][0], pts[i][1]), Point(pts[(i+1)%4][0], pts[(i+1)%4][1]), Scalar(255,0,255), 1, CV_AA);
    }
    showImage(image_tem);

    p_curves.clear();
    p_label.clear();
    for(int i = 0; i < 4; i++)
    {
        vector<Vec2d> my_curve;
        my_curve.resize(100);
        double t;
        for(int j = 0; j < 100; j++)
        {
            t = j / 100.0;
            my_curve[j] = t * Vec2d(pts[i][0], pts[i][1]) + (1.0 - t) * Vec2d(pts[(i+1)%4][0], pts[(i+1)%4][1]);
        }
        p_curves.push_back(my_curve);
        p_label.push_back((i%2) == 0);
    }
}

void my_qlabel::curve_sphere(Sphere sphere)
{
    //image.copyTo(image_tem);
	circle(image_tem, Point(sphere.center[0], sphere.center[1]) , sphere.radius , Scalar(255,0,255), 1, CV_AA);
    showImage(image_tem);
}

void my_qlabel::curve_cone(Cone cone)
{
    //image.copyTo(image_tem);
	/*Vec2d center(cone.bottom[0], cone.bottom[1]);
	Vec2d height(cone.norm[0], cone.norm[1]);
	double theta = 3.141592 / 2.0;
	double sin_theta = sin(theta);
	double cos_theta = cos(theta);
	Vec2d c_dir;
	c_dir[0] = height[0] * cos_theta - height[1] * sin_theta;
    c_dir[1] = height[0] * sin_theta + height[1] * cos_theta;
	c_dir[0] = c_dir[0] / sqrt(c_dir[0]*c_dir[0] + c_dir[1]*c_dir[1]);
	c_dir[1] = c_dir[1] / sqrt(c_dir[0]*c_dir[0] + c_dir[1]*c_dir[1]);
	vector<Vec2d> pts(4);
	pts[0] = center + height - c_dir * cone.radius1;
	pts[1] = center + height + c_dir * cone.radius1;
	pts[2] = center - height + c_dir * cone.radius2;
	pts[3] = center - height - c_dir * cone.radius2;*/
	
    Vec2i pts[4];
	double height = sqrt(cone.norm[0]*cone.norm[0] + cone.norm[1]*cone.norm[1]);
	pts[0] = Vec2i(-cone.radius1, -height); // top_left
	pts[1] = Vec2i(cone.radius1, -height); // top_right
    pts[2] = Vec2i(cone.radius2, height);// bottom_right
    pts[3] = Vec2i(-cone.radius2, height); // bottom_left
	double tem = abs(cone.norm[1] / cone.norm[0]);
	double my_theta = atan(tem) - PI / 2.0;
    double cos_theta = cos(my_theta);
    double sin_theta = sin(my_theta);
    for(int i = 0; i < 4; i++)
    {
        double x = pts[i][0], y = pts[i][1];
        pts[i][0] = x * cos_theta - y * sin_theta;
        pts[i][1] = x * sin_theta + y * cos_theta;
		pts[i] += Vec2i(cone.bottom[0],cone.bottom[1]);
    }
    for(int i = 0; i < 4; i++)
    {
        line(image_tem, Point(pts[i][0], pts[i][1]), Point(pts[(i+1)%4][0], pts[(i+1)%4][1]), Scalar(255,0,255), 1, CV_AA);
    }
    showImage(image_tem);
}

void my_qlabel::curve_cylinder(Cylinder cylinder)
{
    //image.copyTo(image_tem);
    Vec2i pts[4];
	double height = sqrt(cylinder.norm[0]*cylinder.norm[0] + cylinder.norm[1]*cylinder.norm[1]);
	pts[0] = Vec2i(-cylinder.radius, -height); // top_left
	pts[1] = Vec2i(cylinder.radius, -height); // top_right
    pts[2] = Vec2i(cylinder.radius, height);// bottom_right
    pts[3] = Vec2i(-cylinder.radius, height); // bottom_left
	double my_theta = atan(cylinder.norm[1] / cylinder.norm[0]) - PI / 2.0;
    double cos_theta = cos(my_theta);
    double sin_theta = sin(my_theta);
    for(int i = 0; i < 4; i++)
    {
        double x = pts[i][0], y = pts[i][1];
        pts[i][0] = x * cos_theta - y * sin_theta;
        pts[i][1] = x * sin_theta + y * cos_theta;
		pts[i] += Vec2i(cylinder.bottom[0],cylinder.bottom[1]);
    }
    for(int i = 0; i < 4; i++)
    {
        line(image_tem, Point(pts[i][0], pts[i][1]), Point(pts[(i+1)%4][0], pts[(i+1)%4][1]), Scalar(255,0,255), 1, CV_AA);
    }
    showImage(image_tem);
}
