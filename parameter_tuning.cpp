#include "parameter_tuning.h"

void param::RenderUI(file_handler& fh)
{
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    

    ImGuiStyle& style = ImGui::GetStyle();
    style.FrameRounding = 10;

    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoScrollbar;
    
    ImGui::Begin("Data input application", NULL, window_flags);
    static int e = 0;
    ImGui::RadioButton("X-Plane Flight Sim  ", &e, 0); ImGui::SameLine();
    ImGui::RadioButton("AirSim Car Sim  ", &e, 1); ImGui::SameLine();
    ImGui::RadioButton("Microsoft Flight Sim", &e, 2);
    switch (e)
    {   
        case 0:
            fh.inputChoice = DataInputApp::XPLANE;
            break;
        case 1:
            fh.inputChoice = DataInputApp::AIRSIM;
            break;
        case 2:
            fh.inputChoice = DataInputApp::MFS22;
            break;
        default:
            fh.inputChoice = DataInputApp::XPLANE;
            break;
    }

    ImGui::End();

    fh.PrintParams();

    static int updateCounter = 0;
    static int resetCounter = 0;
    static int cueingCounter = 0;
    ImGui::Begin("MCA simplified tuning");
    ImGui::NewLine();
    ImGui::SameLine(0.0f, 100.0f);
    ImGui::TextColored((ImVec4)ImColor::HSV(0.44f, 0.96f, 1.0f), "Set the slider value and press update parameter");

    initial_values::init_res = mapRangeClamped(fh.paramMap["k_ax"], param_limit::min_xplane.k_ax, param_limit::max_xplane.k_ax, 0.0, 1.0);
    initial_values::init_smooth = mapRangeClamped(fh.paramMap["hp_ax"], param_limit::min_xplane.hp_ax, param_limit::max_xplane.hp_ax, 0.0, 1.0);

    static float values[2] = { initial_values::init_res,initial_values::init_smooth };

    if (fh.isFileReset)
    {
        values[0] = initial_values::init_res;
        values[1] = initial_values::init_smooth;
        fh.isFileReset = false;
    }
        
         

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::NewLine();
    ImGui::SameLine(0.0f, 225.0f);

    ImGui::PushID("set1");
    for (int i = 0; i < 2; i++)
    {
        if (i > 0) ImGui::SameLine(0.0f, 100.0f);
        ImGui::PushID(i);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(i / 7.0f, 0.5f, 0.5f));
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor::HSV(i / 7.0f, 0.6f, 0.5f));
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, (ImVec4)ImColor::HSV(i / 7.0f, 0.7f, 0.5f));
        ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(i / 7.0f, 0.9f, 0.9f));
        ImGui::VSliderFloat("##v", ImVec2(60, 160), &values[i], 0.0f, 1.0f, "");
        if (ImGui::IsItemActive() || ImGui::IsItemHovered())
            ImGui::SetTooltip("%.3f", values[i]);
        ImGui::PopStyleColor(4);
        ImGui::PopID();

    }
    ImGui::PopID();
    ImGui::NewLine();
    ImGui::SameLine(0.0f, 180.0f);
    ImGui::TextColored((ImVec4)ImColor::HSV(0 / 7.0f, 0.9f, 0.9f), "Responsiveness");
    ImGui::SameLine(0.0f, 30.0f);
    ImGui::TextColored((ImVec4)ImColor::HSV(1 / 7.0f, 0.9f, 0.9f), "Smoothness");

    ImGui::AlignTextToFramePadding();

    ImGui::NewLine();
    ImGui::SameLine(0.0f, 180.0f);
    bool updateButtonPressed = ImGui::Button("Update parameter file", ImVec2(300.f, 50.0f));
    if (updateButtonPressed)
    {
        fh.UpdateFile(values[0], values[1]);
        updateCounter++;

        initial_values::init_res = mapRangeClamped(fh.paramMap["k_ax"], param_limit::min_xplane.k_ax, param_limit::max_xplane.k_ax, 0.0, 1.0);
        initial_values::init_smooth = mapRangeClamped(fh.paramMap["hp_ax"], param_limit::min_xplane.hp_ax, param_limit::max_xplane.hp_ax, 0.0, 1.0);
    }

    ImGui::Spacing();

    ImGui::NewLine();
    ImGui::SameLine(0.0f, 180.0f);
    bool resetButtonPressed = ImGui::Button("Reset parameter file", ImVec2(300.f, 50.0f));
    if (resetButtonPressed)
    {
        
        fh.ResetFile();
        resetCounter++;

        initial_values::init_res = mapRangeClamped(fh.paramMap["k_ax"], param_limit::min_xplane.k_ax, param_limit::max_xplane.k_ax, 0.0, 1.0);
        initial_values::init_smooth = mapRangeClamped(fh.paramMap["hp_ax"], param_limit::min_xplane.hp_ax, param_limit::max_xplane.hp_ax, 0.0, 1.0);
        

    }


    ImGui::BeginChild("outer_child", ImVec2(0, ImGui::GetFontSize() * 3.0f), true);
    ImGui::BulletText("@msihub : Responsiveness = %f, Smoothness = %f", values[0], values[1]);
    if (updateButtonPressed || updateCounter > 0)    
        ImGui::BulletText("@msihub : File Update Success [count: %d]", updateCounter);
    if (resetButtonPressed || resetCounter > 0)
        ImGui::BulletText("@msihub : File Reset Success [count: %d]", resetCounter);
    
    ImGui::EndChild();

    ImGui::End();

    ImGui::Begin("Motion Cueing Process");
    ImGui::NewLine();
    ImGui::SameLine(0.0f, 250.0f);
    bool cueingStartPressed = ImGui::Button("Start motion cueing", ImVec2(300.f, 50.0f));
    if (cueingStartPressed)
    {
        
        switch (fh.inputChoice)
        {
        case XPLANE:
            cueing_handler::startCueingProcess();
            cueingCounter++;
            break;
        case AIRSIM:
            cueing_handler::startCueingProcess();
            cueingCounter++;
            break;
        case MFS22:
            cueing_handler::startCueingWithDataExtractionFromMFS();
            cueingCounter++;
            break;
        default:
            cueing_handler::startCueingProcess();
            cueingCounter++;
            break;
        }
        
    }

    ImGui::BeginChild("outer_child", ImVec2(0, ImGui::GetFontSize() * 3.0f), true);
    if(cueingCounter>0)
        ImGui::BulletText("@msihub : Cueing Started [%d]", cueingCounter);
    ImGui::EndChild();

    ImGui::End();
}
