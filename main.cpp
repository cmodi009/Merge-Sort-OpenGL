#include <GL/glut.h>
#include <iostream>

#define WIDTH  600
#define HEIGHT  600

using namespace std;

double rotationX = 20.0; // Variables that control application rotation
double rotationY = 20.0;

int last_press_x = 0;
int last_press_y = 0;

double pos_z[15]; // Vectors responsible for saving the positions of the bars on the 3 axes
double pos_x[15];
double pos_y[15];
int rotY[15];

float color1[15]; // Vectors responsible for the coloring of the bars - RGB
float color2[15];
float color3[15];

bool stop = false; // Variable responsible for controlling the stop in Animation
int velocity = 50;
int step = 1; // Variable that controls the steps within the animation
int eyeCamera = 40;

void ParametersLighting()
{
	GLfloat ambientlight[4]={0.8, 0.8, 0.8, 1.0};
	GLfloat Diffusedlight[4]={1.0, 0.0, 0.4, 1.0};
    GLfloat lightSpecific[4]={1, 1, 0.6, 1.0};
    GLfloat positionLight[4]={-1.0,1.0, 1.0, 1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientlight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecific );
    glLightfv(GL_LIGHT0, GL_POSITION, positionLight );
    glLightfv(GL_LIGHT0, GL_POSITION, Diffusedlight );

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientlight);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, positionLight);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightSpecific);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Diffusedlight);

}
void Draw_Bar(void){
    glBegin(GL_QUADS);

            glVertex3f( 0.2f, 0.2f,-0.2f);    // Top face
            glVertex3f(-0.2f, 0.2f,-0.2f);
            glVertex3f(-0.2f, 0.2f, 0.2f);
            glVertex3f( 0.2f, 0.2f, 0.2f);

            glVertex3f( 0.2f,-0.2f, 0.2f);    // Bottom face
            glVertex3f(-0.2f,-0.2f, 0.2f);
            glVertex3f(-0.2f,-0.2f,-0.2f);
            glVertex3f( 0.2f,-0.2f,-0.2f);

            glVertex3f( 0.2, 0.2, 0.2);    // Front face
            glVertex3f(-0.2, 0.2, 0.2);
            glVertex3f(-0.2,-0.2, 0.2);
            glVertex3f( 0.2,-0.2, 0.2);

            glVertex3f( 0.2f,-0.2f,-0.2f);    // Back face
            glVertex3f(-0.2f,-0.2f,-0.2f);
            glVertex3f(-0.2f, 0.2f,-0.2f);
            glVertex3f( 0.2f, 0.2f,-0.2f);

            glVertex3f(-0.2f, 0.2f, 0.2f);    // Left face
            glVertex3f(-0.2f, 0.2f,-0.2f);
            glVertex3f(-0.2f,-0.2f,-0.2f);
            glVertex3f(-0.2f,-0.2f, 0.2f);

            glVertex3f( 0.2f, 0.2f,-0.2f);    // Right face
            glVertex3f( 0.2f, 0.2f, 0.2f);
            glVertex3f( 0.2f,-0.2f, 0.2f);
            glVertex3f( 0.2f,-0.2f,-0.2f);
    glEnd();
}

void Draw_Plane(void){ // Drawing the plane below the bars and their colored lines that define their phases
 glBegin(GL_QUADS);
   glColor3f(0.0f,0.0f,0.2f);
        glVertex3f(30.0f, 0.0f, 30.0f);
        glVertex3f(-30.0f, 0.0f, 30.0f);
        glVertex3f(-30.0f,0.0f,-30.0f);
        glVertex3f( 30.0f,0.0f,-30.0f);
  glEnd();


	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(WIDTH/2, 0, 0);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(-WIDTH/2, 0, 0);
	glEnd();

	glColor3f(1, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 2);
		glVertex3i(WIDTH/2, 0, 2);
	glEnd();


	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 2);
		glVertex3i(-WIDTH/2, 0, 2);
	glEnd();

	glColor3f(1, 1.0, 0.0);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 4);
		glVertex3i(WIDTH/2, 0, 4);
	glEnd();


	glColor3f(1, 1, 0);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 4);
		glVertex3i(-WIDTH/2, 0, 4);
	glEnd();

	glColor3f(0, 1.0, 1.0);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 6);
		glVertex3i(WIDTH/2, 0, 6);
	glEnd();


	glColor3f(0, 1, 1);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 6);
		glVertex3i(-WIDTH/2, 0, 6);
	glEnd();

}
void Draw(void) // Function that draws the components of the application: bars, planes, lines and points
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(0.0, 0.0, eyeCamera,
    		  0.0, 0.0, -30.0,
    		  0.0, 1.0, 0.0);

    ParametersLighting();

	glRotatef(rotationY, 1.0, 0.0, 0.0);
	glRotatef(rotationX, 0.0, 1.0, 0.0);

    Draw_Plane();
    glPushMatrix();
        glScalef(1.0, 6.0, 1.0); // Each bar will have its size defined by its scale in relation to the standard bar
        glTranslatef(pos_x[0], 0.2, pos_z[0]); // Here the location that belongs to each bar on the x, y and z axes is defined
        glRotatef(rotY[0],0, 10,0); // bar rotation angle in the change animation
        glColor3d(color1[0], color2[0], color3[0]); // bar color
        Draw_Bar(); // Bar 0
    glPopMatrix();

    glPushMatrix();
        glScalef(1.0, 4.0, 1.0);
        glTranslatef(pos_x[1], 0.2, pos_z[1]);
        glRotatef(rotY[1],0, 10,0);
        glColor3d(color1[1], color2[1], color3[1]);
        Draw_Bar(); // Bar 1
    glPopMatrix();

    glPushMatrix();
        glScalef(1.0, 1.0, 1.0);
        glTranslatef(pos_x[2], 0.2, pos_z[2]);
        glRotatef(rotY[2],0, 10,0);
        glColor3d(color1[2], color2[2], color3[2]);
        Draw_Bar(); // Bar 2
    glPopMatrix();

    glPushMatrix();
        glScalef(1.0, 7.0, 1.0);
        glTranslatef( pos_x[3], 0.2, pos_z[3]);
        glRotatef(rotY[3],0, 10,0);
        glColor3d(color1[3], color2[3], color3[3]);
        Draw_Bar(); // Bar 3
    glPopMatrix();

    glPushMatrix();
        glScalef(1.0, 3.0, 1.0);
        glTranslatef(pos_x[4], 0.2, pos_z[4]);
        glRotatef(rotY[4],0, 10,0);
        glColor3d(color1[4], color2[4], color3[4]);
        Draw_Bar(); // Bar 4
    glPopMatrix();

    glPushMatrix();
        glScalef(1.0, 10.0, 1.0);
        glTranslatef(pos_x[5], 0.2, pos_z[5]);
        glRotatef(rotY[5],0, 10,0);
        glColor3d(color1[5], color2[5], color3[5]);
        Draw_Bar(); // Bar 5
    glPopMatrix();

    glPushMatrix();
        glScalef(1.0, 5.0, 1.0);
        glTranslatef(pos_x[6], 0.2, pos_z[6]);
        glRotatef(rotY[6],0, 10,0);
        glColor3d(color1[6], color2[6], color3[6]);
        Draw_Bar(); // Bar 6
    glPopMatrix();

    glPushMatrix();
        glScalef(1.0, 10.0, 1.0);
        glTranslatef(pos_x[7], 0.2, pos_z[7]);
        glRotatef(rotY[7],0, 10,0);
        glColor3d(color1[7], color2[7], color3[7]);
        Draw_Bar(); // Bar 7
    glPopMatrix();

	glPushMatrix();
        glScaled(1, 4.0, 1.0);
        glTranslatef(pos_x[8], 0.2, pos_z[8]);
        glRotatef(rotY[8],0, 10,0);
        glColor3d(color1[8], color2[8], color3[8]);
        Draw_Bar(); // Bar 8
	glPopMatrix();

	glPushMatrix();
        glScalef(1.0, 10.0, 1.0);
        glTranslatef(pos_x[9], 0.2,pos_z[9]);
        glRotatef(rotY[9],0, 10,0);
        glColor3d(color1[9], color2[9], color3[9]);
        Draw_Bar(); // Bar 9
    glPopMatrix();

    glPushMatrix();
       glScalef(1.0, 5.0, 1.0);
       glTranslatef(pos_x[10], 0.2, pos_z[10]);
       glRotatef(rotY[10],0, 10,0);
       glColor3d(color1[10], color2[10], color3[10]);
       Draw_Bar(); // Bar 10
    glPopMatrix();

    glPushMatrix();
        glScalef(1.0, 8.0, 1.0);
        glTranslatef(pos_x[11], 0.2, pos_z[11]);
        glRotatef(rotY[11],0, 10,0);
        glColor3d(color1[11], color2[11], color3[11]);
        Draw_Bar(); // Bar 11
    glPopMatrix();

    glPushMatrix();
        glScalef(1.0, 7.0, 1.0);
        glTranslatef(pos_x[12], 0.2, pos_z[12]);
        glRotatef(rotY[12],0, 10,0);
        glColor3d(color1[12], color2[12], color3[12]);
        Draw_Bar(); // Bar 12
    glPopMatrix();

    glPushMatrix();
        glScalef(1.0, 9.0, 1.0);
        glTranslatef(pos_x[13], 0.2, pos_z[13]);
        glRotatef(rotY[13],0, 10,0);
        glColor3d(color1[13], color2[13], color3[13]);
        Draw_Bar(); // Bar 13
    glPopMatrix();

    glPushMatrix();
        glScalef(1.0, 12.0, 1.0);
        glTranslatef(pos_x[14], 0.2, pos_z[14]);
        glRotatef(rotY[14],0, 10,0);
        glColor3d(color1[14], color2[14], color3[14]);
        Draw_Bar(); // Bar 14
    glPopMatrix();

    glPushMatrix();
        glScalef(1.0, 13.0, 1.0);
        glTranslatef(pos_x[15], 0.2, pos_z[15]);
        glRotatef(rotY[15],0, 10,0);
        glColor3d(color1[15], color2[15], color3[15]);
        Draw_Bar(); // Bar 15
    glPopMatrix();

	glFlush();
}
void Anim(int value) //In this function we have the variable "step" defining each stage of the animation
{

    if( pos_z[0]<0 && step == 1) // Bringing all bars from position z-4 to position z0
    {
        for(int i = 0; i<16; i++)
        {
            pos_z[i] += 0.05;
        }
        if(pos_z[15] >= 0)
        {
            step = 2;
        }
    }
    if(pos_z[0]<2 && step == 2) // This if is responsible both for bringing the first 8 bars forward and for coloring them red
    {
        for(int i = 0; i<8; i++)
        {
            pos_z[i] +=0.05;
            color1[i] = 1;
            color2[i] = 0;
            color3[i] = 0;
        }
        if(pos_z[0] >= 2)
        {
            step = 3;
        }
    }
    if(pos_z[0]<4 && step == 3)
    {
        for(int i = 0; i<4; i++)
        {
            pos_z[i] +=0.05;
            color1[i] = 1;
            color2[i] = 1;
            color3[i] = 0;
        }
        if(pos_z[0] >= 4)
        {
            step = 4;
        }
    }
    if(pos_z[0]<6 && step == 4)
    {
        for(int i = 0; i<2; i++)
        {
            pos_z[i] +=0.05;
            color1[i] = 0;
            color2[i] = 1;
            color3[i] = 1;
        }

        if(pos_z[0] >= 6)
        {
            step = 5;
        }
    }

    if(pos_x[0]<-7.0 && step == 5)
    {
        pos_x[0] += 0.02;
        pos_x[1] -= 0.02;

        if(rotY[0]<10000)
        {
            rotY[0] += 20;
            rotY[1] += 20;
        }
        for(int i = 0; i<2; i++)
        {
            color1[i] = 1;
            color2[i] = 1;
            color3[i] = 1;
        }
        if(pos_x[0]>=-7)
        {
            step = 6;
            rotY[0] = 0;
            rotY[1] = 0;
            for(int i = 0; i<2; i++)
            {
                color1[i] = 0;
                color2[i] = 1;
                color3[i] = 1;
            }
        }
    }
    if(pos_z[0]>4 && step == 6)
    {
        pos_z[0] -= 0.05;
        pos_z[1] -= 0.05;
        for(int i = 0; i<2; i++)
        {
            color1[i] = 1;
            color2[i] = 1;
            color3[i] = 0;
        }
        if(pos_z[0]<=4)
        {
            step = 7;
        }
    }
    if(pos_z[2]<6 && step == 7)
    {
        for(int i = 2; i<4; i++)
        {
            pos_z[i] +=0.05;
            color1[i] = 0;
            color2[i] = 1;
            color3[i] = 1;
        }
        if(pos_z[2] >= 6)
        {
            step = 8;
        }
    }
    if(pos_z[2]>4 && step == 8)
    {
        pos_z[2] -= 0.05;
        pos_z[3] -= 0.05;
        for(int i = 2; i<4; i++)
        {
            color1[i] = 1;
            color2[i] = 1;
            color3[i] = 0;
        }
        if(pos_z[2]<=4)
        {
            step = 9;
        }
    }
    if(pos_x[1]<-6.0  && step == 9)
    {
        pos_x[1] += 0.02;
        pos_x[2] -= 0.02;
        rotY[1] += 15;
        rotY[2] += 15;
        for(int i = 1; i<3; i++)
        {
            color1[i] = 1;
            color2[i] = 1;
            color3[i] = 1;
        }
        if(pos_x[1]>=-6.0)
        {
            step = 10;
            rotY[1] = 0;
            rotY[2] = 0;
            for(int i = 1; i<3; i++)
            {
                color1[i] = 1;
                color2[i] = 1;
                color3[i] = 0;
            }
        }
    }
    if(pos_x[0]<-6.0  && step == 10)
    {
        pos_x[0] += 0.02;
        pos_x[1] -= 0.02;
        rotY[0] += 15;
        rotY[1] += 15;

        for(int i = 0; i<2; i++)
        {
            color1[i] = 1;
            color2[i] = 1;
            color3[i] = 1;
        }
        if(pos_x[0]>=-6.0)
        {
            step = 11;
            rotY[0] = 0;
            rotY[1] = 0;
            for(int i = 0; i<2; i++)
            {
                color1[i] = 1;
                color2[i] = 1;
                color3[i] = 0;
            }

        }
    }
    if(pos_z[0]>2.0 && step == 11)
    {
        for(int i = 0; i<4; i++)
        {
            pos_z[i] -=0.05;
            color1[i] = 1;
            color2[i] = 0;
            color3[i] = 0;
        }
        if(pos_z[0]<= 2)
        {
            step = 12;
        }
    }
    if(pos_z[4]<4.0 && step == 12)
    {
        for(int i = 4; i<8; i++)
        {
            pos_z[i] +=0.05;
            color1[i] = 1;
            color2[i] = 1;
            color3[i] = 0;
        }
        if(pos_z[4]>= 4)
        {
            step = 13;
        }
    }

    if(pos_z[4]<6.0 && step == 13)
    {
        pos_z[4] +=0.05;
        pos_z[5] +=0.05;
        for(int i = 4; i<6; i++)
        {
            color1[i] = 0;
            color2[i] = 1;
            color3[i] = 1;
        }
        if(pos_z[4]>= 6)
        {
            step = 14;
        }
    }

    if(pos_z[4]>4.0 && step == 14)
    {
        pos_z[4] -=0.05;
        pos_z[5] -=0.05;
        for(int i = 4; i<6; i++)
        {
            color1[i] = 1;
            color2[i] = 1;
            color3[i] = 0;
        }

        if(pos_z[4]<=4)
        {
            step = 15;
        }

    }
    if(pos_z[6]<6.0 && step == 15)
    {
        pos_z[6] +=0.05;
        pos_z[7] +=0.05;
        for(int i = 6; i<8; i++)
        {
            color1[i] = 0;
            color2[i] = 1;
            color3[i] = 1;
        }

        if(pos_z[6]>=6)
        {
            step = 16;
        }
    }

    if(pos_z[6]>4.0 && step == 16)
    {
        pos_z[6] -=0.05;
        pos_z[7] -=0.05;
        for(int i = 6; i<8; i++)
        {
            color1[i] = 1;
            color2[i] = 1;
            color3[i] = 0;
        }

        if(pos_z[6]<=4)
        {
            step = 17;
        }
    }
    if(pos_x[5]<-2.0  && step == 17)
    {
        pos_x[5] += 0.02;
        pos_x[6] -= 0.02;
        rotY[5] += 15;
        rotY[6] += 15;

        for(int i = 5; i<7; i++)
        {
            color1[i] = 1;
            color2[i] = 1;
            color3[i] = 1;
        }
        if(pos_x[5]>=-2.0)
        {
            step = 18;
            rotY[5] = 0;
            rotY[6] = 0;
            for(int i = 5; i<7; i++)
            {
                color1[i] = 1;
                color2[i] = 1;
                color3[i] = 0;
            }
        }
    }
    if(pos_z[4]>2.0 && step == 18)
    {
        for(int i = 4; i<8; i++)
        {
            pos_z[i] -=0.05;
            color1[i] = 1;
            color2[i] = 0;
            color3[i] = 0;
        }
        if(pos_z[4]<= 2)
        {
            step = 19;
        }
    }

    if(pos_x[1]<-4.0  && step == 19)
    {
        pos_x[1] += 0.02;
        pos_x[4] -= 0.02;
        rotY[1] += 15;
        rotY[4] += 15;

        for(int i = 1; i<5; i++)
        {
            if(i==1 || i==4)
            {
                color1[i] = 1;
                color2[i] = 1;
                color3[i] = 1;
            }
        }
        if(pos_x[1]>=-4.0)
        {
            step = 20;
            rotY[1] = 0;
            rotY[4] = 0;
            for(int i = 1; i<5; i++)
            {
                if(i==1 || i==4)
                {
                    color1[i] = 1;
                    color2[i] = 0;
                    color3[i] = 0;
                }
            }
        }
    }
    if(pos_x[0]<-4.0  && step == 20)
    {
        pos_x[0] += 0.02;
        pos_x[1] -= 0.02;
        rotY[0] += 15;
        rotY[1] += 15;

        for(int i = 0; i<2; i++)
        {
            color1[i] = 1;
            color2[i] = 1;
            color3[i] = 1;
        }
        if(pos_x[0]>=-4.0)
        {
            step = 21;
            rotY[0] = 0;
            rotY[1] = 0;
            for(int i = 0; i<2; i++)
            {
                color1[i] = 1;
                color2[i] = 0;
                color3[i] = 0;
            }
        }
    }
    if(pos_x[3]<-3.0  && step == 21)
    {
        pos_x[3] += 0.02;
        pos_x[6] -= 0.02;
        rotY[3] += 15;
        rotY[6] += 15;

        for(int i = 3; i<7; i++)
        {
            if(i==3 || i==6)
            {
                color1[i] = 1;
                color2[i] = 1;
                color3[i] = 1;
            }
        }
        if(pos_x[3]>=-3.0)
        {
            step = 22;
            rotY[3] = 0;
            rotY[6] = 0;
            for(int i = 3; i<7; i++)
            {
                if(i==3 || i==6)
                {
                    color1[i] = 1;
                    color2[i] = 0;
                    color3[i] = 0;
                }
            }
        }
    }
    if(pos_z[0]>0  && step == 22)
    {
        for(int i = 0; i<8; i++)
        {
            pos_z[i] -=0.05;
            color1[i] = 0;
            color2[i] = 1;
            color3[i] = 0;
        }
        if(pos_z[0]<=0)
        {
            step = 23;
        }
    }
    if(pos_z[8]<2  && step == 23)
    {
        for(int i = 8; i<16; i++)
        {
            pos_z[i] +=0.05;
            color1[i] = 1;
            color2[i] = 0;
            color3[i] = 0;
        }
        if(pos_z[8]>=2)
        {
            step = 24;
        }
    }

    if(pos_z[8]<4  && step == 24)
    {
        for(int i = 8; i<12; i++)
        {
            pos_z[i] +=0.05;
            color1[i] = 1;
            color2[i] = 1;
            color3[i] = 0;
        }
        if(pos_z[8]>=4)
        {
            step = 25;
        }
    }
    if(pos_z[8]<6  && step == 25)
    {
        for(int i = 8; i<10; i++)
        {
            pos_z[i] +=0.05;
            color1[i] = 0;
            color2[i] = 1;
            color3[i] = 1;
        }
        if(pos_z[8]>=6)
        {
            step = 26;
        }
    }
    if(pos_z[8]>4  && step == 26)
    {
        for(int i = 8; i<10; i++)
        {
            pos_z[i] -=0.05;
            color1[i] = 1;
            color2[i] = 1;
            color3[i] = 0;
        }
        if(pos_z[8]<=4)
        {
            step = 27;
        }
    }
    if(pos_z[10]<6  && step == 27)
    {
        for(int i = 10; i<12; i++)
        {
            pos_z[i] +=0.05;
            color1[i] = 0;
            color2[i] = 1;
            color3[i] = 1;
        }
        if(pos_z[10]>=6)
        {
            step = 28;
        }
    }
    if(pos_z[10]>4  && step == 28)
    {
        for(int i = 10; i<12; i++)
        {
            pos_z[i] -=0.05;
            color1[i] = 1;
            color2[i] = 1;
            color3[i] = 0;
        }
        if(pos_z[10]<=4)
        {
            step = 29;
        }
    }
    if(pos_x[9]<2  && step == 29)
    {
        pos_x[9] += 0.02;
        pos_x[10] -= 0.02;
        rotY[9] += 15;
        rotY[10] += 15;
        for(int i = 9; i<11; i++)
        {
            color1[i] = 1;
            color2[i] = 1;
            color3[i] = 1;
        }
        if(pos_x[9]>=2)
        {
            step = 30;
            rotY[9] = 0;
            rotY[10] = 0;
            for(int i = 9; i<11; i++)
            {
                color1[i] = 1;
                color2[i] = 1;
                color3[i] = 0;
            }
        }
    }
    if(pos_x[9]<3  && step == 30)
    {
        pos_x[9] += 0.02;
        pos_x[11] -= 0.02;
        rotY[9] += 15;
        rotY[11] += 15;
        for(int i = 9; i<12; i++)
        {
            if(i==9 || i==11)
            {
                color1[i] = 1;
                color2[i] = 1;
                color3[i] = 1;
            }
        }
        if(pos_x[9]>=3)
        {
            step = 31;
            rotY[9] = 0;
            rotY[10] = 0;
            for(int i = 9; i<12; i++)
            {
                if(i==9 || i==11)
                {
                    color1[i] = 1;
                    color2[i] = 1;
                    color3[i] = 0;
                }
            }
        }
    }
    if(pos_z[8]>2  && step == 31)
    {
        for(int i = 8; i<12; i++)
        {
            pos_z[i] -=0.05;
            color1[i] = 1;
            color2[i] = 0;
            color3[i] = 0;
        }
        if(pos_z[8]<=2)
        {
            step = 32;
        }
    }
    if(pos_z[12]<4  && step == 32)
    {
        for(int i = 12; i<16; i++)
        {
            pos_z[i] +=0.05;
            color1[i] = 1;
            color2[i] = 1;
            color3[i] = 0;
        }
        if(pos_z[12]>=4)
        {
            step = 33;
        }
    }
    if(pos_z[12]<6  && step == 33)
    {
        for(int i = 12; i<14; i++)
        {
            pos_z[i] +=0.05;
            color1[i] = 0;
            color2[i] = 1;
            color3[i] = 1;
        }
        if(pos_z[12]>=6)
        {
            step = 34;
        }
    }
    if(pos_z[12]>4  && step == 34)
    {
        for(int i = 12; i<14; i++)
        {
            pos_z[i] -=0.05;
            color1[i] = 1;
            color2[i] = 1;
            color3[i] = 0;
        }
        if(pos_z[12]<=4)
        {
            step = 35;
        }
    }
    if(pos_z[14]<6  && step == 35)
    {
        for(int i = 14; i<16; i++)
        {
            pos_z[i] +=0.05;
            color1[i] = 0;
            color2[i] = 1;
            color3[i] = 1;
        }
        if(pos_z[14]>=6)
        {
            step = 36;
        }
    }
    if(pos_z[14]>4  && step == 36)
    {
        for(int i = 14; i<16; i++)
        {
            pos_z[i] -=0.05;
            color1[i] = 1;
            color2[i] = 1;
            color3[i] = 0;
        }
        if(pos_z[14]<=4)
        {
            step = 37;
        }
    }
    if(pos_z[12]>2  && step == 37)
    {
        for(int i = 12; i<16; i++)
        {
            pos_z[i] -=0.05;
            color1[i] = 1;
            color2[i] = 0;
            color3[i] = 0;
        }
        if(pos_z[12]<=2)
        {
            step = 38;
        }
    }
    if(pos_x[11]<4  && step == 38)
    {
        pos_x[11] += 0.02;
        pos_x[12] -= 0.02;
        rotY[11] += 15;
        rotY[12] += 15;
        for(int i = 11; i<13; i++)
        {
            color1[i] = 1;
            color2[i] = 1;
            color3[i] = 1;
        }
        if(pos_x[11]>=4)
        {
            step = 39;
            rotY[11] = 0;
            rotY[12] = 0;
            for(int i = 11; i<13; i++)
            {
                color1[i] = 1;
                color2[i] = 0;
                color3[i] = 0;
            }
        }
    }
    if(pos_x[9]<4  && step == 39)
    {
        pos_x[9] += 0.02;
        pos_x[11] -= 0.02;
        rotY[9] += 15;
        rotY[11] += 15;
        for(int i = 9; i<12; i++)
        {
            if(i==9 || i==11)
            {
                color1[i] = 1;
                color2[i] = 1;
                color3[i] = 1;
            }
        }
        if(pos_x[9]>=4)
        {
            step = 40;
            rotY[9] = 0;
            rotY[11] = 0;
            for(int i = 9; i<12; i++)
            {
                if(i==9 || i==11)
                {
                    color1[i] = 1;
                    color2[i] = 0;
                    color3[i] = 0;
                }
            }
        }
    }
    if(pos_x[9]<5  && step == 40)
    {
        pos_x[9] += 0.02;
        pos_x[13] -= 0.02;
        rotY[9] += 15;
        rotY[13] += 15;
        for(int i = 9; i<14; i++)
        {
            if(i==9 || i==13)
            {
                color1[i] = 1;
                color2[i] = 1;
                color3[i] = 1;
            }
        }
        if(pos_x[9]>=5)
        {
            step = 41;
            rotY[9] = 0;
            rotY[13] = 0;
            for(int i = 9; i<14; i++)
            {
                if(i==9 || i==13)
                {
                    color1[i] = 1;
                    color2[i] = 0;
                    color3[i] = 0;
                }
            }
        }
    }
    if(pos_z[8]>0  && step == 41)
    {
        for(int i = 8; i<16; i++)
        {
            pos_z[i] -=0.05;
            color1[i] = 0;
            color2[i] = 1;
            color3[i] = 0;
        }
        if(pos_z[8]<=0)
        {
            step = 42;
        }
    }
    if(pos_x[6]<0  && step == 42)
    {
        pos_x[6] += 0.02;
        pos_x[8] -= 0.02;
        rotY[6] += 15;
        rotY[8] += 15;
        for(int i = 6; i<9; i++)
        {
            if(i==6 || i==8)
            {
                color1[i] = 1;
                color2[i] = 1;
                color3[i] = 1;
            }
        }
        if(pos_x[6]>=0)
        {
            step = 43;
            rotY[6] = 0;
            rotY[8] = 0;
            for(int i = 6; i<9; i++)
            {
                if(i==6 || i==8)
                {
                    color1[i] = 0;
                    color2[i] = 1;
                    color3[i] = 0;
                }
            }
        }
    }
    if(pos_x[0]<0  && step == 43)
    {
        pos_x[0] += 0.02;
        pos_x[6] -= 0.02;
        rotY[0] += 15;
        rotY[6] += 15;
        for(int i = 0; i<7; i++)
        {
            if(i==0 || i==6)
            {
                color1[i] = 1;
                color2[i] = 1;
                color3[i] = 1;
            }
        }
        if(pos_x[0]>=0)
        {
            step = 44;
            rotY[0] = 0;
            rotY[6] = 0;
            for(int i = 0; i<7; i++)
            {
                if(i==0 || i==6)
                {
                    color1[i] = 0;
                    color2[i] = 1;
                    color3[i] = 0;
                }
            }
        }
    }
    if(pos_x[3]<1  && step == 44)
    {
        pos_x[3] += 0.02;
        pos_x[10] -= 0.02;
        rotY[3] += 15;
        rotY[10] += 15;
        for(int i = 3; i<11; i++)
        {
            if(i==3 || i==10)
            {
                color1[i] = 1;
                color2[i] = 1;
                color3[i] = 1;
            }
        }
        if(pos_x[3]>=1)
        {
            step = 45;
            rotY[3] = 0;
            rotY[10] = 0;
            for(int i = 3; i<11; i++)
            {
                if(i==3 || i==10)
                {
                    color1[i] = 0;
                    color2[i] = 1;
                    color3[i] = 0;
                }
            }
        }
    }
    if(pos_x[5]<0  && step == 45)
    {
        pos_x[5] += 0.02;
        pos_x[0] -= 0.02;
        rotY[5] += 15;
        rotY[0] += 15;
        for(int i = 0; i<6; i++)
        {
            if(i==0 || i==5)
            {
                color1[i] = 1;
                color2[i] = 1;
                color3[i] = 1;
            }
        }
        if(pos_x[5]>=0)
        {
            step = 46;
            rotY[5] = 0;
            rotY[0] = 0;
            for(int i = 0; i<6; i++)
            {
                if(i==0 || i==5)
                {
                    color1[i] = 0;
                    color2[i] = 1;
                    color3[i] = 0;
                }
            }
        }
    }
    if(pos_x[7]<1  && step == 46)
    {
        pos_x[7] += 0.02;
        pos_x[3] -= 0.02;
        rotY[7] += 15;
        rotY[3] += 15;
        for(int i = 3; i<8; i++)
        {
            if(i==3 || i==7)
            {
                color1[i] = 1;
                color2[i] = 1;
                color3[i] = 1;
            }
        }
        if(pos_x[7]>=1)
        {
            step = 47;
            rotY[7] = 0;
            rotY[3] = 0;
            for(int i = 3; i<8; i++)
            {
                if(i==3 || i==7)
                {
                    color1[i] = 0;
                    color2[i] = 1;
                    color3[i] = 0;
                }
            }
        }
    }
    if(pos_x[5]<2  && step == 47)
    {
        pos_x[5] += 0.02;
        pos_x[12] -= 0.02;
        rotY[5] += 15;
        rotY[12] += 15;
        for(int i = 5; i<13; i++)
        {
            if(i==5 || i==12)
            {
                color1[i] = 1;
                color2[i] = 1;
                color3[i] = 1;
            }
        }
        if(pos_x[5]>=2)
        {
            step = 48;
            rotY[5] = 0;
            rotY[12] = 0;
            for(int i = 5; i<13; i++)
            {
                if(i==5 || i==12)
                {
                    color1[i] = 0;
                    color2[i] = 1;
                    color3[i] = 0;
                }
            }
        }
    }
    if(pos_x[7]<3  && step == 48)
    {
        pos_x[7] += 0.02;
        pos_x[11] -= 0.02;
        rotY[7] += 15;
        rotY[11] += 15;
        for(int i = 7; i<12; i++)
        {
            if(i==7 || i==11)
            {
                color1[i] = 1;
                color2[i] = 1;
                color3[i] = 1;
            }
        }
        if(pos_x[7]>=3)
        {
            step = 49;
            rotY[7] = 0;
            rotY[11] = 0;
            for(int i = 7; i<12; i++)
            {
                if(i==7 || i==11)
                {
                    color1[i] = 0;
                    color2[i] = 1;
                    color3[i] = 0;
                }
            }
        }
    }
    if(pos_x[5]<4  && step == 49)
    {
        pos_x[5] += 0.02;
        pos_x[13] -= 0.02;
        rotY[5] += 15;
        rotY[13] += 15;
        for(int i = 5; i<14; i++)
        {
            if(i==5 || i==13)
            {
                color1[i] = 1;
                color2[i] = 1;
                color3[i] = 1;
            }
        }
        if(pos_x[5]>=4)
        {
            for(int i = 5; i<14; i++)
            {
                if(i==5 || i==13)
                {
                    color1[i] = 0;
                    color2[i] = 1;
                    color3[i] = 0;
                }
                step=50;
            }
        }
    }

    glutPostRedisplay();
    if(stop == false)
    {
        glutTimerFunc(velocity, Anim, 1);
    }



}

static void key(unsigned char key, int x, int y) // Function responsible for the interaction of the keyboard with the application
{
    switch (key)
    {
        case 'e':
            exit(0);
            break;
        case '+': // increasing velocity
            if(velocity>10){
                velocity -= 10;
            }else{
                velocity--;
            }
            break;
        case '-': // decreasing velocity
            if(velocity>10){
                velocity += 10;
            }else{
                velocity++;
            }
            break;
        case 'a': // increasing eye distance
            eyeCamera++;
            break;
        case 'd': // decreasing eye distance
            eyeCamera--;
            break;
        glutPostRedisplay();
    }
}
void Mouse_Motion(int x, int y)
{
	rotationX += (double)(x - last_press_x);
	rotationY += (double)(y - last_press_y);
	last_press_x = x;
	last_press_y = y;
	glutPostRedisplay();
}

void Mouse_Press(int button, int state, int x, int y)
{
	if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
	{
		last_press_x = x;
		last_press_y = y;
	}
}

void Window(int option)
{
	switch(option){
		case 0:
		    stop = false;
            glutTimerFunc(velocity, Anim, 1);   /* Resume */
		break;

		case 1:
            stop = true;                    /* Pause */
		break;
		case 2:
		    velocity = 0;                          /* Advance to the end */
        break;
        case 3:                             /* Close Application */
            exit(0);
        break;
	}
	glutPostRedisplay();
}

void Menu()
{
	glutCreateMenu(Window);
	glutAddMenuEntry("Resume", 0);
	glutAddMenuEntry("Pause", 1);
	glutAddMenuEntry("Finish", 2);
	glutAddMenuEntry("Exit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Init(void)
{
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0f, ((GLfloat)WIDTH/(GLfloat)HEIGHT), 1, 50.0f);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glColorMaterial ( GL_FRONT_AND_BACK,GL_AMBIENT) ;
    glEnable(GL_COLOR_MATERIAL);

}

int main(int argc, char **argv)
{
    int j = -8;
    for(int i = 0; i<16; i++){ // Initializing vectors and variables
        pos_x[i] = j;
        pos_z[i] = -4;
        color1[i] = 0;
        color2[i] = 1;
        color3[i] = 0;
        rotY[i] = 0;
        j++;
    }
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (WIDTH, HEIGHT);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("MergeSort");
	glutDisplayFunc(Draw);
	glutMouseFunc(Mouse_Press);
	glutMotionFunc(Mouse_Motion);
    glutKeyboardFunc(key);
	Init();
	Menu();
	glutTimerFunc(1, Anim, 1000);
	glutMainLoop();
}
