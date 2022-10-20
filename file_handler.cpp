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
		float value;
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
    std::map<std::string, float>::iterator itr;

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
    std::map<std::string, float>::iterator itr;
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
    
    parameter p_min, p_max;
    switch (inputChoice)
    {
    case XPLANE:
        p_min = param_limit::min_xplane;
        p_max = param_limit::max_xplane;
        break;
    case AIRSIM:
        p_min = param_limit::min_airsim;
        p_max = param_limit::max_airsim;
        break;
    case MFS22:
        p_min = param_limit::min_mfs22;
        p_max = param_limit::max_mfs22;
        break;
    default:
        p_min = param_limit::min_xplane;
        p_max = param_limit::max_xplane;
        break;
    }
    
    //Ensure the values are with the limit to avoid param mapped to values greater or lower.
    if (responsiveness > 1.0f) responsiveness = 1.0f;
    if (responsiveness < 0.0f) responsiveness = 0.0f;

    if (smoothness > 1.0f) smoothness = 1.0f;
    if (smoothness < 0.0f) smoothness = 0.0f;
    

    paramMap["k_ax"] = mapRangeClamped(responsiveness, 0.0, 1.0, p_min.k_ax, p_max.k_ax);
    paramMap["k_ay"] = mapRangeClamped(responsiveness, 0.0, 1.0, p_min.k_ay, p_max.k_ay);
    paramMap["k_az"] = mapRangeClamped(responsiveness, 0.0, 1.0, p_min.k_az, p_max.k_az);
    paramMap["k_vroll"] = mapRangeClamped(responsiveness, 0.0, 1.0, p_min.k_vroll, p_max.k_vroll);
    paramMap["k_vpitch"] = mapRangeClamped(responsiveness, 0.0, 1.0, p_min.k_vpitch, p_max.k_vpitch);
    paramMap["k_vyaw"] = mapRangeClamped(responsiveness, 0.0, 1.0, p_min.k_vyaw, p_max.k_vyaw);

    paramMap["hp_ax"] = mapRangeClamped(smoothness, 0.0, 1.0, p_min.hp_ax, p_max.hp_ax);
    paramMap["hp_ay"] = mapRangeClamped(smoothness, 0.0, 1.0, p_min.hp_ay, p_max.hp_ay);
    paramMap["hp_az"] = mapRangeClamped(smoothness, 0.0, 1.0, p_min.hp_az, p_max.hp_az);
    paramMap["hp_vroll"] = mapRangeClamped(smoothness, 0.0, 1.0, p_min.hp_vroll, p_max.hp_vroll);
    paramMap["hp_vpitch"] = mapRangeClamped(smoothness, 0.0, 1.0, p_min.hp_vpitch, p_max.hp_vpitch);
    paramMap["hp_vyaw"] = mapRangeClamped(smoothness, 0.0, 1.0, p_min.hp_vyaw, p_max.hp_vyaw);

    paramMap["lp_ax"] = mapRangeClamped(smoothness, 0.0, 1.0, p_min.lp_ax, p_max.lp_ax);
    paramMap["lp_ay"] = mapRangeClamped(smoothness, 0.0, 1.0, p_min.lp_ay, p_max.lp_ay);
}


void file_handler::ResetFile()
{

    ResetParamMapToIdeal();

    std::map<std::string, float>::iterator itr;
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

    parameter p;
    switch (inputChoice)
    {
    case XPLANE:
        p = initial_values::param_ideal_xplane;
        break;
    case AIRSIM:
        p = initial_values::param_ideal_airsim;
        break;
    case MFS22:
        p = initial_values::param_ideal_mfs22;
        break;
    default:
        p = initial_values::param_ideal_xplane;
        break;
    }
    paramMap["k_ax"] = p.k_ax;
    paramMap["k_ay"] = p.k_ay;
    paramMap["k_az"] = p.k_az;
    paramMap["k_vroll"] = p.k_vroll;
    paramMap["k_vpitch"] = p.k_vpitch;
    paramMap["k_vyaw"] = p.k_vyaw;
    paramMap["hp_ax"] = p.hp_ax;
    paramMap["hp_ay"] = p.hp_ay;
    paramMap["hp_az"] = p.hp_az;
    paramMap["hp_vroll"] = p.hp_vroll;
    paramMap["hp_vpitch"] = p.hp_vpitch;
    paramMap["hp_vyaw"] = p.hp_vyaw;
    paramMap["lp_ax"] = p.lp_ax;
    paramMap["lp_ay"] = p.lp_ay;
}

float mapRangeClamped(float inVal, float minInRange, float maxInRange, float minOutRange, float maxOutRange)
{
    float x = (inVal - minInRange) / (maxInRange - minInRange);
    return minOutRange + ((maxOutRange - minOutRange) * x);
}


