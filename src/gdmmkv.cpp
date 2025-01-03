#ifndef GFMMKV
#define GFMMKV

#include <string>
#include <map>
#include <locale>
#include <codecvt>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/engine_ptrcall.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include "MMKV/Core/MMKV.h"
#include "MMKV/Core/MemoryFile.h"
#include "gdmmkv.h"

using namespace godot;

// std::map<std::string, MMKV*> stores = {};

bool isFileExist(const MMKVPath_t &nsFilePath) {
    if (nsFilePath.empty()) {
        return false;
    }
    auto attribute = GetFileAttributesW(nsFilePath.c_str());
    return (attribute != INVALID_FILE_ATTRIBUTES);
}

void GDMMKV::_bind_methods() {
    // ClassDB::bind_method(D_METHOD("GDMMKV", "file_path", "id"), &GDMMKV::init, DEFVAL("default"));
    ClassDB::bind_method(D_METHOD("init", "file_path", "id"), &GDMMKV::init, DEFVAL("default"));
    
    ClassDB::bind_method(D_METHOD("create_store", "id"), &GDMMKV::create_store);
    ClassDB::bind_method(D_METHOD("has_store", "id"), &GDMMKV::has_store);

    ClassDB::bind_method(D_METHOD("remove_key", "key"), &GDMMKV::remove_key);
    ClassDB::bind_method(D_METHOD("has_key", "key"), &GDMMKV::has_key);

    ClassDB::bind_method(D_METHOD("set_bool", "key", "value"), &GDMMKV::set_bool);
    ClassDB::bind_method(D_METHOD("get_bool", "key", "default_value"), &GDMMKV::get_bool, DEFVAL(false));

    ClassDB::bind_method(D_METHOD("set_int", "key", "value"), &GDMMKV::set_int);
    ClassDB::bind_method(D_METHOD("get_int", "key", "default_value"), &GDMMKV::get_int, DEFVAL(0));

    ClassDB::bind_method(D_METHOD("set_float", "key", "value"), &GDMMKV::set_float);
    ClassDB::bind_method(D_METHOD("get_float", "key", "default_value"), &GDMMKV::get_float, DEFVAL(0.0f));

    ClassDB::bind_method(D_METHOD("set_vector2", "key", "value"), &GDMMKV::set_vector2);
    ClassDB::bind_method(D_METHOD("get_vector2", "key"), &GDMMKV::get_vector2);

    ClassDB::bind_method(D_METHOD("set_vector2i", "key", "value"), &GDMMKV::set_vector2i);
    ClassDB::bind_method(D_METHOD("get_vector2i", "key"), &GDMMKV::get_vector2i);

    
}

// bool GDMMKV::init_ref() {
// 	static GDExtensionMethodBindPtr _gde_method_bind = internal::gdextension_interface_classdb_get_method_bind(GDMMKV::get_class_static()._native_ptr(), StringName("init_ref")._native_ptr(), 22409110601);
// 	CHECK_METHOD_BIND_RET(_gde_method_bind, false);
// 	return internal::_call_native_mb_ret<int8_t>(_gde_method_bind, _owner);
// }

// bool GDMMKV::reference() {
// 	static GDExtensionMethodBindPtr _gde_method_bind = internal::gdextension_interface_classdb_get_method_bind(GDMMKV::get_class_static()._native_ptr(), StringName("reference")._native_ptr(), 22409110601);
// 	CHECK_METHOD_BIND_RET(_gde_method_bind, false);
// 	return internal::_call_native_mb_ret<int8_t>(_gde_method_bind, _owner);
// }

// bool GDMMKV::unreference() {
// 	static GDExtensionMethodBindPtr _gde_method_bind = internal::gdextension_interface_classdb_get_method_bind(GDMMKV::get_class_static()._native_ptr(), StringName("unreference")._native_ptr(), 22409110601);
// 	CHECK_METHOD_BIND_RET(_gde_method_bind, false);
// 	return internal::_call_native_mb_ret<int8_t>(_gde_method_bind, _owner);
// }

// int32_t GDMMKV::get_reference_count() const {
// 	static GDExtensionMethodBindPtr _gde_method_bind = internal::gdextension_interface_classdb_get_method_bind(GDMMKV::get_class_static()._native_ptr(), StringName("get_reference_count")._native_ptr(), 39052457861);
// 	CHECK_METHOD_BIND_RET(_gde_method_bind, 0);
// 	return internal::_call_native_mb_ret<int64_t>(_gde_method_bind, _owner);
// }

String GDMMKV::_to_string() const {
	return "<GDMMKV#" + uitos(get_instance_id()) + " " + this->id + ">";
}

GDMMKV::GDMMKV() {}

// GDMMKV::GDMMKV(String file_path, String id = "default") {
//     MMKV::initializeMMKV(std::wstring(file_path.wide_string()));
//     stores[std::string(id.utf8())] = MMKV::mmkvWithID(std::string(id.utf8()), MMKV_MULTI_PROCESS);
//     this->store = stores[std::string(id.utf8())];
// }

GDMMKV::~GDMMKV() {
    this->store->close();
}


void GDMMKV::_process(double delta) {
    // UtilityFunctions::print("MMKV process");
}

void GDMMKV::init(String root_path, String id = "default") {
    MMKV::initializeMMKV(std::wstring(root_path.wide_string()));
    this->root_path = root_path;
    this->id = id;
    this->store = MMKV::mmkvWithID(std::string(id.utf8()));
}

bool GDMMKV::has_store(String id) {
    std::wstring path = std::wstring(this->root_path.wide_string()) + MMKV_PATH_SLASH + std::wstring(id.wide_string());
    
    // if (std::wstring(id.wide_string()).empty()) {
        // return false;
    // }
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string narrow_string = converter.to_bytes(path);
    // auto attribute = GetFileAttributesW(path.c_str());
    // return (attribute != INVALID_FILE_ATTRIBUTES);
    struct stat buffer;   
    return (stat (narrow_string.c_str(), &buffer) == 0); 
}

void GDMMKV::create_store(String id) {
    this->id = id;
    this->store = MMKV::mmkvWithID(std::string(id.utf8()));
}

// bool GDMMKV::set_current_store(String id) {
//     if (stores.count(std::string(id.utf8())) == 1) {
//         this->store = stores[std::string(id.utf8())];
//         return true;
//     }
//     return false;
// }

bool GDMMKV::set_bool(String key, bool value) {
    const std::string utf8_key = std::string(key.utf8());
    return this->store->set(value, utf8_key);
}

bool GDMMKV::get_bool(String key, bool default_value = false) {
    const std::string utf8_key = std::string(key.utf8());
    if (this->store->containsKey(utf8_key)) {
        return this->store->getBool(utf8_key, default_value);
    }
    return Variant();
}

bool GDMMKV::set_int(String key, int64_t value) {
    const std::string utf8_key = std::string(key.utf8());
    return this->store->set(value, utf8_key);
}

int64_t GDMMKV::get_int(String key, int64_t default_value = 0) {
    const std::string utf8_key = std::string(key.utf8());
    UtilityFunctions::prints(this->store->containsKey(utf8_key));
    if (this->store->containsKey(utf8_key)) {
        return this->store->getInt64(utf8_key, default_value);
    }
    return Variant();
}

bool GDMMKV::set_float(String key, double value) {
    const std::string utf8_key = std::string(key.utf8());
    return this->store->set(value, utf8_key);
}

double GDMMKV::get_float(String key, double default_value = 0.0f) {
    const std::string utf8_key = std::string(key.utf8());
    if (this->store->containsKey(utf8_key)) {
        return this->store->getDouble(utf8_key, default_value);
    }
    return Variant();
}

bool GDMMKV::set_vector2(String key, Vector2 value) {
    std::vector<std::string> v = {std::to_string(value.x), std::to_string(value.y)};
    return this->store->set(v, std::string(key.utf8()));
}

Vector2 GDMMKV::get_vector2(String key) {
    std::vector<std::string> v;
    const std::string utf8_key = std::string(key.utf8());
    bool res = this->store->getVector(utf8_key, v);
    if (this->store->containsKey(utf8_key) && res && v.size() == 2) {
        return Vector2(std::stof(v[0]), std::stof(v[1]));
    }
    return Variant();
}

bool GDMMKV::set_vector2i(String key, Vector2i value) {
    std::vector<std::string> v = {std::to_string(value.x), std::to_string(value.y)};
    return this->store->set(v, std::string(key.utf8()));
}

Vector2i GDMMKV::get_vector2i(String key) {
    std::vector<std::string> v;
    const std::string utf8_key = std::string(key.utf8());
    bool res = this->store->getVector(utf8_key, v);
    if (this->store->containsKey(utf8_key) && res && v.size() == 2) {
        return Vector2i(std::stof(v[0]), std::stof(v[1]));
    }
    return Variant();
}


bool GDMMKV::remove_key(String key) {
    return this->store->removeValueForKey(std::string(key.utf8()));
}

bool GDMMKV::has_key(String key) {
    return this->store->containsKey(std::string(key.utf8()));
}

#endif