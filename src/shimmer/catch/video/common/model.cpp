#include "catch.hpp"
#include "video/common/model.hpp"

TEST_CASE ( "Creating a generic model." )
{
        const std::string json_a = R"({"children":["child_a","child_b","child_c"],"id":"model_a","material":"material_a","mesh":"mesh_a","transform":[[3.0,0.0,0.0,0.0],[0.0,3.0,0.0,0.0],[0.0,0.0,3.0,0.0],[0.0,0.0,0.0,3.0]],"visible":true})";

        const std::string json_b = R"({"children":[],"id":"model_b","material":null,"mesh":null,"transform":[[1.0,0.0,0.0,0.0],[0.0,1.0,0.0,0.0],[0.0,0.0,1.0,0.0],[0.0,0.0,0.0,1.0]],"visible":false})";

        const std::string json_c = R"({"children":["child_a","child_b","child_c","child_d"],"id":"","material":null,"mesh":"mesh_b","transform":[[1.0,0.0,0.0,0.0],[0.0,1.0,0.0,0.0],[0.0,0.0,1.0,0.0],[0.0,0.0,0.0,1.0]],"visible":false})";
        
        const std::string json_a_mod = R"({"children":["child_a","child_b","child_c","model_b"],"id":"model_a","material":"material_a","mesh":"mesh_a","transform":[[3.0,0.0,0.0,0.0],[0.0,3.0,0.0,0.0],[0.0,0.0,3.0,0.0],[0.0,0.0,0.0,3.0]],"visible":true})";
        
        
        shimmer::model model_a;
        model_a.id ( "model_a" )
        .children ( {
                std::make_shared<shimmer::model> ( "child_a" ),
                std::make_shared<shimmer::model> ( "child_b" ),
                std::make_shared<shimmer::model> ( "child_c" )
        } )
        .material ( std::make_shared<shimmer::material> ( "material_a" ) )
        .mesh ( std::make_shared<shimmer::mesh> ( "mesh_a" ) )
        .transform ( glm::mat4 ( 3 ) )
        .visible ( true );

        auto model_b_ptr = std::make_shared<shimmer::model> ( "model_b" );

        CHECK ( model_a.to_json() == json_a );
        CHECK ( model_b_ptr->to_json() == json_b );

        shimmer::model model_c;
        model_c.children(model_a.children());
        model_c.children().push_back(std::make_shared<shimmer::model> ( "child_d"));
        model_c.mesh(std::make_shared<shimmer::mesh> ( "mesh_b" ));
        CHECK ( model_c.to_json() == json_c );
        
        model_a.children().push_back(model_b_ptr);
        CHECK ( model_a.to_json() == json_a_mod );
}
