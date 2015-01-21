#ifndef PRIMITIVE
#define PRIMITIVE

#include<opencv2/core/core.hpp>
#include <armadillo>
#include <iostream>
using namespace std;
using namespace cv;

enum SHAPE {P_SPHERE, P_CYLINDER, P_CONE};

class Primitive
{
public:
    Primitive(){}
    SHAPE get_shape()
	{
		return shape;
	}
    virtual Vec2i get_id()
    {

        return id;
    }
	SHAPE shape;
    Vec2i id;
};

class Sphere: public Primitive
{
public:
	Sphere(Vec3d center, double radius)
	{
		shape = P_SPHERE;
		this->center = center;
		this->radius = radius;
	}
	Vec3d center;
	double radius;
};

class Cylinder: public Primitive
{
public:
	Cylinder(Vec3d norm, Vec3d bottom, double radius)
	{
		shape = P_CYLINDER;
		this->norm = norm;
		this->bottom = bottom;
		this->radius = radius;
	}

	Vec3d norm;
	Vec3d bottom;
	double radius;
};

class Cone: public Primitive
{
public:
	Cone(Vec3d norm, Vec3d bottom, double radius1, double radius2)
	{
		shape = P_CONE;
		this->norm = norm;
		this->bottom = bottom;
		this->radius1 = radius1;
		this->radius2 = radius2;
	}
	Vec3d norm;
	Vec3d bottom;
	double radius1;
	double radius2;
};

#endif
