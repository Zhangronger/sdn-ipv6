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

#ifndef   	MIH_LINK_STATUS_REQUEST_H
#define   	MIH_LINK_STATUS_REQUEST_H

#include <ostream>
#include <stdint.h>
#include "mih-link-states-request.h"
#include "mih-link-parameter-type.h"
#include "mih-link-descriptors-request.h"
#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class LinkStatusRequest : public Tlv {
    public:
      LinkStatusRequest (void);
      LinkStatusRequest (LinkStatesRequest linkStatesRequest,
			 LinkDescriptorsRequest linkDescriptorsRequest);
      LinkStatusRequest (LinkStatusRequest const &o);
      LinkStatesRequest GetLinkStatesRequest (void);
      LinkDescriptorsRequest GetLinkDescriptorsRequest (void);
      LinkParameterTypeListI LinkParameterTypeListBegin (void);
      LinkParameterTypeListI LinkParameterTypeListEnd (void);
      void AddLinkParameterTypeItem (Ptr<LinkParameterType> linkparameterType);
      uint32_t GetLinkParameterTypeN (void);
      LinkParameterTypeList GetLinkParameterTypeList (void);
      LinkStatusRequest operator = (LinkStatusRequest const &o);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void Print (std::ostream &os) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (LinkStatusRequest);
    protected:
      LinkStatesRequest m_linkStatesRequest;
      LinkDescriptorsRequest m_linkDescriptorsRequest;
      LinkParameterTypeList m_linkParameterList;
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_LINK_STATUS_REQUEST_H */
