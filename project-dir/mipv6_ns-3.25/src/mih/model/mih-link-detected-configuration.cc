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

#include "mih-link-detected-configuration.h"

namespace ns3 {
  namespace mih {
    LinkDetectedConfiguration::LinkDetectedConfiguration (std::string networkIdentifier, uint64_t signalStrength, uint32_t dataRate) :
      m_networkIdentifier (networkIdentifier),
      m_signalStrength (signalStrength),
      m_dataRate (dataRate)
    {}
    LinkDetectedConfiguration::LinkDetectedConfiguration (LinkDetectedConfiguration const &o) : 
      m_networkIdentifier (o.m_networkIdentifier),
      m_signalStrength (o.m_signalStrength),
      m_dataRate (o.m_dataRate)
    {}
    NetworkIdentifier 
    LinkDetectedConfiguration::GetNetworkIdentifier (void)
    {
      return m_networkIdentifier;
    }
    SignalStrength 
    LinkDetectedConfiguration::GetSignalStrength (void)
    {
      return m_signalStrength;
    }
    DataRate 
    LinkDetectedConfiguration::GetDataRate (void)
    {
      return m_dataRate;
    }
  } // namespace mih
} // namespace ns3
