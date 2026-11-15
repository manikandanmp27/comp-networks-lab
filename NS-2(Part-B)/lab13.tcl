set ns [new Simulator]

set tf [open lab13.tr w]            ;# trace file (awk reads this)
$ns trace-all $tf
set nf [open lab13.nam w]           ;# nam file (animation)
$ns namtrace-all $nf

# Create 6 nodes
for {set i 0} {$i < 6} {incr i} {
    set n$i [$ns node]
}

# Links: 0.5 Mb is slow, so the queue fills and packets drop
$ns duplex-link $n0 $n2 0.5Mb 10ms DropTail
$ns duplex-link $n1 $n2 0.5Mb 10ms DropTail
$ns duplex-link $n2 $n3 0.5Mb 10ms DropTail
$ns duplex-link $n3 $n4 0.5Mb 10ms DropTail
$ns duplex-link $n3 $n5 0.5Mb 10ms DropTail

# Ping agents on nodes 0, 1, 4, 5
set ping0 [new Agent/Ping]
$ns attach-agent $n0 $ping0
set ping1 [new Agent/Ping]
$ns attach-agent $n1 $ping1
set ping4 [new Agent/Ping]
$ns attach-agent $n4 $ping4
set ping5 [new Agent/Ping]
$ns attach-agent $n5 $ping5

$ping0 set packetSize_ 500
$ping1 set packetSize_ 500

# Connect ping senders to receivers: 0 -> 4 and 1 -> 5
$ns connect $ping0 $ping4
$ns connect $ping1 $ping5

# Background UDP traffic from n0 to n4 to cause congestion
set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0
set null4 [new Agent/Null]
$ns attach-agent $n4 $null4
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp0
$cbr set packetSize_ 512
$cbr set interval_ 0.001            ;# fast: 512 B every 1 ms
$ns connect $udp0 $null4

# Runs when a ping reply comes back
Agent/Ping instproc recv {from rtt} {
    $self instvar node_
    puts "Node [$node_ id] received reply from $from, RTT = $rtt ms"
}

proc finish {} {
    global ns tf nf
    $ns flush-trace
    close $tf
    close $nf
    exec nam lab13.nam &
    exit 0
}

# Send 10 pings from each source (every 0.1 s) using a loop
for {set i 1} {$i <= 10} {incr i} {
    $ns at [expr $i * 0.1] "$ping0 send"
    $ns at [expr $i * 0.1] "$ping1 send"
}

$ns at 0.2 "$cbr start"
$ns at 4.0 "$cbr stop"
$ns at 5.5 "finish"
$ns run