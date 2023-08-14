#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"
#include "Sphere.h"
#include "Config.h"
#include "Camera.h"
#include <Renderer.h>
#include "Texture.h"

#include "VertexObject/VertexArray.h"
#include "VertexObject/VertexBuffer.h"
#include "VertexObject/IndexBuffer.h"
#include "VertexObject/VertexBufferLayout.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// camera
Camera camera(glm::vec3(0.0f, 5.0f, 35.0f));
float lastX = WindowWidth / 2.0f;
float lastY = WindowHeight / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(WindowWidth, WindowHeight, "Solar System", nullptr, nullptr);

  if (!window)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSwapInterval(1);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  std::cout << glGetString(GL_VERSION) << std::endl;
  
  //����������ж��������Լ�EBO����
  Sphere mySphere(40);
  std::vector<float> sphereVertices = mySphere.getVertices();
  std::vector<unsigned int> sphereIndices = mySphere.getIndices();

  {
    VertexArray va;
    VertexBuffer vb(&sphereVertices[0], sphereVertices.size() * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    va.AddBuffer(layout);

    IndexBuffer ib(&sphereIndices[0], sphereIndices.size());//�������

    glEnable(GL_DEPTH_TEST);

    Shader shader("D:/opengl picture/SolarSystem-master/SolarSystem/res/shader/task3.vs", "D:/opengl picture/SolarSystem-master/SolarSystem/res/shader/task3.fs");
    shader.Bind();
    shader.setInt("u_Texture", 0);

    Texture textureSun("D:/opengl picture/SolarSystem-master/SolarSystem/res/textures/sun.jpg");
    Texture textureEarth("D:/opengl picture/SolarSystem-master/SolarSystem/res/textures/earth.jpg");
    Texture textureMoon("D:/opengl picture/SolarSystem-master/SolarSystem/res/textures/moon.jpg");
    Texture textureMer("D:/opengl picture/SolarSystem-master/SolarSystem/res/textures/mer.jpg");
    Texture textureVen("D:/opengl picture/SolarSystem-master/SolarSystem/res/textures/ven.jpg");
    Texture textureMar("D:/opengl picture/SolarSystem-master/SolarSystem/res/textures/mar.jpg");
    Texture textureJup("D:/opengl picture/SolarSystem-master/SolarSystem/res/textures/jup.jpg");
    Texture textureSat("D:/opengl picture/SolarSystem-master/SolarSystem/res/textures/sat.jpg");
    Texture textureUra("D:/opengl picture/SolarSystem-master/SolarSystem/res/textures/ura.jpg");
    Texture textureNep("D:/opengl picture/SolarSystem-master/SolarSystem/res/textures/nep.jpg");
    vb.Unbind();
    va.Unbind();
    ib.Unbind();
    shader.Unbind();

    Renderer render;

   
    while (!glfwWindowShouldClose(window))
    {
      float currentFrame = static_cast<float>(glfwGetTime());
      deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;

      processInput(window);

      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glm::mat4 view = camera.GetViewMatrix();
      glm::mat4 proj = glm::perspective(glm::radians(camera.Zoom), (float)WindowWidth / (float)WindowHeight, 0.1f, 100.0f);

      va.Bind();
      {
        // Sun
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(glm::mat4(1.0f), -(float)glfwGetTime() / 5, glm::vec3(0.0f, 1.0f, 0.0f));
        model = scale(model, glm::vec3(sunScale, sunScale, sunScale));
        glm::mat4 mvp = proj * view * model;

        textureSun.Bind();
        shader.Bind();
        shader.setMat4("u_MVP", mvp);

        render.Draw(mySphere.getNumIndices());
      }
      
      {
        // Earth
        glm::mat4 model = glm::mat4(1.0f);
        // ��ת
        model = glm::rotate(model, (float)glfwGetTime() / 1.5f, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(SunEarthDistance, .0f, .0f));
        // ������ת��������б�����Ӱ�죬��֤��ת�� ��Ȼ������б
        model = glm::rotate(model, -(float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, -glm::radians(ErothAxialAngle), glm::vec3(0.0, 0.0, 1.0));
        // ��ת
        model = glm::rotate(model, -(float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        model = scale(model, glm::vec3(earthScale, earthScale, earthScale));
        glm::mat4 mvp = proj * view * model;

        textureEarth.Bind();
        shader.Bind();
        shader.setMat4("u_MVP", mvp);

        render.Draw(mySphere.getNumIndices());
      }
      {
          // merth
          glm::mat4 model = glm::mat4(1.0f);
          // ��ת
          model = glm::rotate(model, (float)glfwGetTime() /5.0f, glm::vec3(0.0f, 1.0f, 0.0f));
          model = glm::translate(model, glm::vec3(merDistance, .0f, .0f));
          // ������ת��������б�����Ӱ�죬��֤��ת�� ��Ȼ������б
          model = glm::rotate(model, -(float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
          model = glm::rotate(model, -glm::radians(ErothAxialAngle), glm::vec3(0.0, 0.0, 1.0));
          // ��ת
          model = glm::rotate(model, -(float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
          model = scale(model, glm::vec3(merScale, merScale, merScale));
          glm::mat4 mvp = proj * view * model;

          textureMer.Bind();
          shader.Bind();
          shader.setMat4("u_MVP", mvp);

          render.Draw(mySphere.getNumIndices());
      }
      {
          // ven
          glm::mat4 model = glm::mat4(1.0f);
          // ��ת
          model = glm::rotate(model, (float)glfwGetTime() / 2.0f, glm::vec3(0.0f, 1.0f, 0.0f));
          model = glm::translate(model, glm::vec3(venDistance, .0f, .0f));
          // ������ת��������б�����Ӱ�죬��֤��ת�� ��Ȼ������б
          model = glm::rotate(model, -(float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
          model = glm::rotate(model, -glm::radians(ErothAxialAngle), glm::vec3(0.0, 0.0, 1.0));
          // ��ת
          model = glm::rotate(model, -(float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
          model = scale(model, glm::vec3(venScale, venScale, venScale));
          glm::mat4 mvp = proj * view * model;

          textureVen.Bind();
          shader.Bind();
          shader.setMat4("u_MVP", mvp);

          render.Draw(mySphere.getNumIndices());
      }
      {
          // mar
          glm::mat4 model = glm::mat4(1.0f);
          // ��ת
          model = glm::rotate(model, (float)glfwGetTime() / 0.75f, glm::vec3(0.0f, 1.0f, 0.0f));
          model = glm::translate(model, glm::vec3(marDistance, .0f, .0f));
          // ������ת��������б�����Ӱ�죬��֤��ת�� ��Ȼ������б
          model = glm::rotate(model, -(float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
          model = glm::rotate(model, -glm::radians(ErothAxialAngle), glm::vec3(0.0, 0.0, 1.0));
          // ��ת
          model = glm::rotate(model, -(float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
          model = scale(model, glm::vec3(marScale, marScale, marScale));
          glm::mat4 mvp = proj * view * model;

          textureMar.Bind();
          shader.Bind();
          shader.setMat4("u_MVP", mvp);

          render.Draw(mySphere.getNumIndices());
      }
      {
          // jup
          glm::mat4 model = glm::mat4(1.0f);
          // ��ת
          model = glm::rotate(model, (float)glfwGetTime() / 0.5f, glm::vec3(0.0f, 1.0f, 0.0f));
          model = glm::translate(model, glm::vec3(jupDistance, .0f, .0f));
          // ������ת��������б�����Ӱ�죬��֤��ת�� ��Ȼ������б
          model = glm::rotate(model, -(float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
          model = glm::rotate(model, -glm::radians(ErothAxialAngle), glm::vec3(0.0, 0.0, 1.0));
          // ��ת
          model = glm::rotate(model, -(float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
          model = scale(model, glm::vec3(jupScale, jupScale, jupScale));
          glm::mat4 mvp = proj * view * model;

          textureJup.Bind();
          shader.Bind();
          shader.setMat4("u_MVP", mvp);

          render.Draw(mySphere.getNumIndices());
      }
      {
          // sat
          glm::mat4 model = glm::mat4(1.0f);
          // ��ת
          model = glm::rotate(model, (float)glfwGetTime() / 0.3f, glm::vec3(0.0f, 1.0f, 0.0f));
          model = glm::translate(model, glm::vec3(satDistance, .0f, .0f));
          // ������ת��������б�����Ӱ�죬��֤��ת�� ��Ȼ������б
          model = glm::rotate(model, -(float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
          model = glm::rotate(model, -glm::radians(ErothAxialAngle), glm::vec3(0.0, 0.0, 1.0));
          // ��ת
          model = glm::rotate(model, -(float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
          model = scale(model, glm::vec3(satScale, satScale, satScale));
          glm::mat4 mvp = proj * view * model;

          textureSat.Bind();
          shader.Bind();
          shader.setMat4("u_MVP", mvp);

          render.Draw(mySphere.getNumIndices());
      }
      {
          // ura
          glm::mat4 model = glm::mat4(1.0f);
          // ��ת
          model = glm::rotate(model, (float)glfwGetTime() / 0.35f, glm::vec3(0.0f, 1.0f, 0.0f));
          model = glm::translate(model, glm::vec3(uraDistance, .0f, .0f));
          // ������ת��������б�����Ӱ�죬��֤��ת�� ��Ȼ������б
          model = glm::rotate(model, -(float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
          model = glm::rotate(model, -glm::radians(ErothAxialAngle), glm::vec3(0.0, 0.0, 1.0));
          // ��ת
          model = glm::rotate(model, -(float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
          model = scale(model, glm::vec3(uraScale, uraScale, uraScale));
          glm::mat4 mvp = proj * view * model;

          textureUra.Bind();
          shader.Bind();
          shader.setMat4("u_MVP", mvp);

          render.Draw(mySphere.getNumIndices());
      }
      {
          // nep
          glm::mat4 model = glm::mat4(1.0f);
          // ��ת
          model = glm::rotate(model, (float)glfwGetTime() / 0.2f, glm::vec3(0.0f, 1.0f, 0.0f));
          model = glm::translate(model, glm::vec3(nepDistance, .0f, .0f));
          // ������ת��������б�����Ӱ�죬��֤��ת�� ��Ȼ������б
          model = glm::rotate(model, -(float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
          model = glm::rotate(model, -glm::radians(ErothAxialAngle), glm::vec3(0.0, 0.0, 1.0));
          // ��ת
          model = glm::rotate(model, -(float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
          model = scale(model, glm::vec3(nepScale, nepScale, nepScale));
          glm::mat4 mvp = proj * view * model;

          textureNep.Bind();
          shader.Bind();
          shader.setMat4("u_MVP", mvp);

          render.Draw(mySphere.getNumIndices());
      }
      {
        // Moon
        glm::mat4 model = glm::mat4(1.0f);
        // ���չ�ת
        model = glm::rotate(model, (float)glfwGetTime() / 1.5f, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(SunEarthDistance, .0f, .0f));
        // ����ת
        model = glm::rotate(model, (float)glfwGetTime() * 2.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(MoonEarthDistance, 0.0, 0.0));
        // ������ת
        model = glm::rotate(model, -(float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        model = scale(model, glm::vec3(moonScale, moonScale, moonScale));
        glm::mat4 mvp = proj * view * model;

        textureMoon.Bind();
        shader.Bind();
        shader.setMat4("u_MVP", mvp);

        render.Draw(mySphere.getNumIndices());
      }

      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  }

  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.ProcessKeyboard(FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
  float xpos = static_cast<float>(xposIn);
  float ypos = static_cast<float>(yposIn);

  if (firstMouse)
  {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

  lastX = xpos;
  lastY = ypos;

  camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  camera.ProcessMouseScroll(static_cast<float>(yoffset));
}