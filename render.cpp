#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Define a 3D point
struct Point3D
{
    float x, y, z;
};

// Define a 2D point
struct Point2D
{
    float x, y;
};

// Define a cube with 8 vertices
std::vector<Point3D> cubeVertices = {
    {-1, -1, -1},
    {1, -1, -1},
    {1, 1, -1},
    {-1, 1, -1},
    {-1, -1, 1},
    {1, -1, 1},
    {1, 1, 1},
    {-1, 1, 1}};

// Define edges of the cube
std::vector<std::pair<int, int>> cubeEdges = {
    {0, 1},
    {1, 2},
    {2, 3},
    {3, 0},
    {4, 5},
    {5, 6},
    {6, 7},
    {7, 4},
    {0, 4},
    {1, 5},
    {2, 6},
    {3, 7}};

// Function to project 3D point to 2D point
Point2D project(Point3D point, float angleX, float angleY, float angleZ)
{
    // Rotate around X axis
    float y = point.y * cos(angleX) - point.z * sin(angleX);
    float z = point.y * sin(angleX) + point.z * cos(angleX);
    point.y = y;
    point.z = z;

    // Rotate around Y axis
    float x = point.x * cos(angleY) + point.z * sin(angleY);
    z = -point.x * sin(angleY) + point.z * cos(angleY);
    point.x = x;
    point.z = z;

    // Rotate around Z axis
    x = point.x * cos(angleZ) - point.y * sin(angleZ);
    y = point.x * sin(angleZ) + point.y * cos(angleZ);
    point.x = x;
    point.y = y;

    // Project to 2D
    Point2D projected;
    projected.x = point.x / (point.z + 5) * (600.0 / 800);
    projected.y = point.y / (point.z + 5);
    return projected;

    // Point2D projected;
    // projected.x = point.x * 0.5;
    // projected.y = point.y * 0.5;
    // return projected;
}

// Function to draw a line
void drawLine(const Point2D &p1, const Point2D &p2)
{
    GLfloat vertices[] = {
        p1.x, p1.y, 0.0f,
        p2.x, p2.y, 0.0f};

    // Enable vertex arrays
    glEnableClientState(GL_VERTEX_ARRAY);

    // Set vertex pointer
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    // Draw the line
    glDrawArrays(GL_LINES, 0, 2);

    // Disable vertex arrays
    glDisableClientState(GL_VERTEX_ARRAY);
}

// Function to draw the cube
void drawCube(float angleX, float angleY, float angleZ)
{
    std::vector<Point2D> projectedVertices;
    for (const auto &vertex : cubeVertices)
    {
        projectedVertices.push_back(project(vertex, angleX, angleY, angleZ));
    }

    // // Clear the screen
    // system("cls");

    // Draw edges
    for (const auto &edge : cubeEdges)
    {
        Point2D p1 = projectedVertices[edge.first];
        Point2D p2 = projectedVertices[edge.second];

        // Clear the color buffer
        drawLine(p1, p2);

        // std::cout << "Line from (" << p1.x << ", " << p1.y << ") to (" << p2.x << ", " << p2.y << ")\n";
    }
}

void initOpenGL()
{
    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Set the viewport
    glViewport(0, 0, 800, 600);

    // Set the clear color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

// Function to draw a line
void drawLine(float x1, float y1, float x2, float y2)
{
    GLfloat vertices[] = {
        x1, y1, 0.0f,
        x2, y2, 0.0f};

    // Enable vertex arrays
    glEnableClientState(GL_VERTEX_ARRAY);

    // Set vertex pointer
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    // Draw the line
    glDrawArrays(GL_LINES, 0, 2);

    // Disable vertex arrays
    glDisableClientState(GL_VERTEX_ARRAY);
}

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow *window = glfwCreateWindow(800, 600, "Empty Window", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize OpenGL
    initOpenGL();

    float angleX = 0, angleY = 0, angleZ = 0;
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        drawCube(angleX, angleY, angleZ);
        angleX += 0.002f;
        angleY += 0.01f;
        // angleZ += 0.01f;

        // // Clear the color buffer

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();

        // drawLine(-0.5, 0.0, 0.5, 0);
        Sleep(1 / 120);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    // Clean up and exit
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
