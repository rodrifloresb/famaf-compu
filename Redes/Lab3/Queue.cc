#ifndef QUEUE
#define QUEUE

#include <string.h>
#include <omnetpp.h>
#include "packet_m.h"

using namespace omnetpp;

class Queue: public cSimpleModule {
private:
    cQueue buffer;
    cQueue bufferFeed;
    cMessage *endServiceEvent;
    simtime_t serviceTime;

    // Vectores
    cOutVector bufferSizeVector;
    cOutVector packetDropVector;
public:
    Queue();
    virtual ~Queue();
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(Queue);

Queue::Queue() {
    endServiceEvent = NULL;
}

Queue::~Queue() {
    cancelAndDelete(endServiceEvent);
}

void Queue::initialize() {
    buffer.setName("buffer");
    bufferFeed.setName("bufferFeed"); // para los feedbacks
    endServiceEvent = new cMessage("endService");
    bufferSizeVector.setName("bufferSize");
    packetDropVector.setName("packetDrop");
}

void Queue::finish() {
}

void Queue::handleMessage(cMessage *msg) {

    // if msg is signaling an endServiceEvent
    if (msg == endServiceEvent) {
        // if packet in buffer, send next one
        if (!buffer.isEmpty()) {
            // dequeue packet
            cPacket *pkt = (cPacket*) buffer.pop();
            // send packet
            send(pkt, "out");
            // start new service

            // getDuration da el tiempo que omnet
            // Cree que tardara en enviar el paquete
            serviceTime = pkt->getDuration();

            scheduleAt(simTime() + serviceTime, endServiceEvent);
        } else if (!bufferFeed.isEmpty()) {

            FeedbackPkt * feedback = (FeedbackPkt *) bufferFeed.pop();

            send(feedback, "out");

            serviceTime = feedback->getDuration();

            scheduleAt(simTime() + serviceTime, endServiceEvent);
        }

    } else { // if msg is a data packet

        if (msg->getKind() == 0){ // QueueMid

            if (buffer.getLength() == par("bufferSize").intValue()) {
                delete msg;
                this->bubble("Packet Drop");
                packetDropVector.record(1);
            } else {
                buffer.insert(msg);
                this->bubble("Encolado");

                bufferSizeVector.record(buffer.getLength());
                if (!endServiceEvent->isScheduled()) {
                    scheduleAt(simTime(), endServiceEvent);
                }
            }

        } else if (msg->getKind() == 2){ // QueueBack


            if (bufferFeed.getLength() == par("bufferSize").intValue()) {
                delete msg;
                this->bubble("FeedBack Drop");
            } else {
                bufferFeed.insert(msg);
                this->bubble("Llego el feed");

                if (!endServiceEvent->isScheduled()) {
                    scheduleAt(simTime(), endServiceEvent);
                }
            }
        }
    }
}

#endif /* QUEUE */
