#include "model.hpp"
#include "external/json/json.hpp"
#include <iostream>

shimmer::model::model()
: _visible(false)
{}

shimmer::model::model(std::string id)
: _id(id), _visible(false)
{}

void shimmer::model::render()
{
        std::cout << "Rendering default model: " << *this << "\n";
}

std::string shimmer::model::to_json() const
{
        using namespace nlohmann;
        
        json model_json {
                {"id", _id},
                {"visible", _visible},
        };
        
        if(_material) model_json["material"] = _material->id();
        else model_json["material"] = nullptr;
        
        if(_mesh) model_json["mesh"] = _mesh->id();
        else model_json["mesh"] = nullptr;
        
        model_json["children"] = json::array();
        for ( auto child : _children ) {
                if(child) model_json["children"].push_back(child->id());
                else model_json["children"].push_back(nullptr);
        }
        for( unsigned int j = 0; j < 4; j++){
                json row;
                for(unsigned int i = 0; i < 4; i++){
                        row.push_back(_transform[j][i]);
                }
                model_json["transform"].push_back(row);
        }
         
        return model_json.dump();
}
