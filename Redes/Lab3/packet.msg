packet FeedbackPkt {
    // lugar disponible en el buffer
	int placeInBuffer;
	
	// transmitir siguiente paquete
	bool next = true; 	// true si esta por debajo del 90%
}
