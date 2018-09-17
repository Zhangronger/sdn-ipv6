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

#ifndef   	SIMPLE_MIH_USER_H
#define   	SIMPLE_MIH_USER_H

#include "ns3/application.h"
#include "mih-callbacks.h"

namespace ns3 {
  namespace mih {
    class SimpleMihUser : public Application {
    public:
      static TypeId GetTypeId (void);
      SimpleMihUser (void);
      virtual ~SimpleMihUser (void);

      void Register (MihfId destMihf);
      void CapabilityDiscover (MihfId destMihf);
      void EventSubscribe (MihfId destMihf,
			   LinkIdentifier destLinkIdentifier);
      void LinkGetParameters (MihfId destMihf,
			      LinkIdentifier destLinkIdentifier);
      void LinkConfigureThresholds (MihfId destMihf,
				    LinkIdentifier destLinkIdentifier);
      void LinkActions (MihfId destMihf,
			LinkIdentifier destLinkIdentifier);

      // Event callbacks;
      void RecvLinkDetected (MihfId sourceIdentifier,
			     LinkDetectedInformationList detectedInfoList);
      void RecvLinkUp (MihfId sourceIdentifier,
		       LinkIdentifier linkIdentifier, 
		       Address oldAR,
		       Address newAR,
		       bool ipRenewalFlag, 
		       MobilityManagementSupport mobilityProtocol);
      void RecvLinkDown (MihfId sourceIdentifier,
			 LinkIdentifier linkIdentifier,
			 Address oldAR,
			 LinkDownReason reason);
      void RecvLinkParametersReport (MihfId sourceIdentifier, 
				     LinkIdentifier linkIdentifier,
				     LinkParameterReportList params);
      void RecvLinkGoingDown (MihfId sourceIdentifier,
			      LinkIdentifier linkIdentifier,
			      uint64_t timeInterval,
			      LinkGoingDownReason reason);
      void RecvLinkHandoverImminent (MihfId sourceIdentifier, 
				     LinkIdentifier oldLinkIdentifier,
				     LinkIdentifier newLinkIdentifier, 
				     Address oldAR,
				     Address newAR);
      void RecvLinkHandoverComplete (MihfId sourceIdentifier,
				     LinkIdentifier oldLinkIdentifier,
				     LinkIdentifier newLinkIdentifier,
				     Address oldAR, 
				     Address newAR,
				     Status status);
      // Command Confirm Callbacks;
      void ConfirmCapabilityDiscover (MihfId sourceIdentifier, 
				      Status status,
				      NetworkTypeAddressList networkTypeAddresses, 
				      EventList events, 
				      MihCommandList commands, 
				      InformationServiceQueryTypeList queries, 
				      TransportSupportList transports,
				      MakeBeforeBreakSupportList mbbs);
      void ConfirmEventSubscribe (MihfId sourceIdentifier, 
				  Status status, 
				  LinkIdentifier linkIdentifier,
				  EventList events);
      void ConfirmLinkGetParameters (MihfId sourceIdentifier,
				     Status status, 
				     DeviceStatesResponseList deviceStates, 
				     LinkStatusResponseList);
      void ConfirmLinkConfigureThresholds (MihfId sourceIdentifier, 
					   Status status, 
					   LinkIdentifier linkIdentifier, 
					   LinkConfigurationStatusList configs);
      void ConfirmLinkActions (MihfId sourceIdentifier, 
			       Status status,
			       LinkActionResponseList actionResponses);
      // Management callbacks;
      void RegisterIndication (MihfId mihfid,
                               LinkIdentifierList linkIdentifiers,
                               RegistrationCode code,
                               MihRegisterResponseCallback responseCallback);
      void RegisterConfirm (MihfId src,
                            Status status,
                            uint32_t delay);
      void Start (void);
    protected:
      virtual void DoDispose (void);
    private:
      virtual void StartApplication (void);
      virtual void StopApplication (void);
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !SIMPLE_MIH_USER_H */
