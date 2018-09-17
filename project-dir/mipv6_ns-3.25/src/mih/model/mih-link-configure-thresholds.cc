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

#include "mih-link-configure-thresholds.h"

namespace ns3 {
  namespace mih {
    LinkConfigureThresholdsConfirm::LinkConfigureThresholdsConfirm (enum Status::Type status) :
      m_status (status)
    {}
    LinkConfigureThresholdsConfirm::LinkConfigureThresholdsConfirm (LinkConfigureThresholdsConfirm const &o) :
      m_status (o.m_status),
      m_linkConfigurationStatusList (o.m_linkConfigurationStatusList)
    {}
    LinkConfigureThresholdsConfirm 
    LinkConfigureThresholdsConfirm::operator = (LinkConfigureThresholdsConfirm const &o)
    {
      if (this == &o)
        {
          return *this;
        }
      m_status = o.m_status;
      m_linkConfigurationStatusList = o.m_linkConfigurationStatusList;
      return *this;
    }
    Status 
    LinkConfigureThresholdsConfirm::GetStatus (void)
    {
      return m_status;
    }
    LinkConfigurationStatusListI 
    LinkConfigureThresholdsConfirm::GetLinkConfigurationStatusListBegin (void)
    {
      return m_linkConfigurationStatusList.begin ();
    }
    LinkConfigurationStatusListI 
    LinkConfigureThresholdsConfirm::GetLinkConfigurationStatusListEnd (void)
    {
      return m_linkConfigurationStatusList.end ();
    }
    void 
    LinkConfigureThresholdsConfirm::AddLinkConfigurationStatusItem (Ptr<LinkConfigurationStatus> linkConfigurationStatusItem)
    {
      NS_ASSERT (linkConfigurationStatusItem != 0);
      m_linkConfigurationStatusList.push_back (linkConfigurationStatusItem);
    }
    uint32_t 
    LinkConfigureThresholdsConfirm::GetLinkConfigurationStatusN (void)
    {
      return m_linkConfigurationStatusList.size ();
    }
    LinkConfigurationStatusList 
    LinkConfigureThresholdsConfirm::GetLinkConfigurationStatusList (void)
    {
      return m_linkConfigurationStatusList;
    }
  } // namespace mih
} // namespace ns3
