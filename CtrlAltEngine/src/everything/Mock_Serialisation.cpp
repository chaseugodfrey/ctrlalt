/******************************************************************************/
/*!
\group  	CtrlAlt
\file		Mock_Serialisation.cpp
\author 	Sherman Goh Wee Hao
\par    	shermanweehao.goh@digipen.edu
\date   	Oct 02, 2024
\brief		Data Serialisation with rapidJson

\par 
        These functions were ported from a working sandbox, it has not been
        tested with the ECS , so we have not considered how integration would 
        go when saving / switching scenes.
        This does not allow for scaliability and also address special 
        considerations like potential pointers or holding onto relations
        of entities with each other.

        Lastly, when I did this, Jerron and I aimed for simplicity,
        Where Entities are stored as an array.
        Looking at the current state of our ECS, I believe that having names
        or taking the EntityID would allow easier tagging/identification.
Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "../src/pch.h"
#include "Mock_Serialisation.h"


/// <summary>
    /// This is a Component serialisation of CTransform type.
    /// </summary>
    /// <param name="transform_comp"></param>
    /// 
    /// <param name="componentJson"></param>
    /// We use the implementation for arrays
    /// <param name="allocator"></param>
    /// allocator is important with rapidJson
void TSerialise(Component::CTransform const& transform_comp, rapidjson::Value& componentJson,
    rapidjson::Document::AllocatorType& allocator);
/// <summary>
/// 
/// </summary>
/// <param name="entity_obj"></param>
/// <param name="entity_data"></param>
void RSerialise(Component::CRigidBody const& rigidbody_comp, rapidjson::Value& componentJson,
    rapidjson::Document::AllocatorType& allocator);

void TDeserialise(Component::CTransform& transform_comp, const rapidjson::Value& componentJson);
void RDeserialise(Component::CRigidBody& rigidbody_comp, const rapidjson::Value& componentJson);


/// <summary>
/// This is a Entity serialisation.
/// </summary>
/// <param name="entity_obj"></param>
/// To get Entity's data
/// <param name="entity_array"></param>
/// We use the implementation for arrays
/// <param name="base_document"></param>
/// this is to get the 
void ESerialise(ECS::Entity& entity_obj, rapidjson::Value& entity_array, rapidjson::Document& base_document);
/// <summary>
/// This is a Entity Deserialisation.
/// </summary>
/// <param name="entity_obj"></param>
/// To get Entity's data
/// <param name="entity_data"></param>
/// This is a Value of type kObject.
void EDeserialise(ECS::Entity& entity_obj, const rapidjson::Value& entity_data);


using namespace Serialisation;

void TSerialise(Component::CTransform const& transform_comp, rapidjson::Value& componentJson, rapidjson::Document::AllocatorType& allocator)
{
    // abstraction of json to add members
    // Add the transform data to the JSON object
    // this pos_x is hard coded
    // can this send in many values?
    componentJson.AddMember("pos_x", transform_comp.position.x, allocator); 
    componentJson.AddMember("pos_y", transform_comp.position.y, allocator); 
    componentJson.AddMember("scale_x", transform_comp.scale.x, allocator); 
    componentJson.AddMember("scale_y", transform_comp.scale.y, allocator);  
    componentJson.AddMember("rot", transform_comp.rotation, allocator);  

    // pretty sure I can just use it like a map with its key and value.


}

void RSerialise(Component::CRigidBody const& rigidbody_comp, rapidjson::Value& componentJson, rapidjson::Document::AllocatorType& allocator)
{
    // abstraction of json to add members
    // Add the transform data to the JSON object
    // this pos_x is hard coded
    // can this send in many values?
    componentJson.AddMember("vel_x", rigidbody_comp.vel.x, allocator);
    componentJson.AddMember("vel_y", rigidbody_comp.vel.y, allocator);


    // pretty sure I can just use it like a map with its key and value.


}

void TDeserialise(Component::CTransform& transform_comp, const rapidjson::Value& componentJson)
{
    transform_comp.position.x = componentJson["pos_x"].GetFloat();
    transform_comp.position.y = componentJson["pos_y"].GetFloat();
    transform_comp.scale.x = componentJson["scale_x"].GetFloat();
    transform_comp.scale.y = componentJson["scale_y"].GetFloat();
    transform_comp.rotation = componentJson["rot"].GetFloat();
}

void RDeserialise(Component::CRigidBody& rigidbody_comp, const rapidjson::Value& componentJson)
{
    rigidbody_comp.vel.x = componentJson["vel_x"].GetFloat();
    rigidbody_comp.vel.y = componentJson["vel_y"].GetFloat();
}


void ESerialise(ECS::Entity& entity_obj, rapidjson::Value& entity_array, rapidjson::Document& base_document) {

    rapidjson::Document::AllocatorType& allocator = base_document.GetAllocator();
    rapidjson::Value entity_data(rapidjson::kObjectType); // this is the root object.


    //creating a the object member // it is a Value. 
    rapidjson::Value transform_data(rapidjson::kObjectType);
    auto transform_comp = entity_obj.GetComponent<Component::CTransform>();
    TSerialise(transform_comp, transform_data, allocator);

    // close off
    entity_data.AddMember("CTransform", transform_data, allocator); // i used auto return type.


    //creating a the object member // it is a Value. 
    rapidjson::Value rigidbody_data(rapidjson::kObjectType);
    auto rigidbody_comp = entity_obj.GetComponent<Component::CRigidBody>(); 
    RSerialise(rigidbody_comp, rigidbody_data, allocator);

    // close off
    entity_data.AddMember("CRigidBody", transform_data, allocator); // i used auto return type.

    entity_array.PushBack(entity_data, allocator);
    //base_document.AddMember("Entity", entity_data, allocator); 
}




void EDeserialise(ECS::Entity& entity_obj, const rapidjson::Value& entity_data) {




    // Check if the JSON has the "transformT" field
    if (!entity_data.HasMember("CTransform")) {
        std::cerr << "'CTransform' not found in JSON!" << std::endl;
        return;
    }

    if (!entity_data.HasMember("CRigidBody")) {
        std::cerr << "'CRigidBody' not found in JSON!" << std::endl;
        return;
    }

    // I may send in the document to comp deserialisation if I need multiple object values.
    const rapidjson::Value& transform_data = entity_data["CTransform"];
    auto transform_comp = entity_obj.GetComponent<Component::CTransform>(); 
    TDeserialise(transform_comp, transform_data); 


    const rapidjson::Value& rigidbody_data = entity_data["CRigidBody"]; 
    auto rigidbody_comp = entity_obj.GetComponent<Component::CRigidBody>();
    RDeserialise(rigidbody_comp, rigidbody_data);
   

}



Scene_Serialiser::Scene_Serialiser() {
    this->base_document.SetObject();  // Initialize as an object
}


// what to do
void Scene_Serialiser::Serialise(ECS::Registry* registry, std::vector<ECS::Entity> entities) { 
    registry;
    rapidjson::Value entity_array(rapidjson::kArrayType);

    //// this entity will serialise itself to the Document.
    //entity.Serialise(entity_array, this->base_document); // my entity cannot be const?
    //entity.Serialise(entity_array, this->base_document); // my entity cannot be const?
    //entity.Serialise(entity_array, this->base_document); // my entity cannot be const?
    //entity.Serialise(entity_array, this->base_document); // my entity cannot be const?
    //entity.Serialise(entity_array, this->base_document); // my entity cannot be const?

    //this->base_document.AddMember("Entity_Array", entity_array, this->base_document.GetAllocator());
    for (ECS::Entity x : entities) 
    {
        ESerialise(x, entity_array, this->base_document);  
        
    }
}


void Scene_Serialiser::Write_To_File(const char* filename) {
    // waiting to transfer onto json file.
    FILE* out_file_stream;
    fopen_s(&out_file_stream, filename, "w"); // orh it is not buffer  
    if (out_file_stream == NULL)
    {
        std::cout << "file cannot be open, check again." << filename << std::endl;
        //fclose(out_file_stream);
        //exit 
        return;
    }

    // creating the out stream and writer
    char* writeBuffer = new char [65536]; // what should i do here.
    rapidjson::FileWriteStream os(out_file_stream, writeBuffer, sizeof(writeBuffer));
    rapidjson::Writer<rapidjson::FileWriteStream> writer(os);

    //attach the writer.
    this->base_document.Accept(writer);

    //clean
    delete []writeBuffer;
    fclose(out_file_stream); 

}

void Scene_Serialiser::Deserialise(ECS::Registry* registry) {

    // Check if the JSON has the "Entity_Array" field
    if (this->base_document.HasMember("Entity_Array") && this->base_document["Entity_Array"].IsArray()) {
        const rapidjson::Value& entity_array_data_Json = this->base_document["Entity_Array"];

        // iterate through the array 
        for (rapidjson::SizeType i = 0; i < entity_array_data_Json.Size(); i++) {
            const rapidjson::Value& entity_data = entity_array_data_Json[i];
            // Create entity
            ECS::Entity entity = registry->CreateEntity();
            // Deserialise with json::Value into ECS::Entity.
            EDeserialise(entity, entity_data);  
        }

    }
}


void Scene_Serialiser::Read_From_File(const char* filename) {
    FILE* in_file_stream;
    fopen_s(&in_file_stream, filename, "r");
    if (!in_file_stream) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    char* readBuffer = new char[65536]; // what should i do here.
    rapidjson::FileReadStream is(in_file_stream, readBuffer, sizeof(readBuffer));

    rapidjson::Document Entity_json;
    Entity_json.ParseStream(is);
    // this is the write to file.

        // Check for parsing errors
    // it don't like comments
    if (Entity_json.HasParseError()) {
        std::cerr << "JSON parsing error!" << std::endl;
        fclose(in_file_stream);
        return;
    }

    // Check if the JSON has the "My Big Ass" field
    if (!Entity_json.HasMember("Entity_Array") && !Entity_json["Entity_Array"].IsArray()) {
        std::cerr << "'Entity_Array' not found in JSON! " << filename << std::endl;
        fclose(in_file_stream);
        return;
    }


    //clean up
    delete[] readBuffer;
    fclose(in_file_stream);

}
