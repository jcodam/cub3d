#include <stdio.h>
#include <math.h>

// Define the map dimensions
#define MAP_WIDTH 8
#define MAP_HEIGHT 8

// Define map data
int map[MAP_WIDTH][MAP_HEIGHT] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
};

int raycast(int playerX, int playerY, float playerAngle) {
    // Define the step size for the ray
    float stepSize = 0.1;

    // Calculate the ray's direction vector
    float rayDirX = cos(playerAngle);
    float rayDirY = sin(playerAngle);

    // Initialize the starting position
    float posX = playerX;
    float posY = playerY;

    // Raycasting loop
    while (1) {
        // Increment the position along the ray direction
        posX += rayDirX * stepSize;
        posY += rayDirY * stepSize;

        // Check if the ray hit a wall
        int mapX = (int)posX;
        int mapY = (int)posY;
        if (map[mapX][mapY] == 1) {
            // Ray hit a wall, return the distance to the wall
            float distance = sqrt((posX - playerX) * (posX - playerX) + (posY - playerY) * (posY - playerY));
            return distance;
        }
    }

    return -1; // Ray didn't hit anything
}

int main() {
    // Player's position and angle
    int playerX = 3;
    int playerY = 5;
    float playerAngle = 19.0;

    // Perform raycasting
    float distanceToWall = raycast(playerX, playerY, playerAngle);

    // Print the result
    printf("Distance to wall: %f\n", distanceToWall);

    return 0;
}
