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

#ifndef   	MIH_LINK_CONFIGURE_THRESHOLDS_H
#define   	MIH_LINK_CONFIGURE_THRESHOLDS_H

#include <stdint.h>
#include "mih-status.h"
#include "mih-link-configuration-status.h"

namespace ns3 {
  namespace mih {
    class LinkConfigureThresholdsConfirm {
    public:
      LinkConfigureThresholdsConfirm (enum Status::Type status = Status::INVALID);
      LinkConfigureThresholdsConfirm (LinkConfigureThresholdsConfirm const &o);
      LinkConfigureThresholdsConfirm operator = (LinkConfigureThresholdsConfirm const &o);
      Status GetStatus (void);
      LinkConfigurationStatusListI GetLinkConfigurationStatusListBegin (void);
      LinkConfigurationStatusListI GetLinkConfigurationStatusListEnd (void);
      void AddLinkConfigurationStatusItem (Ptr<LinkConfigurationStatus> linkConfigurationStatusItem);
      uint32_t GetLinkConfigurationStatusN (void);
      LinkConfigurationStatusList GetLinkConfigurationStatusList (void);
    protected:
      Status m_status;
      LinkConfigurationStatusList m_linkConfigurationStatusList;
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_LINK_CONFIGURE_THRESHOLDS_H */
