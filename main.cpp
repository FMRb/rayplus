#include <fstream>
#include <iostream>
#include "vec3.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "hitable_list.hpp"
#include "camera.hpp"
#include "utils.hpp"

vec3 random_in_unit_sphere()
{
  vec3 p;
  do
  {
    p = 2.0 * vec3(get_random_number(), get_random_number(), get_random_number()) - vec3(1, 1, 1);
  } while (p.squared_length() >= 1.0);
  return p;
}

vec3 color(const ray &r, hitable *world)
{
  hit_record rec;
  if (world->hit(r, 0.001, MAXFLOAT, rec))
  {
    vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    return 0.5 * color(ray(rec.p, target - rec.p), world);
  }
  else
  {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
  }
}

int main()
{
  int nx = 400;
  int ny = 200;
  int ns = 100;

  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<float> dist(0, 1);

  std::ofstream file("out.png");
  file << "P3\n"
       << nx << " " << ny << "\n255\n";

  hitable *list[2];
  list[0] = new sphere(vec3(0, 0, -1), 0.5);
  list[1] = new sphere(vec3(0, -100.5, -1), 100);
  hitable *world = new hitable_list(list, 2);
  camera cam;
  for (int j = ny - 1; j >= 0; j--)
  {
    for (int i = 0; i < nx; i++)
    {
      vec3 col(0, 0, 0);
      for (int s = 0; s < ns; s++)
      {
        float u = float(i + get_random_number()) / float(nx);
        float v = float(j + get_random_number()) / float(ny);
        ray r = cam.get_ray(u, v);
        vec3 p = r.point_at_parameter(2.0);
        col += color(r, world);
      }
      col /= float(ns);
      col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
      int ir = int(255.99 * col[0]);
      int ig = int(255.99 * col[1]);
      int ib = int(255.99 * col[2]);

      file << ir << " " << ig << " " << ib << "\n";
    }
  }

  file.close();
}
