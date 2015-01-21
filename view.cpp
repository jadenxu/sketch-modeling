#include "view.h"

void Viewer::init()
{
	// Restore previous viewer state.
	restoreStateFromFile();

    glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                   // Black Background
    glClearDepth(1.0f);                         // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                         // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective
    camera()->setPosition(qglviewer::Vec(250,250,700));
	//camera()->setOrientation(qglviewer::Vec(1,0,0));
    camera()->lookAt(qglviewer::Vec(250,250,0));
    camera()->setUpVector(qglviewer::Vec(0,1,0));
	camera()->setSceneRadius(1000);
	this->resize(520,520);
	camera()->setSceneCenter(qglviewer::Vec(255,255,0));
    //setSceneRadius(100.0);          // scene has a 100 OpenGL units radiusden
    //setSceneCenter(qglviewer::Vec(0,0,0) ); // with a center shifted by 400 units along X direction
    //camera()->showEntireScene();
}

void Viewer::draw()
{
	//cout<<camera()->upVector().x<<" "<<camera()->upVector().y<<" "<<camera()->upVector().z<<endl;
	//glPushMatrix();
	//glTranslated(490,500-s_point->center[1] ,0);
    //gluSphere(quadratic, s_point->radius, 100, 100);
	//glLoadIdentity();
    for(size_t i = 0; i < p_vector.size(); i++)
	{
		glPushMatrix();
        draw_primitive(*p_vector[i]);
		glPopMatrix();
    }
}

void Viewer::draw_primitive(Primitive& p)
{
    /*Sphere* s_point = NULL;
    Cylinder* cy_point = NULL;
    Cone* co_point = NULL;
    if (p!= NULL  && p->get_shape() == P_SPHERE)
        s_point = static_cast<Sphere*> (p);
    if (p!= NULL && p->get_shape() == P_CYLINDER)
        cy_point = (Cylinder*) p;
    if (p!= NULL && p->get_shape() == P_CONE )
        co_point = (Cone*) p;*/
	Primitive *pri = &p;
	Sphere* s_point = dynamic_cast<Sphere*>(pri);
	Cylinder* cy_point = dynamic_cast<Cylinder*>(pri);
	Cone* co_point = dynamic_cast<Cone*>(pri);

    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    if(s_point != NULL && s_point->get_shape() == P_SPHERE)
	{
		cout<<"I am sphere\n"<<"center : "<<s_point->center[0]<<" "<<s_point->center[1]<<" radius: "<<s_point->radius<<endl;
        //glPushMatrix();
        glTranslated(s_point->center[0],500-s_point->center[1]-15,0);
		glRotated(90,1,0,0);
        gluSphere(quadratic, s_point->radius, 100, 100);
        //glPopMatrix();
	}
    else if(cy_point != NULL&& cy_point->get_shape() ==P_CYLINDER)
	{
		 cout<<"I am cylinder\n"<<"center : "<<cy_point->bottom[0]
              <<" "<<cy_point->bottom[1]
              <<"radiu: "<<cy_point->radius<<" height: "<<cy_point->norm[0]<<" "<<cy_point->norm[1]<<endl;
        Vec3d center = cy_point->bottom;
        Vec3d normal = cy_point->norm;
		double radius = cy_point->radius;
		//normal[1] = (normal[1] < 0)?normal[1]:-normal[1];
		center[1] = 500 - center[1];
		normal[1] *= -1;
		double height = 2 * sqrt(normal[0]*normal[0] + normal[1]*normal[1]);
        //glPushMatrix();
		double angle = atan(normal[0]/ normal[1])*180/3.1415926;
		cout<<"angle "<<angle<<endl;
		glTranslated(center[0]+110, center[1], 0);
		glRotated(-angle,0,0,1);
		glRotated(90,1,0,0);
        gluCylinder(quadratic,radius,radius,height, 32,32);
        //glPopMatrix();
	}
    else if(co_point != NULL && co_point->get_shape() ==P_CONE)
	{
         cout<<"I am cone\n"<<"center : "<<co_point->bottom[0]
              <<" "<<co_point->bottom[1]
			  <<" radiu: "<<co_point->radius1<<" "<<co_point->radius2<<" height: "<<co_point->norm[0]<<" "<<co_point->norm[1]<<endl;
        Vec3d center = co_point->bottom;
        Vec3d normal = co_point->norm;
		//normal[1] = (normal[1] < 0)?normal[1]:-normal[1];
		center[1] = 500 - center[1];
		normal[1] *= -1;
		double height = 2 * sqrt(normal[0]*normal[0] + normal[1]*normal[1]);
        //glPushMatrix();
		double angle = atan(normal[0]/ normal[1])*180/3.1415926;
		glTranslated(center[0], center[1], 0);
		glRotated(-angle,0,0,1);
		glRotated(90,1,0,0);
		gluCylinder(quadratic,co_point->radius1,co_point->radius2,height, 32,32);
        //glPopMatrix();
	}
    gluDeleteQuadric(quadratic);
}
