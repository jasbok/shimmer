#include "material.hpp"
#include "external/json/json.hpp"
#include <iostream>

shimmer::material::material() {}

shimmer::material::material ( const std::string& id )
        : _id ( id )
{}

shimmer::material::~material() {}

void shimmer::material::use()
{
        std::cout << "Using common material: " << "\n";
}

std::string shimmer::material::to_json() const
{
        using namespace nlohmann;

        json model_json {
                {"id", _id}
        };

        if ( _shader ) model_json["shader"] = _shader->id();
        else model_json["shader"] = nullptr;

        model_json["samplers"] = json::array();
        for ( auto sampler : _samplers ) {
                if(sampler) model_json["samplers"].push_back(sampler->id());
                else model_json["samplers"].push_back ( nullptr );
        }

        return model_json.dump();
}

