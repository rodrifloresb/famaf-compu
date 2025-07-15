#ifndef TRASNPORTTX
#define TRASNPORTTX

#include <string.h>
#include <omnetpp.h>
#include "packet_m.h"

using namespace omnetpp;

class TransportRx: public cSimpleModule {
private:
    cQueue buffer;
    cMessage *endServiceEvent;
    simtime_t serviceTime;
    simtime_t serviceTimeFeed;
    int packetloss;

    // Vectores
    cOutVector bufferSizeVector;
    cOutVector packetDropVector;
public:
    TransportRx();
    virtual ~TransportRx();
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
    virtual FeedbackPkt* feed();
};

Define_Module(TransportRx);

TransportRx::TransportRx() {
    endServiceEvent = NULL;
}

TransportRx::~TransportRx() {
    cancelAndDelete(endServiceEvent);
}

void TransportRx::initialize() {
    buffer.setName("buffer");
    endServiceEvent = new cMessage("endService");
    bufferSizeVector.setName("bufferSize");
    packetDropVector.setName("packetDrop");
    packetloss = 0;
}

void TransportRx::finish() {
}

FeedbackPkt * TransportRx::feed(){
    FeedbackPkt * feedback = new FeedbackPkt("feedback");
    feedback->setKind(2); // para que tx sepa que es feedback

    // max capacidad - lo ocupado
    int maxBuffer = par("bufferSize").intValue();
    int loadBuffer = buffer.getLength();
    int placeInBuffer = maxBuffer - loadBuffer;

    feedback->setPlaceInBuffer(placeInBuffer);

    if (placeInBuffer <= maxBuffer * 0.1) {
        feedback->setNext(false);
    }

    return feedback;
}

void TransportRx::handleMessage(cMessage *msg) {

    // if msg is signaling an endServiceEvent
    if (msg == endServiceEvent) {
        // if packet in buffer, send next one
        if (!buffer.isEmpty()) {
            cPacket *pkt = (cPacket*) buffer.pop();
            send(pkt, "toOut$o");

            FeedbackPkt * feedback = feed();
            send(feedback, "toApp");

            // getDuration da el tiempo que omnet
            // Cree que tardara en enviar el paquete
            serviceTime = pkt->getDuration();
            serviceTimeFeed = feedback->getDuration();
            scheduleAt(simTime() + serviceTime + serviceTimeFeed, endServiceEvent);
        }
    } else { // msg is packet or feedback

        if (buffer.getLength() == par("bufferSize").intValue()) {
            delete msg;
            this->bubble("Packet Drop");

            // metricas
            packetloss++;
            packetDropVector.record(packetloss);

        } else {
            buffer.insert(msg);
            this->bubble("Encolado");


            // Metricas

            if (packetloss > 0){
                packetloss--;
                packetDropVector.record(packetloss);
            }

            bufferSizeVector.record(buffer.getLength());


            // ---------------
            if (!endServiceEvent->isScheduled()) {
                scheduleAt(simTime(), endServiceEvent);
            }
        }
    }
}

#endif /* TRASNPORTTX */
