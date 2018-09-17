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

#ifndef   	MIH_LINK_PARAMETER_H
#define   	MIH_LINK_PARAMETER_H

#include <vector>
#include "ns3/ptr.h"
#include "ns3/ref-count-base.h"
#include "mih-link-parameter-type.h"
#include "mih-parameter-value.h"
#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class LinkParameter : public RefCountBase, public Tlv {
    public:
      LinkParameter (Ptr<LinkParameterType> parameterType = 0, 
		     Ptr<ParameterValue> parameterValue = 0);
      LinkParameter (LinkParameter const &o);
      Ptr<LinkParameterType> GetLinkParameterType (void);
      Ptr<ParameterValue> GetParameterValue (void);
      virtual ~LinkParameter (void);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void Print (std::ostream &os) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);    
      TLV_TYPE_HELPER_HEADER (LinkParameter);
      static Ptr<LinkParameter> CreateFromTlvType (uint8_t tlvTypeValue);
    protected:
      Ptr<LinkParameterType> m_linkParameterType;
      Ptr<ParameterValue> m_parameterValue;
    };
    typedef std::vector<Ptr<LinkParameter> > LinkParameterList;
    typedef LinkParameterList::iterator LinkParameterListI;
    uint32_t GetTlvSerializedSize (const LinkParameterList &linkParameterList);
    void TlvSerialize (Buffer &buffer, const LinkParameterList &linkParameterList);
    uint32_t TlvDeserialize (Buffer &buffer, LinkParameterList &linkParameterList);
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_LINK_PARAMETER_H */
