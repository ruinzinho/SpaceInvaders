#include <iostream>
#include <sstream>
#include <string>

#include <gl/glew.h>
#include <gl/freeglut.h>

#include "Scene.hpp"
#include "SpaceInvaders.hpp"


#define CAPTION "Space Invaders"
#define FRAMES_PER_SECOND 120


int WindowHandle = 0;
int Width = 640;
int Height = 480;

unsigned int FrameCount = 0;


Scene scene;
SpaceInvaders spaceInvaders;


bool IsOpenGLError(void) {
	bool isError = false;
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		isError = true;
		errString = gluErrorString(errCode);
		std::cerr << "OpenGL ERROR [" << errString << "]." << std::endl;
	}
	return isError;
}


void CheckOpenGLError(const std::string &message) {
	if (IsOpenGLError()) {
		std::cerr << message << std::endl;
		exit(EXIT_FAILURE);
	}
}


void UpdateCaption(int value) {
	if (WindowHandle > 0) {
		std::stringstream ss;
		ss << CAPTION << ": " << FrameCount << " FPS @ (" << Width << "x" << Height << ") ";
		ss << "Lives: " << spaceInvaders.Lives() << " Points: " << spaceInvaders.Points();
		FrameCount = 0;

		std::string &title = ss.str();
		glutSetWindow(WindowHandle);
		glutSetWindowTitle(title.c_str());
		glutTimerFunc(1000, UpdateCaption, 0);
	}
}


void Refresh(int value) {
	static int time = glutGet(GLUT_ELAPSED_TIME);
	int now = glutGet(GLUT_ELAPSED_TIME);
	float dt = (now - time) / 1000.0f;
	time = now;

	if (WindowHandle > 0) {
		spaceInvaders.Update(dt);
		glutPostRedisplay();
		glutTimerFunc(1000 / FRAMES_PER_SECOND, Refresh, 0);
	}
}


void Reshape(int width, int height) {
	Width = width;
	Height = height;

	glViewport(0, 0, width, height);
	scene.Reshape(width, height);
}


void Display(void) {
	FrameCount++;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.Render(spaceInvaders);
	glutSwapBuffers();

	CheckOpenGLError("ERROR: Could not draw scene.");
}


void Close(void) {
	WindowHandle = 0;

	scene.Delete();
}


void KeyPressed(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		scene.FixedOrthogonal();
		break;
	case '2':
		scene.FixedPerspective();
		break;
	case '3':
		scene.FlexiblePerspective();
		break;
	case 'b':
		spaceInvaders.Fire();
		break;
	case 'c':
		scene.TogglePointLights();
		break;
	case 'h':
		scene.ToggleSpotLight();
		break;
	case 'n':
		scene.ToggleDirectionalLight();
		break;
	case 'r':
		spaceInvaders.Restart();
		break;
	case 's':
		if (spaceInvaders.Paused()) {
			spaceInvaders.Resume();
			break;
		}
		spaceInvaders.Pause();
		break;
	case 27:
		glutLeaveMainLoop();
		break;
	}
}


void SpecialKeyPressed(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		spaceInvaders.Move(-1.0f, 0.0f, 0.0f);
		break;
	case GLUT_KEY_RIGHT:
		spaceInvaders.Move(+1.0f, 0.0f, 0.0f);
		break;
	}
}


void SpecialKeyReleased(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		spaceInvaders.Move(+1.0f, 0.0f, 0.0f);
		break;
	case GLUT_KEY_RIGHT:
		spaceInvaders.Move(-1.0f, 0.0f, 0.0f);
		break;
	}
}


void SetupCallbacks(void) {
	glutKeyboardFunc(KeyPressed);
	glutSpecialFunc(SpecialKeyPressed);
	glutSpecialUpFunc(SpecialKeyReleased);
	glutCloseFunc(Close);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);

	glutTimerFunc(0, Refresh, 0);
	glutTimerFunc(0, UpdateCaption, 0);
}


void InitializeProgram(void) {
	scene.Initialize();
}


void InitializeOpenGL(void) {
	std::cout << "CONTEXT: OpenGL v" << glGetString(GL_VERSION) << std::endl;

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0f, 1.0f);
	glClearDepth(1.0f);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glClearStencil(0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_MULTISAMPLE);

	CheckOpenGLError("Error: Could not initialize OpenGL.");
}


void InitializeGLEW(void) {
	glewExperimental = GL_TRUE;

	GLenum result = glewInit();
	if (result != GLEW_OK) {
		std::cerr << "Error: " << glewGetErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}

	GLenum error = glGetError();
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}


void InitializeGLUT(int argc, char *argv[]) {
	glutInit(&argc, argv);

	glutInitContextVersion(3, 3);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutSetOption(GLUT_MULTISAMPLE, 4);

	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

	glutInitWindowSize(Width, Height);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE);
	WindowHandle = glutCreateWindow(CAPTION);

	if (WindowHandle < 1) {
		std::cerr << "Error: Could not create a new rendering window." << std::endl;
		exit(EXIT_FAILURE);
	}
}


int main(int argc, char *argv[]) {
	InitializeGLUT(argc, argv);
	InitializeGLEW();
	InitializeOpenGL();
	InitializeProgram();
	SetupCallbacks();

	glutMainLoop();

	return EXIT_SUCCESS;
}