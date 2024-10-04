/******************************************************************************/
/*!
\group  	CtrlAlt
\file		Mock_Serialisation.h
\author 	Sherman Goh Wee Hao
\par    	shermanweehao.goh@digipen.edu
\date   	Oct 02, 2024
\brief		Data Serialisation with rapidJson


Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
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

    //Class Scene_Serialiser would be a singleton at Editor scope,
    //
    class Scene_Serialiser {
    public:
        //std::string name; // file location?
        //std::ofstream serialiser_stream; // this will be used with the writer.
        //std::ifstream deserialiser_stream;

        /// <summary>
        /// This Function will write Json Document to a .json file
        /// </summary>
        /// <param name="filename"></param>
        /// intended file name for the .json file.
        void Write_To_File(const char* filename);
        /// <summary>
        /// This Function will parse the .json file to the Json Document
        /// </summary>
        /// <param name="filename"></param>
        /// to open the name of .json file, to get data.
        void Read_From_File(const char* filename);

        /// <summary>
        /// This Serialise Function is incomplete.
        /// It requires to take in a std::vector of Entities to serialise its data.
        /// </summary>
        /// <param name="registry"></param>
        void Serialise(ECS::Registry* registry, std::vector<ECS::Entity> entities); // unsure how to iterate through the entities
        void Deserialise(ECS::Registry* registry);

        

        rapidjson::Document base_document; // Now at a class level 

        /// <summary>
        /// default constructor, 
        /// I will set the base_document as base object.
        /// </summary>
        Scene_Serialiser();
    };

    

}

#endif // end of SERIALISATION_H

