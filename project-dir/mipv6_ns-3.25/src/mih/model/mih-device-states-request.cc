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

#include "mih-device-states-request.h"

namespace ns3 {
  namespace mih {
    DeviceStatesRequest::DeviceStatesRequest (uint16_t deviceStatesRequest) :
      m_deviceStatesRequest (deviceStatesRequest)
    {}
    DeviceStatesRequest::DeviceStatesRequest (DeviceStatesRequest const &o) :
      m_deviceStatesRequest (o.m_deviceStatesRequest)
    {
    }
    TLV_TYPE_HELPER_IMPLEM (DeviceStatesRequest, TLV_DEVICE_STATES_REQUEST)
    uint16_t 
    DeviceStatesRequest::GetRequestedDeviceStates (void)
    {
      return m_deviceStatesRequest;
    }
    DeviceStatesRequest 
    DeviceStatesRequest::operator = (DeviceStatesRequest const &o)
    {
      m_deviceStatesRequest = o.m_deviceStatesRequest;
      return *this;
    }
    uint32_t
    DeviceStatesRequest::GetTlvSerializedSize (void) const
    {
      return Tlv::GetSerializedSizeU16 ();
    }
    void 
    DeviceStatesRequest::Print (std::ostream &os) const
    {
      os << "Device State Request = " << std::hex << (int)m_deviceStatesRequest << std::endl;
    }
    void
    DeviceStatesRequest::TlvSerialize (Buffer &buffer) const
    {
      Tlv::SerializeU16 (buffer, m_deviceStatesRequest, TLV_DEVICE_STATES_REQUEST);
    }
    uint32_t 
    DeviceStatesRequest::TlvDeserialize (Buffer &buffer) 
    {
      return Tlv::DeserializeU16 (buffer, m_deviceStatesRequest, TLV_DEVICE_STATES_REQUEST);
    }
  } // namespace mih
} // namespace ns3
