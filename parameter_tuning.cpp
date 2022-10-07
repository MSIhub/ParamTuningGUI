#include "parameter_tuning.h"

void param::RenderUI(file_handler& fh)
{
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    fh.PrintParams();

    static int updateCounter = 0;
    static int resetCounter = 0;
    static int cueingCounter = 0;
    ImGui::Begin("MCA simplified tuning");
    ImGui::NewLine();
    ImGui::SameLine(0.0f, 100.0f);
    ImGui::TextColored((ImVec4)ImColor::HSV(0.44f, 0.96f, 1.0f), "Set the slider value and press update parameter");

    initial_values::init_res = mapRangeClamped(fh.paramMap["k_ax"], param_limits::lim_k_ax[0], param_limits::lim_k_ax[1], 0.0, 1.0);
    initial_values::init_smooth = mapRangeClamped(fh.paramMap["hp_ax"], param_limits::lim_hp_ax[0], param_limits::lim_hp_ax[1], 0.0, 1.0);

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
    bool updateButtonPressed = ImGui::Button("Update Parameter File", ImVec2(300.f, 50.0f));
    if (updateButtonPressed)
    {
        fh.UpdateFile(values[0], values[1]);
        updateCounter++;
    }

    ImGui::Spacing();

    ImGui::NewLine();
    ImGui::SameLine(0.0f, 180.0f);
    bool resetButtonPressed = ImGui::Button("Reset Parameter File", ImVec2(300.f, 50.0f));
    if (resetButtonPressed)
    {
        fh.ResetFile();
        resetCounter++;
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
    bool cueingStartPressed = ImGui::Button("Start Cueing", ImVec2(300.f, 50.0f));
    if (cueingStartPressed)
    {
        cueing_handler::startCueingProcess();
        cueingCounter++;
    }

    ImGui::BeginChild("outer_child", ImVec2(0, ImGui::GetFontSize() * 3.0f), true);
    if(cueingCounter>0)
        ImGui::BulletText("@msihub : Cueing Started");
    ImGui::EndChild();

    ImGui::End();


}
