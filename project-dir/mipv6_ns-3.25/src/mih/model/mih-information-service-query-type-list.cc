/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */            
/*
 * Copyright (c) 2008 IT-SUDPARIS
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Providence SALUMU M. <Providence.Salumu_Munga@it-sudparis.eu>
 */

#include "mih-information-service-query-type-list.h"

namespace ns3 {
  namespace mih {
    InformationServiceQueryTypeList::InformationServiceQueryTypeList (uint64_t queryTypes) :
      m_bitmap (queryTypes)
    {}
    InformationServiceQueryTypeList::InformationServiceQueryTypeList (InformationServiceQueryTypeList const &o) :
      m_bitmap (o.m_bitmap)
    {}
    TLV_TYPE_HELPER_IMPLEM (InformationServiceQueryTypeList, TLV_MIIS_QUERY_TYPE_LIST)
    InformationServiceQueryTypeList::~InformationServiceQueryTypeList (void)
    {}
    uint64_t
    InformationServiceQueryTypeList::GetInformationServiceQueryTypes (void)
    {
      return m_bitmap;
    }
    void
    InformationServiceQueryTypeList::SetInformationServiceQueryTypes (uint64_t queryTypes)
    {
      m_bitmap = queryTypes;
    }
    uint32_t 
    InformationServiceQueryTypeList::GetTlvSerializedSize (void) const
    {
      return Tlv::GetSerializedSizeU64 ();
    }
    void 
    InformationServiceQueryTypeList::Print (std::ostream &os) const
    {
      os <<
        "MIIS queries = 0x" << std::hex << (uint64_t)m_bitmap 
                    << std::endl
        ;
    }
    void
    InformationServiceQueryTypeList::TlvSerialize (Buffer &buffer) const
    {
      Tlv::SerializeU64 (buffer, m_bitmap, TLV_MIIS_QUERY_TYPE_LIST);
    }
    uint32_t 
    InformationServiceQueryTypeList::TlvDeserialize (Buffer &buffer)
    {
      return Tlv::DeserializeU64 (buffer, m_bitmap, TLV_MIIS_QUERY_TYPE_LIST);
    }
  } // namespace mih
} // namespace ns3
