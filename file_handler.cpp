#include "file_handler.h"
#include <iostream>

void file_handler::ReadFile()
{
  
    std::ifstream param;
	param.open(filename);
	if (!param.is_open())
	{
        ImGui::Begin("File Loading Error");
        ImGui::TextColored((ImVec4)ImColor::HSV(0.0f, 1.0f, 1.0f), "ERROR: Could not open file!");
        ImGui::End();
		return;
	}

	while (param)
	{
		std::string key;
		double value;
		std::getline(param, key, ':');
		param >> value;
		param.get(); // catch empty line
		if (!param)
			return;
		paramMap[key] = value; //paramMap.insert(std::pair<std::string, float>(key, value));
	}
	param.close();
    
	return;
}

void file_handler::PrintParams()
{
    ReadFile();
    ImGui::Begin("Print Parameter");
    std::map<std::string, double>::iterator itr;

    for (itr = paramMap.begin(); itr != paramMap.end(); ++itr)
    {
        ImGui::Text("%s : ", (itr->first).c_str()); ImGui::SameLine();
        ImGui::Text("%f\n", itr->second);
    }
    ImGui::End();
}

void file_handler::UpdateFile(float responsiveness, float smoothness)
{
   
    //Update the paramMap
    UpdateParams(responsiveness, smoothness);
    std::map<std::string, double>::iterator itr;
    //Write the paramMap to file
    std::ofstream param;
    param.open(filename, std::ofstream::out | std::ofstream::trunc);
    if (!param.is_open())
    {
        ImGui::Begin("File Loading Error");
        ImGui::TextColored((ImVec4)ImColor::HSV(0.0f, 1.0f, 1.0f), "ERROR: Could not open file!");
        ImGui::End();
        return;
    }

    for (itr = paramMap.begin(); itr != paramMap.end(); ++itr)
        param << (itr->first) << ": " << itr->second << std::endl;


    param.close();

    return;

}

void file_handler::UpdateParams(float responsiveness, float smoothness)
{

    paramMap["k_ax"] = mapRangeClamped(responsiveness, 0.0, 1.0, param_limits::lim_k_ax[0], param_limits::lim_k_ax[1]);
    paramMap["k_ay"] = mapRangeClamped(responsiveness, 0.0, 1.0, param_limits::lim_k_ay[0], param_limits::lim_k_ay[1]);
    paramMap["k_az"] = mapRangeClamped(responsiveness, 0.0, 1.0, param_limits::lim_k_az[0], param_limits::lim_k_az[1]);
    paramMap["k_vroll"] = mapRangeClamped(responsiveness, 0.0, 1.0, param_limits::lim_k_vroll[0], param_limits::lim_k_vroll[1]);
    paramMap["k_vpitch"] = mapRangeClamped(responsiveness, 0.0, 1.0, param_limits::lim_k_vpitch[0], param_limits::lim_k_vpitch[1]);
    paramMap["k_vyaw"] = mapRangeClamped(responsiveness, 0.0, 1.0, param_limits::lim_k_vyaw[0], param_limits::lim_k_vyaw[1]);

    paramMap["hp_ax"] = mapRangeClamped(smoothness, 0.0, 1.0, param_limits::lim_hp_ax[0], param_limits::lim_hp_ax[1]);
    paramMap["hp_ay"] = mapRangeClamped(smoothness, 0.0, 1.0, param_limits::lim_hp_ay[0], param_limits::lim_hp_ay[1]);
    paramMap["hp_az"] = mapRangeClamped(smoothness, 0.0, 1.0, param_limits::lim_hp_az[0], param_limits::lim_hp_az[1]);
    paramMap["hp_vroll"] = mapRangeClamped(smoothness, 0.0, 1.0, param_limits::lim_hp_vroll[0], param_limits::lim_hp_vroll[1]);
    paramMap["hp_vpitch"] = mapRangeClamped(smoothness, 0.0, 1.0, param_limits::lim_hp_vpitch[0], param_limits::lim_hp_vpitch[1]);
    paramMap["hp_vyaw"] = mapRangeClamped(smoothness, 0.0, 1.0, param_limits::lim_hp_vyaw[0], param_limits::lim_hp_vyaw[1]);

    paramMap["lp_ax"] = mapRangeClamped(smoothness, 0.0, 1.0, param_limits::lim_lp_ax[0], param_limits::lim_lp_ax[1]);
    paramMap["lp_ay"] = mapRangeClamped(smoothness, 0.0, 1.0, param_limits::lim_lp_ay[0], param_limits::lim_lp_ay[1]);
    paramMap["lp_az"] = mapRangeClamped(smoothness, 0.0, 1.0, param_limits::lim_lp_az[0], param_limits::lim_lp_az[1]);
}


void file_handler::ResetFile()
{

    ResetParamMapToIdeal();

    std::map<std::string, double>::iterator itr;
    //Write the paramMap to file
    std::ofstream param;
    param.open(filename, std::ofstream::out | std::ofstream::trunc);
    if (!param.is_open())
    {
        ImGui::Begin("File Loading Error");
        ImGui::TextColored((ImVec4)ImColor::HSV(0.0f, 1.0f, 1.0f), "ERROR: Could not open file!");
        ImGui::End();
        return;
    }

    for (itr = paramMap.begin(); itr != paramMap.end(); ++itr)
        param << (itr->first) << ": " << itr->second << std::endl;

    param.close();

    isFileReset = true;
    return;
}


void file_handler::ResetParamMapToIdeal()
{
    paramMap["k_ax"] = initial_values::k_ax;
    paramMap["k_ay"] = initial_values::k_ay;
    paramMap["k_az"] = initial_values::k_az;
    paramMap["k_vroll"] = initial_values::k_vroll;
    paramMap["k_vpitch"] = initial_values::k_vpitch;
    paramMap["k_vyaw"] = initial_values::k_vyaw;
    paramMap["hp_ax"] = initial_values::hp_ax;
    paramMap["hp_ay"] = initial_values::hp_ay;
    paramMap["hp_az"] = initial_values::hp_az;
    paramMap["hp_vroll"] = initial_values::hp_vroll;
    paramMap["hp_vpitch"] = initial_values::hp_vpitch;
    paramMap["hp_vyaw"] = initial_values::hp_vyaw;
    paramMap["lp_ax"] = initial_values::lp_ax;
    paramMap["lp_ay"] = initial_values::lp_ay;
    paramMap["lp_az"] = initial_values::lp_az;
}

float mapRangeClamped(float inVal, float minInRange, float maxInRange, float minOutRange, float maxOutRange)
{
    float x = (inVal - minInRange) / (maxInRange - minInRange);
    return minOutRange + ((maxOutRange - minOutRange) * x);
}


