#pragma once

#include <math.h>
#include <iostream>

class vec3 {
  public:
    vec3() {}

    vec3(float e0, float e1, float e2) {
      e[0] = e0;
      e[1] = e1;
      e[2] = e2;
    }

    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }

    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }

    inline const vec3& operator+() const { return *this; }
    inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

    inline float operator[](int i) const { return e[i]; }
    inline float& operator[](int i) { return e[i]; }

    vec3& operator+=(const vec3 &v);
    vec3& operator-=(const vec3 &v);
    vec3& operator*=(const vec3 &v);
    vec3& operator/=(const vec3 &v);
    vec3& operator*=(const float t);
    vec3& operator/=(const float t);

    inline float length() const {
      // return sqrt(this->squared_length());
      return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    }

    inline float squared_length() const {
      return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    void make_unit_vector();

    float e[3];
};

inline std::istream& operator>>(std::istream &is, vec3 &t) {
  is >> t.e[0] >> t.e[1] >> t.e[2];
  return is;
}

inline std::ostream & operator<<(std::ostream &os, const vec3 &t) {
  os << t.x() << " " << t.y() << " " << t.z();
  return os;
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
  return vec3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
  return vec3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
  return vec3(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2) {
  return vec3(v1.x() / v2.x(), v1.y() / v2.y(), v1.z() / v2.z());
}

inline vec3 operator/(float t, const vec3 &v) {
  return vec3(v.x() / t, v.y() / t, v.z() / t);
}

inline vec3 operator*(float t, const vec3 &v) {
  return vec3(t * v.x(), t * v.y(), t * v.z());
}

inline vec3 operator*(const vec3 &v, float t) {
  return vec3(t * v.x(), t * v.y(), t * v.z());
}

inline vec3 operator/(const vec3 &v, float t) {
  return vec3(v.x() / t, v.y() / t, v.z() / t);
}

inline float dot(const vec3 &v1, const vec3 &v2) {
  return (v1.x() * v2.x()) + (v1.y() * v2.y() ) + (v1.z() * v2.z());
}

inline vec3 cross(const vec3 &v1, const vec3 &v2) {
  return vec3(
    (v1.y() * v2.z() - v1.z() * v2.y()),
    (-(v1.x() * v2.z() - v1.z() * v2.x())),
    (v1.x() * v2.y() - v1.y() * v2.x())
  );
}

inline vec3 unit_vector(vec3 v) {
  return v / v.length();
}
