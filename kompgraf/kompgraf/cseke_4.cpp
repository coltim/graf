#include <GL/glut.h>
#include <vector>
#include <bevgrafmath2017.h>

GLsizei winWidth = 800, winHeight = 600;

std::vector<vec2> points, points2, points3, points4, points5;
GLint dragged = -1, keyStates[256];;
vec2 temp;
GLdouble a[4], a2[4], a3[4], a4[4], beta, beta_plus, gamma, beta_plus2, gamma2, beta_plus3, gamma3, beta_plus4, gamma4;
bool elsor = true, masodikr = true, harmadikr = true, negyedikr = true;
bool elso_show = true, masodik_show = true, harmadik_show = true, negyedik_show = true;

void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, winWidth, 0.0f, winHeight, 0.0f, 1.0f);
	glLineWidth(1.0);
	glPointSize(4.0);
	beta = 0.0;
}

void grid() {
	glColor3f(0.8f, 0.8f, 0.8f);
	glBegin(GL_LINES);
	//Y-tengely menten(parhuzamosan vele)
	for (int i = 0; i < 32; i++) {
		glVertex2d(i * 25, 0);
		glVertex2d(i * 25, 600);
	}
	//X-tengely menten
	for (int i = 0; i < 24; i++) {
		glVertex2d(0, i * 25);
		glVertex2d(800, i * 25);
	}
	glEnd();
}

void keyOperations() {
	if (keyStates['q'])
		elso_show = true;
	if (keyStates['w'])
		masodik_show = true;
	if (keyStates['e'])
		harmadik_show = true;
	if (keyStates['r'])
		negyedik_show = true;
	if (keyStates['a'])
		elso_show = false;
	if (keyStates['s'])
		masodik_show = false;
	if (keyStates['d'])
		harmadik_show = false;
	if (keyStates['f'])
		negyedik_show = false;
	if (keyStates['+']) {
		beta += 0.001;
		//elsor = true;
		//masodikr = true;
		//harmadikr = true;
		//negyedikr = true;
	}
	if (keyStates['-']) {
		beta -= 0.001;
		if (beta < -2.0) 
			beta = -2.0;
		//elsor = true;
		//masodikr = true;
		//harmadikr = true;
		//negyedikr = true;
	}
	glutPostRedisplay();
}

void finomitas1() {
	beta_plus = sqrt(2.0 + beta);
	gamma = -1.0 / (3.0 * (1.0 - (beta_plus * beta_plus))*(1.0 + beta_plus));

	a[0] = (1.0 / 60.0)*(-90.0 * gamma - 1.0);
	a[1] = (1.0 / 60.0)*(90.0 * gamma + 43.0);
	a[2] = (1.0 / 60.0)*(90.0 * gamma + 17.0);
	a[3] = (1.0 / 60.0)*(-90.0 * gamma + 1.0);
}

void finomitas2() {
	beta_plus2 = sqrt(2.0 + beta_plus);
	gamma2 = -1.0 / (3.0 * (1.0 - (beta_plus2 * beta_plus2))*(1.0 + beta_plus2));

	a2[0] = (1.0 / 60.0)*(-90.0 * gamma2 - 1.0);
	a2[1] = (1.0 / 60.0)*(90.0 * gamma2 + 43.0);
	a2[2] = (1.0 / 60.0)*(90.0 * gamma2 + 17.0);
	a2[3] = (1.0 / 60.0)*(-90.0 * gamma2 + 1.0);
}

void finomitas3() {
	beta_plus3 = sqrt(2.0 + beta_plus2);
	gamma3 = -1.0 / (3.0 * (1.0 - (beta_plus3 * beta_plus3))*(1.0 + beta_plus3));

	a3[0] = (1.0 / 60.0)*(-90.0 * gamma3 - 1.0);
	a3[1] = (1.0 / 60.0)*(90.0 * gamma3 + 43.0);
	a3[2] = (1.0 / 60.0)*(90.0 * gamma3 + 17.0);
	a3[3] = (1.0 / 60.0)*(-90.0 * gamma3 + 1.0);
}

void finomitas4() {
	beta_plus4 = sqrt(2.0 + beta_plus3);
	gamma4 = -1.0 / (3.0 * (1.0 - (beta_plus4 * beta_plus4))*(1.0 + beta_plus4));

	a4[0] = (1.0 / 60.0)*(-90.0 * gamma4 - 1.0);
	a4[1] = (1.0 / 60.0)*(90.0 * gamma4 + 43.0);
	a4[2] = (1.0 / 60.0)*(90.0 * gamma4 + 17.0);
	a4[3] = (1.0 / 60.0)*(-90.0 * gamma4 + 1.0);
}

void elso_iteracio() {

	finomitas1();

	points2.clear();
	int n = points.size();
	for (int i = 1; i < n + 1; i++) {
		points2.push_back(points[i%n]);
		temp = a[0] * points[(i - 1) % n] + a[1] * points[i % n] + a[2] * points[(i + 1) % n] + a[3] * points[(i + 2) % n];
		points2.push_back(temp);
		temp = a[3] * points[(i - 1) % n] + a[2] * points[i % n] + a[1] * points[(i + 1) % n] + a[0] * points[(i + 2) % n];
		points2.push_back(temp);
	}
}

void masodik_iteracio() {

	finomitas2();

	points3.clear();
	int n2 = points2.size();
	for (int i = 1; i < n2 + 1; i++) {
		points3.push_back(points2[i%n2]);
		temp = a2[0] * points2[(i - 1) % n2] + a2[1] * points2[i % n2] + a2[2] * points2[(i + 1) % n2] + a2[3] * points2[(i + 2) % n2];
		points3.push_back(temp);
		temp = a2[3] * points2[(i - 1) % n2] + a2[2] * points2[i % n2] + a2[1] * points2[(i + 1) % n2] + a2[0] * points2[(i + 2) % n2];
		points3.push_back(temp);
	}
}

void harmadik_iteracio() {
	finomitas3();
	points4.clear();
	int n3 = points3.size();
	for (int i = 1; i < n3 + 1; i++) {
		points4.push_back(points3[i%n3]);
		temp = a3[0] * points3[(i - 1) % n3] + a3[1] * points3[i % n3] + a3[2] * points3[(i + 1) % n3] + a3[3] * points3[(i + 2) % n3];
		points4.push_back(temp);
		temp = a3[3] * points3[(i - 1) % n3] + a3[2] * points3[i % n3] + a3[1] * points3[(i + 1) % n3] + a3[0] * points3[(i + 2) % n3];
		points4.push_back(temp);
	}
}

void negyedik_itaracio() {

	/*harmadik_iteracio();
	if (negyedikr) {
		finomitas4();
		negyedikr = false;
	}*/
	finomitas4();
	points5.clear();
	int n4 = points4.size();
	for (int i = 1; i < n4 + 1; i++) {
		points5.push_back(points4[i%n4]);
		temp = a4[0] * points4[(i - 1) % n4] + a4[1] * points4[i % n4] + a4[2] * points4[(i + 1) % n4] + a4[3] * points4[(i + 2) % n4];
		points5.push_back(temp);
		temp = a4[3] * points4[(i - 1) % n4] + a4[2] * points4[i % n4] + a4[1] * points4[(i + 1) % n4] + a4[0] * points4[(i + 2) % n4];
		points5.push_back(temp);
	}
}

void draw() {

	keyOperations();

	int n = points.size();

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < n; i++) {
		glVertex2f(points[i].x, points[i].y);
	}
	glEnd();

	if (n > 3) {
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		for (int i = 0; i < n; i++) {
			glVertex2f(points[i].x, points[i].y);
			glVertex2f(points[(i + 1) % n].x, points[(i + 1) % n].y);
		}
		glEnd();

		elso_iteracio();
		int n2 = points2.size();
		if (elso_show) {
			glColor3f(0.0f, 0.0f, 1.0f);
			glBegin(GL_LINES);
			for (int i = 0; i < n2; i++) {
				glVertex2f(points2[i].x, points2[i].y);
				glVertex2f(points2[(i + 1) % n2].x, points2[(i + 1) % n2].y);
			}
			glEnd();
		}
		masodik_iteracio();
		int n3 = points3.size();
		if (masodik_show) {
			glColor3f(0.0f, 0.7f, 0.7f);
			glBegin(GL_LINES);
			for (int i = 0; i < n3; i++) {
				glVertex2f(points3[i].x, points3[i].y);
				glVertex2f(points3[(i + 1) % n3].x, points3[(i + 1) % n3].y);
			}
			glEnd();
		}

		harmadik_iteracio();
		int n4 = points4.size();
		if (harmadik_show) {
			glColor3f(0.7f, 0.2f, 0.7f);
			glBegin(GL_LINES);
			for (int i = 0; i < n4; i++) {
				glVertex2f(points4[i].x, points4[i].y);
				glVertex2f(points4[(i + 1) % n4].x, points4[(i + 1) % n4].y);
			}
			glEnd();
		}
		
		negyedik_itaracio();
		int n5 = points5.size();
		if (negyedik_show) {
			glColor3f(0.7f, 0.2f, 0.0f);
			glBegin(GL_LINES);
			for (int i = 0; i < n5; i++) {
				glVertex2f(points5[i].x, points5[i].y);
				glVertex2f(points5[(i + 1) % n5].x, points5[(i + 1) % n5].y);
			}
			glEnd();
		}
	}
	glFlush();
	glutSwapBuffers();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	grid();
	draw();
}

void keyPressed(unsigned char key, int x, int y) {
	keyStates[key] = 1;
}

void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = 0;
}

GLint getActivePoint1(GLint sens, GLint x, GLint y) {
	GLint i, s = sens * sens;
	vec2 P = { (float)x, (float)y };

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
		points.clear();

		/*for (int i = 0; i < points.size(); i++)
		{
			if (dist(points[i], vec2(xMouse, winHeight - yMouse)) < 10)
			{
				points.erase(points.begin() + i);
			}
		}*/
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
	glutCreateWindow("subdivision");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseActiveMotion);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutMainLoop();
	return 0;
}