#include "OpenGL.h"

GLenum g_OpenGLError = GL_NO_ERROR;

#define OPENGL_INT_PRINT_DEBUG(name) \
	GLint info_ ## name; \
	glGetIntegerv(name, &info_ ## name); \
	LOG_DEBUG(#name " = %d\n", info_ ## name);

void OpenGLPrintDebugInfo()
{
	// выведем в лог немного информации о контексте OpenGL
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	LOG_DEBUG("OpenGL render context information:\n"
		"  Renderer       : %s\n"
		"  Vendor         : %s\n"
		"  Version        : %s\n"
		"  GLSL version   : %s\n"
		"  OpenGL version : %d.%d\n",
		(const char*)glGetString(GL_RENDERER),
		(const char*)glGetString(GL_VENDOR),
		(const char*)glGetString(GL_VERSION),
		(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION),
		major, minor
	);

	// значения различных параметров OpenGL
	OPENGL_INT_PRINT_DEBUG(GL_MAX_VERTEX_ATTRIBS);
	OPENGL_INT_PRINT_DEBUG(GL_MAX_TEXTURE_IMAGE_UNITS);
	OPENGL_INT_PRINT_DEBUG(GL_MAX_UNIFORM_BUFFER_BINDINGS);
	OPENGL_INT_PRINT_DEBUG(GL_MAX_VERTEX_UNIFORM_BLOCKS);
	OPENGL_INT_PRINT_DEBUG(GL_MAX_UNIFORM_BLOCK_SIZE);

	OPENGL_CHECK_FOR_ERRORS();
}

bool OpenGLInitExtensions()
{
	// Texture
	OPENGL_GET_PROC(PFNGLACTIVETEXTUREPROC, glActiveTexture);
	// VAO
	OPENGL_GET_PROC(PFNGLGENVERTEXARRAYSPROC,    glGenVertexArrays);
	OPENGL_GET_PROC(PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays);
	OPENGL_GET_PROC(PFNGLBINDVERTEXARRAYPROC,    glBindVertexArray);
	// VBO
	OPENGL_GET_PROC(PFNGLGENBUFFERSPROC,    glGenBuffers);
	OPENGL_GET_PROC(PFNGLDELETEBUFFERSPROC, glDeleteBuffers);
	OPENGL_GET_PROC(PFNGLBINDBUFFERPROC,    glBindBuffer);
	OPENGL_GET_PROC(PFNGLBUFFERDATAPROC,    glBufferData);
	OPENGL_GET_PROC(PFNGLBUFFERSUBDATAPROC, glBufferSubData);
	OPENGL_GET_PROC(PFNGLMAPBUFFERPROC,     glMapBuffer);
	OPENGL_GET_PROC(PFNGLUNMAPBUFFERPROC,   glUnmapBuffer);
	// Shaders
	OPENGL_GET_PROC(PFNGLCREATEPROGRAMPROC,     glCreateProgram);
	OPENGL_GET_PROC(PFNGLDELETEPROGRAMPROC,     glDeleteProgram);
	OPENGL_GET_PROC(PFNGLLINKPROGRAMPROC,       glLinkProgram);
	OPENGL_GET_PROC(PFNGLVALIDATEPROGRAMPROC,   glValidateProgram);
	OPENGL_GET_PROC(PFNGLUSEPROGRAMPROC,        glUseProgram);
	OPENGL_GET_PROC(PFNGLGETPROGRAMIVPROC,      glGetProgramiv);
	OPENGL_GET_PROC(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog);
	OPENGL_GET_PROC(PFNGLCREATESHADERPROC,      glCreateShader);
	OPENGL_GET_PROC(PFNGLDELETESHADERPROC,      glDeleteShader);
	OPENGL_GET_PROC(PFNGLSHADERSOURCEPROC,      glShaderSource);
	OPENGL_GET_PROC(PFNGLCOMPILESHADERPROC,     glCompileShader);
	OPENGL_GET_PROC(PFNGLATTACHSHADERPROC,      glAttachShader);
	OPENGL_GET_PROC(PFNGLDETACHSHADERPROC,      glDetachShader);
	OPENGL_GET_PROC(PFNGLGETSHADERIVPROC,       glGetShaderiv);
	OPENGL_GET_PROC(PFNGLGETSHADERINFOLOGPROC,  glGetShaderInfoLog);
	// Shaders attributes
	OPENGL_GET_PROC(PFNGLGETATTRIBLOCATIONPROC,        glGetAttribLocation);
	OPENGL_GET_PROC(PFNGLVERTEXATTRIBPOINTERPROC,      glVertexAttribPointer);
	OPENGL_GET_PROC(PFNGLENABLEVERTEXATTRIBARRAYPROC,  glEnableVertexAttribArray);
	OPENGL_GET_PROC(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray);
	OPENGL_GET_PROC(PFNGLVERTEXATTRIBDIVISORPROC,      glVertexAttribDivisor);
	// Uniforms
	OPENGL_GET_PROC(PFNGLGETUNIFORMLOCATIONPROC,        glGetUniformLocation);
	OPENGL_GET_PROC(PFNGLUNIFORMMATRIX3FVPROC,          glUniformMatrix3fv);
	OPENGL_GET_PROC(PFNGLUNIFORMMATRIX4FVPROC,          glUniformMatrix4fv);
	OPENGL_GET_PROC(PFNGLUNIFORM1IPROC,                 glUniform1i);
	OPENGL_GET_PROC(PFNGLGETACTIVEUNIFORMSIVPROC,       glGetActiveUniformsiv);
	OPENGL_GET_PROC(PFNGLGETACTIVEUNIFORMNAMEPROC,      glGetActiveUniformName);
	OPENGL_GET_PROC(PFNGLGETUNIFORMINDICESPROC,         glGetUniformIndices);
	OPENGL_GET_PROC(PFNGLGETUNIFORMBLOCKINDEXPROC,      glGetUniformBlockIndex);
	OPENGL_GET_PROC(PFNGLUNIFORMBLOCKBINDINGPROC,       glUniformBlockBinding);
	OPENGL_GET_PROC(PFNGLBINDBUFFERRANGEPROC,           glBindBufferRange);
	OPENGL_GET_PROC(PFNGLBINDBUFFERBASEPROC,            glBindBufferBase);
	OPENGL_GET_PROC(PFNGLGETACTIVEUNIFORMBLOCKIVPROC,   glGetActiveUniformBlockiv);
	OPENGL_GET_PROC(PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC, glGetActiveUniformBlockName);
	// Instancing
	OPENGL_GET_PROC(PFNGLDRAWARRAYSINSTANCEDPROC,   glDrawArraysInstanced);
	OPENGL_GET_PROC(PFNGLDRAWELEMENTSINSTANCEDPROC, glDrawElementsInstanced);

	OPENGL_CHECK_FOR_ERRORS();

	return true;
}

// объявим расширения OpenGL
// Texture
PFNGLACTIVETEXTUREPROC glActiveTexture = NULL;
// VAO
PFNGLGENVERTEXARRAYSPROC    glGenVertexArrays    = NULL;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = NULL;
PFNGLBINDVERTEXARRAYPROC    glBindVertexArray    = NULL;
// VBO
PFNGLGENBUFFERSPROC    glGenBuffers    = NULL;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;
PFNGLBINDBUFFERPROC    glBindBuffer    = NULL;
PFNGLBUFFERDATAPROC    glBufferData    = NULL;
PFNGLBUFFERSUBDATAPROC glBufferSubData = NULL;
PFNGLMAPBUFFERPROC     glMapBuffer     = NULL;
PFNGLUNMAPBUFFERPROC   glUnmapBuffer   = NULL;
// Shaders
PFNGLCREATEPROGRAMPROC     glCreateProgram     = NULL;
PFNGLDELETEPROGRAMPROC     glDeleteProgram     = NULL;
PFNGLLINKPROGRAMPROC       glLinkProgram       = NULL;
PFNGLVALIDATEPROGRAMPROC   glValidateProgram   = NULL;
PFNGLUSEPROGRAMPROC        glUseProgram        = NULL;
PFNGLGETPROGRAMIVPROC      glGetProgramiv      = NULL;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
PFNGLCREATESHADERPROC      glCreateShader      = NULL;
PFNGLDELETESHADERPROC      glDeleteShader      = NULL;
PFNGLSHADERSOURCEPROC      glShaderSource      = NULL;
PFNGLCOMPILESHADERPROC     glCompileShader     = NULL;
PFNGLATTACHSHADERPROC      glAttachShader      = NULL;
PFNGLDETACHSHADERPROC      glDetachShader      = NULL;
PFNGLGETSHADERIVPROC       glGetShaderiv       = NULL;
PFNGLGETSHADERINFOLOGPROC  glGetShaderInfoLog  = NULL;
// Shaders attributes
PFNGLGETATTRIBLOCATIONPROC        glGetAttribLocation        = NULL;
PFNGLVERTEXATTRIBPOINTERPROC      glVertexAttribPointer      = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC  glEnableVertexAttribArray  = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = NULL;
PFNGLVERTEXATTRIBDIVISORPROC      glVertexAttribDivisor      = NULL;
// Uniforms
PFNGLGETUNIFORMLOCATIONPROC        glGetUniformLocation        = NULL;
PFNGLUNIFORMMATRIX3FVPROC          glUniformMatrix3fv          = NULL;
PFNGLUNIFORMMATRIX4FVPROC          glUniformMatrix4fv          = NULL;
PFNGLUNIFORM1IPROC                 glUniform1i                 = NULL;
PFNGLGETACTIVEUNIFORMSIVPROC       glGetActiveUniformsiv       = NULL;
PFNGLGETACTIVEUNIFORMNAMEPROC      glGetActiveUniformName      = NULL;
PFNGLGETUNIFORMINDICESPROC         glGetUniformIndices         = NULL;
PFNGLGETUNIFORMBLOCKINDEXPROC      glGetUniformBlockIndex      = NULL;
PFNGLUNIFORMBLOCKBINDINGPROC       glUniformBlockBinding       = NULL;
PFNGLBINDBUFFERRANGEPROC           glBindBufferRange           = NULL;
PFNGLBINDBUFFERBASEPROC            glBindBufferBase            = NULL;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC   glGetActiveUniformBlockiv   = NULL;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glGetActiveUniformBlockName = NULL;
// Instancing
PFNGLDRAWARRAYSINSTANCEDPROC   glDrawArraysInstanced   = NULL;
PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced = NULL;