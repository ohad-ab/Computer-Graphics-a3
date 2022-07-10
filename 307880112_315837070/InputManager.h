#pragma once   //maybe should be static class
#include "display.h"
#include "renderer.h"
#include "game.h"


	void mouse_callback(GLFWwindow* window,int button, int action, int mods)
	{	
		Renderer* rndr = (Renderer*)glfwGetWindowUserPointer(window);
		Game* scn = (Game*)rndr->GetScene();
		if(action == GLFW_PRESS )
		{
			
			double x2,y2;
			glfwGetCursorPos(window,&x2,&y2);
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
			{
				if (rndr->Picking((int)x2, (int)y2))
				{
					printf("picked\n");
					rndr->UpdatePosition(x2, y2);
				}
			}
		}
	}
	
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		Renderer* rndr = (Renderer*)glfwGetWindowUserPointer(window);
		Game* scn = (Game*)rndr->GetScene();
		printf("scroll\n");
		//scn->MyScale(glm::vec3(4,4,4));
		//scn->ScrollProccessing(xoffset, yoffset);
		rndr->MoveCamera(0, 2, -yoffset);
	}
	
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Renderer* rndr = (Renderer*)glfwGetWindowUserPointer(window);
		Game* scn = (Game*)rndr->GetScene();

		rndr->UpdatePosition((float)xpos,(float)ypos);

			//if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
			//{

			//	if (rndr->Picking((int)xpos, (int)ypos))
			//		;//rndr->MouseProccessing(GLFW_MOUSE_BUTTON_RIGHT);
			//}
			//else 
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			{
				rndr->MouseProccessing(GLFW_MOUSE_BUTTON_LEFT);
			}

	}

	void window_size_callback(GLFWwindow* window, int width, int height)
	{
		Renderer* rndr = (Renderer*)glfwGetWindowUserPointer(window);
		
		rndr->Resize(width,height);
		
	}
	
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Renderer* rndr = (Renderer*)glfwGetWindowUserPointer(window);
		Game* scn = (Game*)rndr->GetScene();

		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			switch (key)
			{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GLFW_TRUE);
				break;
			case GLFW_KEY_R:
				scn->KeyProccessing(GLFW_KEY_R);

				break;
			case GLFW_KEY_U:
				scn->KeyProccessing(GLFW_KEY_U);
				break;
			case GLFW_KEY_L:
				scn->KeyProccessing(GLFW_KEY_L);
				break;
			case GLFW_KEY_D:
				scn->KeyProccessing(GLFW_KEY_D);
				break;
			case GLFW_KEY_B:
				scn->KeyProccessing(GLFW_KEY_B);
				break;
			case GLFW_KEY_F:
				scn->KeyProccessing(GLFW_KEY_F);
				break;
			case GLFW_KEY_Z:
				scn->KeyProccessing(GLFW_KEY_Z);
				break;
			case GLFW_KEY_A:
				scn->KeyProccessing(GLFW_KEY_A);
				break;
			case GLFW_KEY_M:
				scn->KeyProccessing(GLFW_KEY_M);
				break
			;case GLFW_KEY_SPACE:
				scn->KeyProccessing(GLFW_KEY_SPACE);
				break;

			default:
				break;
			}
		}
	}

	void Init(Display &display)
	{
		display.AddKeyCallBack(key_callback);
		display.AddMouseCallBacks(mouse_callback,scroll_callback,cursor_position_callback);
		display.AddResizeCallBack(window_size_callback);
	}
