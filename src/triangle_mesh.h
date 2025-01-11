#pragma once

#include "config.h"

class TriangleMesh {
private:
    GLuint vbo = 0;
    GLuint vao = 0;
    unsigned int vertex_count;

public:
    TriangleMesh();
    void draw();
    void updateData();
    ~TriangleMesh();
};
