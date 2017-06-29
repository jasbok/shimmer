#ifndef SHIMMER_VIDEO_COMMON_MODEL_HPP
#define SHIMMER_VIDEO_COMMON_MODEL_HPP

#include "common/macros.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <ostream>

namespace shimmer
{
class model
{
public:
        model();
        model(std::string id);
        virtual ~model() {}

        virtual void render();

        virtual std::string to_json() const;

        friend std::ostream& operator<< ( std::ostream& os, const model& model ){
                os << model.to_json();
                return os;
        }

private:
        SHIMMER_MEMBER ( model, std::string, id );
        SHIMMER_MEMBER ( model, std::shared_ptr<shimmer::material>, material );
        SHIMMER_MEMBER ( model, std::shared_ptr<shimmer::mesh>, mesh );
        SHIMMER_MEMBER ( model, glm::mat4, transform );
        SHIMMER_MEMBER ( model, bool, visible );
        SHIMMER_MEMBER ( model, std::vector<std::shared_ptr<shimmer::model>>, children);
        //SHIMMER_VECTOR ( model, std::shared_ptr<shimmer::model>, children, add_child);
};
}

#endif
