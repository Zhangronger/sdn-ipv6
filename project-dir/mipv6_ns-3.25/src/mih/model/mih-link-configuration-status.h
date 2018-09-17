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

#ifndef   	MIH_LINK_CONFIGURATION_STATUS_H
#define   	MIH_LINK_CONFIGURATION_STATUS_H

#include <vector>
#include "ns3/ref-count-base.h"
#include "mih-link-parameter-type.h"
#include "mih-threshold.h"
#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class LinkConfigurationStatus : public RefCountBase, public Tlv {
    public:
      LinkConfigurationStatus (Ptr<LinkParameterType> linkParameterType = 0,
			       Threshold threshold = Threshold (),
			       bool configurationStatus = false);
      LinkConfigurationStatus (LinkConfigurationStatus const &o);
      virtual ~LinkConfigurationStatus (void);
      Ptr<LinkParameterType> GetLinkParameterType (void);
      void SetLinkParameterType (Ptr<LinkParameterType> linkParameterType);
      Threshold GetThreshold (void);
      bool IsSuccess (void);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (LinkConfigurationStatus);
      static Ptr<LinkConfigurationStatus> CreateFromTlvType (uint8_t val);
    protected:
      Ptr<LinkParameterType> m_linkParameterType;
      Threshold m_threshold;
      bool m_configurationStatus;
    };
    typedef std::vector<Ptr<LinkConfigurationStatus> > LinkConfigurationStatusList;
    typedef LinkConfigurationStatusList::iterator LinkConfigurationStatusListI;
    uint32_t GetTlvSerializedSize (const LinkConfigurationStatusList &linkConfigurationStatusList);
    void TlvSerialize (Buffer &buffer, const LinkConfigurationStatusList &linkConfigurationStatusList);
    uint32_t TlvDeserialize (Buffer &buffer, LinkConfigurationStatusList &linkConfigurationStatusList);
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_LINK_CONFIGURATION_STATUS_H */
