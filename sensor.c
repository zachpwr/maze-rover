unsigned char getSensorData() {
    return get_QTR_value();
}

int lookForTurn(unsigned char readings[2]) {

}

int lookForCurve(unsigned char last_state, unsigned char next_state) {
    if(last_state < next_state) {
        // Curve?
    } else if(last_state > next_state) {
        // Curve?
    }
}

int lookForTee(unsigned char reading) {
    if(reading == 0xFF) {

    }
}

int lookForDeadEnd(unsigned char readings[2]) {

}

int lookForIntersection(unsigned char readings[2]) {

}

int isThreeOrFourWayIntersection() {

}
