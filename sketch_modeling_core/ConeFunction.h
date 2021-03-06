#include <iostream>
#include <armadillo>
#include "primitive.h"

class ConeFunction
{
public:
	ConeFunction(){}; // initialize initial point
	ConeFunction(Cone s, vector<Vec2i> key_points);
	double Evaluate(const arma::mat& coordinates);
	void Gradient(const arma::mat& coordinates, arma::mat& gradient);

	const arma::mat& GetInitialPoint() const {return initialPoint;};

private:
	arma::mat initialPoint;
	vector<Vec2i> key_points;
};

ConeFunction::ConeFunction(Cone s, vector<Vec2i> key_points)
{
	initialPoint.set_size(6,1);
	initialPoint[0] = s.bottom[0];
	initialPoint[1] = s.bottom[1];
	initialPoint[2] = s.norm[0];
	initialPoint[3] = s.norm[1];
	initialPoint[4] = s.radius1;
	initialPoint[5] = s.radius2;
	this->key_points = key_points;
}

double ConeFunction::Evaluate(const arma::mat& coordinates)
{
	Vec2d center(coordinates[0], coordinates[1]);
	Vec2d height(coordinates[2], coordinates[3]);
	double theta = 3.141592 / 2.0;
	double sin_theta = sin(theta);
	double cos_theta = cos(theta);
	Vec2d c_dir;
	c_dir[0] = height[0] * cos_theta - height[1] * sin_theta;
    c_dir[1] = height[0] * sin_theta + height[1] * cos_theta;
	c_dir[0] = c_dir[0] / sqrt(c_dir[0]*c_dir[0] + c_dir[1]*c_dir[1]);
	c_dir[1] = c_dir[1] / sqrt(c_dir[0]*c_dir[0] + c_dir[1]*c_dir[1]);
	vector<Vec2d> p_points(4);
	p_points[0] = center + height - c_dir * coordinates[4];
	p_points[1] = center + height + c_dir * coordinates[4];
	p_points[2] = center - height + c_dir * coordinates[5];
	p_points[3] = center - height - c_dir * coordinates[5];

	double dis = 0;
	for(int i = 0; i < 4; i++)
	{
		dis += (p_points[i][0] - key_points[i][0]) * (p_points[i][0] - key_points[i][0]) + (p_points[i][1] - key_points[i][1]) * (p_points[i][1] - key_points[i][1]);
		//cout<<p_points[i][0]<<" "<<p_points[i][1]<<" "<<key_points[i][0]<<" "<<key_points[i][1]<<endl;
	}

	return dis;
}

void ConeFunction::Gradient(const arma::mat& coordinates, arma::mat& gradient)
{
	gradient.set_size(6, 1);
    gradient.zeros(6, 1);
	arma::mat coor;

	double delta = 1e-5;
    for(int i = 0; i < 6; i++)
	{
		coor = coordinates;
		double f_old = Evaluate(coor);
		coor[i] += delta;
		double f_new = Evaluate(coor);
		gradient[i] = (f_new - f_old) / delta;
	}
}