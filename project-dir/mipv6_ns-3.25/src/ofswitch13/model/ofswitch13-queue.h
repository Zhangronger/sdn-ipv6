/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2015 University of Campinas (Unicamp)
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
 * Author: Luciano Chaves <luciano@lrc.ic.unicamp.br>
 */
#ifndef OFSWITCH13_QUEUE_H
#define OFSWITCH13_QUEUE_H

#include <queue>
#include "ns3/packet.h"
#include "ns3/queue.h"
#include "ofswitch13-interface.h"
#include "queue-tag.h"

namespace ns3 {

/**
 * \ingroup ofswitch13
 *
 * \brief The OpenFlow 1.3 queue interface for simple QoS management. An
 * OpenFlow switch provides limited Quality-of-Service support (QoS) through a
 * simple queuing mechanism. One (or more) queues can attach to a port and be
 * used to map flow entries on it. Flow entries mapped to a specific queue will
 * be treated according to that queue's configuration. Queue configuration
 * takes place outside the OpenFlow protocol. This class implements the common
 * queue interface, extending the ns3::Queue class to allow compatibility
 * with the CsmaNetDevice used in OFSwitch13Port. Internally, it can hold a
 * collection of other queues, indentified by an unique id. The ns3::QueueTag
 * is used to identify which internal queue will hold the packet, and the
 * internal schedulling algorithms decides from which queue get the packets
 * to send over the wire.
 */
class OFSwitch13Queue : public Queue
{
public:
  /**
   * The output scheduling algorithm, used to select the internal queue for
   * Peek and Dequeue operations.
   */
  enum Scheduling
  {
    PRIO = 0    //!< Priority schedulling
  };

  /**
   * \brief Get the type ID.
   * \return the object TypeId.
   */
  static TypeId GetTypeId (void);

  OFSwitch13Queue ();           //!< Default constructor
  virtual ~OFSwitch13Queue ();  //!< Dummy destructor, see DoDispose.

  /**
   * Complete constructor, including the pointer to the ofsoftswitch13 internal
   * port structure.
   * \param port The ofsoftswitch13 port structure
   */
  OFSwitch13Queue (sw_port* port);

  /**
   * Get the maximun number of queues allowed.
   * \return The number of allowed queues.
   */
  static uint16_t GetMaxQueues (void);

  /**
   * Get the current number of queues.
   * \return The current number of queues.
   */
  uint16_t GetNQueues (void) const;

protected:
  /** Destructor implementation */
  virtual void DoDispose ();

  // Inherited from ObjectBase
  virtual void NotifyConstructionCompleted (void);

private:
  // Inherited from Queue
#ifdef NS3_OFSWITCH13_PRIOR_325
  virtual bool DoEnqueue (Ptr<Packet> p);
  virtual Ptr<Packet> DoDequeue (void);
  virtual Ptr<const Packet> DoPeek (void) const;
#else
  virtual bool DoEnqueue (Ptr<QueueItem> item);
  virtual Ptr<QueueItem> DoDequeue (void);
  virtual Ptr<const QueueItem> DoPeek (void) const;
#endif

  /**
   * Add a new internal queue to this OpenFlow queue.
   * \param queue The queue pointer.
   * \return The queue id for the new queue.
   */
  uint32_t AddQueue (Ptr<Queue> queue);

  /**
   * Get a pointer to internal queue with specific id.
   * \param queueId The queue id.
   * \return The queue pointer.
   * \internal
   * This function is marked as const to allow its usage inside DoPeek ()
   * member function.
   */
  Ptr<Queue> GetQueue (uint32_t queueId) const;

  /**
   * Return the queue id that will be used by DoPeek and DoDequeue functions
   * based on selected scheduling output algorithm.
   * \internal
   * This function has to keep consistence in its queue decision despite
   * arbitrary calls from peek and dequeue functions. When a peek operation is
   * performed, a output queue must be selected and has to remain the same
   * until the packet is effectively dequeued from it.
   * \param peekLock Get the output queue and lock it.
   * \return The queue id.
   */
  uint32_t GetOutputQueue (bool peekLock = false) const;

  /** Structure to save the list of internal queues in this port queue. */
  typedef std::vector<Ptr<Queue> > QueueList_t;

  sw_port*              m_swPort;     //!< ofsoftswitch13 struct sw_port
  QueueList_t           m_queues;     //!< Sorted list of available queues
  static const uint16_t m_maxQueues;  //!< Maximum number of queues
  Scheduling            m_scheduling; //!< Output scheduling strategy
};

} // namespace ns3
#endif /* OFSWITCH13_QUEUE_H */
