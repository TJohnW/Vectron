/*
 main.cpp
 article-01-skeleton

 Copyright 2012 Thomas Dalling - http://tomdalling.com/

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

// third-party libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>

// tdogl classes
#include "Program.h"
#include "Helper.h"

// constants
const glm::vec2 SCREEN_SIZE(800, 600);

// globals
tdogl::Program* gProgram = NULL;
GLuint gVAO = 0;
GLuint gVBO = 0;

// returns the full path to the file `fileName` in the same folder as the executable
static std::string ResourcePath(std::string fileName) {
	return GetProcessPath() + "/../" + fileName;
}

// loads the vertex shader and fragment shader, and links them to make the global gProgram
static void LoadShaders() {
    std::vector<tdogl::Shader> shaders;
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("source/vertex-shader.txt"), GL_VERTEX_SHADER));
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("source/fragment-shader.txt"), GL_FRAGMENT_SHADER));
    gProgram = new tdogl::Program(shaders);
}


// loads a triangle into the VAO and VBO globals: gVAO and gVBO
static void LoadTriangle() {
    // make and bind the VAO
    glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);
    
    // make and bind the VBO
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    
    // Put the three triangle verticies into the VBO
    GLfloat vertexData[] = {
        //  X     Y     Z
         0.0f, 0.8f, 0.0f,
        -0.8f,-0.8f, 0.0f,
         0.8f,-0.8f, 0.0f,
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    
    // connect the xyz to the "vert" attribute of the vertex shader
    glEnableVertexAttribArray(gProgram->attrib("vert"));
    glVertexAttribPointer(gProgram->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    // unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


// draws a single frame
static void Render(GLFWwindow *window) {
    // clear everything
    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // bind the program (the shaders)
    glUseProgram(gProgram->object());
        
    // bind the VAO (the triangle)
    glBindVertexArray(gVAO);
    
    // draw the VAO
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    // unbind the VAO
    glBindVertexArray(0);
    
    // unbind the program
    glUseProgram(0);
    
    // swap the display buffers (displays what was just drawn)
    glfwSwapBuffers(window);
    glfwPollEvents();
}


// the program starts here
int main(int argc, char *argv[]) {
    // initialise GLFW
    if(!glfwInit())
        throw std::runtime_error("glfwInit failed");

    // open a window with GLFW
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    

    int pxWidth = 0;
    int pxHeight = 0;

    glfwMakeContextCurrent(window);
    //glfwSetFramebufferSizeCallback(window, _framebuffer);
    //glfwSetWindowSizeCallback(window, Screen::_size);
    glfwGetFramebufferSize( window, &pxWidth, &pxHeight );
    glViewport( 0, 0, pxWidth, pxHeight );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( -SCREEN_SIZE.x / 2, SCREEN_SIZE.x / 2, 
        -SCREEN_SIZE.y / 2, SCREEN_SIZE.y / 2, 0, 1 );

    glewInit();

    std::cout << glGetString( GL_VERSION ) << std::endl;

    // initialise GLEW
    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");
    
    // make sure OpenGL version 3.2 API is available
    if(!GLEW_VERSION_3_2)
        throw std::runtime_error("OpenGL 3.2 API is not available.");

    std::cout << "Try to load shaders loaded" << std::endl;
    // load vertex and fragment shaders into opengl
    LoadShaders();
    std::cout << "shaders loaded" << std::endl;
    
    // create buffer and fill it with the points of the triangle
    LoadTriangle();

    std::cout << "Triangle loaded" << std::endl;
    
    // run while the window is open
    while(!glfwWindowShouldClose( window )){
        // draw one frame
        Render(window);

    }
    
    // clean up and exit
    glfwTerminate();
    return EXIT_SUCCESS;
}
