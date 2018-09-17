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

#ifndef   	MIH_REMOTE_EVENT_DESTINATION_TRAP_H
#define   	MIH_REMOTE_EVENT_DESTINATION_TRAP_H

#include "ns3/ref-count-base.h"
#include "mih-callbacks.h"

namespace ns3 {
  namespace mih {
    class RemoteEventDestinationTrap : public RefCountBase {
    public:
      RemoteEventDestinationTrap (void);
      // AddRemove callback methods;
      void AddLinkDetectedCallback (MihLinkDetectedIndicationCallback linkDetectedCb);
      void RemoveLinkDetectedCallback (MihLinkDetectedIndicationCallback linkDetectedCb);
      void AddLinkUpCallback (MihLinkUpIndicationCallback linkUpCb);
      void RemoveLinkUpCallback (MihLinkUpIndicationCallback linkUpCb);
      void AddLinkDownCallback (MihLinkDownIndicationCallback linkDownCb);
      void RemoveLinkDownCallback (MihLinkDownIndicationCallback linkDownCb);
      void AddLinkParamatersReportCallback (MihLinkParametersReportIndicationCallback parametersReportCb);
      void RemoveLinkParametersReportCallback (MihLinkParametersReportIndicationCallback parametersReportCb);
      void AddLinkGoingDownCallback (MihLinkGoingDownIndicationCallback linkGoingDownCb);
      void RemoveLinkGoingDownCallback (MihLinkGoingDownIndicationCallback linkGoingDownCb);
      void AddLinkHandoverImminentCallback (MihLinkHandoverImminentIndicationCallback linkHOImminentCb);
      void RemoveLinkHandoverImminentCallback (MihLinkHandoverImminentIndicationCallback linkHOImminentCb);
      void AddLinkHandoverCompleteCallback (MihLinkHandoverCompleteIndicationCallback linkHOCompleteCb);
      void RemoveLinkHandoverCompleteCallback (MihLinkHandoverCompleteIndicationCallback linkHOCompleteCb);
      void AddLinkPduTxStatusCallback (MihLinkPduTransmitStatusIndicationCallback linkPduTxStatusCb);
      void RemoveLinkPduTxStatusCallback (MihLinkPduTransmitStatusIndicationCallback linkPduTxStatusCb);
      // Callback accessors;
      void LinkDetected (MihfId mihfId, 
			 LinkDetectedInformationList linkDetectedInfoList);
      void LinkUp (MihfId mihfId, 
		   LinkIdentifier linkIdentifier, 
		   Address oldAR, 
		   Address newAR, 
		   bool ipRenewalFlag,
		   MobilityManagementSupport mobilitySupport);
      void LinkDown (MihfId mihfId, 
		     LinkIdentifier linkIdentifier, 
		     Address oldAR, 
		     LinkDownReason reasonCode);
      void LinkParametersReport (MihfId mihfId,
				 LinkIdentifier linkIdentifier,
				 LinkParameterReportList params);
      void LinkGoingDown (MihfId mihfId, 
			  LinkIdentifier linkIdentifier, 
			  uint64_t timeInterval, 
			  LinkGoingDownReason reasonCode);
      void LinkHandoverImminent (MihfId mihfId, 
				 LinkIdentifier oldLinkIdentifier,
				 LinkIdentifier newLinkIdentifier, 
				 Address oldAR, 
				 Address newAR);
      void LinkHandoverComplete (MihfId mihfId, 
				 LinkIdentifier oldLinkIdentifier, 
				 LinkIdentifier newLinkIdentifier,
				 Address oldAR, 
				 Address newAR, 
				 Status handoverStatus);
      void LinkPduTxStatus (MihfId mihfId, 
			    LinkIdentifier linkIdentifier, 
			    uint16_t packetIdentifier, 
			    bool transmissionStatus);
      
    protected:
      MihLinkDetectedIndicationTracedCallback m_linkDetectedIndication;
      MihLinkUpIndicationTracedCallback m_linkUpIndication;
      MihLinkDownIndicationTracedCallback m_linkDownIndication;
      MihLinkParametersReportIndicationTracedCallback m_linkParametersReportIndication;
      MihLinkGoingDownIndicationTracedCallback m_linkGoingDownIndication;
      MihLinkHandoverImminentIndicationTracedCallback m_linkHandoverImminentIndication;
      MihLinkHandoverCompleteIndicationTracedCallback m_linkHandoverCompleteIndication;
      MihLinkPduTransmitStatusIndicationTracedCallback m_linkPduTransmitStatusIndication;
    };
  }
}

#endif 	    /* !MIH_REMOTE_EVENT_DESTINATION_TRAP_H */
