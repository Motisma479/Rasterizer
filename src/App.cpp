#include <App.hpp>
#include <Renderer.hpp>
#include <Framebuffer.hpp>
#include <Camera.hpp>

#include<cstring>

using namespace sMatrix;

//Get back Events and setup ImGUI frame
void App::NewFrame(bool mouseCaptured)
{
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    if (mouseCaptured)
        ImGui::GetIO().MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
    ImGui::NewFrame();
}

//Clear buffer et render ImGUI
void App::EndFrame()
{
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}

//Constructor with Init struct
App::App(const AppInit& p_init)
{
    // Setup glfw
    glfwSetErrorCallback(p_init.ErrorCallback);
    if (!glfwInit())
    {
        printf("glfwInit failed\n");
        state = GLFWFAILED;
        return;
    }

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    window = glfwCreateWindow(p_init.width, p_init.height, p_init.title, nullptr, nullptr);
    if (window == nullptr)
    {
        printf("glfwCreateWindow failed\n");
        state = WINDOWFAILED;
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // V-Sync
    
    // Setup glad
    if (gladLoadGL((GLADloadfunc)glfwGetProcAddress) == 0)
    {
        printf("gladLoaderLoadGL failed\n");
        state = GLADFAILED;
        return;
    }

    // Setup KHR debug
    if (GLAD_GL_KHR_debug)
    {
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(p_init.DebugMessageCallback, NULL);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_PERFORMANCE, GL_DONT_CARE, 0, nullptr, GL_FALSE);
        glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_OTHER, GL_DONT_CARE, 0, nullptr, GL_FALSE);
    }

    printf("GL_VENDOR: %s\n", glGetString(GL_VENDOR));
    printf("GL_VERSION: %s\n", glGetString(GL_VERSION));
    printf("GL_RENDERER: %s\n", glGetString(GL_RENDERER));

    // Setup Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    state = SUCCESS;

    //load Texture
        scene.loadTexture("assets/SUS.png");
        scene.loadTexture("assets/crate.png");
    //-----------
}

void App::ScreenResetWidth(){
    width = 1600;
}
void App::ScreenResetHeight(){
    height = 1000;
}

bool ButtonCenteredOnLine(const char* label, float alignment = 0.5f) {
    ImGuiStyle& style = ImGui::GetStyle();
    float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
    float avail = ImGui::GetContentRegionAvail().x;
    float off = (avail - size) * alignment;

    if (off > 0.0f)
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
    return ImGui::Button(label);
}

bool CheckBoxCenteredOnLine(const char* label, bool* v, float alignment = 0.5f) {
    ImGuiStyle& style = ImGui::GetStyle();
    float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
    float avail = ImGui::GetContentRegionAvail().x;
    float off = (avail - size) * alignment;

    if (off > 0.0f)
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
    return ImGui::Checkbox(label, v);
}

bool ComboCenteredOnLine(const char* label, int* current_item, const char* item[], int items_count, float alignment = 0.12f) {
    ImGuiStyle& style = ImGui::GetStyle();
    float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
    float avail = ImGui::GetContentRegionAvail().x;
    float off = (avail - size) * alignment;

    if (off > 0.0f)
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
    return ImGui::Combo(label, current_item, item, items_count);
}

//Update device and call the renderer
void App::Update()
{
    bool mouse = false;
    // Create renderer framebuffer (color+depth+opengl texture)
    // We need an OpenGL texture to display the result of the renderer to the screen
    // Init renderer
    Renderer renderer(width, height);  
    Framebuffer* framebuffer = renderer.getFrameBuffer();

    

    

    CameraInputs inputs;
    Camera camera(framebuffer->GetWidth(), framebuffer->GetHeight());

    bool mouseCaptured = false;
    double mouseX = 0.0;
    double mouseY = 0.0;
    float mouseDeltaX = 0.0;
    float mouseDeltaY = 0.0;

    while (glfwWindowShouldClose(window) == false)
    {
        NewFrame(mouseCaptured); //ImGui

        {
            double newMouseX, newMouseY;
            glfwGetCursorPos(window, &newMouseX, &newMouseY);
            mouseDeltaX = (float)(newMouseX - mouseX);
            mouseDeltaY = (float)(newMouseY - mouseY);
            mouseX = newMouseX;
            mouseY = newMouseY;
        }

        // Update camera
        if (ImGui::IsKeyPressed(GLFW_KEY_ESCAPE))
        {
            mouseCaptured = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

        if (mouseCaptured)
        {
            inputs.deltaX = mouseDeltaX;
            inputs.deltaY = mouseDeltaY;
            
            inputs.moveForward  = ImGui::IsKeyDown(GLFW_KEY_W);
            inputs.moveBackward = ImGui::IsKeyDown(GLFW_KEY_S);
            inputs.moveLeft  = ImGui::IsKeyDown(GLFW_KEY_A);
            inputs.moveRight = ImGui::IsKeyDown(GLFW_KEY_D);

            camera.Update(ImGui::GetIO().DeltaTime, inputs);
        }

        // Clear buffers
        framebuffer->Clear();

        // Setup matrices
        camera.FOV = 70;
        camera.projectionMatrix = camera.GetProjection(0.1f, 100.f,camera.FOV, (float)renderer.p_height / renderer.p_width);
        camera.viewMatrix       = camera.GetViewMatrix(camera.viewPosition ,camera.viewRotation.x, camera.viewRotation.y);
        renderer.SetProjection(camera.projectionMatrix);
        renderer.SetView(camera.viewMatrix);

        // Render scene
        scene.Update(ImGui::GetIO().DeltaTime, renderer);
        
        // Upload texture
        framebuffer->UpdateTexture();

        //ImVec4* colors = ImGui::GetStyle().Colors;
        ImGui::GetStyle().WindowRounding = 10.0f;
        // colors[ImGuiCol_Text] = ImVec4(250.f/255.f, 50.f/255.f, 20.f/255.f, 1.0f);

        static const char* geometry[] {"Triangle", "Square", "Sphere", "Cube", "All Shapes","texturedCube"};
        static const char* lightening[] {"Diffuse", "Ambient"};

        if(ImGui::Begin("Config")) {
            if(ImGui::CollapsingHeader("Framebuffer", ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::ColorEdit4("clearColor", framebuffer->clearColor.e);
                ImGui::SliderFloat("FrameWidth", &width, 100.f, 2500.f);
                ImGui::SliderFloat("FrameHeight", &height, 100.f, 2500.f);

                if(ButtonCenteredOnLine("Reset Screen Width", 0.1f)) ScreenResetWidth();
                ImGui::SameLine();
                if(ButtonCenteredOnLine("Reset Screen Height", 0.1f)) ScreenResetHeight();
            }

            ComboCenteredOnLine("Lights", &renderer.typeLight, lightening, IM_ARRAYSIZE(lightening));
            if(ImGui::CollapsingHeader(lightening[renderer.typeLight], ImGuiTreeNodeFlags_DefaultOpen)) {
                
                float colorToReturn;
                if(renderer.typeLight == 1) colorToReturn = renderer.LightIntens;
                if(renderer.typeLight == 2) colorToReturn = renderer.LightDiffuseIntens;

                renderer.updateOnChange(renderer.colorWLight, colorToReturn, renderer.vertices, renderer.typeLight);
                
                if(renderer.typeLight == 1) {
                    ImGui::SliderFloat("Ambient Light", &renderer.LightIntens, 0, 1); }
                else {
                    ImGui::SliderFloat("Diffuse Light", &renderer.LightDiffuseIntens, 0, 1);
                    ImGui::SliderFloat3("Diffuse Position", renderer.LightDirDiff, -100.f, 100.f);
                }
            }

            ComboCenteredOnLine("Shapes", &scene.vers, geometry, IM_ARRAYSIZE(geometry));
            if(ImGui::CollapsingHeader(geometry[scene.vers], ImGuiTreeNodeFlags_DefaultOpen)) {
                // TRIANGLE
                if(scene.vers == 0) {
                    renderer.lineColor[scene.vers] = cApp.color[scene.vers]; renderer.type[scene.vers] = cApp.type[scene.vers];
                    ImGui::ColorEdit4("Triangle Color", cApp.color[scene.vers].e);
                    ImGui::SliderInt("Triangle Type", &cApp.type[scene.vers], 0, 1);
                }
                // CARRE
                if(scene.vers == 1) {
                    renderer.lineColor[scene.vers] = cApp.color[scene.vers]; renderer.type[scene.vers] = cApp.type[scene.vers];
                    ImGui::ColorEdit4("Square Color", cApp.color[scene.vers].e);
                    ImGui::SliderInt("Square Type", &cApp.type[scene.vers], 0, 1);
                }
                // SPHERE
                if(scene.vers == 2) {
                    renderer.lineColor[scene.vers] = cApp.color[scene.vers]; renderer.type[scene.vers] = cApp.type[scene.vers];
                    ImGui::ColorEdit4("Sphere Color", cApp.color[scene.vers].e);
                    ImGui::SliderInt("Sphere Type", &cApp.type[scene.vers], 0, 1);
                }
                // CUBE
                if(scene.vers == 3) {
                    renderer.lineColor[scene.vers] = cApp.color[scene.vers]; renderer.type[scene.vers] = cApp.type[scene.vers];
                    ImGui::ColorEdit4("Cube Color", cApp.color[scene.vers].e);
                    ImGui::SliderInt("Cube Type", &cApp.type[scene.vers], 0, 1);
                }

                if(scene.vers == 4) {
                    // TRIANGLE
                    renderer.lineColor[0] = cApp.color[0]; renderer.type[0] = cApp.type[0];
                    ImGui::ColorEdit4("Triangle Color", cApp.color[0].e);
                    ImGui::SliderInt("Triangle Type", &cApp.type[0], 0, 1);
                    // CARRE
                    renderer.lineColor[1] = cApp.color[1]; renderer.type[1] = cApp.type[1];
                    ImGui::ColorEdit4("Square Color", cApp.color[1].e);
                    ImGui::SliderInt("Square Type", &cApp.type[1], 0, 1);
                    // SPHERE
                    renderer.lineColor[2] = cApp.color[2]; renderer.type[2] = cApp.type[2];
                    ImGui::ColorEdit4("Sphere Color", cApp.color[2].e);
                    ImGui::SliderInt("Sphere Type", &cApp.type[2], 0, 1);
                    // CUBE
                    renderer.lineColor[3] = cApp.color[3]; renderer.type[3] = cApp.type[3];
                    ImGui::ColorEdit4("Cube Color", cApp.color[3].e);
                    ImGui::SliderInt("Cube Type", &cApp.type[3], 0, 1);
                }

                CheckBoxCenteredOnLine("Show Wireframe", &renderer.wireframe, 0.125f);
                ImGui::SameLine();
                CheckBoxCenteredOnLine("Back-Face Culling", &renderer.back_face_culling, 0.125f);

                ImGui::SliderFloat3("Rotation", scene.rot, -720.f, 720.f);
                ImGui::SliderFloat3("Translation", scene.tra, -10.f, 10.f);
                ImGui::SliderFloat("Scale", &scene.sca, 0.f, 10.f);

                if(ButtonCenteredOnLine("Reset Shape Position", 0.05f)) scene.resetPosition();
                ImGui::SameLine();
                if(ButtonCenteredOnLine("Reset Shape Rotation", 0.05f)) scene.resetRotation();

                if(ImGui::IsKeyDown(GLFW_KEY_F1)) { 
                    renderer.wireframe = true;
                } else { 
                    renderer.wireframe = false; }

                if(ImGui::IsKeyDown(GLFW_KEY_F2)) { 
                    renderer.back_face_culling = true;
                } else { 
                    renderer.back_face_culling = false; }
            }
            
            if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Text("Position X = %.1f, Y = %.1f, Z = %.1f", camera.viewPosition.x, camera.viewPosition.y, camera.viewPosition.z);
                ImGui::Text("Rotation X = %.1f, Y = %.1f, Z = %.1f", camera.viewRotation.x, camera.viewRotation.y, camera.viewRotation.z);

                if(ButtonCenteredOnLine("Reset Camera Position", 0.f)) camera.resetPosition();
                ImGui::SameLine();
                if(ButtonCenteredOnLine("Reset Camera Rotation", 0.f)) camera.resetRotation();
                camera.ShowImGuiControls();
            }
        }
        ImGui::End();
        
        ImGui::Begin("Framebuffer");
        ImGui::Text("(Right click to capture mouse, Esc to un-capture)");
        // Display framebuffer (renderer output)
        ImGui::Image((ImTextureID)(size_t)framebuffer->GetColorTexture(), { (float)width, (float)height });
        if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
        {
            mouseCaptured = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        
        ImGui::End();
        EndFrame();

    }
    
}

//destructor who kill glfw and clean the window buffer
App::~App()
{
    //unload Texture
        scene.unloadTexture(0);
        scene.unloadTexture(1);
    //-----------
    glfwDestroyWindow(window);
    glfwTerminate();
    
}
