/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "DNSAnswer.h"
#include <AK/Stream.h>
#include <time.h>

namespace LookupServer {

DNSAnswer::DNSAnswer(const DNSName& name, DNSRecordType type, DNSRecordClass class_code, u32 ttl, const String& record_data, bool mdns_cache_flush)
    : m_name(name)
    , m_type(type)
    , m_class_code(class_code)
    , m_ttl(ttl)
    , m_record_data(record_data)
    , m_mdns_cache_flush(mdns_cache_flush)
{
    auto now = time(nullptr);
    m_expiration_time = now + m_ttl;
    if (m_expiration_time < now)
        m_expiration_time = 0;
}

bool DNSAnswer::has_expired() const
{
    return time(nullptr) >= m_expiration_time;
}

}

void AK::Formatter<LookupServer::DNSRecordType>::format(AK::FormatBuilder& builder, LookupServer::DNSRecordType value)
{
    switch (value) {
    case LookupServer::DNSRecordType::A:
        builder.put_string("A");
        return;
    case LookupServer::DNSRecordType::NS:
        builder.put_string("NS");
        return;
    case LookupServer::DNSRecordType::CNAME:
        builder.put_string("CNAME");
        return;
    case LookupServer::DNSRecordType::SOA:
        builder.put_string("SOA");
        return;
    case LookupServer::DNSRecordType::PTR:
        builder.put_string("PTR");
        return;
    case LookupServer::DNSRecordType::MX:
        builder.put_string("MX");
        return;
    }

    builder.put_string("DNS record type ");
    builder.put_u64((u16)value);
}

void AK::Formatter<LookupServer::DNSRecordClass>::format(AK::FormatBuilder& builder, LookupServer::DNSRecordClass value)
{
    switch (value) {
    case LookupServer::DNSRecordClass::IN:
        builder.put_string("IN");
        return;
    }

    builder.put_string("DNS record class ");
    builder.put_u64((u16)value);
}
