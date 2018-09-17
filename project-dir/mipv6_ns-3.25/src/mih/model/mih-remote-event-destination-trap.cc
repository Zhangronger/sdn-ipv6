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

#include "mih-remote-event-destination-trap.h"

namespace ns3 {
  namespace mih {
    RemoteEventDestinationTrap::RemoteEventDestinationTrap (void)
    {
    }
    // AddRemove callback methods;
    void 
    RemoteEventDestinationTrap::AddLinkDetectedCallback (MihLinkDetectedIndicationCallback linkDetectedCb)
    {
      if (linkDetectedCb.IsNull ())
        return;
      m_linkDetectedIndication.ConnectWithoutContext (linkDetectedCb);
    }
    void
    RemoteEventDestinationTrap::RemoveLinkDetectedCallback (MihLinkDetectedIndicationCallback linkDetectedCb)
    {
      if (linkDetectedCb.IsNull ())
        return;
      m_linkDetectedIndication.DisconnectWithoutContext (linkDetectedCb);
    }
    void
    RemoteEventDestinationTrap::AddLinkUpCallback (MihLinkUpIndicationCallback linkUpCb)
    {
      if (linkUpCb.IsNull ())
        return;
      m_linkUpIndication.ConnectWithoutContext (linkUpCb);
    }
    void
    RemoteEventDestinationTrap::RemoveLinkUpCallback (MihLinkUpIndicationCallback linkUpCb)
    {
      if (linkUpCb.IsNull ())
        return;
      m_linkUpIndication.DisconnectWithoutContext (linkUpCb);
    }
    void
    RemoteEventDestinationTrap::AddLinkDownCallback (MihLinkDownIndicationCallback linkDownCb)
    {
      if (linkDownCb.IsNull ())
        return;
      m_linkDownIndication.ConnectWithoutContext (linkDownCb);
    }
    void
    RemoteEventDestinationTrap::RemoveLinkDownCallback (MihLinkDownIndicationCallback linkDownCb)
    {
      if (linkDownCb.IsNull ())
        return;
      m_linkDownIndication.DisconnectWithoutContext (linkDownCb);
    }
    void
    RemoteEventDestinationTrap::AddLinkParamatersReportCallback (MihLinkParametersReportIndicationCallback parametersReportCb)
    {
      if (parametersReportCb.IsNull ())
        return;
      m_linkParametersReportIndication.ConnectWithoutContext (parametersReportCb);
    }
    void
    RemoteEventDestinationTrap::RemoveLinkParametersReportCallback (MihLinkParametersReportIndicationCallback parametersReportCb)
    {
      if (parametersReportCb.IsNull ())
        return;
      m_linkParametersReportIndication.DisconnectWithoutContext (parametersReportCb);
    }
    void
    RemoteEventDestinationTrap::AddLinkGoingDownCallback (MihLinkGoingDownIndicationCallback linkGoingDownCb)
    {
      if (linkGoingDownCb.IsNull ())
        return;
      m_linkGoingDownIndication.ConnectWithoutContext (linkGoingDownCb);
    }
    void
    RemoteEventDestinationTrap::RemoveLinkGoingDownCallback (MihLinkGoingDownIndicationCallback linkGoingDownCb)
    {
      if (linkGoingDownCb.IsNull ())
        return;
      m_linkGoingDownIndication.DisconnectWithoutContext (linkGoingDownCb);
    }
    void
    RemoteEventDestinationTrap::AddLinkHandoverImminentCallback (MihLinkHandoverImminentIndicationCallback linkHOImminentCb)
    {
      if (linkHOImminentCb.IsNull ())
        return;
      m_linkHandoverImminentIndication.ConnectWithoutContext (linkHOImminentCb);
    }
    void 
    RemoteEventDestinationTrap::RemoveLinkHandoverImminentCallback (MihLinkHandoverImminentIndicationCallback linkHOImminentCb)
    {
      if (linkHOImminentCb.IsNull ())
        return;
      m_linkHandoverImminentIndication.DisconnectWithoutContext (linkHOImminentCb);
    }
    void
    RemoteEventDestinationTrap::AddLinkHandoverCompleteCallback (MihLinkHandoverCompleteIndicationCallback linkHOCompleteCb)
    {
      if (linkHOCompleteCb.IsNull ())
        return;
      m_linkHandoverCompleteIndication.ConnectWithoutContext (linkHOCompleteCb);
    }
    void
    RemoteEventDestinationTrap::RemoveLinkHandoverCompleteCallback (MihLinkHandoverCompleteIndicationCallback linkHOCompleteCb)
    {
      if (linkHOCompleteCb.IsNull ())
        return;
      m_linkHandoverCompleteIndication.DisconnectWithoutContext (linkHOCompleteCb);
    }
    void
    RemoteEventDestinationTrap::AddLinkPduTxStatusCallback (MihLinkPduTransmitStatusIndicationCallback linkPduTxStatusCb)
    {
      if (linkPduTxStatusCb.IsNull ())
        return;
      m_linkPduTransmitStatusIndication.ConnectWithoutContext (linkPduTxStatusCb);
    }
    void
    RemoteEventDestinationTrap::RemoveLinkPduTxStatusCallback (MihLinkPduTransmitStatusIndicationCallback linkPduTxStatusCb)
    {
      if (linkPduTxStatusCb.IsNull ())
        return;
      m_linkPduTransmitStatusIndication.DisconnectWithoutContext (linkPduTxStatusCb);
    }
    // Callback accessors;
    void
    RemoteEventDestinationTrap::LinkDetected (MihfId mihfId,
					      LinkDetectedInformationList linkDetectedInfoList)
    {
      m_linkDetectedIndication (mihfId, linkDetectedInfoList);
    }
    void
    RemoteEventDestinationTrap::LinkUp (MihfId mihfId, 
					LinkIdentifier linkIdentifier,
					Address oldAR,
					Address newAR, 
					bool ipRenewalFlag, 
					MobilityManagementSupport mobilitySupport)
    {
      m_linkUpIndication (mihfId,
			  linkIdentifier,
			  oldAR,
			  newAR,
			  ipRenewalFlag,
			  mobilitySupport);
    }
    void
    RemoteEventDestinationTrap::LinkDown (MihfId mihfId, 
					  LinkIdentifier linkIdentifier,
					  Address oldAR, 
					  LinkDownReason reasonCode)
    {
      m_linkDownIndication (mihfId,
			    linkIdentifier,
			    oldAR,
			    reasonCode);
    }
    void
    RemoteEventDestinationTrap::LinkParametersReport (MihfId mihfId,
						      LinkIdentifier linkIdentifier,
						      LinkParameterReportList params)
    {
      m_linkParametersReportIndication (mihfId,
					linkIdentifier,
					params);
    }
    void
    RemoteEventDestinationTrap::LinkGoingDown (MihfId mihfId,
					       LinkIdentifier linkIdentifier, 
					       uint64_t timeInterval,
					       LinkGoingDownReason reasonCode)
    {
      m_linkGoingDownIndication (mihfId,
				 linkIdentifier,
				 timeInterval,
				 reasonCode);
    }
    void
    RemoteEventDestinationTrap::LinkHandoverImminent (MihfId mihfId, 
						      LinkIdentifier oldLinkIdentifier, 
						      LinkIdentifier newLinkidentifier,
						      Address oldAR, 
						      Address newAR)
    {
      m_linkHandoverImminentIndication (mihfId,
					oldLinkIdentifier,
					newLinkidentifier,
					oldAR,
					newAR);
    }
    void
    RemoteEventDestinationTrap::LinkHandoverComplete (MihfId mihfId, 
						      LinkIdentifier oldLinkIdentifier, 
						      LinkIdentifier newLinkIdentifier,
						      Address oldAR, 
						      Address newAR,
						      Status handoverStatus)
    {
      m_linkHandoverCompleteIndication (mihfId,
					oldLinkIdentifier,
					newLinkIdentifier,
					oldAR,
					newAR,
					handoverStatus);
    }
    void
    RemoteEventDestinationTrap::LinkPduTxStatus (MihfId mihfId, 
						 LinkIdentifier linkIdentifier, 
						 uint16_t packetIdentifier,
						 bool transmissionStatus) 
    {
      m_linkPduTransmitStatusIndication (mihfId,
					 linkIdentifier,
					 packetIdentifier,
					 transmissionStatus);
    }
  }
}
