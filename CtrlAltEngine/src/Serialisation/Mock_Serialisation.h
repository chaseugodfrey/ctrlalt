#ifndef SERIALISATION_H
#define SERIALISATION_H

// from CtrlAltEngine.vcxproj location I guess.
#include "../libs/rapidjson/document.h"  
#include "../libs/rapidjson/writer.h"
#include "../libs/rapidjson/stringbuffer.h"
#include "../libs/rapidjson/filereadstream.h"
#include "../libs/rapidjson/filewritestream.h"

#include "../Components/CTransform.h"
#include "../Components/CRigidBody.h"
#include "../ECS/ECS.h"


#include <fstream>
#include <vector>
#include <iostream>

namespace Serialisation{
    //class transformT {
    //public:
    //    float pos_x;
    //    float pos_y;

    //    std::string component_name{ "transformT" };
    //    auto get_name() { return rapidjson::StringRef(this->component_name.c_str()); }

    //    // this would be the json value and allocator
    //    void Serialise(rapidjson::Value& componentJson, rapidjson::Document::AllocatorType& allocator);
    //    void Deserialise(const rapidjson::Value& componentJson);
    //};


    //class Entity {
    //public:
    //    std::string EntityID;
    //    transformT transformC;
    //    std::string json_filename;
    //    // this will use EntityID name as json file name?
    //    // this will serialise to a json file
    //    //void Serialise(rapidjson::Value& entity_array, rapidjson::Document& base_document);
    //    //void Deserialise(const rapidjson::Value& entity_data);
    //};

    class Scene_Serialiser {
    public:
        std::string name; // file location?
        std::ofstream serialiser_stream; // this will be used with the writer.
        std::ifstream deserialiser_stream;
        // then I construct and deconstruct.
        // no I need to make a function to close/exit & open/create.

        void Serialise(ECS::Registry* registry); // unsure how to iterate through the entities
        void Deserialise(ECS::Registry* registry);

        void Write_To_File(const char* filename);
        void Read_From_File(const char* filename);
        // of the scene text file.

        rapidjson::Document base_document; // Now at a class level 

        Scene_Serialiser();
    };
}

#endif // end of SERIALISATION_H

