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
#include "mih-event-configuration-information.h"

NS_LOG_COMPONENT_DEFINE ("ns3::mih::EventConfigurationInformation");

namespace ns3 {
  namespace mih {
    EventConfigurationInformation::EventConfigurationInformation (void)
    {}
    EventConfigurationInformation::EventConfigurationInformation (EventConfigurationInformation const &o) :
      m_detectedConfigurations (o.m_detectedConfigurations),
      m_configurationParameters (o.m_configurationParameters)
    {
      NS_LOG_WARN ("Check this copy hack: m_detectedConfigurations (o.m_detectedConfigurations)!");
      NS_LOG_WARN ("Check this copy hack: m_detectedConfigurations (o.m_detectedConfigurations)");
    }
    LinkDetectedConfigurationListI 
    EventConfigurationInformation::GetLinkDetectedConfigurationListBegin (void)
    {
      return m_detectedConfigurations.begin ();
    }
    LinkDetectedConfigurationListI EventConfigurationInformation::GetLinkDetectedConfigurationListEnd (void)
    {
      return m_detectedConfigurations.end ();
    }
    void
    EventConfigurationInformation::AddLinkDetectedConfigurationItem (Ptr<LinkDetectedConfiguration> detectedConfigurationItem)
    {
      NS_ASSERT_MSG (detectedConfigurationItem != 0, "Illegal NULL pointer addressing!");
      m_detectedConfigurations.push_back (detectedConfigurationItem);
    }
    uint32_t 
    EventConfigurationInformation::GetLinkDetectedConfigurationN (void)
    {
      return m_detectedConfigurations.size ();
    }
    LinkConfigurationParameterListI 
    EventConfigurationInformation::GetLinkConfigurationParameterListBegin (void)
    {
      return m_configurationParameters.begin ();
    }
    LinkConfigurationParameterListI 
    EventConfigurationInformation::GetLinkConfigurationParameterListEnd (void)
    {
      return m_configurationParameters.end ();
    }
    void 
    EventConfigurationInformation::AddLinkConfigurationParameterItem (Ptr<LinkConfigurationParameter> configurationParameterItem)
    {
      NS_ASSERT_MSG (configurationParameterItem != 0, "Illegal NULL pointer addressing!");
      m_configurationParameters.push_back (configurationParameterItem);
    }
    uint32_t
    EventConfigurationInformation::GetLinkConfigurationParameterN (void)
    {
      return m_configurationParameters.size ();
    }
    
  } // namespace mih
} // namespace ns3
