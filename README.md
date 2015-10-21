# alice

ups.c - sends UPS status to METRICS stream
tnh.c - sends temperature and heat to METRICS stream
comp.c - computes current system status from METRICS stream
ui.c - requests system status from whomever has it

## RFC1 - HARDWARE protocol
The HARDWARE peer produces metric data and publishes them on "METRICS" stream.

The protocol consists of the following message:
* name/key/value - The HARDWARE peer 'name' produced a metric 'key' with value 'value'.

Where
* "name" is a  unique name for HARDWARE node and 
* "key" is a unique name for HARDWARE metric
and "/" indicates a multipart message.

Furthermore the HARDWARE peer MUST send a state message at regular intervals (every 10 second), otherwise it is considered exploded. The state message uses the key = 'state' and values = [ "ON" | "OFF" ].


## RFC2 - COMPUTATION protocol
The COMPUTATION peer offers a named service to any USER peers who request it.

The protocol consists of the following messages:
* GET/key - The USER peer requests a computed value for 'key' metric 
* key/value - The COMPUTATION peer returns the requested computed value for metric key.

Where "key" is a unique name for HARDWARE metric, "value" is a string representation of the value and "/" indicates a multipart message.

