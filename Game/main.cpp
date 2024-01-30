#ifdef _WIN32
    #include<windows.h>
#endif
#include<stdio.h>
#include<stdlib.h>
#include<GLUT/GLUT.h>
#include <math.h>
#define GL_SILENCE_DEPRECATION

#define XMAX 1200
#define YMAX 700
#define Person_SPEED 2
#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3

GLint m_viewport[4];
bool mButtonPressed = false;
float mouseX, mouseY;
int x,y,r=20;  //for head
enum view {INTRO, MENU, INSTRUCTIONS, GAME, GAMEOVER};
view viewPage = INTRO; // initial value
bool keyStates[256] = {false};
bool direction[4] = {false};
bool laser1Dir[2] = {false};
bool laser2Dir[2] = {false};
int personLife1 = 100;
int personLife2 = 100;
bool gameOver = false;
float xOne = 500, yOne = 0;
float xTwo = 500, yTwo = 0;
bool laser1 = false, laser2 = false;

void displayRasterText(float x ,float y ,float z, char *stringToDisplay) {
    glRasterPos3f(x, y, z);
    for(char* c = stringToDisplay; *c != '\0'; c++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}

void init(){
    glClearColor(0.0,0.0,0.0,0);
    glColor3f(1.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1200,1200,-700,700); //<---CHANGE THIS TO GET EXTRA SPACE
    glMatrixMode(GL_MODELVIEW);
}

void introScreen()
{
    glClear(GL_COLOR_BUFFER_BIT); 

        glColor3f(0.0, 0.5, 1.0); // GL_Points
    displayRasterText(-150, 550, 0.0,"\"Laser War Game\"");
        glColor3f(1.0, 1.0, 0.25);
    displayRasterText(-700, 400, 0.0,"Team Members: ");
        glColor3f(1.0, 1.0, 0.50);
    displayRasterText(-700, 334, 0.0,"- Basmala Abuzaid CS");
        glColor3f(1.0, 1.0, 0.50);
    displayRasterText(-700, 268, 0.0,"- Tasbeeh Ismail CS");
        glColor3f(1.0, 1.0, 0.50);
    displayRasterText(-700, 202, 0.0,"- Omnia Gamal IS");
        glColor3f(1.0, 1.0, 0.50);
    displayRasterText(-700, 136, 0.0,"- Norhan Kamal IT");
        glColor3f(1.0, 1.0, 0.50);
    displayRasterText(-700, 70, 0.0,"- Mohamed Rizk CS");
        glColor3f(1.0, 1.0, 0.50);
    displayRasterText(-700, 4, 0.0,"- Mohamed Abdullah CS");
        glColor3f(1.0, 0.20, 0.5);
    displayRasterText(400, 400, 0.0,"Associate Professor: ");
        glColor3f(1.0, 0.45, 0.5);
    displayRasterText(400, 334, 0.0,"- Dr. Ebtsam Adel");
        glColor3f(1.0, 0.20, 0.5);
    displayRasterText(400, 202, 0.0,"TA Supervisor: ");
        glColor3f(1.0, 0.45, 0.5);
    displayRasterText(400, 136, 0.0,"- Eng. Mohamed Yacoub");
        glColor3f(1.0, 1.0, 1.0);
    displayRasterText(-300, -550, 0.0,"Press ENTER to start the game");
    glFlush();
    glutSwapBuffers();
}

void startScreenDisplay()
{
    glLineWidth(10);

    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);               //Border
        glVertex2f(-750 ,-500);
        glVertex2f(-750 ,550);
        glVertex2f(750 ,550);
        glVertex2f(750 ,-500);
    glEnd();

    glLineWidth(1);

    glColor3f(1, 1, 0);
    glBegin(GL_POLYGON);                //START GAME PLOYGON
        glVertex2f(-200 ,300);
        glVertex2f(-200 ,400);
        glVertex2f(200 ,400);
        glVertex2f(200 ,300);
    glEnd();

    glBegin(GL_POLYGON);                //INSTRUCTIONS POLYGON
        glVertex2f(-200, 50);
        glVertex2f(-200 ,150);
        glVertex2f(200 ,150);
        glVertex2f(200 ,50);
    glEnd();

    glBegin(GL_POLYGON);                //QUIT POLYGON
        glVertex2f(-200 ,-200);
        glVertex2f(-200 ,-100);
        glVertex2f(200, -100);
        glVertex2f(200, -200);
    glEnd();

    if(mouseX>=-100 && mouseX<=100 && mouseY>=150 && mouseY<=200){
        glColor3f(0 ,0 ,1) ;
        if(mButtonPressed){
            personLife1 = personLife2 = 100;
            viewPage = GAME;
            mButtonPressed = false;
        }
    } else
        glColor3f(0 , 0, 0);

    displayRasterText(-100 ,340 ,0.4 ,"Start Game");

    if(mouseX>=-100 && mouseX<=100 && mouseY>=30 && mouseY<=80) {
        glColor3f(0 ,0 ,1);
        if(mButtonPressed){
            viewPage = INSTRUCTIONS;
            printf("button pressed bitch\n");
            mButtonPressed = false;
        }

    } else
        glColor3f(0 , 0, 0);

    displayRasterText(-120 ,80 ,0.4 ,"Instructions");

    if(mouseX>=-100 && mouseX<=100 && mouseY>=-90 && mouseY<=-40){
        glColor3f(0 ,0 ,1);
        if(mButtonPressed){
            mButtonPressed = false;
            exit(0);
        }
    }
    else
        glColor3f(0 , 0, 0);
    displayRasterText(-100 ,-170 ,0.4 ,"    Quit");
    glutPostRedisplay();
}

void backButton() {
    if(mouseX <= -450 && mouseX >= -500 && mouseY >= -275 && mouseY <= -250){
            glColor3f(0, 0, 1);
            if(mButtonPressed) {
                viewPage = MENU;
                mButtonPressed = false;
                glutPostRedisplay();
            }
    }
    else glColor3f(1, 0, 0);
    
    displayRasterText(-1000 ,-550 ,0, "Back");
}

void instructionsScreenDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 0, 0);
    displayRasterText(-900 ,550 ,0.4 ,"INSTRUCTIONS");
    
    glColor3f(1, 0, 0);
    displayRasterText(-1000 ,400 ,0.4 ,"PLAYER 1");
    displayRasterText(200 ,400 ,0.4 ,"PLAYER 2");
    
    glColor3f(1, 1, 1);
    displayRasterText(-1100 ,300 ,0.4 ,"Key 'w' to move up.");
    displayRasterText(-1100 ,200 ,0.4 ,"Key 's' to move down.");
    displayRasterText(-1100 ,100 ,0.4 ,"Key 'd' to move right.");
    displayRasterText(-1100 ,0 ,0.4 ,"Key 'a' to move left.");
    displayRasterText(100 ,300 ,0.4 ,"Key 'i' to move up.");
    displayRasterText(100 ,200 ,0.4 ,"Key 'k' to move down.");
    displayRasterText(100 ,100 ,0.4 ,"Key 'j' to move right.");
    displayRasterText(100 ,0 ,0.4 ,"Key 'l' to move left.");
    displayRasterText(-1100 ,-100 ,0.4 ,"Key 'c' to shoot, Use 'w' and 's' to change direction.");
    displayRasterText(100 ,-100 ,0.4 ,"Key 'm' to shoot, Use 'i' and 'k' to change direction.");
    displayRasterText(-1100, -300,0.4,"The Objective is to kill your opponent.");
    displayRasterText(-1100 ,-370 ,0.4 ,"Each time a player gets shot, LIFE decreases by 1 points.");
    
    backButton();
    
}

void DrawPerson(bool isPlayer1)
{
    if(isPlayer1)
        glColor3f(0,1,0);
    else
        glColor3f(1,1,0);        //BODY color

   glPointSize(2);
    glBegin(GL_POINTS);
    for(double i=0;i<2*M_PI;i+=0.0001){
        x=r*cos(i);
        y=r*sin(i);
        glVertex2i(x,y);
    }
    glEnd();

    glBegin(GL_LINES);

    glVertex2i(0,-r);
    glVertex2i(0,-100);

    glVertex2i(0,-40);
    glVertex2i(-50,-70);

    glVertex2i(0,-40);
    glVertex2i(50,-70);

    glVertex2i(0,-100);
    glVertex2i(-50,-170);

    glVertex2i(0,-100);
    glVertex2i(50,-170);

    glEnd();

}

void DrawLaser(int x, int y, bool dir[]) {
    y-=50;
    int xend = -XMAX, yend = y;
    if(dir[0])
        yend = YMAX;
    else if(dir[1])
        yend = -YMAX;
    
    glLineWidth(5);
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
        glVertex2f(x-50, y);
        glVertex2f(xend, yend);
    glEnd();
}

void PresonCreate(int x, int y, bool isPlayer1){
    glPushMatrix();
    glTranslated(x,y,0);
    glPushMatrix();
    glTranslated(4,19,0);
    DrawPerson(isPlayer1);
    glPopMatrix();
    glEnd();
    glPopMatrix();
}
void DisplayHealthBar1() {
    char temp1[40];
    glColor3f(1 ,1 ,1);
    sprintf(temp1,"  LIFE = %d",personLife1);
    displayRasterText(-1100 ,600 ,0.4 ,temp1);
}

void DisplayHealthBar2() {
    char temp2[40];
    glColor3f(1 ,1 ,1);
    sprintf(temp2,"  LIFE = %d",personLife2);
    displayRasterText(800 ,600 ,0.4 ,temp2);
}

void checkLaserContact(int x, int y, bool dir[], int xp, int yp, bool player1) {
    int xend = -XMAX, yend = y;
    xp += 8; yp += 8; // moving circle slightly up to fix laser issue
    if(dir[0])
        yend = YMAX;
    else if(dir[1])
        yend = -YMAX;

    // Here we find out if the laser(line) intersects with person's heart(circle)
    // by solving the equations for the same and finding the discriminant of the
    // quadratic equation obtained
    float m = (float)(yend - y) / (float)(xend - x);
    float k = y - m * x ;

    //calculating value of b, a, and c needed to find discriminant
    float b = 2 * xp - 2 * m * (k - yp);
    float a = 1 + m * m;
    float c = xp * xp + (k - yp) * (k - yp) - r * r;

    float d = (b * b - 4 * a * c); // discriminant for the equation

    if(d >= 0) {
        if(player1)
            personLife1 -= 1;
        else
            personLife2 -= 1;

    }
}

void gameScreenDisplay()
{
    DisplayHealthBar1();
    DisplayHealthBar2();
    glScalef(2, 2, 0);

    if(personLife1 > 0){
        PresonCreate(xOne,yOne,true); // displat person
        if(laser1) {
            DrawLaser(xOne, yOne, laser1Dir);
            checkLaserContact(xOne, yOne, laser1Dir, -xTwo, yTwo, true);
        }
    }
    else {
        viewPage = GAMEOVER;
    }

    if(personLife2 > 0) {
        glPushMatrix();
        glScalef(-1, 1, 1);
        PresonCreate(xTwo,yTwo,false);
        if(laser2) {
            DrawLaser(xTwo, yTwo, laser2Dir);
            checkLaserContact(xTwo, yTwo, laser2Dir, -xOne, yOne, false);
        }
        glPopMatrix();
    }
    else {
        viewPage = GAMEOVER;
    }

    if(viewPage == GAMEOVER) {
        xOne = xTwo = 500;
        yOne = yTwo = 0;
    }
}

void displayGameOverMessage() {
    glColor3f(1, 1, 0);
    char* message;
    if(personLife1 > 0)
        message = "Game Over! Player 1 won the game";
    else
        message = "Game Over! Player 2 won the game";

    displayRasterText(-350 ,0 ,0, message);
    backButton();
}

void keyOperations() {
    if(keyStates[13] == true && viewPage == INTRO) {
        viewPage = MENU;
        printf("view value changed to %d", viewPage);
        printf("enter key pressed\n");
    }
    
    if(viewPage == GAME) {
        laser1Dir[0] = laser1Dir[1] = false;
        laser2Dir[0] = laser2Dir[1] = false;
        if(keyStates['c'] == true) {
            laser2 = true;
            if(keyStates['w'] == true)     laser2Dir[0] = true;
            if(keyStates['s'] == true)     laser2Dir[1] = true;
        }
        else {
            laser2 = false;
            if(keyStates['d'] == true) xTwo-=Person_SPEED;
            if(keyStates['a'] == true) xTwo+=Person_SPEED;
            if(keyStates['w'] == true) yTwo+=Person_SPEED;
            if(keyStates['s'] == true) yTwo-=Person_SPEED;
        }

        if(keyStates['m'] == true) {
            laser1 = true;
            if(keyStates['i'] == true) laser1Dir[0] = true;
            if(keyStates['k'] == true) laser1Dir[1] = true;
        }
        else {
            laser1 = false;
            if(keyStates['l'] == true) xOne+=Person_SPEED;
            if(keyStates['j'] == true) xOne-=Person_SPEED;
            if(keyStates['i'] == true) yOne+=Person_SPEED;
            if(keyStates['k'] == true) yOne-=Person_SPEED;
        }
    }
}

void display()
{
    keyOperations();
    glClear(GL_COLOR_BUFFER_BIT);

    switch (viewPage)
    {
        case INTRO:
            introScreen();
            break;
        case MENU:
            startScreenDisplay();
            break;
        case INSTRUCTIONS:
            instructionsScreenDisplay();
            break;
        case GAME:
            gameScreenDisplay();
            break;
        case GAMEOVER:
            displayGameOverMessage();
            break;
    }

    glFlush();
    glLoadIdentity();
    glutSwapBuffers();
}
void passiveMotionFunc(int x,int y) {

    //when mouse not clicked
    mouseX = float(x)/(m_viewport[2]/1200.0)-600.0;  //converting screen resolution to ortho 2d spec
    mouseY = -(float(y)/(m_viewport[3]/700.0)-350.0);

    glutPostRedisplay();
}

void mouseClick(int buttonPressed ,int state ,int x, int y) {

    if(buttonPressed == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        mButtonPressed = true;
    else
        mButtonPressed = false;
    glutPostRedisplay();
}

void keyPressed(unsigned char key, int x, int y)
{
    keyStates[key] = true;
    glutPostRedisplay();
}

void refresh() {
    glutPostRedisplay();
}

void keyReleased(unsigned char key, int x, int y) {
    keyStates[key] = false;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1200, 600);
    glutCreateWindow("Laser War");
    init();

    glutIdleFunc(refresh);
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyReleased);
    glutMouseFunc(mouseClick);
    glutPassiveMotionFunc(passiveMotionFunc);
    glGetIntegerv(GL_VIEWPORT ,m_viewport);
    glutDisplayFunc(display);
    glutMainLoop();
}
