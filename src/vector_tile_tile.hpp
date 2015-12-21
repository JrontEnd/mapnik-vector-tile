#ifndef __MAPNIK_VECTOR_TILE_TILE_H__
#define __MAPNIK_VECTOR_TILE_TILE_H__

// mapnik-vector-tile
#include "vector_tile_config.hpp"

// mapnik
#include <mapnik/layer.hpp>

// libprotobuf
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#include "vector_tile.pb.h"
#pragma GCC diagnostic pop

namespace mapnik
{

namespace vector_tile_impl
{

struct tile
{
public:
    tile();
    tile(std::string const& str);
    tile(tile && t);
    
    MAPNIK_VECTOR_INLINE bool add_layer(std::unique_ptr<vector_tile::Tile_Layer> vt_layer, 
                                        bool layer_is_painted,
                                        bool layer_is_solid,
                                        bool layer_is_empty);
    
    MAPNIK_VECTOR_INLINE bool append_to_string(std::string & str);

    MAPNIK_VECTOR_INLINE bool serialize_to_string(std::string & str);

    vector_tile::Tile & get_tile()
    {
        return *tile_;
    }

    vector_tile::Tile const& get_tile() const
    {
        return *tile_;
    }

    bool is_painted() const
    {
        return !painted_layers_.empty();
    }

    bool is_empty() const
    {
        return tile_->layers_size() == 0;
    }

    bool is_solid() const
    {
        return !solid_layers_.empty();
    }

    std::vector<std::string> const& get_painted() const
    {
        return painted_layers_;
    }

    std::vector<std::string> const& get_empty() const
    {
        return empty_layers_;
    }

    std::vector<std::string> const& get_solid() const
    {
        return solid_layers_;
    }

private:
    std::unique_ptr<vector_tile::Tile> tile_;
    std::vector<std::string> empty_layers_;
    std::vector<std::string> solid_layers_;
    std::vector<std::string> painted_layers_;
};

} // end ns vector_tile_impl

} // end ns mapnik

#if !defined(MAPNIK_VECTOR_TILE_LIBRARY)
#include "vector_tile_tile.ipp"
#endif

#endif // __MAPNIK_VECTOR_TILE_TILE_H__
