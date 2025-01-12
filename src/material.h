#pragma once

#include "config.h"

class Material {
public:
    Material(std::string& filename);
    ~Material();
    void use(int unit);

private:
    int m_Width, m_Height, channels;
    unsigned char* m_Buffer;
    unsigned int texture;
};
