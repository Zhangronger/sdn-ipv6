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

#include "ns3/assert.h"
#include "ns3/log.h"
#include "mih-link-get-parameters.h"

NS_LOG_COMPONENT_DEFINE ("ns3::mih::LinkGetParametersConfirm");

namespace ns3 {
  namespace mih {
    LinkGetParametersConfirm::LinkGetParametersConfirm (enum Status::Type status) :
      m_status (status)
    {}
    LinkGetParametersConfirm::LinkGetParametersConfirm (LinkGetParametersConfirm const &o) :
      m_status (o.m_status),
      m_linkParameterStatusList (o.m_linkParameterStatusList),
      m_linkStatesResponseList (o.m_linkStatesResponseList),
      m_linkDescriptorsList (o.m_linkDescriptorsList)
    {
      NS_LOG_WARN ("Dangerous list copy hack: m_linkParameterStatusList (o.m_linkParameterStatusList)!");
      NS_LOG_WARN ("Dangerous list copy hack: m_linkStatesResponseList (o.m_linkStatesResponseList)!");
      NS_LOG_WARN ("Dangerous list copy hack: m_linkDescriptorsList (o.m_linkDescriptorsList)!");
    }
    void
    LinkGetParametersConfirm::SetStatus (Status status)
    {
      m_status = status;
    }
    Status
    LinkGetParametersConfirm::GetStatus (void)
    {
      return m_status;
    }
    LinkParameterListI
    LinkGetParametersConfirm::GetLinkParameterListBegin (void)
    {
      return m_linkParameterStatusList.begin ();
    }
    LinkParameterListI
    LinkGetParametersConfirm::GetLinkParameterListEnd (void)
    {
      return m_linkParameterStatusList.end ();
    }
    void
    LinkGetParametersConfirm::AddLinkParameterItem (Ptr<LinkParameter> linkParameterItem)
    {
      NS_ASSERT_MSG (linkParameterItem != 0, "Illegal NULL pointer addressing!");
      m_linkParameterStatusList.push_back (linkParameterItem);
    }
    uint32_t 
    LinkGetParametersConfirm::GetLinkParameterN (void)
    {
      return m_linkParameterStatusList.size ();
    }
    LinkParameterList
    LinkGetParametersConfirm::GetLinkParameterList (void)
    {
      return m_linkParameterStatusList;
    }
    LinkStatesResponseListI 
    LinkGetParametersConfirm::GetLinkStatesResponseListBegin (void)
    {
      return m_linkStatesResponseList.begin ();
    }
    LinkStatesResponseListI 
    LinkGetParametersConfirm::GetLinkStatesResponseListEnd (void)
    {
      return m_linkStatesResponseList.end ();
    }
    uint32_t 
    LinkGetParametersConfirm::GetLinkStatesResponseN (void)
    {
      return m_linkStatesResponseList.size ();
    }
    void 
    LinkGetParametersConfirm::AddLinkStatesResponseItem (Ptr<LinkStatesResponse> linkStatesResponseItem)
    {
      NS_ASSERT_MSG (linkStatesResponseItem != 0, "Illegal NULL pointer addressing!");
      m_linkStatesResponseList.push_back (linkStatesResponseItem);
    }
    LinkStatesResponseList
    LinkGetParametersConfirm::GetLinkStatesResponseList (void)
    {
      return m_linkStatesResponseList;
    }
    LinkDescriptorsResponseListI 
    LinkGetParametersConfirm::GetLinkDescriptorsResponseListBegin (void)
    {
      return m_linkDescriptorsList.begin ();
    }
    LinkDescriptorsResponseListI 
    LinkGetParametersConfirm::GetLinkDescriptorsResponseListEnd (void)
    {
      return m_linkDescriptorsList.end ();
    }
    uint32_t 
    LinkGetParametersConfirm::GetLinkDescriptorsResponseN (void)
    {
      return m_linkDescriptorsList.size ();
    }
    void
    LinkGetParametersConfirm::AddLinkDescriptorsResponseItem (Ptr<LinkDescriptorsResponse> linkDescriptorsResponseItem)
    {
      NS_ASSERT_MSG (linkDescriptorsResponseItem != 0, "Illegal NULL pointer addressing");
      m_linkDescriptorsList.push_back (linkDescriptorsResponseItem);
    }
    LinkDescriptorsResponseList
    LinkGetParametersConfirm::GetLinkDescriptorsResponseList (void)
    {
      return m_linkDescriptorsList;
    }
    LinkGetParametersConfirm
    LinkGetParametersConfirm::operator = (const LinkGetParametersConfirm &o)
    {
      m_status = o.m_status;
      m_linkParameterStatusList = o.m_linkParameterStatusList;
      m_linkStatesResponseList = o.m_linkStatesResponseList;
      m_linkDescriptorsList = o.m_linkDescriptorsList;
      return *this;
    }
  } // namespace mih
} // namespace ns3
