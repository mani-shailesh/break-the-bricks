//
// Created by shailesh on 11/10/16.
//

#include <cmath>
#include <GL/glu.h>
#include "util.h"

Vector2f::Vector2f() {
    x = 0;
    y = 0;
}

Vector2f::Vector2f(float x, float y) {
    this->x = x;
    this->y = y;
}

Vector2f Vector2f::operator+(const Vector2f &other) const {
    return Vector2f(x + other.x, y + other.y);
}

Vector2f Vector2f::operator-(const Vector2f &other) const {
    return Vector2f(x - other.x, y - other.y);
}

Vector2f Vector2f::operator*(const float &a) const {
    return Vector2f(x * a, y * a);
}

void Vector2f::normalize() {
    float magnitude = norm();
    x /= magnitude;
    y /= magnitude;
}

float Vector2f::dot(const Vector2f &other) {
    float dot_product = x * other.x + y * other.y;
    return dot_product;
}

Vector2f Vector2f::reflect(Vector2f normal) {
    normal.normalize();
    return *this - normal * (2 * this->dot(normal));
}

float Vector2f::norm() {
    return (float) sqrt(x * x + y * y);
}

Vector2f Vector2f::clamp(Vector2f a, Vector2f b) {
    return Vector2f(clampf(x, a.x, b.x), clampf(y, a.y, b.y));
}

Texture::Texture(){
    _loaded = false;
}

Texture::Texture(std::string filename, int width, int height){
    _filename = filename;
    _width = width;
    _height = height;
    _loaded = false;
}

// Ref : http://stackoverflow.com/questions/12518111/how-to-load-a-bmp-on-glut-to-use-it-as-a-texture
GLuint Texture::load_texture() {
    GLuint texture;

    char * data = new char[_width * _height * 3];

    FILE * file;

    file = fopen( _filename.c_str(), "rb" );

    if ( file == NULL ) return 0;
    fread(data, 54, 1, file);
    fread( data, _width * _height * 3, 1, file );
    fclose( file );

    char * data2 = new char[_width * _height * 3];
    for(int i = 0; i < _width * _height * 3; i+=3){
        data2[i] = data[i + 2];
        data2[i+1] = data[i + 1];
        data2[i+2] = data[i];
    }

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0,GL_RGB, GL_UNSIGNED_BYTE, data2);
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, _width, _height, GL_RGB, GL_UNSIGNED_BYTE, data2 );

    delete[] data;
    delete[] data2;

    _id = texture;
    _loaded = true;
    return _id;
}