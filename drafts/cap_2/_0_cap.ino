#include <CapacitiveSensor.h>
#include <AverageValue.h>

CapacitiveSensor cs = CapacitiveSensor(2,3);  

const byte AVERAGE_SIZE = 50;
AverageValue<long> av(AVERAGE_SIZE);  

const long LOW_CAP = 100;
const long HIGH_CAP = 1000;
const long LOW_MAP = 0;
const long HIGH_MAP = 100;


void setup_cap() {
   cs.set_CS_AutocaL_Millis(0xFFFFFFFF); 
   
   cs.set_CS_Timeout_Millis(50);
}

struct cap_result {
  long value;
  long capped;
  long mapped;
};

struct cap_result getSense() {
    unsigned long now = millis();

    struct cap_result res;
    
    long sense = cs.capacitiveSensor(30);
    av.push(sense);

    long average = av.average();

    res.value = average;
    res.capped = constrain(average, LOW_CAP, HIGH_CAP);
    res.mapped = map(res.capped, LOW_CAP, HIGH_CAP, LOW_MAP, HIGH_MAP);

    return res;
}
