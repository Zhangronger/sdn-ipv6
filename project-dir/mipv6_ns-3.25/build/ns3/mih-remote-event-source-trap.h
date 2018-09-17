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

#ifndef   	MIH_REMOTE_EVENT_SOURCE_TRAP_H
#define   	MIH_REMOTE_EVENT_SOURCE_TRAP_H

#include "ns3/ptr.h"
#include "ns3/ref-count-base.h"
#include "mih-callbacks.h"

namespace ns3 {
  namespace mih {
    
    class Session;
    
    class RemoteEventSourceTrap : public RefCountBase {
    public:
      RemoteEventSourceTrap (void);
      virtual ~RemoteEventSourceTrap (void);
      void SetSession (Ptr<Session> session);
      // Callback accessors;
      void LinkDetected (MihfId mihfId, 
			 LinkDetectedInformationList linkDetectedInformationList);
      void LinkUp (MihfId mihfId,
                   LinkIdentifier linkIdentifier, 
                   Address oldAR,
                   Address newAR, 
                   bool ipRenewalFlag, 
                   MobilityManagementSupport mbbSupport);
      void LinkDown (MihfId mihfId, 
		     LinkIdentifier linkIdentifier,
		     Address oldAR,
		     LinkDownReason reasonCode);
      void LinkParametersReport (MihfId mihfId, 
				 LinkIdentifier linkIdentifier, 
				 LinkParameterReportList parameters);
      void LinkGoingDown (MihfId mihfId, 
			  LinkIdentifier linkIdentifier,
			  uint64_t timeInterval,
			  LinkGoingDownReason reasonCode);
      void LinkHandoverImminent (MihfId mihfId,
				 LinkIdentifier oldLinkId,
				 LinkIdentifier newLinkId, 
				 Address oldAR, 
				 Address newAR);
      void LinkHandoverComplete (MihfId mihfId, 
				 LinkIdentifier oldLinkId, 
				 LinkIdentifier newLinkId, 
				 Address oldAR, 
				 Address newAR, 
				 Status handoverStatus);
    protected:
      Ptr<Session> m_session;
    };
  }
}

#endif 	    /* !MIH_REMOTE_EVENT_SOURCE_TRAP_H */
