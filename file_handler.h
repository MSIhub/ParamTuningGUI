#ifndef FILE_HANDLER_H_
#define FILE_HANDLER_H_

#pragma once
#include "imgui.h"
#include <map>
#include <string>
#include <fstream>

enum DataInputApp { XPLANE = 0, AIRSIM = 1, MFS22 = 2 };

class file_handler
{
private:
    std::string filename;

public:
    bool isFileReset;
    DataInputApp inputChoice;
    std::map<std::string, float> paramMap;

    file_handler() :filename("param.yaml"), isFileReset(false), inputChoice(DataInputApp::XPLANE) {};

    void ReadFile();
    void PrintParams();
    void UpdateFile(float, float);
    void ResetFile();
    void UpdateParams(float responsiveness, float smoothness);
    void ResetParamMapToIdeal();

};


struct parameter
{   
    float k_ax;
    float k_ay;
    float k_az;
    float k_vroll;
    float k_vpitch;
    float k_vyaw;
    float hp_ax;
    float hp_ay;
    float hp_az;
    float hp_vroll;
    float hp_vpitch;
    float hp_vyaw;
    float lp_ax;
    float lp_ay;
};

namespace param_limit
{
    //Limits
    const struct parameter min_xplane = { 0.00001f, 0.000005f, 0.0001f, 0.175f, 0.175f, 0.175f, 0.0070f, 0.0070f, 0.0070f, 0.0200f, 0.0200f,  0.0085f, 0.0069f, 0.0069f };

    const struct parameter max_xplane = { 0.00010f, 0.00002f, 0.0005f, 0.55f, 0.55f, 0.55f, 0.0086f, 0.0086f, 0.0086f, 0.0255f, 0.0255f,  0.0094f, 0.0085f , 0.0085f };

    const struct parameter min_airsim = { 0.0000001f, 0.0000001f, 0.0000001f, 1.0f, 1.0f, 1.0f, 0.355f, 0.355f, 0.01f, 0.79f, 0.79f,  0.79f,0.40f, 0.40f };

    const struct parameter max_airsim = { 0.00001f, 0.00001f, 0.00001f, 2.0f,1.3f, 1.3f, 0.555f, 0.555f, 0.01f, 0.91f, 0.91f,  0.91f, 0.46f , 0.46f };

    const struct parameter min_mfs22 = { 0.00001f, 0.000005f, 0.0001f, 0.175f, 0.175f, 0.175f, 0.0070f, 0.0070f, 0.0070f, 0.0200f, 0.0200f,  0.0085f, 0.0069f, 0.0069f };

    const struct parameter max_mfs22 = { 0.00010f, 0.00002f, 0.0005f, 0.55f, 0.55f, 0.55f, 0.0086f, 0.0086f, 0.0086f, 0.0255f, 0.0255f,  0.0094f, 0.0085f , 0.0085f };

}




namespace initial_values
{
    static float init_res = 0.00000f;
    static float init_smooth = 0.00000f;
    //Ideal/tested values
    const struct parameter param_ideal_xplane = { 0.00005f, 0.00001f, 0.00050f,  0.35000f, 0.35000f, 0.35000f, 0.00860f, 0.00860f, 0.00860f, 0.02550f, 0.02550f, 0.00940f,0.00850f, 0.00850f };

    const struct parameter param_ideal_airsim = { 0.000001f,  0.000001f,  0.000001f,  2.0f, 1.2f, 1.2f, 0.455f, 0.455f, 0.01f, 0.89f, 0.89f, 0.89f,0.44f, 0.44f };

    const struct parameter param_ideal_mfs22 = { 0.0000889f, 0.00001f, 0.00050f,  0.35000f, 0.35000f, 0.35000f, 0.00860f, 0.00860f, 0.00860f, 0.02550f, 0.02550f, 0.00940f,0.00850f, 0.00850f };
}


//helper functions
float mapRangeClamped(float inVal, float minInRange, float maxInRange, float minOutRange, float maxOutRange);
#endif
