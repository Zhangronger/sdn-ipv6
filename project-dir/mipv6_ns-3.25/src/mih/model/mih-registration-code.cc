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
#include "mih-registration-code.h"

NS_LOG_COMPONENT_DEFINE ("RegistrationCode");

namespace ns3 {
  namespace mih {
    RegistrationCode::RegistrationCode (enum RegistrationCode::Type code) :
      m_code (code)
    {}
    RegistrationCode::RegistrationCode (RegistrationCode const &o) :
      m_code (o.m_code)
    {}
    enum RegistrationCode::Type 
    RegistrationCode::GetCode (void)
    {
      return m_code;
    }
    uint32_t 
    RegistrationCode::GetTlvSerializedSize (void) const
    {
      return Tlv::GetSerializedSizeU8 ();
    }
    void 
    RegistrationCode::Print (std::ostream &os) const
    {
      os << "Register Code = " << std::dec << static_cast<int> (m_code);
    }
    void
    RegistrationCode::TlvSerialize (Buffer &buffer) const
    {
      Tlv::SerializeU8 (buffer, static_cast<uint8_t> (m_code), TLV_REGISTRATION_CODE);
    }
    uint32_t 
    RegistrationCode::TlvDeserialize (Buffer &buffer)
    {
      uint32_t bytesRead = 0;
      uint8_t code = 0;
      bytesRead += Tlv::DeserializeU8 (buffer, code, TLV_REGISTRATION_CODE);
      m_code = static_cast<enum RegistrationCode::Type> (code);
      return bytesRead;
    }
    RegistrationCode& 
    RegistrationCode::operator = (RegistrationCode const &a)
    {
      m_code = a.m_code;
      return *this;
    }
    TLV_TYPE_HELPER_IMPLEM (RegistrationCode, TLV_REGISTRATION_CODE);
  } // namespace mih
} // namespace ns3
