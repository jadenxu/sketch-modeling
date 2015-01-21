#include "my_qlabel.h"

void my_qlabel::mousePressEvent(QMouseEvent* ev)
{
    if(status == DRAW)
    {
        cur_curve.push_back(Vec2i(ev->x(), ev->y()));
        mouse_press = true;
		//cout<<ev->x()<<" "<<ev->y()<<endl;
    }
    else if(status == SEMANTIC)
    {
        int min_ind = -1;
        double min_dis = INT_MAX;
        for(int i = 0; i < s_curves.size(); i++)
        {
            for(int j = 0; j < s_curves[i].size(); j++)
            {
                double dis = distance(s_curves[i][j], Vec2i(ev->x(), ev->y()));
                if(dis < min_dis)
                {
                    min_dis = dis;
                    min_ind = i;
                }
            }
        }
        if(min_dis < 15)
        {
            s_label[min_ind] = true;
            draw_lines();
        }
    }
}

void my_qlabel::mouseMoveEvent(QMouseEvent* ev)
{
    if(status == DRAW && mouse_press)
    {
        line(image, Point(cur_curve[cur_curve.size() - 1][0], cur_curve[cur_curve.size() - 1][1]), Point(ev->x(), ev->y()), Scalar(0,0,0), 1, CV_AA);
        cur_curve.push_back(Vec2i(ev->x(), ev->y()));
        showImage(image);
    }
    else if(status == SPHERE || status == CYLINDER || status == CONE)
    {
        cursor_pos = Vec2i(ev->x(), ev->y());
        my_update();
    }

}

void my_qlabel::mouseReleaseEvent(QMouseEvent* ev)
{
    if(status == DRAW)
    {
        mouse_press = false;
        cur_curve.push_back(Vec2i(ev->x(), ev->y()));
        if(cur_curve.size() > 3)
        {
            s_curves.push_back(cur_curve);
            s_label.push_back(false);
        }
        cur_curve.clear();
    }
    else if(status == SPHERE || status == CYLINDER || status == CONE)
    {
        cursor_pos = Vec2i(ev->x(), ev->y());
        my_update();
    }
}
