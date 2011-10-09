CHARTER CLIENT LIBRARIES
========================

Charter is a Mac OS X application available on the [Mac App Store](http://t.co/6JKesQaV). Charter allows you make realtime charts on data sent to it via a simple UDP protocol. It is pretty easy to send UDP packets from almost every modern programming language with a decent socket library, so you would much probably be able to add a realtime charting functionality to your code.

Here you will find a selection of client libraries (at the present time: Ruby, C, and Arduino), plus the protocol description, so to allow you to implement your own client.

**Would you happen to develop libraries for other language, share them! fork, edit and request a pull or - if you don't like GitHub - simply contact me: p4010 at me dot com**

Protocol
--------

The communication protocol is pretty simple and quick. The Charter client listens on a UDP port that by default is 2001, but that can be configured by the user in the application Preferences: the "Graph identifier" entry (defaults to 1) defines the actual port, which is 2000 + Graph identifier.

The *allowed commands* are:

1. `CLEAR` or `clear` clears the data buffer
2. `CLOSE` or `close` closes the connection (which must be open on the Charter app, by clicking on the On|Off switch in the toolbar)
3. a set of series with common abscissa (x) values: an `s` character followed by a space, the x value, and the sequence of y values, using a space or tab separator between each number
4. a set of series as list of couples `x,y`: an `m` character followed by a space and a list of `x,y` values (separated by a comma, no spaces), with a space or a tab between each couple.
5. `NAMES` or `names` followed by a set of `n` strings, where `n` is the number of series, sets the labels in the chart legend (i.e. the names of the series). Note that Charter must receive at least one valid data message before it can successfully set the series names.

The Charter application resets the chart every time it gets a message corresponding to a data structure different by the last one, for example a different number of series, or a `s` message after a `m` message.

Client libraries
----------------

Currently, the following libraries are available:

1. **Ruby**: complete
2. **C**: almost complete but fully functional (one method missing)
3. **Arduino**: complete (it reads analog input values from an attached Arduino and makes a stripchart)
4. **Python***