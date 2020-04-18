`test1` in an initial POC to try to test some matching algorithm.

`test2` generates a lot of "connections" with session variables: it is meant to mimic ProxySQL connections and tracking of session variables.
If performs 4 different algorithms to search for mis-matches, with incremental number of tracked variables (16, 24, 64, 128).

An important thing to note is how performance *drastically* change based on the number of connections.
I assume this depends from the fact that dataset doesn't fit anymore in CPU cache.
