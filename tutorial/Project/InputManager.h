#pragma once // maybe should be static class
#include "igl/opengl/glfw/Display.h"
#include "igl/opengl/glfw/renderer.h"
#include "Project.h"
#include "imgui/imgui.h"
#include "SceneShape.h"

bool holdsLeft;
double xStart, yStart;

float normelize(float num, int maxSize)
{
    return (((2 * num) / maxSize) - 1);
}

bool inside(float xStart, float yStart, float xEnd, float yEnd, float screenX, float screenY)
{
    if (xStart > xEnd)
    {
        float tmp = xStart;
        xStart = xEnd;
        xEnd = tmp;
    }
    if (yStart > yEnd)
    {
        float tmp = yStart;
        yStart = yEnd;
        yEnd = tmp;
    }
    bool goodX = xStart <= screenX && screenX <= xEnd;
    bool goodY = yStart <= screenY && screenY <= yEnd;
    return goodX && goodY;
}


// Zoom in objects
Eigen::Vector3f FindCenterOfPickedObjects(Project* scn) {

    int shapesCount = scn->pickedShapes.size();
    if (shapesCount > 0) {
        float xVals = 0;
        float yVals = 0;
        float zVals = 0;
        for (auto shape : scn->shapesGlobal) { // chaneg to picked shapes
            Eigen::Vector3f shapePos = shape.getPosition(0);
            xVals += shapePos.x();
            yVals += shapePos.y();
            zVals += shapePos.z();
        }
        return Eigen::Vector3f(xVals / shapesCount, yVals / shapesCount, zVals / shapesCount);
    }
    return Eigen::Vector3f(0, 0, 0);
}

// Viewport coords, normalized:
//
//  -1 -->       0 -->         1
//  ---------------------------- -1
//  -                          -
//  -                          -  |
//  -                          -  v
//  -                          -
//  -                          -  0
//  -                          -
//  -                          -  |
//  -                          -  v
//  -                          -
//  ----------------------------  1

// TODO check projection in point Mult scale/ratio
//float xAngleShit(Renderer* rnd){
//    float angle = rnd->getCameraAngle(0, x);
//    float near = rnd->getCameraNear(0);
//    if (angle<0){
//        return -near * tan(abs(angle));
//    }
//    return near * tan(angle);
//}
//
//float yAngleShit(Renderer* rnd){
//    float angle = rnd->getCameraAngle(0, y);
//    float near = rnd->getCameraNear(0);
//    if (angle<0){
//        return -near * tan(abs(angle));
//    }
//    return near * tan(angle);
//}


void movePickedObjects(double shiftSize, directions d ,Project* scn){
    for ( int i : scn->pShapes) {
        scn->shapesGlobal[i].move(shiftSize,d);
    }
}

void glfw_mouse_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {

        Renderer *rndr = (Renderer *)glfwGetWindowUserPointer(window);
        Project *scn = (Project *)rndr->GetScene();
        if (button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            rndr->Pressed();
            glfwGetCursorPos(window, &xStart, &yStart);
        }
        rndr->UpdatePress(xStart, yStart);
    }
    else
    {
        Renderer *rndr = (Renderer *)glfwGetWindowUserPointer(window);
        Project *scn = (Project *)rndr->GetScene();

        if (button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            rndr->UnPick(2);
            double xEnd, yEnd;
            glfwGetCursorPos(window, &xEnd, &yEnd);
            rndr->PickMany(2);
            rndr->Pressed();
        }
    }
}

void glfw_scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    Renderer *rndr = (Renderer *)glfwGetWindowUserPointer(window);
    Project *scn = (Project *)rndr->GetScene();

    if (rndr->IsPicked())
    {
        rndr->UpdateZpos((int)yoffset);
        rndr->MouseProccessing(GLFW_MOUSE_BUTTON_MIDDLE);
    }
    else
    {
        rndr->MoveCamera(0, rndr->zTranslate, (float)yoffset);
    }
}

void glfw_cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    Renderer *rndr = (Renderer *)glfwGetWindowUserPointer(window);
    Project *scn = (Project *)rndr->GetScene();
    double xStart, yStart;

    rndr->UpdatePosition((float)xpos, (float)ypos);

    if (rndr->CheckViewport(xpos, ypos, 0))
    {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            rndr->UnPick(2);
            glfwGetCursorPos(window, &xStart, &yStart);
            if (!rndr->IsPressed())
            {
                rndr->Pressed();
            }
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {

            rndr->MouseProccessing(GLFW_MOUSE_BUTTON_LEFT);
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE && rndr->IsPressed())
        {
            double xEnd, yEnd;
            glfwGetCursorPos(window, &xEnd, &yEnd);
            rndr->PickMany(2);
            scn->pickedShapes = scn->pShapes;
            rndr->Pressed();
        }
    }
}

void glfw_window_size_callback(GLFWwindow *window, int width, int height)
{
    Renderer *rndr = (Renderer *)glfwGetWindowUserPointer(window);

    rndr->resize(window, width, height);
}

void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Renderer *rndr = (Renderer *)glfwGetWindowUserPointer(window);
    Project *scn = (Project *)rndr->GetScene();
    // rndr->FreeShapes(2);
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;

        case GLFW_KEY_SPACE:
            if (scn->IsActive())
                scn->Deactivate();
            else
                scn->Activate();
            break;

        case GLFW_KEY_UP:
            rndr->MoveCamera(0, scn->xRotate, 0.05f);

            break;
        case GLFW_KEY_DOWN:
            // scn->shapeTransformation(scn->xGlobalRotate,-5.f);
            // cout<< "down: "<<endl;
            rndr->MoveCamera(0, scn->xRotate, -0.05f);
            break;
        case GLFW_KEY_LEFT:
            rndr->MoveCamera(0, scn->yRotate, 0.05f);
            break;
        case GLFW_KEY_RIGHT:
            // scn->shapeTransformation(scn->xGlobalRotate,-5.f);
            // cout<< "down: "<<endl;
            rndr->MoveCamera(0, scn->yRotate, -0.5f);
            break;
        case GLFW_KEY_U:
            rndr->MoveCamera(0, scn->yTranslate, 0.25f);
            break;
        case GLFW_KEY_D:
//            rndr->MoveCamera(0, scn->yTranslate, -0.25f);
            movePickedObjects(0.02,x,scn);
            break;
        case GLFW_KEY_A:
            movePickedObjects(-0.02,x,scn);
            break;
        case GLFW_KEY_W:
            movePickedObjects(0.02,y,scn);
            break;
        case GLFW_KEY_S:
            movePickedObjects(-0.02,y,scn);
            break;
        case GLFW_KEY_L:
            rndr->MoveCamera(0, scn->xTranslate, -0.25f);
            break;
        case GLFW_KEY_K:
            scn->NextCubeMap();
            break;
        case GLFW_KEY_R:
            rndr->MoveCamera(0, scn->xTranslate, 0.25f);
            break;

        case GLFW_KEY_B:
            rndr->MoveCamera(0, scn->zTranslate, 0.5f);
            break;
        case GLFW_KEY_F:
            rndr->MoveCamera(0, scn->zTranslate, -0.5f);
            break;
        case GLFW_KEY_O: {
            Eigen::Vector3f center = FindCenterOfPickedObjects(scn);
            rndr->MoveCamera(0, 100, 0);
            //rndr->TranslateCamera(center);
            /*if (!scn->pickedShapes.empty())
                std::cout << scn->pickedShapes.front() << std::endl;*/
            //rndr->MoveCamera(0, scn->zTranslate, -0.5f);
            break;
        }
        case GLFW_KEY_1:
            movePickedObjects(0.02,z,scn);
            break;
        case GLFW_KEY_2:
            movePickedObjects(-0.02,z,scn);
            break;
        case GLFW_KEY_3:
            scn->selected_data_index = 3;
            break;
        default:
            break;
        }
    }
}

void Init(Display &display, igl::opengl::glfw::imgui::ImGuiMenu *menu)
{
    display.AddKeyCallBack(glfw_key_callback);
    display.AddMouseCallBacks(glfw_mouse_callback, glfw_scroll_callback, glfw_cursor_position_callback);
    display.AddResizeCallBack(glfw_window_size_callback);
    menu->init(&display);
}
