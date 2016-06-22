# netbroken

Server should NOT be sending out a packet reactively or a packet per ship.


Once a packet comes from a new IP, we should ALWAYS be broadcasting updates to that IP (until a timeout occurs, which means that a packet hasn't been recieved in some such amount of time).

Also, one packet for ALL changes/updates should be sent out, not one per ship.
