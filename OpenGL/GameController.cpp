#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    GameController* gameController = (GameController*)glfwGetWindowUserPointer(window);    
    if (key == GLFW_KEY_V && action == GLFW_PRESS)
    {
        WindowController::GetInstance().ResizeWindow(*gameController->resIt);
        gameController->MoveResIterator();
    }
    if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        gameController->camera = new Camera(*gameController->camIt);
        gameController->MoveCamIterator();
    }
}

GameController::GameController()
{
    resOptions = {
        Resolution(640, 200),
        Resolution(1280, 384),
        Resolution(1280, 768)
    };
    resIt = resOptions.begin();

    camOptions = {
        Camera(WindowController::GetInstance().GetResolution(), {100, 100, 2}, {0, 0, 0}, {1, 1, 0}),
        Camera(WindowController::GetInstance().GetResolution(), {100, 100, 2}, {0, 0, 0}, {0, 1, 1}),
        Camera(WindowController::GetInstance().GetResolution(), {100, 100, 2}, {0, 0, 0}, {0, 1, 0})
    };
    camIt = camOptions.begin();
}

void GameController::MoveResIterator()
{
    if (resIt != resOptions.end() - 1) {
        resIt++;
    }
    else {
        resIt = resOptions.begin();
    }
}

void GameController::MoveCamIterator()
{
    if (camIt != camOptions.end() - 1) {
        camIt++;
    }
    else {
        camIt = camOptions.begin();
    }
}

void GameController::Initialize()
{
    GLFWwindow* window = WindowController::GetInstance().GetWindow();
    M_ASSERT(glewInit() == GLEW_OK, "Unable");
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glEnable(GL_CULL_FACE);

    camera = new Camera(
        WindowController::GetInstance().GetResolution(),
        { 100, 100, 2 }, { 0, 0, 0 }, { 0, 1, 0 }
    );
}

void GameController::RunGame()
{
    shader = new Shader();
    shader->LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
    mesh = new Mesh();
    mesh->Create(shader);

    GLFWwindow* window = WindowController::GetInstance().GetWindow();
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, key_callback);
    do {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            mesh->RotateWorld(0.01f, {1,0,0});
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            mesh->RotateWorld(-0.01f, { 0,1,0 });
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            mesh->RotateWorld(-0.01f, { 1,0,0 });
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            mesh->RotateWorld(0.01f, { 0,1,0 });
        }

        System::Windows::Forms::Application::DoEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        mesh->Render(camera->GetProjection() * camera->GetView());

        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (
        glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0
        );

    delete mesh;
    delete shader;
    delete camera;
}
