#ifndef GDMMKV_H
#define GDMMKV_H

#include <godot_cpp/classes/object.hpp>
#include "MMKV/Core/MMKV.h"

namespace godot {

    class GDMMKV : public Object {
        GDCLASS(GDMMKV, Object);

        private:
            MMKV *store;
            String id;
            String root_path;
            
        protected:
            static void _bind_methods();
            String _to_string() const;
        public:
            // bool init_ref();
	        // bool reference();
	        // bool unreference();
	        // int32_t get_reference_count() const;

            GDMMKV();
            // GDMMKV(String root_path, String id);
            ~GDMMKV();
            void _process(double delta);
            void init(String root_path, String id);
            bool has_store(String id);
            void create_store(String id);
            bool set_current_store(String id);

            bool set_bool(String key, bool value);
            bool get_bool(String key, bool default_value);

            bool set_int(String key, int64_t value);
            int64_t get_int(String key, int64_t default_value);

            bool set_float(String key, double value);
            double get_float(String key, double default_value);

            bool set_vector2(String key, Vector2 value);
            Vector2 get_vector2(String key);

            bool set_vector2i(String key, Vector2i value);
            Vector2i get_vector2i(String key);

            bool remove_key(String key);
            bool has_key(String key);
    };
}

#endif