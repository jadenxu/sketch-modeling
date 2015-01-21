#include "my_qlabel.h"

double my_qlabel::distance(Vec2i p1, Vec2i p2)
{
    return sqrt(double((p1[0] - p2[0]) * (p1[0] - p2[0]) + (p1[1] - p2[1]) * (p1[1] - p2[1])));
}


double my_qlabel::curve_distance(vector<Vec2i>& sc, vector<Vec2d>& pc)
{
	/*Vec2d s_c(0,0);
	for(int i = 0; i < sc.size(); i++)
	{
		s_c[0] += sc[i][0]; s_c[1] += sc[i][1];
	}
	s_c[0] /= sc.size(); s_c[1] /= sc.size();
	Vec2d p_c(0,0);
	for(int i = 0; i < pc.size(); i++)
	{
		p_c[0] += pc[i][0]; p_c[1] += pc[i][1];
	}
	p_c[0] /= pc.size(); p_c[1] /= pc.size();
	return sqrt(double((s_c[0] - p_c[0]) * (s_c[0] - p_c[0]) + (s_c[1] - p_c[1]) * (s_c[1] - p_c[1])));*/
   double min_dis = INT_MAX;
    for(size_t i = 0; i < sc.size(); i++)
    {
        double tem_dis = 0;
        for(size_t j = 0; j < pc.size(); j++)
        {
            tem_dis = sqrt(double((sc[i][0] - pc[j][0]) * (sc[i][0] - pc[j][0]) + (sc[i][1] - pc[j][1]) * (sc[i][1] - pc[j][1])));
            if(tem_dis < min_dis)
                min_dis = tem_dis;
        }
    }
    return min_dis;
}

void my_qlabel::curve_match()
{
    match_label.clear();
    if (s_curves.size() <= 0)
        return;

	vector<vector<double> > dis_m(p_curves.size(), vector<double>(s_curves.size(), FLT_MAX));
	Vec2i m1_ind(-1,-1);
	double m1_dis = FLT_MAX;
    for(size_t i = 0; i < p_curves.size(); i++)
    {
        if(!p_label[i])
            continue;
        for(size_t j = 0; j < s_curves.size(); j++)
        {
            if(!s_label[j])
                continue;
            dis_m[i][j] = curve_distance(s_curves[j], p_curves[i]);
			if(dis_m[i][j] < m1_dis)
			{
				m1_dis = dis_m[i][j];
				m1_ind = Vec2i(i,j);
			}
        }
    }
	match_label.push_back(m1_ind);
	if(p_curves.size() == 1)
		s_label[m1_ind[1]] = false;
	double m2_dis = FLT_MAX;
	Vec2i m2_ind = Vec2i(-1,-1);
	if(p_curves.size() > 1)
	{
		for(int i = 0; i < dis_m.size(); i++)
		{
			if(i == m1_ind[0])
				continue;
			for(int j = 0; j < dis_m[0].size(); j++)
			{
				if(j == m1_ind[1])
					continue;
				if(dis_m[i][j] < m2_dis)
				{
					m2_dis = dis_m[i][j];
					m2_ind = Vec2i(i,j);
				}
			}
		}
		match_label.push_back(m2_ind);
	}
	//cout<<m1_ind[0]<<" "<<m1_ind[1]<<" "<<m2_ind[0]<<" "<<m2_ind[1]<<endl;
	draw_match();
}

void my_qlabel::draw_match()
{
    for(int i = 0; i < match_label.size(); i++)
    {
        int x1 = match_label[i][0], y1 = p_curves[x1].size() / 2, x2 = match_label[i][1], y2 = s_curves[x2].size() / 2;
        line(image_tem, Point(p_curves[x1][y1][0], p_curves[x1][y1][1]), Point(s_curves[x2][y2][0], s_curves[x2][y2][1]), Scalar(255,255,0), 1, CV_AA);
    }
    showImage(image_tem);
}
