#include "triangle_mesh.h"

TriangleMesh ::TriangleMesh()
{

    vertex_count = 6;
    // std::vector<float> data = { -1.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f,
    //     1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f };
    //
    std::vector<float> data = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f };

    std::vector<int> colorIndex = { 0, 1, 2, 3 };
    // std::iota(colorIndex.begin(), colorIndex.end(), 0);

    std::vector<int> elements = { 0, 1, 2, 1, 2, 3 };

    vbo.resize(2);

    // vertex array
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // position
    glGenBuffers(1, &vbo[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(),
        GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color
    glGenBuffers(1, &vbo[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, colorIndex.size() * sizeof(int),
        colorIndex.data(), GL_STATIC_DRAW);

    glVertexAttribIPointer(1, 1, GL_INT, sizeof(int), (void*)0);
    glEnableVertexAttribArray(1);

    // element buffer object
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(int),
        elements.data(), GL_STATIC_DRAW);
}

void TriangleMesh ::draw()
{
    // this->updateData();

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, NULL);
}

void TriangleMesh ::updateData() {

};

TriangleMesh::~TriangleMesh()
{
    GLCall(glDeleteVertexArrays(1, &vao));
    GLCall(glDeleteBuffers(vbo.size(), vbo.data()));
}
