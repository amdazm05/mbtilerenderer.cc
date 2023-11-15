### Design Flow
1- Tile Format
2- SQL queries to get tile_data field
    - tile_id -> Composed of "zoom_level/tile_column/tile_row"
    - tile_data

Querying data for 
Example: SELECT tile_data FROM tiles WHERE zoom_level = $YY AND  tile_column = $ZZZ AND tile_row = $WWW