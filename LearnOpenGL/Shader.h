#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    unsigned int ID;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath);
    
    // activate the shader
    // ------------------------------------------------------------------------
    void use();

    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string& name, bool value) const;
    
    // ------------------------------------------------------------------------
    void setInt(const std::string& name, int value) const;

    // ------------------------------------------------------------------------
    void setFloat(const std::string& name, float value) const;

    void setMat4(const std::string& name,const float* value) const;

    void setMat4(const std::string& name, glm::mat4 value) const;

    void setVec3(const std::string& name, float val1, float val2, float val3);

    void setVec3(const std::string& name, glm::vec3& vec);

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type);
    

};

