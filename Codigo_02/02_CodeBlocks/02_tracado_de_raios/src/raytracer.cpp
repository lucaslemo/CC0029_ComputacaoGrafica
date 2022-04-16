#include <iostream>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../include/Sphere_3.h"
#include "../include/Ray_3.h"
#include "../include/Color.h"
#include "../include/Image.h"

std::string program_name;


int maxval;
GLsizei width, height;
GLubyte *imgrtx;

Object::Hit_pair
hit(const Ray_3& r, std::vector<Object*>& object,
    double tmin, double tmax)
{
  typedef Object::Hit_pair Hit_pair;

  Hit_pair closest(NULL, tmax);
  for (int i = 0; i < object.size(); ++i) {
    Hit_pair res = object[i]->hit(r, tmin, closest.second);
    if (res.first != NULL) { // hit found
      closest = res;
    }
  }

  return closest;
}

double maxvalue(double a, double b){
    if (a >= b)
        return a;
    else
        return b;
}

Color trace(const Ray_3& r, std::vector<Object*>& object,
    double tmin = 0.0, double tmax = INF)
{
  Object::Hit_pair res = hit(r, object, tmin, tmax);
  if (res.first != NULL) {

    /*Point_3 p = find_point(r.direction(), r.origin(), tmin);
    Point_3 c = Point_3(0.5,0.5,-1.0);
    Vector_3 n = p - c;
    Vector_3 I = cross_product(r.direction(), n) * 230;
    return Color(maxvalue(I.x(), 0.0),
                 maxvalue(I.y(), 0.0),
                 maxvalue(I.z(), 0.0));*/

    /*double Id = 230, rd = 1, cos;
    Point_3 c = (0.5,0.5,-1.0);
    Point_3 p = find_point(r.direction(), r.origin(), tmin);
    Vector_3 n = (p - c), l = r.direction();
    cos = maxvalue(cos0(n, l), 0.0);
    return Color(Id*rd*cos*18, Id*rd*cos*10, Id*rd*cos*143);*/

    return Color(18, 10, 143);
  } else
    return Color(0, 0, 0);
}

Ray_3 construct_ray(int nx, int ny, int i, int j)
{
  // Configurações de câmera
  Vector_3 u(1, 0, 0);
  Vector_3 v(0, 1, 0);
  Vector_3 w(0, 0, 1);
  Point_3  e(0, 0, 1);
  double t = 1.0;
  double r = 1.0;
  double l = -r, b = -t;

  double lambda_u = l + (r - l)*(i + 0.5)/nx;
  double lambda_v = b + (t - b)*(j + 0.5)/ny;

  Point_3 origin;
  Vector_3 direction;
  origin = e + (lambda_u * u + lambda_v * v);
  direction = -w;

  return Ray_3(origin, direction);
}

int main(int argc, char *argv[])
{
  //Object::Hit_pair res;
  std::vector<Object*> object;
  Image image(400, 400);

  // Cena contém apenas uma esfera
  object.push_back(new Sphere_3(Point_3(0.5,0.5,-1.0), 0.6));
  //object.push_back(new Sphere_3(Point_3(0.0,0.0,0.0), 0.5));

  for (int i = 0; i < image.height(); ++i) {
    for (int j = 0; j < image.width(); ++j) {
      Ray_3 r = construct_ray(image.width(), image.height(), i, j);
      Color c = trace(r, object);
      image.set_pixel(i, j, c);
    }
  }

  // Carregando a imagem
  width = GLint(image.width());
  height = GLint(image.height());
  imgrtx = new GLubyte[3 * width * height];
  image.create_image(imgrtx);

  // Criando a Janela
  GLFWwindow* window;

  if (!glfwInit())
        return -1;

  window = glfwCreateWindow(width, height, "Image Viewer", NULL, NULL);

  if (!window){
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  // Loop da janela
  while (!glfwWindowShouldClose(window)){
    glClear(GL_COLOR_BUFFER_BIT);

    glRasterPos2i(-1, -1);
    glDrawBuffer(GL_BACK);
    glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, imgrtx);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();

  //image.write_ppm();


  return 0;
}
