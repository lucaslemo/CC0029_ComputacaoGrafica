#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <cassert>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Mesh.h>
#include <Shader.h>
#include <Scene.h>

std::string program_name;
GLsizei width, height; // window size
float theta = 0;
float head_mov[2] = {0, 0};
int rotate = 1;
int pulo = 0;

void idle();

class MyScene : public Scene
{
public:
    void rotate_steve(int steve){
      glm::vec3 head_RotationAxis = leg_top_center(0);

      glm::mat4 matrixRotate = glm::translate(glm::mat4(1.0f), head_RotationAxis);

      matrixRotate = glm::rotate(matrixRotate, 0.1f*rotate, glm::vec3(0.0,1.0,0.0));

      matrixRotate = glm::translate(matrixRotate, -head_RotationAxis);
      
      glm::mat4 model_matrix = model(steve).get_matrix();
      glm::mat4 update = model_matrix*matrixRotate;

      model(steve).set_matrix(update);
    }

    void move_head(int steve){
      glm::vec3 head_RotationAxis = leg_top_center(0);
      glm::mat4 matrixH = glm::translate(glm::mat4(1.0f), head_RotationAxis);
      matrixH = glm::rotate(matrixH, head_mov[steve], glm::vec3(0.0,1.0,0.0));

      std::cout << head_mov[steve] << std::endl;
      matrixH = glm::translate(matrixH, -head_RotationAxis);
      model(steve).mesh(0).set_matrix(matrixH);

    }

    void jump(int steve){
        glm::mat4 pula = model(steve).get_matrix();
        pula = glm::translate(pula, glm::vec3(0.0,0.4,0.0));
        model(steve).set_matrix(pula);
    }

    void walk_forward(int steve)
    {
        glm::vec3 legL_RotationAxis = leg_top_center(2);
        glm::vec3 legR_RotationAxis = leg_top_center(5);
        glm::vec3 armL_RotationAxis = leg_top_center(3);
        glm::vec3 armR_RotationAxis = leg_top_center(4);
        
        // we know meshes #2 and #5 are left and right legs, respectively
        glm::mat4 matrixL = glm::translate(glm::mat4(1.0f), legL_RotationAxis);
        glm::mat4 matrixR = glm::translate(glm::mat4(1.0f), legR_RotationAxis);
        glm::mat4 matrixAL = glm::translate(glm::mat4(1.0f), armL_RotationAxis);
        glm::mat4 matrixAR = glm::translate(glm::mat4(1.0f), armR_RotationAxis);
        
        matrixL = glm::rotate(matrixL, std::sin(theta), glm::vec3(0.0,0.0,1.0));
        matrixR = glm::rotate(matrixR, std::sin(theta), glm::vec3(0.0,0.0,-1.0));
        matrixAL = glm::rotate(matrixAL, std::sin(theta), glm::vec3(0.0,0.0,-1.0));
        matrixAR = glm::rotate(matrixAR, std::sin(theta), glm::vec3(0.0,0.0,1.0));
        
        theta += 2*M_PI/30;
        if (theta >= 2*M_PI)
          theta = 0;

        matrixL = glm::translate(matrixL, -legL_RotationAxis);
        matrixR = glm::translate(matrixR, -legR_RotationAxis);
        matrixAL = glm::translate(matrixAL, -armL_RotationAxis);
        matrixAR = glm::translate(matrixAR, -armR_RotationAxis);
        
        model(steve).mesh(2).set_matrix(matrixL);
        model(steve).mesh(5).set_matrix(matrixR);
        model(steve).mesh(3).set_matrix(matrixAL);
        model(steve).mesh(4).set_matrix(matrixAR);

        glm::mat4 anda = model(steve).get_matrix();
        anda = glm::translate(anda, glm::vec3(0.4,0.0,0.0));
        model(steve).set_matrix(anda);
    }

    glm::vec3 leg_top_center(int leg)
    {
       // compute bounding box
       GLfloat xmin(0), xmax(0), ymin(0), ymax(0), zmin(0), zmax(0);
       
       Mesh& mesh = model(0).mesh(leg);
       for (size_t i = 0; i < mesh.number_of_vertices(); ++i) {
           glm::vec3 p = mesh.vertex(i).Position;
           
           std::cout << glm::to_string(p) << std::endl;
           
           xmax = std::max(xmax, p.x);
           xmin = std::min(xmin, p.x);
           ymax = std::max(ymax, p.y);
           ymin = std::min(ymin, p.y);
           zmax = std::max(zmax, p.z);
           zmin = std::min(zmin, p.z);
       }
       
       return glm::vec3(0.5*(xmin + xmax),
                        ymax,
                        0.5*(zmin + zmax));
    }
};

MyScene scene;

// Called when the window is resized
void
window_resized(GLFWwindow *window, int width, int height);

// Called for keyboard events
void
keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);

// Render scene
void
display(GLFWwindow* window);

// Initialize the data to be rendered
void
initialize();

static void
error(int id, const char* description);

int
main(int argc, char *argv[])
{
  GLFWwindow* window;
  program_name = std::string(argv[0]);
  
  // Initialize the library
  if (!glfwInit())
    return EXIT_FAILURE;
    
  // Use OpenGL 3.2 core profile
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwSetErrorCallback(&error);

  // Create a windowed mode window and its OpenGL context
  width = 900;
  height = 900;
  window = glfwCreateWindow(width, height, "OpenGL Viewer", NULL, NULL);
  if (!window) {
    error(-1, "Failed to open a window.");
    glfwTerminate();
    return EXIT_FAILURE;
  }
    
  // Register a callback function for window resize events
  glfwSetWindowSizeCallback(window, &window_resized);
  
  // Register a callback function for keyboard pressed events
  glfwSetKeyCallback(window, &keyboard);

  // Make the window's context current
  glfwMakeContextCurrent(window);
  
  // Print the OpenGL version
  std::cout << "OpenGL - " << glGetString(GL_VERSION) << std::endl;
  
  // Initialize GLEW
  glewExperimental = GL_TRUE;
  if(glewInit() != GLEW_OK) {
    error(EXIT_FAILURE, "Failed to initialize GLEW! I'm out!");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Initialize the scene to be rendered
  initialize();
  
  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window))
  {
    // Display scene
    display(window);

    // Poll for and process events
    glfwPollEvents();

    //idl scene
    idle();
  }
  
  // Terminate GLFW
  glfwTerminate();
  
  return EXIT_SUCCESS;
}

// Render scene
void
display(GLFWwindow* window)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
    scene.render();

    // Swap front and back buffers
    glfwSwapBuffers(window);
}

void
initialize()
{
  glEnable(GL_DEPTH_TEST);

  // set projection
  scene.set_projection(45.0, (float)width/(float)height, 1.0, 100.0);

  // set view
  glm::vec3 eye(6.0,5.0,6.0);
  glm::vec3 at(0.0,0.0,-1.0);
  glm::vec3 up(0.0,1.0,0.0);
  scene.set_view(eye,at,up);

  // add model from OBJ    
  scene.add_model("Data/Steve.obj");
  scene.add_model("Data/Steve2.obj");

  // set model matrix
  glm::mat4 matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-10.5f, -4.0f, -10.0f));
  glm::mat4 matrix2 = glm::translate(glm::mat4(1.0f), glm::vec3(-3.5f, -4.0f, -10.0f));
  scene.model(0).set_matrix(matrix);
  scene.model(1).set_matrix(matrix2);
  
  std::cout << "Number of models: " << scene.number_of_models() << std::endl;
  
  // set scene light
  Light light = {
    glm::vec3(1.2f, 1.0f, 2.0f), // position
    glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), // ambient
    glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), // diffuse
    glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), // specular
  };
  
  scene.set_light(light);

  scene.set_shader("Sources/shaders/vertex.glsl", "Sources/shaders/fragment.glsl");
}

// Called when the window is resized
void
window_resized(GLFWwindow* window, int width, int height)
{
  // Use  black to clear the screen
  glClearColor(0, 0, 0, 1);

  // Set the viewport
  glViewport(0, 0, width, height);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glfwSwapBuffers(window);
}

// Called for keyboard events
void
keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  switch (key) {
    case GLFW_KEY_UP:
      if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        // Steve Normal
        std::cout << "caminha para frente\n";
        scene.walk_forward(0);        
      }
      break;
      case GLFW_KEY_RIGHT:
      if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        // Steve normal
        std::cout << "Rotaciona para a Direita\n";
        rotate = -1;
        scene.rotate_steve(0);     
      }
      break;
      case GLFW_KEY_LEFT:
      if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        // Steve normal
        std::cout << "Rotaciona para a Esquerda\n";
        rotate = 1;
        scene.rotate_steve(0);  
      }
      break;
      case GLFW_KEY_W:
      if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        // Anti Steve 
        std::cout << "caminha para frente\n";
        scene.walk_forward(1);        
      }
      break;
      case GLFW_KEY_D:
      if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        // Anti Steve
        std::cout << "Move\n";
        rotate = -1;
        scene.rotate_steve(1);        
      }
      break;
      case GLFW_KEY_A:
      if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        // Anti Steve
        std::cout << "Move\n";
        rotate = 1;
        scene.rotate_steve(1);        
      }
      break;
      case GLFW_KEY_E:
      if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        // Steve normal
        std::cout << "Move a cabeça para a direita\n";
        if (head_mov[1] >= -1)
          head_mov[1] -= 0.1;
        scene.move_head(1);        
      }
      break;
      case GLFW_KEY_Q:
      if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        // Steve normal
        std::cout << "Move a cabeça para a direita\n";
        if (head_mov[1] <= 1)
          head_mov[1] += 0.1;
        scene.move_head(1);        
      }
      break;
      case GLFW_KEY_P:
      if (action == GLFW_PRESS) {
        // Anti Steve
        std::cout << "Faz o steve pular\n";
        pulo = 1;
      }
      break;
    case GLFW_KEY_ESCAPE:
      if (action == GLFW_PRESS) {
        // Sai do programa
        glfwTerminate();
        exit(0);
      }
    default:
      break;
  }
}

void idle(){
  if(pulo){
    scene.jump(1);
  }
}

static void
error(int id, const char* description)
{
  std::cerr << program_name << ": " << description << std::endl;
}

