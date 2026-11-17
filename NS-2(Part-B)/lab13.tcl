set ns [new Simulator]

# Open trace file and NAM animation file
set tf [open lab13.tr w]
$ns trace-all $tf
set nf [open lab13.nam w]
$ns namtrace-all $nf

# Create 6 nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]

# Colors for ping packets
$ns color 1 "blue"
$ns color 2 "orange"

# Labels for NAM
$n0 label "Ping 0 (Blue)"
$n1 label "Ping 1 (Orange)"
$n2 label "Router 2"
$n3 label "Router 3"
$n4 label "Ping 4"
$n5 label "Ping 5"

# Duplex links: 0.5Mb bottleneck links cause congestion
$ns duplex-link $n0 $n2 0.5Mb 10ms DropTail
$ns duplex-link $n1 $n2 0.5Mb 10ms DropTail
$ns duplex-link $n2 $n3 0.5Mb 10ms DropTail
$ns duplex-link $n3 $n4 0.5Mb 10ms DropTail
$ns duplex-link $n3 $n5 0.5Mb 10ms DropTail

# Attach Ping agents to nodes 0, 1, 4, 5
set ping0 [new Agent/Ping]
$ping0 set class_ 1
$ns attach-agent $n0 $ping0

set ping1 [new Agent/Ping]
$ping1 set class_ 2
$ns attach-agent $n1 $ping1

set ping4 [new Agent/Ping]
$ns attach-agent $n4 $ping4

set ping5 [new Agent/Ping]
$ns attach-agent $n5 $ping5

# Connect ping senders to receivers: 0 -> 4 and 1 -> 5
$ns connect $ping0 $ping4
$ns connect $ping1 $ping5

# Background UDP traffic from n0 to n4 to create congestion
set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0
set null4 [new Agent/Null]
$ns attach-agent $n4 $null4
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp0
$cbr set packetSize_ 512
$cbr set interval_ 0.001
$ns connect $udp0 $null4

# Procedure executed when a ping reply arrives back
Agent/Ping instproc recv {from rtt} {
    $self instvar node_
    puts "Node [$node_ id] received reply from $from with RTT $rtt ms"
}

# Finish procedure
proc finish {} {
    global ns tf nf
    $ns flush-trace
    close $tf
    close $nf
    exec nam lab13.nam &
    exit 0
}

# Schedule 10 ping sends from each source (every 0.1s)
for {set i 1} {$i <= 10} {incr i} {
    $ns at [expr $i * 0.1] "$ping0 send"
    $ns at [expr $i * 0.1] "$ping1 send"
}

# Start/stop background congestion traffic
$ns at 0.2 "$cbr start"
$ns at 4.0 "$cbr stop"
$ns at 5.5 "finish"

$ns run
