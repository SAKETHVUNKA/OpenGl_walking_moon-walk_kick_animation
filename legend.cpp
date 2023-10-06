#include <GL/glut.h>
#include <GL/GL.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <thread> // for std::this_thread::sleep_for
#include <chrono> // for std::chrono::seconds
using namespace std;



#define PI 3.14159265358979323846
float lr1=1,lg1=0,lb1=0,lr2=0,lg2=1,lb2=0,lr3=0,lg3=0,lb3=1;

std::ifstream fin;
std::string line;

float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;
bool mouseDown = false;
bool kick = false;
bool moon= false;

double rja = 0;
double rka = 0;
double lja = 0;
double lka = 0;

double hrja = 0;
double hrka = 0;
double hlja = 0;
double hlka = 0;

float move1 = 0;

char direction = 'o';
char camerad = 'd';
float h = 9;

int moving = 0;
int loop_number = 0;

double xpos = 0;
double ypos = 0;

double valZoom = 10.0;
int up = 1;

double camX = 50, camY = 5, camZ = 80.0;

int frame = 0;

float tx = 0;
float ty = 0;
float axrot = 0;

string filename;

void fileOpen()
{
    fin.open(filename);
    if (!fin.is_open())
    {
        std::cerr << "Error: Could not open the file." << endl;
    }
}
void fileClose()
{
    fin.close();
}

float calHeight(int JA, int KA)
{
    float H = abs(cos(JA)) * 4.5 + abs(cos(KA + JA) * 4.5);
    return H;
}

float ActualHeight()
{
    float H1 = calHeight(rja, rka);
    float H2 = calHeight(lja, lka);
    return (H1 > H2) ? H1 : H2;
}

void sphereMouseEvent(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseDown = true;
    }
    else
        mouseDown = false;

    if (mouseDown)
    {
        xdiff = (yrot + x);
        ydiff = -y + xrot;
    }
}

void sphereMouseMotion(int x, int y)
{
    if (mouseDown)
    {
        yrot = -(x + xdiff);
        xrot = (y + ydiff);
        if (xrot > 89)
            xrot = 89.0f;
        if (xrot < -89)
            xrot = -89.0f;

        camX = valZoom * (cos(xrot * PI / 180) * sin(yrot * PI / 180));
        camY = valZoom * (sin(xrot * PI / 180));
        camZ = valZoom * (cos(xrot * PI / 180) * cos(yrot * PI / 180));
    }
    glutPostRedisplay();
}




void keyBoard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'c':camerad='c';
        break;
    
    case 'd':camerad = 'd';
        break;

    case 'k':
        if (moving == 0)
        {
            filename="kick.csv";
            kick = true;
            moon = false;
            fileOpen();
            loop_number = 0;
            direction = 'k';
        }
        break;

    case 'w':
        if (moving == 0)
        {
            filename="walking_efficient.csv";
            kick = false;
            moon = false;
            fileOpen();
            loop_number = 0;
            direction = 'w';
        }
        break;

    case 'm':
        
        if (moving == 0)
        {
            PlaySound(TEXT("Dangerous.wav"), NULL, SND_ASYNC);
            std::this_thread::sleep_for(std::chrono::seconds(2));
            filename="moonwalk.csv";
            kick = false;
            moon = true;
            fileOpen();
            loop_number = 0;
            direction = 'm';
        }
       
        break;

    default:
        break;
    }
}

void arrowKey(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        valZoom = valZoom + 0.1;
        break;
    case GLUT_KEY_DOWN:
        valZoom = valZoom - 0.1;
        break;
    case GLUT_KEY_RIGHT:
        valZoom = valZoom + 0.1;
    case GLUT_KEY_LEFT:
        valZoom = valZoom - 0.1;
    default:
        break;
    }
    camX = valZoom * (cos(xrot * PI / 180) * sin(yrot * PI / 180));
    camY = valZoom * (sin(xrot * PI / 180));
    camZ = valZoom * (cos(xrot * PI / 180) * cos(yrot * PI / 180));
    glutPostRedisplay();
}

void setMaterial(GLfloat ambientR, GLfloat ambientG, GLfloat ambientB,
                 GLfloat diffuseR, GLfloat diffuseG, GLfloat diffuseB,
                 GLfloat specularR, GLfloat specularG, GLfloat specularB,
                 GLfloat shininess)
{

    GLfloat ambient[] = {ambientR, ambientG, ambientB};
    GLfloat diffuse[] = {diffuseR, diffuseG, diffuseB};
    GLfloat specular[] = {specularR, specularG, specularB};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void initLight()
{
    /* set up lights */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_LIGHTING);

    GLfloat lightpos[] = {10.0, 10.0, 100.0};
    GLfloat lightcolor[] = {lr1, lg1, lb1};
    GLfloat ambcolor[] = {0.2, 0.2, 0.2};
    GLfloat specular[] = {1.0, 1.0, 1.0};

    glEnable(GL_LIGHT0);
    glDisable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambcolor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightcolor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    GLfloat lightpos1[] = { -10.0, 10.0, 100.0 };
    GLfloat lightcolor1[] = { lr2, lg2, lb2};
    GLfloat ambcolor1[] = { 0.2, 0.2, 0.2 };
    GLfloat specular1[] = { 1.0, 1.0, 1.0 };

    glEnable(GL_LIGHT1);
    glDisable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambcolor1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightcolor1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);

    GLfloat lightpos2[] = { 0.0, 10.0, 110.0 };
    GLfloat lightcolor2[] = { lr3, lg3, lb3};
    GLfloat ambcolor2[] = { 0.2, 0.2, 0.2 };
    GLfloat specular2[] = { 1.0, 1.0, 1.0 };

    glEnable(GL_LIGHT2);
    glDisable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_POSITION, lightpos2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambcolor2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightcolor2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular2);

    GLfloat lightpos3[] = { 0.0, 10.0, 100.0 };
    GLfloat lightcolor3[] = { 1, 1, 1};
    GLfloat ambcolor3[] = { 0.2, 0.2, 0.2 };
    GLfloat specular3[] = { 1.0, 1.0, 1.0 };
    glEnable(GL_LIGHT3);
    glLightfv(GL_LIGHT3, GL_POSITION, lightpos3);
    glLightfv(GL_LIGHT3, GL_AMBIENT, ambcolor3);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, lightcolor3);
    glLightfv(GL_LIGHT3, GL_SPECULAR, specular3);

    glEnable(GL_COLOR_MATERIAL); // tells opengl to maintain the original color of the object
}


void animate()
{
   if (!moon) {
    switch (camerad) {
        case 'c':camX = 50, camY = 5, camZ = 0.0;
            break;
        case 'd':camX = 50, camY = 5, camZ = 80.0;
            break;
    }
    }

    if(moon){
        glDisable(GL_LIGHT3);
        frame++;
        frame = frame % 360;
        if (frame <= 120) {
            glEnable(GL_LIGHT0);
            glDisable(GL_LIGHT1);
            glDisable(GL_LIGHT2);
        }
        else if(frame>120 && frame<=240){
            glDisable(GL_LIGHT0);
            glEnable(GL_LIGHT1);
            glDisable(GL_LIGHT2);
        }
        else {
            glDisable(GL_LIGHT0);
            glDisable(GL_LIGHT1);
            glEnable(GL_LIGHT2);
        }
    }

    switch (direction)
    {
    case 'k':
        if (loop_number < 1010)
        {
            glDisable(GL_LIGHT0);
            glDisable(GL_LIGHT1);
            glDisable(GL_LIGHT2);
            glEnable(GL_LIGHT3);
            loop_number++;
            //move1 += 0.01;
            getline(fin, line);
            stringstream ss(line);
            std::string value1, value2, value3, value4, value5, value6, value7, value8, value9, value10, value11;
            getline(ss, value1, ',');
            getline(ss, value2, ',');
            getline(ss, value3, ',');
            getline(ss, value4, ',');
            getline(ss, value5, ',');
            getline(ss, value6, ',');
            getline(ss, value7, ',');
            getline(ss, value8, ',');
            getline(ss, value9, ',');
            getline(ss, value10, ',');
            getline(ss, value11, ',');
            rja = stod(value1);
            rka = stod(value2);
            lja = stod(value3);
            lka = stod(value4);
            hrja = stod(value5);
            hrka = stod(value6);
            hlja = stod(value7);
            hlka = stod(value8);
            tx = stod(value9);
            ty = stod(value10);
            axrot = stod(value11);
            h = ActualHeight();
            if (loop_number < 1010)
                moving = 1;
        }
        break;

    case 'w':
        if (loop_number < 760)
        {
            glDisable(GL_LIGHT0);
            glDisable(GL_LIGHT1);
            glDisable(GL_LIGHT2);
            glEnable(GL_LIGHT3);
            loop_number++;
            xpos += 0.007;
            getline(fin, line);
            stringstream ss(line);
            std::string value1, value2, value3, value4, value5, value6, value7, value8;
            getline(ss, value1, ',');
            getline(ss, value2, ',');
            getline(ss, value3, ',');
            getline(ss, value4, ',');
            getline(ss, value5, ',');
            getline(ss, value6, ',');
            getline(ss, value7, ',');
            getline(ss, value8, ',');
            rja = stod(value1);
            rka = stod(value2);
            lja = stod(value3);
            lka = stod(value4);
            hrja = stod(value5);
            hrka = stod(value6);
            hlja = stod(value7);
            hlka = stod(value8);
            axrot = 0;
            h = ActualHeight();
            if (loop_number < 760)
                moving = 1;
        }
        cout << h << endl;
        break;

    case 'm':
        if (loop_number < 2040)
        {
            camX = 50, camY = 5, camZ = 80.0;
            loop_number++;
            xpos -= 0.01;
            getline(fin, line);
            stringstream ss(line);
            std::string value1, value2, value3, value4, value5, value6, value7, value8;
            getline(ss, value1, ',');
            getline(ss, value2, ',');
            getline(ss, value3, ',');
            getline(ss, value4, ',');
            getline(ss, value5, ',');
            getline(ss, value6, ',');
            getline(ss, value7, ',');
            getline(ss, value8, ',');
            rja = stod(value1);
            rka = stod(value2);
            lja = stod(value3);
            lka = stod(value4);
            hrja = -25;
            hrka = 25;
            hlja = -25;
            hlka = 25;
            axrot = -5;
            h = ActualHeight();
            if (loop_number < 2040)
                moving = 1;
        }
        cout << h << endl;
        break;
    }

    if (loop_number >= 760 && !kick && !moon)
    {
        moving = 0;
        fin.close();
        if (direction == 'k') {
            xpos += 25;
            tx = 0;
            ty = 0;
            direction = 's';
        }
    }
    if (loop_number >= 1010 && kick && !moon)
    {
        moving = 0;
        fin.close();
        if (direction == 'k') {
            xpos += 25;
            tx = 0;
            ty = 0;
            direction = 's';
        }
    }
    if (loop_number >= 2040 && !kick && moon)
    {
        moving = 0;
        fin.close();
        if (direction == 'k') {
            xpos += 25;
            tx = 0;
            ty = 0;
            direction = 's';
        }
    }
    glutPostRedisplay();
}

void display()
{

    /* clear window */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        camX, camY, camZ,
        0.0f, 0.0f, 0.0f, // 3rd variable can be move1 also to be following the body
        0.0f, 1.0f, 0.0f);

    GLUquadric *quadric = gluNewQuadric();
    
    glPushMatrix(); // whole set
    glTranslatef(0, 8, 0);
        glTranslatef(0, h/42, 0);
    if (direction == 'k') {
        glTranslatef(0, ty, xpos+tx);
    }
    else {
        glTranslatef(0,0,xpos);
    }
    glRotatef(axrot, -1, 0, 0);
        glColor3f(1.000, 0.894, 0.710);
        glPushMatrix(); // abdomen

            glPushMatrix(); // neck
            glTranslatef(0, -2, 0);
                glPushMatrix(); // face
                glTranslatef(0, 2.8, 0);
                glScalef(1, 1.5, 1);
                glutWireCube(3.5);
                glPopMatrix(); // face
            gluSphere(quadric, 1.0, 20, 20);
            glPopMatrix(); // neck

            glPushMatrix(); // right hand 1 joint
            glTranslatef(-3.9, -3.2, 0);
            glRotatef(hrja, -1, 0, 0);
            glTranslatef(3.9, 3.2, 0);
                glPushMatrix(); // right hand 1
                    glPushMatrix(); // right hand 2 joint
                    glTranslatef(-3.9, -8.2, 0);
                    glRotatef(hrka, -1, 0, 0);
                    glTranslatef(3.9, 8.2, 0);
                        glPushMatrix(); // right hand 2
                        glTranslatef(-3.9, -11, 0);
                        glScalef(0.8, 2, 0.8);
                        glutSolidCube(2.5);
                        glPopMatrix(); // right hand 2
                    glTranslatef(-3.9, -8.2, 0);
                    gluSphere(quadric, 1.0, 20, 20);
                    glPopMatrix(); // right hand 2 joint
                glTranslatef(-3.9, -5.7, 0);
                glScalef(0.8, 2, 0.8);
                glutWireCube(2.5);
                glPopMatrix(); // right hand 1
            glTranslatef(-3.9, -3.2, 0);
            gluSphere(quadric, 1.0, 20, 20);
            glPopMatrix(); // right hand 1 joint

            glPushMatrix(); // left hand 1 joint
            glTranslatef(3.9, -3.2, 0);
            glRotatef(hlja, -1, 0, 0);
            glTranslatef(-3.9, 3.2, 0);
                glPushMatrix(); // left hand 1
                    glPushMatrix(); // left hand 2 joint
                    glTranslatef(3.9, -8.2, 0);
                    glRotated(hlka, -1, 0, 0);
                    glTranslatef(-3.9, 8.2, 0);
                        glPushMatrix(); // left hand 2
                        glTranslatef(3.9, -11, 0);
                        glScalef(0.8, 2, 0.8);
                        glutSolidCube(2.5);
                        glPopMatrix(); // left hand 2
                    glTranslatef(3.9, -8.2, 0);
                    gluSphere(quadric, 1.0, 20, 20);
                    glPopMatrix(); // left hand 2 joint
                glTranslatef(3.9, -5.7, 0);
                glScalef(0.8, 2, 0.8);
                glutWireCube(2.5);
                glPopMatrix(); // left hand 1
            glTranslatef(3.9, -3.2, 0);
            gluSphere(quadric, 1.0, 20, 20);
            glPopMatrix(); // left hand 1 joint

            glPushMatrix(); // right butt
            glTranslatef(-1.4, -11, 0);
            glRotatef((rja), -1, 0, 0);
            glTranslatef(1.4, 11, 0);
                glPushMatrix(); // right leg 1
                    glPushMatrix(); // right leg 2 joint
                    glTranslatef(-1.4, -17.5, 0);
                    glRotatef((rka), -1, 0, 0);
                    glTranslatef(1.4, 17.5, 0);
                        glPushMatrix(); // right leg 2
                        glPushMatrix();
                        glTranslatef(-1.4, -22, 0);
                        glutWireCube(2.5);
                        glPopMatrix();
                        glTranslatef(-1.4, -20, 0);
                        glScalef(1, 1.8, 1);
                        glutSolidCube(2.5);
                        glPopMatrix(); // right leg 2
                    glTranslatef(-1.4, -17.5, 0);
                    gluSphere(quadric, 1.0, 20, 20);
                    glColor3f(1.000, 0.894, 0.710);
                    glPopMatrix(); // right leg 2 joint
                glTranslatef(-1.4, -14.8, 0);
                glScalef(1, 1.8, 1);
                glutSolidCube(2.5);
                glPopMatrix(); // right leg 1
            glTranslatef(-1.4, -11, 0);
            glutWireCube(2.5);
            glPopMatrix(); // right butt

            glPushMatrix(); // left butt
            glTranslatef(1.4, -11, 0);
            glRotatef((lja), -1, 0, 0);
            glTranslatef(-1.4, 11, 0);
                glPushMatrix(); // left leg 1
                    glPushMatrix(); // left leg 2 joint
                    glTranslatef(1.4, -17.5, 0);
                    glRotatef((lka), -1, 0, 0);
                    glTranslatef(-1.4, 17.5, 0);
                        glPushMatrix(); // left leg 2
                        glPushMatrix();
                        glTranslatef(1.4, -22, 0);
                        glutWireCube(2.5);
                        glPopMatrix();
                        glTranslatef(1.4, -20, 0);
                        glScalef(1, 1.8, 1);
                        glutSolidCube(2.5);
                        glPopMatrix(); // left leg 2
                    glTranslatef(1.4, -17.5, 0);
                    gluSphere(quadric, 1.0, 20, 20);
                    glPopMatrix(); // left leg 2 joint
                glTranslatef(1.4, -14.8, 0);
                glScalef(1, 1.8, 1);
                glutSolidCube(2.5);
                glColor3f(1.000, 0.894, 0.710);
                glPopMatrix(); // left leg 1
            glTranslatef(1.4, -11, 0);
            glutWireCube(2.5);
            glPopMatrix(); // left butt

            glPushMatrix(); // shoulder bone
            glTranslatef(0, -3, 0);
            glScalef(8, 1, 1);
            glutSolidCube(1);
            glPopMatrix(); // shoulder bone

        glTranslatef(0, -6, 0);
        glScalef(1.5, 2, 1);
        glutSolidCube(3.5);
        glPopMatrix(); // abdomen

    glPopMatrix(); // whole set

    gluDeleteQuadric(quadric);
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex3f(100, -15.5, 100);
    glVertex3f(-100, -15.5, 100);
    glVertex3f(-100, -15.5, -100);
    glVertex3f(100, -15.5, -100);
    glEnd();
    glFlush();
}

void reshape(int width, int height)
{

    /* define the viewport transformation */
    glViewport(0, 0, width, height);
}

int main(int argc, char *argv[])
{

    std::atexit(fileClose);
    /* initialize GLUT, using any commandline parameters passed to the program */
    glutInit(&argc, argv);

    /* setup the size, position, and display mode for new windows */
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);

    /* create and set up a window */
    glutCreateWindow("The Legend");
    glutDisplayFunc(display);
    
    /* set up depth-buffering */
    glEnable(GL_DEPTH_TEST);

    initLight();

    /* define the projection transformation */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 4, 100);

    glutMouseFunc(sphereMouseEvent);
    glutMotionFunc(sphereMouseMotion);
    glutKeyboardFunc(keyBoard); // void keyBoard(unsigned char key, int x, int y);
    glutSpecialFunc(arrowKey);  // void arrowKey(int key, intx, int y)
    glutIdleFunc(animate);      // register the IdleFunction

    glutMainLoop(); /* tell GLUT to wait for events */
}