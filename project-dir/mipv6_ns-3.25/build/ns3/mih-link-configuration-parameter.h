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

#ifndef   	MIH_LINK_CONFIGURATION_PARAMETER_H
#define   	MIH_LINK_CONFIGURATION_PARAMETER_H

#include <stdint.h>
#include <vector>
#include "ns3/ref-count-base.h"
#include "mih-link-parameter-type.h"
#include "mih-threshold.h"
#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class LinkConfigurationParameter : public RefCountBase, public Tlv {
    public:
      enum ThresholdAction {
	NORMAL_THRESHOLD = 0,
	ONE_SHOT_THRESHOLD = 1,
	CANCEL_SHOT_THRESHOLD= 2,
      };
      LinkConfigurationParameter (void);
      LinkConfigurationParameter (Ptr<LinkParameterType> linkParameterType,
				  uint64_t timerInterval,
				  enum ThresholdAction thresholdAction,
				  ThresholdList thresholdList);
      LinkConfigurationParameter (LinkConfigurationParameter const &o);
      static Ptr<LinkConfigurationParameter> CreateFromTlvType (uint8_t val);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (LinkConfigurationParameter);
      Ptr<LinkParameterType> GetLinkParameterType (void);
      uint64_t GetTimerInterval (void);
      ThresholdListI GetThresholdsListBegin (void);
      ThresholdListI GetThresholdsListEnd (void);
      uint32_t GetThresholdsN (void);
      void AddThresholdItem (Ptr<Threshold> thresholdItem);
      enum ThresholdAction GetThresholdAction (void);
    protected:
      Ptr<LinkParameterType> m_linkParameterType;
      uint64_t m_timerInterval;
      enum ThresholdAction m_thresholdAction;
      ThresholdList m_thresholdList;
    };
    typedef std::vector<Ptr<LinkConfigurationParameter> > LinkConfigurationParameterList;
    typedef LinkConfigurationParameterList::iterator LinkConfigurationParameterListI;
    uint32_t GetTlvSerializedSize (const LinkConfigurationParameterList &linkConfigurationParameterList);
    void TlvSerialize (Buffer &buffer, const LinkConfigurationParameterList &linkConfigurationParameterList);
    uint32_t TlvDeserialize (Buffer &buffer, LinkConfigurationParameterList &linkConfigurationParameterList);
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_LINK_CONFIGURATION_PARAMETER_H */
