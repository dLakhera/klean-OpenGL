#include "triangle_mesh.h"

TriangleMesh ::TriangleMesh()
{

    vertex_count = 3;
    // uint64_t timeSeed =
    // std::chrono::high_resolution_clock::now().time_since_epoch().count();
    // std::seed_seq ss { uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >>
    // 32) }; this->rng.seed(ss);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void TriangleMesh ::draw()
{
    this->updateData();

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}

void TriangleMesh ::updateData()
{

    std::vector<float> data = { 0.0f,
        0.5f,
        0.0f,
        float(rand()) / (RAND_MAX),
        float(rand()) / (RAND_MAX),
        float(rand()) / (RAND_MAX),
        0.5f,
        -0.5f,
        0.0f,
        float(rand()) / (RAND_MAX),
        float(rand()) / (RAND_MAX),
        float(rand()) / (RAND_MAX),
        -0.5f,
        -0.5f,
        0.0f,
        float(rand()) / (RAND_MAX),
        float(rand()) / (RAND_MAX),
        float(rand()) / (RAND_MAX) };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(),
        GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*)0);
    glEnableVertexAttribArray(0);

    // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*)12);
    glEnableVertexAttribArray(1);
};

TriangleMesh::~TriangleMesh()
{
    GLCall(glDeleteVertexArrays(1, &vao));
    GLCall(glDeleteBuffers(1, &vbo));
}
