//Práctica 04
//Sanchez Gachuz Jenyfer Estefanya
//No. de cuenta: 319025901
//Fecha de entrega: 06 de septiembre del 2025

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);

const GLint WIDTH = 800, HEIGHT = 600;
float movX = 0.0f;
float movY = 0.0f;
float movZ = -8.0f;
float rot = 0.0f;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, " Jenyfer E Sanchez_Rectangulos 3D Pegados", nullptr, nullptr);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (nullptr == window)
    {
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

    glViewport(0, 0, screenWidth, screenHeight);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

    // Vertices de un cubo
    float vertices[] = {
        -0.5f, -0.5f, 0.5f, 1.0f, 1.0f,0.0f,
         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,
         0.5f,  0.5f, 0.5f, 1.0f, 0.0f,0.0f,
         0.5f,  0.5f, 0.5f, 1.0f, 0.0f,0.0f,
        -0.5f,  0.5f, 0.5f, 1.0f, 0.0f,0.0f,
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,

        -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
         0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
         0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
         0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
        -0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
        -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,

         0.5f, -0.5f, 0.5f,  0.0f, 0.0f,1.0f,
         0.5f, -0.5f,-0.5f,  0.0f, 0.0f,1.0f,
         0.5f,  0.5f,-0.5f,  0.0f, 0.0f,1.0f,
         0.5f,  0.5f,-0.5f,  0.0f, 0.0f,1.0f,
         0.5f,  0.5f, 0.5f,  0.0f, 0.0f,1.0f,
         0.5f, -0.5f, 0.5f,  0.0f, 0.0f,1.0f,

        -0.5f,  0.5f, 0.5f,  1.0f, 1.0f,0.0f,
        -0.5f,  0.5f,-0.5f,  1.0f, 1.0f,0.0f,
        -0.5f, -0.5f,-0.5f,  1.0f, 1.0f,0.0f,
        -0.5f, -0.5f,-0.5f,  1.0f, 1.0f,0.0f,
        -0.5f, -0.5f, 0.5f,  1.0f, 1.0f,0.0f,
        -0.5f,  0.5f, 0.5f,  1.0f, 1.0f,0.0f,

        -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,1.0f,
         0.5f, -0.5f,-0.5f, 0.0f, 1.0f,1.0f,
         0.5f, -0.5f, 0.5f, 0.0f, 1.0f,1.0f,
         0.5f, -0.5f, 0.5f, 0.0f, 1.0f,1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f,1.0f,
        -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,1.0f,

        -0.5f,  0.5f,-0.5f, 1.0f, 0.2f,0.5f,
         0.5f,  0.5f,-0.5f, 1.0f, 0.2f,0.5f,
         0.5f,  0.5f, 0.5f, 1.0f, 0.2f,0.5f,
         0.5f,  0.5f, 0.5f, 1.0f, 0.2f,0.5f,
        -0.5f,  0.5f, 0.5f, 1.0f, 0.2f,0.5f,
        -0.5f,  0.5f,-0.5f, 1.0f, 0.2f,0.5f
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Posición
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glm::mat4 projection = glm::mat4(1);
    projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window))
    {

        Inputs(window);
        glfwPollEvents();

        glClearColor(0.35f, 0.75f, 0.55f, 1.0f);//color de fondo
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.Use();
        glm::mat4 model = glm::mat4(1);
        glm::mat4 view = glm::mat4(1);

        view = glm::translate(view, glm::vec3(movX, movY, movZ));
        view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");

        glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glBindVertexArray(VAO);



        // Parámetros
        float altura = 0.6f;
        float ancho = 3.0f;
        float zProf = 0.1f;
        //                           ------CUERPO TRONCO INICIO-------------------
        // --- Rectángulo 1 (naranja) ---
        glUniform1i(glGetUniformLocation(ourShader.Program, "useUniformColor"), 1);
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.5f, 0.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f, 0.4f, 0.8f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- Rectángulo 2 (amarillo) ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.9f, 0.2f);//color

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.6f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f, 0.4f, 0.8f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- Rectángulo 3 (naranja) ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.5f, 0.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f, 0.4f, 0.8f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- Rectángulo 4 (amarillo) ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.9f, 0.2f);//color
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.2f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f, 0.4f, 0.8f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- Rectángulo 5 (naranja) ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.5f, 0.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.6f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f, 0.4f, 0.8f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- Rectángulo 6 (amarillo) ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.9f, 0.2f); //color
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f, 0.4f, 0.8f));// menos ancho z largo x
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //                           ------CUERPO TRONCO FINAL-------------------
        // 
        ///////---------------------------------------BRAZO DERECHO----------------------------------
        // --- Rectángulo 1 (naranja) ---
        glUniform1i(glGetUniformLocation(ourShader.Program, "useUniformColor"), 1);
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.5f, 0.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.8f, .7f, 0.0f)); // TRSLADA MOVIMIENTO .6 X .7 Y (abajo)
        model = glm::scale(model, glm::vec3(1.9f, 0.4f, 0.8f));// SCALA TAMAÑO
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- Rectángulo 2 (Amarillo, alto 0.3) ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.9f, 0.2f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.8f, 0.35f, 0.0f)); // 0.7 - (0.2 + 0.15)
        model = glm::scale(model, glm::vec3(1.9f, 0.3f, 0.8f)); //1.9 x a la derecha
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- Rectángulo 3 (Naranja, alto 0.3) ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.5f, 0.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.5f, 0.05f, 0.0f)); // 0.35 - (0.15 + 0.15)
        model = glm::scale(model, glm::vec3(.5f, 0.3f, 0.8f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- Rectángulo 4 (Amarillo, alto 0.3) ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.9f, 0.2f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.5f, -0.25f, 0.0f)); // 0.05 - (0.15 + 0.15)
        model = glm::scale(model, glm::vec3(.5f, 0.3f, 0.8f));//.5 acortar
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- Rectángulo 5 (Naranja, alto 0.3) ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.5f, 0.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.5f, -.55f, 0.0f)); // -0.25 - (0.15 + 0.15) //1.7 derecha .55 subir
        model = glm::scale(model, glm::vec3(.5f, 0.3f, 0.8f)); //5 ancho
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model))
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- Rectángulo 6 (amarillo) ---
        //glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.9f, 0.2f); //color
        //model = glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(2.0f, 0.4f, 0.8f));// menos ancho z largo x
        //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        ///////---------------------------------------BRAZO DERECHO----------------------------------
        // --- Brazo izquierdo, Rectángulo 1 ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.5f, 0.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.8f, 0.7f, -0.1f)); // X negativo, Z hacia atrás
        model = glm::scale(model, glm::vec3(1.9f, 0.4f, 0.8f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- Brazo izquierdo, Rectángulo 2 ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.9f, 0.2f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.8f, 0.35f, -0.15f));
        model = glm::scale(model, glm::vec3(1.9f, 0.3f, 0.8f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- Brazo izquierdo, Rectángulo 3 ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.5f, 0.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.5f, 0.05f, -0.2f));
        model = glm::scale(model, glm::vec3(0.5f, 0.3f, 0.8f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // --- Brazo izquierdo, Rectángulo 1 ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.5f, 0.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.8f, 0.7f, -0.1f));
        model = glm::scale(model, glm::vec3(1.9f, 0.4f, 0.8f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- Brazo izquierdo, Rectángulo 2 ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.9f, 0.2f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.8f, 0.35f, -0.15f));
        model = glm::scale(model, glm::vec3(1.9f, 0.3f, 0.8f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- Brazo izquierdo, Rectángulo 3 ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.5f, 0.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.5f, 0.05f, -0.2f));
        model = glm::scale(model, glm::vec3(0.5f, 0.3f, 0.8f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- Brazo izquierdo, Rectángulo 4 ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.9f, 0.2f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.5f, -0.25f, -0.25f));
        model = glm::scale(model, glm::vec3(0.5f, 0.3f, 0.8f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- Brazo izquierdo, Rectángulo 5 ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.5f, 0.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.5f, -0.55f, -0.3f));
        model = glm::scale(model, glm::vec3(0.5f, 0.3f, 0.8f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        /////--------------------Fin Brazo izquierdo------------
        //----------------------CABEZA-------------

       // --- Rectángulo encima del tronco ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.5f, 0.0f); // naranja

        model = glm::mat4(1.0f); // reiniciamos la matriz, NO usar glm::mat4 model

        glm::vec3 newScale(2.0f * 0.75f, 0.4f * 1.75f, 0.8f * 1.75f); //.75 ancho de cabeza
        glm::vec3 newPos(0.0f, 1.0f + 0.4f / 2 + newScale.y / 2, 0.0f + 0.1f);
        newPos.y -= 0.3f; //bajamos cabeza

        model = glm::translate(model, newPos);
        model = glm::scale(model, newScale);

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
//
        // ---------------//Punta de la cabeza---------
             // --- Rectángulo encima del anterior (cabeza más pequeña) ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.5f, 0.0f); // naranja

        model = glm::mat4(1.0f); // reiniciamos la matriz

        // Escala: un poco menos de largo (reducción en X), misma altura y profundidad
        glm::vec3 newScale2(newScale.x * 0.85f, newScale.y, newScale.z); // 85 ancho de cabeza

        // Posición: encima del rectángulo anterior
        glm::vec3 newPos2 = newPos;
        newPos2.y += newScale.y / 2 + newScale2.y / 2; // mitad del anterior + mitad del nuevo
        // Mantener Z igual o ajustar si quieres que sobresalga hacia ti
        newPos2.z = newPos.z;
        newPos2.y -= 0.35f;//subir o bajar cabeza


        model = glm::translate(model, newPos2);
        model = glm::scale(model, newScale2);



        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //-------------Fin punta cabeza-----------


        // --- Ceja izquierda ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 0.55f, 0.27f, 0.07f); // café

        model = glm::mat4(1.0f);

        // Escala más visible
        glm::vec3 eyebrowScale(newScale2.x * 0.3f, 0.08f, newScale2.z * 0.2f);

        // Posición: 1/3 desde el lado superior izquierdo, un poco delante de la cabeza
        glm::vec3 eyebrowPos;
        eyebrowPos.x = newPos2.x - newScale2.x / 2 + newScale2.x * 0.28f;
        eyebrowPos.y = newPos2.y + newScale2.y / 2 - eyebrowScale.y / 2;
        eyebrowPos.z = newPos2.z + newScale2.z / 2 + 0.01f; // delante de la cabeza

        model = glm::translate(model, eyebrowPos);
        model = glm::scale(model, eyebrowScale);

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        eyebrowPos.y = -.2f;


        // --- Ceja derecha ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 0.59f, 0.27f, 0.07f); // café

        model = glm::mat4(1.0f);

        eyebrowScale = glm::vec3(newScale2.x * 0.3f, 0.08f, newScale2.z * 0.2f);

        // Posición: simétrica en X, mismo Y y Z
        eyebrowPos.x = newPos2.x + newScale2.x / 2 - newScale2.x * 0.28f; // espejo de la izquierda
        eyebrowPos.y = newPos2.y + newScale2.y / 2 - eyebrowScale.y / 2;   // parte superior de la cabeza
        eyebrowPos.z = newPos2.z + newScale2.z / 2 + 0.01f;               // un poco hacia ti

        model = glm::translate(model, eyebrowPos);
        model = glm::scale(model, eyebrowScale);

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //---------------PARPADO DERECHO --------------
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 0.93f, 0.40f, 0.0f); // naranja oscuro 

        glm::vec3 eyelidPosRight = eyebrowPos; // copia de la ceja derecha
        glm::vec3 eyelidScale = eyebrowScale;  // copia de la escala de ceja

        eyelidPosRight.y -= 0.1f;
        eyelidScale.y = 0.003f;
        eyelidPosRight.z = newPos2.z + newScale2.z / 2 + 0.05f;

        model = glm::mat4(1.0f);
        model = glm::translate(model, eyelidPosRight);
        model = glm::scale(model, eyelidScale);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //---------------OJO DERECHO --------------
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 1.0f, 1.0f); // blanco

        glm::vec3 eyePosRight = eyelidPosRight;
        glm::vec3 eyeScale = eyelidScale;

        eyePosRight.y -= 0.1f;
        eyePosRight.z = newPos2.z + newScale2.z / 2 + 0.01f;
        eyeScale.y = 0.10f;

        model = glm::mat4(1.0f);
        model = glm::translate(model, eyePosRight);
        model = glm::scale(model, eyeScale);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //---------------PARPADO IZQUIERDO --------------
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 0.93f, 0.40f, 0.0f); // naranja oscuro 

        glm::vec3 eyelidPosLeft = eyelidPosRight; // copia del derecho
        eyelidPosLeft.x = -(eyelidPosRight.x - newPos2.x) + newPos2.x; // espejo en X

        model = glm::mat4(1.0f);
        model = glm::translate(model, eyelidPosLeft);
        model = glm::scale(model, eyelidScale);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //---------------OJO IZQUIERDO --------------
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 1.0f, 1.0f); // blanco

        glm::vec3 eyePosLeft = eyelidPosLeft;
        glm::vec3 eyeScaleLeft = eyeScale;

        eyePosLeft.y -= 0.1f;
        eyePosLeft.z = newPos2.z + newScale2.z / 2 + 0.01f;

        model = glm::mat4(1.0f);
        model = glm::translate(model, eyePosLeft);
        model = glm::scale(model, eyeScaleLeft);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //---------------PUPILA OJO DERECHO --------------
        glm::vec3 pupilPosRight = eyePosRight;
        pupilPosRight.z += 0.15f; // más al frente para que sobresalga del ojo

        glm::vec3 pupilScale(0.12f, 0.12f, 0.02f); // tamaño visible

        model = glm::mat4(1.0f);
        model = glm::translate(model, pupilPosRight);
        model = glm::scale(model, pupilScale);
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 0.0f, 0.0f, 0.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //---------------PUPILA OJO IZQUIERDO --------------
        glm::vec3 pupilPosLeft = eyePosLeft;
        pupilPosLeft.z += 0.15f; // más al frente

        model = glm::mat4(1.0f);
        model = glm::translate(model, pupilPosLeft);
        model = glm::scale(model, pupilScale);
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 0.0f, 0.0f, 0.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //---------------BOCA --------------
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 0.0f, 0.0f, 0.0f); // negro

        // Variables para controlar el tamaño de la boca
        float mouthWidth = 0.85f;   // ancho de la boca (X)
        float mouthHeight = 0.15f;  // alto de la boca (Y)
        float mouthDepth = 0.01f;  // grosor (Z)

        // Posición: debajo de la punta de la cabeza
        glm::vec3 mouthPos;
        mouthPos.x = newPos2.x;                    // centrado en X
        mouthPos.y = newPos2.y - newScale2.y / 2 + 0.15f; // un poco debajo del rectángulo superior de la cabeza
        mouthPos.z = newPos2.z + newScale2.z / 2 + 0.02f; // al frente para que se vea

        glm::vec3 mouthScale(mouthWidth, mouthHeight, mouthDepth); // escala del rectángulo

        model = glm::mat4(1.0f);
        model = glm::translate(model, mouthPos);
        model = glm::scale(model, mouthScale);

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //-------------------Diente grande-------------------- 
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 1.0f, 1.0f); // negro

        // Variables para controlar el tamaño de la boca
        float dienteWidth = 0.55f;   // ancho de la boca (X)
        float dienteHeight = 0.15f;  // alto de la boca (Y)
        float dienteDepth = 0.06f;  // grosor (Z)

        // Posición: debajo de la punta de la cabeza
        glm::vec3 dientePos;
        dientePos.x = newPos2.x;                    // centrado en X
        dientePos.y = newPos2.y - newScale2.y / 2 + 0.15f; // un poco debajo del rectángulo superior de la cabeza
        dientePos.z = newPos2.z + newScale2.z / 2 + 0.02f; // al frente para que se vea

        glm::vec3 dienteScale(dienteWidth, dienteHeight, dienteDepth); // escala del rectángulo

        model = glm::mat4(1.0f);
        model = glm::translate(model, dientePos);
        model = glm::scale(model, dienteScale);

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //-------------------Diente chiquito-------------------- 
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 1.0f, 1.0f); // blanco

        float dientecWidth = 0.35f;  // ancho de la boca (X)
        float dientecHeight = 0.05f;  // alto de la boca (Y)
        float dientecDepth = 0.06f; // grosor (z)

        glm::vec3 dientecPos;
        dientecPos.x = newPos2.x;
        dientecPos.y = dientePos.y - dienteHeight + 0.05f;   // justo debajo del grande
        dientecPos.z = newPos2.z + newScale2.z / 2 + 0.02f;

        glm::vec3 dientecScale(dientecWidth, dientecHeight, dientecDepth);

        model = glm::mat4(1.0f);
        model = glm::translate(model, dientecPos);
        model = glm::scale(model, dientecScale);

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //---------------Supuesto sombrero parte de abajo-------------
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 0.05f, 0.05f, 0.05f); // negro fuerte
        glm::vec3 middlePos;
        middlePos.x = (eyePosRight.x + eyePosLeft.x) / 2.0f;
        middlePos.y = (eyePosRight.y + eyePosLeft.y) / 2.0f + .30f; // <-- aquí lo bajamos
        middlePos.z = newPos2.z + newScale2.z / 2 - .5f;//<- mover hacia atras

        glm::vec3 middleScale(2.3f, 0.19f, 1.7f); //largo. alto y ancho  del sombrero

        model = glm::mat4(1.0f);
        model = glm::translate(model, middlePos);
        model = glm::scale(model, middleScale);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //---------------Sombrero parte de arriba
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 0.15f, 0.15f, 0.15f); // negro claro
        // Reducimos la altura de la cabeza al 50% (o el valor que quieras)
        glm::vec3 headScale(newScale.x * 0.95f, newScale.y * 0.6f, newScale.z);

        // Posición: encima del sombrero
        glm::vec3 headPos = middlePos;
        headPos.y += middleScale.y / 2 + headScale.y / 2; // mitad del sombrero + mitad de la cabeza
        headPos.y -= 0.00001f; // opcional: ajusta más arriba o abajo
        headPos.z = middlePos.z;


        model = glm::mat4(1.0f);
        model = glm::translate(model, headPos);
        model = glm::scale(model, headScale);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
//
        //Patitas
// ----------------- PIERNAS -----------------
// --- Pierna izquierda (naranja) ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.5f, 0.0f); // color naranja
        model = glm::mat4(1.0f);

        // Traslación: mueve la pierna a la izquierda y hacia abajo del tronco
        // x = -0.6f (izquierda), y = -1.8f (baja debajo del tronco), z = 0.0f
        model = glm::translate(model, glm::vec3(-0.6f, -1.6f, 0.0f));

        // Escalado: tamaño de la pierna
        // x = 5.9f (ancho), y = .5f (alto = 3 cubos * 0.4f), z = 0.4f (profundidad)
        model = glm::scale(model, glm::vec3(0.7f, .9f, 0.4f));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- Pierna derecha (naranja) ---
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 1.0f, 0.5f, 0.0f); // color naranja
        model = glm::mat4(1.0f);

        // Traslación: mueve la pierna a la derecha y hacia abajo del tronco
        // x = 0.6f (derecha), y = -1.8f (baja debajo del tronco), z = 0.0f
        model = glm::translate(model, glm::vec3(0.6f, -1.6f, 0.0f));

        // Escalado: tamaño de la pierna
        // x = 0.4f (ancho), y = 1.2f (alto = 3 cubos * 0.4f), z = 0.4f (profundidad)
        model = glm::scale(model, glm::vec3(0.7f, .9f, 0.4f));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);



                                        //Zapatitos derecho 
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 0.0f, 0.0f, 0.0f); // color negro
        model = glm::mat4(1.0f);

         /*Traslación: mueve la pierna a la derecha y hacia abajo del tronco
         x = 0.6f (derecha), y = -1.8f (baja debajo del tronco), z = 0.0f*/
        model = glm::translate(model, glm::vec3(0.6f, -2.0f, 0.15f));

         /*Escalado: tamaño de la pierna
         x = 0.4f (ancho), y = 1.2f (alto = 3 cubos * 0.4f), z = 0.4f (profundidad)*/
        model = glm::scale(model, glm::vec3(0.8f, .3f, -0.9f));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

                                        //Zapatitos izquierdo
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 0.0f, 0.0f, 0.0f); // color negro
        model = glm::mat4(1.0f);

        /* Traslación: mueve la pierna a la derecha y hacia abajo del tronco
         x = 0.6f (derecha), y = -1.8f (baja debajo del tronco), z = 0.0f*/
        model = glm::translate(model, glm::vec3(-0.6f, -2.0f, 0.15f));

        /* Escalado: tamaño de la pierna
         x = 0.4f (ancho), y = 1.2f (alto = 3 cubos * 0.4f), z = 0.4f (profundidad)*/
        model = glm::scale(model, glm::vec3(0.8f, .3f, -0.9f));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

    
         //----------------- Parte superior del zapato derecho (gris oscuro) -----------------
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 0.15f, 0.15f, 0.15f); // color gris oscuro 
        model = glm::mat4(1.0f);

         //Traslación: misma posición en X y Z que el zapato, pero más arriba en Y
         //x = 0.6f (derecha)
         //y = -1.8f (un poco encima del zapato que estaba en -2.0f)
         //z = 0.15f (alineado al frente con el zapato)
        model = glm::translate(model, glm::vec3(0.6f, -1.8f, 0.15f));

        /* Escalado: más delgado y un poco menos ancho
         x = 0.6f (menos ancho que el zapato negro que era 0.8f)
         y = 0.2f (más delgado que el zapato negro que era 0.3f)
         z = -0.7f (un poco menos profundo que el zapato)*/
        model = glm::scale(model, glm::vec3(0.73f, 0.1f, -0.5f));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

         //----------------- Parte superior del zapato izquierdo (gris oscuro) -----------------
        glUniform3f(glGetUniformLocation(ourShader.Program, "objectColor"), 0.15f, 0.15f, 0.15f); // color gris oscuro
        model = glm::mat4(1.0f);

        /* Traslación: lado izquierdo
         x = -0.6f (izquierda)
         y = -1.8f (encima del zapato izquierdo que estaba en -2.0f)
         z = 0.15f (alineado al frente con el zapato)*/
        model = glm::translate(model, glm::vec3(-0.6f, -1.8f, 0.15f));

         /*Escalado: mismo que el derecho
         x = 0.4f (menos ancho)
         y = 0.2f (más delgado)
         z = -0.7f (menos profundo)*/
        model = glm::scale(model, glm::vec3(0.73f, 0.1f, -0.5f));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);


        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return EXIT_SUCCESS;
}

void Inputs(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        movX += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        movX -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
        movY += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
        movY -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        movZ -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        movZ += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        rot += 0.4f;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        rot -= 0.4f;
}
