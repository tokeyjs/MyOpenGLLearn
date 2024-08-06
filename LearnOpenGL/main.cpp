#include<iostream>
#include <glad/glad.h> 
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<Windows.h>
#include"Shader.h"
#include"Camera.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

//extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
float lastFrame = 0.0f; // ��һ֡��ʱ��

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// �����������
Camera cam;

// 0-1  ��������Ļ�ϱ���
float mixVal = 0;

bool firstMouse = true;


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    static float lastX;
    static float lastY;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    cam.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    cam.ProcessMouseScroll(yoffset);
}


int main()
{

    //test();
#pragma region ��ʼ��


    // opengl V3.3   COREģʽ
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

#pragma endregion


#pragma region ����ͼ���������ɻ������



    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };


    // ���ɶ����������Ͷ��㻺�����
    unsigned int objVBO, objVAO;
    glGenVertexArrays(1, &objVAO);
    glGenBuffers(1, &objVBO);
    
    glBindVertexArray(objVAO);
    glBindBuffer(GL_ARRAY_BUFFER, objVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // �Զ�������λ��ֵ��Ϊ���������ö������ԣ�
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);



    // ���ɶ����������Ͷ��㻺�����
    unsigned int lightVBO, lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &lightVBO);

    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // �Զ�������λ��ֵ��Ϊ���������ö������ԣ�
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

#pragma endregion

    // ������ɫ��
    Shader objShader("shader.vs", "shader.fs");
    
    // �ƹ���ɫ��
    Shader lightShader("shader.vs", "lightShader.fs");


    // ��������ƶ��ص�
    glfwSetCursorPosCallback(window, mouse_callback);
    // ���������ֻص�
    glfwSetScrollCallback(window, scroll_callback);


    // ��Ⱦѭ��
    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // ��ȡ����
        processInput(window);

        // ����
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!


        glm::mat4 projection;
        projection = glm::perspective(glm::radians(cam.Zoom), 
            static_cast<float>(SCR_WIDTH)/ static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);
        
        glm::mat4 objModel = glm::mat4(1.0f);
        objModel = glm::translate(objModel, glm::vec3(0.0f, 0.0f, 0.0f));

        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
        lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
        lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, lightPos);
        lightModel = glm::scale(lightModel, glm::vec3(0.2f));



        // ��Դ
        glm::vec3 lightColor;
        //lightColor.x = sin(glfwGetTime() * 2.0f);
        //lightColor.y = sin(glfwGetTime() * 0.7f);
        //lightColor.z = sin(glfwGetTime() * 1.3f);
        lightColor.x = 1.0f;
        lightColor.y = 1.0f;
        lightColor.z = 1.0f;
        objShader.use();
        //glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
        //glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
        glm::vec3 diffuseColor = lightColor * glm::vec3(1.0f);
        glm::vec3 ambientColor = diffuseColor * glm::vec3(1.0f);
        glm::vec3 specularColor = glm::vec3(1.0f);
        objShader.setVec3("light.ambient", ambientColor.x, ambientColor.y, ambientColor.z); //��Դ�� ��������
        objShader.setVec3("light.diffuse", diffuseColor.x, diffuseColor.y, diffuseColor.z);  //��Դ�� ������
        objShader.setVec3("light.specular", specularColor.x, specularColor.y, specularColor.z);  //��Դ�� ���淴��
        objShader.setVec3("light.position", lightPos.x, lightPos.y, lightPos.z);

        objShader.setMat4("model", glm::value_ptr(objModel));
        objShader.setMat4("view", glm::value_ptr(cam.GetViewMatrix()));
        objShader.setMat4("projection", glm::value_ptr(projection));
        // ����
        objShader.setVec3("viewPos", cam.Position.x, cam.Position.y, cam.Position.z);
        //objShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f); // ��������
        //objShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);  // ������
        //objShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);  // ���淴��
        objShader.setVec3("material.ambient", 0.0f, 0.1f, 0.06f); // ��������
        objShader.setVec3("material.diffuse", 0.0f, 0.50980392f, 0.50980392f);  // ������
        objShader.setVec3("material.specular", 0.50196078f, 0.50196078f, 0.50196078f);  // ���淴��
        objShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(objVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // ���ƹ�Դ
        lightShader.use();
        lightShader.setMat4("model", glm::value_ptr(lightModel));
        lightShader.setMat4("view", glm::value_ptr(cam.GetViewMatrix()));
        lightShader.setMat4("projection", glm::value_ptr(projection));
        lightShader.setVec3("lightColor", lightColor.x, lightColor.y, lightColor.z);
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &objVAO);
    glDeleteBuffers(1, &objVBO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &lightVBO);

    glfwTerminate();
    return 0;
}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        // ��   +
        mixVal = (mixVal + 0.00001) >= 1.0 ? 1.0 : mixVal + 0.0001;
        return;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        // ��   +
        mixVal = (mixVal - 0.00001) <= 0.0 ? 0.0 : mixVal - 0.0001;
        return;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);

}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // ���û��ı䴰�ڴ�Сʱ����̬�����ӿڵĴ�С
    glViewport(0, 0, width, height);
}