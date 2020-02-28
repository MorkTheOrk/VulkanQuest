//#include <vulkan/vulkan.h> // ENUMS, FUNCTIONS, STRUCTS FROM VULKAN
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h> // AUTO LOADS VULKAN
#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <vector>

class HelloTriangleApplication {
public:
	void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

private:
	const unsigned int WIDTH = 1920, HEIGHT = 1080;
	void initWindow() {
		glfwInit(); // init glfw functions

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // disable OpenGL
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // disable window resize

		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr); // create window with 1920x1080 and title Vulakn
	}
	void initVulkan() {
		createInstance();
	}

	void mainLoop() {
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}
	}

	void cleanup() {
		vkDestroyInstance(instance, nullptr);
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void createInstance() {
		// General program info
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Hello Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;
		// Creation info
		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		// Get Vulkan extensions with GLFW
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		// Print GLFW extensions
		std::cout << "GLFW extensions: " << std::endl;
		for (size_t i = 0; i < glfwExtensionCount; i++)
		{
			std::cout << "\t" << glfwExtensions[i] << std::endl;
		}

		createInfo.enabledLayerCount = 0;
		// create instance and check for success
		VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
		if (result != VK_SUCCESS)
			throw std::runtime_error("failed to create instance!");

		// Get vulkan extensions
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		// Store extention list in a vector and print them
		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

		std::cout << "Vulkan extensions:" << std::endl;

		for (const auto& extension : extensions)
		{
			std::cout << "\t" << extension.extensionName << std::endl;
		}
	}

	GLFWwindow* window;
	VkInstance instance;
};

int main() {
	HelloTriangleApplication app;

	try {
		app.run();
	}
	catch (const std::exception & e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}