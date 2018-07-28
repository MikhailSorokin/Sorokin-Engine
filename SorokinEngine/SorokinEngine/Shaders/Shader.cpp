#include "Shader.h"



Shader::Shader(const char* vertexSrcPath, const char* destSrcPath)
{
	m_vertexShaderSource = filetobuf(vertexSrcPath);
	m_fragmentShaderSource = filetobuf(destSrcPath);
}


/* A simple function that will read a file into an allocated char pointer buffer */
char* Shader::filetobuf(const char *file)
{
	FILE *fptr;
	long length;
	char *buf;

	fptr = fopen(file, "rb"); /* Open file for reading */
	if (!fptr) /* Return NULL on failure */
		return NULL;
	fseek(fptr, 0, SEEK_END); /* Seek to the end of the file */
	length = ftell(fptr); /* Find out how many bytes into the file we are */
	buf = (char*)malloc(length + 1); /* Allocate a buffer for the entire length of the file and a null terminator */
	fseek(fptr, 0, SEEK_SET); /* Go back to the beginning of the file */
	fread(buf, length, 1, fptr); /* Read the contents of the file in to the buffer */
	fclose(fptr); /* Close the file */
	buf[length] = 0; /* Null terminator */

	return buf; /* Return the buffer */
}

Shader::~Shader()
{
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
}


/* These are handles used to reference the shaders */
void Shader::compileShaders()
{

	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);

	/* Send the vertex shader source code to GL */
	/* Note that the source code is NULL character terminated. */
	/* GL will automatically detect that therefore the length info can be 0 in this case (the last parameter) */
	glShaderSource(m_vertexShader, 1, (const GLchar**)&m_vertexShaderSource, 0);
	glCompileShader(m_vertexShader);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragmentShader, 1, (const GLchar**)&m_fragmentShaderSource, 0);
	glCompileShader(m_fragmentShader);
	glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	glShaderSource(m_fragmentShader, 1, &m_fragmentShaderSource, NULL);
	glCompileShader(m_fragmentShader);

}


/* If we reached this point it means the vertex and fragment shaders compiled and are syntax error free. */
/* We must link them together to make a GL shader program */
/* GL shader programs are monolithic. It is a single piece made of 1 vertex shader and 1 fragment shader. */
/* Assign our program handle a "name" */
GLuint Shader::createProgram()
{
	GLuint shaderprogram = glCreateProgram();

	/* Attach our shaders to our program */
	glAttachShader(shaderprogram, m_vertexShader);
	glAttachShader(shaderprogram, m_fragmentShader);

	/* Bind attribute index 0 (coordinates) to in_Position and attribute index 1 (color) to in_Color */
	/* Attribute locations must be setup before calling glLinkProgram. */
	glBindAttribLocation(shaderprogram, 0, "in_Position");

	/* Link our program */
	/* At this stage, the vertex and fragment programs are inspected, optimized and a binary code is generated for the shader. */
	/* The binary code is uploaded to the GPU, if there is no error. */
	glLinkProgram(shaderprogram);
	/* Load the shader into the rendering pipeline */

	return shaderprogram;
}