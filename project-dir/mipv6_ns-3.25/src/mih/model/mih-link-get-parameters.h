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

#ifndef   	MIH_LINK_GET_PARAMETERS_H
#define   	MIH_LINK_GET_PARAMETERS_H

#include <stdint.h>
#include "mih-status.h"
#include "mih-link-parameter.h"
#include "mih-link-states-response.h"
#include "mih-link-descriptors-response.h"

namespace ns3 {
  namespace mih {
    class LinkGetParametersConfirm {
    public:
      LinkGetParametersConfirm (enum Status::Type status = Status::UNSPECIFIED_FAILURE);
      LinkGetParametersConfirm (LinkGetParametersConfirm const &o);
      Status GetStatus (void);
      void SetStatus (Status status);
      LinkParameterListI GetLinkParameterListBegin (void);
      LinkParameterListI GetLinkParameterListEnd (void);
      void AddLinkParameterItem (Ptr<LinkParameter> linkParameterItem);
      uint32_t GetLinkParameterN (void);
      LinkParameterList GetLinkParameterList (void);
      LinkStatesResponseListI GetLinkStatesResponseListBegin (void);
      LinkStatesResponseListI GetLinkStatesResponseListEnd (void);
      uint32_t GetLinkStatesResponseN (void);
      LinkStatesResponseList GetLinkStatesResponseList (void);
      void AddLinkStatesResponseItem (Ptr<LinkStatesResponse> linkStatesResponseItem);
      LinkDescriptorsResponseListI GetLinkDescriptorsResponseListBegin (void);
      LinkDescriptorsResponseListI GetLinkDescriptorsResponseListEnd (void);
      uint32_t GetLinkDescriptorsResponseN (void);
      void AddLinkDescriptorsResponseItem (Ptr<LinkDescriptorsResponse> linkDescriptorsResponseItem);
      LinkDescriptorsResponseList GetLinkDescriptorsResponseList (void);
      LinkGetParametersConfirm operator = (const LinkGetParametersConfirm &o);
    protected:
      Status m_status;
      LinkParameterList m_linkParameterStatusList;
      LinkStatesResponseList m_linkStatesResponseList;
      LinkDescriptorsResponseList m_linkDescriptorsList;
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_LINK_GET_PARAMETERS_H */
