#include <Framebuffer.hpp>

Framebuffer::Framebuffer(int p_width, int p_height)
    : width(p_width)
    , height(p_height)
    , colorBuffer(p_width* p_height)
    , depthBuffer(p_width* p_height)
{
    glGenTextures(1, &colorTexture);
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
}

Framebuffer::~Framebuffer()
{
    glDeleteTextures(1, &colorTexture);
}

void Framebuffer::Clear()
{
    // Clear color buffer
    {
        float4* colors = colorBuffer.data();

        // Fill the first line with the clear color
        for (std::size_t i = 0; i < (std::size_t)width; ++i)
            std::memcpy(&colors[i], &clearColor, sizeof(float4));

        // Copy the first line onto every line
        for (std::size_t i = 1; i < (std::size_t)height; ++i)
            std::memcpy(&colors[i * width], &colors[0], width * sizeof(float4));
    }

    // Clear depth buffer
    {
        float* depth = depthBuffer.data();
        float dp = MAX_FLOAT_VALUE;

        for (std::size_t i = 0; i < (std::size_t)width; ++i)
            std::memcpy(&depth[i], &dp, sizeof(float)); ; // Sets the z value to the greatest possible distance
        for (std::size_t i = 1; i < (std::size_t)height; ++i)
            std::memcpy(&depth[i * width], &depth[0], width * sizeof(float)); ; // Sets the z value to the greatest possible distance
                //depthBuff(x,y) = -1 
                //frameBuff(x,y) = backgroundColor
            
        
    }
}

void Framebuffer::UpdateTexture()
{
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, colorBuffer.data());
}