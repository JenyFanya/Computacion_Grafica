//Práctica 2
//Jenyfer Estefanya Sánchez Gachuz
//Fehca de entrega 24 de agosto
//Número de cuenta 319025901
#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

// Prototipo
void resize(GLFWwindow* window, int width, int height);

// ----------------------
// Matriz My melody
// ----------------------
// 0 = fondo, 1 = rosa, 2 = negro, 3 = amarillo 4=rosa fuerte
int image[19][15] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,4,4,0,0,0,0,0,4,4,0,0,0},
{0,0,4,1,1,4,0,0,0,4,1,1,4,0,0},
{0,0,4,1,1,4,0,0,0,4,1,1,4,0,0},
{0,0,4,1,1,4,0,0,0,4,1,1,4,0,0},
{0,0,4,1,1,4,0,0,0,4,1,1,4,0,0},
{0,0,0,4,1,1,4,4,4,1,1,4,0,0,0},
{0,0,0,0,4,1,1,1,1,1,4,0,0,0,0},
{0,0,0,4,1,1,1,1,1,1,1,4,0,0,0},
{0,0,4,1,1,0,0,0,0,0,1,1,4,0,0},
{0,0,4,1,4,0,0,0,0,0,4,1,4,0,0},
{0,0,4,4,0,2,0,0,0,2,0,4,4,0,0},
{0,0,4,0,0,2,0,3,0,2,0,0,4,0,0},
{0,0,0,4,0,0,0,0,0,0,0,4,0,0,0},
{0,0,0,0,4,4,4,4,4,4,4,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

// ----------------------
// DIBUJAR UNA CELDA
// ----------------------
//row=fila col=columna    r,g,b colores
void drawCell(int row, int col, float r, float g, float b, Shader& shader) {
    // Tamaño de celda:
    float cellWidth = 1.9f / 16.0f;
    float cellHeight = 2.1f / 16.0f;

    // Calcular coordenadas esquina superior izquierda
    float x = -.9f + col * cellWidth; //centrar (izquierda o derecha)
    float y = 1.18f - row * cellHeight; //subir o bajar

    // Dos triángulos para formar un cuadrado
    float vertices[] = {
        //   X              Y               Z     R    G    B
         x,           y,            0.0f,   r, g, b,
         x + cellWidth, y,            0.0f,   r, g, b,
         x + cellWidth, y - cellHeight, 0.0f,   r, g, b,

         x,           y,            0.0f,   r, g, b,
         x + cellWidth, y - cellHeight, 0.0f,   r, g, b,
         x,           y - cellHeight, 0.0f,   r, g, b
    };
    //como se leen los vértices
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //copia arreglovertices[] coordenadas y colores
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Posición
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    shader.Use();
    //dibuja 6 vertices como triangulos
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

// ----------------------
// MAIN
// ----------------------
const GLint WIDTH = 800, HEIGHT = 600;

int main() {
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "My Melody", NULL, NULL);
    glfwSetFramebufferSizeCallback(window, resize);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

    // ----------------------
    // LOOP PRINCIPAL
    // ----------------------
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // fondo blanco
        glClear(GL_COLOR_BUFFER_BIT);

        // Dibujar conejito recorriendo la matriz
        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < 15; j++) {
                if (image[i][j] != 0) {
                    float r, g, b;
    //ajuste de colores
                    if (image[i][j] == 1) { r = 1.0f; g = 0.7f; b = 0.7f; } // rosa
                    else if (image[i][j] == 4) { r = 0.98f; g = 0.50f; b = 0.45f; } // salmón
                    else if (image[i][j] == 2) { r = 0.0f; g = 0.0f; b = 0.0f; } // negro
                    else if (image[i][j] == 3) { r = 1.0f; g = 0.9f; b = 0.4f; } // amarillo (nariz)

                    drawCell(i, j, r, g, b, ourShader);
                }
            }
        }

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

// ----------------------
// CALLBACK RESIZE
// ----------------------
void resize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
