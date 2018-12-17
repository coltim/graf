#include <GL/glut.h>
#include <vector>
#include <bevgrafmath2017.h>

GLsizei winWidth = 800, winHeight = 600;

std::vector<vec2> points;
GLint dragged = -1;

vec4 T, temp;
mat4 M;
mat24 G, C;

void init()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, winWidth, 0.0f, winHeight, 0.0f, 1.0f);
	glLineWidth(2.0);
	glPointSize(4.0);

	M = {	-1.0,  3.0, -3.0, 1.0, 
			 3.0, -6.0,  0.0, 4.0, 
			-3.0,  3.0,  3.0, 1.0, 
			 1.0,  0.0,  0.0, 0.0};

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			M[i][j] /= 6.0;
}


void display() {
	
	glClear(GL_COLOR_BUFFER_BIT);
	int n = points.size();
	

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < n; i++) {
		glVertex2f(points[i].x, points[i].y);
	}
	glEnd();


	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	for (int i = 0; i < n - 1; i++) {
		glVertex2f(points[i].x, points[i].y);
		glVertex2f(points[i + 1].x, points[i + 1].y);
	}
	glEnd();


	if (n > 3) 
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_LINE_STRIP);
		vec2 p_1 = 2 * points[0] - points[ 1];
		vec2 S = 1 / 6 *( p_1 + 4 * points[0] + points[1]);
		G = { p_1, points[0], points[1] , points[2] };
		C = G * M;
		for (GLfloat t = 0; t <= 1; t += 0.01)
		{

			T = { pow(t,3), pow(t,2), t, 1 };
			vec2 Q = C * T;
			glVertex2d(Q.x, Q.y);
		}
		glEnd();

		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_LINE_STRIP);
		vec2 p_plus = 2 * points[n-1] - points[n-2];
		vec2 E = 1 / 6 * ( points[n -2]  + 4 * points[n-1] + p_plus);
		G = { points[n - 3], points[n - 2], points[n-1], p_plus};
		C = G * M;
		for (GLfloat t = 0; t <= 1; t += 0.01)
		{

			T = { pow(t,3), pow(t,2), t, 1 };
			vec2 Q = C * T;
			glVertex2d(Q.x, Q.y);
		}
		glEnd();

		for (int i = 0; i < n - 3; i++) 
		{
			glColor3f(0.0f, 1.0f, 0.0f);
			glBegin(GL_LINE_STRIP);
			G = { points[i] , points[i + 1], points[i + 2] , points[i + 3] };
			C = G * M;
			for (GLfloat t = 0; t <= 1; t += 0.01)
			{

				T = { pow(t,3), pow(t,2), t, 1 };
				vec2 Q = C * T;
				glVertex2d(Q.x, Q.y);
					
			}
			glEnd();

			glColor3f(0.0f, 0.5f, 0.3f);
			glBegin(GL_POINTS);
			for (GLfloat t = 0; t <= 1; t += 1) 
			{
				T = { pow(t,3), pow(t,2), t, 1 };
				vec2 Q = C * T;
				glVertex2d(Q.x, Q.y);
				
			}
			glEnd();
		}
	}

	glFlush();
	glutSwapBuffers();
}

GLint getActivePoint1( GLint sens, GLint x, GLint y) {
	GLint i, s = sens * sens;
	vec2 P =  { (float)x, (float)y };
	
	for (i = 0; i < points.size(); i++)
		if (dist(points[i], P) < s)
			return i;
	return -1;
}

GLint getActivePoint2(vec2 *p, GLint size, GLint sens, GLint x, GLint y) {
	GLint i;
	for (i = 0; i < size; i++)
		if (fabs((*(p + i)).x - x) < sens && fabs((*(p + i)).y - y) < sens)
			return i;
	return -1;
}

void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	GLint i;
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		if ((i = getActivePoint1(3, xMouse, winHeight - yMouse)) != -1)
			dragged = i;
		else {
			points.push_back(vec2(xMouse, winHeight - yMouse));
		}
	}
		if (button == GLUT_LEFT_BUTTON && action == GLUT_UP)
			dragged = -1;
		if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN) {
			for (int i = 0; i < points.size(); i++)
			{
				if (dist(points[i], vec2(xMouse, winHeight - yMouse)) < 10)
				{
					points.erase(points.begin() + i);
				}
			}
		}
}

void processMouseActiveMotion(GLint xMouse, GLint yMouse) {
	GLint i;
	if (dragged >= 0) {
		points[dragged].x = xMouse;
		points[dragged].y = winHeight - yMouse;
		glutPostRedisplay();
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("B-spline görbe");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseActiveMotion);
	glutMainLoop();
	return 0;
}