#include <app.h>

const float APP_WIDTH = 800.0;
const float APP_HEIGHT = 600.0;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float speed = 10.0f;

Spectator spectator;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

int main()
{

#pragma region init

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

	glViewport(0, 0, APP_WIDTH, APP_HEIGHT);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

#pragma endregion

#pragma region objects

	unsigned int indices[] = {
        //Top
        7, 6, 2,
        2, 3, 7,

        //Bottom
        0, 4, 5,
        5, 1, 0,

        //Left
        0, 2, 6,
        6, 4, 0,

        //Right
        7, 3, 1,
        1, 5, 7,

        //Front
        3, 2, 0,
        0, 1, 3,

        //Back
        4, 6, 7,
        7, 5, 4
    };


    float vertices[] = {
        -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, //0
         0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, //1
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, //2
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, //3
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, //4
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, //5
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, //6
         0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f  //7
    };

	std::vector<unsigned int> cubePositions;

	for (unsigned int i = 0; i < 1000000; i++)
	{
		cubePositions.push_back(1);
	}

	std::vector<glm::mat4> cubeTranslations;
	float cubeX = 0.0f;
	float cubeZ = 0.0f;
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int rowEnd = 1000;
	while (i < cubePositions.size())
	{
		while (j < rowEnd)
		{
			if (cubePositions[j])
				cubeTranslations.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(cubeX, 0.0f, cubeZ)));
			cubeX += 1.0f;
			i++;
			j++;
		}
		cubeX = 0.0f;
		cubeZ += 1.0f;
		rowEnd += 1000;
		i++;
	}

#pragma endregion

#pragma region VAO setup

	unsigned int VBO, instanceVBO, VAO, EBO;

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &instanceVBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // xyz
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // color
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, cubeTranslations.size() * sizeof(glm::mat4), &(cubeTranslations[0]), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);

	glBindVertexArray(0);

#pragma endregion

#pragma region textures

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;

	for(unsigned int i = 0; i < 6; i++)
	{
		unsigned char* data = stbi_load("../../../resources/textures/cubemap.png", &width, &height, &nrChannels, 0);
		if(data) 
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else 
		{
			std::cout << "Failed to load texture\n";
		}
		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

#pragma endregion

#pragma region shaders

	Shader shaders("../../../resources/shaders/vertexShader.vert",
				   "../../../resources/shaders/fragmentShader.frag");

#pragma endregion

#pragma region opengl features

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

#pragma endregion

#pragma region main loop

	while (!glfwWindowShouldClose(window)) {

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processKeys(window, spectator.cameraPosition, spectator.cameraFront, spectator.cameraUp, speed, deltaTime);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

        view = glm::lookAt(spectator.cameraPosition, spectator.cameraPosition + spectator.cameraFront, spectator.cameraUp);
        projection = glm::perspective(glm::radians(spectator.fov), APP_WIDTH / APP_HEIGHT, 1.0f, 10000.0f);

        shaders.setMat4("view", view);
        shaders.setMat4("projection", projection);

		shaders.use();
		glBindVertexArray(VAO);
		glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, 1000000);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

#pragma endregion

#pragma region cleaning

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &instanceVBO);
	glDeleteBuffers(1, &EBO);

#pragma endregion

	glfwTerminate();
	return 0;
}

#pragma region callbacks

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, APP_WIDTH, APP_HEIGHT);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    spectator.processCursor(xposIn, yposIn);
}

#pragma endregion