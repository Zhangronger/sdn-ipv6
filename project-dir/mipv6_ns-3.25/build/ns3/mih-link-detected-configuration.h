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

#ifndef   	MIH_LINK_DETECTED_CONFIGURATION_H
#define   	MIH_LINK_DETECTED_CONFIGURATION_H

#include <string>
#include <vector>
#include <stdint.h>
#include "ns3/ptr.h"
#include "ns3/ref-count-base.h"
#include "mih-network-identifier.h"
#include "mih-signal-strength.h"
#include "mih-data-rate.h"

namespace ns3 {
  namespace mih {
    class LinkDetectedConfiguration : public RefCountBase {
    public:
      LinkDetectedConfiguration (std::string networkIdentifier,
				 uint64_t signalStrength,
				 uint32_t dataRate);
      LinkDetectedConfiguration (LinkDetectedConfiguration const &o);
      NetworkIdentifier GetNetworkIdentifier (void);
      SignalStrength GetSignalStrength (void);
      DataRate GetDataRate (void);
    protected:
      NetworkIdentifier m_networkIdentifier;
      SignalStrength m_signalStrength;
      DataRate m_dataRate;
    };
    typedef std::vector<Ptr<LinkDetectedConfiguration> > LinkDetectedConfigurationList;
    typedef LinkDetectedConfigurationList::iterator LinkDetectedConfigurationListI;
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_LINK_DETECTED_CONFIGURATION_H */
