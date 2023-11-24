
# raster or vector tilesets
### Tile Sets
raster or vector data broken up into a uniform grid of square tiles at 22
vector tilesets store vector data in the form of points, lines, and polygons as vector tiles.

# MBTiles Specs
MBTiles is a specification for storing arbitrary tiled map data in SQLite databases


## Flow
SQL Query -> Zoom Level , x, y
          -> Tile Data -> GZIP Uncompress -> (mbtilecacher) -> (pbf files)
                                        TileLRUCache ->
