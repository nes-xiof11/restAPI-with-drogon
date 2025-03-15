#pragma once

#include <exception>
#include <optional>
#include <sys/select.h>
#include <vector>
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include <glog/logging.h>

namespace service 
{   
    template <typename Storage, typename Model>
    class crud 
    {
        protected:
            Storage &storage;
            std::string get_current_datatime() {
                using namespace sqlite_orm;
                return storage.template select(sqlite_orm::datetime("now")).front();
            }

        public:
            explicit crud(Storage& storage) : storage(storage)
            { }

            virtual long create(Model& model)
            {
                using namespace sqlite_orm;
                model.created_at = get_current_datatime();
                try {
                    return storage.template insert<Model>(model);
                } catch (const std::exception& e) {
                    LOG(ERROR) << e.what(); 
                }
                return (-1);
            }

            virtual bool update(Model& model)
            {
                try {
                    using namespace sqlite_orm;
                    model.updated_at = get_current_datatime();
                    model.created_at = storage.template select(&Model::created_at, where(c(&Model::id) == model.id)).front();
                    storage.template update<Model>(model);
                    return true;
                } catch (const std::exception& e) {
                    LOG(ERROR) << e.what();
                }
                return false;
            }

            virtual bool remove_by_id(long id)
            {
                try {
                    using namespace sqlite_orm;
                    storage.template remove_all<Model>(where(c(&Model::id) == id));
                    return true;
                } catch (const std::exception& e) {
                    LOG(ERROR) << e.what();
                } return false;
            }

            virtual std::optional<std::vector<Model>> get_all()
            {
                auto all = storage.template get_all<Model>();
                if (all.empty())
                    return std::nullopt;
                return all;
            }

            virtual std::optional<std::vector<Model>> get_by_id(long id)
            {
                using namespace sqlite_orm;
                auto model = storage.template get_all<Model>(where(c(&Model::id) == id));
                if (model.empty())
                    return std::nullopt;
                return model;
            }
    };

}