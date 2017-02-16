#ifndef SHIMMER_VIDEO_COMMON_SCENE_MANAGER_HPP
#define SHIMMER_VIDEO_COMMON_SCENE_MANAGER_HPP

#include "common/macros.hpp"
#include "resource_manager.hpp"
#include "scene.hpp"
#include <memory>
#include <unordered_map>

namespace shimmer
{
class scene_manager
{
public:
        scene_manager() {}
        virtual ~scene_manager() {}
private:
        typedef std::unordered_map<std::string, std::shared_ptr<shimmer::scene>> scene_map;
        typedef std::shared_ptr<shimmer::resource_manager> resource_manager_ptr;
        SHIMMER_MEMBER ( scene_manager, scene_map, scenes );
        SHIMMER_MEMBER ( scene_manager, resource_manager_ptr, resource_manager );
};
}

#endif
