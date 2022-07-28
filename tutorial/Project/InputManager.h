#pragma once // maybe should be static class
#include "igl/opengl/glfw/Display.h"
#include "igl/opengl/glfw/renderer.h"
#include "Project.h"
#include "imgui/imgui.h"
#include "SceneShape.h"

bool holdsLeft;
double xStart, yStart;
//0=LEFT/UP, 1=RIGHT/DOWN
int ChosenScreen = 0;

float normelize(float num, int maxSize)
{
    return (((2 * num) / maxSize) - 1);
}

// Zoom in objects
Eigen::Vector3f FindCenterOfPickedObjects(Project *scn)
{
    float zoomInCenter = 4;
    int shapesCount = scn->pShapes.size();

    if (shapesCount > 0)
    {

        Eigen::Vector3f averagePos = Eigen::Vector3f(0, 0, 0);

        for (int shapeIndex : scn->pShapes)
        { // chaneg to picked shapes
            averagePos += scn->shapesGlobal[shapeIndex].getCurrentPosition();
        }
        averagePos /= shapesCount;
        averagePos -= Eigen::Vector3f(0, 0, zoomInCenter);

        return averagePos;
    }
    return Eigen::Vector3f(0, 0, 0);
}

void scalePickedObjects(double shiftSize, directions d, Project *scn)
{
    for (int i : scn->pShapes)
    {
        scn->shapesGlobal[i].Scale(shiftSize, d);
    }
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
// float xAngleShit(Renderer* rnd){
//    float angle = rnd->getCameraAngle(0, x);
//    float near = rnd->getCameraNear(0);
//    if (angle<0){
//        return -near * tan(abs(angle));
//    }
//    return near * tan(angle);
//}
//
// float yAngleShit(Renderer* rnd){
//    float angle = rnd->getCameraAngle(0, y);
//    float near = rnd->getCameraNear(0);
//    if (angle<0){
//        return -near * tan(abs(angle));
//    }
//    return near * tan(angle);
//}

void movePickedObjects(double shiftSize, directions d, Project *scn)
{
    for (int i : scn->pShapes)
    {
        scn->shapesGlobal[i].move(shiftSize, d);
        // void handlePicking(double xStart, double yStart, double xEnd, double yEnd, Project *scn, Renderer *rndr)
        // {
        //     xStart = normelize(xStart, rndr->getViewPortWidth(0));
        //     xEnd = normelize(xEnd, rndr->getViewPortWidth(0));
        //     yStart = normelize(yStart, rndr->getViewPortHeight(0));
        //     yEnd = normelize(yEnd, rndr->getViewPortHeight(0));
        //     std::cout << "(xS,yS): (" << xStart << "," << yStart << "), (xE,yE): (" << xEnd << "," << yEnd << ")" << std::endl;
        //     for (auto shape : scn->pickedShapes)
        //     {
        //         scn->SetShapeViewport(shape, -3);
        //     }
        //     scn->pickedShapes.clear();
        //     Eigen::Matrix4f projection = rndr->GetProjection(0);
        //     for (auto shape : scn->shapesGlobal)
        //     {
        //         if (shape.getIndex() != scn->cubeMapIndx && shape.getIndex() != scn->pickingPlaneIndx)
        //         {
        //             Eigen::Vector3f pos = shape.getPosition(0);
        //             Eigen::Vector4f posVec = Eigen::Vector4f(pos.x(), pos.y(), pos.z(), 1);
        //             Eigen::Vector4f res = projection * posVec;
        //             float screenX, screenY;
        //             screenX = res.x();
        //             screenY = res.y();
        //             if (inside(xStart, yStart, xEnd, yEnd, screenX, screenY))
        //             {
        //                 scn->SetShapeViewport(shape.getIndex(), 3);
        //                 scn->pickedShapes.push_back(shape.getIndex());
        //             }
        //         }
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
            rndr->UnPick(3);
            double xEnd, yEnd;
            glfwGetCursorPos(window, &xEnd, &yEnd);
            rndr->PickMany(3);
            rndr->Pressed();
        }
    }
}

void glfw_scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    Renderer *rndr = (Renderer *)glfwGetWindowUserPointer(window);
    Project *scn = (Project *)rndr->GetScene();

    //Set chosen camera
    //If chosen screen is 0, than we need viewport 0 so drawinfo 1=1+0 is still valid,
    //and if screen is 1 than we need draw info 2 = 1+1
    int ChosenCamera = scn->GetRenderer()->GetDrawCamera(ChosenScreen+1);

    if (rndr->IsPicked())
    {
        std::cout<<"picked!"<<std::endl;
        rndr->UpdateZpos((int)yoffset);
        rndr->MouseProccessing(GLFW_MOUSE_BUTTON_MIDDLE);
    }
    else
    {
        std::cout<<"not picked!"<<std::endl;
        rndr->MoveCamera(ChosenCamera, rndr->zTranslate, (float)yoffset);
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
            std::cout<<"Unpick"<<std::endl;
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

    //Set chosen camera
    //If chosen screen is 0, than we need viewport 0 so drawinfo 1=1+0 is still valid,
    //and if screen is 1 than we need draw info 2 = 1+1
    int ChosenCamera = scn->GetRenderer()->GetDrawCamera(ChosenScreen+1);
    
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
            rndr->MoveCamera(ChosenCamera, scn->xRotate, 0.05f);

            break;
        case GLFW_KEY_DOWN:
            // scn->shapeTransformation(scn->xGlobalRotate,-5.f);
            // cout<< "down: "<<endl;
            rndr->MoveCamera(ChosenCamera, scn->xRotate, -0.05f);
            break;
        case GLFW_KEY_LEFT:
            rndr->MoveCamera(ChosenCamera, scn->yRotate, 0.05f);
            break;
        case GLFW_KEY_RIGHT:
            // scn->shapeTransformation(scn->xGlobalRotate,-5.f);
            // cout<< "down: "<<endl;
            rndr->MoveCamera(ChosenCamera, scn->yRotate, -0.5f);
            break;
        case GLFW_KEY_U:
            rndr->MoveCamera(0, scn->yTranslate, 0.25f);
            break;
        case GLFW_KEY_D:
            //            rndr->MoveCamera(0, scn->yTranslate, -0.25f);
            movePickedObjects(0.02, x, scn);
            break;
        case GLFW_KEY_A:
            movePickedObjects(-0.02, x, scn);
            break;
        case GLFW_KEY_W:
            movePickedObjects(0.02, y, scn);
            break;
        case GLFW_KEY_S:
            movePickedObjects(-0.02, y, scn);
            break;
        case GLFW_KEY_L:
            rndr->MoveCamera(ChosenCamera, scn->xTranslate, -0.25f);
            break;
        case GLFW_KEY_K:
            scn->NextCubeMap();
            break;
        case GLFW_KEY_R:
            rndr->MoveCamera(ChosenCamera, scn->xTranslate, 0.25f);
            break;

        case GLFW_KEY_B:
            rndr->MoveCamera(ChosenCamera, scn->zTranslate, 0.5f);
            break;
        case GLFW_KEY_F:
            rndr->MoveCamera(ChosenCamera, scn->zTranslate, -0.5f);
            break;
        case GLFW_KEY_T:
        {
            rndr->MoveCamera(ChosenCamera, 100, 0);
            break;
        }
        case GLFW_KEY_O:
        {
            Eigen::Vector3f center = FindCenterOfPickedObjects(scn);
            rndr->MoveCamera(ChosenCamera, 100, 0);
            rndr->MoveCamera(ChosenCamera, scn->xTranslate, center.x());
            rndr->MoveCamera(ChosenCamera, scn->yTranslate, center.y());
            rndr->MoveCamera(ChosenCamera, scn->zTranslate, center.z());
            /*if (!scn->pickedShapes.empty())
                std::cout << scn->pickedShapes.front() << std::endl;*/
            // rndr->MoveCamera(0, scn->zTranslate, -0.5f);
            break;
        }
        case GLFW_KEY_X:
            movePickedObjects(+0.02, z, scn);
            break;
        case GLFW_KEY_Z:
            movePickedObjects(-0.02, z, scn);
            break;
        case GLFW_KEY_1:
            scalePickedObjects(1.1, x, scn);
            break;
        case GLFW_KEY_2:
            scalePickedObjects(0.9, x, scn);
            break;
        case GLFW_KEY_3:
            scalePickedObjects(1.1, y, scn);
            break;
        case GLFW_KEY_4:
            scalePickedObjects(0.9, y, scn);
            break;
        case GLFW_KEY_5:
            scalePickedObjects(1.1, z, scn);
            break;
        case GLFW_KEY_6:
            scalePickedObjects(0.9, z, scn);
            break;
        case GLFW_KEY_EQUAL:
            scalePickedObjects(1.1, w, scn);
            break;
        case GLFW_KEY_MINUS:
            std::cout << "minus" << std::endl;
            scalePickedObjects(0.9, w, scn);
            break;
        case GLFW_KEY_LEFT_SHIFT:
            ChosenScreen = 0;
            break;
        case GLFW_KEY_RIGHT_SHIFT:
            ChosenScreen = 1;
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
