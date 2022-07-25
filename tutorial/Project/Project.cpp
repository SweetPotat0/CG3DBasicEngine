#include "Project.h"
#include <iostream>

<<<<<<< Updated upstream
=======
std::vector<int> emptyVec;
Layer *defaultLayer = new Layer(true, "default", emptyVec);

static void printMat(const Eigen::Matrix4d &mat)
{
    std::cout << " matrix:" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            std::cout << mat(j, i) << " ";
        std::cout << std::endl;
    }
}

IGL_INLINE void Project::my_open_dialog_load_mesh()
{
    std::string fname = igl::file_dialog_open();

    if (fname.length() == 0)
        return;
>>>>>>> Stashed changes

static void printMat(const Eigen::Matrix4d& mat)
{
<<<<<<< Updated upstream
	std::cout<<" matrix:"<<std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout<< mat(j,i)<<" ";
		std::cout<<std::endl;
	}
=======
    std::vector<Eigen::Vector3f> points = {Eigen::Vector3f(4, 4, 0),
                                           Eigen::Vector3f(0, 20, 0),
                                           Eigen::Vector3f(-10, -10, -100),
                                           Eigen::Vector3f(4, 4, 0)};

    std::shared_ptr<ObjectMoverBezier> bez = std::make_shared<ObjectMoverBezier>(points, 0, 500);
    SceneShape *shape = AddGlobalShapeFromFile("file: " + indxFile++, mesh_file_name_string, -1);
    SetShapeShader(shape->getIndex(), 2);
    SetShapeMaterial(shape->getIndex(), 2);
    std::cout << "Load mesh from file: " << mesh_file_name_string << std::endl;
    return true;
>>>>>>> Stashed changes
}

Project::Project()
{
}

<<<<<<< Updated upstream
//Project::Project(float angle ,float relationWH, float near, float far) : Scene(angle,relationWH,near,far)
//{ 	
//}

void Project::Init()
{		
	unsigned int texIDs[3] = { 0 , 1, 2};
	unsigned int slots[3] = { 0 , 1, 2 };
	
	AddShader("shaders/pickingShader");
	AddShader("shaders/cubemapShader");
	AddShader("shaders/basicShaderTex");
	AddShader("shaders/basicShader");
	
	AddTexture("textures/plane.png",2);
	AddTexture("textures/cubemaps/Daylight Box_", 3);
	AddTexture("textures/grass.bmp", 2);
	//AddTexture("../res/textures/Cat_bump.jpg", 2);

	AddMaterial(texIDs,slots, 1);
	AddMaterial(texIDs+1, slots+1, 1);
	AddMaterial(texIDs + 2, slots + 2, 1);
	
	AddShape(Cube, -2, TRIANGLES);
	AddShape(zCylinder, -1, TRIANGLES);
	AddShape(zCylinder, 1, TRIANGLES);
	AddShape(zCylinder, 2, TRIANGLES);
	AddShape(Axis, -1, LINES);
	//AddShapeFromFile("../res/objs/Cat_v1.obj", -1, TRIANGLES);
	
	SetShapeShader(1, 2);
	SetShapeShader(2, 2);
	SetShapeShader(3, 2);
	SetShapeShader(4, 2);


	SetShapeMaterial(1, 0);
	SetShapeMaterial(2, 0);	
	SetShapeMaterial(3, 0);	
	SetShapeMaterial(4, 0);

	SetShapeMaterial(0, 1);


	selected_data_index = 0;
	float cylinderLen = 1.6f;
	float s = 60;
	ShapeTransformation(scaleAll, s,0);
	selected_data_index = 1;
	data()->SetCenterOfRotation(Eigen::Vector3d(0, 0, -cylinderLen / 2.0));
	ShapeTransformation(zTranslate, cylinderLen / 2.0, 1);
	
	selected_data_index = 2;
	ShapeTransformation(zTranslate, cylinderLen , 1);
	data()->SetCenterOfRotation(Eigen::Vector3d(0, 0, -cylinderLen / 2.0));
	
	selected_data_index = 3;
	ShapeTransformation(zTranslate, cylinderLen, 1);
	data()->SetCenterOfRotation(Eigen::Vector3d(0, 0, -cylinderLen / 2.0));

	selected_data_index = 0;
	SetShapeStatic(0);


	//SetShapeViewport(6, 1);
//	ReadPixel(); //uncomment when you are reading from the z-buffer
}

void Project::Update(const Eigen::Matrix4f& Proj, const Eigen::Matrix4f& View, const Eigen::Matrix4f& Model, unsigned int  shaderIndx, unsigned int shapeIndx)
{
	Shader *s = shaders[shaderIndx];
	int r = ((shapeIndx+1) & 0x000000FF) >>  0;
	int g = ((shapeIndx+1) & 0x0000FF00) >>  8;
	int b = ((shapeIndx+1) & 0x00FF0000) >> 16;


		s->Bind();
	s->SetUniformMat4f("Proj", Proj);
	s->SetUniformMat4f("View", View);
	s->SetUniformMat4f("Model", Model);
	if (data_list[shapeIndx]->GetMaterial() >= 0 && !materials.empty())
	{
//		materials[shapes[pickedShape]->GetMaterial()]->Bind(textures);
		BindMaterial(s, data_list[shapeIndx]->GetMaterial());
	}
	if (shaderIndx == 0)
		s->SetUniform4f("lightColor", r / 255.0f, g / 255.0f, b / 255.0f, 0.0f);
	else
		s->SetUniform4f("lightColor", 4/100.0f, 60 / 100.0f, 99 / 100.0f, 0.5f);
	//textures[0]->Bind(0);

	
	

	//s->SetUniform1i("sampler2", materials[shapes[pickedShape]->GetMaterial()]->GetSlot(1));
	//s->SetUniform4f("lightDirection", 0.0f , 0.0f, -1.0f, 0.0f);
//	if(shaderIndx == 0)
//		s->SetUniform4f("lightColor",r/255.0f, g/255.0f, b/255.0f,1.0f);
//	else 
//		s->SetUniform4f("lightColor",0.7f,0.8f,0.1f,1.0f);
	s->Unbind();
}

=======
Project::Project() {}

void Project::SetMenu(igl::opengl::glfw::imgui::ImGuiMenu *menu)
{
    this->menu = menu;
}

// Project::Project(float angle ,float relationWH, float near, float far) : Scene(angle,relationWH,near,far)
//{
// }

SceneShape *Project::AddGlobalShapeFromFile(std::string name, std::string file_name,
                                            int parent)
{
    int index = AddShapeFromFile(file_name, parent, TRIANGLES);
    SceneShape *scnShape = new SceneShape(name, MeshCopy, defaultLayer, index);
    // scnShape->setlastDrawnPosition(Eigen::Vector3f(0, 0, 0));
    shapesGlobal.push_back(scnShape);
    return scnShape;
}

SceneShape *Project::AddGlobalShape(std::string name, igl::opengl::glfw::Viewer::shapes shapeType,
                                    int parent, int viewPort = 0)
{

    int index = AddShape(shapeType, parent, TRIANGLES, viewPort);
    SceneShape *scnShape = new SceneShape(name, shapeType, defaultLayer, index);
    // scnShape->setlastDrawnPosition(Eigen::Vector3f(0, 0, 0));
    shapesGlobal.push_back(scnShape);
    return scnShape;
}

void Project::Init()
{
    layers.push_back(defaultLayer);
    globalTime = -1;
    unsigned int texIDs[4] = {0, 1, 2, 3};
    unsigned int slots[4] = {0, 1, 2, 3};
    int pickingShaderIndx = AddShader("shaders/pickingShader");
    int cubemapShaderIndx = AddShader("shaders/cubemapShader");
    int basicShaderIndx = AddShader("shaders/basicShader");

    unsigned int grassTexIndx = AddTexture("textures/grass.bmp", 2);
    unsigned int dayLightBoxTexIndx = AddTexture("textures/cubemaps/Daylight Box_", 3);
    unsigned int boxTexIndx = AddTexture("textures/box0.bmp", 2);
    unsigned int planeTexIndx = AddTexture("textures/plane.png", 2);

    int grass2DMatIndx = AddMaterial(&grassTexIndx, slots, 1);
    int dayLight3DMatIndx = AddMaterial(&dayLightBoxTexIndx, slots + 1, 1);

    int box2DMatIndx = AddMaterial(&boxTexIndx, slots + 2, 1);
    int plane2DMatIndx = AddMaterial(&planeTexIndx, slots + 3, 1);

    std::vector<Eigen::Vector3f> points = {Eigen::Vector3f(0, 0, 0),
                                           Eigen::Vector3f(0, 20, 0),
                                           Eigen::Vector3f(-10, -10, -100),
                                           Eigen::Vector3f(0, 0, 0)};

    std::vector<Eigen::Vector3f> pointsRev = {Eigen::Vector3f(0, 0, 0),
                                              Eigen::Vector3f(-10, -10, -100),
                                              Eigen::Vector3f(0, 20, 0),
                                              Eigen::Vector3f(0, 0, 0)};

    std::shared_ptr<ObjectMoverBezier> bez = std::make_shared<ObjectMoverBezier>(points, 0, 500);

    // Cube map -->

    SceneShape *cubeMap = AddGlobalShape("cubeMap", Cube, -2);
    SetShapeShader(cubeMap->getIndex(), cubemapShaderIndx);
    SetShapeMaterial(cubeMap->getIndex(), dayLight3DMatIndx);

    selected_data_index = cubeMap->getIndex();
    ShapeTransformation(scaleAll, 150, 0);
    SetShapeStatic(cubeMap->getIndex());

    cubeMapIndx = cubeMap->getIndex();

    // End cubeMap

    SceneShape *shp = AddGlobalShape("test", Cube, -1);

    SetShapeShader(shp->getIndex(), basicShaderIndx);
    SetShapeMaterial(shp->getIndex(), box2DMatIndx);

    SceneShape *shp1 = AddGlobalShape("test 1", Cube, -1);
    SetShapeShader(shp1->getIndex(), basicShaderIndx);
    SetShapeMaterial(shp1->getIndex(), box2DMatIndx);

    SceneShape *shp2 = AddGlobalShape("test 2", Cube, -1);
    SetShapeShader(shp2->getIndex(), basicShaderIndx);
    SetShapeMaterial(shp2->getIndex(), box2DMatIndx);

    // Picking plane -->

    SceneShape *pickingPlane = AddGlobalShape("Picking plane", Plane, 1);
    SetShapeShader(pickingPlane->getIndex(), pickingShaderIndx);
    SetShapeMaterial(pickingPlane->getIndex(), plane2DMatIndx);

    selected_data_index = pickingPlane->getIndex();
    ShapeTransformation(zTranslate, -1.1, 1);

    SetShapeStatic(pickingPlane->getIndex());

    // Picking plane End

    selected_data_index = cubeMapIndx;
    animating = true;

    // SetShapeViewport(6, 1);
    //	ReadPixel(); //uncomment when you are reading from the z-buffer
}

void Project::Update(const Eigen::Matrix4f &Proj, const Eigen::Matrix4f &View, const Eigen::Matrix4f &Model, unsigned int shaderIndx, unsigned int shapeIndx)
{
    ++globalTime;
    if (globalTime == 100)
    {
        //        std::list<int> x, y;
        //        const int DISPLAY_WIDTH = 1200;
        //        const int DISPLAY_HEIGHT = 800;
        //        x.push_back(DISPLAY_WIDTH);
        //        y.push_back(DISPLAY_HEIGHT);
        //        igl::opengl::glfw::imgui::ImGuiMenu* menu = new igl::opengl::glfw::imgui::ImGuiMenu();
        //        renderer->Init(this,x,y,1,menu);
    }
    Shader *s = shaders[shaderIndx];
    long time;
    if (animating)
        time = globalTime;
    else
        time = 0;
    int r = ((shapeIndx + 1) & 0x000000FF) >> 0;
    int g = ((shapeIndx + 1) & 0x0000FF00) >> 8;
    int b = ((shapeIndx + 1) & 0x00FF0000) >> 16;

    SceneShape *scnShape = shapesGlobal[shapeIndx];
    // Eigen::Vector3f pos = scnShape->getlastDrawnPosition();

    // Eigen::Vector3f newPos = scnShape->getPosition((float)time);
    // Eigen::Vector3f delta = newPos - pos;

    // pickedShapes = {scnShape.getIndex()};
    ShapeTransformation(xTranslate, delta[0], 0);
    ShapeTransformation(yTranslate, delta[1], 0);
    ShapeTransformation(zTranslate, delta[2], 0);
    // shapesGlobal[shapeIndx]->setlastDrawnPosition(newPos);
    // pickedShapes.clear();

    s->Bind();
    s->SetUniformMat4f("Proj", Proj);
    s->SetUniformMat4f("View", View);
    s->SetUniformMat4f("Model", Model);
    s->SetUniform2f("shapeId", 0, shapeIndx);
    if (data_list[shapeIndx]->GetMaterial() >= 0 && !materials.empty())
    {
        //		materials[shapes[pickedShape]->GetMaterial()]->Bind(textures);
        BindMaterial(s, data_list[shapeIndx]->GetMaterial());
    }
    if (shaderIndx == 0)
        s->SetUniform4f("lightColor", r / 255.0f, g / 255.0f, b / 255.0f, 0.0f);
    else
        s->SetUniform4f("lightColor", 4 / 100.0f, 60 / 100.0f, 99 / 100.0f, 0.5f);
    // textures[0]->Bind(0);

    // s->SetUniform1i("sampler2", materials[shapes[pickedShape]->GetMaterial()]->GetSlot(1));
    // s->SetUniform4f("lightDirection", 0.0f , 0.0f, -1.0f, 0.0f);
    //	if(shaderIndx == 0)
    //		s->SetUniform4f("lightColor",r/255.0f, g/255.0f, b/255.0f,1.0f);
    //	else
    //		s->SetUniform4f("lightColor",0.7f,0.8f,0.1f,1.0f);
    s->Unbind();
}
>>>>>>> Stashed changes

void Project::WhenRotate()
{
}

void Project::WhenTranslate()
{
}

void Project::Animate() {
    if(isActive)
	{
		if(selected_data_index > 0 )
			data()->MyRotate(Eigen::Vector3d(0, 1, 0), 0.01);
	}
}

void Project::ScaleAllShapes(float amt,int viewportIndx)
{
	for (int i = 1; i < data_list.size(); i++)
	{
		if (data_list[i]->Is2Render(viewportIndx))
		{
            data_list[i]->MyScale(Eigen::Vector3d(amt, amt, amt));
		}
	}
}

Project::~Project(void)
{
}

<<<<<<< Updated upstream
=======
void Project::SetRenderer(Renderer *renderer)
{
    if (this->renderer != nullptr)
        throw std::invalid_argument("renderer cannot be set twice");
    this->renderer = renderer;
}

void Project::SetParent(int shape, int newParent)
{
    shapesGlobal[shapesGlobal[shape]->getParent()->getIndex()]->removeChild(shapesGlobal[shape]);
    shapesGlobal[shape]->setParent(shapesGlobal[newParent]);
    shapesGlobal[newParent]->addChild(shapesGlobal[shape]);
}

int Project::GetParent(int shape)
{
    return shapesGlobal[shape]->getParent()->getIndex();
}

std::vector<int> Project::GetChildren(int shape)
{
    std::vector<int> indxs;
    std::vector<SceneShape *> childs = shapesGlobal[shape]->getChildren();
    for (size_t i = 0; i < childs.size(); i++)
    {
        indxs.push_back(childs[i]->getIndex());
    }
    return indxs;
}

void Project::Play()
{
    animating = !animating;
    globalTime = -1;
}
>>>>>>> Stashed changes
