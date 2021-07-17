#ifndef ___LEARN_OPENGL_SHADER_H___
#define ___LEARN_OPENGL_SHADER_H___

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
private:
    GLuint shaderProgram;

public:
    Shader(std::string vertexSourcePath, std::string fragmentSourcePath)
    {
        std::string vSource, fSource;
        std::ifstream vSourceFile;
        std::ifstream fSourceFile;
        vSourceFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fSourceFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            vSourceFile.open(vertexSourcePath);
            fSourceFile.open(fragmentSourcePath);

            std::stringstream vSourceStream, fSourceStream;
            vSourceStream << vSourceFile.rdbuf();
            fSourceStream << fSourceFile.rdbuf();

            vSourceFile.close();
            fSourceFile.close();

            vSource = vSourceStream.str();
            fSource = fSourceStream.str();
        }
        catch (const std::ifstream::failure &e)
        {
            std::cerr << "Open shader source file failed: " << e.what() << std::endl;
        }

        const char *vertexSource = vSource.c_str();
        const char *fragmentSource = fSource.c_str();

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, nullptr);
        glCompileShader(vertexShader);
        checkCompileError(vertexShader, "Vertex");

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
        glCompileShader(fragmentShader);
        checkCompileError(fragmentShader, "Fragment");

        shaderProgram = glCreateProgram();
        glUseProgram(shaderProgram);
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        checkLinkError();

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    // activate the shader
    // ------------------------------------------------------------------------
    void activate() const
    {
        glUseProgram(shaderProgram);
    }
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) const
    {
        glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
    }
    void setVec2(const std::string &name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string &name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const
    {
        glUniform4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
    }
    void setVec4(const std::string &name, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:
    void checkCompileError(const GLuint shader, std::string shaderType)
    {
        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char log[512];
            glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
            std::cout << "LearnOpenGL::Shader::" << shaderType << "Error: " << log << std::endl;
        }
    }
    void checkLinkError()
    {
        int status;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
        if (!status)
        {
            char log[512];
            glGetProgramInfoLog(shaderProgram, 512, nullptr, log);
            std::cout << "LearnOpenGL::ShaderProgram::Error: " << log << std::endl;
        }
    }
};

#endif