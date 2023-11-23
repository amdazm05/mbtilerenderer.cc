### Scope
1- Version 0.0 
- The scope here is to make a simple renderer map renderer api, allowing tiles to be rendered on OpenGL and extracted as images
- Not targetting PNG based mbtiles and focussing on Vector Tiless
### Design Flow
- Tile Format
- SQL queries to get tile_data field
    - tile_id -> Composed of "zoom_level/tile_column/tile_row"
    - tile_data

Querying data for 
Example: SELECT tile_data FROM tiles WHERE zoom_level = $YY AND  tile_column = $ZZZ AND tile_row = $WWW

- Once the blob has been extracted it is decompressed
- The extracted PBF Vectortile is then placed in an LRU Cache (To keep for rendering ahead)
- Decoding PBF VectorTile