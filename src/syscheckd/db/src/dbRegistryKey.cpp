/*
 * Wazuh Syscheckd
 * Copyright (C) 2015-2021, Wazuh Inc.
 * October 15, 2021.
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public
 * License (version 2) as published by the FSF - Free Software
 * Foundation.
 */
#include "dbRegistryKey.hpp"
#include "fimCommonDefs.h"

void RegistryKey::createFimEntry()
{
    fim_entry* fim = reinterpret_cast<fim_entry*>(std::calloc(1, sizeof(fim_entry)));;
    fim_registry_key* key = reinterpret_cast<fim_registry_key*>(std::calloc(1, sizeof(fim_registry_key)));

    fim->type = FIM_TYPE_REGISTRY;
    key->id = std::atoi(m_identifier.c_str());
    key->arch = m_arch;
    std::strncpy(key->checksum, m_checksum.c_str(), sizeof(key->checksum));
    key->gid = reinterpret_cast<char*>(std::calloc(1, sizeof(char*)));
    std::strncpy(key->gid, std::to_string(m_gid).c_str(), sizeof(std::to_string(m_gid).size()));
    key->group_name = const_cast<char*>(m_groupname.c_str());
    key->last_event = m_lastEvent;
    key->mtime = m_time;
    key->path = const_cast<char*>(m_path.c_str());
    key->perm = const_cast<char*>(m_perm.c_str());
    key->scanned =  m_scanned;
    key->uid = reinterpret_cast<char*>(std::calloc(1, sizeof(char*)));
    std::strncpy(key->uid, std::to_string(m_uid).c_str(), sizeof(std::to_string(m_uid).size()));
    key->user_name = const_cast<char*>(m_username.c_str());
    fim->registry_entry.key = key;

    m_fimEntry = std::unique_ptr<fim_entry, FimRegistryKeyDeleter>(fim);
}

void RegistryKey::createJSON()
{
    nlohmann::json conf;
    nlohmann::json data;


    conf["table"] = FIMDB_REGISTRY_KEY_TABLENAME;
    data["name"] = m_identifier;
    data["path"] = m_path;
    data["arch"] = ((m_arch == 0) ? "[x32]" : "[x64]");
    data["last_event"] = m_lastEvent;
    data["scanned"] = m_scanned;
    data["checksum"] = m_checksum;
    data["perm"] = m_perm;
    data["uid"] = m_uid;
    data["gid"] = m_gid;
    data["user_name"] = m_username;
    data["group_name"] = m_groupname;
    data["mtime"] = m_time;
    conf["data"] = nlohmann::json::array({data});
    m_statementConf = std::make_unique<nlohmann::json>(conf);

}
