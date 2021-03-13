#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Application.hpp"


#include "stb_image.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Window.hpp"
#include "Application.hpp"

int main(int argc, char** argv)
{
    Window window(argc, argv);

    if (!window.Init())
        return -1;

    /* Main Game Loop */
    mainloop(window.WindowPtr());

    glfwTerminate();
    return 0;
}