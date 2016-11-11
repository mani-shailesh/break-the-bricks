//
// Contains declarations for utility classes.
//

#ifndef BREAK_THE_BRICKS_UTIL_H
#define BREAK_THE_BRICKS_UTIL_H

#include <algorithm>
#include <GL/gl.h>

class Vector2f {
private:
    float x, y;
public:
    Vector2f();

    Vector2f(float x, float y);

    inline float get_x() { return x; }

    inline float get_y() { return y; }

    Vector2f operator-(const Vector2f &) const;

    Vector2f operator+(const Vector2f &) const;

    Vector2f operator*(const float &) const;

    float dot(const Vector2f &);

    void normalize();

    float norm();

    Vector2f reflect(Vector2f normal);

    Vector2f clamp(Vector2f min, Vector2f max);
};


class Texture{
private:
    GLuint _id;
    int _width, _height;
    std::string _filename;
    bool _loaded;
public:
    Texture();

    Texture(std::string filename, int width, int height);

    GLuint load_texture();

    inline bool is_loaded(){ return _loaded; }

    inline GLuint get_id(){ return _id; }
};


// Some other utility functions

inline float clampf(float num, float a, float b) {
    return std::max(a, std::min(b, num));
}

#endif //BREAK_THE_BRICKS_UTIL_H
