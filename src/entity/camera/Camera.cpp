#include "Camera.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>


        Camera::Camera(int width, int height, glm::vec3 position){
            Camera::width = width;
            Camera::height = height;
            Position = position;
        }

        void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader&shader, const char* uniform){
            // Initializes matrices since otherwise they will be the null matrix
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection = glm::mat4(1.0f);

            // Makes camera look in the right direction from the right position
            view = glm::lookAt(Position, Position + Orientation, Up);
            // Adds perspective to the scene
            projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

            // Exports the camera matrix to the Vertex Shader
            glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
        }

        
        void Camera::Inputs(GLFWwindow* window){

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
                Position += speed * Orientation;
            }
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
                Position += speed * -glm::normalize(glm::cross(Orientation, Up));
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
                Position += speed * -Orientation;
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
                Position += speed * glm::normalize(glm::cross(Orientation, Up));;
            }

            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
                Position += speed * Up;
            }
            if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
                Position += speed * -Up;
            }        

            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
                speed = 0.05f;
            }
            else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE){
                speed = 0.01f;
            }    



            if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
                if ( !pausePressedLastFrame) {
                    paused = !paused;  // Toggle only when key is first pressed
                    std::cout << "pause Toggled\n";
                }

                pausePressedLastFrame = true;
                
            }else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE){
                pausePressedLastFrame = false;
            }
            if (glfwGetKey(window, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS){
                if (!debugPressedLastFrame) {
                    debugEnabled = !debugEnabled;  // Toggle only when key is first pressed
                    std::cout << "debug Toggled\n";
                }

                debugPressedLastFrame = true;
                
            }else if (glfwGetKey(window, GLFW_KEY_GRAVE_ACCENT) == GLFW_RELEASE){
                debugPressedLastFrame = false;
            }
            
            

            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
                if (firstClick)
                {
                    mouseLocked = true;
                }
            }    

            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){

                double mouseX;
                double mouseY;

                glfwGetCursorPos(window, &mouseX, &mouseY);

                float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
                float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

                glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

                if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
                {
                    Orientation = newOrientation;
                }

                Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

                glfwSetCursorPos(window, (width /2 ), (height/2));
            }    

            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                mouseLocked = false;
                firstClick = true;
            }    
        }