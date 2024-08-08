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
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

unsigned int loadTexture(char const* path);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// 创建摄像机类
Camera cam;

// 0-1  两种纹理的混合比例
//float mixVal = 0;

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
#pragma region 初始化


    // opengl V3.3   CORE模式
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


#pragma region 载入图形数据生成缓冲对象

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
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

    // 生成顶点数组对象和顶点缓冲对象
    unsigned int objVBO, objVAO;
    glGenVertexArrays(1, &objVAO);
    glGenBuffers(1, &objVBO);
    
    glBindVertexArray(objVAO);
    glBindBuffer(GL_ARRAY_BUFFER, objVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 以顶点属性位置值作为参数，启用顶点属性；
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);



    // 生成顶点数组对象和顶点缓冲对象
    unsigned int lightVBO, lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &lightVBO);

    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 以顶点属性位置值作为参数，启用顶点属性；
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    // 纹理
    unsigned int diffuseMap = loadTexture("./container2.png");
    unsigned int diffuseMap2 = loadTexture("./container2_specular.png");

#pragma endregion

    // 物体着色器
    Shader objShader("shader.vs", "shader.fs");
    
    // 灯光着色器
    Shader lightShader("shader.vs", "lightShader.fs");


    // 设置鼠标移动回调
    glfwSetCursorPosCallback(window, mouse_callback);
    // 设置鼠标滚轮回调
    glfwSetScrollCallback(window, scroll_callback);


    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // 获取输入
        processInput(window);

        // 清屏
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!


        glm::mat4 projection;
        projection = glm::perspective(glm::radians(cam.Zoom), 
            static_cast<float>(SCR_WIDTH)/ static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);
        
        //glm::mat4 objModel = glm::mat4(1.0f);
        //objModel = glm::translate(objModel, glm::vec3(0.0f, 0.0f, 0.0f));

        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
        lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
        lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, lightPos);
        lightModel = glm::scale(lightModel, glm::vec3(0.2f));



        // 光源
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
        glm::vec3 diffuseColor = glm::vec3(0.5f);
        glm::vec3 ambientColor = glm::vec3(0.2f);
        glm::vec3 specularColor = glm::vec3(1.0f);
        objShader.setVec3("light.ambient", ambientColor); //光源的 环境光照
        objShader.setVec3("light.diffuse", diffuseColor);  //光源的 漫反射
        objShader.setVec3("light.specular", specularColor);  //光源的 镜面反射
        //objShader.setVec3("light.position", lightPos);
        objShader.setVec3("light.position", cam.Position);
        objShader.setVec3("light.direction", cam.Front);
        objShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
        objShader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
        //objShader.setVec3("light.direction", -0.2f, -1.0f, -0.3f);


        //objShader.setMat4("model", glm::value_ptr(objModel));
        objShader.setMat4("view", glm::value_ptr(cam.GetViewMatrix()));
        objShader.setMat4("projection", glm::value_ptr(projection));
        // 物体
        objShader.setVec3("viewPos", cam.Position.x, cam.Position.y, cam.Position.z);
        //objShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f); // 环境光照
        //objShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);  // 漫反射
        //objShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);  // 镜面反射
        //objShader.setVec3("material.ambient", 0.0f, 0.1f, 0.06f); // 环境光照
        //objShader.setVec3("material.diffuse", 0.0f, 0.50980392f, 0.50980392f);  // 漫反射
        objShader.setInt("material.diffuse", 0);
        //objShader.setVec3("material.specular", 0.50196078f, 0.50196078f, 0.50196078f);  // 镜面反射
        objShader.setInt("material.specular", 1);
        objShader.setFloat("material.shininess", 32.0f);
        objShader.setFloat("light.constant", 1.0f);
        objShader.setFloat("light.linear", 0.09f);
        objShader.setFloat("light.quadratic", 0.032f);
        
        
        // bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, diffuseMap2);

        glBindVertexArray(objVAO);


        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            objShader.setMat4("model", glm::value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }



        //glDrawArrays(GL_TRIANGLES, 0, 36);


        // 绘制光源
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


// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    //if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    //    // 上   +
    //    mixVal = (mixVal + 0.00001) >= 1.0 ? 1.0 : mixVal + 0.0001;
    //    return;
    //}
    //if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    //    // 下   +
    //    mixVal = (mixVal - 0.00001) <= 0.0 ? 0.0 : mixVal - 0.0001;
    //    return;
    //}

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
    // 当用户改变窗口大小时，动态调整视口的大小
    glViewport(0, 0, width, height);
}