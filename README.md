# alice

## RFC1 - HARDWARE protocol

The HARDWARE peer produces metric data and publishes them on "METRICS" stream with topic "<key>.<name>".

The protocol consists of the following message:
* name/key/value - The HARDWARE peer 'name' produced a metric 'key' with value 'value'.

Where "name" is a  unique name for HARDWARE node, "key" is a unique name for HARDWARE metric and "/" indicates a multipart message.

Furthermore the HARDWARE peer MUST send a state message at regular intervals (every 10 second), otherwise it is considered exploded. The state message uses the key = 'state' and values = [ "ON" | "OFF" ].

## RFC2 - COMPUTATION protocol

The COMPUTATION peer offers a named service to any USER peers who request it.

The protocol consists of the following messages:
* GET/key - The USER peer requests a computed value for 'key' metric
* key/value - The COMPUTATION peer returns the requested computed value for metric key.

Where "key" is a unique name for HARDWARE metric, "value" is a string representation of the value and "/" indicates a multipart message.

## Parts

* ups.c - Implements HARDWARE protocol. Produces ups metric data.
* tnh.c - Implements. HARDWARE protocol. Produces temperature, humidity metric data.
* comp.c - Implements COMPUTATION protocol. Offers 'status' service which computes current system status from METRICS stream.
* ui.c - requests system status from whomever has it.
