#include<iostream>
#include<math.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
using namespace std;

void line_direct()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);
    glPointSize(5);
    glBegin(GL_POINTS);

    int x,y,x1=0,y1=0,x2=9,y2=9,dx=x2-x1,dy=y2-y1;
    double m=dy/dx;
    double b=y1-(m*x1);
    glVertex2f(x1,y1);
    x=x1,y=y1;
    if(m<=1)
    {
        while(x<x2)
            {
                x++;
                y=(m*x)+b;
                glVertex2f(x,y);
            }
    }
    else
    {
        while(y<y2)
            {
                y++;
                x=(1/m)*(y-b);
                glVertex2f(x,y);
            }
    }
    glVertex2f(x2,y2);
    glEnd();
    glFlush();
}

void line_dda()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);
    glPointSize(5);
    glBegin(GL_POINTS);

    int x,y,x1=0,y1=0,x2=9,y2=9,dx=x2-x1,dy=y2-y1;
    double m=dy/dx;
    glVertex2f(x1,y1);
    x=x1,y=y1;
    if(m<1)
    {
        while(x<x2)
            {
                x++;
                y=y+m;
                glVertex2f(x,y);
            }
    }
    else if(m>1)
    {
        while(y<y2)
            {
                y++;
                x=x+(1/m);
                glVertex2f(x,y);
            }
    }
    else
    {
        while(x<x2)
            {
                x++;
                y++;
                glVertex2f(x,y);
            }
    }
    glVertex2f(x2,y2);
    glEnd();
    glFlush();
}

void line_bresenham()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);
    glPointSize(5);
    glBegin(GL_POINTS);

    int x,y,x1=0,y1=0,x2=9,y2=9,dx=x2-x1,dy=y2-y1,dS=2*dy,dT=2*(dy-dx),d=2*dy-dx;
    glVertex2f(x1,y1);
    x=x1,y=y1;
    while(x<x2)
    {
        x++;
        if(d<0)
            d+=dS;
        else
        {
            d+=dT;
            y++;
        }
        glVertex2f(x,y);
    }
    glEnd();
    glFlush();
}

void circle_direct()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);
    glPointSize(3);

    glBegin(GL_POINTS);
    int r=8;
    int x=0,y=r;
    double k=r/(sqrt(2));
    int R=r*r;
    while(x<=k)
    {
        glVertex2f(x,y);
        glVertex2f(y,x);
        glVertex2f(-y,x);
        glVertex2f(-x,y);
        glVertex2f(-x,-y);
        glVertex2f(-y,-x);
        glVertex2f(y,-x);
        glVertex2f(x,-y);
        x++;
        y=sqrt(R-(x*x));
    }
    glEnd();

    glFlush();
}

void circle_trigonometric()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);
    glPointSize(3);

    glBegin(GL_POINTS);
    int r=8;
    int x=r,y=0;
    int theta=0;
    while(theta<=45)
    {
        glVertex2f(x,y);
        glVertex2f(y,x);
        glVertex2f(-y,x);
        glVertex2f(-x,y);
        glVertex2f(-x,-y);
        glVertex2f(-y,-x);
        glVertex2f(y,-x);
        glVertex2f(x,-y);
        theta++;
        x=r*cos(theta);
        y=r*sin(theta);
    }
    glEnd();

    glFlush();
}

void circle_bresenham()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);
    glPointSize(3);

    glBegin(GL_POINTS);
    int r=8;
    int x=0,y=r,d=3-2*r;
    while(x<=y)
    {
        glVertex2f(x,y);
        glVertex2f(y,x);
        glVertex2f(-y,x);
        glVertex2f(-x,y);
        glVertex2f(-x,-y);
        glVertex2f(-y,-x);
        glVertex2f(y,-x);
        glVertex2f(x,-y);
        if(d<0)
        {
            d=d+4*x+6;
        }
        else
        {
            d=d+4*(x-y)+10;
            y--;
        }
        x++;
    }
    glEnd();

    glFlush();
}

void circle_midpoint()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);
    glPointSize(3);

    glBegin(GL_POINTS);
    int r=8;
    int x=0,y=r,p=1-r;
    while(x<=y)
    {
        glVertex2f(x,y);
        glVertex2f(y,x);
        glVertex2f(-y,x);
        glVertex2f(-x,y);
        glVertex2f(-x,-y);
        glVertex2f(-y,-x);
        glVertex2f(y,-x);
        glVertex2f(x,-y);
        if(p<0)
        {
            p=p+2*x+3;
        }
        else
        {
            p=p+2*(x-y)+5;
            y--;
        }
        x++;
    }
    glEnd();

    glFlush();
}

void ellipse_direct()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);
    glPointSize(3);

    glBegin(GL_POINTS);

    double h=0,k=0;
    double a=8,b=5;
    double x=0,x2=a;
    double aa=a*a;
    double y;
    while(x<=x2)
    {
        y=b*sqrt(1-((x*x)/aa));
        glVertex2f(x+h,y+k);
        glVertex2f(-x+h,-y+k);
        glVertex2f(x+h,-y+k);
        glVertex2f(-x+h,y+k);
        x++;
    }

    glEnd();
    glFlush();
}

void ellipse_trigonometric()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);
    glPointSize(3);

    glBegin(GL_POINTS);

    double h=0,k=0;
    double a=8,b=5;
    double x,y,theta=0;
    while(theta<=45)
    {
        x=a*cos(theta)+h;
        y=b*sin(theta)+k;
        glVertex2f(x+h,y+k);
        glVertex2f(-x+h,-y+k);
        glVertex2f(x+h,-y+k);
        glVertex2f(-x+h,y+k);
        theta++;
    }

    glEnd();
    glFlush();
}

void ellipse_midpoint()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);
    glPointSize(3);

    glBegin(GL_POINTS);

    double h=0,k=0;
    double a=8,b=5;
    double x=0,y=b,aa=a*a,bb=b*b,aa2=2*aa,bb2=2*bb;
    double fx=0,fy=aa2*b;
    double p=bb-(aa*b)+(0.25*aa);

    while(fx<fy)
    {
        glVertex2f(x+h,y+k);
        glVertex2f(-x+h,-y+k);
        glVertex2f(x+h,-y+k);
        glVertex2f(-x+h,y+k);
        x++;
        fx=fx+bb2;
        if(p<0)
            p=p+fx+bb;
        else
        {
            y--;
            fy=fy-aa2;
            p=p+fx+bb-fy;
        }

    }

    glVertex2f(x+h,y+k);
    glVertex2f(-x+h,-y+k);
    glVertex2f(x+h,-y+k);
    glVertex2f(-x+h,y+k);

    p=(bb*(x+0.5)*(x+0.5))+(aa*(y-1)*(y-1))-(aa*bb);
    while(y>0)
    {
        y--;
        fy=fy-aa2;
        if(p>=0)
            p=p-fy+aa;
        else
        {
            x++;
            fx=fx+bb2;;
            p=p+fx-fy+aa;
        }
        glVertex2f(x+h,y+k);
        glVertex2f(-x+h,-y+k);
        glVertex2f(x+h,-y+k);
        glVertex2f(-x+h,y+k);
    }

    glEnd();
    glFlush();
}

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10.0,10.0,-10.0,10.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Computer Graphics Lab");
    init();
    glutDisplayFunc(circle_midpoint);
    glutMainLoop();
    return 0;
}
