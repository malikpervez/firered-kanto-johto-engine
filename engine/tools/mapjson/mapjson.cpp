// mapjson.cpp

#include <iostream>
using std::cout; using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <algorithm>
using std::sort; using std::find;

#include <map>
using std::map;

#include <fstream>
using std::ofstream; using std::ifstream;

#include <sstream>
using std::ostringstream;

#include <limits>
using std::numeric_limits;

#include "json11.h"
using json11::Json;

#include <regex>

#include "mapjson.h"

#include <filesystem>

string version;
// Actual game target is distinct from map/header serialization version.
string build_game;
// System directory separator
string sep;

string read_text_file(string filepath) {
    ifstream in_file(filepath);

    if (!in_file.is_open())
        FATAL_ERROR("Cannot open file %s for reading.\n", filepath.c_str());

    string text;

    in_file.seekg(0, std::ios::end);
    text.resize(in_file.tellg());

    in_file.seekg(0, std::ios::beg);
    in_file.read(&text[0], text.size());

    in_file.close();

    return text;
}

void write_text_file(string filepath, string text) {
    // Keep identical FireRed generated headers at their original timestamps.
    // Map identities and shared declarations must not trigger unrelated C
    // recompilation when a room's event or geometry payload changes.
    if (build_game == "FIRERED") {
        ifstream current(filepath, std::ifstream::binary);
        if (current.is_open()) {
            ostringstream existing;
            existing << current.rdbuf();
            if (!current.bad() && existing.str() == text)
                return;
        }
    }
    ofstream out_file(filepath, std::ofstream::binary);

    if (!out_file.is_open())
        FATAL_ERROR("Cannot open file %s for writing.\n", filepath.c_str());

    out_file << text;

    out_file.close();
}


string json_to_string(const Json &data, const string &field = "", bool silent = false) {
    const Json value = !field.empty() ? data[field] : data;
    string output = "";
    switch (value.type()) {
        case Json::Type::STRING:
            output = value.string_value();
            break;
        case Json::Type::NUMBER:
            output = std::to_string(value.int_value());
            break;
        case Json::Type::BOOL:
            output = value.bool_value() ? "TRUE" : "FALSE";
            break;
        case Json::Type::NUL:
            output = "";
            break;
        default:{
            if (!silent) {
                string s = !field.empty() ? ("Value for '" + field + "'") : "JSON field";
                FATAL_ERROR("%s is unexpected type; expected string, number, or bool.\n", s.c_str());
            }
        }
    }

    if (!silent && output.empty()) {
        string s = !field.empty() ? ("Value for '" + field + "'") : "JSON field";
        FATAL_ERROR("%s cannot be empty.\n", s.c_str());
    }

    return output;
}

// Campaign overlays preserve original HnS maps, global map order and layout IDs.
bool is_firered_campaign_map(const Json &map_data) {
    return build_game == "FIRERED"
        && map_data["firered_campaign"].is_object();
}

Json select_map_events(Json map_data) {
    if (build_game != "FIRERED") {
        Json::array objects;
        for (const auto &event : map_data["object_events"].array_items())
            if (!event["firered_slice_only"].bool_value()) objects.push_back(event);
        auto fields = map_data.object_items();
        fields["object_events"] = objects;
        return fields;
    }
    if (!is_firered_campaign_map(map_data)) return map_data;
    if (!map_data["firered_campaign"].is_object())
        FATAL_ERROR("FireRed campaign map requires explicit events.\n");
    auto fields = map_data.object_items();
    for (const auto &field : map_data["firered_campaign"].object_items())
        fields[field.first] = field.second;
    return fields;
}

string get_generated_warning(const string &filename, bool isAsm) {
    string comment = isAsm ? "@" : "//";

    ostringstream warning;
    warning << comment << "\n"
            << comment << " DO NOT MODIFY THIS FILE! It is auto-generated from " << filename << "\n"
            << comment << "\n\n";
    return warning.str();
}

string get_include_guard_start(const string &name) {
    ostringstream guard;
    guard << "#ifndef GUARD_" << name << "_H\n"
          << "#define GUARD_" << name << "_H\n\n";
    return guard.str();
}

string get_include_guard_end(const string &name) {
    ostringstream guard;
    guard << "#endif // GUARD_" << name << "_H\n";
    return guard.str();
}

Json select_layout_geometry(const Json &layout_data);
string generate_layout_geometry_text(const Json &layout, const string &layoutName);

// Read opaque raw payloads in binary mode on every supported host.
string read_geometry_bytes(const string &filepath) {
    ifstream input(filepath, std::ios::binary);
    if (!input.is_open())
        FATAL_ERROR("Cannot open geometry payload %s.\n", filepath.c_str());
    ostringstream bytes;
    bytes << input.rdbuf();
    if (input.bad())
        FATAL_ERROR("Cannot read geometry payload %s.\n", filepath.c_str());
    return bytes.str();
}

// Only these four source-qualified current25 interior maps can share the
// now-identical global descriptor. All other descriptor identities stay unique.
bool may_alias_current25_interior_descriptor(const string &name, const string &layoutId, const Json &layouts) {
    // Explicitly audited unique native defaults only; exact geometry is checked below.
    if (build_game == "FIRERED"
     && layouts["firered_global_geometry_aliases"][name].string_value() == layoutId)
        return true;
    return name == "CeladonCity_Restaurant_Frlg"
        || name == "SaffronCity_CopycatsHouse_1F_Frlg"
        || name == "VermilionCity_PokemonFanClub_Frlg"
        || name == "ViridianCity_House_Frlg";
}

// Exact raw payload aliases are a FireRed-only emission optimization. This
// does not alter the layout decoder, descriptor IDs or original asset files.
string generate_geometry_payload_text(const string &label, const string &filepath) {
    ostringstream text;
    if (build_game == "FIRERED") {
        static bool loaded = false;
        static Json aliases;
        if (!loaded) {
            string err;
            Json plan = Json::parse(read_text_file("data/layouts/firered_geometry_payload_aliases.json"), err);
            if (!err.empty() || !plan["aliases"].is_object())
                FATAL_ERROR("Invalid FireRed geometry alias plan.\n");
            aliases = plan["aliases"];
            loaded = true;
        }
        const Json &alias = aliases[label];
        if (alias.is_object()) {
            string source = json_to_string(alias, "source_filepath");
            string owner = json_to_string(alias, "owner_filepath");
            string bytes = read_geometry_bytes(filepath);
            if (source != filepath || bytes != read_geometry_bytes(owner)
             || bytes.size() != static_cast<size_t>(alias["bytes"].int_value()))
                FATAL_ERROR("Stale or unequal FireRed geometry alias for %s.\n", label.c_str());
            text << "\t.global " << label << "\n"
                 << "\t.set " << label << ", " << json_to_string(alias, "owner") << "\n\n";
            return text.str();
        }
    }
    text << label << "::\n"
         << "\t.incbin \"" << filepath << "\"\n\n";
    return text.str();
}

bool same_geometry(const Json &a, const Json &b) {
    for (const string &key : {"width", "height", "primary_tileset", "secondary_tileset",
         "border_filepath", "blockdata_filepath", "layout_version", "border_width", "border_height", "blockdata_overrides", "blockdata_composition"})
        if (a[key] != b[key]) return false;
    return true;
}

string generate_map_header_text(Json map_data, Json layouts_data) {
    string map_layout_id = json_to_string(map_data, "layout");

    vector<Json> matched;

    for (auto &layout : layouts_data["layouts"].array_items()) {
        if (map_layout_id == json_to_string(layout, "id", true))
            matched.push_back(layout);
    }

    if (matched.size() != 1)
        FATAL_ERROR("Failed to find matching layout for %s.\n", map_layout_id.c_str());

    Json layout = matched[0];

    ostringstream text;

    string mapName = json_to_string(map_data, "name");
    bool mapGeometry = build_game == "FIRERED" && map_data["firered_geometry"].is_object();
    bool redundantGeometry = false;
    if (mapGeometry) {
        auto fields = layout.object_items();
        fields["firered_campaign"] = map_data["firered_geometry"];
        redundantGeometry = may_alias_current25_interior_descriptor(mapName, map_layout_id, layouts_data)
            && same_geometry(select_layout_geometry(fields), select_layout_geometry(layout));
        if (redundantGeometry) mapGeometry = false;
    }
    string geometryName = mapGeometry ? mapName + "_FireRedGeometry" : json_to_string(layout, "name");
    text << get_generated_warning("data/maps/" + mapName + "/map.json", true);

    text << mapName << ":\n"
         << "\t.4byte " << geometryName << "\n";

    if (map_data.object_items().find("shared_events_map") != map_data.object_items().end())
        text << "\t.4byte " << json_to_string(map_data, "shared_events_map") << "_MapEvents\n";
    else
        text << "\t.4byte " << mapName << "_MapEvents\n";

    if (map_data.object_items().find("shared_scripts_map") != map_data.object_items().end())
        text << "\t.4byte " << json_to_string(map_data, "shared_scripts_map") << "_MapScripts\n";
    else
        text << "\t.4byte " << mapName << "_MapScripts\n";

    if (map_data.object_items().find("connections") != map_data.object_items().end()
     && map_data["connections"].array_items().size() > 0 && json_to_string(map_data, "connections_no_include", true) != "TRUE")
        text << "\t.4byte " << mapName << "_MapConnections\n";
    else
        text << "\t.4byte NULL\n";

    text << "\t.2byte " << json_to_string(map_data, "music") << "\n"
         << "\t.2byte " << json_to_string(layout, "id") << "\n"
         << "\t.byte "  << json_to_string(map_data, "region_map_section") << "\n"
         << "\t.byte "  << json_to_string(map_data, "requires_flash") << "\n"
         << "\t.byte "  << json_to_string(map_data, "weather") << "\n"
         << "\t.byte "  << json_to_string(map_data, "map_type") << "\n";

    if (version != "firered")
        text << "\t.2byte 0\n";

    if (version == "ruby")
        text << "\t.byte " << json_to_string(map_data, "show_map_name") << "\n";
    else if (version == "emerald" || version == "firered" || version == "hns")
        text << "\tmap_header_flags "
             << "allow_cycling=" << json_to_string(map_data, "allow_cycling") << ", "
             << "allow_escaping=" << json_to_string(map_data, "allow_escaping") << ", "
             << "allow_running=" << json_to_string(map_data, "allow_running") << ", "
             << "show_map_name=" << json_to_string(map_data, "show_map_name") << "\n";

    if (version == "firered")
        text << "\t.byte " << json_to_string(map_data, "floor_number") << "\n";

     text << "\t.byte " << json_to_string(map_data, "battle_scene") << "\n\n";

    if (mapGeometry) {
        auto fields = layout.object_items();
        fields["firered_campaign"] = map_data["firered_geometry"];
        text << "\t.align 2\n"
             << generate_layout_geometry_text(select_layout_geometry(fields), geometryName);
    }
    if (redundantGeometry) {
        const string local = mapName + "_FireRedGeometry";
        for (const string &suffix : {"", "_Border", "_Blockdata"})
            text << "\t.global " << local << suffix << "\n"
                 << "\t.set " << local << suffix << ", " << geometryName << suffix << "\n";
        text << "\n";
    }

    return text.str();
}

vector<string> get_existing_maps() {
    vector<string> v = {};
    string map_constants = read_text_file("include/constants/map_groups.h");

    std::regex map_regex("(MAP_\\w+)\\s+=\\s+\\(\\d+");

    for (std::smatch sm; regex_search(map_constants, sm, map_regex);)
    {
        v.push_back(sm[1]);
        map_constants = sm.suffix();
    }
    return v;
}

string generate_map_connections_text(Json map_data) {
    if (map_data["connections"] == Json())
        return string("\n");

    string mapName = json_to_string(map_data, "name");

    vector<string> existing_maps = get_existing_maps();
    ostringstream text;
    text << get_generated_warning("data/maps/" + mapName + "/map.json", true);
    text << mapName << "_MapConnectionsList:\n";

    for (auto &connection : map_data["connections"].array_items()) {
        auto it = find(existing_maps.begin(), existing_maps.end(), json_to_string(connection, "map"));
        if (it == existing_maps.end())
            continue;
        text << "\tconnection "
             << json_to_string(connection, "direction") << ", "
             << json_to_string(connection, "offset") << ", "
             << json_to_string(connection, "map") << "\n";
    }

    text << "\n" << mapName << "_MapConnections:\n"
         << "\t.4byte " << map_data["connections"].array_items().size() << "\n"
         << "\t.4byte " << mapName << "_MapConnectionsList\n\n";

    return text.str();
}

string generate_map_events_text(Json map_data) {
    if (map_data.object_items().find("shared_events_map") != map_data.object_items().end())
        return string("\n");

    string mapName = json_to_string(map_data, "name");

    ostringstream text;
    text << get_generated_warning("data/maps/" + mapName + "/map.json", true);
    text << "\t.align 2\n\n";

    string objects_label, warps_label, coords_label, bgs_label;

    if (map_data["object_events"].array_items().size() > 0) {
        objects_label = mapName + "_ObjectEvents";
        text << objects_label << ":\n";
        for (unsigned int i = 0; i < map_data["object_events"].array_items().size(); i++) {
            auto obj_event = map_data["object_events"].array_items()[i];
            string type = json_to_string(obj_event, "type", true);

            // If no type field is present, assume it's a regular object event.
            if (type == "" || type == "object") {
                text << "\tobject_event " << i + 1 << ", "
                     << json_to_string(obj_event, "graphics_id") << ", "
                     << json_to_string(obj_event, "x") << ", "
                     << json_to_string(obj_event, "y") << ", "
                     << json_to_string(obj_event, "elevation") << ", "
                     << json_to_string(obj_event, "movement_type") << ", "
                     << json_to_string(obj_event, "movement_range_x") << ", "
                     << json_to_string(obj_event, "movement_range_y") << ", "
                     << json_to_string(obj_event, "trainer_type") << ", "
                     << json_to_string(obj_event, "trainer_sight_or_berry_tree_id") << ", "
                     << json_to_string(obj_event, "script") << ", "
                     << json_to_string(obj_event, "flag") << "\n";
            } else if (type == "clone") {
                text << "\tclone_event " << i + 1 << ", "
                     << json_to_string(obj_event, "graphics_id") << ", "
                     << json_to_string(obj_event, "x") << ", "
                     << json_to_string(obj_event, "y") << ", "
                     << json_to_string(obj_event, "target_local_id") << ", "
                     << json_to_string(obj_event, "target_map") << "\n";
            } else {
                FATAL_ERROR("Unknown object event type '%s'. Expected 'object' or 'clone'.\n", type.c_str());
            }
        }
        text << "\n";
    } else {
        objects_label = "NULL";
    }

    if (map_data["warp_events"].array_items().size() > 0) {
        warps_label = mapName + "_MapWarps";
        text << warps_label << ":\n";
        for (auto &warp_event : map_data["warp_events"].array_items()) {
            text << "\twarp_def "
                 << json_to_string(warp_event, "x") << ", "
                 << json_to_string(warp_event, "y") << ", "
                 << json_to_string(warp_event, "elevation") << ", "
                 << json_to_string(warp_event, "dest_warp_id") << ", "
                 << json_to_string(warp_event, "dest_map") << "\n";
        }
        text << "\n";
    } else {
        warps_label = "NULL";
    }

    if (map_data["coord_events"].array_items().size() > 0) {
        coords_label = mapName + "_MapCoordEvents";
        text << coords_label << ":\n";
        for (auto &coord_event : map_data["coord_events"].array_items()) {
            string type = json_to_string(coord_event, "type");
            if (type == "trigger") {
                text << "\tcoord_event "
                     << json_to_string(coord_event, "x") << ", "
                     << json_to_string(coord_event, "y") << ", "
                     << json_to_string(coord_event, "elevation") << ", "
                     << json_to_string(coord_event, "var") << ", "
                     << json_to_string(coord_event, "var_value") << ", "
                     << json_to_string(coord_event, "script") << "\n";
            }
            else if (type == "weather") {
                text << "\tcoord_weather_event "
                     << json_to_string(coord_event, "x") << ", "
                     << json_to_string(coord_event, "y") << ", "
                     << json_to_string(coord_event, "elevation") << ", "
                     << json_to_string(coord_event, "weather") << "\n";
            } else {
                FATAL_ERROR("Unknown coord event type '%s'. Expected 'trigger' or 'weather'.\n", type.c_str());
            }
        }
        text << "\n";
    } else {
        coords_label = "NULL";
    }

    if (map_data["bg_events"].array_items().size() > 0) {
        bgs_label = mapName + "_MapBGEvents";
        text << bgs_label << ":\n";
        for (auto &bg_event : map_data["bg_events"].array_items()) {
            string type = json_to_string(bg_event, "type");
            if (type == "sign") {
                text << "\tbg_sign_event "
                     << json_to_string(bg_event, "x") << ", "
                     << json_to_string(bg_event, "y") << ", "
                     << json_to_string(bg_event, "elevation") << ", "
                     << json_to_string(bg_event, "player_facing_dir") << ", "
                     << json_to_string(bg_event, "script") << "\n";
            }
            else if (type == "hidden_item") {
                string quantity = json_to_string(bg_event, "quantity", true);
                if (quantity.empty()) {
                    quantity = "1";
                }
                string underfoot = json_to_string(bg_event, "underfoot", true);
                if (underfoot.empty()) {
                    underfoot = "FALSE";
                }
                text << "\tbg_hidden_item_event "
                     << json_to_string(bg_event, "x") << ", "
                     << json_to_string(bg_event, "y") << ", "
                     << json_to_string(bg_event, "elevation") << ", "
                     << json_to_string(bg_event, "item") << ", "
                     << json_to_string(bg_event, "flag") << ", "
                     << quantity << ", "
                     << underfoot << "\n";
            }
            else if (type == "secret_base") {
                text << "\tbg_secret_base_event "
                     << json_to_string(bg_event, "x") << ", "
                     << json_to_string(bg_event, "y") << ", "
                     << json_to_string(bg_event, "elevation") << ", "
                     << json_to_string(bg_event, "secret_base_id") << "\n";
            } else {
                FATAL_ERROR("Unknown bg event type '%s'. Expected 'sign', 'hidden_item', or 'secret_base'.\n", type.c_str());
            }
        }
        text << "\n";
    } else {
        bgs_label = "NULL";
    }

    text << mapName << "_MapEvents::\n"
         << "\tmap_events " << objects_label << ", " << warps_label << ", "
         << coords_label << ", " << bgs_label << "\n\n";

    return text.str();
}

string strip_trailing_separator(string filename) {
    if(filename.back() == '/' || filename.back() == '\\')
        filename.pop_back();

    return filename;
}
void infer_separator(string filename) {
    size_t dir_pos = filename.find_last_of("/\\");
    sep = filename[dir_pos];
}
string file_parent(string filename){
    size_t dir_pos = filename.find_last_of("/\\");
    return filename.substr(0, dir_pos + 1);
}

void process_map(string map_filepath, string layouts_filepath, string output_dir) {
    string mapdata_err, layouts_err;

    string mapdata_json_text = read_text_file(map_filepath);
    string layouts_json_text = read_text_file(layouts_filepath);

    Json map_data = Json::parse(mapdata_json_text, mapdata_err);
    if (map_data == Json())
        FATAL_ERROR("%s\n", mapdata_err.c_str());

    Json layouts_data = Json::parse(layouts_json_text, layouts_err);
    if (layouts_data == Json())
        FATAL_ERROR("%s\n", layouts_err.c_str());

    map_data = select_map_events(map_data);
    string header_text = generate_map_header_text(map_data, layouts_data);
    string events_text = generate_map_events_text(map_data);
    string connections_text = generate_map_connections_text(map_data);

    string out_dir = strip_trailing_separator(output_dir).append(sep);
    write_text_file(out_dir + "header.inc", header_text);
    write_text_file(out_dir + "events.inc", events_text);
    write_text_file(out_dir + "connections.inc", connections_text);
}

void process_event_constants(const vector<string> &map_filepaths, string output_ids_file) {
    string warning = get_generated_warning("data/maps/*/map.json", false);

    string guard_name = "CONSTANTS_MAP_EVENT_IDS";
    ostringstream ids_file_text;
    ids_file_text << get_include_guard_start(guard_name) << warning;

    for (const string &filepath : map_filepaths) {
        string err;
        string map_json_text = read_text_file(filepath);
        Json map_data = Json::parse(map_json_text, err);
        if (map_data == Json())
            FATAL_ERROR("Failed to read '%s' while generating map event constants: %s\n", filepath.c_str(), err.c_str());

        map_data = select_map_events(map_data);
        string map_id = json_to_string(map_data, "id");

        // Get IDs from the object/clone events.
        ostringstream map_ids_text;
        auto obj_events = map_data["object_events"].array_items();
        for (unsigned int i = 0; i < obj_events.size(); i++) {
            auto obj_event = obj_events[i];
            if (obj_event.object_items().find("local_id") != obj_event.object_items().end())
                map_ids_text << "#define " << json_to_string(obj_event, "local_id") << " " << i + 1 << "\n";
        }
        // Get IDs from the warp events.
        auto warp_events = map_data["warp_events"].array_items();
        for (unsigned int i = 0; i < warp_events.size(); i++) {
            auto warp_event = warp_events[i];
            if (warp_event.object_items().find("warp_id") != warp_event.object_items().end())
                map_ids_text << "#define " << json_to_string(warp_event, "warp_id") << " " << i << "\n";
        }
        // Only output if we found any IDs
        string temp = map_ids_text.str();
        if (!temp.empty()) {
            ids_file_text << "// " << map_id << "\n" << temp << "\n";
        }
    }

    ids_file_text << get_include_guard_end(guard_name);
    write_text_file(output_ids_file, ids_file_text.str());
}

string generate_groups_text(Json groups_data, vector<string> &invalid_maps) {
    ostringstream text;

    text << get_generated_warning("data/maps/map_groups.json", true);

    for (auto &key : groups_data["group_order"].array_items()) {
        string group = json_to_string(key);
        auto maps = groups_data[group].array_items();

        text << group << "::\n";
        for (Json &map_name : maps) {
            string map_name_str = json_to_string(map_name);
            auto it = find(invalid_maps.begin(), invalid_maps.end(), map_name_str);
            if (it == invalid_maps.end()) {
                text << "\t.4byte " << map_name_str << "\n";
            } else {
                text << "\t.4byte NULL\n";
            }
        }
        text << "\n";
    }

    text << "\t.align 2\n" << "gMapGroups::\n";
    for (auto &group : groups_data["group_order"].array_items()) {
        text << "\t.4byte " << json_to_string(group) << "\n";
    }
    text << "\n";

    return text.str();
}

string generate_connections_text(Json groups_data, vector<string> &invalid_maps, string include_path) {
    vector<Json> map_names;

    for (auto &group : groups_data["group_order"].array_items()) {
        for (auto map_name : groups_data[json_to_string(group)].array_items()) {
            string map_name_str = json_to_string(map_name);
            auto it = find(invalid_maps.begin(), invalid_maps.end(), map_name_str);
            if (it == invalid_maps.end())
                map_names.push_back(map_name);
        }
    }

    vector<Json> connections_include_order = groups_data["connections_include_order"].array_items();

    if (connections_include_order.size() > 0)
        sort(map_names.begin(), map_names.end(), [connections_include_order](const Json &a, const Json &b) {
            auto iter_a = find(connections_include_order.begin(), connections_include_order.end(), a);
            if (iter_a == connections_include_order.end())
                iter_a = connections_include_order.begin() + numeric_limits<int>::max();
            auto iter_b = find(connections_include_order.begin(), connections_include_order.end(), b);
            if (iter_b == connections_include_order.end())
                iter_b = connections_include_order.begin() + numeric_limits<int>::max();
            return iter_a < iter_b;
        });

    ostringstream text;

    text << get_generated_warning("data/maps/map_groups.json", true);

    for (Json map_name : map_names)
        text << "\t.include \"" << include_path << "/" <<  json_to_string(map_name) << "/connections.inc\"\n";

    return text.str();
}

string generate_headers_text(Json groups_data, vector<string> &invalid_maps, string include_path) {
    vector<string> map_names;

    for (auto &group : groups_data["group_order"].array_items()) {
        for (auto map_name : groups_data[json_to_string(group)].array_items()) {
            string map_name_str = json_to_string(map_name);
            auto it = find(invalid_maps.begin(), invalid_maps.end(), map_name_str);
            if (it == invalid_maps.end())
                map_names.push_back(json_to_string(map_name));
        }
    }

    ostringstream text;

    text << get_generated_warning("data/maps/map_groups.json", true);

    for (string map_name : map_names)
        text << "\t.include \"" << include_path << "/" << map_name << "/header.inc\"\n";

    return text.str();
}

string generate_events_text(Json groups_data, vector<string> &invalid_maps, string include_path) {
    vector<string> map_names;

    for (auto &group : groups_data["group_order"].array_items()) {
        for (auto map_name : groups_data[json_to_string(group)].array_items()) {

            string map_name_str = json_to_string(map_name);
            auto it = find(invalid_maps.begin(), invalid_maps.end(), map_name_str);
            if (it == invalid_maps.end())
                map_names.push_back(json_to_string(map_name));
        }
    }

    ostringstream text;

    text << get_generated_warning(include_path + "/map_groups.json", true);

    for (string map_name : map_names)
        text << "\t.include \"" << include_path << "/" << map_name << "/events.inc\"\n";

    return text.str();
}

Json parse_required_map_defines(void) {
    string json_err;

    string json_text = read_text_file("tools/mapjson/required_map_defines.json");

    Json json_data = Json::parse(json_text, json_err);
    if (json_data == Json())
        FATAL_ERROR("%s\n", json_err.c_str());
    return json_data;
}

string generate_map_constants_text(string groups_filepath, Json groups_data, vector<string> &valid_map_ids) {
    string file_dir = file_parent(groups_filepath) + sep;

    string guard_name = "CONSTANTS_MAP_GROUPS";
    ostringstream text;
    ostringstream mapCountText;

    text << get_include_guard_start(guard_name) << get_generated_warning("data/maps/map_groups.json", false);

    text << "//\n// DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/map_groups.json\n//\n\n";

    text << "enum\n{\n";

    int group_num = 0;
    vector<int> map_count_vec; //DEBUG
    for (auto &group : groups_data["group_order"].array_items()) {
        string groupName = json_to_string(group);
        text << "    // " << groupName << "\n";
        vector<string> map_ids;
        size_t max_length = 0;

        int map_count = 0; //DEBUG

        for (auto &map_name : groups_data[groupName].array_items()) {
            string map_filepath = file_dir + json_to_string(map_name) + sep + "map.json";
            string err_str;
            Json map_data = Json::parse(read_text_file(map_filepath), err_str);
            if (map_data == Json())
                FATAL_ERROR("%s: %s\n", map_filepath.c_str(), err_str.c_str());
            string id = json_to_string(map_data, "id", true);
            map_ids.push_back(id);
            valid_map_ids.push_back(id);
            if (id.length() > max_length)
                max_length = id.length();
            map_count++; //DEBUG
        }

        int map_id_num = 0;
        for (string map_id : map_ids) {
            text << "    " << map_id << string(max_length - map_id.length(), ' ')
                 << " = (" << map_id_num++ << " | (" << group_num << " << 8)),\n";
        }

        text << "\n";

        group_num++;
        map_count_vec.push_back(map_count); //DEBUG
    }

    text << "};\n\n";

    text << "//Constants for unused maps\n";
    int map_id_num = 0;
    int old_map_group = -1;
    Json required_map_defines = parse_required_map_defines();
    map <int, string> filtered_map_defines;
    size_t max_length = 0;
    for (auto required_map_id : required_map_defines["required_maps"].array_items()) {
        string map_id = json_to_string(required_map_id[0]);
        auto it = find(valid_map_ids.begin(), valid_map_ids.end(), map_id);
        int current_map_group = required_map_id[1].int_value();
        if (old_map_group != current_map_group) {
            map_id_num = 0;
        } else {
            map_id_num++;
        }
        if (it == valid_map_ids.end()) {
            filtered_map_defines[(map_id_num + 256 * current_map_group)] = map_id;
            if (map_id.length() > max_length)
                max_length = map_id.length();
        }
        old_map_group = current_map_group;
    }

    for ( const auto &[map_value, map_id]: filtered_map_defines) {
        text << "#define " << map_id << string(max_length - map_id.length(), ' ')
             << "  " << map_value << "\n";
    }

    text << "\n#define MAP_GROUPS_COUNT " << group_num << "\n\n";
    text << get_include_guard_end(guard_name);

    char s = file_dir.back();
    mapCountText << "static const u8 MAP_GROUP_COUNT[] = {"; //DEBUG
    for(int i=0; i<group_num; i++){                          //DEBUG
        mapCountText << map_count_vec[i] << ", ";            //DEBUG
    }                                                        //DEBUG
    mapCountText << "0};\n";                                 //DEBUG
    write_text_file(file_dir + ".." + s + ".." + s + "src" + s + "data" + s + "map_group_count.h", mapCountText.str());

    return text.str();
}

void clean_heal_locations(vector<string> &valid_map_ids)
{
    std::stringstream new_json;
    std::ifstream infile("src/data/heal_locations.json");
    bool deleted_flag = false;

    std::regex map_regex("\"respawn_map\"\\s*:\\s*\"(MAP_\\w+)\"");
    std::regex npc_regex("LOCALID_\\w+");
    std::smatch map_match;
    string line;
    while (std::getline(infile, line))
    {
        if (std::regex_search(line, map_match, map_regex) && !deleted_flag) {
            auto it = find(valid_map_ids.begin(), valid_map_ids.end(), map_match[1]);
            if (it == valid_map_ids.end())
                deleted_flag = true;
        }
        if (deleted_flag && std::regex_search(line, npc_regex)) {
            deleted_flag = false;
            new_json << std::regex_replace(line, npc_regex, "0") << "\n";
        } else {
            new_json << line << "\n";
        }
    }

    write_text_file("src/data/heal_locations.json", new_json.str());
}

// Output paths are directories with trailing path separators
void process_groups(string groups_filepath, vector<string> &map_filepaths, string output_asm, string output_c) {
    output_asm = strip_trailing_separator(output_asm); // Remove separator if existing.
    output_c = strip_trailing_separator(output_c);

    string err;
    Json groups_data = Json::parse(read_text_file(groups_filepath), err);
    vector<string> invalid_maps;
    vector<string> valid_map_ids;

    for (const string &filepath : map_filepaths) {
        string err;
        string map_json_text = read_text_file(filepath);
        Json map_data = Json::parse(map_json_text, err);
        if (map_data == Json())
            FATAL_ERROR("Failed to read '%s' while processing groups: %s\n", filepath.c_str(), err.c_str());

        string game_ver = json_to_string(map_data, "game_version", true);
        if (game_ver.empty())
            game_ver = "emerald";

        string map_name = json_to_string(map_data, "name");

        string expected_game_ver = version;
        if (expected_game_ver == "firered")
            expected_game_ver = "frlg";

        if (game_ver != expected_game_ver && !is_firered_campaign_map(map_data)) {
            invalid_maps.push_back(map_name);
        }
    }

    if (groups_data == Json())
        FATAL_ERROR("%s\n", err.c_str());

    string groups_text = generate_groups_text(groups_data, invalid_maps);
    string connections_text = generate_connections_text(groups_data, invalid_maps, output_asm);
    string headers_text = generate_headers_text(groups_data, invalid_maps, output_asm);
    string events_text = generate_events_text(groups_data, invalid_maps, output_asm);
    string map_header_text = generate_map_constants_text(groups_filepath, groups_data, valid_map_ids);

    clean_heal_locations(valid_map_ids);
    write_text_file(output_asm + sep + "groups.inc", groups_text);
    write_text_file(output_asm + sep + "connections.inc", connections_text);
    write_text_file(output_asm + sep + "headers.inc", headers_text);
    write_text_file(output_asm + sep + "events.inc", events_text);
    write_text_file(output_c + sep + "map_groups.h", map_header_text);
}

bool layout_matches_version(const Json &layout) {
    string game_ver = json_to_string(layout, "game_version", true);
    if (game_ver.empty())
        game_ver = "emerald";
    string expected = version;
    if (expected == "firered")
        expected = "frlg";
    return game_ver == expected
        || (build_game == "FIRERED" && (layout["firered_campaign"].bool_value()
            || layout["firered_campaign"].is_object()));
}

// Native FireRed layouts may adopt donor geometry without changing identities.
// Existing boolean campaign selection and all other targets stay unchanged.
Json select_layout_geometry(const Json &layout_data) {
    if (build_game != "FIRERED" || !layout_data["firered_campaign"].is_object())
        return layout_data;
    auto fields = layout_data.object_items();
    for (const auto &field : layout_data["firered_campaign"].object_items()) {
        const string &key = field.first;
        if (key != "width" && key != "height" && key != "primary_tileset"
         && key != "secondary_tileset" && key != "border_filepath"
         && key != "blockdata_filepath" && key != "border_width"
         && key != "border_height" && key != "layout_version"
         && key != "blockdata_overrides" && key != "blockdata_composition")
            FATAL_ERROR("FireRed layout overlay cannot change '%s'.\n", key.c_str());
        fields[key] = field.second;
    }
    return fields;
}

// Sparse geometry adaptations retain the pinned binary as the source. Validate
// expected words before emitting unchanged incbin ranges and replacement words.
// This affects the host-generated readonly map data, not the native save format.

// A FireRed map can join original source rectangles without changing map IDs,
// provider assets or native structures. Every fill word is read from a pinned
// source; sparse expected-word replacements are checked after composition.
string generate_composed_layout_blockdata_text(const Json &layout) {
    const Json &composition = layout["blockdata_composition"];
    if (build_game != "FIRERED" || !composition.is_object()
     || composition.object_items().size() != 2
     || !composition["fill_source"].is_object()
     || !composition["parts"].is_array() || composition["parts"].array_items().empty())
        FATAL_ERROR("Source-grid composition requires a FireRed fill_source and parts.\n");
    auto integer = [](const Json &object, const string &key) {
        if (!object[key].is_number() || object[key].number_value() != object[key].int_value())
            FATAL_ERROR("Source-grid field '%s' must be an integer.\n", key.c_str());
        return object[key].int_value();
    };
    int width = integer(layout, "width");
    int height = integer(layout, "height");
    if (width <= 0 || height <= 0 || width > numeric_limits<int>::max() / height / 2)
        FATAL_ERROR("Invalid composed source-grid dimensions.\n");
    auto checked_bytes = [](const string &filepath) {
        if (filepath.empty()) FATAL_ERROR("Source-grid filepath is empty.\n");
        return read_geometry_bytes(filepath);
    };
    auto word_at = [](const string &bytes, int offset) {
        if (offset < 0 || offset % 2 || static_cast<size_t>(offset) > bytes.size() || bytes.size() - static_cast<size_t>(offset) < 2)
            FATAL_ERROR("Source-grid word offset is outside its pinned source.\n");
        return static_cast<unsigned char>(bytes[offset])
             | static_cast<unsigned char>(bytes[offset + 1]) << 8;
    };
    const Json &fill = composition["fill_source"];
    if (fill.object_items().size() != 3 || !fill["filepath"].is_string())
        FATAL_ERROR("Source-grid fill requires filepath, offset, expected.\n");
    string fill_path = fill["filepath"].string_value();
    int fill_offset = integer(fill, "offset");
    int fill_expected = integer(fill, "expected");
    string fill_bytes = checked_bytes(fill_path);
    int fill_word = word_at(fill_bytes, fill_offset);
    if (fill_expected < 0 || fill_expected > 65535 || fill_word != fill_expected)
        FATAL_ERROR("Source-grid fill expected word mismatch.\n");
    struct Origin { string filepath; int offset; int word; bool replacement; };
    vector<Origin> cells(width * height, {fill_path, fill_offset, fill_word, false});
    vector<bool> written(width * height, false);
    for (const Json &part : composition["parts"].array_items()) {
        if (!part.is_object() || part.object_items().size() != 9 || !part["filepath"].is_string())
            FATAL_ERROR("Source-grid part requires its nine explicit source/destination fields.\n");
        int sw = integer(part, "source_width"), sh = integer(part, "source_height");
        int sx = integer(part, "source_x"), sy = integer(part, "source_y");
        int pw = integer(part, "width"), ph = integer(part, "height");
        int dx = integer(part, "dest_x"), dy = integer(part, "dest_y");
        if (sw <= 0 || sh <= 0 || sw > numeric_limits<int>::max() / sh / 2
         || sx < 0 || sy < 0 || pw <= 0 || ph <= 0 || pw > sw || ph > sh
         || sx > sw - pw || sy > sh - ph || dx < 0 || dy < 0
         || pw > width || ph > height || dx > width - pw || dy > height - ph)
            FATAL_ERROR("Source-grid rectangle exceeds its original or target bounds.\n");
        string filepath = part["filepath"].string_value();
        string bytes = checked_bytes(filepath);
        if (bytes.size() != static_cast<size_t>(sw * sh * 2))
            FATAL_ERROR("Source-grid file size differs from its explicit dimensions.\n");
        for (int y = 0; y < ph; ++y)
            for (int x = 0; x < pw; ++x) {
                int dest = (dy + y) * width + dx + x;
                int offset = ((sy + y) * sw + sx + x) * 2;
                if (written[dest]) FATAL_ERROR("Source-grid rectangles overlap.\n");
                cells[dest] = {filepath, offset, word_at(bytes, offset), false};
                written[dest] = true;
            }
    }
    const Json &overrides = layout["blockdata_overrides"];
    if (overrides != Json()) {
        if (!overrides.is_array() || overrides.array_items().empty())
            FATAL_ERROR("Composed sparse overrides require a nonempty array.\n");
        vector<bool> edited(width * height, false);
        for (const Json &edit : overrides.array_items()) {
            if (!edit.is_object() || edit.object_items().size() != 4)
                FATAL_ERROR("Composed sparse edit requires x, y, expected, value.\n");
            int x = integer(edit, "x"), y = integer(edit, "y");
            int expected = integer(edit, "expected"), value = integer(edit, "value");
            if (x < 0 || y < 0 || x >= width || y >= height
             || expected < 0 || expected > 65535 || value < 0 || value > 65535)
                FATAL_ERROR("Composed sparse edit exceeds its geometry/word bounds.\n");
            int dest = y * width + x;
            if (edited[dest] || cells[dest].word != expected)
                FATAL_ERROR("Composed sparse expected word mismatch or duplicate coordinate.\n");
            cells[dest].word = value;
            cells[dest].replacement = true;
            edited[dest] = true;
        }
    }
    ostringstream text;
    for (size_t i = 0; i < cells.size();) {
        const Origin &first = cells[i];
        if (first.replacement) {
            text << "\t.2byte " << first.word << "\n";
            ++i;
            continue;
        }
        size_t end = i + 1;
        while (end < cells.size() && !cells[end].replacement
            && cells[end].filepath == first.filepath
            && cells[end].offset == first.offset + static_cast<int>((end - i) * 2)) ++end;
        if (end == i + 1) {
            while (end < cells.size() && !cells[end].replacement
                && cells[end].filepath == first.filepath && cells[end].offset == first.offset) ++end;
            if (end > i + 1) text << "\t.rept " << end - i << "\n";
            text << "\t.incbin \"" << first.filepath << "\", " << first.offset << ", 2\n";
            if (end > i + 1) text << "\t.endr\n";
        } else
            text << "\t.incbin \"" << first.filepath << "\", " << first.offset << ", " << (end - i) * 2 << "\n";
        i = end;
    }
    text << "\n";
    return text.str();
}

string generate_layout_blockdata_text(const Json &layout) {
    if (layout["blockdata_composition"] != Json())
        return generate_composed_layout_blockdata_text(layout);
    ostringstream text;
    string filepath = json_to_string(layout, "blockdata_filepath");
    const Json &overrides = layout["blockdata_overrides"];
    if (overrides == Json())
        return "\t.incbin \"" + filepath + "\"\n\n";
    if (build_game != "FIRERED" || !overrides.is_array() || overrides.array_items().empty())
        FATAL_ERROR("Sparse blockdata overrides require a nonempty FireRed geometry array.\n");
    int width = layout["width"].int_value();
    int height = layout["height"].int_value();
    if (width <= 0 || height <= 0 || width > numeric_limits<int>::max() / height / 2)
        FATAL_ERROR("Invalid sparse blockdata geometry dimensions.\n");
    ifstream input(filepath, std::ios::binary);
    if (!input.is_open())
        FATAL_ERROR("Cannot open sparse blockdata source '%s'.\n", filepath.c_str());
    input.seekg(0, std::ios::end);
    if (input.tellg() != width * height * 2)
        FATAL_ERROR("Sparse blockdata source size does not match geometry '%s'.\n", filepath.c_str());
    input.seekg(0, std::ios::beg);
    string bytes(width * height * 2, '\0');
    if (!input.read(&bytes[0], bytes.size()))
        FATAL_ERROR("Cannot read sparse blockdata source '%s'.\n", filepath.c_str());
    map<int, int> edits;
    for (const Json &edit : overrides.array_items()) {
        if (!edit.is_object() || edit.object_items().size() != 4)
            FATAL_ERROR("Sparse blockdata edit requires x, y, expected, value.\n");
        for (const string &key : {string("x"), string("y"), string("expected"), string("value")}) {
            if (!edit[key].is_number() || edit[key].number_value() != edit[key].int_value())
                FATAL_ERROR("Sparse blockdata edit '%s' must be an integer.\n", key.c_str());
        }
        int x = edit["x"].int_value();
        int y = edit["y"].int_value();
        int expected = edit["expected"].int_value();
        int value = edit["value"].int_value();
        if (x < 0 || y < 0 || x >= width || y >= height
         || expected < 0 || expected > 65535 || value < 0 || value > 65535)
            FATAL_ERROR("Sparse blockdata edit is outside its geometry/word bounds.\n");
        int offset = (y * width + x) * 2;
        int original = static_cast<unsigned char>(bytes[offset])
                     | static_cast<unsigned char>(bytes[offset + 1]) << 8;
        if (original != expected || !edits.emplace(offset, value).second)
            FATAL_ERROR("Sparse blockdata expected word mismatch or duplicate coordinate.\n");
    }
    int start = 0;
    for (const auto &edit : edits) {
        if (edit.first > start)
            text << "\t.incbin \"" << filepath << "\", " << start << ", " << edit.first - start << "\n";
        text << "\t.2byte " << edit.second << "\n";
        start = edit.first + 2;
    }
    if (start < static_cast<int>(bytes.size()))
        text << "\t.incbin \"" << filepath << "\", " << start << ", " << bytes.size() - start << "\n";
    text << "\n";
    return text.str();
}

string generate_layout_geometry_text(const Json &layout, const string &layoutName) {
    ostringstream text;
    string layout_version = json_to_string(layout, "layout_version", true);
    if (layout_version.empty())
        layout_version = "emerald";
    string border_label = layoutName + "_Border";
    string blockdata_label = layoutName + "_Blockdata";
    text << generate_geometry_payload_text(border_label, json_to_string(layout, "border_filepath"));
    if (layout["blockdata_overrides"] == Json() && layout["blockdata_composition"] == Json())
        text << generate_geometry_payload_text(blockdata_label, json_to_string(layout, "blockdata_filepath"));
    else {
        // Raw aliases must never bind to an owner whose emitted words differ.
        string err;
        Json aliases = Json::parse(read_text_file("data/layouts/firered_geometry_payload_aliases.json"), err)["aliases"];
        if (!err.empty() || !aliases.is_object())
            FATAL_ERROR("Invalid sparse owner alias plan.\n");
        for (const auto &alias : aliases.object_items())
            if (alias.second["owner"].string_value() == blockdata_label)
                FATAL_ERROR("Raw alias targets encoded sparse owner %s; regenerate alias plan.\n", blockdata_label.c_str());
        text << blockdata_label << "::\n" << generate_layout_blockdata_text(layout);
    }
    text << "\t.align 2\n"
         << layoutName << "::\n"
         << "\t.4byte " << json_to_string(layout, "width") << "\n"
         << "\t.4byte " << json_to_string(layout, "height") << "\n"
         << "\t.4byte " << border_label << "\n"
         << "\t.4byte " << blockdata_label << "\n"
         << "\t.4byte " << json_to_string(layout, "primary_tileset") << "\n"
         << "\t.4byte " << json_to_string(layout, "secondary_tileset") << "\n";
    if (layout_version == "frlg")
        text << "\t.byte 1\n"; // LAYOUT_VERSION_FRLG
    else if (layout_version == "hns")
        text << "\t.byte 2\n"; // LAYOUT_VERSION_HNS
    else
        text << "\t.byte 0\n"; // LAYOUT_VERSION_EMERALD

    if (layout_version == "frlg")
    {
        text << "\t.byte " << json_to_string(layout, "border_width") << "\n"
             << "\t.byte " << json_to_string(layout, "border_height") << "\n"
             << "\t.byte 0\n";
    }
    else
    {
        text << "\t.2byte 0\n"
             << "\t.byte 0\n";
    }
    text << "\n";
    return text.str();
}

string generate_layout_headers_text(Json layouts_data) {
    ostringstream text;

    text << get_generated_warning("data/layouts/layouts.json", true);

    for (const auto &layout_data : layouts_data["layouts"].array_items()) {
        if (layout_data == Json::object()) continue;
        if (!std::filesystem::exists(json_to_string(layout_data, "border_filepath")))
            continue;
        if (!layout_matches_version(layout_data))
            continue;
        Json layout = select_layout_geometry(layout_data);
        text << generate_layout_geometry_text(layout, json_to_string(layout, "name"));
    }

    return text.str();
}

string generate_layouts_table_text(Json layouts_data) {
    ostringstream text;
    vector<string> boundIds;
    const Json &bindings = layouts_data["firered_global_default_bindings"];
    if (build_game == "FIRERED" && bindings != Json() && !bindings.is_object())
        FATAL_ERROR("FireRed default layout bindings require an explicit object.\n");

    text << get_generated_warning("data/layouts/layouts.json", true);
    text << "\t.align 2\n"
         << json_to_string(layouts_data, "layouts_table_label") << "::\n";

    for (auto &layout : layouts_data["layouts"].array_items()) {
        if (!std::filesystem::exists(json_to_string(layout, "border_filepath")))
            continue;
        if (!layout_matches_version(layout)) {
            text << "\t.4byte NULL\n";
        } else {
            string layout_name = json_to_string(layout, "name", true);
            if (layout_name.empty()) layout_name = "NULL";
            const string id = json_to_string(layout, "id");
            const Json &binding = bindings[id];
            if (build_game == "FIRERED" && binding != Json()) {
                // Source-audited unique Kanto defaults retain original raw/global
                // descriptors; cold lookup uses the selected per-map owner.
                if (!binding.is_object() || binding.object_items().size() != 3
                 || layout["game_version"].string_value() != "frlg"
                 || binding["original_descriptor"].string_value() != layout_name)
                    FATAL_ERROR("Invalid FireRed default binding for %s.\n", id.c_str());
                const string owner = json_to_string(binding, "owner_map");
                const string selected = json_to_string(binding, "selected_descriptor");
                string err;
                Json map = Json::parse(read_text_file("data/maps/" + owner + "/map.json"), err);
                if (!err.empty() || map["name"].string_value() != owner
                 || map["layout"].string_value() != id
                 || map["game_version"].string_value() != "frlg"
                 || map["region"].string_value() != "REGION_KANTO"
                 || !map["firered_geometry"].is_object()
                 || selected != owner + "_FireRedGeometry"
                 || layouts_data["firered_global_geometry_aliases"][owner] != Json()
                 || may_alias_current25_interior_descriptor(owner, id, layouts_data))
                    FATAL_ERROR("Stale or coalesced FireRed default owner for %s.\n", id.c_str());
                if (find(boundIds.begin(), boundIds.end(), id) != boundIds.end())
                    FATAL_ERROR("Duplicate FireRed default slot for %s.\n", id.c_str());
                boundIds.push_back(id);
                layout_name = selected;
            }
            text << "\t.4byte " << layout_name << "\n";
        }
    }
    if (build_game == "FIRERED" && boundIds.size() != bindings.object_items().size())
        FATAL_ERROR("FireRed default binding has no active original layout slot.\n");
    return text.str();
}

vector<string> parse_required_layout_defines()
{
    vector<string> v;
    string json_err;

    string json_text = read_text_file("tools/mapjson/required_map_defines.json");

    Json json_data = Json::parse(json_text, json_err);
    if (json_data == Json())
        FATAL_ERROR("%s\n", json_err.c_str());

    for (auto required_layout : json_data["required_layouts"].array_items()) {
        v.push_back(json_to_string(required_layout));
    }

    return v;
}
string generate_layouts_constants_text(Json layouts_data) {
    string guard_name = "CONSTANTS_LAYOUTS";
    ostringstream text;
    vector<string> defined_layouts;
    text << get_include_guard_start(guard_name) << get_generated_warning("data/layouts/layouts.json", false);

    int i = 1;
    for (auto &layout : layouts_data["layouts"].array_items()) {
        if (!std::filesystem::exists(json_to_string(layout, "border_filepath")))
            continue;
        if (layout != Json::object())
        {
            text << "#define " << json_to_string(layout, "id") << " " << i << "\n";
            defined_layouts.push_back(json_to_string(layout, "id"));
        }
        i++;
    }

    text << "\n//Constants for unused layouts\n";
    vector<string> required_layout_defines = parse_required_layout_defines();
    vector<string> filtered_layout_defines;
    size_t max_length = 0;
    for (auto &layout : required_layout_defines) {
        auto it = find(defined_layouts.begin(), defined_layouts.end(), layout);
        if (it == defined_layouts.end()) {
            filtered_layout_defines.push_back(layout);
            if (layout.length() > max_length)
                max_length = layout.length();
        }
    }

    for (auto &layout : filtered_layout_defines) {
        text << "#define " << layout << string(max_length - layout.length(), ' ')
             << "  0xFFFF\n";
    }
    text << "\n" << get_include_guard_end(guard_name);

    return text.str();
}

void process_layouts(string layouts_filepath, string output_asm, string output_c) {
    output_asm = strip_trailing_separator(output_asm).append(sep);
    output_c = strip_trailing_separator(output_c).append(sep);

    string err;
    Json layouts_data = Json::parse(read_text_file(layouts_filepath), err);

    if (layouts_data == Json())
        FATAL_ERROR("%s\n", err.c_str());

    string layout_headers_text = generate_layout_headers_text(layouts_data);
    string layouts_table_text = generate_layouts_table_text(layouts_data);
    string layouts_constants_text = generate_layouts_constants_text(layouts_data);

    write_text_file(output_asm + "layouts.inc", layout_headers_text);
    write_text_file(output_asm + "layouts_table.inc", layouts_table_text);
    write_text_file(output_c + "layouts.h", layouts_constants_text);
}

int main(int argc, char *argv[]) {
    if (argc < 4)
        FATAL_ERROR("USAGE: mapjson <mode> <map-version> <game-target> [options]\n");

    char *version_arg = argv[2];
    version = string(version_arg);
    if (version != "emerald" && version != "ruby" && version != "firered" && version != "hns")
        FATAL_ERROR("ERROR: <game-version> must be 'emerald', 'firered', 'hns', or 'ruby'.\n");

    build_game = argv[3];
    if (build_game != "EMERALD" && build_game != "FIRERED"
        && build_game != "LEAFGREEN" && build_game != "POKEMON_HNS")
        FATAL_ERROR("Unsupported game target.\n");

    char *mode_arg = argv[1];
    string mode(mode_arg);
    if (mode == "map") {
        if (argc != 7)
            FATAL_ERROR("USAGE: mapjson map <map-version> <game-target> <map_file> <layouts_file> <output_dir>\n");

        infer_separator(argv[4]);
        string filepath(argv[4]);
        string layouts_filepath(argv[5]);
        string output_dir(argv[6]);

        process_map(filepath, layouts_filepath, output_dir);
    }
    else if (mode == "groups") {
        if (argc < 7)
            FATAL_ERROR("USAGE: mapjson groups <map-version> <game-target> <groups_file> <map_file> [additional_map_files] <output_asm_dir> <output_c_dir>\n");

        infer_separator(argv[4]);
        string filepath(argv[4]);

        vector<string> map_filepaths;
        const int firstMapFileArg = 5;
        const int lastMapFileArg = argc - 3;
        for (int i = firstMapFileArg; i <= lastMapFileArg; i++) {
            map_filepaths.push_back(argv[i]);
        }

        string output_asm(argv[argc - 2]);
        string output_c(argv[argc - 1]);

        process_groups(filepath, map_filepaths, output_asm, output_c);
    }
    else if (mode == "layouts") {
        if (argc != 7)
            FATAL_ERROR("USAGE: mapjson layouts <map-version> <game-target> <layouts_file> <output_asm_dir> <output_c_dir>\n");

        infer_separator(argv[4]);
        string filepath(argv[4]);
        string output_asm(argv[5]);
        string output_c(argv[6]);

        process_layouts(filepath, output_asm, output_c);
    }
    else if (mode == "event_constants") {
        if (argc < 6)
            FATAL_ERROR("USAGE: mapjson event_constants <map-version> <game-target> <map_file> [additional_map_files] <output_ids_file>");

        infer_separator(argv[4]);

        vector<string> filepaths;
        const int firstMapFileArg = 4;
        const int lastMapFileArg = argc - 2;
        for (int i = firstMapFileArg; i <= lastMapFileArg; i++) {
            filepaths.push_back(argv[i]);
        }
        string output_ids_file(argv[argc - 1]);

        process_event_constants(filepaths, output_ids_file);
    }
    else {
        FATAL_ERROR("ERROR: <mode> must be 'layouts', 'map', 'event_constants', or 'groups'.\n");
    }

    return 0;
}
