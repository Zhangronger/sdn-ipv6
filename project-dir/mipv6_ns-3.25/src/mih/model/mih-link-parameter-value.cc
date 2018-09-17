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

#include "mih-link-parameter-value.h"

namespace ns3 {
  namespace mih {
    LinkParameterValue::LinkParameterValue (uint16_t value) :
      m_value (value)
    {
      SimulationSingleton<TlvObjectFactory<ParameterValue> >::Get ()->AddTlvTypeConstructor (TLV_LINK_PARAMETER_VALUE,
                                                                                             MakeCallback (&LinkParameterValue::Create));
    }
    LinkParameterValue::LinkParameterValue (LinkParameterValue const &o) :
      m_value (o.m_value)
    {}
    uint16_t 
    LinkParameterValue::GetValue (void)
    {
      return m_value;
    }
    CHOICE_HELPER_IMPLEM (LinkParameterValue, ParameterValue);
    TLV_TYPE_HELPER_IMPLEM (LinkParameterValue, TLV_LINK_PARAMETER_VALUE);
    uint32_t
    LinkParameterValue::GetTlvSerializedSize (void) const
    {
      return Tlv::GetSerializedSizeU16 ();
    }
    void 
    LinkParameterValue::Print (std::ostream &os) const
    {
      os << "Link Parameter Value = " << std::dec << (int) m_value << std::endl;
    }
    void
    LinkParameterValue::TlvSerialize (Buffer &buffer) const
    {
      Tlv::SerializeU16 (buffer, m_value, TLV_LINK_PARAMETER_VALUE);
    }
    uint32_t
    LinkParameterValue::TlvDeserialize (Buffer &buffer)
    {
      return Tlv::DeserializeU16 (buffer, m_value, TLV_LINK_PARAMETER_VALUE);
    }
  } // namespace mih
} // namespace ns3
