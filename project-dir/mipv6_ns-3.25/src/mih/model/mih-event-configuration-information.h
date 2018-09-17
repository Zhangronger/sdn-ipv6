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

#ifndef   	MIH_EVENT_CONFIGURATION_INFORMATION_H
#define   	MIH_EVENT_CONFIGURATION_INFORMATION_H

#include <stdint.h>
#include "ns3/ptr.h"
#include "mih-link-configuration-parameter.h"
#include "mih-link-detected-configuration.h"

namespace ns3 {
  namespace mih {
    class EventConfigurationInformation {
    public:
      EventConfigurationInformation (void);
      EventConfigurationInformation (EventConfigurationInformation const &o);
      LinkDetectedConfigurationListI GetLinkDetectedConfigurationListBegin (void);
      LinkDetectedConfigurationListI GetLinkDetectedConfigurationListEnd (void);
      void AddLinkDetectedConfigurationItem (Ptr<LinkDetectedConfiguration> detectedConfigurationItem);
      uint32_t GetLinkDetectedConfigurationN (void);
      LinkConfigurationParameterListI GetLinkConfigurationParameterListBegin (void);
      LinkConfigurationParameterListI GetLinkConfigurationParameterListEnd (void);
      void AddLinkConfigurationParameterItem (Ptr<LinkConfigurationParameter> configurationParameterItem);
      uint32_t GetLinkConfigurationParameterN (void);
    protected:
      LinkDetectedConfigurationList m_detectedConfigurations;
      LinkConfigurationParameterList m_configurationParameters;
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_EVENT_CONFIGURATION_INFORMATION_H */
