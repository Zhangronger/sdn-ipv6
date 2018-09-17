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

#include "mih-link-parameter-80211.h"

namespace ns3 {
  namespace mih {
    LinkParameter80211::LinkParameter80211 (uint8_t paramterCode) :
      m_parameterCode (paramterCode)
    {
      SimulationSingleton<TlvObjectFactory<LinkParameterType> >::Get ()->AddTlvTypeConstructor (TLV_LINK_PARAMETER_802_11,
                                                                                                MakeCallback (&LinkParameter80211::Create));
    }
    LinkParameter80211::LinkParameter80211 (LinkParameter80211 const &o) :
      m_parameterCode (o.m_parameterCode)
    {}
    uint8_t 
    LinkParameter80211::GetParameterCode (void)
    {
      return m_parameterCode;
    }
    CHOICE_HELPER_IMPLEM (LinkParameter80211, LinkParameterType)
    TLV_TYPE_HELPER_IMPLEM (LinkParameter80211, TLV_LINK_PARAMETER_802_11)
    uint32_t
    LinkParameter80211::GetTlvSerializedSize (void) const 
    {
      return Tlv::GetSerializedSizeU8 ();
    }
    void 
    LinkParameter80211::Print (std::ostream &os) const 
    {
      std::string codestr = " (INVALID) ";
      switch (m_parameterCode)
        {
        case LinkParameter80211::BEACON_CHANNEL_RSSI :
          {
            codestr = " (BEACON_CHANNEL_RSSI) ";
            break;
          }
        case LinkParameter80211::NO_QOS_RESOURCE_AVAILABLE :
          {
            codestr = " (NO_QOS_RESOURCE_AVAILABLE) ";
            break;
          }
        case LinkParameter80211::MULTICAST_PACKET_LOSS_RATE :
          {
            codestr = " (MULTICAST_PACKET_LOSS_RATE) ";
            break;
          }
        default:
          {
            codestr = " (INVALID) ";
            break;
          }
        }
      os << "Link Parameter 802.11 = " 
         << std::hex << (int)m_parameterCode << codestr;
    }
    void 
    LinkParameter80211::TlvSerialize (Buffer &buffer) const
    {
      Tlv::SerializeU8 (buffer, m_parameterCode, TLV_LINK_PARAMETER_802_11);
    }
    uint32_t
    LinkParameter80211::TlvDeserialize (Buffer &buffer) 
    {
      return Tlv::DeserializeU8 (buffer, m_parameterCode, TLV_LINK_PARAMETER_802_11);
    }    
  } // namespace mih
} // namespace ns3
