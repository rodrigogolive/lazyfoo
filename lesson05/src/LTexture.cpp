#include "LTexture.h"

using namespace std;

LTexture::LTexture()
{
    m_textureID = 0;
    m_textureWidth = 0;
    m_textureHeight = 0;
}

LTexture::~LTexture()
{
    freeTexture();
}

bool LTexture::loadTextureFromPixels32(GLuint *pixels, GLuint width, GLuint height)
{
    freeTexture();

    m_textureWidth = height;
    m_textureHeight = height;

    // generate texture ID
    glGenTextures(1, &m_textureID);

    // bind texture ID
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    // generate texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, pixels);

    // set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // check for error
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        cout << "Error loading texture from " << pixels << " pixels"
            << gluErrorString(error) << endl;
        return false;
    }

    return true;
}

void LTexture::freeTexture()
{
    if (m_textureID != 0) {
        glDeleteTextures(1, &m_textureID);
        m_textureID = 0;
    }

    m_textureWidth = 0;
    m_textureHeight = 0;
}

void LTexture::render(GLfloat x, GLfloat y)
{
    if (m_textureID != 0) {
        // remove anu previous transformations
        glLoadIdentity();

        // move to rendering point
        glTranslatef(x, y, 0.f);

        // set texture ID
        glBindTexture(GL_TEXTURE_2D, m_textureID);

        // render textured quad
        glBegin(GL_QUADS);
            glTexCoord2f(0.f, 0.f);
            glVertex2f(0.f, 0.f);

            glTexCoord2f(1.f, 0.f);
            glVertex2f(m_textureWidth, 0.f);

            glTexCoord2f(1.f, 1.f);
            glVertex2f(m_textureWidth, m_textureHeight);

            glTexCoord2f(0.f, 1.f);
            glVertex2f(0.f, m_textureHeight);
        glEnd();
    }
}

GLuint LTexture::getTextureID()
{
    return m_textureID;
}

GLuint LTexture::textureWidth()
{
    return m_textureWidth;
}

GLuint LTexture::textureHeight()
{
    return m_textureHeight;
}
