#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include<stdbool.h>

int flag=0,flag1=0;
int value=42;
float ballX = 0.0,ballY = 0.0,ballZ = -5,hi=0,mv=0;
int pitched,hit=0,count=0;
char spin[10],score[20];
double turn,offX=0,offY=0,offZ=0,midX=0,midY=0,midZ=0,legX=0,legY=0,legZ=0,bX=0,bY=0,bZ=0;
GLdouble mx,my;
bool ball_hit;
int miss=0;
int winID,winID1,winID2;
int whoseturn = 1;

int player1_score = 0;
bool player1 = true;
bool player2 = false;
int player2_score = 0;


GLdouble cord[3];
GLint viewport[4];
GLdouble modelview[16];
GLdouble projection[16];
void start();
void move();
void game_over();
void draw_stumps();
void drawBitmapText(char *string,float x,float y,float z);




double random_gen()
{
srand(time(NULL));
double r1=(double)rand()/(double)RAND_MAX;
r1=(r1*2.64)-1.32;
printf("%f\n",r1);
return r1;
}
void mykeyboard(unsigned char key, int x, int y)
{
    if(key==13)
        {
       glutIdleFunc(start);
        }


}


void scorer()
{
    glColor3f(1.0,1.0,1.0);
    if(player1){
    sprintf(score, "PLAYER1 SCORE : %d", count);
    drawBitmapText(score,3.25,4.0,-6.0);
    }
    else{
    sprintf(score, "PLAYER2 SCORE : %d", count);
    drawBitmapText(score,3.25,4.0,-6.0);

    }

    if(turn<=0)
        sprintf(spin, "<<<%2.2f", (turn*-5/1.32));
    else
        sprintf(spin, "%2.2f>>>", (turn*5/1.32));
    drawBitmapText(spin,-0.20,4,-6.0);
}
void frontscreen()
{
     drawBitmapText("SAHYADRI COLLEGE OF ENGINEERING ",-0.60,4,-6.0);
    glColor3f(0.7,0,1);
     drawBitmapText("DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING",-1.90,3.5,-6.0);
    //glColor3f(1,0.5,0);
     //drawBitmapText("A MINI PROJECT ON",-0.75,3,-6.0);
    glColor3f(1,0,0);
     drawBitmapText("HIT THE STUMPS !!!",-0.65,2.5,-6.0);
    glColor3f(1,0.5,0);
     drawBitmapText("BY:",-0.2,2,-6.0);
    glColor3f(0.5,0,0.5);
     drawBitmapText("SUGHOSH S V (4SF20CS158)",-1.05,1.5,-6.0);
    glColor3f(0.5,0,0.5);
     drawBitmapText("VINAYAK B KALMANE (4SF20CS175)",-1,1,-6.0);
    glColor3f(0,0,0);
     drawBitmapText("PRESS ENTER TO START",-0.80,-2,-6.0);
    glColor3f(0.0,0.0,0.0);
     drawBitmapText("INSTRUCTIONS  FOR  THE  GAME",-01.1,0,-6.0);
    glColor3f(0,0,1);
     drawBitmapText("* The spin for each of the ball will be displayed at top-centre position.",-2.8,-0.5,-6.0);
    glColor3f(0,0,1);
     drawBitmapText("* You need to pitch the ball using mouse clicks, taking the spin into account so as to hit the stumps.",-2.8,-1,-6);
    glColor3f(0.0,0.0,01.0);
     drawBitmapText("* Pitch the ball on the white strip for best results.Break 'em all!! :)",-2.8,-1.5,-6);
    glColor3f(0.0,0.0,0.0);
     //drawBitmapText("PRESS  'p' TO  PLAY",-0.8,0,-6);
}


void drawBall(float ballX,float ballY,float ballZ) {
        //glColor3f(1.0, 0.0, 0.0); //set ball colour
        glTranslatef(ballX,ballY,ballZ); //moving it toward the screen a bit on creation
        glutSolidSphere (0.06, 20, 20); //create ball.
}


void draw_middle_stump()
{
//middle stump
    glColor3f(0.502, 0.502, 0.000);
    glLineWidth(5.40);
    if(hit==1)
    {
     midX=midX+0.001;
     midY=midY-0.0015;
     midZ=midZ-0.002;
    glBegin(GL_LINES);
    glVertex3f(0.0,-1,-11.06);
    glVertex3f(0.0+midX,0.0+midY,-11.06+midZ);
    glVertex3f(0.0,-1,-11.16);
    glVertex3f(0.0+midX,0.0+midY,-11.16+midZ);
    glEnd();
    }
    else{
    glBegin(GL_LINES);
    glVertex3f(0.0,-1,-11.06);
    glVertex3f(0.0,-0.0,-11.06);
    glVertex3f(0.0,-1,-11.16);
    glVertex3f(0.0,-0.0,-11.16);
    glEnd();
    }


}

void draw_off_stump()
{
//off stump
    //glColor3f(0.50,0.50,0.80);
    glLineWidth(5.40);
    if(hit==1)
    {
     offX=offX-0.004;
     offY=offY-0.0015;
     offZ=offZ-0.002;
    glBegin(GL_LINES);
    glVertex3f(-0.10,-1,-11.06);
    glVertex3f(-0.10+offX,0.0+offY,-11.06+offZ);
    glVertex3f(-0.10,-1,-11.16);
    glVertex3f(-0.10+offX,0.0+offY,-11.16+offZ);
    glEnd();
 //   printf("middle %f\t%f\n",0.0+posX);
    }
    else
    {
    glBegin(GL_LINES);
    glVertex3f(-0.10,-1,-11.06);
    glVertex3f(-0.10,-0.0,-11.06);
    glVertex3f(-0.10,-1,-11.16);
    glVertex3f(-0.10,-0.0,-11.16);
    glEnd();
    }
}

void game_over(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glRasterPos2f(-0.2, 0.2);  // Set the position for drawing text (adjust as needed)
    const char* text;
    if(count == 0){
        text  = "Try Again";
    }
    else{
        text  = "Game Over";
    }
glRasterPos2f(0,0);
    for (int i = 0; i < strlen(text); i++) {

        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
    glRasterPos2f(0,0);
    //sprintf(score, "SCORE : %d", count);
    //drawBitmapText(score,3.25,4.0,-6.0);


    sprintf(score, "PLAYER1 SCORE : %d", player1_score);
    drawBitmapText(score,4.25,2.0,-6.0);

    sprintf(score, "PLAYER2 SCORE : %d", player2_score);
    drawBitmapText(score,4.25,4.0,-6.0);


    if(whoseturn==3){

    if(player1_score > player2_score)
    {
    sprintf(score, "PLAYER1 WINS : %d", player1_score);
    drawBitmapText(score,3.25,8.0,-6.0);
    sleep(1);

    }

    else if(player1_score == player2_score)
    {
    sprintf(score, "MATCH DRAW ");
    drawBitmapText(score,3.25,8.0,-6.0);
        sleep(1);

    }
    else{
    sprintf(score, "PLAYER2 WINS : %d", player1_score);
    drawBitmapText(score,3.25,8.0,-6.0);
        sleep(1);

    }



    player1_score = 0;
    player2_score = 0;
    whoseturn = 1;


    }
    sleep(2);
    glFlush();

    }



void draw_leg_stump()
{
//leg stump
    //glColor3f(1.0,1.0,1.0);
    glLineWidth(5.40);
    if(hit==1)
    {
     legX=legX+0.002;
     legY=legY-0.001;
     legZ=legZ-0.002;glBegin(GL_LINES);
    glVertex3f(0.10,-1,-11.06);
    glVertex3f(0.10+legX,-0.0+legY,-11.06+legZ);
    glVertex3f(0.10,-1,-11.16);
    glVertex3f(0.10+legX,-0.0+legY,-11.16+legZ);
    glEnd();
    }
    else
    {
    glBegin(GL_LINES);
    glVertex3f(0.10,-1,-11.06);
    glVertex3f(0.10,-0.0,-11.06);
    glVertex3f(0.10,-1,-11.16);
    glVertex3f(0.10,-0.0,-11.16);
    glEnd();
    }


}

/*void draw_off_stump1()
{
//off stump
    //glColor3f(0.50,0.50,0.80);
    glLineWidth(5.40);
    if(hit==1)
    {offX=offX-0.004;
     offY=offY-0.0015;
     offZ=offZ-0.002;
    glBegin(GL_LINES);
    glVertex3f(-0.10,-1,-11.06);
    glVertex3f(-0.10+offX,0.0+offY,-11.06+offZ);
    glVertex3f(-0.10,-1,-11.16);
    glVertex3f(-0.10+offX,0.0+offY,-11.16+offZ);
    glEnd();
 //   printf("middle %f\t%f\n",0.0+posX);
    }
    else
    {glBegin(GL_LINES);
    glVertex3f(-0.10,-1,-11.06);
    glVertex3f(-0.10,-0.0,-11.06);
    glVertex3f(-0.10,-1,-11.16);
    glVertex3f(-0.10,-0.0,-11.16);
    glEnd();}
}
void draw_leg_stump1()
{
//leg stump
    //glColor3f(1.0,1.0,1.0);
    glLineWidth(5.40);
    if(hit==1)
    {legX=legX+0.002;
     legY=legY-0.001;
     legZ=legZ-0.002;}
    else{
    glBegin(GL_LINES);
    glVertex3f(0.0,-1,-11.06);
    glVertex3f(0.0,-0.0,-11.06);
    glVertex3f(0.0,-1,-11.16);
    glVertex3f(0.0,-0.0,-11.16);
    glEnd();
    }


}

void draw_off_stump()
{
//off stump
    //glColor3f(0.50,0.50,0.80);
    glLineWidth(5.40);
    if(hit==1)
    {offX=offX-0.004;
     offY=offY-0.0015;
     offZ=offZ-0.002;
    glBegin(GL_LINES);
    glVertex3f(-0.10,-1,-11.06);
    glVertex3f(-0.10+offX,0.0+offY,-11.06+offZ);
    glVertex3f(-0.10,-1,-11.16);
    glVertex3f(-0.10+offX,0.0+offY,-11.16+offZ);
    glEnd();
 //   printf("middle %f\t%f\n",0.0+posX);
    }
    else
    {glBegin(GL_LINES);
    glVertex3f(-0.10,-1,-11.06);
    glVertex3f(-0.10,-0.0,-11.06);
    glVertex3f(-0.10,-1,-11.16);
    glVertex3f(-0.10,-0.0,-11.16);
    glEnd();}
}
void draw_leg_stump2()
{
//leg stump
    //glColor3f(1.0,1.0,1.0);
    glLineWidth(5.40);
    if(hit==1)
    {legX=legX+0.002;
     legY=legY-0.001;
     legZ=legZ-0.002;
     glBegin(GL_LINES);
    glVertex3f(0.10,-1,-11.06);
    glVertex3f(0.10+legX,0.0+legY,-11.06+legZ);
    glVertex3f(0.10,-1,-11.16);
    glVertex3f(0.10+legX,0.0+legY,-11.16+legZ);
    glEnd();
 //   printf("middle %f\t%f\n",0.0+posX);
    }
    else
    {
    glBegin(GL_LINES);
    glVertex3f(0.10,-1,-11.06);
    glVertex3f(0.10,-0.0,-11.06);
    glVertex3f(0.10,-1,-11.16);
    glVertex3f(0.10,-0.0,-11.16);
    glEnd();
    }
}*/
void draw_bails()
{
//bails
glColor3f(1.000, 0.980, 0.941);
    if(hit==1)
    {bX=bX-0.005;
    bY=bY+0.01;
    bZ=bZ-0.04;
    glBegin(GL_LINES);
    glVertex3f(0.015-bX,0.0+bY,-11.06+bZ);
    glVertex3f(0.095-bX,0.0+bY,-11.06+bZ);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(-0.015+bX,0.0+bY,-11.06+bZ);
    glVertex3f(-0.095+bX,0.0+bY,-11.06+bZ);
    glEnd();
    }
    else
    {
    glBegin(GL_LINES);
    glVertex3f(0.015,0.0,-11.06);
    glVertex3f(0.095,0.0,-11.06);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(-0.015,0.0,-11.06);
    glVertex3f(-0.095,0.0,-11.06);
    glEnd();
    }
}
void pitch()
{
    glColor3f(0.941,0.902,0.549);
    glBegin(GL_POLYGON);
    glVertex3f(-1.32,-1,-13.28);
    glVertex3f(1.32,-1,-13.28);
    glVertex3f(1.32,-1,13.28);
    glVertex3f(-1.32,-1,13.28);
    glEnd();
    //crease
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-1.50,-1,-9.0);
    glVertex3f(1.50,-1,-9.0);
    glVertex3f(1.50,-1,-9.1);
    glVertex3f(-1.50,-1,-9.1);
    glEnd();
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-1.32,-1,-10.90);
    glVertex3f(1.32,-1,-10.90);
    glVertex3f(1.32,-1,-11.30);
    glVertex3f(-1.32,-1,-11.30);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(-1.30,-1,-7.50);
    glVertex3f(1.30,-1,-7.50);
    glVertex3f(1.30,-1,-7.90);
    glVertex3f(-1.30,-1,-7.90);
    glEnd();
    glLineWidth(3.50);
    glBegin(GL_POLYGON);
    glVertex3f(-0.98,-1.0,-13.28);
    glVertex3f(-0.98,-1.0,-9.0);
    glVertex3f(-1.02,-1.0,-9.0);
    glVertex3f(-1.02,-1.0,-13.28);
    glEnd();
    glLineWidth(3.20);
    glBegin(GL_POLYGON);
    glVertex3f(0.98,-1.0,-13.28);
    glVertex3f(0.98,-1.0,-9.0);
    glVertex3f(1.02,-1.0,-9.0);
    glVertex3f(1.02,-1.0,-13.28);
    glEnd();
}
void draw_stumps()
{draw_middle_stump();
draw_leg_stump();
draw_off_stump();
draw_bails();
}
void reset()
{



ballX = 0.0,ballY =0.0,ballZ = -5;pitched=0;turn=random_gen();hit=0;
offX=0,offY=0,offZ=0;
midX=0,midY=0,midZ=0;
legX=0,legY=0,legZ=0;
bX=0,bY=0,bZ=0;
glutIdleFunc(start);
}
void before_pitch()
{
sleep(0.99);
hi=-0.01;
mv=mx/100.0;
ballY=ballY+hi;
ballX=ballX+mv;
}
void after_pitch()
{
sleep(0.99);
hi=0.008;
mv=turn/100.0;
ballY=ballY+hi;
ballX=ballX+mv;
}

void move()
{   //scorer();
    draw_stumps();
    glColor3f(1.0,0.0,0.0);
    drawBall(ballX,ballY,ballZ);

    if (ballY<=-1)
    pitched=1;
    if (pitched == 1)
    after_pitch();
    else
    before_pitch();

    if(ballX>=-0.15 && ballX <=0.15 && ballZ<=-11.06 && ballZ >= -11.2)
    {hit=1;printf("****HIT****\n");}
        ball_hit = true;
    if (ballZ<=-12.0)
    {
    if(hit==0){

    whoseturn++;

    if(player1){

    player1 = false;
    player1_score = count;
    player2 = true;
    }
    else{

    player2_score = count;
    player2 = false;
    player1 = true;
    }


    ball_hit = false;
    printf("\nGame Over");


    sleep(1);

    game_over();
    count=0;



    }
    else
    count++;

    if(player1)
player1_score = count;
    else
player2_score = count;



    glutIdleFunc(NULL);
    sleep(2);
    reset();

    //scorer();
    }
    else
    ballZ=ballZ-0.0303;
    glLoadIdentity();
    scorer();
    glFlush ();
    glutPostRedisplay();
}
void start()
{



    flag1=1;
    draw_stumps();
    glLoadIdentity();
    scorer();
    //pitch();
    glFlush ();
    glutPostRedisplay();
    //pitch();

}
void drawBitmapText(char *string,float x,float y,float z)
{
char *c;
glRasterPos3f(x, y,z);
for (c=string; *c != '\0'; c++)
    {
    glColor3f(1.0,1.0,1.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}
void mouse(int btn, int state, int x, int y)
{
if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {mx=(((x-252)*2.64)/760)-1.32;my=y;
    //printf("%f\t%f\n",mx,my);
    glutIdleFunc(move);
    }
}
void dynam()
{
    if(flag==0)
        {
            frontscreen();
            flag=1;
            glFlush();
        }
        else if(flag1==1)
        {
            glColor3f (1.0, 1.0, 1.0);
            glLoadIdentity ();   /* clear the matrix */
            /* viewing transformation  */
            gluLookAt (0.0, -0.5, -5.0, 0.0, 0.0, -10.0,0.0, 1.0, 0.10);
            //draw_stumps();
            pitch();
            //glutPostRedisplay();
        }
}
void init(void)
{
   glClearColor (0.196, 0.804, 0.196, 1.0);
   glShadeModel(GL_FLAT);
   turn=random_gen();
   //glutIdleFunc(start);
}
void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    dynam();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glGetIntegerv( GL_VIEWPORT, viewport );
   glMatrixMode (GL_PROJECTION);
   glGetDoublev( GL_PROJECTION_MATRIX, projection );
   glLoadIdentity ();


   gluPerspective(75.0,(float)(w/h),0.0,22.0);
   glMatrixMode (GL_MODELVIEW);
   glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
   turn=random_gen();
   glutIdleFunc(dynam);
}



int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (1260,720);
   glutInitWindowPosition (0, 0);
  winID= glutCreateWindow (argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMouseFunc(mouse);
   glutKeyboardFunc(mykeyboard);
   //glutIdleFunc(start);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glEnable(GL_BLEND);
   glEnable(GL_LINE_SMOOTH);
   glutMainLoop();
   return 0;
}
