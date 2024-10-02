#ifndef SERIALISATION_H
#define SERIALISATION_H

// from CtrlAltEngine.vcxproj location I guess.
#include "../libs/rapidjson/document.h"  
#include "../libs/rapidjson/writer.h"
#include "../libs/rapidjson/stringbuffer.h"
#include "../libs/rapidjson/filereadstream.h"
#include "../libs/rapidjson/filewritestream.h"


#include <fstream>
#include <vector>
#include <iostream>

class transformT {
public:
    float pos_x;
    float pos_y;

    std::string component_name{ "transformT" }; 
    inline auto get_name() { return rapidjson::StringRef(this->component_name.c_str()); }  
    inline const char* get_cname() { return (this->component_name.c_str()); }

    // this would be the json value and allocator
    void Serialise(rapidjson::Value& componentJson, rapidjson::Document::AllocatorType& allocator); 
    void Deserialise(const rapidjson::Value& componentJson); 
};


class Entity {
public:
    std::string EntityID;
    transformT transformC;
    std::string json_filename;
    // this will use EntityID name as json file name?
    // this will serialise to a json file
    void Serialise(const char* filename); // its json file name 
    void Deserialise(const char* filename);
};

// yet to implement this.
class Scene_Serialiser {
    std::string name; // file location?
    std::ofstream serialiser_stream;
    std::ifstream deserialiser_stream;
    // then I construct and deconstruct.
    // no I need to make a function to close/exit & open/create.


    // of the scene text file.
};

#endif // end of SERIALISATION_H

