#include "my_qlabel.h"
#include "LBFGS.h"
#include "CylinderFunction.h"
#include "ConeFunction.h"
#include "SphereFunction.h"
#include "primitive.h"

vector<Vec2i> my_qlabel::get4points()
{
    vector<Vec2i> si_upper, si_lower;
    Vec2i ul,ur,ll,lr;
    vector<Vec2i> result;
     if(match_label[0][1]!=-1 && match_label[1][1] != -1)
     {
        if(match_label[0][0] == 0)
        {
            si_upper = s_curves[match_label[0][1]];
            si_lower = s_curves[match_label[1][1]];
        }
        else
        {
            si_upper = s_curves[match_label[0][1]];
            si_lower = s_curves[match_label[1][1]];
        }
        double maxdist = 0;
        for (int i =0; i<si_upper.size(); i++)
        {
            for(int j =0; j<si_upper.size(); j++)
            {
                double temp = distance(si_upper[i], si_upper[j]);
                if (maxdist <= temp)
                {
                    maxdist = temp;
                    if(si_upper[i][0]> si_upper[j][0])
                    {
                        ul = si_upper[j];
                        ur = si_upper[i];
                    }
                    else
                    {
                        ul = si_upper[i];
                        ur = si_upper[j];
                    }
                }

            }

        }

        maxdist=0;
        for (int i =0; i<si_lower.size(); i++)
        {
            for(int j =0; j<si_lower.size(); j++)
            {
                double temp = distance(si_lower[i], si_lower[j]);
                if (maxdist <= temp)
                {
                    maxdist = temp;
                    if(si_lower[i][0]> si_lower[j][0])
                    {
                        ll = si_lower[j];
                        lr = si_lower[i];
                    }
                    else
                    {
                        ll = si_lower[i];
                        lr = si_lower[j];
                    }
                }

            }

        }
        result.push_back(ul);
        result.push_back(ur);
        result.push_back(lr);
        result.push_back(ll);
     }

     return result;
}

void my_qlabel::optimization_sphere(Sphere s)
{
	int curve_id= match_label[0][1];
    SphereFunction f(s, s_curves[curve_id]);
	L_BFGS<SphereFunction> opt(f);
	arma::vec coords = f.GetInitialPoint();
	if (!opt.Optimize(coords, 200))
		cout << "L-BFGS reported an error during optimization."<< endl;

    Sphere* result = new Sphere (Vec3d(coords[0], coords[1],0), coords[2]);
	curve_sphere(*result);

	result->id = Vec2i(-1, match_label[0][1]);
	for(int i = 0; i < viewer->p_vector.size(); i++)
	{
		if(viewer->p_vector[i]->get_id() == result->id)
		{
			viewer->p_vector.erase(viewer->p_vector.begin()+i);
			break;
		}
	}
	viewer->p_vector.push_back(result);
	viewer->update();
}

void my_qlabel::optimization_cylinder(Cylinder s)
{
	vector<Vec2i> key_points = get4points();
	CylinderFunction f(s, key_points);
	//arma::vec coords = f.GetInitialPoint();
	//cout<<f.Evaluate(coords)<<endl;
	L_BFGS<CylinderFunction> opt(f);
	arma::vec coords = f.GetInitialPoint();
	if (!opt.Optimize(coords, 200))
		 cout << "L-BFGS reported an error during optimization."<< endl;
	if(coords[4] < 0)
	{
		coords[4] *= -1;
		coords[2] *= -1;
		coords[3] *= -1;
	}
	Cylinder* result =new Cylinder (Vec3d (coords[2],coords[3],0),
            Vec3d(coords[0], coords[1],0), coords[4]);
	curve_cylinder(*result);
	
	int my_small, my_big;
	my_small = min(match_label[0][1], match_label[1][1]);
	my_big = max(match_label[0][1], match_label[1][1]);

	result->id = Vec2i(my_small, my_big);
	for(int i = 0; i < viewer->p_vector.size(); i++)
	{
		if(viewer->p_vector[i]->get_id() == result->id)
        {
			viewer->p_vector.erase(viewer->p_vector.begin()+i);
            break;
         }
	}
     viewer->p_vector.push_back(result);
     viewer->update();
}

void my_qlabel::optimization_cone(Cone s)
{
	vector<Vec2i> key_points = get4points();
	ConeFunction f(s, key_points);
	L_BFGS<ConeFunction> opt(f);
	arma::vec coords = f.GetInitialPoint();
	if (!opt.Optimize(coords, 200))
		 cout << "L-BFGS reported an error during optimization."<< endl;
	cout<<"norm "<<coords[2]<<" "<<coords[3]<<endl;
	
	if(coords[4] < 0 || coords[5] < 0)
	{
		double tem = coords[4];
		coords[4] = abs(coords[5]);
		coords[5] = abs(tem);
		coords[2] *= -1;
		coords[3] *= -1;
	}
	Vec2i dir = key_points[0] - key_points[3];
	cout<<"dir "<<dir[0]<<" "<<dir[1]<<endl;
	if(dir[0]*coords[2] + dir[1]*coords[3] < 0)
	{
		coords[2] *= -1;
		coords[3] *= -1;
	}
	Cone* result =new Cone (Vec3d (coords[2],coords[3],0),
            Vec3d(coords[0], coords[1],0), coords[4], coords[5]);
	curve_cone(*result);
	int my_small, my_big;
	my_small = min(match_label[0][1], match_label[1][1]);
	my_big = max(match_label[0][1], match_label[1][1]);

	result->id = Vec2i(my_small, my_big);
	for(int i = 0; i < viewer->p_vector.size(); i++)
	{
		if(viewer->p_vector[i]->get_id() == result->id)
        {
			viewer->p_vector.erase(viewer->p_vector.begin()+i);
            break;
         }
	}
     viewer->p_vector.push_back(result);
     viewer->update();
}
