#include <app.h>

const float APP_WIDTH = 1280.0;
const float APP_HEIGHT = 800.0;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float speed = 10.0f;

Spectator spectator;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(APP_WIDTH, APP_HEIGHT, "Demo3D", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create a GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    // stbi_set_flip_vertically_on_load(true);

    Model glados("../../../resources/models/glados/scene.gltf");

    Cubemap skybox;

    Shader model_shaders(
        "../../../resources/shaders/vertexShader.vert",
        "../../../resources/shaders/fragmentShader.frag"
    );

    Shader skybox_shaders(
        "../../../resources/shaders/skyboxVertexShader.vert",
        "../../../resources/shaders/skyboxFragmentShader.frag"
    );
    skybox_shaders.setInt("skybox", 0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    while (!glfwWindowShouldClose(window)) {

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // ImGui::ShowDemoWindow();

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processKeys(window, spectator.cameraPosition, spectator.cameraFront, spectator.cameraUp, speed, deltaTime);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
        view = glm::lookAt(spectator.cameraPosition, spectator.cameraPosition + spectator.cameraFront, spectator.cameraUp);
        projection = glm::perspective(glm::radians(spectator.fov), APP_WIDTH / APP_HEIGHT, 0.1f, 1000.0f);

        model_shaders.use();
        model_shaders.setMat4("model", model);
        model_shaders.setMat4("view", view);
        model_shaders.setMat4("projection", projection);

        glados.drawModel(model_shaders);

        view = glm::mat4(glm::mat3(glm::lookAt(spectator.cameraPosition, spectator.cameraPosition + spectator.cameraFront, spectator.cameraUp)));

        skybox_shaders.use();
        skybox_shaders.setMat4("view", view);
        skybox_shaders.setMat4("projection", projection);

        skybox.drawCubemap();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, APP_WIDTH, APP_HEIGHT);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    spectator.processCursor(xposIn, yposIn);
}
