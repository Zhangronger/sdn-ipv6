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

#include <string>
#include "mih-status.h"

namespace ns3 {
  namespace mih {
    Status::Status (enum Status::Type code) :
      m_type (code)
    {}
    Status::Status (Status const &o) :
      m_type (o.m_type)
    {}
    TLV_TYPE_HELPER_IMPLEM (Status, TLV_STATUS)
    void 
    Status::SetType (enum Status::Type code)
    {
      m_type = code;
    }
    enum Status::Type 
    Status::GetType (void)
    {
      return m_type;
    }
    uint32_t
    Status::GetTlvSerializedSize (void) const
    {
      return Tlv::GetSerializedSizeU8 ();
    }
    void
    Status::Print (std::ostream &os) const
    {
      os << "Status = " << static_cast<int> (m_type) << std::endl;
    }
    void
    Status::TlvSerialize (Buffer &buffer) const
    {
      Tlv::SerializeU8 (buffer, static_cast<uint8_t> (m_type), TLV_STATUS);
    }
    uint32_t
    Status::TlvDeserialize (Buffer &buffer)
    {
      uint32_t bytesRead = 0;
      uint8_t typ = 0;
      bytesRead += Tlv::DeserializeU8 (buffer, typ, TLV_STATUS);
      m_type = static_cast<enum Status::Type> (typ);
      return bytesRead;
    }
    std::ostream& 
    operator << (std::ostream &os, const Status &a)
    {
      std::string status = "INVALID";
      switch (a.m_type)
        {
        case Status::SUCCESS :
          {
            status = "SUCCESS";
            break;
          }
        case Status::UNSPECIFIED_FAILURE :
          {
            status = "SUCCESS";
            break;
          }
        case Status::REJECTED :
          {
            status = "REJECTED";
            break;
          }
        case Status::AUTHORIZATION_FAILURE :
          {
            status = "AUTHORIZATION_FAILURE";
            break;
          }
        case Status::NETWORK_ERROR :
          {
            status = "NETWORK_ERROR";
            break;
          }
        default:
          break;
        }
      os << status;
      return os;
    }
  } // namespace mih
} // namespace ns3
