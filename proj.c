#include<stdio.h>
//#include<GL/glut.h>
#include<GLUT/glut.h>
#include<OpenGL/gl.h>
#include<math.h>
#include<stdbool.h>
#include<time.h>

#define CIRCLE_RADIUS 0.15f
#define pi 3.142857
#define discount 1
#define MAX 6

float q_matrix[16][4] = { {-10000, 0, 0, -10000},
							{0, 0, 0, -10000},
							{0, 0, 0, -10000},
							{0, -10000, 0, -10000},
							{-10000, 0, 0, 0},
							{0, 0, 0,0},
							{0, 0, 0, 0}, //WUMPUS
							{0, -10000, 0, 0},
							{10000, 10000, 10000, 10000}, //GOLD
							{0, 0, 0, 0},
							{0, 0, 0, 0},
							{0, -10000, 0, 0},
							{-10000, 0, -10000, 0}, //FINDS GOLD
							{0, 0, -10000, 0},
							{0, 0, -10000, 0},
                            {0, -10000, -10000, 0}
						};
float value = 0.0;
int cur_pos = 0;
float max =-1;
float val = 0;
int next_pos = 0;
int action = 1;
float reward = -0.04;

int j=0, i = 0, pos = 0, tx = 0, ty = 0;
float learning_rate = 0.5;
int select_action(int);
bool gameOver(int);

int circle_points = 100;
int flag = 0;
GLfloat yr,xr;
int score = 505;
int choice = 0;
int iter = 0;

void mydisplay();
void wumpus();
void display();
void grid();
void frontsreen();
void drawstring(float x,float y,float z,char *string);
void square();
void setFont();
void update();
void control();
void helpscreen();
void menu();
void *currentfont;
void final_page();
void translate();

int action_array[200];
float posx = 0.0, posy = 0.0;
int last_death;
int z;
int ctrl = 0;

char buf[MAX];

void final_page() //finalGrid
{
	
	glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
	glClearColor(0,0.5,0.5,1.0); //grid background
	glLineWidth(2.5);
	glColor3f(0.0,0.0,0.0);
	grid();
	glPopMatrix();
	setFont(GLUT_BITMAP_HELVETICA_18);
//1
    val = q_matrix[0][0];
	float rounded_up = ceilf(val * 100) / 100;
    gcvt(rounded_up, MAX, buf);
    drawstring(407.0,125.0,0.0,buf);
	
	val = q_matrix[0][1];
	rounded_up = ceilf(val * 100) / 100;
    gcvt(rounded_up, MAX, buf);
    drawstring(490.0,125.0,0.0,buf);

    val = q_matrix[0][2];
	rounded_up = ceilf(val * 100) / 100;
    gcvt(rounded_up, MAX, buf);
    drawstring(450.0,162.5,0.0,buf);

    val = q_matrix[0][3];
	rounded_up = ceilf(val * 100) / 100;
    gcvt(rounded_up, MAX, buf);
    drawstring(450.0,83.0,0.0,buf);

//2
    val = q_matrix[1][0];
    rounded_up = ceilf(val * 100) / 100;
    gcvt(rounded_up, MAX, buf);
    drawstring(557.0,125.0,0.0,buf);


    val = q_matrix[1][1];
    rounded_up = ceilf(val * 100) / 100;
    gcvt(rounded_up, MAX, buf);
    drawstring(650.0,125.0,0.0,buf);


    val = q_matrix[1][2];
	rounded_up = ceilf(val * 100) / 100;
    gcvt(rounded_up, MAX, buf);
    drawstring(600.0,162.5,0.0,buf);


    val = q_matrix[1][3];
	rounded_up = ceilf(val * 100) / 100;
    gcvt(rounded_up, MAX, buf);
    drawstring(600.0,83.0,0.0,buf);

//3
    val = q_matrix[2][0];
	rounded_up = ceilf(val * 100) / 100;
    gcvt(rounded_up, MAX, buf);
    drawstring(707.0,125.0,0.0,buf);

    val = q_matrix[2][1];
	rounded_up = ceilf(val * 100) / 100;
    gcvt(rounded_up, MAX, buf);
    drawstring(800.0,125.0,0.0,buf);

    val = q_matrix[2][2];
	rounded_up = ceilf(val * 100) / 100;
    gcvt(rounded_up, MAX, buf);
    drawstring(750.0,162.5,0.0,buf);

    val = q_matrix[2][3];
	rounded_up = ceilf(val * 100) / 100;
    gcvt(rounded_up, MAX, buf);
    drawstring(750.0,83.0,0.0,buf);

//4
    val = q_matrix[3][0];
    rounded_up = ceilf(val * 100) / 100;
    gcvt(rounded_up, MAX, buf);
    drawstring(857.0,125.0,0.0,buf);

    val = q_matrix[3][1];
    rounded_up = ceilf(val * 100) / 100;
    gcvt(rounded_up, MAX, buf);
    drawstring(950.0,125.0,0.0,buf);

    val = q_matrix[3][2];
    rounded_up = ceilf(val * 100) / 100;
    gcvt(rounded_up, MAX, buf);
    drawstring(900.0,162.5,0.0,buf);

    val = q_matrix[3][3];
    rounded_up = ceilf(val * 100) / 100;
    gcvt(rounded_up, MAX, buf);
    drawstring(900.0,83.0,0.0,buf);

//5
	val = -10000;
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(407.0,275.0,0.0,buf);

	val = -10000;
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(490.0,275.0,0.0,buf);

	val = -10000;
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(450.0,312.5,0.0,buf);

	val = -10000;
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(450.0,233.0,0.0,buf);

//6
	val = q_matrix[5][0];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(557.0,275.0,0.0,buf);


	val = q_matrix[5][1];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(650.0,275.0,0.0,buf);


	val = q_matrix[5][2];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(600.0,312.5,0.0,buf);


	val = q_matrix[5][3];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(600.0,233.0,0.0,buf);

//7
	val = -10000;
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(707.0,275.0,0.0,buf);

	val = -10000;
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(783.0,275.0,0.0,buf);

	val = -10000;
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(750.0,312.5,0.0,buf);

	val = -10000;
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(750.0,233.0,0.0,buf);

//8
	val = q_matrix[7][0];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(857.0,275.0,0.0,buf);


	val = q_matrix[7][1];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(931.0,275.0,0.0,buf);


	val = q_matrix[7][2];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(900.0,312.5,0.0,buf);

	val = q_matrix[7][3];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(900.0,233.0,0.0,buf);

//9
	val = q_matrix[8][0];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(407.0,425.0,0.0,buf);

	val = q_matrix[8][1];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(490.0,425.0,0.0,buf);

	val = q_matrix[8][2];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(450.0,462.5,0.0,buf);

	val = q_matrix[8][3];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(450.0,383.0,0.0,buf);

//10
	val = -10000;
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(557.0,425.0,0.0,buf);


	val = -10000;
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(650.0,425.0,0.0,buf);


	val = -10000;
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(600.0,462.5,0.0,buf);


	val = -10000;
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(600.0,383.0,0.0,buf);

//11
	val = q_matrix[10][0];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(707.0,425.0,0.0,buf);

	val = q_matrix[10][1];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(783.0,425.0,0.0,buf);

	val = q_matrix[10][2];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(750.0,462.5,0.0,buf);

	val = q_matrix[10][3];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(750.0,383.0,0.0,buf);

//12
	val = q_matrix[11][0];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(857.0,425.0,0.0,buf);


	val = q_matrix[11][1];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(931.0,425.0,0.0,buf);


	val = q_matrix[11][2];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(900.0,462.5,0.0,buf);

	val = q_matrix[11][3];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(900.0,383.0,0.0,buf);
//13
	val = q_matrix[12][0];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(407.0,575.0,0.0,buf);

	val = q_matrix[12][1];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(490.0,575.0,0.0,buf);

	val = q_matrix[12][2];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(450.0,612.5,0.0,buf);

	val = q_matrix[12][3];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(450.0,533.0,0.0,buf);

//14
	val = q_matrix[13][0];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(557.0,575.0,0.0,buf);


	val = q_matrix[13][1];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(650.0,575.0,0.0,buf);


	val = q_matrix[13][2];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(600.0,612.5,0.0,buf);


	val = q_matrix[13][3];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(600.0,533.0,0.0,buf);

//15
	val = q_matrix[14][0];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(707.0,575.0,0.0,buf);

	val = q_matrix[14][1];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(783.0,575.0,0.0,buf);

	val = q_matrix[14][2];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(750.0,612.5,0.0,buf);

	val = q_matrix[14][3];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(750.0,533.0,0.0,buf);

//16
	val = q_matrix[15][0];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(857.0,575.0,0.0,buf);

	val = q_matrix[15][1];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(931.0,575.0,0.0,buf);

	val = q_matrix[15][2];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(900.0,612.5,0.0,buf);

	val = q_matrix[15][3];
	rounded_up = ceilf(val * 100) / 100;
	gcvt(rounded_up, MAX, buf);
	drawstring(900.0,533.0,0.0,buf);
	
}

void translate()
{
	if(choice == 1) //learn
	{
		if(action_array[z] ==0 )
		{
			tx = -150.0;
			ty = 0.0;
			posx+=tx; posy+=ty;
			sleep(1);
			glPushMatrix();
			glTranslatef(posx, posy, 0.0);
			square();
			glPopMatrix();
			
		}
		else if (action_array[z] ==1 )
		{
			tx = 150.0;
			ty = 0.0;
			posx+=tx; posy+=ty;
			sleep(1);
			glPushMatrix();
			glTranslatef(posx, posy, 0.0);
			square();
			glPopMatrix();
			
		}
		else if(action_array[z] == 2 )
		{
			tx = 0.0;
			ty = 150.0;
			posx+=tx; posy+=ty;
			sleep(1);
			glPushMatrix();
			glTranslatef(posx, posy, 0.0);
			square();
			glPopMatrix();
		}
		else if( action_array[z] == 3 )
		{
			tx = 0.0;
			ty = -150.0;
			posx+=tx; posy+=ty;
			sleep(1);
			glPushMatrix();
			glTranslatef(posx, posy, 0.0);
			square();
			glPopMatrix();		
		}
		if(z <ctrl) z++;
		else
		{
			final_page();
		}
	}
}
void square()
{
    if(choice ==2)  //play
	{
		if(xr == 0 && yr == 150 || xr == 150 && yr == 300 || xr == 300 && yr == 150 || score < 0)
        {
			setFont(GLUT_BITMAP_TIMES_ROMAN_24);
			//glClearColor(0,0.5,0.5,1.0);/*background for cover page and grid */
			//glClear(GL_COLOR_BUFFER_BIT);
			drawstring(650.0,660.0,0.0,"You lost :-(");
			//choice = 0;
			//xr = 0;
			//yr = 0;
			score = 505;
        }
        else if (xr == 0 && yr == 300)
        {
			setFont(GLUT_BITMAP_TIMES_ROMAN_24);
			//glClearColor(0,0.5,0.5,1.0);/*background for cover page and grid */
			//glClear(GL_COLOR_BUFFER_BIT);
			drawstring(650.0,660.0,0.0,"You win! :-)");
			//choice = 0;
			xr = 0;
			yr = 300;
			score = 505;
			glBegin(GL_POLYGON);
				glColor3f(1.0,0.0,0.0);
				glVertex2f(xr+450,yr+100);
				glVertex2f(xr+500,yr+100);
				glColor3f(0.0,1.0,0.0);
				glVertex2f(xr+450,yr+150);
				glVertex2f(xr+500,yr+150);
				glColor3f(0.0,0.0,1.0);
				glVertex2f(xr+450,yr+100);
				glVertex2f(xr+450,yr+150);
				glColor3f(1.0,1.0,0.0);
				glVertex2f(xr+500,yr+100);
				glVertex2f(xr+500,yr+150);
			glEnd();
        }
        else
	    {
			glBegin(GL_POLYGON);
				glColor3f(1.0,0.0,0.0);
				glVertex2f(xr+450,yr+100);
				glVertex2f(xr+500,yr+100);
				glColor3f(0.0,1.0,0.0);
				glVertex2f(xr+450,yr+150);
				glVertex2f(xr+500,yr+150);
				glColor3f(0.0,0.0,1.0);
				glVertex2f(xr+450,yr+100);
				glVertex2f(xr+450,yr+150);
				glColor3f(1.0,1.0,0.0);
				glVertex2f(xr+500,yr+100);
				glVertex2f(xr+500,yr+150);
			glEnd();
        }
 	}
	if(choice ==1) //learn
	{
	glBegin(GL_POLYGON);
			glColor3f(1.0,0.0,0.0);
				glVertex2f(450,100);
				glVertex2f(500,100);
				glColor3f(0.0,1.0,0.0);
				glVertex2f(450,150);
				glVertex2f(500,150);
				glColor3f(0.0,0.0,1.0);
				glVertex2f(450,100);
				glVertex2f(450,150);
				glColor3f(1.0,1.0,0.0);
				glVertex2f(500,100);
				glVertex2f(500,150);	
		glEnd();
	}
 	glFlush();
}
void wumpus()
{
	//1
	int i;
		int triangleAmount = 20; //# of triangles used to draw circle

		//GLfloat radius = 0.8f; //radius
		GLfloat twicePi = 2.0f * pi;

		glBegin(GL_TRIANGLE_FAN);
		int x = 475;
		int y = 285;
		glVertex2f(x, y); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x + (50 * cos(i *  twicePi / triangleAmount)),
					y + (50 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x1 = 457;
		int y1 = 290;
		glVertex2f(x1, y1); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x1 + (15 * cos(i *  twicePi / triangleAmount)),
					y1 + (15 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x2 = 497;
		int y2 = 290;
		glVertex2f(x2, y2); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x2 + (15 * cos(i *  twicePi / triangleAmount)),
					y2 + (15 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x3 = 457;
		int y3 = 288;
		glVertex2f(x3, y3); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x3 + (7 * cos(i *  twicePi / triangleAmount)),
					y3 + (7 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x4 = 497;
		int y4 = 288;
		glVertex2f(x4, y4); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x4 + (7 * cos(i *  twicePi / triangleAmount)),
					y4 + (7 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
	//2
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x5 = 775;
		int y5 = 285;
		glVertex2f(x5, y5); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x5 + (50 * cos(i *  twicePi / triangleAmount)),
					y5 + (50 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x6 = 757;
		int y6 = 290;
		glVertex2f(x6, y6); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x6 + (15 * cos(i *  twicePi / triangleAmount)),
					y6 + (15 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x7 = 797;
		int y7 = 290;
		glVertex2f(x7, y7); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x7 + (15 * cos(i *  twicePi / triangleAmount)),
					y7 + (15 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x8 = 757;
		int y8 = 288;
		glVertex2f(x8, y8); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x8 + (7 * cos(i *  twicePi / triangleAmount)),
					y8 + (7 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x9 = 797;
		int y9 = 288;
		glVertex2f(x9, y9); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x9 + (7 * cos(i *  twicePi / triangleAmount)),
					y9 + (7 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();

	//3
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_TRIANGLE_FAN);
		int x10 = 625;
		int y10 = 435;
		glVertex2f(x10, y10); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x10 + (50 * cos(i *  twicePi / triangleAmount)),
					y10 + (50 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x11 = 607;
		int y11 = 440;
		glVertex2f(x11, y11); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x11 + (15 * cos(i *  twicePi / triangleAmount)),
					y11 + (15 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x12 = 647;
		int y12 = 440;
		glVertex2f(x12, y12); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x12 + (15 * cos(i *  twicePi / triangleAmount)),
					y12 + (15 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x13 = 607;
		int y13 = 438;
		glVertex2f(x13, y13); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x13 + (7 * cos(i *  twicePi / triangleAmount)),
					y13 + (7 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x14 = 647;
		int y14 = 438;
		glVertex2f(x14, y14); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x14 + (7 * cos(i *  twicePi / triangleAmount)),
					y14 + (7 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		//gold
		glColor3f(0.94,0.89,0.22);
			glBegin(GL_POLYGON);
			glVertex3f(435.0, 405.0, 0.0);
			glColor3f(1.0,1.0,1.0);
			glVertex3f(515.0, 405.0, 0.0);
			glColor3f(0.94,0.89,0.22);
			glVertex3f(505.0, 465.0, 0.0);
			glColor3f(1.0,1.0,1.0);
			glVertex3f(445.0, 465.0, 0.0);
			glEnd();
}

void grid()
{
	glPushMatrix();
	//glScaled(40.0,40.0,0.0);
	glClearColor(0,0.5,0.5,1.0); //grid background
	glLineWidth(2.5);
	glColor3f(0.0,0.0,0.0); //lines color
	glBegin(GL_LINES);
		glVertex2f(400, 50);
		glVertex2f(1000, 50);
		glVertex2f(400,50);
		glVertex2f(400,650);

		glVertex2f(400, 650);
		glVertex2f(1000, 650);
		glVertex2f(1000,650);
		glVertex2f(1000,50);

		glVertex2f(400, 200);
		glVertex2f(1000, 200);
		glVertex2f(400,350);
		glVertex2f(1000,350);

		glVertex2f(400, 500);
		glVertex2f(1000, 500);
		glVertex2f(550,50);
		glVertex2f(550,650);

		glVertex2f(700, 50);
		glVertex2f(700, 650);
		glVertex2f(850,50);
		glVertex2f(850,650);
	glEnd();
	glPopMatrix();
}

void setFont(void *font)
{
	currentfont=font;
}

void drawstring(float x,float y,float z,char *string)
{
	char *c;
	glRasterPos3f(x,y,z);
	for(c=string;*c!='\0';c++)
	{	glColor3f(0.0,0.0,0.0);
		glutBitmapCharacter(currentfont,*c);
	}
}

void frontscreen(void) 
{
	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	//glClearColor(1.0,1.0,1.0,1.0); //doesnt matter
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON); //1346, 728
		glColor3f(1.0,0.0,0.0);
		glVertex3f(0.0,0.0,0.0);
		glColor3f(0.0,1.0,0.0);
		glVertex3f(0.0,728.0,0.0);
		glColor3f(0.0,0.0,1.0);
		glVertex3f(1346.0,728.0,0.0);
		glColor3f(1.0,1.0,0.0);
		glVertex3f(1346.0,0.0,0.0);
	glEnd();
	//text and the text color
	//glColor3f(1,0,0);
	glColor3f(1,1,1);
	drawstring(450.0,650.0,0.0," PES INSTITUTE OF TECHNOLOGY ");
	//glColor3f(0.7,0,1);
	glColor3f(1,1,1);
	drawstring(330,600,0.0,"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
	//glColor3f(1,0.5,0); //background for grid
	glColor3f(1,1,1);
	drawstring(530,500,0.0,"A MINI PROJECT ON");
	//glColor3f(1,0,0);
	glColor3f(1,1,1);
	drawstring(360,450,0.0,"WUMPUS WORLD PROBLEM - AN AI ALGORITHM");
	//glColor3f(1,0.5,0);
	glColor3f(1,1,1);
	drawstring(650,300,0.0,"BY:");
	glColor3f(1,1,1);
	drawstring(450,250,0.0,"ANISHA KHETAN      1PE16CS022");
	glColor3f(1,1,1);
	drawstring(450,200,0.0,"ASHWINI KELKAR      1PE16CS034");
	//glColor3f(1,0.5,0);
	//glColor3f(1,1,1);
	//drawstring(930,360,0.0,"GUIDES:");
	//glColor3f(1,1,1);
	//drawstring(930,300,0.0,"Name");
	//glColor3f(1,1,1);
	//drawstring(930,240,0.0,"Name");
	//glColor3f(1,0.1,1);
	//glColor3f(1,1,1);
	//drawstring(543,100,0.0,"PRESS ENTER TO START");
	glFlush();
}

void helpscreen()
{
	/* The Wumpus World problem deals with an AI robot navigating its way through a 4x4 puzzle to try and find gold. The robot must safely navigate its way around the evil Wumpus creatures to locate the gold on the board.
    An agent is placed at a location in the grid which is its starting point and is given a destination point ie gold. The actions available to the agent consist of moving in one of four directions.
	In order to perform q-learning for this task, a description of the states, actions, and rewards is needed. A qmatrix is updated every time the agent "learns" using the Belford's Formula.
	After training, the agent is able to find the gold while avoiding the hazards of the Wumpus World.


	1> The environment is a grid of dimensions, here 4 x 4 squares.
	2> A robot/agent is placed at a location in the grid which is its starting point.
	3> The robot/agent is given a destination point. here, gold
	4> The robot has a fixed set of actions i.e. moving right, moving left etc
	5> The robot/agent is surrounded by walls and can only perceive the world  after coming in contact with it: i.e. bumping into wall etc
	6> There is a rewarding system based on the action taken : for example positive reward reinforcement for correct action taken, negative reward reinforcement for incorrect action taken etc.
	7> The objective is to implent an RL algorithm with which the robot reaches its destination.
	
	*/
	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glClearColor(0,0.5,0.5,1.0);/*background for cover page and grid */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,1,1);
	drawstring(400.0,630.0,0.0,"INTRODUCTION");
	glColor3f(1,1,1);
	drawstring(650.0,630.0,0.0,"TO");
	glColor3f(1,1,1);
	drawstring(750.0,630.0,0.0,"WUMPUS WORLD");
	glColor3f(0.5,0.1,0.2);
	drawstring(100.0,530.0,0.0,"*  The Wumpus World problem deals with an AI robot navigating its way through a 4x4 puzzle to try and find gold.");
	glColor3f(0.5,0.1,0.3);
	drawstring(100.0,460.0,0.0,"*  The robot must safely navigate its way around the 'evil' Wumpus creatures to locate the gold on the board.");
	glColor3f(0.5,0.1,0.4);
	drawstring(100.0,390.0,0.0,"*  An agent is placed at a location in the grid which is its starting point and is given a destination point ie gold.");
	glColor3f(0.4,0.1,0.5);
	drawstring(100.0,320.0,0.0,"*  The actions available to the agent consist of moving in one of four directions.");
	glColor3f(0.5,0.1,0.6);
	//drawstring(100.0,240.0,0.0,"*****                                           *****");
	glColor3f(0.5,0.1,0.7);
	drawstring(100.0,250.0,0.0,"*  In order to perform Q-learning for this task, a description of the states, actions, and rewards is needed.");
	glColor3f(0.5,0.1,0.8);
	drawstring(100.0,180.0,0.0, "*  A Q-matrix is updated every time the agent 'learns' using the Belford's Formula. ");
	glColor3f(0.5,0.1,0.9);
	drawstring(100.0,110.0,0.0,"*  After training, the agent is able to find the gold while avoiding the hazards of the Wumpus World.");
	glFlush();
}

void menu(int id)
{
	glClear(GL_COLOR_BUFFER_BIT);
	switch(id)
	{
		case 1: choice = 1;//learn();
				break;
		case 2: choice = 2;//play
				break;
        case 3: choice = 3;//final grid
                break;
		case 4: exit(0); break;
	}
	glutPostRedisplay();
}

int select_action(int i)
{
    for(j = 0; j< 4; j++ )
	{
		if(q_matrix[i][j] > -10000)
		{	if(q_matrix[i][j] > max)
			{
				max = q_matrix[i][j];
			}
		}
	}
	for(j = 0; j< 4; j++ )
	{
	    if(q_matrix[i][j] == max)
        {
            max = -1;
            return j;
        }
	}
}

bool gameOver(int cur_pos)
{
	if(cur_pos == 8) return true;
	return false;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	if(choice == 3)
    {
        final_page();
    }
	if(choice ==2) //play
	{
		grid();
		wumpus();
		square();
		glFlush();
	}
	else if(choice == 1) //learn
    {
		grid();
		wumpus();
		glFlush();
		while(!gameOver(cur_pos) )
		{
			action = select_action(cur_pos);
			if(action == 0) next_pos = cur_pos - 1;//left		
			if(action == 1) next_pos = cur_pos +1;//right			
			if(action == 2) next_pos = cur_pos +4;//top			
			if(action == 3) next_pos = cur_pos - 4;//bottom		
            action_array[ctrl] = action;
            ctrl++;
			if(next_pos == 4 || next_pos == 6 || next_pos == 9)
			{
				next_pos = 0;
				learning_rate = 0;
				q_matrix[cur_pos][action] = -10000;
				action_array[ctrl] = 10;
				last_death = ctrl;
                ctrl++;
			}
			else learning_rate = 0.5;
			int maxa = -1;
			for(int i1 = 0;i1<4;i1++)
            {
                if(q_matrix[next_pos][i1] > maxa)
                {
                    maxa = q_matrix[next_pos][i1];
                    pos = i1;
                }
            }
			q_matrix[cur_pos][action] = q_matrix[cur_pos][action] + learning_rate * ( reward + 1*(q_matrix[next_pos][pos]) - q_matrix[cur_pos][action] );
			cur_pos = next_pos;
		}
		flag = 3; //keep calling finaldraw which calls translate
		z = last_death;
    }
}

void finaldraw()
{
	grid();
	wumpus();
	translate();
}

void myKeyboard( unsigned char key, int x, int y )
{
	switch(key)
	{
		case 13: //Ascii of 'enter' key is 13
			if(flag==1)
			{
				flag=2;
				mydisplay();
			}
			if(flag==0)
			{
				flag=1;
				mydisplay();
			}
			break;
		default:
			break;
	}
}

void mySpecial(int key, int x, int y)
{
	switch(key)
	{
			case GLUT_KEY_RIGHT:
							yr = yr+0;
							if(score > 0)
							{
								if(xr < 450)
								{
									xr = xr+150;
									score = score - 50;
								}
							}
							glutPostRedisplay();
							break;
    	case GLUT_KEY_LEFT:
							yr = yr+0;
							if(score >0)
							{
								if(xr > 0)
									xr = xr-150;
									score = score - 50;
							}
							glutPostRedisplay();
							break;
    	case GLUT_KEY_UP:
							xr = xr+0;
							if(score >0)
							{
								if(yr < 450)
									yr = yr+150;
									score = score - 50;
							}
							glutPostRedisplay();
							break;
    	case GLUT_KEY_DOWN:
							xr = xr+0;
							if(score >0)
							{
								if(yr > 0)
									yr = yr-150;
									score = score -50;
							}
							glutPostRedisplay();
							break;
			default:
							break;
	}

}

void mydisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	if(flag==0)
		frontscreen();
	if(flag==1)
		helpscreen();
	if(flag==2)
		display();
	if(flag==3)
		finaldraw(); //used in learn
	glutSwapBuffers(); //cuz Double Buffer
}

void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,1346.0,0.0,728.0);
}

void idle()
{
	if(flag==3) glutPostRedisplay(); //flag 3 is finaldraw
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1346,728);
	glutInitWindowPosition(0,0);
	glutCreateWindow("WumpusWorld");
	glutCreateMenu(menu);
	glutAddMenuEntry("Learn", 1);
	glutAddMenuEntry("Play", 2);
	glutAddMenuEntry("FinalGrid", 3);
	glutAddMenuEntry("Exit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutIdleFunc(idle);
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecial);
	myinit();
	glutMainLoop();
}
