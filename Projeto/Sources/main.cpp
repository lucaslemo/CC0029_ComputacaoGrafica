#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <cassert>

#include <iostream>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif // _WIN32

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Mesh.h>
#include <Shader.h>
#include <Scene.h>
#include <TrackBall.h>

enum {
    MODE_IDLE = 0,
    MODE_ORBITING,
    MODE_ZOOMING,
    MODE_PANNING
};

std::string program_name;
GLsizei width, height, status; // window size

float theta = 0;
float theta2[2] = {0, 0};
float head_mov[2] = {0, 0};
int rotate = 1;
int pulo[2] = {0, 0};
int parado = 1;
glm::mat4 jumpOrigin;
glm::mat4 jumpOrigin2;

void sleepcp(int milliseconds) // Cross-platform sleep function
{
    #ifdef _WIN32
        Sleep(milliseconds);
    #else
        usleep(milliseconds * 1000);
    #endif // _WIN32
}

void idle();

class MyScene : public Scene
{
public:
    MyScene()
        : _theta(0.0) { }
    
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
        pula = glm::translate(pula, glm::vec3(0.0,std::sin(theta2[steve]),0.0));
        model(steve).set_matrix(pula);

        if (theta2[steve] >= 2*M_PI){
          theta2[steve] = 0;
          pulo[steve] = 0;
          if (steve == 0)
            model(steve).set_matrix(jumpOrigin);
          else if (steve == 1)
            model(steve).set_matrix(jumpOrigin2);
          std::cout << glm::to_string(model(steve).get_matrix()) << std::endl;
        }
        
        theta2[steve] += 2*M_PI/25;
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
        parado = 1;
    }

private:
    
    glm::vec3 leg_top_center(int n)
    {
       // compute bounding box
       GLfloat xmin(0), xmax(0), ymin(0), ymax(0), zmin(0), zmax(0);
       
       Mesh& mesh = model(0).mesh(n);
       for (size_t i = 0; i < mesh.number_of_vertices(); ++i) {
           glm::vec3 p = mesh.vertex(i).Position;
           
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
    
private:
    GLfloat _theta;
};

MyScene scene;
TrackBall* trackball;

// Called when the window is resized
void
window_resized(GLFWwindow *window, int width, int height);

// Called for keyboard events
void
keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);

// Called for mouse events
void
mouse_button(GLFWwindow* window, int button, int action, int mods);

void mouse_motion(GLFWwindow* window, double x, double y);

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
  
  // Register a callback function for mouse buttons events
  glfwSetMouseButtonCallback(window, mouse_button);

  // Register a callback function for mouse move events
  glfwSetCursorPosCallback(window, mouse_motion);

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
  
  double lasttime = glfwGetTime();
  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window))
  {
    // Display scene
    display(window);

    // Poll for and process events
    glfwPollEvents();

    //idl scene
    idle();

     while (glfwGetTime() < lasttime + 1.0/60.0) {
        // TODO: Put the thread to sleep, yield, or simply do nothing
    }
    lasttime += 1.0/60.0;
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
  
    scene.set_orbit(trackball->matrix());

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
    glm::vec3 eye(16.0,15.0,16.0);
    glm::vec3 at(0.0,0.0,-1.0);
    glm::vec3 up(0.0,1.0,0.0);
    scene.set_view(eye,at,up);

    // setting up a virtual trackball
    trackball = new TrackBall(width,height);

    // set scene light
    Light light = {
        glm::vec3(1.2f, 1.0f, 2.0f), // position
        glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), // ambient
        glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), // diffuse
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), // specular
    };
    scene.set_light(light);

    scene.set_shader("Sources/shaders/vertex.glsl", "Sources/shaders/fragment.glsl");
    
    // add model from OBJ    
    scene.add_model("Data/Steve.obj");
    scene.add_model("Data/Steve2.obj");
    scene.add_model("Data/chao.obj");

    // set model matrix
    glm::mat4 matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-10.5f, -6.0f, -10.0f));
     glm::mat4 matrix2 = glm::translate(glm::mat4(1.0f), glm::vec3(-3.5f, -6.0f, -10.0f));
    scene.model(0).set_matrix(matrix);
    scene.model(1).set_matrix(matrix2);
    scene.model(2).set_matrix(matrix);

}

// Called when the window is resized
void
window_resized(GLFWwindow* window, int width, int height)
{
  // Use  black to clear the screen
  glClearColor(0, 0, 0, 1);

  // Set the viewport
  glViewport(0, 0, width, height);
  
  scene.set_projection(45.0, (float)width/(float)height, 1.0, 100.0);
  
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
      case GLFW_KEY_KP_8:
      if (action == GLFW_PRESS && pulo[0] == 0) {
        // Steve Normal
        std::cout << "Faz o steve pular\n";
        jumpOrigin = scene.model(0).get_matrix();
        pulo[0] = 1;
      }
      break;
      case GLFW_KEY_W:
      if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        // Anti Steve 
        std::cout << "caminha para frente\n";
        scene.walk_forward(1);
        parado = 0; 
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
      case GLFW_KEY_SPACE:
      if (action == GLFW_PRESS && pulo[1] == 0) {
        // Anti Steve
        std::cout << "Faz o steve pular\n";
        std::cout << glm::to_string(scene.model(1).get_matrix()) << std::endl;
        jumpOrigin2 = scene.model(1).get_matrix();
        pulo[1] = 1;
      }
      break;
    case GLFW_KEY_I:
      if (action == GLFW_PRESS) {
        std::cout << "reset view.\n";   
        trackball->reset();
      }
      break;
    case GLFW_KEY_O:
      if (action == GLFW_PRESS) {
        status = MODE_ORBITING;
        std::cout << "entering ORBIT mode.\n";
      }
      break;
    case GLFW_KEY_ESCAPE:
      if (action == GLFW_PRESS) {
        glfwTerminate();
        exit(0);
      }
    case GLFW_KEY_P:
      if (action == GLFW_PRESS) {
        status = MODE_IDLE;
        std::cout << "entering IDLE mode.\n";
      }
    default:
      break;
  }
}

void mouse_button(GLFWwindow* window, int button, int action, int mods)
{
	if (button != GLFW_MOUSE_BUTTON_LEFT)
		return;
	
	switch (action) {
		case GLFW_PRESS:
			double x, y;
         	glfwGetCursorPos(window, &x, &y);
         	std::cout << "cursor position: " << x << ", " << y << std::endl;
         	if (status == MODE_ORBITING)
         	    trackball->start(x, y);
			break;
		case GLFW_RELEASE:
       		if (status == MODE_ORBITING)
		    	trackball->stop();
			break;
   }
}

void mouse_motion(GLFWwindow* window, double x, double y)
{
    if (trackball->dragging())
        trackball->drag(x, y);
}

void idle(){
  if(pulo[0]){
    scene.jump(0);
  }
  if(pulo[1]){
    scene.jump(1);
  }
  if(parado){
    
  }
}

static void
error(int id, const char* description)
{
  std::cerr << program_name << ": " << description << std::endl;
}

