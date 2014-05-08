#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

using namespace std;

GLuint triangle_vao;
GLint vertexID;
GLint fragID;
GLuint shader;


// This function asks the driver for a vertex array object, which will store information
// about what is being drawn, such as geometry, color information, texture information and so on.
// Hold on to the ID that this function returns, because you can use it later on!
GLuint createVertexArray() {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	return vao;
}

// This function takes in a vertex array object ID and an array of vertices. It should be called 
// immediately after calling createVertexArray.  It returns a buffer ID (which you probably won't
// use).  NOTE: this assumes that you want triangles and not points or lines.
GLuint loadVertexPositions(GLuint shaderProgramID, GLuint vao, GLfloat* vVerts, GLuint numVertices) {
	glBindVertexArray(vao);
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer (GL_ARRAY_BUFFER, buffer);
	
	// Copy the array data into the active buffer (remember, there's a GLuint above that's active)
	glBufferData(GL_ARRAY_BUFFER, numVertices*3*sizeof(GLfloat), vVerts, GL_STATIC_DRAW);
	
	// Figure out where vPosition is in our shader
	GLuint loc = glGetAttribLocation(shaderProgramID, "vPosition");
	// Turn it on
	glEnableVertexAttribArray(loc);
	// Tell it how the data should be parsed
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

	return buffer;
}

// You shouldn't have to call this function (it's called from the functions
// that make shaders); it is a helper function to determine if a shader compiled correctly.
int compiledStatus(GLint shaderID){
	GLint compiled = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
	if (compiled) {
		return true;
	}
	else {
		GLint logLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
		char* msgBuffer = new char[logLength];
		glGetShaderInfoLog(shaderID, logLength, NULL, msgBuffer);
		printf ("%s\n", msgBuffer);
		delete (msgBuffer);
		return false;
	}
}

// This function takes in the source code for a vertex shader,
// compiles it, and returns the ID (number) of the shader. It returns
// -1 if the shader didn't compile
GLint makeVertexShader (char* shaderSource) {
	GLint vShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource (vShaderID, 1, (const GLchar**)&shaderSource, NULL);
	glCompileShader(vShaderID);
	int compiledCorrectly = compiledStatus(vShaderID);
	if (compiledCorrectly) {
		return vShaderID;
	}
	return -1;
}

// This function takes in the source code for a fragment shader,
// compiles it, and returns the ID (number) of the shader. It returns
// -1 if the shader didn't compile
GLuint makeFragmentShader (char* shaderSource) {
	GLint fShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource (fShaderID, 1, (const GLchar**)&shaderSource, NULL);
	glCompileShader(fShaderID);
	int compiledCorrectly = compiledStatus(fShaderID);
	if (compiledCorrectly) {
		return fShaderID;
	}
	return -1;
}

// A helper function that takes in a program ID and returns whether
// or not it linked correctly.  If not, it prints out an error
// message letting you know what the problem was. This will
// be called from makeShaderProgram()
bool linkedStatus(GLint programID){
	GLint linked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &linked);
	if (linked) {
		return true;
	}
	else {
		GLint logLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);
		char* msgBuffer = new char[logLength];
		glGetProgramInfoLog(programID, logLength, NULL, msgBuffer);
		printf ("%s\n", msgBuffer);
		delete (msgBuffer);
		return false;
	}
}

// A function that takes in the IDs for vertex and fragment shader,
// and returns the ID of a shader program that has been linked.
GLint makeShaderProgram (GLint vertexShaderID, GLint fragmentShaderID) {
	printf ("Linking %d with %d\n", vertexShaderID, fragmentShaderID);
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram (programID);

	bool linked = linkedStatus (programID);

	if (linked) {
		return programID;
	}
	return -1;
}

// Any time the window is resized, this function gets called.  It's setup to the 
// "glutReshapeFunc" in main.
void changeViewport(int w, int h){
	glViewport(0, 0, w, h);
}

// Here is the function that gets called each time the window needs to be redrawn.
// It is the "paint" method for our program, and is set up from the glutDisplayFunc in main
void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();
}

int main (int argc, char** argv) {
	// Initialize GLUT
	glutInit(&argc, argv);

	// Set up some memory buffers for our display
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	// Set the window size
	glutInitWindowSize(800, 600);
	// Create the window with the title "Triangle"
	glutCreateWindow("Triangle");
	// Bind the two functions (above) to respond when necessary
	glutReshapeFunc(changeViewport);
	glutDisplayFunc(render);

	// Very important!  This initializes the entry points in the OpenGL driver so we can 
	// call all the functions in the API.
	
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}

	char* vertexProg = "#version 150\n\n\
					   in vec4 vPosition;\n\n\
					   void main () {\n\
					   \tgl_Position = vPosition;\n\
					   }\n";

	char* fragmentProg="#version 150\n\n\
					   out vec4 fColor;\n\n\
					   void main () {\n\
					   \tfColor = vec4 (1.0, 0.0, 0.0, 1.0);\n\
					   }\n";

	float vertices[] = {-0.5f, -0.5f, 0.0f, 
						0.5f, -0.5f, 0.0f,
						0.0f, 0.5f, 0.0f};

	vertexID = makeVertexShader (vertexProg);
	fragID = makeFragmentShader (fragmentProg);
	shader = makeShaderProgram(vertexID, fragID);

	glUseProgram (shader);

	cout << "Vertex ID is " << vertexID << endl;
	cout << "Fragment ID is " << fragID << endl;
	cout << "Shader program ID is " << shader << endl;

	triangle_vao = createVertexArray();
	loadVertexPositions(shader, triangle_vao, vertices, 3);

	// Start up a loop that runs in the background (you never see it).
	glutMainLoop();
	return 0;
}