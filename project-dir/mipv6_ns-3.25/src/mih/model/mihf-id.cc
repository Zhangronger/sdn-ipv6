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

#include "ns3/log.h"
#include "ns3/assert.h"
#include "mihf-id.h"

NS_LOG_COMPONENT_DEFINE ("MihfId");

namespace ns3 {
  namespace mih {
    MihfId::MihfId (void) :
      m_mihfid ("")
    {}
    MihfId::MihfId (std::string mihfid) :
      m_mihfid (mihfid)
    {
      NS_ASSERT (mihfid.length () <= 253);
    }
    MihfId::MihfId (MihfId const &o) :
      m_mihfid (o.m_mihfid)
    {}
    TLV_TYPE_HELPER_IMPLEM (MihfId, TLV_SOURCE_MIHFID)
    const char * 
    MihfId::PeekString (void) const
    {
      return m_mihfid.c_str ();
    }
    uint32_t 
    MihfId::GetTlvSerializedSize (void) const
    {
      return Tlv::GetSerializedSizeString (m_mihfid);
    }
    void
    MihfId::Print (std::ostream &os) const
    {
      os << "MihfId = " << m_mihfid << std::endl;
    }
    void 
    MihfId::TlvSerialize (Buffer &buffer) const
    {
      Tlv::SerializeString (buffer, m_mihfid, GetTlvTypeValue ());
    }
    uint32_t 
    MihfId::TlvDeserialize (Buffer &buffer)
    {
      return Tlv::DeserializeString (buffer, m_mihfid, GetTlvTypeValue ());
    }
    MihfId&
    MihfId::operator = (MihfId const &o)
    {
      m_mihfid = o.m_mihfid;
      return *this;
    }
    bool 
    operator == (const MihfId &a, const MihfId &b)
    {
      return (a.m_mihfid.compare (b.m_mihfid) == 0);
    }
    bool 
    operator != (const MihfId &a, const MihfId &b)
    {
      return (a.m_mihfid.compare (b.m_mihfid) != 0);
    }

    bool
    operator < (const MihfId &a, const MihfId &b)
    {
      return (a.m_mihfid.compare (b.m_mihfid) < 0 ? true : false);
    }

    ATTRIBUTE_HELPER_CPP (MihfId);
    
    std::ostream &
    operator << (std::ostream &os, const MihfId &mihfId)
    {
      os << mihfId.PeekString ();
      return os;
    }
    
    std::istream &operator >> (std::istream &is, MihfId &mihfId)
    {
      std::string str;
      is >> str;
      mihfId = MihfId (str.c_str ());
      return is;
    }
    
  } // namespace mih
} // namespace ns3
