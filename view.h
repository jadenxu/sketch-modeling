#ifndef VIEW_H
#define VIEW_H

#include <QGLViewer/qglviewer.h>
#include <iostream>
#include "primitive.h"

using namespace std;

class Viewer : public QGLViewer
{
protected :
    void draw_primitive(Primitive& p);
	virtual void init();	

public:
	virtual void draw();
	int num_seg;
    vector<Primitive*> p_vector;
	//void updateGL();
};

#endif
