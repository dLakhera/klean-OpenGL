#include "config.h"
#include "material.h"
#include "triangle_mesh.h"
#include <ostream>

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action,
    int mods)
{

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

unsigned int make_module(std::string filePath, GLenum shaderType)
{

    std::ifstream file;
    std::string line;
    std::stringstream buffString;

    file.open(filePath);

    while (std::getline(file, line)) {
        buffString << line << "\n";
    }

    std::string shaderSource = buffString.str();
    const char* sourceStr = shaderSource.c_str();
    buffString.str("");

    file.close();

    // GLuint shader_program = glCreateProgram();

    GLuint vs = glCreateShader(shaderType);
    glShaderSource(vs, 1, &sourceStr, NULL);
    glCompileShader(vs);

    GLint success;

    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(vs, 1024, &log_length, message);
        std::cout << "Error occured while compiling shader for " << filePath
                  << std::endl;
        std::cout << "Error : " << message << std::endl;
    }

    return vs;
}

unsigned int make_shader(const std::string& vertex_file,
    const std::string& fragment_file)
{

    std::vector<unsigned int> modules;

    modules.emplace_back(make_module(vertex_file, GL_VERTEX_SHADER));
    modules.emplace_back(make_module(fragment_file, GL_FRAGMENT_SHADER));

    GLuint shader_program = glCreateProgram();
    for (unsigned int i = 0; i < modules.size(); i++) {
        glAttachShader(shader_program, modules[i]);
    }
    glLinkProgram(shader_program);

    GLint program_linked;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &program_linked);
    if (program_linked != GL_TRUE) {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetProgramInfoLog(shader_program, 1024, &log_length, message);
        // Write the error to a log

        std::cout << "Error : " << message << std::endl;
    }

    for (unsigned int i = 0; i < modules.size(); i++) {
        glDeleteShader(modules[i]);
    }

    return shader_program;
}

int main(int argc, char* argv[])
{
    std::cout << "Heloo World!" << std::endl;

    glfwSetErrorCallback(error_callback);
    GLFWwindow* window;

    if (!glfwInit()) {
        std::cout << " Failed to create window! " << std::endl;
        // exit 0;
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 480, "klean", NULL, NULL);
    glfwSetKeyCallback(window, key_callback);
    // glfwSwapInterval(1);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    int version_glad = gladLoadGL();
    if (version_glad == 0) {

        glfwTerminate();
        return -1;
    }

    unsigned int shader_program = make_shader("../src/shaders/vertex.txt", "../src/shaders/fragment.txt");

    std::string filename = "../assets/duggu_1.png";
    std::string mask_file = "../assets/duggu.png";
    TriangleMesh* triangle = new TriangleMesh();
    Material* material = new Material(filename);
    Material* mask = new Material(mask_file);

    // set texture units
    GLCall(glUseProgram(shader_program));
    GLCall(glUniform1i(glGetUniformLocation(shader_program, "material"), 0));
    GLCall(glUniform1i(glGetUniformLocation(shader_program, "mask"), 1));

    // enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // GLCall(glClearColor(.25f, .5f, 0.75f, 1.0f));
    while (!glfwWindowShouldClose(window)) {
        // mat4x4 mat;
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // GL_COLOR_BUFFER_BIT parameter means that
                                                            // the clear call will affect the color
                                                            // buffer, causing it to be cleared to the
                                                            // current clearing color

        GLCall(glUseProgram(shader_program));
        triangle->draw();
        material->use(0);
        mask->use(1);
        glfwSwapBuffers(window);
    }
    delete triangle;
    delete material;
    delete mask;
    glDeleteProgram(shader_program);
    glfwTerminate();

    return 0;
}
