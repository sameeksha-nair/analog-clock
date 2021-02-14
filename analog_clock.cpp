
//Header files
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <time.h>
#include <sys/timeb.h>
#include <string.h>

//Constants and global variables 
#define PI 3.14159
double second_angle = 0, minute_angle = 0, hour_angle = 0;


//Function to draw a line
void drawLine(GLfloat x, GLfloat y, GLfloat angle) {
	glVertex2f(x, x);
	glVertex2f(y * cos(angle), y * sin(angle));
}

//Function to display the face of the clock (the hours)
void face() {

	GLfloat x1, y1, angle_clock, x2, y2;
	glBegin(GL_LINES);
	int i = 0;
	for (angle_clock = 0.0f; angle_clock <= (2.0f * 3.14); angle_clock += 0.10478f)
	{

		x1 = 50.0f * sin(angle_clock);
		y1 = 50.0f * cos(angle_clock);
		if (i % 5 == 0) {
			glColor3f(1, 0, 0);
			x2 = 40.0f * sin(angle_clock);
			y2 = 40.0f * cos(angle_clock);
		}
		else {
			glColor3f(0, 0, 1);
			x2 = 45.0f * sin(angle_clock);
			y2 = 45.0f * cos(angle_clock);
		}

		glVertex3f(x1, y1, 0.0f);
		glVertex3f(x2, y2, 0);
		i++;
	}
	glEnd();

}

//Function to display the circular shape of the clock
void display_clock(void) {

	GLfloat x, y, angle;	
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(1.5);
	glBegin(GL_POINTS);
	for (angle = 0.0f; angle <= (2.0f * 3.14); angle += 0.01f)
	{
		x = 50.0f * sin(angle);
		y = 50.0f * cos(angle);
		glVertex3f(x, y, 0.0f);
	}
	glClear(GL_COLOR_BUFFER_BIT);
	angle = 0.0f;
	glEnd();
	face();

}

//Function to display the hands of the clock
void hands(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(2.0);
	display_clock();

	glColor3f(1.0f, 0.5f, 0.0f);
	glBegin(GL_LINES);
	drawLine(0.0, 35.0, -second_angle + PI / 2);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	drawLine(0.0, 40.0, -minute_angle + PI / 2);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	drawLine(0.0, 25.0, -hour_angle + PI / 2);
	glEnd();	
	glFlush();
	glutSwapBuffers();
}

//Function to change time steadily every 15 ms
void time_change(int i) {
	struct timeb tb;
	time_t tim = time(0);
	struct tm* local_time;
	local_time = localtime(&tim);
	ftime(&tb);

	second_angle = (double)(local_time->tm_sec + (double)tb.millitm / 1000.0) / 30.0 * PI;
	minute_angle = (double)(local_time->tm_min) / 30.0 * PI + second_angle / 60.0;
	hour_angle = (double)(local_time->tm_hour > 12 ? local_time->tm_hour - 12 : local_time->tm_hour) / 6.0 * PI + minute_angle / 12.0;

	glutPostRedisplay();
	glutTimerFunc(15, time_change, 1);
}


//Main function
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 640);
	glutCreateWindow("Analog Clock");
	gluOrtho2D(-100, 100, -100, 100);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glutDisplayFunc(hands);
	glutTimerFunc(15, time_change, 1);
	glutMainLoop();
	return 0;
}