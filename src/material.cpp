#include "material.h"

Material::Material(std::string& filename)
{
    stbi_set_flip_vertically_on_load(1);
    m_Buffer = stbi_load(filename.c_str(), &m_Width, &m_Height, &channels,
        STBI_rgb_alpha);

    assert(m_Width > 0 and m_Height > 0 and channels > 0);

    std::cout << "Image width: " << m_Width << "\nImage height: " << m_Height
              << "\nNumber of channels: " << channels << "\n";
    // make texture
    //
    GLCall(glGenTextures(1, &texture));

    GLCall(glBindTexture(GL_TEXTURE_2D, texture));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA,
        GL_UNSIGNED_BYTE, m_Buffer));

    if (m_Buffer) {
        stbi_image_free(m_Buffer);
    }

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
}

Material::~Material() { GLCall(glDeleteTextures(1, &texture)); }

void Material::use(int unit)
{
    GLCall(glActiveTexture(GL_TEXTURE0 + unit));
    GLCall(glBindTexture(GL_TEXTURE_2D, texture));
}
