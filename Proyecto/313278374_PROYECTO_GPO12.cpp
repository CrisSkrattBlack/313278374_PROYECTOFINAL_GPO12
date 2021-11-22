//Ruiz Trejo Cristian Jesus
//Proyecto final Lab. Computacion Grafica I.H-C.
//Profesor: Ing. Carlos Aldair Roman Balbuena

//codigo tomado de los proporcionados en la clase de Lab. Computacion Grafica I.H-C. proporcionado por Ing. Carlos Aldair Roman Balbuena

// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Otras librerias
#include "SOIL2/SOIL2.h"

// Propiedades
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Prototipos de funciones
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;


glm::vec3 Light1 = glm::vec3(0);

//variables para rotacion

float rotReg = 0.0f;
float rotMu = 0.0f;
float rotTrin = 0.0f;
float movBal = 0.0f;
float rotBal = 0.0f;
bool inicanim;
bool cerrar;

// Variables de animacion
bool anim = false;
bool active;
float posicion = 0.0;
float rot = 0.0f;
bool animman;
bool baloon;

//recorridos
//Trineo
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = false;
bool recorrido4 = false;
bool recorrido5 = false;
float movtrinx = 0.0f;
float movtriny = 0.0f;
float movtrinz = 0.0f;
float movbalx = 0.0f;
float movbaly = 0.0f;

//Balon
bool recorrido6 = true;
bool recorrido7 = false;
bool recorrido8 = false;
bool recorrido9 = false;


int main()
{
    // Inicia GLFW
    glfwInit();
    // Configuracion de opciones para GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Crea un objeto de GLFWwindow para usar las funciones de GLFW
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 9", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    //Establece las funciones de devolucion de llamada
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // Opciones de glfw
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    // Se debe stablecer esto como TRUE para que GLFW sepa utilizar un enfoque moderno para recuperar extensiones y punteros de funcion
    glewExperimental = GL_TRUE;
    // Initialice GLEW para configurar los punteros de OpenGl
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define las dimenciones de la ventana
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // opciones de OpenGL
    glEnable(GL_DEPTH_TEST);

    // Configura y captura los shaders
    Shader shader("Shaders/modelLoading.vs", "Shaders/modelLoading.frag");
    Shader lampsshader("Shaders/lamp.vs", "Shaders / lamp.frag");

    // Carga de modelos
    //Casa
    Model Piso((char*)"Modelpasto/Piso.obj");
    Model PisoC((char*)"ModelCasa/Piso_Casa.obj");
    Model Techo((char*)"ModelCasa/Techo_Casa.obj");
    Model Puerta1((char*)"ModelCasa/PuertaTrac.obj");
    Model Puerta2((char*)"ModelCasa/PuertaPrinc.obj");
    Model Puerta3((char*)"ModelCasa/Puerta_Cochera.obj");
    Model PlAlt((char*)"ModelCasa/Paredes_techoPA.obj");
    Model EstC((char*)"ModelCasa/Estructura casa.obj");
    Model Escalera((char*)"ModelCasa/escalera.obj");
    Model Plbaj((char*)"ModelCasa/Divisiones_PB.obj");
    Model Plal((char*)"ModelCasa/Divisiones_PA.obj");
    Model Ventanas((char*)"ModelCasa/Ventanas.obj");

    //interior
    Model Msala((char*)"Interior/muebles/mueblesala.obj");
    Model Sala((char*)"Interior/muebles/sala.obj");
    Model Baño((char*)"Interior/objetos/baño.obj");
    Model Carro((char*)"Interior/objetos/carro.obj");
    Model Comedor((char*)"Interior/objetos/comedor.obj");

    //Exterior
    Model Arbol1((char*)"Exterior/arboles/arbol1.obj");
    Model Arbol2((char*)"Exterior/arboles/arbol2.obj");
    Model Bancas((char*)"Exterior/Bancas/bancas.obj");
    Model Plantas((char*)"Exterior/Plantas/plantas.obj");

    //objetos
    //Muñeco nueve
    Model Cuerpo((char*)"Modelmunieve/cuerpo.obj");
    Model Mano((char*)"Modelmunieve/brazoder.obj");

    //Arbol
    Model Arbol((char*)"Modelarb/Arbol.obj");

    //Balon
    Model Balon((char*)"Modelbal/balon fut.obj");

    //Regalo
    Model Tapa((char*)"Modelreg/model/tapareg.obj");
    Model Caja((char*)"Modelreg/model/cajareg.obj");

    //Trineo
    Model Trineo((char*)"ModelTrineo/Trineo_renos.obj");


    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    // Buble de juego
    while (!glfwWindowShouldClose(window))
    {
        // Establece el tiempo
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Consultar y llamas eventos
        glfwPollEvents();
        DoMovement();

        // Limpia el colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        //carga de modelos
        glm::mat4 model(1); //se crea la matriz para usarla
        ////model = glm::rotate(model, glm::radians(-rot), glm::vec3(0.0f, 0.0f, 0.0f)); //rotacion con respecto a Y, gettime normaliza el tiempo de rotacion
        //model=glm::rotate(model,(float)glfwGetTime(),glm::vec3(0.0f,0.1f,0.0f)); //rotacion con respecto a Y, gettime normaliza el tiempo de rotacion

        //Casa
        model = glm::mat4(1);// se usa la matriz
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f)); //Se escala el objeto dependiendo de el valor de los ejes
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Piso.Draw(shader); // se dibuja el modelo

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, -0.21f, 0.0f)); // se traslada el modelo en la posicion marcada en los ejes correspondientes
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        PisoC.Draw(shader);


        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Techo.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Puerta1.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Puerta2.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Puerta3.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        PlAlt.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        EstC.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Escalera.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Plbaj.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Plal.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Ventanas.Draw(shader);

        //interior
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Msala.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Sala.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Baño.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Carro.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Comedor.Draw(shader);

        //exterior
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Arbol1.Draw(shader);
        
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Arbol2.Draw(shader);
        
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Bancas.Draw(shader);
        
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Plantas.Draw(shader);

        // Objetos

        //muñeco de nueve
        //Cuerpo
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Cuerpo.Draw(shader);

        //Mano
        model = glm::mat4(1);
        //model = glm::translate(model, glm::vec3(0.0f, 0.3f, -47.0f));
        model = glm::rotate(model, glm::radians(rotMu), glm::vec3(0.0f, 0.0f, 1.0f)); //rotacion con respecto a Y, gettime normaliza el tiempo de rotacion
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Mano.Draw(shader);

        //Arbol
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.1f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Arbol.Draw(shader);

        //Balon
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(3.0f, 0.0f + movBal, 3.0f));
        model = glm::rotate(model, glm::radians(rotBal), glm::vec3(1.0f, 1.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Balon.Draw(shader);

        //Regalo
        //tapa
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Tapa.Draw(shader);

        //caja
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Caja.Draw(shader);

        //trineo
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.0f + movtrinx, 0.3f, 1.0f + movtrinz)); // Translate it down a bit so it's at the center of the scene
        model = glm::rotate(model, glm::radians(rotTrin), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Trineo.Draw(shader);


        glBindVertexArray(0);

        // Swap the buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
    // Camera controls
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (anim)
    {
        if (recorrido1) //recorrido 1
        {
            if (movtrinz > 6.0f)
            {
                recorrido1 = false;
                recorrido2 = true;
                rotTrin = 90.0f;

            }
            else
            {
                rot += 0.1f;
                movtrinz += 0.03f;
            }
        }


        if (recorrido2) //recorrido 2
        {
            if (movtrinx > 6.0f)
            {
                recorrido2 = false;
                recorrido3 = true;
                rotTrin = 180.0f;

            }
            else
            {
                rot += 0.1f;
                movtrinx += 0.03f;
            }
        }

        if (recorrido3) //recorrido 3
        {
            if (movtrinz < 0.0f)
            {
                recorrido3 = false;
                recorrido4 = true;
                rotTrin = 315.0f;

            }
            else
            {
                rot += 0.1f;
                movtrinz -= 0.03f;
            }
        }

        if (recorrido4) //recorrido 4
        {
            if (movtrinx < 0.0f)
            {
                recorrido4 = false;
                rotTrin = 0.0f;

            }
            else
            {
                rot += 0.1f;
                movtrinx -= 0.01f;
            }
        }

        //if (recorrido4) //recorrido 4 diagonal
        //{
        //    if (movx < 0.0f && movz > 94.0f)
        //    {
        //        recorrido4 = false;
        //        recorrido2 = true;
        //        rotvehiculo = 90.0f;

        //    }
        //    else
        //    {
        //        rot += 0.1f;
        //        movx -= 0.03f;
        //        movz += 0.03f;
        //    }
        //}

   /* if (keys[GLFW_KEY_O])
    {
        rot += 0.2f;
    }

    if (inicanim) {
        if (rot < 20.0) {
            rot += 0.1f;
        }

    }
    else if (!inicanim) {
        if (rot > 0.0) {
            rot -= 0.1f;
        }
    }*/
    }
    //animacion mano
    if (animman) {
        rotMu += 0.01;
    }
    else if (!animman) {
        rotMu -= 0.01;
    }
    if (baloon) {
        if (recorrido6) {
            if (movBal > 5.0f) {
                recorrido6 = false;
                recorrido7 = true;
            }
            else {
                movBal += 0.01f;
                rotBal += 0.01;
            }
        }
        if (recorrido7) {
            if (movBal < 0.0f) {
                recorrido7 = false;
                recorrido6 = true;
            }
            else {
                movBal -= 0.01;
                rotBal -= 0.01f;
            }
        }
    }
}


// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }

    if (keys[GLFW_KEY_SPACE])
    {
        active = !active;
        anim = !anim;
        if (active)
        {
            Light1 = glm::vec3(0.0f, 0.0f, 0.0f);
        }
        else
        {
            Light1 = glm::vec3(0);
        }
    }
    if (keys[GLFW_KEY_M]) {
        animman = !animman;
    }
    if (keys[GLFW_KEY_B]) {
        baloon = !baloon;
    }
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}
