simple Generator
{
    parameters:
        volatile double generationInterval; // sec
        int packetByteSize;
        @display("i=block/source");
    gates:
        output out;
}

simple Queue
{
    parameters:
        int bufferSize;
        @display("i=block/queue;q=buffer");
    gates:
        input in;
        output out;
}

simple Sink
{
    parameters:
        @display("i=block/sink");
    gates:
        input in;
}

simple TransportTx
{
    parameters:
        volatile double delayOutput;
        int bufferSize;
        @display("i=block/queue;q=buffer");
    gates:
        input toApp;
        inout toOut;
}

simple TransportRx
{
    parameters:
        int bufferSize;
        @display("i=block/queue;q=buffer");
    gates:
        output toApp;
        inout toOut;   
}

module nodeTx
{
    parameters:
        @display("i=block/routing");
    gates:
        output out;
        input in;
    submodules:
        gen: Generator
        {
            parameters:
                @display("p=75,50");
        }
        
        traTx: TransportTx
        {
         	parameters:
         	    @display("p=75,190");
        }
        
	connections:
	    // in (queueBack) --> traTx
	    // No queremos que el feedback
	    // se envie, traTx --> out
	    in --> traTx.toApp;
	    
	    // gen --> traTx --> Out
	    gen.out --> traTx.toOut$i ;
	    traTx.toOut$o --> out;
}

module nodeRx
{
    parameters:
        @display("i=block/routing");
    gates:
        input in;
        output out;
    submodules:
        sink: Sink
        {
            parameters:
                @display("p=75,50");
        }
        
        traRx: TransportRx
        {
         	parameters:
         	    @display("p=75,190");
        }
        
	connections:
		in --> traRx.toOut$i;
		traRx.toOut$o --> {datarate = 0.5Mbps;} --> sink.in; // Case study 1
		//traRx.toOut$o --> {datarate = 1Mbps;} --> sink.in; // Case study 2
		
		traRx.toApp --> out;
}

network Network
{
    @display("bgl=2");
    submodules:
        nodeTx: nodeTx {
            @display("p=30,30");
        }
        queueMid: Queue {
            @display("p=170,30");
        }
        nodeRx: nodeRx {
            @display("p=310,30");
        }
        queueBack: Queue {
            @display("p=170,100");
        }
    connections:
		nodeTx.out --> {datarate = 1Mbps; delay = 100us;} --> queueMid.in;
		queueMid.out --> {datarate = 1Mbps; delay = 100us;} --> nodeRx.in; // Case study 1
		//queueMid.out --> {datarate = 0.5Mbps; delay = 100us;} --> nodeRx.in; // Case study 2 
		nodeRx.out --> queueBack.in;
		queueBack.out --> nodeTx.in;
}
