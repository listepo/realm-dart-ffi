#include <iostream>

#include "wrapper.h"
#include "database.h"
#include "impl/object_accessor_impl.hpp"
#include <realm/group_shared.hpp>
#define typeof __typeof__

struct database
{
	void *db;
};

struct realm_object
{
	void *obj;
};

database_t *create(const char *db_name, const char *schema)
{
	database_t *db_ptr;
	Database *db;

	db_ptr = (typeof(db_ptr))malloc(sizeof(*db_ptr));
	db = new Database(db_name, schema);
	db_ptr->db = db;

	return db_ptr;
}

void destroy(database_t *db_ptr)
{
	if (db_ptr == NULL)
		return;
	delete static_cast<Database *>(db_ptr->db);
	free(db_ptr);
}

// ***********      REALM      *********** //

void begin_transaction(database_t *db_ptr)
{
	Database *db = static_cast<Database *>(db_ptr->db);
	db->realm()->begin_transaction();
}

void commit_transaction(database_t *db_ptr)
{
	Database *db = static_cast<Database *>(db_ptr->db);
	db->realm()->commit_transaction();
}

void cancel_transaction(database_t *db_ptr)
{
	Database *db = static_cast<Database *>(db_ptr->db);
	db->realm()->cancel_transaction();
}

// *********** OBJECT ACCESSOR *********** //

realm_object_t *add_object(database_t *db_ptr, const char *object_type)
{
	Database *db = static_cast<Database *>(db_ptr->db);
	auto &table = *db->realm()->read_group().get_table(std::string("class_").append(object_type));
	size_t row_ndx = table.add_empty_row();
	Object *obj = new Object(db->realm(), object_type, row_ndx);

	realm_object_t *obj_ptr;
	obj_ptr = (typeof(obj_ptr))malloc(sizeof(*obj_ptr)); //TODO heap allocation, remember to deallocate either manually or using finalizers once Dart supports it
	obj_ptr->obj = obj;

	return obj_ptr;
}

int8_t object_get_bool(realm_object_t *obj_ptr, const char *property_name)
{
	realm::Object *obj = static_cast<realm::Object *>(obj_ptr->obj);
	realm::CppContext context(obj->realm()); //FIXME is this the best way to get the context (caching?)
	return any_cast<bool>(obj->get_property_value<util::Any>(context, property_name)) == true ? 1 : 0;
}

int64_t object_get_int64(realm_object_t *obj_ptr, const char *property_name)
{
	realm::Object *obj = static_cast<realm::Object *>(obj_ptr->obj);
	realm::CppContext context(obj->realm());
	return any_cast<int64_t>(obj->get_property_value<util::Any>(context, property_name));
}

double object_get_double(realm_object_t *obj_ptr, const char *property_name)
{
	realm::Object *obj = static_cast<realm::Object *>(obj_ptr->obj);
	realm::CppContext context(obj->realm());
	return any_cast<double>(obj->get_property_value<util::Any>(context, property_name));
}

const char *object_get_string(realm_object_t *obj_ptr, const char *property_name)
{
	realm::Object *obj = static_cast<realm::Object *>(obj_ptr->obj);
	realm::CppContext context(obj->realm());
	std::string value = realm::util::any_cast<std::string>(obj->get_property_value<util::Any>(context, property_name));
	char *data = new char[value.size()];
	std::strcpy(data, value.c_str());
	return data;
}

template <typename ValueType>
void object_set_value(realm_object_t *obj_ptr, const char *property_name, ValueType value)
{
	realm::Object *obj = static_cast<realm::Object *>(obj_ptr->obj);
	realm::CppContext context(obj->realm()); //FIXME is this the right way to invoke the set_property? can we cache the context?
	obj->set_property_value(context, property_name, value, false);
}

void object_set_bool(realm_object_t *obj_ptr, const char *property_name, int8_t value)
{
	object_set_value(obj_ptr, property_name, util::Any(value == true ? 1 : 0));
}

void object_set_int64(realm_object_t *obj_ptr, const char *property_name, int64_t value)
{
	object_set_value(obj_ptr, property_name, util::Any(value));
}

void object_set_double(realm_object_t *obj_ptr, const char *property_name, double value)
{
	object_set_value(obj_ptr, property_name, util::Any(value));
}

void object_set_string(realm_object_t *obj_ptr, const char *property_name, const char *value)
{
	object_set_value(obj_ptr, property_name, util::Any(std::string(value)));
}