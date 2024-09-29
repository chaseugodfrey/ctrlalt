#include "Mock_Serialisation.h"

void transformT::Serialise(rapidjson::Value& componentJson, rapidjson::Document::AllocatorType& allocator)
{
    // abstraction of json to add members
    // Add the transform data to the JSON object
    // this pos_x is hard coded
    // can this send in many values?
    componentJson.AddMember("pos_x", this->pos_x, allocator); // belongs to the same document
    componentJson.AddMember("pos_y", this->pos_y, allocator); // belongs to the same document
    // pretty sure I can just use it like a map with its key and value.


}

void transformT::Deserialise(const rapidjson::Value& componentJson)
{
    this->pos_x = componentJson["pos_x"].GetFloat();
    this->pos_y = componentJson["pos_y"].GetFloat();

}

//template <typename T>
void Entity::Serialise(const char* filename) {

    rapidjson::Document transformT_root; // this is the root object.
    transformT_root.SetObject();

    //allocator is some kind of memory allocation thing
    rapidjson::Document::AllocatorType& allocator = transformT_root.GetAllocator();

    //creating a the object member // it is a Value. 
    rapidjson::Value transform_data(rapidjson::kObjectType); // this is the root object. 

// abstracted
    this->transformC.Serialise(transform_data, allocator);

    // close off
    transformT_root.AddMember(this->transformC.get_name(), transform_data, allocator); // i used auto return type.

    // waiting to transfer onto json file.
    FILE* out_file_stream{};
    fopen_s(&out_file_stream, filename, "w"); // orh it is not buffer
    if (out_file_stream == NULL)
    {
        std::cout << "file cannot be open, check again." << filename << std::endl;
        //fclose(out_file_stream);
        //exit 
        return;
    }

    // creating the out stream and writer
    char writeBuffer[65536]; // what should i do here.
    rapidjson::FileWriteStream os(out_file_stream, writeBuffer, sizeof(writeBuffer));
    rapidjson::Writer<rapidjson::FileWriteStream> writer(os);

    //attach the writer.
    transformT_root.Accept(writer);

    //clean
    fclose(out_file_stream);

}




void Entity::Deserialise(const char* filename) {
    FILE* in_file_stream{};
    fopen_s(&in_file_stream, filename, "r");
    if (!in_file_stream) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    char readBuffer[65536];
    rapidjson::FileReadStream is(in_file_stream, readBuffer, sizeof(readBuffer));

    rapidjson::Document Entity_json;
    Entity_json.ParseStream(is);

    // Check for parsing errors
    // it don't like comments
    if (Entity_json.HasParseError()) {
        std::cerr << "JSON parsing error!" << std::endl;
        fclose(in_file_stream);
        return;
    }

    // convert this to transform.
    // Check if the JSON has the "My Big Ass" field
    if (!Entity_json.HasMember(this->transformC.get_name())) {
        std::cerr << "'transformT' not found in JSON!" << std::endl;
        fclose(in_file_stream);
        return;
    }
    
    // add in rigid body

    // I may send in the document to comp deserialisation if I need multiple object values.
    const rapidjson::Value& data_Json = Entity_json[this->transformC.component_name.c_str()];
    this->transformC.Deserialise(data_Json);


    fclose(in_file_stream);
}