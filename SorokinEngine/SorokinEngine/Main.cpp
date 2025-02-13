#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

//My class includes
#include "Rendering/Window.h"
#include <iostream>
#include "Shaders/Shader.h"
#include "Models/TexturedModel.h"


int main()
{
    //Window must be loaded before gladLoadGLLoader is called!
    Window window(1080, 720, "SirrockinEngine");
    window.create();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float verticesArr[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };

    std::vector<float> vertices(std::begin(verticesArr), std::end(verticesArr));
    //std::vector<int> indices(std::begin(indicesArr), std::end(indicesArr));

    Loader loader;
    loader.createAttributes(vertices);

    TexturedModel model1("Textures/container.jpg", vertices);
    TexturedModel model2("Textures/awesomeFace.png", vertices, true);

    /* ============================ LOAD the SHADERS here (to be loaded in their own class) ==================================== */
    Shader* exampleShader = new Shader("Shaders/Vertex/cube.vert", "Shaders/Fragment/cube.frag");
    exampleShader->compileShaders();
    GLuint shaderProgramExampleID = exampleShader->createProgram();

    model1.init();
    unsigned int textureID1 = model1.getTextureID();

    model2.init();
    unsigned int textureID2 = model2.getTextureID();

    unsigned int VAO = loader.getVAO(0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glUseProgram(shaderProgramExampleID);
    exampleShader->setInt("ourTexture1", 0);
    exampleShader->setInt("ourTexture2", 1);

    glm::vec3 cameraPos = glm::vec3(0.f, 0.f, -3.f);
    glm::vec3 cameraFront = glm::vec3(0.f, 0.f, 1.f);
    glm::vec3 cameraUp = glm::vec3(0.f, 1.f, 0.f);
    /* ========================== Renderer (OWN CLASS) ============================== */
    while (!window.closed())
    {
        window.clear();

        glm::mat4 view = glm::mat4(1.0);

        cameraFront.x = sin(glm::radians(window.deltaYaw)) * cos(glm::radians(window.deltaPitch));
        cameraFront.y = sin(glm::radians(window.deltaPitch));
        cameraFront.z = cos(glm::radians(window.deltaYaw)) * cos(glm::radians(window.deltaPitch));

        glm::vec3 FPSFront = glm::vec3(cameraFront.x, 0.f, cameraFront.z);
        cameraPos += window.deltaZ * FPSFront;
        //FPSFront camera for FPS style, use cameraFront to use flying style camera
        cameraPos += window.deltaX * glm::normalize(glm::cross(cameraFront, cameraUp));

        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        glm::mat4 proj = glm::perspective(glm::radians(Window::FOV),
                                          (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);


        /*============================= RENDERING ======================================== */


        // draw first triangle using the data from the first VAO

        exampleShader->setFloat("blendValue", window.getUpdatingOpacityChange());
        exampleShader->setMatrix4f("view", view);
        exampleShader->setMatrix4f("projection", proj);


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureID2);


        glUseProgram(shaderProgramExampleID);

        glBindVertexArray(VAO);

        glm::vec3 cubePositions[] = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(2.0f, 5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f, 3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f, 2.0f, -2.5f),
            glm::vec3(1.5f, 0.2f, -1.5f),
            glm::vec3(-1.3f, 1.0f, -1.5f)
        };

        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            if (i % 3 == 0) // every 3rd iteration (including the first) we set the angle using GLFW's time function.
                angle = glfwGetTime() * 25.0f;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            exampleShader->setMatrix4f("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        /*============================= END RENDERING ======================================== */

        window.update();
    }

    delete(exampleShader);
    loader.deleteAttribute();

    return 0;
}
