#ifndef FILE_HANDLER_H_
#define FILE_HANDLER_H_

#pragma once
#include "imgui.h"
#include <map>
#include <string>
#include <fstream>

class file_handler
{
private:
    std::string filename;

public:
    bool isFileReset;
    std::map<std::string, double> paramMap;
    file_handler() :filename("param.yaml"), isFileReset(false) {};
    void ReadFile();
    void PrintParams();
    void UpdateFile(float, float);
    void ResetFile();
    void UpdateParams(float responsiveness, float smoothness);
    void ResetParamMapToIdeal();

};


namespace param_limits
{
    const float lim_k_ax[2] = { 0.00001, 0.00010 }; //min, max
    const float lim_k_ay[2] = { 0.000005, 0.00002 }; //min, max
    const float lim_k_az[2] = { 0.0001, 0.0005 }; //min, max
    const float lim_k_vroll[2] = { 0.175, 0.55 }; //min, max
    const float lim_k_vpitch[2] = { 0.175, 0.55 }; //min, max
    const float lim_k_vyaw[2] = { 0.175, 0.55 }; //min, max
    const float lim_hp_ax[2] = { 0.0070, 0.0086 };
    const float lim_hp_ay[2] = { 0.0070, 0.0086 };
    const float lim_hp_az[2] = { 0.0070, 0.0086 };
    const float lim_hp_vroll[2] = { 0.0200, 0.0255 };
    const float lim_hp_vpitch[2] = { 0.0200, 0.0255 };
    const float lim_hp_vyaw[2] = { 0.0085, 0.0094 };
    const float lim_lp_ax[2] = { 0.0069, 0.0085 };
    const float lim_lp_ay[2] = { 0.0069, 0.0085 };
    const float lim_lp_az[2] = { 0.0069, 0.0085 };
}

namespace initial_values
{
    static float init_res   = 0.00000f;
    static float init_smooth= 0.00000f;
    const float k_ax        = 0.00005f;
    const float k_ay        = 0.00001f;
    const float k_az        = 0.00050f;
    const float k_vroll     = 0.35000f;
    const float k_vpitch    = 0.35000f;
    const float k_vyaw      = 0.35000f;
    const float hp_ax       = 0.00860f;
    const float hp_ay       = 0.00860f;
    const float hp_az       = 0.00860f;
    const float hp_vroll    = 0.02550f;
    const float hp_vpitch   = 0.02550f;
    const float hp_vyaw     = 0.00940f;
    const float lp_ax       = 0.00850f;
    const float lp_ay       = 0.00850f;
    const float lp_az       = 0.00850f;
}


//helper functions
float mapRangeClamped(float inVal, float minInRange, float maxInRange, float minOutRange, float maxOutRange);
#endif
