#include <iostream>
#include <armadillo>
#include "primitive.h"

class SphereFunction
{
public:
	SphereFunction(){};
    SphereFunction( Sphere s, vector<Vec2i> s_points);
    
    double Evaluate(const arma::mat& coordinates);
    void Gradient(const arma::mat& coordinates, arma::mat& gradient);
    
    const arma::mat& GetInitialPoint() const { return initialPoint; }
    int length() {return mylength;}
private:
    arma::mat initialPoint;
    vector<Vec2i> si;
    int mylength;
};

SphereFunction::SphereFunction(Sphere s, vector<Vec2i> s_points)
{
    si = s_points;
	mylength = si.size();
    initialPoint.zeros(3,1);
    initialPoint[0] = s.center[0];
    initialPoint[1] = s.center[1];
    initialPoint[2] = s.radius;
}

double SphereFunction::Evaluate(const arma::mat& coordinates)
{
    // f(x) = from 1 to N sum ((cxy - si)^2 -r^2)^2
    double result=0;
    double cx= coordinates[0];
    double cy= coordinates[1];
    double r=coordinates[2];
    for (int i=0; i<mylength;i++)
    {
        double exp = pow(cx-si[i][0],2)+pow(cy-si[i][1], 2)- r*r;
        result += pow(exp,2);
    }
    return result/mylength;
}

void SphereFunction::Gradient(const arma::mat& coordinates,
                              arma::mat& gradient)
{
    // f'_x1(x) = 12 x_1 + 4 x_2
    // f'_x2(x) = 4 x_1 + 6 x_2
    double cx= coordinates[0];
    double cy= coordinates[1];
    double r= coordinates[2];
    
    gradient.set_size(3, 1);
    gradient.zeros(3, 1);
    double exp1, exp2, exp3;
    for (int i=0; i<mylength;i++)
    {
        exp1 =4*(cx-si[i][0]) * (pow(cx-si[i][0],2)+pow(cy-si[i][1], 2)- r*r);
        gradient[0] += exp1;
        
        exp2 =4*(cy-si[i][1]) * (pow(cx-si[i][0],2)+pow(cy-si[i][1], 2)- r*r);
        gradient[1] += exp2;
        
        exp3 =-4*r * (pow(cx-si[i][0],2)+pow(cy-si[i][1], 2)- r*r);
        gradient[2] += exp3;
    }
    //cout<<"gradient: "<<gradient[0]<<" "<<gradient[1]<<" "<<gradient[2]<<endl;
    gradient[0] /= mylength;
    gradient[1] /= mylength;
    gradient[2] /= mylength;
}