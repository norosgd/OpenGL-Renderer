#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

int main(void)
{
    //initialize glfw and set the opengl verison to 3
    //set the opengl profile to the core opengl profile
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //create glfw window and opengl context
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Renderer", NULL, NULL);
    if (window == NULL) 
    {
        std::cout << "Failed to create glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);

    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // 0
         0.5f, -0.5f, 0.0f,  // 1
        -0.5f, -0.5f, 0.0f,  // 2
        -0.5f,  0.5f, 0.0f   // 3
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2 , 3
    };

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    //generate and bind vertex array buffer
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //allocate a vertex buffer object on the gpu memory
    //bind the buffer and send the data to the gpu
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //generate an element buffer object
    //bind the buffer and send indices data to the gpu
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //tell opengl the attribs of the vertex buffer object
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * (sizeof(float)), (void*)0);
    glEnableVertexAttribArray(0);

    //Shaders
    Shader shaderProgram("res/shaders/shader.vs", "res/shaders/shader.fs");

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();

        //uniforms
        float timeValue = glfwGetTime();
        float blueValue = (sin(timeValue) / 2.0f) + 0.5f;
        int uniformLocation = glGetUniformLocation(shaderProgram.m_Id, "Color");
        glUniform4f(uniformLocation, 0.0f, 0.0f, blueValue, 1.0f);

        //bind vertex array and draw elements
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //unbind vertex array
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}