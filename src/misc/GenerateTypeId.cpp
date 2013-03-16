/*
 * Copyright 2010 Mohammad Abdulfatah. All rights reserved.
 *
 * Licensed under the MIT license:
 *
 *     http://www.opensource.org/licenses/mit-license.php
 *
 */

#include "GenerateTypeId.h"

#include <string>
#include <unordered_map>
#include <boost/crc.hpp>
#include <cassert>
#include <cstring>
#include <QtCore>



namespace
{
void EnsureUniqueIdOrDie(const char * typeName, unsigned int id);

int GenerateCrcChecksum(const char * data,
                        uint8_t ** checksum,
                        int checksumSize);
}

unsigned int GenerateTypeId(const char * typeName)
{
    typedef std::unordered_map<const char *, unsigned int> id_cache_type;

    static id_cache_type idCache;

    if (std::strlen(typeName) == 0)
        return 0;

    id_cache_type::const_iterator i = idCache.find(typeName);

    if (i != idCache.end())
        return i->second;

    unsigned int id = 0;
    uint8_t * idAsByteArray = reinterpret_cast<uint8_t *>(&id);
    int bytesInInt = sizeof(unsigned int) / sizeof(uint8_t);
    int byteCount = GenerateCrcChecksum(typeName,
                                        &idAsByteArray,
                                        bytesInInt);

    if (byteCount > 0) {
        EnsureUniqueIdOrDie(typeName, id);
        idCache[typeName] = id;
    }

    return id;
}

namespace
{
void EnsureUniqueIdOrDie(const char * typeName, unsigned int id)
{
#ifndef _DEBUG
    Q_UNUSED(typeName);
    Q_UNUSED(id);
#endif
#ifdef _DEBUG
    typedef std::unordered_map<unsigned int, const char *> id_to_type_map_t;

    static id_to_type_map_t idToTypeMap;

    id_to_type_map_t::const_iterator i = idToTypeMap.find(id);

    if (i != idToTypeMap.end()) {
        std::string storedTypeName(i->second);
        assert(storedTypeName == std::string(typeName));
    }

#endif
}

int GenerateCrcChecksum
(const char * data
 , uint8_t ** checksum
 , int checksumSize
)
{
    if (checksumSize == 0)
        return 0;

    boost::crc_32_type crcGenerator;
    int dataSize = std::strlen(data) * sizeof(uint8_t) / sizeof(char);
    crcGenerator.process_bytes(data, dataSize);

    boost::crc_32_type::value_type crc = crcGenerator.checksum();

    int crcSize = sizeof(boost::crc_32_type::value_type) / sizeof(uint8_t);
    int numberOfBytesToCopy
        = (crcSize < checksumSize) ? crcSize : checksumSize;

    uint8_t * crcAsByteArray = reinterpret_cast<uint8_t *>(&crc);

    for (int i = 0; i < numberOfBytesToCopy; ++i) {
        (*checksum)[i] = crcAsByteArray[i];
    }

    return numberOfBytesToCopy;
}
}
